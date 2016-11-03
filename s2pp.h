/* _S2PP_H */
#ifndef _S2PP_H
#define _S2PP_H 1

#if !defined(__S2PP__)
#error Use the "-ms2pp" flag to enable s2pp support
#endif

#define vector __vector
#define pixel __pixel
#define bool __bool

/* Condition register codes for s2pp predicates. */

#define __C_EQ		3
#define __C_GT		1
#define __C_LT		2

#define vec_fxvstax vec_st
#define vec_st __builtin_vec_st
#define vec_fxvlax vec_ld
#define vec_ld __builtin_vec_ld

#define vec_sel __builtin_vec_fxvsel
#define vec_splat __builtin_vec_splat

#define vec_extract __builtin_vec_extract
#define vec_insert __builtin_vec_insert
#define vec_splats __builtin_vec_splats
#define vec_promote __builtin_vec_promote

#define vec_add __builtin_vec_fxvadd
#define vec_vaddubm vec_fxvaddbm
#define vec_vadduhm vec_fxvaddhm
#define vec_fxvaddbm __builtin_vec_fxvaddbm
#define vec_fxvaddhm __builtin_vec_fxvaddhm

#define vec_fxvsplatb vec_splat_s8
#define vec_fxvsplath vec_splat_s16
#define vec_splat_s8(x) __builtin_s2pp_fxvsplatb ((x))
#define vec_splat_s16(x) __builtin_s2pp_fxvsplath ((x))
#define vec_splat_u8(x) ((__vector unsigned char) vec_splat_s8 ((x)))
#define vec_splat_u16(x) ((__vector unsigned short) vec_splat_s16 ((x)))
//#define vec_splatb(x) __builtin_s2pp_fxvsplatb ((x))
//#define vec_splath(x) __builtin_s2pp_fxvsplath ((x))



///* Given the vec_step of a type, return the corresponding bool type.  */
//template <int STEP> class __s2pp_bool_ret { };
//template <> class __s2pp_bool_ret <4> {
//  typedef __vector __bool int __ret;
//};
//template <> class __s2pp_bool_ret <8> {
//  typedef __vector __bool short __ret;
//};
//template <> class __s2pp_bool_ret <16> {
//  typedef __vector __bool char __ret;
//};

#endif /* _S2PP_H */
