.thumb

.global IBIHook
.type IBIHook, %function

ReturnLocation = 0x08059048 + 1

IBIHook:
	mov r0, r7

	ldr r3, =IBICheck
	bl BXR3

	ldr r3, =ReturnLocation

BXR3:
	bx r3
