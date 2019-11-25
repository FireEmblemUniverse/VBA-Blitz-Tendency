.thumb
.equ MightyNineID, SkillTester+4

push {r4, lr}
mov	r4, r0 @attacker

@check if turn is equal to nine
ldr	r0,=#0x202BCF0
ldrh	r0, [r0,#0x10]
cmp	r0, #0x09
bne	End

@has skill
ldr	r0, SkillTester
mov	lr, r0
mov	r0, r4
ldr	r1, MightyNineID
.short	0xf800
cmp	r0, #0
beq	End

@add 27 to everything, adjusting for formulas
mov	r0, #0x5A
ldrh	r1, [r4,r0]	@load attack
add	r1, #0x1B	@add 27, three nines
strh	r1, [r4,r0]     @store

mov	r0, #0x5C
ldrh	r1, [r4,r0]	@load defence
add	r1, #0x1B	@add 27, three nines
strh	r1, [r4,r0]     @store

mov	r0, #0x5E
ldrh	r1, [r4,r0]	@load AS
add	r1, #0x1B	@add 27, three nines
strh	r1, [r4,r0]     @store

mov	r0, #0x60
ldrh	r1, [r4,r0]	@load hit
add	r1, #0x36	@add 54, six nines
strh	r1, [r4,r0]     @store

mov	r0, #0x62
ldrh	r1, [r4,r0]	@load avoid
add	r1, #0x36	@add 54, six nines
strh	r1, [r4,r0]     @store

mov	r0, #0x64
ldrh	r1, [r4,r0]	@load crit
add	r1, #0x0D	@add 13, 1.5 nines
strh	r1, [r4,r0]     @store

End:
pop	{r4, r15}
.align
.ltorg
SkillTester:
@Poin SkillTester
@WORD MightyNineID
