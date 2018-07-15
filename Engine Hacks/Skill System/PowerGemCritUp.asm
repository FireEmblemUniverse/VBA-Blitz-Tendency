
.thumb
.global PowerGemCritCalc
.type PowerGemCritCalc, %function

.equ DoesUnitHaveItem, 0x080179F8

.macro blh to, reg
    ldr \reg, =\to
    mov lr, \reg
    .short 0xF800
.endm

PowerGemCritCalc:
push { r4 - r7, lr }
mov r4, r0
ldr r1, =#PowerGemLynLink
ldrb r1, [ r1 ]
blh DoesUnitHaveItem, r2
cmp r0, #0x00
beq End
@ So they have the power gem.
mov r1, #0x66
ldrb r0, [ r4, r1 ]
add r0, #10
strb r0, [ r4, r1 ]

End:
pop { r4 - r7 }
pop { r0 }
bx r0
