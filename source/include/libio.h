/*******************************************************************************
 * Copyright (c) 2010, Jean-David Gadina - www.xs-labs.com
 * Distributed under the Boost Software License, Version 1.0.
 * 
 * Boost Software License - Version 1.0 - August 17th, 2003
 * 
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ******************************************************************************/

/* $Id$ */

/*!
 * @file        libio.h
 * @copyright   (c) 2011 - Jean-David Gadina - www.xs-labs.com
 * @abstract    IO functions
 */

#ifndef _LIBIO_H_
#define _LIBIO_H_
#pragma once

#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Definition of the boolean datatype if not enabled */
#ifndef __bool_true_false_are_defined
    #define bool                            _Bool
    #define true                            1
    #define false                           0
    #define __bool_true_false_are_defined   1
#endif

#ifdef stdin
    #undef stdin
#endif

#ifdef stdout
    #undef stdout
#endif

#ifdef stderr
    #undef stderr
#endif

#define FILE                                struct libio_file
#define stdin                               &( libio_stdin )
#define stdout                              &( libio_stdout )
#define stderr                              &( libio_stderr )
#define fopen( filename, mode )             libio_fopen( filename, mode )
#define fflush( stream )                    libio_fflush( stream )
#define fclose( stream )                    libio_fclose( stream )
#define fprintf( stream, ... )              libio_fprintf( stream, __VA_ARGS__ )
#define vfprintf( stream, format, arg )     libio_vfprintf( stream, format, arg )
#define fgetc( stream )                     libio_fgetc( stream )
#define fputc( c, stream )                  libio_fputc( c, stream )
#define fputs( s, stream )                  libio_fputs( s, stream )
#define fread( ptr, size, nobj, stream )    libio_fread( ptr, size, nobj, stream )
#define fwrite( ptr, size, nobj, stream )   libio_fwrite( ptr, size, nobj, stream )
#define fseek( stream, offset, origin )     libio_fseek( stream, offset, origin )
#define ftell( stream )                     libio_ftell( stream )
#define rewind( stream )                    libio_rewind( stream )
#define fgetpos( stream, ptr )              libio_fgetpos( stream, ptr )
#define fsetpos( stream, ptr )              libio_fsetpos( stream, ptr )
#define clearerr( stream )                  libio_clearerr( stream )
#define feof( stream )                      libio_feof( stream )
#define ferror( stream )                    libio_ferror( stream )
    
    struct libio_file;
    extern struct libio_file libio_stdin;
    extern struct libio_file libio_stdout;
    extern struct libio_file libio_stderr;
    
    /*!
     * Opens file named filename and returns a stream, or NULL on failure.
     * Mode may be one of the following for text files:
     * 
     *      - "r"   text reading
     *      - "w"   text writing
     *      - "a"   text append
     *      - "r+"  text update (reading and writing)
     *      - "w+"  text update discarding previous content (if any)
     *      - "a+"  text append, reading, and writing at end
     * 
     * or one of those strings with b included (after the first character),
     * for binary files.
     */
    struct libio_file * libio_fopen( const char * filename, const char * mode );
    
    /*!
     * Flushes stream stream and returns zero on success or EOF on error.
     * Effect undefined for input stream. fflush(NULL) flushes all output
     * streams.
     */
    int libio_fflush( struct libio_file * stream );
    
    /*!
     * Closes stream stream (after flushing, if output stream). Returns EOF on
     * error, zero otherwise.
     */
    int libio_fclose( struct libio_file * stream );
    
    /*!
     * Converts (according to format format) and writes output to stream stream.
     * Number of characters written, or negative value on error, is returned.
     * Conversion specifications consist of:
     *      
     *      -   %
     *      -   (optional) flag:
     *          
     *          -       left adjust
     *          +       always sign
     *          space   space if no sign
     *          0       zero pad
     *          #       Alternate form: for conversion character o, first digit will
     *                  be zero, for [xX], prefix 0x or 0X to non-zero value, for
     *                  [eEfgG], always decimal point, for [gG] trailing zeros not
     *                  removed.
     *          
     *      -   (optional) minimum width: if specified as *, value taken from next
     *          argument (which must be int).
     *      -   (optional) . (separating width from precision):
     *      -   (optional) precision: for conversion character s, maximum characters
     *          to be printed from the string, for [eEf], digits after decimal
     *          point, for [gG], significant digits, for an integer, minimum number
     *          of digits to be printed. If specified as *, value taken from next
     *          argument (which must be int).
     *      -   (optional) length modifier:
     *              
     *          h       short or unsigned short
     *          l       long or unsigned long
     *          L       long double
     *          
     *      conversion character:
     *          
     *          d,i     int argument, printed in signed decimal notation
     *          o       int argument, printed in unsigned octal notation
     *          x,X     int argument, printed in unsigned hexadecimal notation
     *          u       int argument, printed in unsigned decimal notation
     *          c       int argument, printed as single character
     *          s       char* argument
     *          f       double argument, printed with format [-]mmm.ddd
     *          e,E     double argument, printed with format [-]m.dddddd(e|E)(+|-)xx
     *          g,G     double argument
     *          p       void * argument, printed as pointer
     *          n       int * argument : the number of characters written to this
     *                  point is written into argument
     *          %       no argument; prints %  
     */
    int libio_fprintf( struct libio_file * stream, const char * format, ... );
    
    /*!
     * Equivalent to fprintf with variable argument list replaced by arg, which must
     * have been initialised by the va_start macro (and may have been used in calls
     * to va_arg).
     */
    int libio_vfprintf( struct libio_file * stream, const char * format, va_list arg );
    
    /*!
     * Returns next character from (input) stream stream, or EOF on end-of-file
     * or error.
     */
    int libio_fgetc( struct libio_file * stream );
    
    /*!
     * Writes c, to stream stream. Returns c, or EOF on error.
     */
    int libio_fputc( int c, struct libio_file * stream );
    
    /*!
     * Writes s, to (output) stream stream. Returns non-negative on success or
     * EOF on error.
     */
    int libio_fputs( const char * s, struct libio_file * stream );
    
    /*!
     * Reads (at most) nobj objects of size size from stream stream into ptr and
     * returns number of objects read. (feof and ferror can be used to check
     * status.)
     */
    size_t libio_fread( void * ptr, size_t size, size_t nobj, struct libio_file * stream );
    
    /*!
     * Writes to stream stream, nobj objects of size size from array ptr.
     * Returns number of objects written.
     */
    size_t libio_fwrite( const void * ptr, size_t size, size_t nobj, struct libio_file * stream );
    
    /*!
     * Sets file position for stream stream and clears end-of-file indicator.
     * For a binary stream, file position is set to offset bytes from the
     * position indicated by origin: beginning of file for SEEK_SET, current
     * position for SEEK_CUR, or end of file for SEEK_END. Behaviour is similar
     * for a text stream, but offset must be zero or, for SEEK_SET only, a value
     * returned by ftell.
     * Returns non-zero on error.
     */
    int libio_fseek( struct libio_file * stream, long offset, int origin );
    
    /*!
     * Returns current file position for stream stream, or -1 on error.
     */
    long libio_ftell( struct libio_file * stream );
    
    /*!
     * Equivalent to fseek( stream, 0L, SEEK_SET ); clearerr( stream ).
     */
    void libio_rewind( struct libio_file * stream );
    
    /*!
     * Stores current file position for stream stream in * ptr.
     * Returns non-zero on error.
     */
    int libio_fgetpos( struct libio_file * stream, fpos_t * ptr );
    
    /*!
     * Sets current position of stream stream to * ptr.
     * Returns non-zero on error.
     */
    int libio_fsetpos( struct libio_file * stream, const fpos_t * ptr );
    
    /*!
     * Clears end-of-file and error indicators for stream stream.
     */
    void libio_clearerr( struct libio_file * stream );
    
    /*!
     * Returns non-zero if end-of-file indicator is set for stream stream.
     */
    int libio_feof( struct libio_file * stream );
    
    /*!
     * Returns non-zero if error indicator is set for stream stream.
     */
    int libio_ferror( struct libio_file * stream );
    
    /*!
     * Gets the filename associated to the stream-
     */
    const char * fname( struct libio_file * stream );
    
    /*!
     * Gets the stream's open mode
     */
    const char * fmode( struct libio_file * stream );
    
    /*!
     * Returns true if the file is readable
     */
    bool freadable( struct libio_file * stream );
    
    /*!
     * Returns true if the file is writeable
     */
    bool fwriteable( struct libio_file * stream );
    
    /*!
     * Copies a file to another destination.
     */
    bool fcopy( char * name, char * new_name );
    
    /*!
     * Gets the next bit in the stream
     */
    int fgetbit( struct libio_file * stream );
    
    /*!
     * Writes a bit in the stream
     */
    int fputbit( struct libio_file * stream, uint8_t bit );
    
    /*!
     * Gets bits from the stream
     */
    int fgetbits( struct libio_file * stream, unsigned int count );
    
    /*!
     * Writes bits to the stream
     */
    int fputbits( struct libio_file * stream, uint64_t bits, unsigned int count );
    
    /*!
     * 
     */
    dev_t fdevid( struct libio_file * stream );
    
    /*!
     * 
     */
    ino_t finoid( struct libio_file * stream );
    
    /*!
     * 
     */
    nlink_t fnlink( struct libio_file * stream );
    
    /*!
     * 
     */
    uid_t fuid( struct libio_file * stream );
    
    /*!
     * 
     */
    gid_t fgid( struct libio_file * stream );
    
    /*!
     * 
     */
    size_t fsize( struct libio_file * stream );
    
    /*!
     * 
     */
    double fhsize( struct libio_file * stream, char unit[] );
    
    /*!
     * 
     */
    time_t fatime( struct libio_file * stream );
    
    /*!
     * 
     */
    time_t fmtime( struct libio_file * stream );
    
    /*!
     * 
     */
    time_t fctime( struct libio_file * stream );
    
    /*!
     * 
     */
    bool fblock( struct libio_file * stream );
    
    /*!
     * 
     */
    bool fchar( struct libio_file * stream );
    
    /*!
     * 
     */
    bool ffifo( struct libio_file * stream );
    
    /*!
     * 
     */
    bool freg( struct libio_file * stream );
    
    /*!
     * 
     */
    bool fdir( struct libio_file * stream );
    
    /*!
     * 
     */
    bool flink( struct libio_file * stream );
    
    /*!
     * 
     */
    bool fsock( struct libio_file * stream );
    
    /*!
     * 
     */
    bool fuser_r( struct libio_file * stream );
    
    /*!
     * 
     */
    bool fuser_w( struct libio_file * stream );
    
    /*!
     * 
     */
    bool fuser_x( struct libio_file * stream );
    
    /*!
     * 
     */
    bool fgroup_r( struct libio_file * stream );
    
    /*!
     * 
     */
    bool fgroup_w( struct libio_file * stream );
    
    /*!
     * 
     */
    bool fgroup_x( struct libio_file * stream );
    
    /*!
     * 
     */
    bool fother_r( struct libio_file * stream );
    
    /*!
     * 
     */
    bool fother_w( struct libio_file * stream );
    
    /*!
     * 
     */
    bool fother_x( struct libio_file * stream );
    
    /*!
     * 
     */
    bool fsuid( struct libio_file * stream );
    
    /*!
     * 
     */
    bool fsgid( struct libio_file * stream );
    
#ifdef __cplusplus
}
#endif

#endif /* _LIBIO_H_ */
