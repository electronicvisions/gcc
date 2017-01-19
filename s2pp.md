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
   UNSPEC_FXVMUL
   UNSPEC_FXVMTAC
   UNSPEC_FXVMTACF
   UNSPEC_FXVPCKU
   UNSPEC_FXVPCKL
   UNSPEC_FXVUPCKL
   UNSPEC_FXVUPCKR
   UNSPEC_FXVCOND
   UNSPEC_FXVSYNC
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

;;s2pp sync instruction
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
;; 0 at the end of case 2 in order to return true -> similar to vor(x,x)
;; alternatively use 3
;; 1 at the end  of case 6 for gt comp -> similar to xor(1,1)
;; alternatively use 2

;; eventually drop peephole and use split instead -> reload_complete good test -> nope MUST be pro reload?

(define_split
  [(set (match_operand:FXVI 0 "s2pp_register_operand" "")
	(match_operand:FXVI 1 "indexed_or_indirect_operand" ""))] 
  "VECTOR_MEM_S2PP_P (<MODE>mode)
   && (register_operand (operands[0], <MODE>mode) 
       || register_operand (operands[1], <MODE>mode))"
  ;;"TARGET_S2PP && reload_completed"
  [(parallel
    [(set (match_operand:FXVI 0 "s2pp_register_operand" "=kv")
	  (match_operand:FXVI 1 "memory_operand" "Z"))
     (unspec [(const_int 0)] UNSPEC_FXVLAX)])]
  "")

(define_split
  [(set (match_operand:FXVI 0 "indexed_or_indirect_operand" "")
	(match_operand:FXVI 1 "s2pp_register_operand" ""))] 
  "VECTOR_MEM_S2PP_P (<MODE>mode)
   && (register_operand (operands[0], <MODE>mode) 
       || register_operand (operands[1], <MODE>mode))"
  ;;"TARGET_S2PP && reload_completed"
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

;;(define_split
;;  [(set (match_operand:FXVI 0 "int_reg_operand" "")
;;	(match_operand:FXVI 1 "s2pp_register_operand" ""))] 
;;  "TARGET_S2PP && can_create_pseudo_p()"
;;  [(set (match_dup 2) (match_dup 1))
;;   (set (match_dup 0) (match_dup 2))]
;;  "{
;;//    emit_move_insn (operands[1], 
;;    operands[2] = gen_rtx_MEM (GET_MODE(operands[1]));
;;  }")


;;(define_insn "s2pp_fxvstax_<mode>"
;;  [(parallel
;;    [(set (match_operand:FXVI 0 "memory_operand" "=Z")
;;	  (match_operand:FXVI 1 "register_operand" "kv"))
;;    (unspec [(const_int 0)] UNSPEC_FXVSTAX)])]
;;  "TARGET_S2PP"
;;  "#"
;;  [(set_attr "type" "vecstore")])

(define_insn "s2pp_fxvstax<fxvstax_char><mode>"
  [(parallel
    [(set (match_operand:FXVI 0 "memory_operand" "=Z")
	  (match_operand:FXVI 1 "register_operand" "kv"))
    (unspec [(const_int 0)] FXVSTAX)])]
  "TARGET_S2PP"
  "#"
  [(set_attr "type" "vecstore")])

(define_split
  [(parallel
    [(set (match_operand:FXVI 0 "memory_operand" "")
	  (match_operand:FXVI 1 "s2pp_register_operand" ""))
    (unspec [(const_int 0)] FXVSTAX)])]
  "TARGET_S2PP && reload_completed"
  [(set (match_operand:FXVI 0 "memory_operand" "")
	(unspec:FXVI [(match_operand:FXVI 1 "s2pp_register_operand" "")] FXVSTAX))
   (unspec_volatile [(const_int 0)] UNSPEC_FXVSYNC)]
  "")

;;(define_insn "s2pp_fxvlax_<mode>"
;;  [(parallel
;;    [(set (match_operand:FXVI 0 "register_operand" "=kv")
;;	  (match_operand:FXVI 1 "memory_operand" "Z"))
;;     (unspec [(const_int 0)] UNSPEC_FXVLAX)])]
;;  "TARGET_S2PP"
;;  "#"
;;  [(set_attr "type" "vecload")])

(define_insn "*s2pp_fxvstax_<fxvstax_int>_<mode>_direct"
  [(set (match_operand:FXVI 0 "memory_operand" "=Z")
	(unspec:FXVI [(match_operand:FXVI 1 "register_operand" "kv")] FXVSTAX))]
  "TARGET_S2PP"
  "fxvstax %1,%y0,<fxvstax_int>"
  [(set_attr "type" "vecstore")])

(define_insn "s2pp_fxvlax<fxvlax_char><mode>"
[(parallel
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
	(match_operand:FXVI 1 "memory_operand" "Z"))
     (unspec [(const_int 0)] FXVLAX)])]
  "TARGET_S2PP"
  "#"
  [(set_attr "type" "vecload")])

(define_split
  [(parallel
    [(set (match_operand:FXVI 0 "s2pp_register_operand" "")
	  (match_operand:FXVI 1 "memory_operand" ""))
     (unspec [(const_int 0)] FXVLAX)])]
  "TARGET_S2PP && reload_completed"
  [(set (match_operand:FXVI 0 "s2pp_register_operand" "")
	(unspec:FXVI [(match_operand:FXVI 1 "memory_operand" "")] FXVLAX))
   (unspec_volatile [(const_int 0)] UNSPEC_FXVSYNC)]
  "")

(define_insn "*s2pp_fxvlax_<fxvlax_int>_<mode>_direct"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
	(unspec:FXVI [(match_operand:FXVI 1 "memory_operand" "Z")] FXVLAX))]
  "TARGET_S2PP"
  "fxvlax %0,%y1,<fxvlax_int>"
  [(set_attr "type" "vecload")])

(define_insn "s2pp_fxvlax_direct"
  [(set (match_operand:V16QI 0 "register_operand" "=kv")
	(unspec:V16QI [(match_operand:V16QI 1 "memory_operand" "Z")]
                      UNSPEC_FXVLAX_DIRECT))]
  "TARGET_S2PP"
  "fxvlax %0,%y1"
  [(set_attr "type" "vecload")])

;;synram
(define_insn "s2pp_fxvoutx_<mode>"
  [(parallel
    [(set (match_operand:FXVI 0 "memory_operand" "=Z")
	  (match_operand:FXVI 1 "register_operand" "kv"))
    (unspec [(const_int 0)] UNSPEC_FXVOUTX)])]
  "TARGET_S2PP"
  "fxvoutx %1,%y0"
  [(set_attr "type" "vecstore")])

(define_insn "s2pp_fxvoutx_<code>_<mode>"
[(parallel  
  [(set (match_operand:FXVI 0 "memory_operand" "=Z")
        (if_then_else:FXVI (C_cond:CC (reg:CC S2PP_COND_REGNO)
                                 (const_int 0))
	(match_operand:FXVI 1 "register_operand" "kv")
	(match_dup 0)))
    (unspec [(const_int 0)] UNSPEC_FXVOUTX)])]
  "TARGET_S2PP"
  "fxvoutx %1,%y0,<C_char>"
  [(set_attr "type" "vecstore")])

(define_insn "s2pp_fxvinx_<mode>"
  [(parallel
    [(set (match_operand:FXVI 0 "register_operand" "=kv")
	  (match_operand:FXVI 1 "memory_operand" "Z"))
     (unspec [(const_int 0)] UNSPEC_FXVINX)])]
  "TARGET_S2PP"
  "fxvinx %0,%y1"
  [(set_attr "type" "vecload")])

(define_insn "s2pp_fxvinx_<code>_<mode>"
  [(parallel
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
        (if_then_else:FXVI (C_cond:CC (reg:CC S2PP_COND_REGNO)
                                 (const_int 0))
	(match_operand:FXVI 1 "memory_operand" "Z")
	(match_dup 0)))
     (unspec [(const_int 0)] UNSPEC_FXVINX)])]
  "TARGET_S2PP"
  "fxvinx %0,%y1,<C_char>"
  [(set_attr "type" "vecload")])

;; add
(define_insn "fxvadd<mode>3"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
        (plus:FXVI (match_operand:FXVI 1 "register_operand" "kv")
		  (match_operand:FXVI 2 "register_operand" "kv")))]
  "<FXVI_unit>"
  "fxvadd<FXVI_char>m %0,%1,%2"
  [(set_attr "type" "vecsimple")])

;;(define_insn "s2pp_fxvadd<FXVI_char>fs"
;;  [(set (match_operand:FXVI 0 "register_operand" "=kv")
;;        (unspec:FXVI [(match_operand:FXVI 1 "register_operand" "kv")
;;		    (match_operand:FXVI 2 "register_operand" "kv")]
;;		   UNSPEC_FXVADD))]
;;  "<FXVI_unit>"
;;  "fxvadd<FXVI_char>fs %0,%1,%2"
;;  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvadd<FXVI_char>m_c"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
	(if_then_else:FXVI
	 (unspec:CC [(reg:CC S2PP_COND_REGNO)
		(match_operand:SI 3 "u_short_cint_operand" "i")] UNSPEC_FXVCOND)
         (plus:FXVI (match_operand:FXVI 1 "register_operand" "kv")
		  (match_operand:FXVI 2 "register_operand" "kv"))
	 (match_dup 0)))]
  "<FXVI_unit>"
  "fxvadd<FXVI_char>m %0,%1,%2,%3"
  [(set_attr "type" "vecsimple")])

;;(define_insn "s2pp_fxvadd<FXVI_char>fs_c"
;;  [(set (match_operand:FXVI 0 "register_operand" "=kv")
;;	(if_then_else:FXVI
;;	 (unspec:CC [(reg:CC S2PP_COND_REGNO)
;;		(match_operand:SI 3 "u_short_cint_operand" "i")] UNSPEC_FXVCOND)
;;         (unspec:FXVI [(match_operand:FXVI 1 "register_operand" "kv")
;;		    (match_operand:FXVI 2 "register_operand" "kv")]
;;		   UNSPEC_FXVADD)
;;	 (match_dup 0)))]
;;  "<FXVI_unit>"
;;  "fxvadd<FXVI_char>fs %0,%1,%2,%3"
;;  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvadd<FXVI_char>fs_c"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
        (unspec:FXVI [(match_operand:FXVI 1 "register_operand" "kv")
		      (match_operand:FXVI 2 "register_operand" "kv")
		      (match_operand:SI 3 "u_short_cint_operand" "i")]
		   UNSPEC_FXVADD))]
  "<FXVI_unit>"
  "fxvadd<FXVI_char>fs %0,%1,%2,%3"
  [(set_attr "type" "vecsimple")])

;; sub
(define_insn "fxvsub<mode>3"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
        (minus:FXVI (match_operand:FXVI 1 "register_operand" "kv")
		   (match_operand:FXVI 2 "register_operand" "kv")))]
  "<FXVI_unit>"
  "fxvsub<FXVI_char>m %0,%1,%2"
  [(set_attr "type" "vecsimple")])

;;(define_insn "s2pp_fxvsub<FXVI_char>fs"
;;  [(set (match_operand:FXVI 0 "register_operand" "=kv")
;;        (unspec:FXVI [(match_operand:FXVI 1 "register_operand" "kv")
;;                    (match_operand:FXVI 2 "register_operand" "kv")]
;;		   UNSPEC_FXVSUB))]
;;  "VECTOR_UNIT_S2PP_P (<MODE>mode)"
;;  "fxvsub<FXVI_char>fs %0,%1,%2"
;;  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvsub<FXVI_char>m_c"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
	(if_then_else:FXVI
	 (unspec:CC [(reg:CC S2PP_COND_REGNO)
		(match_operand:SI 3 "u_short_cint_operand" "i")] UNSPEC_FXVCOND)
         (minus:FXVI (match_operand:FXVI 1 "register_operand" "kv")
		  (match_operand:FXVI 2 "register_operand" "kv"))
	 (match_dup 0)))]
  "<FXVI_unit>"
  "fxvsub<FXVI_char>m %0,%1,%2,%3"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvsub<FXVI_char>fs_c"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
	(if_then_else:FXVI
	 (unspec:CC [(reg:CC S2PP_COND_REGNO)
		(match_operand:SI 3 "u_short_cint_operand" "i")] UNSPEC_FXVCOND)
         (unspec:FXVI [(match_operand:FXVI 1 "register_operand" "kv")
		    (match_operand:FXVI 2 "register_operand" "kv")]
		   UNSPEC_FXVSUB)
	 (match_dup 0)))]
  "<FXVI_unit>"
  "fxvsub<FXVI_char>fs %0,%1,%2,%3"
  [(set_attr "type" "vecsimple")])

;; multiply
(define_insn "s2pp_fxvmul<FXVI_char>m"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
        (mult:FXVI (match_operand:FXVI 1 "register_operand" "kv")
		  (match_operand:FXVI 2 "register_operand" "kv")))]
  "<FXVI_unit>"
  "fxvmul<FXVI_char>m %0,%1,%2"
  [(set_attr "type" "vecsimple")])

;;(define_insn "s2pp_fxvmul<FXVI_char>fs"
;;  [(set (match_operand:FXVI 0 "register_operand" "=kv")
;;        (unspec:FXVI [(match_operand:FXVI 1 "register_operand" "kv")
;;		    (match_operand:FXVI 2 "register_operand" "kv")]
;;		   UNSPEC_FXVMUL))]
;;  "<FXVI_unit>"
;;  "fxvmul<FXVI_char>fs %0,%1,%2"
;;  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvmul<FXVI_char>m_c"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
	(if_then_else:FXVI
	 (unspec:CC [(reg:CC S2PP_COND_REGNO)
		(match_operand:SI 3 "u_short_cint_operand" "i")] UNSPEC_FXVCOND)
         (mult:FXVI (match_operand:FXVI 1 "register_operand" "kv")
		  (match_operand:FXVI 2 "register_operand" "kv"))
	 (match_dup 0)))]
  "<FXVI_unit>"
  "fxvmul<FXVI_char>m %0,%1,%2,%3"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvmul<FXVI_char>fs_c"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
	(if_then_else:FXVI
	 (unspec:CC [(reg:CC S2PP_COND_REGNO)
		(match_operand:SI 3 "u_short_cint_operand" "i")] UNSPEC_FXVCOND)
         (unspec:FXVI [(match_operand:FXVI 1 "register_operand" "kv")
		    (match_operand:FXVI 2 "register_operand" "kv")]
		   UNSPEC_FXVMUL)
	 (match_dup 0)))]
  "<FXVI_unit>"
  "fxvmul<FXVI_char>fs %0,%1,%2,%3"
  [(set_attr "type" "vecsimple")])

;; splat
(define_insn "s2pp_fxvsplat<FXVI_char>"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
	(unspec:FXVI
	     [(match_operand:SI 1 "register_operand" "r")]
	UNSPEC_FXVSPLAT))]
  "TARGET_S2PP"
  "#"
  [(set_attr "type" "vecperm")])

(define_split
  [(set (match_operand:FXVI 0 "register_operand" "")
	(unspec:FXVI
	     [(match_operand:SI 1 "register_operand" "")]
	UNSPEC_FXVSPLAT))]
  "TARGET_S2PP && reload_completed"
  [(set (match_operand:FXVI 0 "register_operand" "")
	(unspec:FXVI
	     [(match_operand:SI 1 "register_operand" "")]
	UNSPEC_FXVSPLAT_DIRECT))
  (unspec_volatile [(const_int 0)] UNSPEC_FXVSYNC)]
  "")

(define_insn "*s2pp_fxvsplat<FXVI_char>_direct"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
	(unspec:FXVI
	     [(match_operand:SI 1 "register_operand" "r")]
	UNSPEC_FXVSPLAT_DIRECT))]
  "TARGET_S2PP"
  "fxvsplat<FXVI_char> %0,%1"
  [(set_attr "type" "vecperm")])

;; select
;;(define_insn "*s2pp_fxvsel<mode>"
;;  [(set (match_operand:FXVI 0 "register_operand" "=kv")
;;	(if_then_else:FXVI
;;	 (unspec:CC [(reg:CC S2PP_COND_REGNO)
;;		(match_operand:QI 3 "u3bit_cint_operand" "i")] UNSPEC_FXVCOND)
;;	 (match_operand:FXVI 1 "register_operand" "kv")
;;	 (match_operand:FXVI 2 "register_operand" "kv")))]
;;  "VECTOR_MEM_S2PP_P (<MODE>mode)"
;;  "fxvsel %0,%1,%2,%3"
;;  [(set_attr "type" "vecperm")])

(define_insn "s2pp_fxvsel_c_<mode>"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
	(if_then_else:FXVI
	 (unspec:CC [(reg:CC S2PP_COND_REGNO)
		(match_operand:SI 3 "u_short_cint_operand" "i")] UNSPEC_FXVCOND)
	 (match_operand:FXVI 1 "register_operand" "kv")
	 (match_operand:FXVI 2 "register_operand" "kv")))]
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
		     (match_operand:SI 2 "u_short_cint_operand" "i")))]
  "<FXVI_unit>"
  "fxvsh<FXVI_char> %0,%1,%2"
  [(set_attr "type" "vecperm")])

;;compare
(define_insn "s2pp_fxvcmp<FXVI_char>"
  [(set (reg:CC S2PP_COND_REGNO)
        (eq:CC (match_operand:FXVI 0 "register_operand" "kv")
                    (const_int 0)))]
  "TARGET_S2PP"
  "fxvcmp<FXVI_char> %0"
  [(set_attr "type" "veccmp")])

;;accumulator insns
(define_insn "s2pp_fxvmtac<FXVI_char>" 
  [(set	(reg:FXVI S2PP_ACC_REGNO)
	(if_then_else:FXVI
		(unspec:CC [(reg:CC S2PP_COND_REGNO)
			    (match_operand:SI 1 "u_short_cint_operand" "i")]
		UNSPEC_FXVCOND)
		(unspec:FXVI [(match_operand:FXVI 0 "s2pp_register_operand" "kv")]
		UNSPEC_FXVMTAC)
		(reg:FXVI S2PP_ACC_REGNO)))]
  "TARGET_S2PP"
  "fxvmtac<FXVI_char> %0,%1"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvma<FXVI_char>m"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
	(if_then_else:FXVI
		(unspec:CC [(reg:CC S2PP_COND_REGNO)
			    (match_operand:SI 3 "u_short_cint_operand" "i")]
		UNSPEC_FXVCOND)
       		(plus:FXVI (reg:FXVI S2PP_ACC_REGNO)
        	   	   (mult:FXVI (match_operand:FXVI 1 "register_operand" "kv")
			   (match_operand:FXVI 2 "register_operand" "kv")))
		(match_dup 0)))]
  "TARGET_S2PP"
  "fxvma<FXVI_char>m %0,%1,%2,%3"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvmatac<FXVI_char>m"
  [(set (reg:FXVI S2PP_ACC_REGNO)
	(if_then_else:FXVI
		(unspec:CC [(reg:CC S2PP_COND_REGNO)
			    (match_operand:SI 2 "u_short_cint_operand" "i")]
		UNSPEC_FXVCOND)
       		(unspec:FXVI [(reg:FXVI S2PP_ACC_REGNO)
        	   	   (mult:FXVI (match_operand:FXVI 0 "register_operand" "kv")
			   	      (match_operand:FXVI 1 "register_operand" "kv"))]
		UNSPEC_FXVMATAC)
		(reg:FXVI S2PP_ACC_REGNO)))]
  "TARGET_S2PP"
  "fxvmatac<FXVI_char>m %0,%1,%2"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvmultac<FXVI_char>m"
  [(set (reg:FXVI S2PP_ACC_REGNO)
	(if_then_else:FXVI
		(unspec:CC [(reg:CC S2PP_COND_REGNO)
			    (match_operand:SI 2 "u_short_cint_operand" "i")]
		UNSPEC_FXVCOND)
        	(unspec:FXVI [(match_operand:FXVI 0 "register_operand" "kv")
		  	     (match_operand:FXVI 1 "register_operand" "kv")]
		UNSPEC_FXVMULTAC)
		(reg:FXVI S2PP_ACC_REGNO)))]
  "TARGET_S2PP"
  "fxvmultac<FXVI_char>m %0,%1,%2"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvaddactac<FXVI_char>m"
  [(set (reg:FXVI S2PP_ACC_REGNO)
	(if_then_else:FXVI
		(unspec:CC [(reg:CC S2PP_COND_REGNO)
			    (match_operand:SI 1 "u_short_cint_operand" "i")]
		UNSPEC_FXVCOND)
        	(unspec:FXVI [(match_operand:FXVI 0 "register_operand" "kv")
			     (reg:FXVI S2PP_ACC_REGNO)]
		UNSPEC_FXVADDACTAC)
		(reg:FXVI S2PP_ACC_REGNO)))]
  "TARGET_S2PP"
  "fxvaddactac<FXVI_char>m %0,%1"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvaddtac<FXVI_char>"
  [(set (reg:FXVI S2PP_ACC_REGNO)
	(if_then_else:FXVI
		(unspec:CC [(reg:CC S2PP_COND_REGNO)
			    (match_operand:SI 2 "u_short_cint_operand" "i")]
		UNSPEC_FXVCOND)
        	(unspec:FXVI [(match_operand:FXVI 0 "register_operand" "kv")
			     (match_operand:FXVI 1 "register_operand" "kv")]
		UNSPEC_FXVADDTAC)
		(reg:FXVI S2PP_ACC_REGNO)))]
  "TARGET_S2PP"
  "fxvaddtac<FXVI_char> %0,%1,%2"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvaddac<FXVI_char>m"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
	(if_then_else:FXVI
		(unspec:CC [(reg:CC S2PP_COND_REGNO)
			    (match_operand:SI 2 "u_short_cint_operand" "i")]
		UNSPEC_FXVCOND)
	        (unspec:FXVI [(match_operand:FXVI 1 "register_operand" "kv")
			     (reg:FXVI S2PP_ACC_REGNO)]
		UNSPEC_FXVADDAC)
		(match_dup 0)))]
  "TARGET_S2PP"
  "fxvaddac<FXVI_char>m %0,%1,%2"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvmtac<FXVI_char>f" 
  [(set	(reg:FXVI S2PP_ACC_REGNO)
	(if_then_else:FXVI
		(unspec:CC [(reg:CC S2PP_COND_REGNO)
			    (match_operand:SI 1 "u_short_cint_operand" "i")]
		UNSPEC_FXVCOND)
		(unspec:FXVI [(match_operand:FXVI 0 "s2pp_register_operand" "kv")]
		UNSPEC_FXVMTACF)
		(reg:FXVI S2PP_ACC_REGNO)))]
  "TARGET_S2PP"
  "fxvmtac<FXVI_char>f %0,%1"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvma<FXVI_char>fs"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
	(if_then_else:FXVI
		(unspec:CC [(reg:CC S2PP_COND_REGNO)
			    (match_operand:SI 3 "u_short_cint_operand" "i")]
		UNSPEC_FXVCOND)
       		(unspec:FXVI [(reg:FXVI S2PP_ACC_REGNO)
        	      	      (unspec:FXVI [(match_operand:FXVI 1 "register_operand" "kv")
			           	    (match_operand:FXVI 2 "register_operand" "kv")]
			      UNSPEC_FXVMUL)]
		UNSPEC_FXVADD)
		(match_dup 0)))]
  "TARGET_S2PP"
  "fxvma<FXVI_char>fs %0,%1,%2,%3"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvmatac<FXVI_char>fs"
  [(set (reg:FXVI S2PP_ACC_REGNO)
	(if_then_else:FXVI
		(unspec:CC [(reg:CC S2PP_COND_REGNO)
			    (match_operand:SI 2 "u_short_cint_operand" "i")]
		UNSPEC_FXVCOND)
       		(unspec:FXVI [(reg:FXVI S2PP_ACC_REGNO)
        		      (unspec:FXVI [(match_operand:FXVI 0 "register_operand" "kv")
				            (match_operand:FXVI 1 "register_operand" "kv")]
			      UNSPEC_FXVMUL)]
		UNSPEC_FXVMATAC)
		(reg:FXVI S2PP_ACC_REGNO)))]
  "TARGET_S2PP"
  "fxvmatac<FXVI_char>fs %0,%1,%2"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvmultac<FXVI_char>fs"
  [(set (reg:FXVI S2PP_ACC_REGNO)
	(if_then_else:FXVI
		(unspec:CC [(reg:CC S2PP_COND_REGNO)
			    (match_operand:SI 2 "u_short_cint_operand" "i")]
		UNSPEC_FXVCOND)
        	(unspec:FXVI [(match_operand:FXVI 0 "register_operand" "kv")
			      (match_operand:FXVI 1 "register_operand" "kv")]
		UNSPEC_FXVMULTACF)
		(reg:FXVI S2PP_ACC_REGNO)))]
  "TARGET_S2PP"
  "fxvmultac<FXVI_char>fs %0,%1,%2"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvaddactac<FXVI_char>f"
  [(set (reg:FXVI S2PP_ACC_REGNO)
	(if_then_else:FXVI
		(unspec:CC [(reg:CC S2PP_COND_REGNO)
			    (match_operand:SI 1 "u_short_cint_operand" "i")]
		UNSPEC_FXVCOND)
        	(unspec:FXVI [(match_operand:FXVI 0 "register_operand" "kv")
			      (reg:FXVI S2PP_ACC_REGNO)]
		UNSPEC_FXVADDACTACF)
		(reg:FXVI S2PP_ACC_REGNO)))]
  "TARGET_S2PP"
  "fxvaddactac<FXVI_char>f %0,%1"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvaddac<FXVI_char>fs"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
	(if_then_else:FXVI
		(unspec:CC [(reg:CC S2PP_COND_REGNO)
			    (match_operand:SI 2 "u_short_cint_operand" "i")]
		UNSPEC_FXVCOND)
        	(unspec:FXVI [(match_operand:FXVI 1 "register_operand" "kv")
			      (reg:FXVI S2PP_ACC_REGNO)]
		UNSPEC_FXVADDACF)
		(match_dup 0)))]
  "TARGET_S2PP"
  "fxvaddac<FXVI_char>fs %0,%1,%2"
  [(set_attr "type" "vecsimple")])

;; pack
(define_expand "s2pp_fxvpckbu"
  [(set (match_operand:V16QI 0 "register_operand" "=kv")
	(if_then_else:V16QI
		(unspec:CC [(reg:CC S2PP_COND_REGNO)
			    (match_operand:SI 3 "u_short_cint_operand" "i")]
		UNSPEC_FXVCOND)
		(unspec:V16QI [(match_operand:V8HI 1 "indexed_or_indirect_address" "a")
			       (match_operand:V8HI 2 "indexed_or_indirect_address" "a")]
		UNSPEC_FXVPCKU)
		(match_dup 0)))
  (unspec_volatile [(const_int 0)] UNSPEC_FXVSYNC)]
  "TARGET_S2PP"
  "")
 
(define_insn "*s2pp_fxvpckbu_internal"
  [(set (match_operand:V16QI 0 "register_operand" "=kv")
	(if_then_else:V16QI
		(unspec:CC [(reg:CC S2PP_COND_REGNO)
			    (match_operand:SI 3 "u_short_cint_operand" "i")]
		UNSPEC_FXVCOND)
		(unspec:V16QI [(match_operand:V8HI 1 "indexed_or_indirect_address" "a")
			       (match_operand:V8HI 2 "indexed_or_indirect_address" "a")]
		UNSPEC_FXVPCKU)
		(match_dup 0)))]
  "TARGET_S2PP"
  "fxvpckbu %0,%1,%2,%3"
  [(set_attr "type" "vecload")])

(define_expand "s2pp_fxvpckbl"
  [(set (match_operand:V16QI 0 "register_operand" "=kv")
	(if_then_else:V16QI
		(unspec:CC [(reg:CC S2PP_COND_REGNO)
			    (match_operand:SI 3 "u_short_cint_operand" "i")]
		UNSPEC_FXVCOND)
		(unspec:V16QI [(match_operand:V8HI 1 "indexed_or_indirect_address" "a")
			       (match_operand:V8HI 2 "indexed_or_indirect_address" "a")]
		UNSPEC_FXVPCKL)
		(match_dup 0)))
  (unspec_volatile [(const_int 0)] UNSPEC_FXVSYNC)]
  "TARGET_S2PP"
  "")
 
(define_insn "*s2pp_fxvpckbl_internal"
  [(set (match_operand:V16QI 0 "register_operand" "=kv")
	(if_then_else:V16QI
		(unspec:CC [(reg:CC S2PP_COND_REGNO)
			    (match_operand:SI 3 "u_short_cint_operand" "i")]
		UNSPEC_FXVCOND)
		(unspec:V16QI [(match_operand:V8HI 1 "indexed_or_indirect_address" "a")
			       (match_operand:V8HI 2 "indexed_or_indirect_address" "a")]
		UNSPEC_FXVPCKL)
		(match_dup 0)))]
  "TARGET_S2PP"
  "fxvpckbl %0,%1,%2,%3"
  [(set_attr "type" "vecload")])

;;unpack
(define_expand "s2pp_fxvupckbl"
   [(set (match_operand:V8HI 0 "s2pp_register_operand" "=kv")
	(if_then_else:V8HI
		(unspec:CC [(reg:CC S2PP_COND_REGNO)
			    (match_operand:SI 3 "u_short_cint_operand" "i")]
		UNSPEC_FXVCOND)
		(unspec:V8HI [(match_operand:V16QI 1 "indexed_or_indirect_address" "a")
		 	      (match_operand:V16QI 2 "indexed_or_indirect_address" "a")]
		UNSPEC_FXVUPCKL)
		(match_dup 0)))
  (unspec_volatile [(const_int 0)] UNSPEC_FXVSYNC)]
  "TARGET_S2PP"
  "")
 
(define_insn "*s2pp_fxvupckbl_internal"
  [(set (match_operand:V8HI 0 "s2pp_register_operand" "=kv")
	(if_then_else:V8HI
		(unspec:CC [(reg:CC S2PP_COND_REGNO)
			    (match_operand:SI 3 "u_short_cint_operand" "i")]
		UNSPEC_FXVCOND)
		(unspec:V8HI [(match_operand:V16QI 1 "indexed_or_indirect_address" "a")
		 	      (match_operand:V16QI 2 "indexed_or_indirect_address" "a")]
		UNSPEC_FXVUPCKL)
		(match_dup 0)))]
  "TARGET_S2PP"
  "fxvupckbl %0,%1,%2,%3"
  [(set_attr "type" "vecload")])

(define_expand "s2pp_fxvupckbr"
   [(set (match_operand:V8HI 0 "s2pp_register_operand" "=kv")
	(if_then_else:V8HI
		(unspec:CC [(reg:CC S2PP_COND_REGNO)
			    (match_operand:SI 3 "u_short_cint_operand" "i")]
		UNSPEC_FXVCOND)
		(unspec:V8HI [(match_operand:V16QI 1 "indexed_or_indirect_address" "a")
		 	      (match_operand:V16QI 2 "indexed_or_indirect_address" "a")]
		UNSPEC_FXVUPCKR)
		(match_dup 0)))
  (unspec_volatile [(const_int 0)] UNSPEC_FXVSYNC)]
  "TARGET_S2PP"
  "")
 
(define_insn "*s2pp_fxvupckbr_internal"
  [(set (match_operand:V8HI 0 "s2pp_register_operand" "=kv")
	(if_then_else:V8HI
		(unspec:CC [(reg:CC S2PP_COND_REGNO)
			    (match_operand:SI 3 "u_short_cint_operand" "i")]
		UNSPEC_FXVCOND)
		(unspec:V8HI [(match_operand:V16QI 1 "indexed_or_indirect_address" "a")
		 	      (match_operand:V16QI 2 "indexed_or_indirect_address" "a")]
		UNSPEC_FXVUPCKR)
		(match_dup 0)))]
  "TARGET_S2PP"
  "fxvupckbr %0,%1,%2,%3"
  [(set_attr "type" "vecload")])
