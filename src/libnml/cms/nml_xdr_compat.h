/* Fixed-width XDR routines used by cms_xup.cc that some Sun RPC
   implementations lack. Native routines are used whenever declared;
   HAVE_DECL_* come from config.h (or confdefs.h inside configure). */
#ifndef NML_XDR_COMPAT_H
#define NML_XDR_COMPAT_H

#include <rpc/rpc.h>
#include <stdint.h>

#if !defined(HAVE_DECL_XDR_INT8_T) || !defined(HAVE_DECL_XDR_UINT8_T) || \
    !defined(HAVE_DECL_XDR_UINT16_T) || !defined(HAVE_DECL_XDR_UINT32_T) || \
    !defined(HAVE_DECL_XDR_UINT64_T)
#error "include config.h before nml_xdr_compat.h"
#endif

/* Same 4/8-byte encodings; libtirpc implements these names the same way. */
#if !HAVE_DECL_XDR_UINT16_T
#define xdr_uint16_t xdr_u_int16_t
#endif
#if !HAVE_DECL_XDR_UINT32_T
#define xdr_uint32_t xdr_u_int32_t
#endif
#if !HAVE_DECL_XDR_UINT64_T
#define xdr_uint64_t xdr_u_int64_t
#endif

/* One 32-bit XDR word, narrowed on decode without range checks,
   as glibc and libtirpc do. */
#if !HAVE_DECL_XDR_INT8_T
static inline bool_t nml_xdr_int8_t(XDR *xdrs, int8_t *p)
{
    int32_t t;
    switch (xdrs->x_op) {
    case XDR_ENCODE:
        t = *p;
        return (xdr_int32_t)(xdrs, &t);
    case XDR_DECODE:
        if (!(xdr_int32_t)(xdrs, &t))
            return FALSE;
        *p = (int8_t) t;
        return TRUE;
    case XDR_FREE:
        return TRUE;
    }
    return FALSE;
}
#define xdr_int8_t nml_xdr_int8_t
#endif

#if !HAVE_DECL_XDR_UINT8_T
static inline bool_t nml_xdr_uint8_t(XDR *xdrs, uint8_t *p)
{
    uint32_t t;
    switch (xdrs->x_op) {
    case XDR_ENCODE:
        t = *p;
        return (xdr_u_int32_t)(xdrs, &t);
    case XDR_DECODE:
        if (!(xdr_u_int32_t)(xdrs, &t))
            return FALSE;
        *p = (uint8_t) t;
        return TRUE;
    case XDR_FREE:
        return TRUE;
    }
    return FALSE;
}
#define xdr_uint8_t nml_xdr_uint8_t
#endif

#endif
