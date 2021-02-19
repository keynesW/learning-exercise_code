@ set GPX2 OUTPUT mode led 2

    ldr r0,=0x11000c40
    ldr r1,[r0]
    bic r1,#0xf0000000
    orr r1,#0x10000000
    str r1,[r0]

@GPx1_0:   led 3
    ldr r0,=0x11000c20
    ldr r1,[r0]
    bic r1,#0x0000000f
    orr r1,#0x00000001
    str r1,[r0]

@GPF3_4   led 4
@GPF3_5   led 5

    ldr r0,=0x114001e0
    ldr r1,[r0]
    bic r1,#0xff0000
    orr r1,#0x110000
    @orr r1,#0x11111111
    str r1,[r0]


@////////////////////////////////////////////////////

    @ldr r0,=0x114001e4
    @ldr r1,[r0]
    @orr r1,#0x30
    @str r1,[r0]

@GPD0_0  Beef
    ldr r0,=0x114000a0
    ldr r1,[r0]
    bic r1,#0xf
    orr r1,#0x1

    ldr r0,=0x114000a4
    ldr r1,[r0]
    orr r1,#0x1
    str r1,[r0]

    


@///////////////////////////////////////////////////

@write data into DATA register

loop:
@led2
    ldr r0,=0x11000c44
    ldr r1,[r0]
    orr r1,#0x80
    str r1,[r0]
    bl delay

    bic r1,#0x80
    str r1,[r0]
    bl delay

@led 3

    ldr r0,=0x11000c24
    ldr r1,[r0]
    orr r1,#0x01
    str r1,[r0]
    bl delay

    bic r1,#0x01
    str r1,[r0]
    bl delay

@led 4
    @ldr r0,=0x114001e4
    @ldr r1,[r0]
    @orr r1,#0x30
    @str r1,[r0]

    ldr r0,=0x114001e4
    ldr r1,[r0]
    orr r1,#0x10
    str r1,[r0]
    bl delay

    bic r1,#0x10
    str r1,[r0]
    bl delay

@led 5
    ldr r0,=0x114001e4
    ldr r1,[r0]
    orr r1,#0x20
    str r1,[r0]
    bl delay

    bic r1,#0x20
    str r1,[r0]
    bl delay

    b loop


delay:
    ldr r5,=0x5ffffff
sub_loop:
    sub r5,r5,#1
    cmp r5,#0
    bne sub_loop
    mov pc,lr

