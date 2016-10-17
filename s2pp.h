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

#define __C_EQ		0
#define __C_GT		1
#define __C_LT		2

#define s2pp_stax __builtin_s2pp_stax
#define s2pp_lax __builtin_s2pp_lax
#define vec_st __builtin_vec_st
#define vec_ld __builtin_vec_ld

#define vec_splat __builtin_vec_splatx
#define vec_splats __builtin_vec_splats
//#define vec_splatb __builtin_vec_fxvsplatb
//#define vec_splath __builtin_vec_fxvsplath
#define vec_splatb(x) __builtin_s2pp_fxvsplatb ((x))
#define vec_splath(x) __builtin_s2pp_fxvsplath ((x))

#define s2pp_fxvaddbm __builtin_vec_fxvaddbm
#define s2pp_fxvaddhm __builtin_vec_fxvaddhm

#define vec_add __builtin_vec_addx

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
