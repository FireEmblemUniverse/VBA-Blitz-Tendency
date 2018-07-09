.thumb
.equ AxeFaithID, SkillTester+4

push {r4-r7, lr} 

@Check if unit has skill
ldr 	r0, SkillTester
mov 	lr, r0
mov 	r0, r4
ldr 	r1, AxeFaithID
.short	0xf800
cmp 	r0, #0
beq 	NoSkill

@Unit has skill, check to see if unit has an axe equipped
mov     r0, #0x50      @Move to the attacking unit weapon type.
ldrb    r0, [r4, r0]   @Load the attacking unit weapon type.
ldr     r1,            @Load in the list of Faire Skills.
ldrb    r1,[r1,r0]     @Load in the Faire Skill corresponding to the equipped weapon.
mov     r0,r4          @Store attacker data into r0 (for the purposes of SkillTester).
ldr     r3,SkillTester 
mov     lr, r3
.short 0xf800         @Call Skill Tester.
cmp r0, #0            @Check if unit has the corresponding skill.
beq     NoSkill

@Add to Hit
mov     r0, 0x19
ldrh    r0, [r4,r0]   @load luck
lsr     r1, r0, #1    @put half luck in r1
add     r0, r0, r1    @add back together.
mov     r3, #0x60
ldrh    r1, [r4,r3]   @load hit
add     r1, r0        @Increase hit by 1.5x Luck.
strh    r1, [r4,r3]   @store.

NoSkill:
pop {r4-r7} 
pop {r0}
bx r0

.align
SkillTester:
@POIN SkillTester
@POIN FaireIDList


@@Axe Faith
@@+10 Hit if post-enemy evasion hit is above 40 but below 70.

@@for axe faith Ive settled on axes dont break and hit += luck * 1.5

@@but if you follow the Axe Faith
@@anything over 49 is actually 100