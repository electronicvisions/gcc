;;s2pp_hx machine description file

(define_c_enum "unspec"
  [UNSPEC_FXV_HXSTAX
   UNSPEC_FXV_HXLAX
   UNSPEC_FXV_HXLAX_DIRECT
   UNSPEC_FXV_HXSTAX_GT
   UNSPEC_FXV_HXSTAX_LT
   UNSPEC_FXV_HXSTAX_EQ
   UNSPEC_FXV_HXLAX_GT
   UNSPEC_FXV_HXLAX_LT
   UNSPEC_FXV_HXLAX_EQ
   UNSPEC_FXV_HXOUTX
   UNSPEC_FXV_HXINX
   UNSPEC_FXV_HXOUTX_GT
   UNSPEC_FXV_HXOUTX_LT
   UNSPEC_FXV_HXOUTX_EQ
   UNSPEC_FXV_HXINX_GT
   UNSPEC_FXV_HXINX_LT
   UNSPEC_FXV_HXINX_EQ
   UNSPEC_FXV_HXSPLAT_DIRECT
   UNSPEC_FXV_HXSPLAT
   UNSPEC_FXV_HXADD
   UNSPEC_FXV_HXADD_C
   UNSPEC_FXV_HXADDF
   UNSPEC_FXV_HXADDF_C
   UNSPEC_FXV_HXMA
   UNSPEC_FXV_HXMAF
   UNSPEC_FXV_HXADDACTACF
   UNSPEC_FXV_HXADDACTAC
   UNSPEC_FXV_HXMATAC
   UNSPEC_FXV_HXMATACF
   UNSPEC_FXV_HXMULTAC
   UNSPEC_FXV_HXMULTACF
   UNSPEC_FXV_HXADDTAC
   UNSPEC_FXV_HXADDAC
   UNSPEC_FXV_HXADDACF
   UNSPEC_FXV_HXSUB
   UNSPEC_FXV_HXSUB_C
   UNSPEC_FXV_HXSUBF
   UNSPEC_FXV_HXSUBF_C
   UNSPEC_FXV_HXMUL
   UNSPEC_FXV_HXMUL_C
   UNSPEC_FXV_HXMULF
   UNSPEC_FXV_HXMULF_C
   UNSPEC_FXV_HXMTAC
   UNSPEC_FXV_HXMTACF
   UNSPEC_FXV_HXPCKU
   UNSPEC_FXV_HXPCKL
   UNSPEC_FXV_HXUPCKL
   UNSPEC_FXV_HXUPCKR
   UNSPEC_FXV_HXPCKU_DIRECT
   UNSPEC_FXV_HXPCKL_DIRECT
   UNSPEC_FXV_HXUPCKL_DIRECT
   UNSPEC_FXV_HXUPCKR_DIRECT
   UNSPEC_FXV_HXSELECT
   UNSPEC_FXV_HXSYNC
   UNSPEC_FXV_HXCMP
])

;; Vec int modes
(define_mode_iterator FXV_HXI [V64HI V128QI])
(define_code_iterator HX_C_cond [gt lt eq])

(define_int_iterator FXV_HXLAX [UNSPEC_FXV_HXLAX
			       UNSPEC_FXV_HXLAX_GT
			       UNSPEC_FXV_HXLAX_LT
			       UNSPEC_FXV_HXLAX_EQ])
(define_int_iterator FXV_HXSTAX [UNSPEC_FXV_HXSTAX
				UNSPEC_FXV_HXSTAX_GT
				UNSPEC_FXV_HXSTAX_LT
				UNSPEC_FXV_HXSTAX_EQ])
(define_int_iterator FXV_HXINX [UNSPEC_FXV_HXINX
			       UNSPEC_FXV_HXINX_GT
			       UNSPEC_FXV_HXINX_LT
			       UNSPEC_FXV_HXINX_EQ])
(define_int_iterator FXV_HXOUTX [UNSPEC_FXV_HXOUTX
				UNSPEC_FXV_HXOUTX_GT
				UNSPEC_FXV_HXOUTX_LT
				UNSPEC_FXV_HXOUTX_EQ])
;;(define_int_iterator SAT [m fs f])

;; Vec attributes
(define_mode_attr FXV_HXI_char [(V64HI "h") (V128QI "b")])

(define_mode_attr FXV_HXI_unit [(V64HI "VECTOR_UNIT_S2PP_HX_P (V64HImode)")
			   (V128QI "VECTOR_UNIT_S2PP_HX_P (V128QImode)")])

(define_code_attr HX_C_char [(gt "1") (lt "2") (eq "3")])

(define_int_attr fxv_hx_lax_int [(UNSPEC_FXV_HXLAX "0")
			     (UNSPEC_FXV_HXLAX_GT "1")
			     (UNSPEC_FXV_HXLAX_LT "2")
			     (UNSPEC_FXV_HXLAX_EQ "3")])
(define_int_attr fxv_hx_lax_char [(UNSPEC_FXV_HXLAX "_")
			      (UNSPEC_FXV_HXLAX_GT "_gt_")
			      (UNSPEC_FXV_HXLAX_LT "_lt_")
			      (UNSPEC_FXV_HXLAX_EQ "_eq_")])
(define_int_attr fxv_hx_stax_int [(UNSPEC_FXV_HXSTAX "0")
			  (UNSPEC_FXV_HXSTAX_GT "1")
			  (UNSPEC_FXV_HXSTAX_LT "2")
			  (UNSPEC_FXV_HXSTAX_EQ "3")])
(define_int_attr fxv_hx_stax_char [(UNSPEC_FXV_HXSTAX "_")
			       (UNSPEC_FXV_HXSTAX_GT "_gt_")
			       (UNSPEC_FXV_HXSTAX_LT "_lt_")
			       (UNSPEC_FXV_HXSTAX_EQ "_eq_")])
(define_int_attr fxv_hx_inx_int [(UNSPEC_FXV_HXINX "0")
			     (UNSPEC_FXV_HXINX_GT "1")
			     (UNSPEC_FXV_HXINX_LT "2")
			     (UNSPEC_FXV_HXINX_EQ "3")])
(define_int_attr fxv_hx_inx_char [(UNSPEC_FXV_HXINX "_")
			      (UNSPEC_FXV_HXINX_GT "_gt_")
			      (UNSPEC_FXV_HXINX_LT "_lt_")
			      (UNSPEC_FXV_HXINX_EQ "_eq_")])
(define_int_attr fxv_hx_outx_int [(UNSPEC_FXV_HXOUTX "0")
			  (UNSPEC_FXV_HXOUTX_GT "1")
			  (UNSPEC_FXV_HXOUTX_LT "2")
			  (UNSPEC_FXV_HXOUTX_EQ "3")])
(define_int_attr fxv_hx_outx_char [(UNSPEC_FXV_HXOUTX "_")
			       (UNSPEC_FXV_HXOUTX_GT "_gt_")
			       (UNSPEC_FXV_HXOUTX_LT "_lt_")
			       (UNSPEC_FXV_HXOUTX_EQ "_eq_")])

;; s2pp_hx specific load and store instructions
;; PS: in gcc 4.9.4 there was the equivalent for altivec here,
;; their structure seems to have changed.
(define_expand "vector_s2pp_hx_load_<mode>"
  [(set (match_operand:FXV_HXI 0 "vfloat_operand" "")
	(match_operand:FXV_HXI 1 "memory_operand" ""))]
  "VECTOR_MEM_S2PP_HX_P (<MODE>mode)"
  "
{
  gcc_assert (VECTOR_MEM_S2PP_HX_P (<MODE>mode));
}")

(define_expand "vector_s2pp_hx_store_<mode>"
  [(set (match_operand:FXV_HXI 0 "memory_operand" "")
	(match_operand:FXV_HXI 1 "vfloat_operand" ""))]
  "VECTOR_MEM_S2PP_HX_P (<MODE>mode)"
  "
{
  gcc_assert (VECTOR_MEM_S2PP_HX_P (<MODE>mode));
}")

(define_expand "vector_s2pp_hx_input_<mode>"
  [(set (match_operand:FXV_HXI 0 "vfloat_operand" "")
	(match_operand:FXV_HXI 1 "memory_operand" ""))]
  "VECTOR_MEM_S2PP_HX_P (<MODE>mode)"
  "
{
  gcc_assert (VECTOR_MEM_S2PP_HX_P (<MODE>mode));
}")

(define_expand "vector_s2pp_hx_output_<mode>"
  [(set (match_operand:FXV_HXI 0 "memory_operand" "")
	(match_operand:FXV_HXI 1 "vfloat_operand" ""))]
  "VECTOR_MEM_S2PP_HX_P (<MODE>mode)"
  "
{
  gcc_assert (VECTOR_MEM_S2PP_HX_P (<MODE>mode));
}")

;; s2pp_hx sync instruction
(define_insn "hxsync"
  [(unspec_volatile [(const_int 0)] UNSPEC_FXV_HXSYNC)]
  "TARGET_S2PP_HX"
  "sync"
  [(set_attr "type" "sync")])

(define_insn "*s2pp_hx_mov<mode>"
  [(set (match_operand:FXV_HXI 0 "nonimmediate_operand" "=Z,qv,qv,*Y,*r,*r,qv,qv")
	(match_operand:FXV_HXI 1 "input_operand" "qv,Z,qv,r,Y,r,j,W"))]
  "VECTOR_MEM_S2PP_HX_P (<MODE>mode)
   && (register_operand (operands[0], <MODE>mode)
       || register_operand (operands[1], <MODE>mode))"
{
  switch (which_alternative)
    {
    case 0: return "fxvstax %1,%y0";
    case 1: return "fxvlax %0,%y1";
    case 2: return "fxvsel %0,%1,%1";
    case 3: return "#";
    case 4: return "#";
    case 5: return "#";
    case 6: return "fxvsel %0,0,0";
    case 7: return output_vec_const_move (operands);
    default: gcc_unreachable ();
    }
}
  [(set_attr "type" "vecstore,vecload,vecsimple,store,load,*,vecsimple,*")])
;; AWH:
;; 0 at the end of case 2 in order to return true -> similar to vor(x,x)
;; alternatively use 3
;; 1 at the end  of case 6 for gt comp -> similar to xor(1,1)
;; alternatively use 2

;; AWH: keep this, for later, as sync might become necessary again
;;(define_split
;;  [(set (match_operand:FXV_HXI 0 "s2pp_hx_register_operand" "")
;;	(match_operand:FXV_HXI 1 "indexed_or_indirect_operand" ""))]
;;  "VECTOR_MEM_S2PP_HX_P (<MODE>mode)
;;   && (register_operand (operands[0], <MODE>mode)
;;       || register_operand (operands[1], <MODE>mode))"
;;  [(parallel
;;    [(set (match_operand:FXV_HXI 0 "s2pp_hx_register_operand" "=qv")
;;	  (match_operand:FXV_HXI 1 "memory_operand" "Z"))
;;     (unspec [(const_int 0)] UNSPEC_FXV_HXLAX)])]
;;  "")

(define_split
  [(set (match_operand:FXV_HXI 0 "indexed_or_indirect_operand" "")
	(match_operand:FXV_HXI 1 "s2pp_hx_register_operand" ""))]
  "VECTOR_MEM_S2PP_HX_P (<MODE>mode)
   && (register_operand (operands[0], <MODE>mode)
       || register_operand (operands[1], <MODE>mode))"
  [(parallel
    [(set (match_operand:FXV_HXI 0 "memory_operand" "")
	  (match_operand:FXV_HXI 1 "s2pp_hx_register_operand" ""))
    (unspec [(const_int 0)] UNSPEC_FXV_HXSTAX)])]
  "")

(define_split
  [(set (match_operand:FXV_HXI 0 "s2pp_hx_register_operand" "")
	(match_operand:FXV_HXI 1 "easy_vector_constant" ""))]
  "TARGET_S2PP_HX && can_create_pseudo_p()"
  [(set (match_dup 2) (match_dup 3))
   (set (match_dup 0)
	(unspec:FXV_HXI
	     [(match_dup 2)]
	UNSPEC_FXV_HXSPLAT))]
  "{
    operands[2] = gen_reg_rtx (SImode);
    operands[3] = CONST_VECTOR_ELT(operands[1], 1);
  }")

;;store
(define_insn_and_split "s2pp_hx_fxvstax<fxv_hx_stax_char><mode>"
  [(parallel
    [(set (match_operand:FXV_HXI 0 "memory_operand" "=Z")
	  (match_operand:FXV_HXI 1 "register_operand" "qv"))
    (unspec [(const_int 0)] FXV_HXSTAX)])]
  "TARGET_S2PP_HX"
  "#"
  "reload_completed"
  [(set (match_operand:FXV_HXI 0 "memory_operand" "")
        (unspec:FXV_HXI [(match_operand:FXV_HXI 1 "s2pp_hx_register_operand" "")] FXV_HXSTAX))
   (unspec_volatile [(const_int 0)] UNSPEC_FXV_HXSYNC)]
  ""
  [(set_attr "type" "vecstore")])

(define_insn "*s2pp_hx_fxvstax_<fxv_hx_stax_int>_<mode>_direct"
  [(set (match_operand:FXV_HXI 0 "memory_operand" "=Z")
	(unspec:FXV_HXI [(match_operand:FXV_HXI 1 "register_operand" "qv")] FXV_HXSTAX))]
  "TARGET_S2PP_HX"
  "fxvstax %1,%y0,<fxv_hx_stax_int>"
  [(set_attr "type" "vecstore")])


;;load
(define_insn "s2pp_hx_fxvlax<fxv_hx_lax_char><mode>"
  [(parallel
    [(set (match_operand:FXV_HXI 0 "register_operand" "=qv")
	  (match_operand:FXV_HXI 1 "memory_operand" "Z"))
    (unspec [(const_int 0)] FXV_HXLAX)])]
  "TARGET_S2PP_HX"
  "fxvlax %0,%y1,<fxv_hx_lax_int>"
  [(set_attr "type" "vecload")])

;;synram
(define_insn "s2pp_hx_fxvoutx<fxv_hx_outx_char><mode>"
  [(parallel
    [(set (match_operand:FXV_HXI 0 "memory_operand" "=Z")
	  (match_operand:FXV_HXI 1 "register_operand" "qv"))
    (unspec [(const_int 0)] FXV_HXOUTX)])]
  "TARGET_S2PP_HX"
  "fxvoutx %1,%y0,<fxv_hx_outx_int>"
  [(set_attr "type" "vecstore")])

(define_insn "s2pp_hx_fxvinx<fxv_hx_inx_char><mode>"
  [(parallel
    [(set (match_operand:FXV_HXI 0 "register_operand" "=qv")
	  (match_operand:FXV_HXI 1 "memory_operand" "Z"))
    (unspec [(const_int 0)] FXV_HXINX)])]
  "TARGET_S2PP_HX"
  "fxvinx %0,%y1,<fxv_hx_inx_int>"
  [(set_attr "type" "vecload")])

;; add
(define_insn_and_split "fxvadd<mode>3"
  [(set (match_operand:FXV_HXI 0 "register_operand" "=qv")
        (plus:FXV_HXI (match_operand:FXV_HXI 1 "register_operand" "qv")
		   (match_operand:FXV_HXI 2 "register_operand" "qv")))]
  "<FXV_HXI_unit>"
  "#"
  ""
  [(set (match_operand:FXV_HXI 0 "register_operand" "=qv")
	(unspec:FXV_HXI [(match_operand:FXV_HXI 1 "register_operand" "qv")
		      (match_operand:FXV_HXI 2 "register_operand" "qv")]
	UNSPEC_FXV_HXADD))]
  ""
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_hx_fxvadd<FXV_HXI_char>m"
  [(set (match_operand:FXV_HXI 0 "register_operand" "=qv")
	(unspec:FXV_HXI [(match_operand:FXV_HXI 1 "register_operand" "qv")
		      (match_operand:FXV_HXI 2 "register_operand" "qv")]
	UNSPEC_FXV_HXADD))]
  "<FXV_HXI_unit>"
  "fxvadd<FXV_HXI_char>m %0,%1,%2"
  [(set_attr "type" "vecsimple")])

(define_insn_and_split "s2pp_hx_fxvadd<FXV_HXI_char>m_c"
  [(set (match_operand:FXV_HXI 0 "register_operand" "=qv")
	(unspec:FXV_HXI [(match_operand:FXV_HXI 1 "register_operand" "qv")
		      (match_operand:FXV_HXI 2 "register_operand" "qv")
		      (match_operand:SI 3 "u2bit_cint_operand" "i")
		      (reg:FXV_HXI S2PP_HX_COND_REGNO)]
	UNSPEC_FXV_HXADD_C))]
  "<FXV_HXI_unit>"
  "#"
  "can_create_pseudo_p()"
  [(set (match_dup 4)
	(unspec:FXV_HXI [(match_operand:FXV_HXI 1 "register_operand" "")
		      (match_operand:FXV_HXI 2 "register_operand" "")]
	UNSPEC_FXV_HXADD))
   (set (match_operand:FXV_HXI 0 "register_operand" "")
	 (unspec:FXV_HXI [(match_operand:SI 3 "u2bit_cint_operand" "")
	 (match_operand:FXV_HXI 0 "register_operand" "")
	 (match_dup 4)] UNSPEC_FXV_HXSELECT))]
   "{operands[4] = gen_reg_rtx (<MODE>mode);}"
  [(set_attr "type" "vecsimple")])

(define_insn_and_split "s2pp_hx_fxvadd<FXV_HXI_char>fs_c"
  [(set (match_operand:FXV_HXI 0 "register_operand" "=qv")
        (unspec:FXV_HXI [(match_operand:FXV_HXI 1 "register_operand" "qv")
		      (match_operand:FXV_HXI 2 "register_operand" "qv")
		      (match_operand:SI 3 "u2bit_cint_operand" "i")
		      (reg:FXV_HXI S2PP_HX_COND_REGNO)]
	UNSPEC_FXV_HXADDF_C))]
  "<FXV_HXI_unit>"
  "#"
  "can_create_pseudo_p()"
  [(set (match_dup 4)
	(unspec:FXV_HXI [(match_operand:FXV_HXI 1 "register_operand" "")
		      (match_operand:FXV_HXI 2 "register_operand" "")]
	UNSPEC_FXV_HXADDF))
   (set (match_operand:FXV_HXI 0 "register_operand" "")
	 (unspec:FXV_HXI [(match_operand:SI 3 "u2bit_cint_operand" "")
	 (match_operand:FXV_HXI 0 "register_operand" "")
	 (match_dup 4)] UNSPEC_FXV_HXSELECT))]
   "{operands[4] = gen_reg_rtx (<MODE>mode);}"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_hx_fxvadd<FXV_HXI_char>fs"
  [(set (match_operand:FXV_HXI 0 "register_operand" "=qv")
        (unspec:FXV_HXI [(match_operand:FXV_HXI 1 "register_operand" "qv")
		      (match_operand:FXV_HXI 2 "register_operand" "qv")]
	UNSPEC_FXV_HXADDF))]
  "<FXV_HXI_unit>"
  "fxvadd<FXV_HXI_char>fs %0,%1,%2"
  [(set_attr "type" "vecsimple")])

;; sub
(define_insn_and_split "fxvsub<mode>3"
  [(set (match_operand:FXV_HXI 0 "register_operand" "=qv")
        (minus:FXV_HXI (match_operand:FXV_HXI 1 "register_operand" "qv")
		  (match_operand:FXV_HXI 2 "register_operand" "qv")))]
  "<FXV_HXI_unit>"
  "#"
  ""
  [(set (match_operand:FXV_HXI 0 "register_operand" "=qv")
	(unspec:FXV_HXI [(match_operand:FXV_HXI 1 "register_operand" "qv")
		      (match_operand:FXV_HXI 2 "register_operand" "qv")]
	UNSPEC_FXV_HXSUB))]
  ""
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_hx_fxvsub<FXV_HXI_char>m"
  [(set (match_operand:FXV_HXI 0 "register_operand" "=qv")
	(unspec:FXV_HXI [(match_operand:FXV_HXI 1 "register_operand" "qv")
		      (match_operand:FXV_HXI 2 "register_operand" "qv")] UNSPEC_FXV_HXSUB))]
  "<FXV_HXI_unit>"
  "fxvsub<FXV_HXI_char>m %0,%1,%2"
  [(set_attr "type" "vecsimple")])

(define_insn_and_split "s2pp_hx_fxvsub<FXV_HXI_char>m_c"
  [(set (match_operand:FXV_HXI 0 "register_operand" "=qv")
	(unspec:FXV_HXI [(match_operand:FXV_HXI 1 "register_operand" "qv")
		      (match_operand:FXV_HXI 2 "register_operand" "qv")
		      (match_operand:SI 3 "u2bit_cint_operand" "i")
		      (reg:FXV_HXI S2PP_HX_COND_REGNO)]
	UNSPEC_FXV_HXSUB_C))]
  "<FXV_HXI_unit>"
  "#"
  "can_create_pseudo_p()"
  [(set (match_dup 4)
	(unspec:FXV_HXI [(match_operand:FXV_HXI 1 "register_operand" "")
		      (match_operand:FXV_HXI 2 "register_operand" "")]
	UNSPEC_FXV_HXSUB))
   (set (match_operand:FXV_HXI 0 "register_operand" "")
	 (unspec:FXV_HXI [(match_operand:SI 3 "u2bit_cint_operand" "")
	 (match_operand:FXV_HXI 0 "register_operand" "")
	 (match_dup 4)] UNSPEC_FXV_HXSELECT))]
   "{operands[4] = gen_reg_rtx (<MODE>mode);}"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_hx_fxvsub<FXV_HXI_char>fs"
  [(set (match_operand:FXV_HXI 0 "register_operand" "=qv")
	(unspec:FXV_HXI [(match_operand:FXV_HXI 1 "register_operand" "qv")
		      (match_operand:FXV_HXI 2 "register_operand" "qv")] UNSPEC_FXV_HXSUBF))]
  "<FXV_HXI_unit>"
  "fxvsub<FXV_HXI_char>fs %0,%1,%2"
  [(set_attr "type" "vecsimple")])

(define_insn_and_split "s2pp_hx_fxvsub<FXV_HXI_char>fs_c"
  [(set (match_operand:FXV_HXI 0 "register_operand" "=qv")
	(unspec:FXV_HXI [(match_operand:FXV_HXI 1 "register_operand" "qv")
		      (match_operand:FXV_HXI 2 "register_operand" "qv")
		      (match_operand:SI 3 "u2bit_cint_operand" "i")
		      (reg:FXV_HXI S2PP_HX_COND_REGNO)]
	UNSPEC_FXV_HXSUBF_C))]
  "<FXV_HXI_unit>"
  "#"
  "can_create_pseudo_p()"
  [(set (match_dup 4)
	(unspec:FXV_HXI [(match_operand:FXV_HXI 1 "register_operand" "")
		      (match_operand:FXV_HXI 2 "register_operand" "")]
	UNSPEC_FXV_HXSUBF))
   (set (match_operand:FXV_HXI 0 "register_operand" "")
	 (unspec:FXV_HXI [(match_operand:SI 3 "u2bit_cint_operand" "")
	 (match_operand:FXV_HXI 0 "register_operand" "")
	 (match_dup 4)] UNSPEC_FXV_HXSELECT))]
   "{operands[4] = gen_reg_rtx (<MODE>mode);}"
  [(set_attr "type" "vecsimple")])


;; multiply
(define_insn_and_split "s2pp_hx_fxvmul<FXV_HXI_char>"
  [(set (match_operand:FXV_HXI 0 "register_operand" "=qv")
        (mult:FXV_HXI (match_operand:FXV_HXI 1 "register_operand" "qv")
		  (match_operand:FXV_HXI 2 "register_operand" "qv")))]
  "<FXV_HXI_unit>"
  "#"
  ""
  [(set (match_operand:FXV_HXI 0 "register_operand" "")
	(unspec:FXV_HXI [(match_operand:FXV_HXI 1 "register_operand" "")
		      (match_operand:FXV_HXI 2 "register_operand" "")] UNSPEC_FXV_HXMUL))]
  ""
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_hx_fxvmul<FXV_HXI_char>m"
  [(set (match_operand:FXV_HXI 0 "register_operand" "=qv")
	(unspec:FXV_HXI [(match_operand:FXV_HXI 1 "register_operand" "qv")
		      (match_operand:FXV_HXI 2 "register_operand" "qv")] UNSPEC_FXV_HXMUL))]
  "<FXV_HXI_unit>"
  "fxvmul<FXV_HXI_char>m %0,%1,%2"
  [(set_attr "type" "vecsimple")])

(define_insn_and_split "s2pp_hx_fxvmul<FXV_HXI_char>m_c"
  [(set (match_operand:FXV_HXI 0 "register_operand" "=qv")
	(unspec:FXV_HXI [(match_operand:FXV_HXI 1 "register_operand" "qv")
		      (match_operand:FXV_HXI 2 "register_operand" "qv")
		      (match_operand:SI 3 "u2bit_cint_operand" "i")
		      (reg:FXV_HXI S2PP_HX_COND_REGNO)]
	UNSPEC_FXV_HXMUL_C))]
  "<FXV_HXI_unit>"
  "#"
  "can_create_pseudo_p()"
  [(set (match_dup 4)
	(unspec:FXV_HXI [(match_operand:FXV_HXI 1 "register_operand" "")
		      (match_operand:FXV_HXI 2 "register_operand" "")]
	UNSPEC_FXV_HXMUL))
   (set (match_operand:FXV_HXI 0 "register_operand" "")
	 (unspec:FXV_HXI [(match_operand:SI 3 "u2bit_cint_operand" "")
	 (match_operand:FXV_HXI 0 "register_operand" "")
	 (match_dup 4)] UNSPEC_FXV_HXSELECT))]
   "{operands[4] = gen_reg_rtx (<MODE>mode);}"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_hx_fxvmul<FXV_HXI_char>fs"
  [(set (match_operand:FXV_HXI 0 "register_operand" "=qv")
	(unspec:FXV_HXI [(match_operand:FXV_HXI 1 "register_operand" "qv")
		      (match_operand:FXV_HXI 2 "register_operand" "qv")] UNSPEC_FXV_HXMULF))]
  "<FXV_HXI_unit>"
  "fxvmul<FXV_HXI_char>fs %0,%1,%2"
  [(set_attr "type" "vecsimple")])

(define_insn_and_split "s2pp_hx_fxvmul<FXV_HXI_char>fs_c"
  [(set (match_operand:FXV_HXI 0 "register_operand" "=qv")
	(unspec:FXV_HXI [(match_operand:FXV_HXI 1 "register_operand" "qv")
		      (match_operand:FXV_HXI 2 "register_operand" "qv")
		      (match_operand:SI 3 "u2bit_cint_operand" "i")
		      (reg:FXV_HXI S2PP_HX_COND_REGNO)]
	UNSPEC_FXV_HXMULF_C))]
  "<FXV_HXI_unit>"
  "#"
  "can_create_pseudo_p()"
  [(set (match_dup 4)
	(unspec:FXV_HXI [(match_operand:FXV_HXI 1 "register_operand" "")
		      (match_operand:FXV_HXI 2 "register_operand" "")]
	UNSPEC_FXV_HXMULF))
   (set (match_operand:FXV_HXI 0 "register_operand" "")
	 (unspec:FXV_HXI [(match_operand:SI 3 "u2bit_cint_operand" "")
	 (match_operand:FXV_HXI 0 "register_operand" "")
	 (match_dup 4)] UNSPEC_FXV_HXSELECT))]
   "{operands[4] = gen_reg_rtx (<MODE>mode);}"
  [(set_attr "type" "vecsimple")])


;; splat
(define_insn_and_split "s2pp_hx_fxvsplat<FXV_HXI_char>"
  [(set (match_operand:FXV_HXI 0 "register_operand" "=qv")
	(unspec:FXV_HXI
	     [(match_operand:SI 1 "register_operand" "r")]
	UNSPEC_FXV_HXSPLAT))]
  "TARGET_S2PP_HX"
  "#"
  "TARGET_S2PP_HX && reload_completed"
  [(set (match_operand:FXV_HXI 0 "register_operand" "")
	(unspec:FXV_HXI
	     [(match_operand:SI 1 "register_operand" "")]
	UNSPEC_FXV_HXSPLAT_DIRECT))]
  ""
  [(set_attr "type" "vecperm")])

(define_insn "*s2pp_hx_fxvsplat<FXV_HXI_char>_direct"
  [(set (match_operand:FXV_HXI 0 "register_operand" "=qv")
	(unspec:FXV_HXI
	     [(match_operand:SI 1 "register_operand" "r")]
	UNSPEC_FXV_HXSPLAT_DIRECT))]
  "TARGET_S2PP_HX"
  "fxvsplat<FXV_HXI_char> %0,%1"
  [(set_attr "type" "vecperm")])

;; select
(define_insn "s2pp_hx_fxvsel_<mode>"
  [(set (match_operand:FXV_HXI 0 "register_operand" "=qv")
	 (unspec:FXV_HXI [(match_operand:SI 3 "u2bit_cint_operand" "i")
	 (match_operand:FXV_HXI 1 "register_operand" "qv")
	 (match_operand:FXV_HXI 2 "register_operand" "qv")] UNSPEC_FXV_HXSELECT))]
  "VECTOR_MEM_S2PP_HX_P (<MODE>mode)"
  "fxvsel %0,%1,%2,%3"
  [(set_attr "type" "vecperm")])

;; shift
(define_insn "s2pp_hx_fxvshl<FXV_HXI_char>"
  [(set (match_operand:FXV_HXI 0 "register_operand" "=qv")
        (ashift:FXV_HXI (match_operand:FXV_HXI 1 "register_operand" "qv")
		     (const_int 1)))]
  "<FXV_HXI_unit>"
  "fxvsh<FXV_HXI_char> %0,%1,1"
  [(set_attr "type" "vecperm")])

(define_insn "s2pp_hx_fxvshr<FXV_HXI_char>"
  [(set (match_operand:FXV_HXI 0 "register_operand" "=qv")
        (ashift:FXV_HXI (match_operand:FXV_HXI 1 "register_operand" "qv")
		     (const_int -1)))]
  "<FXV_HXI_unit>"
  "fxvsh<FXV_HXI_char> %0,%1,-1"
  [(set_attr "type" "vecperm")])

(define_insn "s2pp_hx_fxvsh<FXV_HXI_char>"
  [(set (match_operand:FXV_HXI 0 "register_operand" "=qv")
        (ashift:FXV_HXI (match_operand:FXV_HXI 1 "register_operand" "qv")
		     (match_operand:SI 2 "u2bit_cint_operand" "i")))]
  "<FXV_HXI_unit>"
  "fxvsh<FXV_HXI_char> %0,%1,%2"
  [(set_attr "type" "vecperm")])

;;compare
(define_insn "s2pp_hx_fxvcmp<FXV_HXI_char>"
  [(set (reg:FXV_HXI S2PP_HX_COND_REGNO)
        (unspec_volatile:FXV_HXI [(match_operand:FXV_HXI 0 "register_operand" "qv")] UNSPEC_FXV_HXCMP))]
  "TARGET_S2PP_HX"
  "fxvcmp<FXV_HXI_char> %0"
  [(set_attr "type" "veccmp")])

;;accumulator insns
(define_insn "s2pp_hx_fxvmtac<FXV_HXI_char>"
  [(set	(reg:FXV_HXI S2PP_HX_ACC_REGNO)
		(unspec:FXV_HXI [(match_operand:FXV_HXI 0 "s2pp_hx_register_operand" "qv")
			      (match_operand:SI 1 "u2bit_cint_operand" "i")
			      (reg:FXV_HXI S2PP_HX_ACC_REGNO)]
		UNSPEC_FXV_HXMTAC))]
  "TARGET_S2PP_HX"
  "fxvmtac<FXV_HXI_char> %0,%1"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_hx_fxvma<FXV_HXI_char>m"
  [(set (match_operand:FXV_HXI 0 "register_operand" "=qv")
	(unspec:FXV_HXI [(reg:FXV_HXI S2PP_HX_ACC_REGNO)
       	   	      (match_operand:FXV_HXI 1 "register_operand" "qv")
		      (match_operand:FXV_HXI 2 "register_operand" "qv")
		      (match_operand:SI 3 "u2bit_cint_operand" "i")] UNSPEC_FXV_HXMA))]
  "TARGET_S2PP_HX"
  "fxvma<FXV_HXI_char>m %0,%1,%2,%3"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_hx_fxvmatac<FXV_HXI_char>m"
  [(set (reg:FXV_HXI S2PP_HX_ACC_REGNO)
       		(unspec:FXV_HXI [(reg:FXV_HXI S2PP_HX_ACC_REGNO)
        	   	      (match_operand:FXV_HXI 0 "register_operand" "qv")
			      (match_operand:FXV_HXI 1 "register_operand" "qv")
			      (match_operand:SI 2 "u2bit_cint_operand" "i")]
		UNSPEC_FXV_HXMATAC))]
  "TARGET_S2PP_HX"
  "fxvmatac<FXV_HXI_char>m %0,%1,%2"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_hx_fxvmultac<FXV_HXI_char>m"
  [(set (reg:FXV_HXI S2PP_HX_ACC_REGNO)
        	(unspec:FXV_HXI [(match_operand:FXV_HXI 0 "register_operand" "qv")
		  	      (match_operand:FXV_HXI 1 "register_operand" "qv")
			      (match_operand:SI 2 "u2bit_cint_operand" "i")]
		UNSPEC_FXV_HXMULTAC))]
  "TARGET_S2PP_HX"
  "fxvmultac<FXV_HXI_char>m %0,%1,%2"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_hx_fxvaddactac<FXV_HXI_char>m"
  [(set (reg:FXV_HXI S2PP_HX_ACC_REGNO)
        	(unspec:FXV_HXI [(match_operand:FXV_HXI 0 "register_operand" "qv")
			      (match_operand:SI 1 "u2bit_cint_operand" "i")
			     (reg:FXV_HXI S2PP_HX_ACC_REGNO)]
		UNSPEC_FXV_HXADDACTAC))]
  "TARGET_S2PP_HX"
  "fxvaddactac<FXV_HXI_char>m %0,%1"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_hx_fxvaddtac<FXV_HXI_char>"
  [(set (reg:FXV_HXI S2PP_HX_ACC_REGNO)
        	(unspec:FXV_HXI [(match_operand:FXV_HXI 0 "register_operand" "qv")
			      (match_operand:FXV_HXI 1 "register_operand" "qv")
			      (match_operand:SI 2 "u2bit_cint_operand" "i")
			      (reg:FXV_HXI S2PP_HX_ACC_REGNO)]
		UNSPEC_FXV_HXADDTAC))]
  "TARGET_S2PP_HX"
  "fxvaddtac<FXV_HXI_char> %0,%1,%2"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_hx_fxvaddac<FXV_HXI_char>m"
  [(set (match_operand:FXV_HXI 0 "register_operand" "=qv")
	        (unspec:FXV_HXI [(match_operand:FXV_HXI 1 "register_operand" "qv")
			      (match_operand:SI 2 "u2bit_cint_operand" "i")
			      (reg:FXV_HXI S2PP_HX_ACC_REGNO)]
		UNSPEC_FXV_HXADDAC))]
  "TARGET_S2PP_HX"
  "fxvaddac<FXV_HXI_char>m %0,%1,%2"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_hx_fxvmtac<FXV_HXI_char>f"
  [(set	(reg:FXV_HXI S2PP_HX_ACC_REGNO)
		(unspec:FXV_HXI [(match_operand:FXV_HXI 0 "s2pp_hx_register_operand" "qv")
			      (match_operand:SI 1 "u2bit_cint_operand" "i")
			      (reg:FXV_HXI S2PP_HX_ACC_REGNO)]
		UNSPEC_FXV_HXMTACF))]
  "TARGET_S2PP_HX"
  "fxvmtac<FXV_HXI_char>f %0,%1"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_hx_fxvma<FXV_HXI_char>fs"
  [(set (match_operand:FXV_HXI 0 "register_operand" "=qv")
       		(unspec:FXV_HXI [(reg:FXV_HXI S2PP_HX_ACC_REGNO)
        	      	      (match_operand:FXV_HXI 1 "register_operand" "qv")
			      (match_operand:FXV_HXI 2 "register_operand" "qv")
			      (match_operand:SI 3 "u2bit_cint_operand" "i")]
		UNSPEC_FXV_HXMAF))]
  "TARGET_S2PP_HX"
  "fxvma<FXV_HXI_char>fs %0,%1,%2,%3"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_hx_fxvmatac<FXV_HXI_char>fs"
  [(set (reg:FXV_HXI S2PP_HX_ACC_REGNO)
       		(unspec:FXV_HXI [(reg:FXV_HXI S2PP_HX_ACC_REGNO)
        		      (match_operand:FXV_HXI 0 "register_operand" "qv")
			      (match_operand:FXV_HXI 1 "register_operand" "qv")
			      (match_operand:SI 2 "u2bit_cint_operand" "i")]
		UNSPEC_FXV_HXMATACF))]
  "TARGET_S2PP_HX"
  "fxvmatac<FXV_HXI_char>fs %0,%1,%2"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_hx_fxvmultac<FXV_HXI_char>fs"
  [(set (reg:FXV_HXI S2PP_HX_ACC_REGNO)
        	(unspec:FXV_HXI [(reg:FXV_HXI S2PP_HX_ACC_REGNO)
			      (match_operand:FXV_HXI 0 "register_operand" "qv")
			      (match_operand:FXV_HXI 1 "register_operand" "qv")
			      (match_operand:SI 2 "u2bit_cint_operand" "i")]
		UNSPEC_FXV_HXMULTACF))]
  "TARGET_S2PP_HX"
  "fxvmultac<FXV_HXI_char>fs %0,%1,%2"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_hx_fxvaddactac<FXV_HXI_char>f"
  [(set (reg:FXV_HXI S2PP_HX_ACC_REGNO)
        	(unspec:FXV_HXI [(reg:FXV_HXI S2PP_HX_ACC_REGNO)
			      (match_operand:FXV_HXI 0 "register_operand" "qv")
			      (match_operand:SI 1 "u2bit_cint_operand" "i")]
		UNSPEC_FXV_HXADDACTACF))]
  "TARGET_S2PP_HX"
  "fxvaddactac<FXV_HXI_char>f %0,%1"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_hx_fxvaddac<FXV_HXI_char>fs"
  [(set (match_operand:FXV_HXI 0 "register_operand" "=qv")
        	(unspec:FXV_HXI [(match_operand:FXV_HXI 1 "register_operand" "qv")
			      (match_operand:SI 2 "u2bit_cint_operand" "i")
			      (reg:FXV_HXI S2PP_HX_ACC_REGNO)]
		UNSPEC_FXV_HXADDACF))]
  "TARGET_S2PP_HX"
  "fxvaddac<FXV_HXI_char>fs %0,%1,%2"
  [(set_attr "type" "vecsimple")])

;;TODO: use define_and_split
;; pack
(define_insn_and_split "s2pp_hx_fxvpckbu"
  [(set (match_operand:V128QI 0 "register_operand" "=qv")
	(unspec:V128QI [(match_operand:V64HI 1 "indexed_or_indirect_address" "a")
        	       (match_operand:V64HI 2 "indexed_or_indirect_address" "a")
        	       (match_operand:SI 3 "u2bit_cint_operand" "i")]
		       UNSPEC_FXV_HXPCKU))]
  "TARGET_S2PP_HX"
  "#"
  "reload_completed"
  [(set (match_operand:V128QI 0 "register_operand" "=qv")
	(unspec:V128QI [(match_operand:V64HI 1 "indexed_or_indirect_address" "a")
        	       (match_operand:V64HI 2 "indexed_or_indirect_address" "a")
        	       (match_operand:SI 3 "u2bit_cint_operand" "i")]
		       UNSPEC_FXV_HXPCKU_DIRECT))
  (unspec_volatile [(const_int 0)] UNSPEC_FXV_HXSYNC)]
  "")

(define_insn "*s2pp_hx_fxvpckbu_internal"
  [(set (match_operand:V128QI 0 "register_operand" "=qv")
	(unspec:V128QI [(match_operand:V64HI 1 "indexed_or_indirect_address" "a")
        	       (match_operand:V64HI 2 "indexed_or_indirect_address" "a")
        	       (match_operand:SI 3 "u2bit_cint_operand" "i")]
		       UNSPEC_FXV_HXPCKU_DIRECT))]
  "TARGET_S2PP_HX"
  "fxvpckbu %0,%1,%2,%3"
  [(set_attr "type" "vecload")])

(define_insn_and_split "s2pp_hx_fxvpckbl"
  [(set (match_operand:V128QI 0 "register_operand" "=qv")
	(unspec:V128QI [(match_operand:V64HI 1 "indexed_or_indirect_address" "a")
        	       (match_operand:V64HI 2 "indexed_or_indirect_address" "a")
        	       (match_operand:SI 3 "u2bit_cint_operand" "i")]
		       UNSPEC_FXV_HXPCKL))]
  "TARGET_S2PP_HX"
  "#"
  "reload_completed"
  [(set (match_operand:V128QI 0 "register_operand" "=qv")
	(unspec:V128QI [(match_operand:V64HI 1 "indexed_or_indirect_address" "a")
        	       (match_operand:V64HI 2 "indexed_or_indirect_address" "a")
        	       (match_operand:SI 3 "u2bit_cint_operand" "i")]
		       UNSPEC_FXV_HXPCKL_DIRECT))
  (unspec_volatile [(const_int 0)] UNSPEC_FXV_HXSYNC)]
  "")

(define_insn "*s2pp_hx_fxvpckbl_internal"
  [(set (match_operand:V128QI 0 "register_operand" "=qv")
	(unspec:V128QI [(match_operand:V64HI 1 "indexed_or_indirect_address" "a")
        	       (match_operand:V64HI 2 "indexed_or_indirect_address" "a")
        	       (match_operand:SI 3 "u2bit_cint_operand" "i")]
		       UNSPEC_FXV_HXPCKL_DIRECT))]
  "TARGET_S2PP_HX"
  "fxvpckbl %0,%1,%2,%3"
  [(set_attr "type" "vecload")])

;;unpack
(define_insn_and_split "s2pp_hx_fxvupckbl"
   [(set (match_operand:V64HI 0 "s2pp_hx_register_operand" "=qv")
	 (unspec:V64HI [(match_operand:V128QI 1 "indexed_or_indirect_address" "a")
	 	       (match_operand:V128QI 2 "indexed_or_indirect_address" "a")
	 	       (match_operand:SI 3 "u2bit_cint_operand" "i")]
         		UNSPEC_FXV_HXUPCKL))]
  "TARGET_S2PP_HX"
  "#"
  "reload_completed"
   [(set (match_operand:V64HI 0 "s2pp_hx_register_operand" "=qv")
	 (unspec:V64HI [(match_operand:V128QI 1 "indexed_or_indirect_address" "a")
	 	       (match_operand:V128QI 2 "indexed_or_indirect_address" "a")
	 	       (match_operand:SI 3 "u2bit_cint_operand" "i")]
         UNSPEC_FXV_HXUPCKL_DIRECT))
  (unspec_volatile [(const_int 0)] UNSPEC_FXV_HXSYNC)]
  "")

(define_insn "*s2pp_hx_fxvupckbl_internal"
   [(set (match_operand:V64HI 0 "s2pp_hx_register_operand" "=qv")
	 (unspec:V64HI [(match_operand:V128QI 1 "indexed_or_indirect_address" "a")
	 	       (match_operand:V128QI 2 "indexed_or_indirect_address" "a")
	 	       (match_operand:SI 3 "u2bit_cint_operand" "i")]
         UNSPEC_FXV_HXUPCKL_DIRECT))]
  "TARGET_S2PP_HX"
  "fxvupckbl %0,%1,%2,%3"
  [(set_attr "type" "vecload")])

(define_insn_and_split "s2pp_hx_fxvupckbr"
   [(set (match_operand:V64HI 0 "s2pp_hx_register_operand" "=qv")
	 (unspec:V64HI [(match_operand:V128QI 1 "indexed_or_indirect_address" "a")
	 	       (match_operand:V128QI 2 "indexed_or_indirect_address" "a")
		       (match_operand:SI 3 "u2bit_cint_operand" "i")]
		       UNSPEC_FXV_HXUPCKR))]
  "TARGET_S2PP_HX"
  "#"
  "reload_completed"
   [(set (match_operand:V64HI 0 "s2pp_hx_register_operand" "=qv")
	 (unspec:V64HI [(match_operand:V128QI 1 "indexed_or_indirect_address" "a")
	 	       (match_operand:V128QI 2 "indexed_or_indirect_address" "a")
	 	       (match_operand:SI 3 "u2bit_cint_operand" "i")]
         UNSPEC_FXV_HXUPCKR_DIRECT))
  (unspec_volatile [(const_int 0)] UNSPEC_FXV_HXSYNC)]
  "")

(define_insn "*s2pp_hx_fxvupckbr_internal"
   [(set (match_operand:V64HI 0 "s2pp_hx_register_operand" "=qv")
	 (unspec:V64HI [(match_operand:V128QI 1 "indexed_or_indirect_address" "a")
	 	       (match_operand:V128QI 2 "indexed_or_indirect_address" "a")
		       (match_operand:SI 3 "u2bit_cint_operand" "i")]
		       UNSPEC_FXV_HXUPCKR_DIRECT))]
  "TARGET_S2PP_HX"
  "fxvupckbr %0,%1,%2,%3"
  [(set_attr "type" "vecload")])
