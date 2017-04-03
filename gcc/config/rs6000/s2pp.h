/* _S2PP_H */
#ifndef _S2PP_H
#define _S2PP_H 1

#if !defined(__S2PP__)
#error Use the "-ms2pp" flag to enable s2pp support
#endif

#if !defined(_SOFT_FLOAT)
#error Use the "-msoft-float" flag to enable s2pp support
#endif

#if !defined(_STRICT_ALIGN)
#error Use the "-mstrict-align" flag to enable s2pp support
#endif

#if defined(_RELOCATABLE)
#error Use the "-mno-relocatable" flag to enable s2pp support
#endif

#if defined(_SDATA)
#error Use the "-msdata=none" flag to enable s2pp support
#endif

#include <stdint.h>

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
#define fxv_stax_gt vec_st_gt
#define vec_st_gt __builtin_vec_st_gt
#define fxv_lax_gt vec_ld_gt
#define vec_ld_gt __builtin_vec_ld_gt
#define fxv_stax_lt vec_st_lt
#define vec_st_lt __builtin_vec_st_lt
#define fxv_lax_lt vec_ld_lt
#define vec_ld_lt __builtin_vec_ld_lt
#define fxv_stax_eq vec_st_eq
#define vec_st_eq __builtin_vec_st_eq
#define fxv_lax_eq vec_ld_eq
#define vec_ld_eq __builtin_vec_ld_eq

#define fxv_in __builtin_vec_in
#define fxv_out __builtin_vec_out
#define fxv_in_gt __builtin_vec_in_gt
#define fxv_out_gt __builtin_vec_out_gt
#define fxv_in_lt __builtin_vec_in_lt
#define fxv_out_lt __builtin_vec_out_lt
#define fxv_in_eq __builtin_vec_in_eq
#define fxv_out_eq __builtin_vec_out_eq

#define fxv_sel __builtin_vec_fxvsel
#define fxv_sel_gt(x,y) fxv_sel(x,y,1)
#define fxv_sel_lt(x,y) fxv_sel(x,y,2)
#define fxv_sel_eq(x,y) fxv_sel(x,y,3)

#define vec_extract __builtin_vec_extract
#define fxv_extract __builtin_vec_extract
#define vec_insert __builtin_vec_insert
#define fxv_insert __builtin_vec_insert
#define vec_splats __builtin_vec_splats
#define vec_promote __builtin_vec_promote
#define fxv_promote __builtin_vec_promote

#define vec_add fxv_add
#define fxv_add __builtin_vec_fxvadd
#define fxv_addfs(x,y) fxv_addfs_c(x,y,0)
#define vec_sub fxv_sub
#define fxv_sub __builtin_vec_fxvsub
#define fxv_subfs(x,y) fxv_subfs_c(x,y,0)
#define vec_mul fxv_mul
#define fxv_mul __builtin_vec_fxvmul
#define fxv_mulfs(x,y) fxv_mulfs_c(x,y,0)

#define fxv_addm_c __builtin_vec_fxvaddm
#define fxv_addbm_c __builtin_vec_fxvaddbm_c
#define fxv_addhm_c __builtin_vec_fxvaddhm_c
#define fxv_addfs_c __builtin_vec_fxvaddfs
#define fxv_addbfs_c __builtin_vec_fxvaddbfs
#define fxv_addhfs_c __builtin_vec_fxvaddhfs
#define fxv_subm_c __builtin_vec_fxvsubm
#define fxv_subbm_c __builtin_vec_fxvsubbm
#define fxv_subhm_c __builtin_vec_fxvsubhm
#define fxv_subfs_c __builtin_vec_fxvsubfs
#define fxv_subbfs_c __builtin_vec_fxvsubbfs
#define fxv_subhfs_c __builtin_vec_fxvsubhfs
#define fxv_mulm_c __builtin_vec_fxvmulm
#define fxv_mulbm_c __builtin_vec_fxvmulbm
#define fxv_mulhm_c __builtin_vec_fxvmulhm
#define fxv_mulfs_c __builtin_vec_fxvmulfs
#define fxv_mulbfs_c __builtin_vec_fxvmulbfs
#define fxv_mulhfs_c __builtin_vec_fxvmulhfs

#define vec_sh fxv_sh
#define fxv_sh __builtin_vec_fxvsh
#define fxv_shb __builtin_vec_fxvshb
#define fxv_shh __builtin_vec_fxvshh
#define vec_shl fxv_shl
#define fxv_shl __builtin_vec_fxvshl
#define fxv_shlb __builtin_vec_fxvshlb
#define fxv_shlh __builtin_vec_fxvshlh
#define vec_shr fxv_shr
#define fxv_shr __builtin_vec_fxvshr
#define fxv_shrb __builtin_vec_fxvshrb
#define fxv_shrh __builtin_vec_fxvshrh

#define fxv_pckbu(x,y) fxv_pckbu_c(x,y,0)
#define fxv_pckbl(x,y) fxv_pckbl_c(x,y,0)
#define fxv_upckbl(x,y) fxv_upckbl_c(x,y,0)
#define fxv_upckbr(x,y) fxv_upckbr_c(x,y,0)

#define fxv_pckbu_c __builtin_vec_fxvpckbu
#define fxv_pckbl_c __builtin_vec_fxvpckbl
#define fxv_upckbl_c __builtin_vec_fxvupckbl
#define fxv_upckbr_c __builtin_vec_fxvupckbr

#define fxv_splath __builtin_s2pp_fxvsplath
#define fxv_splatb __builtin_s2pp_fxvsplatb
#define vec_splat_s16(x) __builtin_s2pp_fxvsplath ((x))
#define vec_splat_s8(x) __builtin_s2pp_fxvsplatb ((x))
#define vec_splat_u16(x) ((__vector unsigned short) vec_splat_s16 ((x)))
#define vec_splat_u8(x) ((__vector unsigned char) vec_splat_s8 ((x)))

#define fxv_cmp __builtin_vec_fxvcmp
#define fxv_cmpb __builtin_vec_fxvcmpb
#define fxv_cmph __builtin_vec_fxvcmph

#define fxv_mtac(x) fxv_mtac_c(x,0)
#define fxv_mtacb(x) fxv_mtacb_c(x,0)
#define fxv_mtach(x) fxv_mtach_c(x,0)
#define fxv_mtacf(x) fxv_mtacf_c(x,0)
#define fxv_mtacbf(x) fxv_mtacbf_c(x,0)
#define fxv_mtachf(x) fxv_mtachf_c(x,0)
#define fxv_addactacm(x) fxv_addactacm_c(x,0)
#define fxv_addactachm(x) fxv_addactachm_c(x,0)
#define fxv_addactacbm(x) fxv_addactacbm_c(x,0)
#define fxv_addactacf(x) fxv_addactacf_c(x,0)
#define fxv_addactachf(x) fxv_addactachf_c(x,0)
#define fxv_addactacbf(x) fxv_addactacbf_c(x,0)

#define fxv_mtac_c __builtin_vec_fxvmtac
#define fxv_mtacb_c __builtin_vec_fxvmtacb
#define fxv_mtach_c __builtin_vec_fxvmtach
#define fxv_mtacf_c __builtin_vec_fxvmtacf
#define fxv_mtacbf_c __builtin_vec_fxvmtacbf
#define fxv_mtachf_c __builtin_vec_fxvmtachf
#define fxv_addactacm_c __builtin_vec_fxvaddactacm
#define fxv_addactachm_c __builtin_vec_fxvaddactachm
#define fxv_addactacbm_c __builtin_vec_fxvaddactacbm
#define fxv_addactacf_c __builtin_vec_fxvaddactacf
#define fxv_addactachf_c __builtin_vec_fxvaddactachf
#define fxv_addactacbf_c __builtin_vec_fxvaddactacbf

#define fxv_addacm(x) fxv_addacm_c(x,0)
#define fxv_addachm(x) fxv_addachm_c(x,0)
#define fxv_addacbm(x) fxv_addacbm_c(x,0)
#define fxv_addacfs(x) fxv_addacfs_c(x,0)
#define fxv_addachfs(x) fxv_addachfs_c(x,0)
#define fxv_addacbfs(x) fxv_addacbfs_c(x,0)
#define fxv_mam(x,y) fxv_mam_c(x,y,0)
#define fxv_mahm(x,y) fxv_mahm_c(x,y,0)
#define fxv_mabm(x,y) fxv_mabm_c(x,y,0)
#define fxv_mafs(x,y) fxv_mafs_c(x,y,0)
#define fxv_mahfs(x,y) fxv_mahfs_c(x,y,0)
#define fxv_mabfs(x,y) fxv_mabfs_c(x,y,0)

#define fxv_addacm_c __builtin_vec_fxvaddacm
#define fxv_addachm_c __builtin_vec_fxvaddachm
#define fxv_addacbm_c __builtin_vec_fxvaddacbm
#define fxv_addacfs_c __builtin_vec_fxvaddacfs
#define fxv_addachfs_c __builtin_vec_fxvaddachfs
#define fxv_addacbfs_c __builtin_vec_fxvaddacbfs
#define fxv_mam_c __builtin_vec_fxvmam
#define fxv_mahm_c __builtin_vec_fxvmahm
#define fxv_mabm_c __builtin_vec_fxvmabm
#define fxv_mafs_c __builtin_vec_fxvmafs
#define fxv_mahfs_c __builtin_vec_fxvmahfs
#define fxv_mabfs_c __builtin_vec_fxvmabfs

#define fxv_matacm(x,y) fxv_matacm_c(x,y,0)
#define fxv_matachm(x,y) fxv_matachm_c(x,y,0)
#define fxv_matacbm(x,y) fxv_matacbm_c(x,y,0)
#define fxv_matacfs(x,y) fxv_matacfs_c(x,y,0)
#define fxv_matachfs(x,y) fxv_matachfs_c(x,y,0)
#define fxv_matacbfs(x,y) fxv_matacbfs_c(x,y,0)
#define fxv_multacm(x,y) fxv_multacm_c(x,y,0)
#define fxv_multachm(x,y) fxv_multachm_c(x,y,0)
#define fxv_multacbm(x,y) fxv_multacbm_c(x,y,0)
#define fxv_multacfs(x,y) fxv_multacfs_c(x,y,0)
#define fxv_multachfs(x,y) fxv_multachfs_c(x,y,0)
#define fxv_multacbfs(x,y) fxv_multacbfs_c(x,y,0)
#define fxv_addtac(x,y) fxv_addtac_c(x,y,0)
#define fxv_addtach(x,y) fxv_addtach_c(x,y,0)
#define fxv_addtacb(x,y) fxv_addtacb_c(x,y,0)

#define fxv_matacm_c __builtin_vec_fxvmatacm
#define fxv_matachm_c __builtin_vec_fxvmatachm
#define fxv_matacbm_c __builtin_vec_fxvmatacbm
#define fxv_matacfs_c __builtin_vec_fxvmatacfs
#define fxv_matachfs_c __builtin_vec_fxvmatachfs
#define fxv_matacbfs_c __builtin_vec_fxvmatacbfs
#define fxv_multacm_c __builtin_vec_fxvmultacm
#define fxv_multachm_c __builtin_vec_fxvmultachm
#define fxv_multacbm_c __builtin_vec_fxvmultacbm
#define fxv_multacfs_c __builtin_vec_fxvmultacfs
#define fxv_multachfs_c __builtin_vec_fxvmultachfs
#define fxv_multacbfs_c __builtin_vec_fxvmultacbfs
#define fxv_addtac_c __builtin_vec_fxvaddtac
#define fxv_addtach_c __builtin_vec_fxvaddtach
#define fxv_addtacb_c __builtin_vec_fxvaddtacb

#define vec_step(x) __builtin_vec_step (* (__typeof__ (x) *) 0)
#define fxv_steps(x) __builtin_vec_step (* (__typeof__ (x) *) 0)
#endif /* _S2PP_H */
