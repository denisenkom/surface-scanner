;----------------------------------------------------------------------------
stack_ptr	.equ 2100h
RAM		.equ 2000h
; variables
IO1_A	.equ	00h
IO1_B	.equ	01h
IO1_C	.equ	02h
IO1_D	.equ	03h

IO2_A	.equ	00h
IO2_B	.equ	01h
IO2_C	.equ	02h
IO2_D	.equ	03h

IO3_A	.equ	00h
IO3_B	.equ	01h
IO3_C	.equ	02h
IO3_D	.equ	03h

TMP		.equ	RAM

ACP_ERROR_CODE	.equ	0FFh	; ACP didn't set until 10 cycles


		.org 0h 			;Общий старт с 0000h
		ld sp,stack_ptr 		; указатель стека
		
		ld a,10011001b	; init U6 mode 0, PA in, PB out, PC in
		out (IO1_D),a	;
		
		ld a,10001001b	; init U7 mode 0, PA out, PB out, PC in
		out (IO2_D),a	;

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
		call recv_char
		and 0FEh	; make odd
		ld c,a
		call recv_char
		ld b,a
loop_acp:
		push bc			;11
		
		call acp_query
		jr z,error_acp	;12,7
		in a,(IO1_A)	;11
		call send_char		
		ld a,0001111b	;11
		and c			; 4
		ld e,a			; 4
		
		; delay 766,4444444 tacts for 57600 speed
		call delay 107
		call delay 107
		call delay 107
		call delay 107
		call delay 107
		call delay 107
		call delay 107
		ld hl,TMP		;10
		ld (hl),a		; 7 sum = 766
		
		call acp_query
		jr z,error_acp	;12,7
		ld a,c			; 4
		sla a			; 8
		sla a			; 8
		sla a			; 8
		sla a			; 8
		or e			; 4
		call send_char
		in a,(IO1_A)	;11
		call sq_send_char
		pop bc			;10
		dec bc			; 6
		dec bc			; 6
		ld a,b			; 4
		or c			; 4
		jp nz,loop_acp	;10
		
		jp main
error_acp:
		pop bc
		ld a,ACP_ERROR_CODE
		call send_char
		jp main

acp_query:
		in a,(IO1_B)	;11
		and 11111110b	; 7
		out (IO1_B),a	;11
		ld b,10			; 7 ????
cont_acp:
		in a,(IO1_B)	;11
		xor 00000010b	; 7
		out (IO1_B),a	;11
		in a,(IO1_C)	;11
		bit 4,a			; 8
		jr nz, end_acp	;12,7
		djnz cont_acp	;13
end_acp:
		ld c,a			; 4
		in a,(IO1_B)	;11
		or 00000011b	; 7
		out (IO1_B),a	;11
		and b			; 4	z=(b==0)
		ret				;10
		
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

; Receive byte from RS232 to register a
; Block execution until receive 1 byte
recv_data:
		ret

; Transmit byte from register a to RS232
transmit_data:
		ret
		.end
