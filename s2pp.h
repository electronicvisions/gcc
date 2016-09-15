/* _S2PP_H */
#ifndef _S2PP_H
#define _S2PP_H 1

#if !defined(__S2PP__)
#error Use the "-ms2pp" flag to enable s2pp support
#endif

/* Condition register codes for s2pp predicates. */

#define __C_EQ		0
#define __C_GT		1
#define __C_LT		2

#define s2pp_fxvstax __builtin_s2pp_fxvstax
#define s2pp_fxvlax __builtin_s2pp_fxvlax

#define s2pp_fxvaddbm __builtin_s2pp_fxvaddbm
#define s2pp_fxvaddhm __builtin_s2pp_fxvaddhm


#endif /* _S2PP_H */
