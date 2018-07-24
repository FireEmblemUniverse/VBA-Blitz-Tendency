@0x30004B8 is where setval stuff is at

.thumb
ldr  r0, SVAL_OFFSET
ldr  r1, [r0, #4]     @sval 1, X
ldr  r2, [r0, #8]     @sval 2, Y
ldr  r0, POIN_UNIT_MAP
ldr  r0, [r0]         @r0 = unit map
lsl  r2, r2, #2       @multiply r2 by 4, because it is a Y value
ldr  r0, [r0, r2]     @r0 = row pointer
mov  r2, #0xCC        @obviously not used for this purpose.
strb r2, [r1, r0]     @r1+r0 = row+column, r2=mark value
bx   lr               @return

.ltorg
SVAL_OFFSET:
.long 0x030004B8
POIN_UNIT_MAP:
.long 0x0202E4D8
.align
