;;s2pp machine description file

(define_c_enum "unspec"
  [UNSPEC_FXVSTAX
   UNSPEC_FXVLAX
   UNSPEC_FXVOUTX
   UNSPEC_FXVINX
   UNSPEC_FXVSPLT_DIRECT
   UNSPEC_FXVADD
   UNSPEC_FXVSUB
   UNSPEC_FXVMUL
   UNSPEC_FXVMTAC
   UNSPEC_FXVMTACF
   UNSPEC_FXVPCKU
   UNSPEC_FXVPCKL
   UNSPEC_FXVUPCKL
   UNSPEC_FXVUPCKR
])  

;; Vec int modes
(define_mode_iterator FXVI [V8HI V16QI])

;; Vec attributes
(define_mode_attr FXVI_char [(V8HI "h") (V16QI "b")])

(define_mode_attr FXVI_unit [(V8HI "VECTOR_UNIT_S2PP_P (V8HImode)")
			   (V16QI "VECTOR_UNIT_S2PP_P (V16QImode)")])

;; Vector move instructions.
;; last zero constant is set automatically
;;(define_insn "*s2pp_mov<mode>"
;;  [(set (match_operand:FXVI 0 "nonimmediate_operand" "=Z,kv,kv,*Y,*r,*r,kv,kv")
;;	(match_operand:FXVI 1 "input_operand" "kv,Z,kv,r,Y,r,j,W"))]
;;  "VECTOR_MEM_S2PP_P (<MODE>mode)
;;   && (register_operand (operands[0], <MODE>mode) 
;;       || register_operand (operands[1], <MODE>mode))"
;;{
;;  switch (which_alternative)
;;    {
;;    case 0: return "fxvstax %1,%y0";
;;    case 1: return "fxvlax %0,%y1";
;;    case 2: return "fxvsel %0,%1,%1,0";
;;    case 3: return "#";
;;    case 4: return "#";
;;    case 5: return "#";
;;    case 6: return "fxvsel %0,0,0,0";
;;    case 7: return output_vec_const_move (operands);
;;    default: gcc_unreachable ();
;;    }
;;}
;;  [(set_attr "type" "vecstore,vecload,vecsimple,store,load,*,vecsimple,*")])

(define_insn "*s2pp_mov<mode>"
  [(set (match_operand:FXVI 0 "nonimmediate_operand" "=Z,kv,kv,*Y,*r,*r,kv")
	(match_operand:FXVI 1 "input_operand" "kv,Z,kv,r,Y,r,j"))]
  "VECTOR_MEM_S2PP_P (<MODE>mode)
   && (register_operand (operands[0], <MODE>mode) 
       || register_operand (operands[1], <MODE>mode))"
{
  switch (which_alternative)
    {
    case 0: return "fxvstax %1,%y0";
    case 1: return "fxvlax %0,%y1";
    case 2: return "fxvsel %0,%1,%1,0";
    case 3: return "#";
    case 4: return "#";
    case 5: return "#";
    case 6: return "fxvsel %0,0,0,0";
    default: gcc_unreachable ();
    }
}
  [(set_attr "type" "vecstore,vecload,vecsimple,store,load,*,*")])
;; 0 at the end of case 2 in order to return true -> similar to vor(x,x)
;; alternatively use 3
;; 1 at the end  of case 6 for gt comp -> similar to xor(1,1)
;; alternatively use 2

;;(define_split
;;  [(set (match_operand:FXVI 0 "s2pp_register_operand" "")
;;	(match_operand:FXVI 1 "input_operand" ""))]
;;  ""
;;  [(set (match_dup 2) (match_dup 1)) 
;;   (set (match_dup 0) (vec_duplicate:FXVI (match_dup 2)))]
;;{
;;  rtx dup = gen_easy_s2pp_constant (operands[1]);
;;  rtx const_vec;
;;  enum machine_mode op_mode = <MODE>mode;
;;  const_vec = simplify_rtx (dup);
;;  operands[3] = const_vec;
;;  operands[4] = gen_rtx_PLUS (op_mode, operands[0], operands[0]);
;;}) 




(define_expand "s2pp_fxvstax_<mode>"
  [(parallel
    [(set (match_operand:FXVI 0 "memory_operand" "=Z")
	  (match_operand:FXVI 1 "register_operand" "kv"))
    (unspec [(const_int 0)] UNSPEC_FXVSTAX)])]
  "TARGET_S2PP"
{
})

(define_insn "*s2pp_fxvstax_<mode>_internal"
  [(parallel
    [(set (match_operand:FXVI 0 "memory_operand" "=Z")
	  (match_operand:FXVI 1 "register_operand" "kv"))
     (unspec [(const_int 0)] UNSPEC_FXVSTAX)])]
  "TARGET_S2PP"
  "fxvstax %1,%y0,0"
  [(set_attr "type" "vecstore")])

(define_expand "s2pp_fxvlax_<mode>"
  [(parallel
    [(set (match_operand:FXVI 0 "register_operand" "=kv")
	  (match_operand:FXVI 1 "memory_operand" "Z"))
     (unspec [(const_int 0)] UNSPEC_FXVLAX)])]
  "TARGET_S2PP"
{
})

(define_insn "*s2pp_fxvlax_<mode>_internal"
  [(parallel
    [(set (match_operand:FXVI 0 "register_operand" "=kv")
	  (match_operand:FXVI 1 "memory_operand" "Z"))
     (unspec [(const_int 0)] UNSPEC_FXVLAX)])]
  "TARGET_S2PP"
  "fxvlax %0,%y1,0"
  [(set_attr "type" "vecload")])

(define_insn "s2pp_fxvlax_direct"
  [(set (match_operand:V16QI 0 "register_operand" "=kv")
	(unspec:V16QI [(match_operand:V16QI 1 "memory_operand" "Z")]
                      UNSPEC_FXVLAX))]
  "TARGET_S2PP"
  "fxvlax %0,%y1,0"
  [(set_attr "type" "vecload")])

;;synram
(define_expand "s2pp_fxvoutx_<mode>"
  [(parallel
    [(set (match_operand:FXVI 0 "memory_operand" "=Z")
	  (match_operand:FXVI 1 "register_operand" "kv"))
    (unspec [(const_int 0)] UNSPEC_FXVOUTX)])]
  "TARGET_S2PP"
{
})

(define_insn "*s2pp_fxvoutx_<mode>_internal"
  [(parallel
    [(set (match_operand:FXVI 0 "memory_operand" "=Z")
	  (match_operand:FXVI 1 "register_operand" "kv"))
     (unspec [(const_int 0)] UNSPEC_FXVOUTX)])]
  "TARGET_S2PP"
  "fxvoutx %1,%y0"
  [(set_attr "type" "vecstore")])

(define_expand "s2pp_fxvinx_<mode>"
  [(parallel
    [(set (match_operand:FXVI 0 "register_operand" "=kv")
	  (match_operand:FXVI 1 "memory_operand" "Z"))
     (unspec [(const_int 0)] UNSPEC_FXVINX)])]
  "TARGET_S2PP"
{
})

(define_insn "*s2pp_fxvinx_<mode>_internal"
  [(parallel
    [(set (match_operand:FXVI 0 "register_operand" "=kv")
	  (match_operand:FXVI 1 "memory_operand" "Z"))
     (unspec [(const_int 0)] UNSPEC_FXVINX)])]
  "TARGET_S2PP"
  "fxvlax %0,%y1"
  [(set_attr "type" "vecload")])


;; add
(define_insn "fxvadd<mode>3"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
        (plus:FXVI (match_operand:FXVI 1 "register_operand" "kv")
		  (match_operand:FXVI 2 "register_operand" "kv")))]
  "<FXVI_unit>"
  "fxvadd<FXVI_char>m %0,%1,%2,0"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvadd<FXVI_char>fs"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
        (unspec:FXVI [(match_operand:FXVI 1 "register_operand" "kv")
		    (match_operand:FXVI 2 "register_operand" "kv")]
		   UNSPEC_FXVADD))]
  "<FXVI_unit>"
  "fxvadd<FXVI_char>fs %0,%1,%2,0"
  [(set_attr "type" "vecsimple")])

;; sub
(define_insn "fxvsub<mode>3"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
        (minus:FXVI (match_operand:FXVI 1 "register_operand" "kv")
		   (match_operand:FXVI 2 "register_operand" "kv")))]
  "<FXVI_unit>"
  "fxvsub<FXVI_char>m %0,%1,%2"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvsub<FXVI_char>fs"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
        (unspec:FXVI [(match_operand:FXVI 1 "register_operand" "kv")
                    (match_operand:FXVI 2 "register_operand" "kv")]
		   UNSPEC_FXVSUB))]
  "VECTOR_UNIT_S2PP_P (<MODE>mode)"
  "fxvsub<FXVI_char>fs %0,%1,%2"
  [(set_attr "type" "vecsimple")])

;; multiply
(define_insn "s2pp_fxvmul<FXVI_char>m"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
        (mult:FXVI (match_operand:FXVI 1 "register_operand" "kv")
		  (match_operand:FXVI 2 "register_operand" "kv")))]
  "<FXVI_unit>"
  "fxvmul<FXVI_char>m %0,%1,%2"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvmul<FXVI_char>fs"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
        (unspec:FXVI [(match_operand:FXVI 1 "register_operand" "kv")
		    (match_operand:FXVI 2 "register_operand" "kv")]
		   UNSPEC_FXVMUL))]
  "<FXVI_unit>"
  "fxvmul<FXVI_char>fs %0,%1,%2"
  [(set_attr "type" "vecsimple")])

;; splat
(define_insn "s2pp_fxvsplat<FXVI_char>"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
	(vec_duplicate:FXVI
	     (match_operand:SI 1 "register_operand" "r")))]
  "TARGET_S2PP"
  "fxvsplat<FXVI_char> %0,%1"
  [(set_attr "type" "vecperm")])

;; select
(define_insn "*s2pp_fxvsel<mode>"
  [(set (match_operand:FXVI 0 "s2pp_register_operand" "=kv")
	(if_then_else:FXVI
	 (ne:CC (reg:CC S2PP_COND_REGNO)
		(match_operand:QI 3 "u3bit_cint_operand" "i"))
	 (match_operand:FXVI 1 "s2pp_register_operand" "kv")
	 (match_operand:FXVI 2 "s2pp_register_operand" "kv")))]
  "VECTOR_MEM_S2PP_P (<MODE>mode)"
  "fxvsel %0,%1,%2,%c3"
  [(set_attr "type" "vecperm")])

(define_insn "s2pp_fxvsel<mode>"
  [(set (match_operand:FXVI 0 "s2pp_register_operand" "=kv")
	(if_then_else:FXVI
	 (eq:CC (reg:CC S2PP_COND_REGNO)
		(match_operand:QI 3 "u3bit_cint_operand" "i"))
	 (match_operand:FXVI 1 "s2pp_register_operand" "kv")
	 (match_operand:FXVI 2 "s2pp_register_operand" "kv")))]
  "VECTOR_MEM_S2PP_P (<MODE>mode)"
  "fxvsel %0,%1,%2,%c3"
  [(set_attr "type" "vecperm")])

;;(define_insn "*s2pp_fxvsel<mode>_uns"
;;  [(set (match_operand:FXVI 0 "s2pp_register_operand" "=kv")
;;	(if_then_else:FXVI
;;	 (eq:CC (reg:CC S2PP_COND_REGNO)
;;		(match_operand:QI 1 "u3bit_cint_operand" "i"))
;;	 (match_operand:FXVI 2 "s2pp_register_operand" "kv")
;;	 (match_operand:FXVI 3 "s2pp_register_operand" "kv")))]
;;  "VECTOR_MEM_S2PP_P (<MODE>mode)"
;;  "fxvsel %0,%3,%2,%1"
;;  [(set_attr "type" "vecperm")])

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
  [(parallel
    [(set (reg:FXVI S2PP_ACC_REGNO)
          (unspec:FXVI [(match_operand:FXVI 0 "s2pp_register_operand" "kv")]
		UNSPEC_FXVMTAC))
     (use (reg:CC S2PP_COND_REGNO))])]
  "TARGET_S2PP"
  "fxvmtac<FXVI_char> %0"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvma<FXVI_char>m"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
       	(plus:FXVI (reg:FXVI S2PP_ACC_REGNO)
        	   (mult:FXVI (match_operand:FXVI 1 "register_operand" "kv")
			     (match_operand:FXVI 2 "register_operand" "kv"))))]
  "TARGET_S2PP"
  "fxvma<FXVI_char>m %0,%1,%2,0"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvmatac<FXVI_char>m"
  [(set (reg:FXVI S2PP_ACC_REGNO)
       	(plus:FXVI (reg:FXVI S2PP_ACC_REGNO)
        	   (mult:FXVI (match_operand:FXVI 0 "register_operand" "kv")
			     (match_operand:FXVI 1 "register_operand" "kv"))))]
  "TARGET_S2PP"
  "fxvmatac<FXVI_char>m %0,%1,0"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvmultac<FXVI_char>m"
  [(set (reg:FXVI S2PP_ACC_REGNO)
        (mult:FXVI (match_operand:FXVI 0 "register_operand" "kv")
		  (match_operand:FXVI 1 "register_operand" "kv")))]
  "TARGET_S2PP"
  "fxvmultac<FXVI_char>m %0,%1,0"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvaddactac<FXVI_char>m"
  [(set (reg:FXVI S2PP_ACC_REGNO)
        (plus:FXVI (match_operand:FXVI 0 "register_operand" "kv")
		  (reg:FXVI S2PP_ACC_REGNO)))]
  "TARGET_S2PP"
  "fxvaddactac<FXVI_char>m %0,0"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvaddtac<FXVI_char>"
  [(set (reg:FXVI S2PP_ACC_REGNO)
        (plus:FXVI (match_operand:FXVI 0 "register_operand" "kv")
		  (match_operand:FXVI 1 "register_operand" "kv")))]
  "TARGET_S2PP"
  "fxvaddtac<FXVI_char> %0,%1,0"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvaddac<FXVI_char>m"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
        (plus:FXVI (match_operand:FXVI 1 "register_operand" "kv")
		  (reg:FXVI S2PP_ACC_REGNO)))]
  "TARGET_S2PP"
  "fxvaddac<FXVI_char>m %0,%1,0"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvmtac<FXVI_char>f" 
  [(parallel
    [(set (reg:FXVI S2PP_ACC_REGNO)
          (unspec:FXVI [(match_operand:FXVI 0 "s2pp_register_operand" "kv")]
		UNSPEC_FXVMTACF))
     (use (reg:CC S2PP_COND_REGNO))])]
  "TARGET_S2PP"
  "fxvmtac<FXVI_char>f %0"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvma<FXVI_char>fs"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
       	(unspec:FXVI [(reg:FXVI S2PP_ACC_REGNO)
        	      (unspec:FXVI [(match_operand:FXVI 1 "register_operand" "kv")
			            (match_operand:FXVI 2 "register_operand" "kv")]
				     UNSPEC_FXVMUL)]
		       UNSPEC_FXVADD))]
  "TARGET_S2PP"
  "fxvma<FXVI_char>fs %0,%1,%2,0"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvmatac<FXVI_char>fs"
  [(set (reg:FXVI S2PP_ACC_REGNO)
       	(unspec:FXVI [(reg:FXVI S2PP_ACC_REGNO)
        	      (unspec:FXVI [(match_operand:FXVI 0 "register_operand" "kv")
			            (match_operand:FXVI 1 "register_operand" "kv")]
				     UNSPEC_FXVMUL)]
		       UNSPEC_FXVADD))]
  "TARGET_S2PP"
  "fxvmatac<FXVI_char>fs %0,%1,0"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvmultac<FXVI_char>fs"
  [(set (reg:FXVI S2PP_ACC_REGNO)
        (unspec:FXVI [(match_operand:FXVI 0 "register_operand" "kv")
		      (match_operand:FXVI 1 "register_operand" "kv")]
			UNSPEC_FXVMUL))]
  "TARGET_S2PP"
  "fxvmultac<FXVI_char>fs %0,%1,0"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvaddactac<FXVI_char>f"
  [(set (reg:FXVI S2PP_ACC_REGNO)
        (unspec:FXVI [(match_operand:FXVI 0 "register_operand" "kv")
		      (reg:FXVI S2PP_ACC_REGNO)]
			UNSPEC_FXVADD))]
  "TARGET_S2PP"
  "fxvaddactac<FXVI_char>f %0,0"
  [(set_attr "type" "vecsimple")])

(define_insn "s2pp_fxvaddac<FXVI_char>fs"
  [(set (match_operand:FXVI 0 "register_operand" "=kv")
        (unspec:FXVI [(match_operand:FXVI 1 "register_operand" "kv")
		      (reg:FXVI S2PP_ACC_REGNO)]
			UNSPEC_FXVADD))]
  "TARGET_S2PP"
  "fxvaddac<FXVI_char>fs %0,%1,0"
  [(set_attr "type" "vecsimple")])


(define_insn "s2pp_fxvmtac<FXVI_char>_c" 
  [(set (reg:FXVI S2PP_ACC_REGNO)
	(if_then_else:FXVI
	 (eq:CC (reg:CC S2PP_COND_REGNO)
		(match_operand:QI 1 "u3bit_cint_operand" "i"))
        (unspec:FXVI [(match_operand:FXVI 0 "s2pp_register_operand" "kv")]
		UNSPEC_FXVMTAC)
	(reg:FXVI S2PP_ACC_REGNO)))]
  "TARGET_S2PP"
  "fxvmtac<FXVI_char> %0"
  [(set_attr "type" "vecsimple")])

;; pack
(define_insn "s2pp_fxvpckbu"
  [(set (match_operand:V16QI 0 "register_operand" "=kv")
	(unspec:V16QI [(match_operand:V8HI 1 "memory_operand" "a")
		      (match_operand:V8HI 2 "memory_operand" "a")]
			   UNSPEC_FXVPCKU))]
  "TARGET_S2PP"
  "fxvpckbu %0,%1,%2"
  [(set_attr "type" "vecperm")])

(define_insn "s2pp_fxvpckbl"
  [(set (match_operand:V16QI 0 "register_operand" "=kv")
	(unspec:V16QI [(match_operand:V8HI 1 "memory_operand" "a")
		      (match_operand:V8HI 2 "memory_operand" "a")]
			   UNSPEC_FXVPCKL))]
  "TARGET_S2PP"
  "fxvpckbl %0,%1,%2"
  [(set_attr "type" "vecperm")])

;;unpack
(define_insn "s2pp_fxvupckbl"
  [(set (match_operand:V8HI 0 "memory_operand" "=Z")
	(unspec:V8HI [(match_operand:V16QI 1 "register_operand" "kv")
	 	     (match_operand:V16QI 2 "register_operand" "kv")]
		     UNSPEC_FXVUPCKL))]
  "TARGET_S2PP"
  "fxvupckbl %0,%1,%2"
  [(set_attr "type" "vecperm")])

(define_insn "s2pp_fxvupckbr"
  [(set (match_operand:V8HI 0 "memory_operand" "=m")
	(unspec:V8HI [(match_operand:V16QI 1 "register_operand" "kv")
	 	     (match_operand:V16QI 2 "register_operand" "kv")]
		     UNSPEC_FXVUPCKR))]
  "TARGET_S2PP"
  "fxvupckbr %0,%1,%2"
  [(set_attr "type" "vecperm")])

