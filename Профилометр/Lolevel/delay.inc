;----------------------------------------------------------------------------
; Задержки
;----------------------------------------------------------------------------
delay_107:      nop             ;4
delay_103:      nop             ;4
delay_99:       nop             ;4
delay_95:       nop             ;4
delay_91:       nop             ;4
delay_87:       nop             ;4
delay_83:       nop             ;4
delay_79:       nop             ;4
delay_75:       nop             ;4
delay_71:       nop             ;4
delay_67:       nop             ;4
delay_63:       nop             ;4
delay_59:       nop             ;4
delay_55:       nop             ;4
delay_51:       nop             ;4
delay_47:       nop             ;4
delay_43:       nop             ;4
delay_39:       nop             ;4
delay_35:       nop             ;4
delay_31:       nop             ;4
delay_27:       ret             ;10 +17(call)

delay_60        push af         ;11 + 17(call) = 28
                pop af          ;10 ;;38
                nop             ;42
                nop             ;46
                nop             ;50
                ret             ;60

delay_100       push af         ;11 + 17(call) = 28
                pop af          ;10 ;;38
                nop             ;42
                nop             ;46
                nop             ;50

                nop             ;4
                nop             ;4
                nop             ;4
                nop             ;4
                nop             ;4

                nop             ;4
                nop             ;4
                nop             ;4
                nop             ;4
                nop             ;4

                ret             ;100

delay_1000      push bc         ;11
                ld bc,72        ;7
loop_1000:      djnz loop_1000  ;+8-13
                pop bc          ;10
                ret             ;10;;63

;----------------------------------------------------------------------------
; 4800 - 833,3
; 9600 - 416,6
; 12200 - 327,8
; 14400 - 277,7
; 19200 - 208,3
;----------------------------------------------------------------------------
