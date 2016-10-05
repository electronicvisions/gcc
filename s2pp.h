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

#define s2pp_fxvstax __builtin_s2pp_fxvstax
#define s2pp_fxvlax __builtin_s2pp_fxvlax
#define vec_st __builtin_vec_fxvst
#define vec_ld __builtin_vec_fxvld

#define vec_splat __builtin_vec_splatx
#define vec_splats __builtin_vec_splats
#define vec_splatb __builtin_vec_fxvsplatb
#define vec_splath __builtin_vec_fxvsplath

#define s2pp_fxvaddbm __builtin_vec_fxvaddbm
#define s2pp_fxvaddhm __builtin_vec_fxvaddhm

#define vec_add __builtin_vec_addx

#endif /* _S2PP_H */
