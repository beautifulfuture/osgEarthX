/**********************************************************************
 * $Id: cpl_recode_iconv.cpp 21755 2011-02-19 18:27:55Z rouault $
 *
 * Name:     cpl_recode_iconv.cpp
 * Project:  CPL - Common Portability Library
 * Purpose:  Character set recoding and char/wchar_t conversions implemented
 *           using the iconv() functionality.
 * Author:   Andrey Kiselev, dron@ak4719.spb.edu
 *
 **********************************************************************
 * Copyright (c) 2011, Andrey Kiselev <dron@ak4719.spb.edu>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 **********************************************************************/

#include "cpl_port.h"

CPL_CVSID("$Id: cpl_recode_iconv.cpp 21755 2011-02-19 18:27:55Z rouault $");

#ifdef CPL_RECODE_ICONV

#include <iconv.h>
#include "cpl_string.h"

#define CPL_RECODE_DSTBUF_SIZE 32768

/************************************************************************/
/*                          CPLRecodeIconv()                            */
/************************************************************************/

/**
 * Convert a string from a source encoding to a destination encoding
 * using the iconv() function.
 *
 * If an error occurs an error may, or may not be posted with CPLError(). 
 *
 * @param pszSource a NULL terminated string.
 * @param pszSrcEncoding the source encoding.
 * @param pszDstEncoding the destination encoding.
 *
 * @return a NULL terminated string which should be freed with CPLFree().
 */

char *CPLRecodeIconv( const char *pszSource, 
                      const char *pszSrcEncoding, 
                      const char *pszDstEncoding )

{
    iconv_t sConv;

    sConv = iconv_open( pszDstEncoding, pszSrcEncoding );

    if ( sConv == (iconv_t)-1 )
    {
        CPLError( CE_Warning, CPLE_AppDefined, 
                  "Recode from %s to %s failed with the error: \"%s\".", 
                  pszSrcEncoding, pszDstEncoding, strerror(errno) );

        return CPLStrdup(pszSource);
    }

/* -------------------------------------------------------------------- */
/*      XXX: There is a portability issue: iconv() function could be    */
/*      declared differently on different platforms. The second         */
/*      argument could be declared as char** (as POSIX defines) or      */
/*      as a const char**. Handle it with the ICONV_CONST macro here.   */
/* -------------------------------------------------------------------- */
    ICONV_CONST char *pszSrcBuf = (ICONV_CONST char *)pszSource;
    size_t  nSrcLen = strlen( pszSource );
    size_t  nDstCurLen = MAX(CPL_RECODE_DSTBUF_SIZE, nSrcLen + 1);
    size_t  nDstLen = nDstCurLen;
    char    *pszDestination = (char *)CPLCalloc( nDstCurLen, sizeof(char) );
    char    *pszDstBuf = pszDestination;

    while ( nSrcLen > 0 )
    {
        size_t  nConverted =
            iconv( sConv, &pszSrcBuf, &nSrcLen, &pszDstBuf, &nDstLen );

        if ( nConverted == (size_t)-1 )
        {
            if ( errno == EILSEQ )
            {
                // Silently skip the invalid sequence in the input string.
                nSrcLen--, pszSrcBuf++;
                continue;
            }

            else if ( errno == E2BIG )
            {
                // We are running out of the output buffer.
                // Dynamically increase the buffer size.
                size_t nTmp = nDstCurLen;
                nDstCurLen *= 2;
                pszDestination =
                    (char *)CPLRealloc( pszDestination, nDstCurLen );
                pszDstBuf = pszDestination + nTmp - nDstLen;
                nDstLen += nDstCurLen - nTmp;
                continue;
            }

            else
                break;
        }
    }

    pszDestination[nDstCurLen - nDstLen] = '\0';

    iconv_close( sConv );

    return pszDestination;
}

/************************************************************************/
/*                      CPLRecodeFromWCharIconv()                       */
/************************************************************************/

/**
 * Convert wchar_t string to UTF-8. 
 *
 * Convert a wchar_t string into a multibyte utf-8 string
 * using the iconv() function.
 *
 * Note that the wchar_t type varies in size on different systems. On
 * win32 it is normally 2 bytes, and on unix 4 bytes.
 *
 * If an error occurs an error may, or may not be posted with CPLError(). 
 *
 * @param pwszSource the source wchar_t string, terminated with a 0 wchar_t.
 * @param pszSrcEncoding the source encoding, typically CPL_ENC_UCS2.
 * @param pszDstEncoding the destination encoding, typically CPL_ENC_UTF8.
 *
 * @return a zero terminated multi-byte string which should be freed with 
 * CPLFree(), or NULL if an error occurs. 
 */

char *CPLRecodeFromWCharIconv( const wchar_t *pwszSource, 
                               const char *pszSrcEncoding, 
                               const char *pszDstEncoding )

{
    iconv_t sConv;

    sConv = iconv_open( pszDstEncoding, pszSrcEncoding );

    if ( sConv == (iconv_t)-1 )
    {
        CPLError( CE_Warning, CPLE_AppDefined, 
                  "Recode from %s to %s failed with the error: \"%s\".", 
                  pszSrcEncoding, pszDstEncoding, strerror(errno) );

        return CPLStrdup( "" );
    }

/* -------------------------------------------------------------------- */
/*      XXX: There is a portability issue: iconv() function could be    */
/*      declared differently on different platforms. The second         */
/*      argument could be declared as char** (as POSIX defines) or      */
/*      as a const char**. Handle it with the ICONV_CONST macro here.   */
/* -------------------------------------------------------------------- */
    ICONV_CONST char *pszSrcBuf = (ICONV_CONST char *)pwszSource;

/* -------------------------------------------------------------------- */
/*      What is the source length.                                      */
/*      TODO: use wcslen() if available.                                */
/* -------------------------------------------------------------------- */
    size_t  nSrcLen = 0;

    while ( pwszSource[nSrcLen] != 0 )
        nSrcLen++;

    /* iconv expects a number of bytes, not characters */
    nSrcLen *= sizeof(wchar_t);

/* -------------------------------------------------------------------- */
/*      Allocate destination buffer.                                    */
/* -------------------------------------------------------------------- */
    size_t  nDstCurLen = MAX(CPL_RECODE_DSTBUF_SIZE, nSrcLen + 1);
    size_t  nDstLen = nDstCurLen;
    char    *pszDestination = (char *)CPLCalloc( nDstCurLen, sizeof(char) );
    char    *pszDstBuf = pszDestination;

    while ( nSrcLen > 0 )
    {
        size_t  nConverted =
            iconv( sConv, &pszSrcBuf, &nSrcLen, &pszDstBuf, &nDstLen );

        if ( nConverted == (size_t)-1 )
        {
            if ( errno == EILSEQ )
            {
                // Silently skip the invalid sequence in the input string.
                nSrcLen--;
                pszSrcBuf += sizeof(wchar_t);
                continue;
            }

            else if ( errno == E2BIG )
            {
                // We are running out of the output buffer.
                // Dynamically increase the buffer size.
                size_t nTmp = nDstCurLen;
                nDstCurLen *= 2;
                pszDestination =
                    (char *)CPLRealloc( pszDestination, nDstCurLen );
                pszDstBuf = pszDestination + nTmp - nDstLen;
                nDstLen += nDstCurLen - nTmp;
                continue;
            }

            else
                break;
        }
    }

    pszDestination[nDstCurLen - nDstLen] = '\0';

    iconv_close( sConv );

    return pszDestination;
}

/************************************************************************/
/*                        CPLRecodeToWCharIconv()                       */
/************************************************************************/

/**
 * Convert UTF-8 string to a wchar_t string.
 *
 * Convert a 8bit, multi-byte per character input string into a wide
 * character (wchar_t) string using the iconv() function.
 *
 * Note that the wchar_t type varies in size on different systems. On
 * win32 it is normally 2 bytes, and on unix 4 bytes.
 *
 * If an error occurs an error may, or may not be posted with CPLError(). 
 *
 * @param pszSource input multi-byte character string.
 * @param pszSrcEncoding source encoding, typically CPL_ENC_UTF8.
 * @param pszDstEncoding destination encoding, typically CPL_ENC_UCS2. 
 *
 * @return the zero terminated wchar_t string (to be freed with CPLFree()) or
 * NULL on error.
 */

wchar_t *CPLRecodeToWCharIconv( const char *pszSource,
                                const char *pszSrcEncoding, 
                                const char *pszDstEncoding )

{
    return (wchar_t *)CPLRecodeIconv( pszSource,
                                      pszSrcEncoding, pszDstEncoding);
}

#endif /* CPL_RECODE_ICONV */
