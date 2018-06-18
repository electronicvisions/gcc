;;s2pp machine description file

(define_c_enum "unspec"
  [UNSPEC_FXVSTAX
   UNSPEC_FXVLAX
   UNSPEC_FXVLAX_DIRECT
   UNSPEC_FXVSTAX_GT
   UNSPEC_FXVSTAX_LT
   UNSPEC_FXVSTAX_EQ
   UNSPEC_FXVLAX_GT
   UNSPEC_FXVLAX_LT
   UNSPEC_FXVLAX_EQ
   UNSPEC_FXVOUTX
   UNSPEC_FXVINX
   UNSPEC_FXVOUTX_GT
   UNSPEC_FXVOUTX_LT
   UNSPEC_FXVOUTX_EQ
   UNSPEC_FXVINX_GT
   UNSPEC_FXVINX_LT
   UNSPEC_FXVINX_EQ
   UNSPEC_FXVSPLAT_DIRECT
   UNSPEC_FXVSPLAT
   UNSPEC_FXVADD
   UNSPEC_FXVADD_C
   UNSPEC_FXVADDF
   UNSPEC_FXVADDF_C
   UNSPEC_FXVMA
   UNSPEC_FXVMAF
   UNSPEC_FXVADDACTACF
   UNSPEC_FXVADDACTAC
   UNSPEC_FXVMATAC
   UNSPEC_FXVMATACF
   UNSPEC_FXVMULTAC
   UNSPEC_FXVMULTACF
   UNSPEC_FXVADDTAC
   UNSPEC_FXVADDAC
   UNSPEC_FXVADDACF
   UNSPEC_FXVSUB
   UNSPEC_FXVSUB_C
   UNSPEC_FXVSUBF
   UNSPEC_FXVSUBF_C
   UNSPEC_FXVMUL
   UNSPEC_FXVMUL_C
   UNSPEC_FXVMULF
   UNSPEC_FXVMULF_C
   UNSPEC_FXVMTAC
   UNSPEC_FXVMTACF
   UNSPEC_FXVPCKU
   UNSPEC_FXVPCKL
   UNSPEC_FXVUPCKL
   UNSPEC_FXVUPCKR
   UNSPEC_FXVPCKU_DIRECT
   UNSPEC_FXVPCKL_DIRECT
   UNSPEC_FXVUPCKL_DIRECT
   UNSPEC_FXVUPCKR_DIRECT
   UNSPEC_FXVSELECT
   UNSPEC_FXVSYNC
   UNSPEC_FXVCMP
])

;; Vec int modes
(define_mode_iterator FXVI [V8HI V16QI])
(define_code_iterator C_cond [gt lt eq])

(define_int_iterator FXVLAX [UNSPEC_FXVLAX
			       UNSPEC_FXVLAX_GT
			       UNSPEC_FXVLAX_LT
			       UNSPEC_FXVLAX_EQ])
(define_int_iterator FXVSTAX [UNSPEC_FXVSTAX
				UNSPEC_FXVSTAX_GT
				UNSPEC_FXVSTAX_LT
				UNSPEC_FXVSTAX_EQ])
(define_int_iterator FXVINX [UNSPEC_FXVINX
			       UNSPEC_FXVINX_GT
			       UNSPEC_FXVINX_LT
			       UNSPEC_FXVINX_EQ])
(define_int_iterator FXVOUTX [UNSPEC_FXVOUTX
				UNSPEC_FXVOUTX_GT
				UNSPEC_FXVOUTX_LT
				UNSPEC_FXVOUTX_EQ])
;;(define_int_iterator SAT [m fs f])

;; Vec attributes
(define_mode_attr FXVI_char [(V8HI "h") (V16QI "b")])

(define_mode_attr FXVI_unit [(V8HI "VECTOR_UNIT_S2PP_P (V8HImode)")
			   (V16QI "VECTOR_UNIT_S2PP_P (V16QImode)")])

(define_code_attr C_char [(gt "1") (lt "2") (eq "3")])

(define_int_attr fxvlax_int [(UNSPEC_FXVLAX "0")
			     (UNSPEC_FXVLAX_GT "1")
			     (UNSPEC_FXVLAX_LT "2")
			     (UNSPEC_FXVLAX_EQ "3")])
(define_int_attr fxvlax_char [(UNSPEC_FXVLAX "_")
			      (UNSPEC_FXVLAX_GT "_gt_")
			      (UNSPEC_FXVLAX_LT "_lt_")
			      (UNSPEC_FXVLAX_EQ "_eq_")])
(define_int_attr fxvstax_int [(UNSPEC_FXVSTAX "0")
			  (UNSPEC_FXVSTAX_GT "1")
			  (UNSPEC_FXVSTAX_LT "2")
			  (UNSPEC_FXVSTAX_EQ "3")])
(define_int_attr fxvstax_char [(UNSPEC_FXVSTAX "_")
			       (UNSPEC_FXVSTAX_GT "_gt_")
			       (UNSPEC_FXVSTAX_LT "_lt_")
			       (UNSPEC_FXVSTAX_EQ "_eq_")])
(define_int_attr fxvinx_int [(UNSPEC_FXVINX "0")
			     (UNSPEC_FXVINX_GT "1")
			     (UNSPEC_FXVINX_LT "2")
			     (UNSPEC_FXVINX_EQ "3")])
(define_int_attr fxvinx_char [(UNSPEC_FXVINX "_")
			      (UNSPEC_FXVINX_GT "_gt_")
			      (UNSPEC_FXVINX_LT "_lt_")
			      (UNSPEC_FXVINX_EQ "_eq_")])
(define_int_attr fxvoutx_int [(UNSPEC_FXVOUTX "0")
			  (UNSPEC_FXVOUTX_GT "1")
			  (UNSPEC_FXVOUTX_LT "2")
			  (UNSPEC_FXVOUTX_EQ "3")])
(define_int_attr fxvoutx_char [(UNSPEC_FXVOUTX "_")
			       (UNSPEC_FXVOUTX_GT "_gt_")
			       (UNSPEC_FXVOUTX_LT "_lt_")
			       (UNSPEC_FXVOUTX_EQ "_eq_")])

;; s2pp sync instruction
(define_insn "sync"
  [(unspec_volatile [(const_int 0)] UNSPEC_FXVSYNC)]
  "TARGET_S2PP"
  "sync"
  [(set_attr "type" "sync")])

(define_insn "*s2pp_mov<mode>"
  [(set (match_operand:FXVI 0 "nonimmediate_operand" "=Z,kv,kv,*Y,*r,*r,kv,kv")
	(match_operand:FXVI 1 "input_operand" "kv,Z,kv,r,Y,r,j,W"))]
  "VECTOR_MEM_S2PP_P (<MODE>mode)
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
;;  [(set (match_operand:FXVI 0 "s2pp_register_operand" "")
;;	(match_operand:FXVI 1 "indexed_or_indirect_operand" ""))]
;;  "VECTOR_MEM_S2PP_P (<MODE>mode)
;;   && (register_operand (operands[0], <MODE>mode)
;;       || register_operand (operands[1], <MODE>mode))"
;;  [(parallel
;;    [(set (match_operand:FXVI 0 "s2pp_register_operand" "=kv")
;;	  (match_operand:FXVI 1 "memory_operand" "Z"))
;;     (unspec [(const_int 0)] UNSPEC_FXVLAX)])]
;;  "")

(define_split
  [(set (match_operand:FXVI 0 "indexed_or_indirect_operand" "")
	(match_operand:FXVI 1 "s2pp_register_operand" ""))]
  "VECTOR_MEM_S2PP_P (<MODE>mode)
   && (register_operand (operands[0], <MODE>mode)
       || register_operand (operands[1], <MODE>mode))"
  [(parallel
    [(set (match_operand:FXVI 0 "memory_operand" "")
	  (match_operand:FXVI 1 "s2pp_register_operand" ""))
    (unspec [(const_int 0)] UNSPEC_FXVSTAX)])]
  "")

(define_split
  [(set (match_operand:FXVI 0 "s2pp_register_operand" "")
	(match_operand:FXVI 1 "easy_vector_constant" ""))]
  "TARGET_S2PP && can_create_pseudo_p()"
  [(set (match_dup 2) (match_dup 3))
   (set (match_dup 0)
	(unspec:FXVI
	     [(match_dup 2)]
	UNSPEC_FXVSPLAT))]
  "{
    operands[2] = gen_reg_rtx (SImode);
    operands[3] = CONST_VECTOR_ELT(operands[1], 1);
  }")

;;store
(define_insn_and_split "s2pp_fxvstax<fxvstax_char><mode>"
  [(parallel
    [(set (match_operand:FXVI 0 "memory_operand" "=Z")
	  (match_operand:FXVI 1 "register_operand" "kv"))
    (unspec [(const_int 0)] FXVSTAX)])]
  "TARGET_S2PP"
  "#"
  "reload_completed"
  [(set (match_operand:FXVI 0 "memory_operand" "")
        (unspec:FXVI [(match_operand:FXVI 1 "s2pp_register_operand" "")] FXVSTAX))
   (unspec_volatile [(const_int 0)] UNSPEC_FXVSYNC)]
  ""
  [(set_attr "type" "vecstore")])

(define_insn "*s2pp_fxvstax_<fxvstax_int>_<mode>_direct"
  [(set (match_operand:FXVI 0 "memory_operand" "=Z")
	(unspec:FXVI [(match_operand:FXVI 1 "register_operand" "kv")] FXVSTAX))]
  "TARGET_S2PP"
  "fxvstax %1,%y0,<fxvstax_int>"
  [(set_attr "type" "vecstore")])


;;load
(define_insn "s2pp_fxvlax<fxvlax_char><mode>"
  [(parallel
    [(set (match_operand:FXVI 0 "register_operand" "=kv")
	  (match_operand:FXVI 1 "memory_operand" "Z"))
    (unspec [(const_int 0)] FXVLAX)])]
  "TARGET_S2PP"
  "fxvlax %0,%y1,<fxvlax_int>"
  [(set_attr "type" "vecload")])

;;synram
(define_insn "s2pp_fxvoutx<fxvoutx_char><mode>"
  [(parallel
    [(set (match_operand:FXVI 0 "memory_operand" "=Z")
	  (match_operand:FXVI 1 "register_operand" "kv"))
    (unspec [(const_int 0)] FXVOUTX)])]
  "TARGET_S2PP"
  "fxvoutx %1,%y0,<fxvoutx_int>"
  [(set_attr "type" "vecstore")])

(define_insn "s2pp_fxvinx<fxvinx_char><mode>"
  [(parallel
    [(set (match_operand:FXVI 0 "register_operand" "=kv")
	  (match_operand:FXVI 1 "memory_operand" "Z"))
    (unspec [(const_int 0)] FXVINX)])]
  "TARGET_S2PP"
  "fxvinx %0,%y1,<fxvinx_int>"
  [(set_attr "type" "vecload")])

;; add
(define_insn_and_split "fxvadd<mode>3"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
        (plus:FXVI (match_operand:FXVI 1 "register_operand" "kv")
		   (match_operand:FXVI 2 "register_operand" "kv")))]
  "<FXVI_unit>"
  "#"
  ""
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
	(unspec:FXVI [(match_operand:FXVI 1 "register_operand" "kv")
		      (match_operand:FXVI 2 "register_operand" "kv")]
	UNSPEC_FXVADDF))]
  ""
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvadd<FXVI_char>m"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
	(unspec:FXVI [(match_operand:FXVI 1 "register_operand" "kv")
		      (match_operand:FXVI 2 "register_operand" "kv")]
	UNSPEC_FXVADD))]
  "<FXVI_unit>"
  "fxvadd<FXVI_char>m %0,%1,%2"
  [(set_attr "type" "vecsimple")])

(define_insn_and_split "s2pp_fxvadd<FXVI_char>m_c"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
	(unspec:FXVI [(match_operand:FXVI 1 "register_operand" "kv")
		      (match_operand:FXVI 2 "register_operand" "kv")
		      (match_operand:SI 3 "u2bit_cint_operand" "i")
		      (reg:FXVI S2PP_COND_REGNO)]
	UNSPEC_FXVADD_C))]
  "<FXVI_unit>"
  "#"
  "can_create_pseudo_p()"
  [(set (match_dup 4)
	(unspec:FXVI [(match_operand:FXVI 1 "register_operand" "")
		      (match_operand:FXVI 2 "register_operand" "")]
	UNSPEC_FXVADD))
   (set (match_operand:FXVI 0 "register_operand" "")
	 (unspec:FXVI [(match_operand:SI 3 "u2bit_cint_operand" "")
	 (match_operand:FXVI 0 "register_operand" "")
	 (match_dup 4)] UNSPEC_FXVSELECT))]
   "{operands[4] = gen_reg_rtx (<MODE>mode);}"
  [(set_attr "type" "vecsimple")])

(define_insn_and_split "s2pp_fxvadd<FXVI_char>fs_c"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
        (unspec:FXVI [(match_operand:FXVI 1 "register_operand" "kv")
		      (match_operand:FXVI 2 "register_operand" "kv")
		      (match_operand:SI 3 "u2bit_cint_operand" "i")
		      (reg:FXVI S2PP_COND_REGNO)]
	UNSPEC_FXVADDF_C))]
  "<FXVI_unit>"
  "#"
  "can_create_pseudo_p()"
  [(set (match_dup 4)
	(unspec:FXVI [(match_operand:FXVI 1 "register_operand" "")
		      (match_operand:FXVI 2 "register_operand" "")]
	UNSPEC_FXVADDF))
   (set (match_operand:FXVI 0 "register_operand" "")
	 (unspec:FXVI [(match_operand:SI 3 "u2bit_cint_operand" "")
	 (match_operand:FXVI 0 "register_operand" "")
	 (match_dup 4)] UNSPEC_FXVSELECT))]
   "{operands[4] = gen_reg_rtx (<MODE>mode);}"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvadd<FXVI_char>fs"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
        (unspec:FXVI [(match_operand:FXVI 1 "register_operand" "kv")
		      (match_operand:FXVI 2 "register_operand" "kv")]
	UNSPEC_FXVADDF))]
  "<FXVI_unit>"
  "fxvadd<FXVI_char>fs %0,%1,%2"
  [(set_attr "type" "vecsimple")])

;; sub
(define_insn_and_split "fxvsub<mode>3"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
        (minus:FXVI (match_operand:FXVI 1 "register_operand" "kv")
		  (match_operand:FXVI 2 "register_operand" "kv")))]
  "<FXVI_unit>"
  "#"
  ""
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
	(unspec:FXVI [(match_operand:FXVI 1 "register_operand" "kv")
		      (match_operand:FXVI 2 "register_operand" "kv")]
	UNSPEC_FXVSUB))]
  ""
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvsub<FXVI_char>m"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
	(unspec:FXVI [(match_operand:FXVI 1 "register_operand" "kv")
		      (match_operand:FXVI 2 "register_operand" "kv")] UNSPEC_FXVSUB))]
  "<FXVI_unit>"
  "fxvsub<FXVI_char>m %0,%1,%2"
  [(set_attr "type" "vecsimple")])

(define_insn_and_split "s2pp_fxvsub<FXVI_char>m_c"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
	(unspec:FXVI [(match_operand:FXVI 1 "register_operand" "kv")
		      (match_operand:FXVI 2 "register_operand" "kv")
		      (match_operand:SI 3 "u2bit_cint_operand" "i")
		      (reg:FXVI S2PP_COND_REGNO)]
	UNSPEC_FXVSUB_C))]
  "<FXVI_unit>"
  "#"
  "can_create_pseudo_p()"
  [(set (match_dup 4)
	(unspec:FXVI [(match_operand:FXVI 1 "register_operand" "")
		      (match_operand:FXVI 2 "register_operand" "")]
	UNSPEC_FXVSUB))
   (set (match_operand:FXVI 0 "register_operand" "")
	 (unspec:FXVI [(match_operand:SI 3 "u2bit_cint_operand" "")
	 (match_operand:FXVI 0 "register_operand" "")
	 (match_dup 4)] UNSPEC_FXVSELECT))]
   "{operands[4] = gen_reg_rtx (<MODE>mode);}"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvsub<FXVI_char>fs"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
	(unspec:FXVI [(match_operand:FXVI 1 "register_operand" "kv")
		      (match_operand:FXVI 2 "register_operand" "kv")] UNSPEC_FXVSUBF))]
  "<FXVI_unit>"
  "fxvsub<FXVI_char>fs %0,%1,%2"
  [(set_attr "type" "vecsimple")])

(define_insn_and_split "s2pp_fxvsub<FXVI_char>fs_c"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
	(unspec:FXVI [(match_operand:FXVI 1 "register_operand" "kv")
		      (match_operand:FXVI 2 "register_operand" "kv")
		      (match_operand:SI 3 "u2bit_cint_operand" "i")
		      (reg:FXVI S2PP_COND_REGNO)]
	UNSPEC_FXVSUBF_C))]
  "<FXVI_unit>"
  "#"
  "can_create_pseudo_p()"
  [(set (match_dup 4)
	(unspec:FXVI [(match_operand:FXVI 1 "register_operand" "")
		      (match_operand:FXVI 2 "register_operand" "")]
	UNSPEC_FXVSUBF))
   (set (match_operand:FXVI 0 "register_operand" "")
	 (unspec:FXVI [(match_operand:SI 3 "u2bit_cint_operand" "")
	 (match_operand:FXVI 0 "register_operand" "")
	 (match_dup 4)] UNSPEC_FXVSELECT))]
   "{operands[4] = gen_reg_rtx (<MODE>mode);}"
  [(set_attr "type" "vecsimple")])


;; multiply
(define_insn_and_split "s2pp_fxvmul<FXVI_char>"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
        (mult:FXVI (match_operand:FXVI 1 "register_operand" "kv")
		  (match_operand:FXVI 2 "register_operand" "kv")))]
  "<FXVI_unit>"
  "#"
  ""
  [(set (match_operand:FXVI 0 "register_operand" "")
	(unspec:FXVI [(match_operand:FXVI 1 "register_operand" "")
		      (match_operand:FXVI 2 "register_operand" "")] UNSPEC_FXVMUL))]
  ""
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvmul<FXVI_char>m"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
	(unspec:FXVI [(match_operand:FXVI 1 "register_operand" "kv")
		      (match_operand:FXVI 2 "register_operand" "kv")] UNSPEC_FXVMUL))]
  "<FXVI_unit>"
  "fxvmul<FXVI_char>m %0,%1,%2"
  [(set_attr "type" "vecsimple")])

(define_insn_and_split "s2pp_fxvmul<FXVI_char>m_c"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
	(unspec:FXVI [(match_operand:FXVI 1 "register_operand" "kv")
		      (match_operand:FXVI 2 "register_operand" "kv")
		      (match_operand:SI 3 "u2bit_cint_operand" "i")
		      (reg:FXVI S2PP_COND_REGNO)]
	UNSPEC_FXVMUL_C))]
  "<FXVI_unit>"
  "#"
  "can_create_pseudo_p()"
  [(set (match_dup 4)
	(unspec:FXVI [(match_operand:FXVI 1 "register_operand" "")
		      (match_operand:FXVI 2 "register_operand" "")]
	UNSPEC_FXVMUL))
   (set (match_operand:FXVI 0 "register_operand" "")
	 (unspec:FXVI [(match_operand:SI 3 "u2bit_cint_operand" "")
	 (match_operand:FXVI 0 "register_operand" "")
	 (match_dup 4)] UNSPEC_FXVSELECT))]
   "{operands[4] = gen_reg_rtx (<MODE>mode);}"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvmul<FXVI_char>fs"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
	(unspec:FXVI [(match_operand:FXVI 1 "register_operand" "kv")
		      (match_operand:FXVI 2 "register_operand" "kv")] UNSPEC_FXVMULF))]
  "<FXVI_unit>"
  "fxvmul<FXVI_char>fs %0,%1,%2"
  [(set_attr "type" "vecsimple")])

(define_insn_and_split "s2pp_fxvmul<FXVI_char>fs_c"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
	(unspec:FXVI [(match_operand:FXVI 1 "register_operand" "kv")
		      (match_operand:FXVI 2 "register_operand" "kv")
		      (match_operand:SI 3 "u2bit_cint_operand" "i")
		      (reg:FXVI S2PP_COND_REGNO)]
	UNSPEC_FXVMULF_C))]
  "<FXVI_unit>"
  "#"
  "can_create_pseudo_p()"
  [(set (match_dup 4)
	(unspec:FXVI [(match_operand:FXVI 1 "register_operand" "")
		      (match_operand:FXVI 2 "register_operand" "")]
	UNSPEC_FXVMULF))
   (set (match_operand:FXVI 0 "register_operand" "")
	 (unspec:FXVI [(match_operand:SI 3 "u2bit_cint_operand" "")
	 (match_operand:FXVI 0 "register_operand" "")
	 (match_dup 4)] UNSPEC_FXVSELECT))]
   "{operands[4] = gen_reg_rtx (<MODE>mode);}"
  [(set_attr "type" "vecsimple")])


;; splat
(define_insn_and_split "s2pp_fxvsplat<FXVI_char>"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
	(unspec:FXVI
	     [(match_operand:SI 1 "register_operand" "r")]
	UNSPEC_FXVSPLAT))]
  "TARGET_S2PP"
  "#"
  "TARGET_S2PP && reload_completed"
  [(set (match_operand:FXVI 0 "register_operand" "")
	(unspec:FXVI
	     [(match_operand:SI 1 "register_operand" "")]
	UNSPEC_FXVSPLAT_DIRECT))]
  ""
  [(set_attr "type" "vecperm")])

(define_insn "*s2pp_fxvsplat<FXVI_char>_direct"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
	(unspec:FXVI
	     [(match_operand:SI 1 "register_operand" "r")]
	UNSPEC_FXVSPLAT_DIRECT))]
  "TARGET_S2PP"
  "fxvsplat<FXVI_char> %0,%1"
  [(set_attr "type" "vecperm")])

;; select
(define_insn "s2pp_fxvsel_<mode>"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
	 (unspec:FXVI [(match_operand:SI 3 "u2bit_cint_operand" "i")
	 (match_operand:FXVI 1 "register_operand" "kv")
	 (match_operand:FXVI 2 "register_operand" "kv")] UNSPEC_FXVSELECT))]
  "VECTOR_MEM_S2PP_P (<MODE>mode)"
  "fxvsel %0,%1,%2,%3"
  [(set_attr "type" "vecperm")])

;; shift
(define_insn "s2pp_fxvshl<FXVI_char>"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
        (ashift:FXVI (match_operand:FXVI 1 "register_operand" "kv")
		     (const_int 1)))]
  "<FXVI_unit>"
  "fxvsh<FXVI_char> %0,%1,1"
  [(set_attr "type" "vecperm")])

(define_insn "s2pp_fxvshr<FXVI_char>"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
        (ashift:FXVI (match_operand:FXVI 1 "register_operand" "kv")
		     (const_int -1)))]
  "<FXVI_unit>"
  "fxvsh<FXVI_char> %0,%1,-1"
  [(set_attr "type" "vecperm")])

(define_insn "s2pp_fxvsh<FXVI_char>"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
        (ashift:FXVI (match_operand:FXVI 1 "register_operand" "kv")
		     (match_operand:SI 2 "u2bit_cint_operand" "i")))]
  "<FXVI_unit>"
  "fxvsh<FXVI_char> %0,%1,%2"
  [(set_attr "type" "vecperm")])

;;compare
(define_insn "s2pp_fxvcmp<FXVI_char>"
  [(set (reg:FXVI S2PP_COND_REGNO)
        (unspec_volatile:FXVI [(match_operand:FXVI 0 "register_operand" "kv")] UNSPEC_FXVCMP))]
  "TARGET_S2PP"
  "fxvcmp<FXVI_char> %0"
  [(set_attr "type" "veccmp")])

;;accumulator insns
(define_insn "s2pp_fxvmtac<FXVI_char>"
  [(set	(reg:FXVI S2PP_ACC_REGNO)
		(unspec:FXVI [(match_operand:FXVI 0 "s2pp_register_operand" "kv")
			      (match_operand:SI 1 "u2bit_cint_operand" "i")
			      (reg:FXVI S2PP_ACC_REGNO)]
		UNSPEC_FXVMTAC))]
  "TARGET_S2PP"
  "fxvmtac<FXVI_char> %0,%1"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvma<FXVI_char>m"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
	(unspec:FXVI [(reg:FXVI S2PP_ACC_REGNO)
       	   	      (match_operand:FXVI 1 "register_operand" "kv")
		      (match_operand:FXVI 2 "register_operand" "kv")
		      (match_operand:SI 3 "u2bit_cint_operand" "i")] UNSPEC_FXVMA))]
  "TARGET_S2PP"
  "fxvma<FXVI_char>m %0,%1,%2,%3"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvmatac<FXVI_char>m"
  [(set (reg:FXVI S2PP_ACC_REGNO)
       		(unspec:FXVI [(reg:FXVI S2PP_ACC_REGNO)
        	   	      (match_operand:FXVI 0 "register_operand" "kv")
			      (match_operand:FXVI 1 "register_operand" "kv")
			      (match_operand:SI 2 "u2bit_cint_operand" "i")]
		UNSPEC_FXVMATAC))]
  "TARGET_S2PP"
  "fxvmatac<FXVI_char>m %0,%1,%2"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvmultac<FXVI_char>m"
  [(set (reg:FXVI S2PP_ACC_REGNO)
        	(unspec:FXVI [(match_operand:FXVI 0 "register_operand" "kv")
		  	      (match_operand:FXVI 1 "register_operand" "kv")
			      (match_operand:SI 2 "u2bit_cint_operand" "i")]
		UNSPEC_FXVMULTAC))]
  "TARGET_S2PP"
  "fxvmultac<FXVI_char>m %0,%1,%2"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvaddactac<FXVI_char>m"
  [(set (reg:FXVI S2PP_ACC_REGNO)
        	(unspec:FXVI [(match_operand:FXVI 0 "register_operand" "kv")
			      (match_operand:SI 1 "u2bit_cint_operand" "i")
			     (reg:FXVI S2PP_ACC_REGNO)]
		UNSPEC_FXVADDACTAC))]
  "TARGET_S2PP"
  "fxvaddactac<FXVI_char>m %0,%1"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvaddtac<FXVI_char>"
  [(set (reg:FXVI S2PP_ACC_REGNO)
        	(unspec:FXVI [(match_operand:FXVI 0 "register_operand" "kv")
			      (match_operand:FXVI 1 "register_operand" "kv")
			      (match_operand:SI 2 "u2bit_cint_operand" "i")
			      (reg:FXVI S2PP_ACC_REGNO)]
		UNSPEC_FXVADDTAC))]
  "TARGET_S2PP"
  "fxvaddtac<FXVI_char> %0,%1,%2"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvaddac<FXVI_char>m"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
	        (unspec:FXVI [(match_operand:FXVI 1 "register_operand" "kv")
			      (match_operand:SI 2 "u2bit_cint_operand" "i")
			      (reg:FXVI S2PP_ACC_REGNO)]
		UNSPEC_FXVADDAC))]
  "TARGET_S2PP"
  "fxvaddac<FXVI_char>m %0,%1,%2"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvmtac<FXVI_char>f"
  [(set	(reg:FXVI S2PP_ACC_REGNO)
		(unspec:FXVI [(match_operand:FXVI 0 "s2pp_register_operand" "kv")
			      (match_operand:SI 1 "u2bit_cint_operand" "i")
			      (reg:FXVI S2PP_ACC_REGNO)]
		UNSPEC_FXVMTACF))]
  "TARGET_S2PP"
  "fxvmtac<FXVI_char>f %0,%1"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvma<FXVI_char>fs"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
       		(unspec:FXVI [(reg:FXVI S2PP_ACC_REGNO)
        	      	      (match_operand:FXVI 1 "register_operand" "kv")
			      (match_operand:FXVI 2 "register_operand" "kv")
			      (match_operand:SI 3 "u2bit_cint_operand" "i")]
		UNSPEC_FXVMAF))]
  "TARGET_S2PP"
  "fxvma<FXVI_char>fs %0,%1,%2,%3"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvmatac<FXVI_char>fs"
  [(set (reg:FXVI S2PP_ACC_REGNO)
       		(unspec:FXVI [(reg:FXVI S2PP_ACC_REGNO)
        		      (match_operand:FXVI 0 "register_operand" "kv")
			      (match_operand:FXVI 1 "register_operand" "kv")
			      (match_operand:SI 2 "u2bit_cint_operand" "i")]
		UNSPEC_FXVMATACF))]
  "TARGET_S2PP"
  "fxvmatac<FXVI_char>fs %0,%1,%2"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvmultac<FXVI_char>fs"
  [(set (reg:FXVI S2PP_ACC_REGNO)
        	(unspec:FXVI [(reg:FXVI S2PP_ACC_REGNO)
			      (match_operand:FXVI 0 "register_operand" "kv")
			      (match_operand:FXVI 1 "register_operand" "kv")
			      (match_operand:SI 2 "u2bit_cint_operand" "i")]
		UNSPEC_FXVMULTACF))]
  "TARGET_S2PP"
  "fxvmultac<FXVI_char>fs %0,%1,%2"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvaddactac<FXVI_char>f"
  [(set (reg:FXVI S2PP_ACC_REGNO)
        	(unspec:FXVI [(reg:FXVI S2PP_ACC_REGNO)
			      (match_operand:FXVI 0 "register_operand" "kv")
			      (match_operand:SI 1 "u2bit_cint_operand" "i")]
		UNSPEC_FXVADDACTACF))]
  "TARGET_S2PP"
  "fxvaddactac<FXVI_char>f %0,%1"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvaddac<FXVI_char>fs"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
        	(unspec:FXVI [(match_operand:FXVI 1 "register_operand" "kv")
			      (match_operand:SI 2 "u2bit_cint_operand" "i")
			      (reg:FXVI S2PP_ACC_REGNO)]
		UNSPEC_FXVADDACF))]
  "TARGET_S2PP"
  "fxvaddac<FXVI_char>fs %0,%1,%2"
  [(set_attr "type" "vecsimple")])

;;TODO: use define_and_split
;; pack
(define_insn_and_split "s2pp_fxvpckbu"
  [(set (match_operand:V16QI 0 "register_operand" "=kv")
	(unspec:V16QI [(match_operand:V8HI 1 "indexed_or_indirect_address" "a")
        	       (match_operand:V8HI 2 "indexed_or_indirect_address" "a")
        	       (match_operand:SI 3 "u2bit_cint_operand" "i")]
		       UNSPEC_FXVPCKU))]
  "TARGET_S2PP"
  "#"
  "reload_completed"
  [(set (match_operand:V16QI 0 "register_operand" "=kv")
	(unspec:V16QI [(match_operand:V8HI 1 "indexed_or_indirect_address" "a")
        	       (match_operand:V8HI 2 "indexed_or_indirect_address" "a")
        	       (match_operand:SI 3 "u2bit_cint_operand" "i")]
		       UNSPEC_FXVPCKU_DIRECT))
  (unspec_volatile [(const_int 0)] UNSPEC_FXVSYNC)]
  "")

(define_insn "*s2pp_fxvpckbu_internal"
  [(set (match_operand:V16QI 0 "register_operand" "=kv")
	(unspec:V16QI [(match_operand:V8HI 1 "indexed_or_indirect_address" "a")
        	       (match_operand:V8HI 2 "indexed_or_indirect_address" "a")
        	       (match_operand:SI 3 "u2bit_cint_operand" "i")]
		       UNSPEC_FXVPCKU_DIRECT))]
  "TARGET_S2PP"
  "fxvpckbu %0,%1,%2,%3"
  [(set_attr "type" "vecload")])

(define_insn_and_split "s2pp_fxvpckbl"
  [(set (match_operand:V16QI 0 "register_operand" "=kv")
	(unspec:V16QI [(match_operand:V8HI 1 "indexed_or_indirect_address" "a")
        	       (match_operand:V8HI 2 "indexed_or_indirect_address" "a")
        	       (match_operand:SI 3 "u2bit_cint_operand" "i")]
		       UNSPEC_FXVPCKL))]
  "TARGET_S2PP"
  "#"
  "reload_completed"
  [(set (match_operand:V16QI 0 "register_operand" "=kv")
	(unspec:V16QI [(match_operand:V8HI 1 "indexed_or_indirect_address" "a")
        	       (match_operand:V8HI 2 "indexed_or_indirect_address" "a")
        	       (match_operand:SI 3 "u2bit_cint_operand" "i")]
		       UNSPEC_FXVPCKL_DIRECT))
  (unspec_volatile [(const_int 0)] UNSPEC_FXVSYNC)]
  "")

(define_insn "*s2pp_fxvpckbl_internal"
  [(set (match_operand:V16QI 0 "register_operand" "=kv")
	(unspec:V16QI [(match_operand:V8HI 1 "indexed_or_indirect_address" "a")
        	       (match_operand:V8HI 2 "indexed_or_indirect_address" "a")
        	       (match_operand:SI 3 "u2bit_cint_operand" "i")]
		       UNSPEC_FXVPCKL_DIRECT))]
  "TARGET_S2PP"
  "fxvpckbl %0,%1,%2,%3"
  [(set_attr "type" "vecload")])

;;unpack
(define_insn_and_split "s2pp_fxvupckbl"
   [(set (match_operand:V8HI 0 "s2pp_register_operand" "=kv")
	 (unspec:V8HI [(match_operand:V16QI 1 "indexed_or_indirect_address" "a")
	 	       (match_operand:V16QI 2 "indexed_or_indirect_address" "a")
	 	       (match_operand:SI 3 "u2bit_cint_operand" "i")]
         		UNSPEC_FXVUPCKL))]
  "TARGET_S2PP"
  "#"
  "reload_completed"
   [(set (match_operand:V8HI 0 "s2pp_register_operand" "=kv")
	 (unspec:V8HI [(match_operand:V16QI 1 "indexed_or_indirect_address" "a")
	 	       (match_operand:V16QI 2 "indexed_or_indirect_address" "a")
	 	       (match_operand:SI 3 "u2bit_cint_operand" "i")]
         UNSPEC_FXVUPCKL_DIRECT))
  (unspec_volatile [(const_int 0)] UNSPEC_FXVSYNC)]
  "")

(define_insn "*s2pp_fxvupckbl_internal"
   [(set (match_operand:V8HI 0 "s2pp_register_operand" "=kv")
	 (unspec:V8HI [(match_operand:V16QI 1 "indexed_or_indirect_address" "a")
	 	       (match_operand:V16QI 2 "indexed_or_indirect_address" "a")
	 	       (match_operand:SI 3 "u2bit_cint_operand" "i")]
         UNSPEC_FXVUPCKL_DIRECT))]
  "TARGET_S2PP"
  "fxvupckbl %0,%1,%2,%3"
  [(set_attr "type" "vecload")])

(define_insn_and_split "s2pp_fxvupckbr"
   [(set (match_operand:V8HI 0 "s2pp_register_operand" "=kv")
	 (unspec:V8HI [(match_operand:V16QI 1 "indexed_or_indirect_address" "a")
	 	       (match_operand:V16QI 2 "indexed_or_indirect_address" "a")
		       (match_operand:SI 3 "u2bit_cint_operand" "i")]
		       UNSPEC_FXVUPCKR))]
  "TARGET_S2PP"
  "#"
  "reload_completed"
   [(set (match_operand:V8HI 0 "s2pp_register_operand" "=kv")
	 (unspec:V8HI [(match_operand:V16QI 1 "indexed_or_indirect_address" "a")
	 	       (match_operand:V16QI 2 "indexed_or_indirect_address" "a")
	 	       (match_operand:SI 3 "u2bit_cint_operand" "i")]
         UNSPEC_FXVUPCKR_DIRECT))
  (unspec_volatile [(const_int 0)] UNSPEC_FXVSYNC)]
  "")

(define_insn "*s2pp_fxvupckbr_internal"
   [(set (match_operand:V8HI 0 "s2pp_register_operand" "=kv")
	 (unspec:V8HI [(match_operand:V16QI 1 "indexed_or_indirect_address" "a")
	 	       (match_operand:V16QI 2 "indexed_or_indirect_address" "a")
		       (match_operand:SI 3 "u2bit_cint_operand" "i")]
		       UNSPEC_FXVUPCKR_DIRECT))]
  "TARGET_S2PP"
  "fxvupckbr %0,%1,%2,%3"
  [(set_attr "type" "vecload")])
