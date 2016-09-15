;;s2pp machine description file

(define_c_enum "unspec"
  [UNSPEC_STAX
   UNSEPC_VADDU
])  

;; Vec int modes
(define_mode_iterator FXVI [V8HI V16QI])

;; Vec attributes
(define_mode_attr FXVI_char [(V8HI "h") (V16QI "b")])

(define_mode_attr FXVI_unit [(V16QI "VECTOR_UNIT_S2PP_P (V16QImode)")
			   (V8HI "VECTOR_UNIT_S2PP_P (V8HImode)")])

;; Vector move instructions.
;;(define_insn "*s2pp_mov<mode>"
 ;; [(set (match_operand:FXVI 0 "nonimmediate_operand" "=Z,v,v")
	;;(match_operand:FXVI 1 "input_operand" "v,Z,v"))]
 ;; "VECTOR_MEM_S2PP_P (<MODE>mode)
 ;;  && (register_operand (operands[0], <MODE>mode) 
 ;;      || register_operand (operands[1], <MODE>mode))"
;;{
 ;; switch (which_alternative)
 ;;   {
 ;;   case 0: return "fxvstax %1,%a0";
 ;;   case 1: return "fxvlax %0,%a1";
 ;;   case 2: return "fxvsel %0,%1,%1,1";
 ;;   default: gcc_unreachable ();
 ;;   }
;;}
 ;; [(set_attr "type" "vecstore,vecload,vecsimple,*")])

(define_insn "s2pp_stax_<mode>"
  [(parallel
    [(set (match_operand:FXVI 0 "memory_operand" "=Z")
	  (match_operand:FXVI 1 "register_operand" "v"))
     (unspec [(const_int 0)] UNSPEC_STAX)])]
  "TARGET_S2PP"
  "fxvstax %1,%a0"
  [(set_attr "type" "vecstore")])

;; add
(define_insn "fxvadd<mode>3"
  [(set (match_operand:FXVI 0 "register_operand" "=v")
        (plus:FXVI (match_operand:FXVI 1 "register_operand" "v")
		  (match_operand:FXVI 2 "register_operand" "v")))]
  "<FXVI_unit>"
  "fxvadd<FXVI_char>m %0,%1,%2"
  [(set_attr "type" "vecsimple")])
