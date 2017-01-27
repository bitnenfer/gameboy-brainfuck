_RESET_: MACRO
    call wait_vblank
    call lcd_off
    ld B, $00
    ld HL, $9C00
    ld DE, $9FFF
    call memset
    call lcd_on
    ld SP, $FFFF
    ld HL, LCD_SCROLL_Y
    ld [HL], $00
    ld HL, LCD_SCROLL_X
    ld [HL], $00
    ENDM

                                ; string should be null term
M_PRINT: MACRO                         ; HL = string address
    call wait_vblank
    ld D, H                     ; store temp HL
    ld E, L
    ld HL, print_ptr
    ld B, [HL]
    inc HL
    ld C, [HL]                  
    ld H, D                     ; dereference print_ptr
    ld L, E
.print_loop:
    ld A, [HL]
    cp $00
    jr nz, .put_char
    jr .print_end
.put_char:
    ld D, H                     ; save string address
    ld E, L
    ld H, B                     ; we put char into buffer
    ld L, C
    cp $0A
    jr z, .print_newline
    ld [HL], A
.put_char_continue:
    inc HL
    ld A, H
    cp $A0
    jr nz, .put_char_continue_0
    ld H, $9C
    ld L, $00
.put_char_continue_0:
    ld B, H                     ; increment print_ptr data
    ld C, L
    ld H, D                     ; we restore string address
    ld L, E
    inc HL                      ; we increment string address
    jr .print_loop
.print_newline:
    ld A, L
    cp $1F
    jr z, .put_char_continue
    cp $3F
    jr z, .put_char_continue
    cp $5F
    jr z, .put_char_continue
    cp $7F
    jr z, .put_char_continue
    cp $9F
    jr z, .put_char_continue
    cp $BF
    jr z, .put_char_continue
    cp $DF
    jr z, .put_char_continue
    cp $FF
    jr z, .put_char_continue
    inc A
    ld L, A
    jr .print_newline
    
.print_end:
    ld HL, print_ptr            ; we save te new print_ptr
    ld [HL], B
    inc HL
    ld [HL], C
    ENDM