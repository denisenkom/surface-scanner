;----------------------------------------------------------------------------
; ��楤�� ��।�� ᮮ�饭��
;----------------------------------------------------------------------------
; hl = ���� ᮮ�饭�� (ᮮ�饭�� �����稢����� ᨬ����� '$')

transmit:       in a,(40h)
                or 04h
                out (40h),a             ; �������� ��।�� ��⨢��


; ���� ����� CRC � ����� ᮮ�饭��
                ld hl,t_msg

                ld b,3                  ;
                ld c,0                  ; c=CRC

lnght_msg:      ld a,(hl)
                cp '$'
                jp z,lnght_fnd

                ld a,(hl)
                add a,c
                ld c,a

                inc b
                inc hl
                jp lnght_msg

lnght_fnd:      ld a,c
                rra
                rra
                rra
                rra
                and 00Fh
                cp 10
                jp c,pass_1
                add a,7
pass_1:         add a,'0'
                ld (hl),a
                inc hl

                ld a,c
                and 00Fh
                cp 10
                jp c,pass_2
                add a,7
pass_2:         add a,'0'
                ld (hl),a
                inc hl

                ld a,'$'
                ld (hl),a

; hl=���� ��।�������� ᮮ�饭��
; b=�������⢮ ��।������� ᨬ�����
;

send:
                ld hl,t_msg

send_msg:       ld d,(hl)       ;7
                ld c,8          ;7              ;���-�� ��।������� ���

                in a,(40h)      ;11
                or 80h          ;7  ;52
                out (40h),a     ;11             ;���⮢� ���

                call delay_35

send_char:      call trans_delay

                rla             ;4
                rr d            ;8
                ccf             ;4
                rra             ;4 ;54
                out (40h),a     ;11             ;��।�� ��।���� ���
                dec c           ;4

                nop
                nop
                nop
                nop
                nop

                jp nz,send_char ;10

                call trans_delay

                in a,(40h)      ;11
                and 7fh         ;7      ;52
                out (40h),a     ;11             ;�⮯��� ���

                call trans_delay

                inc hl          ;6              ;᫥���騩 ᨬ���
                dec b           ;4

                jp nz,send_msg  ;10

                in a,(40h)
                and 11111011b
                out (40h),a                     ;�������� ��।�� ����⨢��

                ret

trans_delay     call delay_107
                call delay_107
;               call delay_107
;               call delay_107
;               call delay_107
;               call delay_107  ;642

        nop
        nop
        nop


                nop
                nop             ;8

                call delay_27
                call delay_27
                call delay_27   ;74

                ret

;-------------------------------------------------------------------------------
; ��楤�� ��ࠢ�� ᨬ����
;-------------------------------------------------------------------------------

send_char_proc:
      ld d,(hl)       ;7
      ld c,8          ;7              ;���-�� ��।������� ���

      in a,(40h)      ;11
      or 80h          ;7  ;52
      out (40h),a     ;11             ;���⮢� ���

	call delay_35

send_char:
	call trans_delay

                rla             ;4
                rr d            ;8
                ccf             ;4
                rra             ;4 ;54
                out (40h),a     ;11             ;��।�� ��।���� ���
                dec c           ;4

                nop
                nop
                nop
                nop
                nop

                jp nz,send_char ;10

                call trans_delay

                in a,(40h)      ;11
                and 7fh         ;7      ;52
                out (40h),a     ;11             ;�⮯��� ���

                call trans_delay
	ret