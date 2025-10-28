// DO NOT edit below
.syntax unified
.thumb
// DO NOT edit above

// FIND IN DATASHEET REGISTER MAP
.equ RCC_BASE,       ???                // RCC base address
.equ RCC_AHBENR,     RCC_BASE + ???     // AHB Peripheral enable register
.equ GPIO_MODER,     ???                // GPIO mode register offset
.equ GPIO_ODR,       ???                // GPIO output data register offset

.global my_gpio_init
.global my_gpio_toggle
.global my_hal_delay

// !!! dont be afraid to look at the C implementation for help !!!
// dont over think it!! nothing is here to trick you !!

.thumb_func
my_gpio_init:
    ldr r3, =???                        // We have to enable some clock thing to init GPIOs
    ldr r4, [r3]
    orr r4, r4, #(1 << ???)             // Find the correct bit position to enable the RCC
    str r4, [r3]

    // r0: port base, r1: pin, r2: mode
    lsl r3, r1, #1
    mov r4, #3
    lsl r4, r4, r3

    ldr r5, [r0, #???]                  // what register are we modifying to set the mode?
    ??? r5, r5, r4                      // clear the 2 bits first
    lsl r6, r2, r3
    orr r5, r5, r6
    str r5, [r0, #???]                  // write back to the what register

    ???                                 // branch link register

.thumb_func
my_gpio_toggle:
    // r0 = port base
    // r1 = pin number

    ldr r2, [r0, #???]                  // read output data register
    movs r3, #1               
    ??? r3, r3, r1                      // create bitmask for pin using bit shift
    ??? r2, r2, r3                      // what logic element toggles something?
    str r2, [r0, #???]                  // write back to what register?

    bx lr                               // branch link register = return to caller

.thumb_func
my_hal_delay:
    // r0 = delay in ms

ms:
    movs r1, #???                       // adjust based on system clock frq  [CONSTANT]

cnt:
    ??? r1, r1, #1                      // count down or count up? which instruction mnemonic supports that?
    ??? cnt                             // loop until done, what branch condition do we want?

    subs r0, r0, #1
    bne ms       

    bx lr
