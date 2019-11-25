
.thumb
.global CheckItem
.type CheckItem, %function

.equ DoesUnitHaveItem, 0x080179F8 @Params: r0=char data ptr, r1=item id to search for

.macro blh to, reg
    ldr \reg, =\to
    mov lr, \reg
    .short 0xF800
.endm

CheckItem:
push { lr }
ldr r0, =#0x03004E50
ldr r0, [ r0 ] @ Get current unit's character struct
ldr r1, =#0x030004BC
ldr r1, [ r1 ] @ Get item specified
blh DoesUnitHaveItem, r2

ldr r1, =#0x030004E8 @ Offset of slot 0xC
cmp r0, #0x00
beq False
mov r2, #0x01
b End

False:
mov r2, #0x00

End:
str r2, [ r1 ]
pop { r0 }
bx r0
