;;s2pp machine description file

(define_c_enum "unspec"
  [UNSPEC_STAX
   UNSPEC_LAX
   UNSPEC_FXVSPLT_DIRECT
])  

;; Vec int modes
(define_mode_iterator FXVI [V8HI V16QI])

;; Vec attributes
(define_mode_attr FXVI_char [(V8HI "h") (V16QI "b")])

(define_mode_attr FXVI_unit [(V16QI "VECTOR_UNIT_S2PP_P (V16QImode)")
			   (V8HI "VECTOR_UNIT_S2PP_P (V8HImode)")])

;; Vector move instructions.
(define_insn "*s2pp_mov<mode>"
  [(set (match_operand:FXVI 0 "nonimmediate_operand" "=Z,k,k")
	(match_operand:FXVI 1 "input_operand" "k,Z,k"))]
  "VECTOR_MEM_S2PP_P (<MODE>mode)
   && (register_operand (operands[0], <MODE>mode) 
       || register_operand (operands[1], <MODE>mode))"
{
  switch (which_alternative)
    {
    case 0: return "fxvstax %1,0,%a0";
    case 1: return "fxvlax %0,0,%a1";
    case 2: return "fxvsel %0,%1,%1,1";
    default: gcc_unreachable ();
    }
}
  [(set_attr "type" "vecstore,vecload,vecsimple,*")])


(define_expand "s2pp_stax_<mode>"
  [(parallel
    [(set (match_operand:FXVI 0 "memory_operand" "=Z")
	  (match_operand:FXVI 1 "register_operand" "k"))
    (unspec [(const_int 0)] UNSPEC_STAX)])]
  "TARGET_S2PP"
{
})

(define_insn "*s2pp_stax_<mode>_internal"
  [(parallel
    [(set (match_operand:FXVI 0 "memory_operand" "=Z")
	  (match_operand:FXVI 1 "register_operand" "k"))
     (unspec [(const_int 0)] UNSPEC_STAX)])]
  "TARGET_S2PP"
  "fxvstax %1,0,%y0"
  [(set_attr "type" "vecstore")])

;;(define_insn "s2pp_stax_<mode>"
;;  [(parallel
;;    [(set (match_operand:FXVI 0 "memory_operand" "=Z")
;;	  (match_operand:FXVI 1 "register_operand" "k"))
;;     (unspec [(const_int 0)] UNSPEC_STAX)])]
;;  "TARGET_S2PP"
;;  "fxvstax %1,0,%a0"
;;  [(set_attr "type" "vecstore")])

(define_expand "s2pp_lax_<mode>"
  [(parallel
    [(set (match_operand:FXVI 0 "register_operand" "=k")
	  (match_operand:FXVI 1 "memory_operand" "Z"))
     (unspec [(const_int 0)] UNSPEC_LAX)])]
  "TARGET_S2PP"
{
})

(define_insn "*s2pp_lax_<mode>_internal"
  [(parallel
    [(set (match_operand:FXVI 0 "register_operand" "=k")
	  (match_operand:FXVI 1 "memory_operand" "Z"))
     (unspec [(const_int 0)] UNSPEC_LAX)])]
  "TARGET_S2PP"
  "fxvlax %0,0,%y1"
  [(set_attr "type" "vecload")])



(define_insn "s2pp_fxvlax_direct"
  [(set (match_operand:V16QI 0 "register_operand" "=k")
	(unspec:V16QI [(match_operand:V16QI 1 "memory_operand" "Z")]
                      UNSPEC_LAX))]
  "TARGET_S2PP"
  "fxvlax %0,0,%a1"
  [(set_attr "type" "vecload")])

;; add
(define_insn "fxvadd<mode>3"
  [(set (match_operand:FXVI 0 "register_operand" "=k")
        (plus:FXVI (match_operand:FXVI 1 "register_operand" "k")
		  (match_operand:FXVI 2 "register_operand" "k")))]
  "<FXVI_unit>"
  "fxvadd<FXVI_char>m %0,%1,%2"
  [(set_attr "type" "vecsimple")])


(define_insn "s2pp_fxvsplat<FXVI_char>"
  [(set (match_operand:FXVI 0 "register_operand" "=k")
	(vec_duplicate:FXVI
	 (match_operand:QI 1 "s5bit_cint_operand" "i")))]
  "TARGET_S2PP"
  "fxvsplat<FXVI_char> %0,%1"
  [(set_attr "type" "vecperm")])

;;(define_expand "s2pp_splatb"
;;  [(use (match_operand:V16QI 0 "register_operand" ""))
;;   (use (match_operand:QI 1 "u5bit_cint_operand" ""))]
;;  "TARGET_S2PP"
;;{
;;  rtvec v;
;;  rtx x;
;;
;;  v = gen_rtvec (1, operands[1]);
;;  x = gen_rtx_VEC_SELECT (QImode, operands[0], gen_rtx_PARALLEL (VOIDmode, v));
;;  x = gen_rtx_VEC_DUPLICATE (V16QImode, x);
;;  emit_insn (gen_rtx_SET (VOIDmode, operands[0], x));
;;  DONE;
;;})

;;(define_insn "*s2pp_splatb_internal"
;;  [(set (match_operand:V16QI 0 "register_operand" "=k")
;;        (unspec:V16QI [(match_operand:QI 1 "u5bit_cint_operand" "")]))]
;;  "TARGET_S2PP"
;;{
;;  return "fxvsplatb %0,%1";
;;}
;;  [(set_attr "type" "vecperm")])

;;(define_insn "s2pp_fxvsplatb_direct"
;;  [(set (match_operand:V16QI 0 "register_operand" "=k")
;;        (unspec:V16QI [(match_operand:QI 1 "u5bit_cint_operand" "i")]
;;                      UNSPEC_FXVSPLT_DIRECT))]
;;  "TARGET_S2PP"
;;  "fxvsplatb %0,%1"
;;  [(set_attr "type" "vecperm")])

;;(define_expand "s2pp_splath"
;;  [(use (match_operand:V8HI 0 "register_operand" ""))
;;   (use (match_operand:QI 1 "u5bit_cint_operand" ""))]
;;  "TARGET_S2PP"
;;{
;;  rtvec v;
;;  rtx x;
;;
;;  v = gen_rtvec (1, operands[1]);
;;  x = gen_rtx_VEC_SELECT (HImode, operands[0], gen_rtx_PARALLEL (VOIDmode, v));
;;  x = gen_rtx_VEC_DUPLICATE (V8HImode, x);
;;  emit_insn (gen_rtx_SET (VOIDmode, operands[0], x));
;;  DONE;
;;})

;;(define_insn "*s2pp_splath_internal"
;;  [(set (match_operand:V8HI 0 "register_operand" "=k")
;;	 (unspec:V8HI [(match_operand:QI 1 "u5bit_cint_operand" "")]))]
;;  "TARGET_S2PP"
;;{
;;  return "fxvsplath %0,%1,%2";
;;}
;;  [(set_attr "type" "vecperm")])

;;(define_insn "s2pp_splath_direct"
;;  [(set (match_operand:V8HI 0 "register_operand" "=k")
;;        (unspec:V8HI [(match_operand:QI 1 "u5bit_cint_operand" "i")]
;;                     UNSPEC_FXVSPLT_DIRECT))]
;;  "TARGET_S2PP"
;;  "fxvsplath %0,%1"
;;  [(set_attr "type" "vecperm")])

