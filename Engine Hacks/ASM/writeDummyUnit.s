@0x30004B8 is where setval stuff is at

.thumb
mov  r2, =0x030004B8 @sval offset
ldr  r0, [r0, #4]    @sval 1, x
ldr  r1, [r0, #8]    @sval 2, y
mov  r2, =0x0202E4D8 @r2 = pointer to unit map
ldr  r2, [r2]        @r2 = unit map
lsl  r1, r1, #2      @multiply r1 by 4, because it is a Y value
ldr  r1, [r2, r1]    @r1 = row pointer
mov  r2, #0xCC       @obviously not used for this purpose.
strb r2, [r1, r0]    @r1+r0 = row+column, r2=mark value
bx   lr              @return
