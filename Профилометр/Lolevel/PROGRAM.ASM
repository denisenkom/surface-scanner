;----------------------------------------------------------------------------
stack_ptr	.equ 2100h
ram		.equ 2000h
; variables
acp_Lbyte	.equ ram
acp_Hbyte	.equ ram+1



		.org 0h 			;Общий старт с 0000h
		ld sp,stack_ptr 		; указатель стека
		
		ld a,10011001b	; init U6 mode 0, PA in, PB out, PC in
		out (011h),a	;
		
		ld a,10001001b	; init U7 mode 0, PA out, PB out, PC in
		out (111b),a	;

main:		; main loop
		call recv_data	; receive byte to accumulator

		cp 0
		jp z, req_acp	; acp request

		cp 1
		jp z, req_motor_rstep

		cp 2
		jp z, req_motor_lstep

		cp 3
		jp z, req_set_digital_output

		cp 4
		jp z, req_get_digital_input

		jp main

; Requests
req_acp:
		call acp_com
		ld a,(acp_LByte)
		call transmit_data
		ld a,(acp_HByte)
		call transmit_data
		jp main

req_motor_rstep:
		call motor_rstep
		jp main

req_motor_lstep:
		call motor_lstep
		jp main

req_set_digital_output:
		call recv_data
		out (0100b),a	; to chanel PA of U7
		jp main

req_get_digital_input:
		ld a,1000b  ; set strob
		out (0101),a  ; to chanel PB of U7
		call delay_strob

		ld c,6
read_register:	; sending data in reverse order
		ld a,c	; clear strob and select register #c
		out (0101),a  ; to chanel PB of U7
		in (0110),a   ; read register 1
		call transmit_data

		dec c

		jp nz, read_register

		jp main

delay_strob:
		ret

;----------------------------------------------------------------------------
;Процедура выполнения одного шага двигателя влево
;----------------------------------------------------------------------------

motor_lstep:	in a,(01h)
		or 00001000b
		out (01h),a
		call delay_step
		and 11110111b
		out (01h),a
		call delay_step
		ret
;----------------------------------------------------------------------------
;Процедура выполнения одного шага двигателя вправо
;----------------------------------------------------------------------------
motor_rstep:	in a,(01h)
		or 00000100b
		out (01h),a
		call delay_step
		and 11111011b
		out (01h),a
		call delay_step
		ret
;----------------------------------------------------------------------------
delay_step:
		ret

;----------------------------------------------------------------------------
;Процедура АЦП
;----------------------------------------------------------------------------
acp_com:	in a,(01h)
		and 11111110b
		out (01h),a

		ld b,58

cont_acp:	in a,(01h)
		xor 00000010b
		out (01h),a

		ld c,1
rep_con:	in a,(02h)
		and 00010000b
		jp nz, end_acp
		dec c
		jp nz, rep_con

		djnz cont_acp

		ld a,00h
;		ld (acp_Lbyte),a
;		ld (acp_Hbyte),a
		ld d,0
		ld e,0
		in a,(01h)
		or 00000011b
		out (01h),a
		ret

end_acp:	in a,(00h)
		ld (acp_Lbyte),a
		ld e,a
		in a,(02h)
		and 00001111b
		ld (acp_Hbyte),a
		ld d,a
		in a,(01h)
		or 00000011b
		out (01h),a
		ret

;----------------------------------------------------------------------------

; Receive byte from RS232 to register a
; Block execution until receive 1 byte
recv_data:
		ret

; Transmit byte from register a to RS232
transmit_data:
		ret
		.end
