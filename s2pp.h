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

#define fxv_in __builtin_vec_in
#define fxv_out __builtin_vec_out

#define fxv_sel_eq __builtin_vec_fxvsel_eq

#define vec_sel __builtin_vec_fxvsel
#define fxv_sel vec_sel
#define vec_splat __builtin_vec_splat

#define vec_extract __builtin_vec_extract
#define vec_insert __builtin_vec_insert
#define vec_splats __builtin_vec_splats
#define vec_promote __builtin_vec_promote

#define vec_add __builtin_vec_fxvadd
#define vec_addbm vec_fxvaddbm
#define vec_addhm vec_fxvaddhm
#define fxv_addbm __builtin_vec_fxvaddbm
#define fxv_addhm __builtin_vec_fxvaddhm
#define vec_addfs __builtin_vec_fxvaddfs
#define vec_addbfs vec_fxvaddbfs
#define vec_addhfs vec_fxvaddhfs
#define fxv_addbfs __builtin_vec_fxvaddbfs
#define fxv_addhfs __builtin_vec_fxvaddhfs

#define fxv_addm_c __builtin_vec_fxvaddm_c
#define fxv_addbm_c __builtin_vec_fxvaddbm_c
#define fxv_addhm_c __builtin_vec_fxvaddhm_c
#define vec_addfs_c __builtin_vec_fxvaddfs_c
#define fxv_addbfs_c __builtin_vec_fxvaddbfs_c
#define fxv_addhfs_c __builtin_vec_fxvaddhfs_c
#define fxv_subm_c __builtin_vec_fxvsubm_c
#define fxv_subbm_c __builtin_vec_fxvsubbm_c
#define fxv_subhm_c __builtin_vec_fxvsubhm_c
#define vec_subfs_c __builtin_vec_fxvsubfs_c
#define fxv_subbfs_c __builtin_vec_fxvsubbfs_c
#define fxv_subhfs_c __builtin_vec_fxvsubhfs_c
#define fxv_mulm_c __builtin_vec_fxvmulm_c
#define fxv_mulbm_c __builtin_vec_fxvmulbm_c
#define fxv_mulhm_c __builtin_vec_fxvmulhm_c
#define vec_mulfs_c __builtin_vec_fxvmulfs_c
#define fxv_mulbfs_c __builtin_vec_fxvmulbfs_c
#define fxv_mulhfs_c __builtin_vec_fxvmulhfs_c

#define vec_sub __builtin_vec_fxvsub
#define vec_subbm vec_fxvsubbm
#define vec_subhm vec_fxvsubhm
#define fxv_subbm __builtin_vec_fxvsubbm
#define fxv_subhm __builtin_vec_fxvsubhm
#define vec_subfs __builtin_vec_fxvsubfs
#define vec_subbfs vec_fxvsubbfs
#define vec_subhfs vec_fxvsubhfs
#define fxv_subbfs __builtin_vec_fxvsubbfs
#define fxv_subhfs __builtin_vec_fxvsubhfs

#define vec_mul __builtin_vec_fxvmul
#define vec_mulbm vec_fxvmulbm
#define vec_mulhm vec_fxvmulhm
#define fxv_mulbm __builtin_vec_fxvmulbm
#define fxv_mulhm __builtin_vec_fxvmulhm
#define vec_mulfs __builtin_vec_fxvmulfs
#define vec_mulbfs vec_fxvmulbfs
#define vec_mulhfs vec_fxvmulhfs
#define fxv_mulbfs __builtin_vec_fxvmulbfs
#define fxv_mulhfs __builtin_vec_fxvmulhfs

#define vec_shl __builtin_vec_fxvshl
#define fxv_shlb __builtin_vec_fxvshlb
#define fxv_shlh __builtin_vec_fxvshlh
#define vec_shr __builtin_vec_fxvshr
#define fxv_shrb __builtin_vec_fxvshrb
#define fxv_shrh __builtin_vec_fxvshrh

#define fxv_pckbu __builtin_vec_fxvpckbu
#define fxv_pckbl __builtin_vec_fxvpckbl
#define fxv_upckbl __builtin_vec_fxvupckbl
#define fxv_upckbr __builtin_vec_fxvupckbr

#define fxv_splath vec_splat_u16
#define fxv_splatb vec_splat_u8
#define vec_splat_s16(x) __builtin_s2pp_fxvsplath ((x))
#define vec_splat_s8(x) __builtin_s2pp_fxvsplatb ((x))
#define vec_splat_u16(x) ((__vector unsigned short) vec_splat_s16 ((x)))
#define vec_splat_u8(x) ((__vector unsigned char) vec_splat_s8 ((x)))

#define fxv_cmp __builtin_vec_fxvcmp
#define fxv_cmpb __builtin_vec_fxvcmpb
#define fxv_cmph __builtin_vec_fxvcmph

#define fxv_mtac __builtin_vec_fxvmtac
#define fxv_mtacb __builtin_vec_fxvmtacb
#define fxv_mtach __builtin_vec_fxvmtach
#define fxv_mtacf __builtin_vec_fxvmtacf
#define fxv_mtacbf __builtin_vec_fxvmtacbf
#define fxv_mtachf __builtin_vec_fxvmtachf

#define fxv_mam __builtin_vec_fxvmam
#define fxv_mahm __builtin_vec_fxvmahm
#define fxv_mabm __builtin_vec_fxvmabm
#define fxv_mafs __builtin_vec_fxvmafs
#define fxv_mahfs __builtin_vec_fxvmahfs
#define fxv_mabfs __builtin_vec_fxvmabfs
#define fxv_matacm __builtin_vec_fxvmatacm
#define fxv_matachm __builtin_vec_fxvmatachm
#define fxv_matacbm __builtin_vec_fxvmatacbm
#define fxv_matacfs __builtin_vec_fxvmatacfs
#define fxv_matachfs __builtin_vec_fxvmatachfs
#define fxv_matacbfs __builtin_vec_fxvmatacbfs
#define fxv_multacm __builtin_vec_fxvmultacm
#define fxv_multachm __builtin_vec_fxvmultachm
#define fxv_multacbm __builtin_vec_fxvmultacbm
#define fxv_multacfs __builtin_vec_fxvmultacfs
#define fxv_multachfs __builtin_vec_fxvmultachfs
#define fxv_multacbfs __builtin_vec_fxvmultacbfs
#define fxv_addactacm __builtin_vec_fxvaddactacm
#define fxv_addactachm __builtin_vec_fxvaddactachm
#define fxv_addactacbm __builtin_vec_fxvaddactacbm
#define fxv_addactacf __builtin_vec_fxvaddactacf
#define fxv_addactachf __builtin_vec_fxvaddactachf
#define fxv_addactacbf __builtin_vec_fxvaddactacbf
#define fxv_addtacm __builtin_vec_fxvaddtacm
#define fxv_addtachm __builtin_vec_fxvaddtachm
#define fxv_addtacbm __builtin_vec_fxvaddtacbm
#define fxv_addacm __builtin_vec_fxvaddacm
#define fxv_addachm __builtin_vec_fxvaddachm
#define fxv_addacbm __builtin_vec_fxvaddacbm
#define fxv_addacfs __builtin_vec_fxvaddacfs
#define fxv_addachfs __builtin_vec_fxvaddachfs
#define fxv_addacbfs __builtin_vec_fxvaddacbfs

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
