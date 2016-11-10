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

#define fxv_stax vec_st
#define vec_st __builtin_vec_st
#define fxv_lax vec_ld
#define vec_ld __builtin_vec_ld

#define vec_sel __builtin_vec_fxvsel
#define fxv_sel vec_sel
#define vec_splat __builtin_vec_splat

#define vec_extract __builtin_vec_extract
#define vec_insert __builtin_vec_insert
#define vec_splats __builtin_vec_splats
#define vec_promote __builtin_vec_promote

#define vec_add __builtin_vec_fxvadd
#define fxv_add vec_add
#define vec_addbm vec_fxvaddbm
#define vec_addhm vec_fxvaddhm
#define fxv_addbm __builtin_vec_fxvaddbm
#define fxv_addhm __builtin_vec_fxvaddhm

#define vec_sub __builtin_vec_fxvsub
#define vec_fxvsub vec_sub
//#define vec_fxvsubbs __builtin_vec_fxvsubbs
#define vec_subbm vec_fxvsubbm
#define vec_subhm vec_fxvsubhm
#define fxv_subbm __builtin_vec_fxvsubbm
#define fxv_subhm __builtin_vec_fxvsubhm
//#define vec_fxvsubhs __builtin_vec_fxvsubhs

#define vec_sh __builtin_vec_fxvsh
#define fxv_shb __builtin_vec_fxvshb
#define fxv_shh __builtin_vec_fxvshh

#define fxv_splatb vec_splat_s8
#define fxv_splath vec_splat_s16
#define vec_splat_s8(x) __builtin_s2pp_fxvsplatb ((x))
#define vec_splat_s16(x) __builtin_s2pp_fxvsplath ((x))
#define vec_splat_u8(x) ((__vector unsigned char) vec_splat_s8 ((x)))
#define vec_splat_u16(x) ((__vector unsigned short) vec_splat_s16 ((x)))


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
