@ .global faes_key_schedule

@ .text

@ sbox:
@     .word 0x7B777C63, 0xC56F6BF2, 0x2B670130, 0x76ABD7FE, 0x7DC982CA, 0xF04759FA, 0xAFA2D4AD, 0xC072A49C
@     .word 0x2693FDB7, 0xCCF73F36, 0xF1E5A534, 0x1531D871, 0xC323C704, 0x9A059618, 0xE2801207, 0x75B227EB
@     .word 0x1A2C8309, 0xA05A6E1B, 0xB3D63B52, 0x842FE329, 0xED00D153, 0x5BB1FC20, 0x39BECB6A, 0xCF584C4A
@     .word 0xFBAAEFD0, 0x85334D43, 0x7F02F945, 0xA89F3C50, 0x8F40A351, 0xF5389D92, 0x21DAB6BC, 0xD2F3FF10
@     .word 0xEC130CCD, 0x1744975F, 0x3D7EA7C4, 0x73195D64, 0xDC4F8160, 0x88902A22, 0x14B8EE46, 0xDB0B5EDE
@     .word 0x0A3A32E0, 0x5C240649, 0x62ACD3C2, 0x79E49591, 0x6D37C8E7, 0xA94ED58D, 0xEAF4566C, 0x08AE7A65
@     .word 0x2E2578BA, 0xC6B4A61C, 0x1F74DDE8, 0x8A8BBD4B, 0x66B53E70, 0x0EF60348, 0xB9573561, 0x9E1DC186
@     .word 0x1198F8E1, 0x948ED969, 0xE9871E9B, 0xDF2855CE, 0x0D89A18C, 0x6842E6BF, 0x0F2D9941, 0x16BB54B0

@ .macro rot_word output input
@     ror \output, \input, #8
@ .endm

@ .macro sub_word output input temp
@     ubfx \temp, \input, #0, #8
@     ldrb \temp, [r2, \temp]
@     bfi \output, \temp, #0, #8

@     ubfx \temp, \input, #8, #8
@     ldrb \temp, [r2, \temp]
@     bfi \output, \temp, #8, #8

@     ubfx \temp, \input, #16, #8
@     ldrb \temp, [r2, \temp]
@     bfi \output, \temp, #16, #8

@     ubfx \temp, \input, #24, #8
@     ldrb \temp, [r2, \temp]
@     bfi \output, \temp, #24, #8

@ .endm

@ .macro xor output input value
@     eor \output, \input, \value
@ .endm


@ .macro step_full rcon

@     rot_word r11, r10
@     sub_word r11, r11, r12
@     xor r11, r11, \rcon
@     xor r3, r3, r11

@     xor r4, r4, r3
@     xor r5, r5, r4
@     xor r6, r6, r5

@     sub_word r11, r6, r12
@     xor r7, r11, r7

@     xor r8, r8, r7
@     xor r9, r9, r8
@     xor r10, r10, r9

@     stmia r1!, {r3-r10}

@ .endm

@ .macro step_half rcon

@     rot_word r11, r10
@     sub_word r11, r11, r12
@     xor r11, r11, \rcon
@     xor r3, r3, r11

@     xor r4, r4, r3
@     xor r5, r5, r4
@     xor r6, r6, r5

@     stmia r1!, {r3-r6}

@ .endm

@ .macro proloque
@     push {r4-r11}
@ .endm

@ .macro epiloque
@     pop {r4-r11}
@ .endm

@ faes_key_schedule:

@     proloque

@     ldm r0, {r3-r10}
@     stmia r1!, {r3-r10}

@     adr r2, sbox

@     step_full #0x00000001
@     step_full #0x00000002
@     step_full #0x00000004
@     step_full #0x00000008
@     step_full #0x00000010
@     step_full #0x00000020
@     step_half #0x00000040

@     epiloque
    
@     bx lr
