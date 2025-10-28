# Work for section 02

Estimated completion time: 2 days.

Do all of your work in this directory (but not in this file) so that it can be easily reviewed by a senior member later.

You should constantly be referring back to the reading or other external sources. It is not expected of you to complete all the exercises in this unaided.

## Exercise 1: DIY HAL in C

Remember blinking the LED in the last section?

Find this function in the HAL files: `void HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init)`.

Delete the generated definition within the C file. Rewrite your own definition of it in C. You should be able to test it by seeing if it compiles, and if it actually blinks the LED.

Do the exact same for `void HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)` and `void HAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)`.

## Exercise 2: DIY HAL in Asm

Write your own GPIO Init, GPIO toggle, and HAL Delay in assembly. The total length of the assembly file should not more than 70 lines.

The goal of this exercise is to help you understand that HAL functionality ultimately reduces to bitwise manipulation of certain peripheral registers.

Read carefully:

A starter `gpio.s` assembly source file has been provided. It has been tested on an STM32L4. (Not the STM32F0, which is what you should use). There are multiple missing statements in the file. You must fill in the blanks as necessary to get the LED (whichever one you want, recommend a User LED and not a power LED) blinking.

While there are missing words or numbers, there are no missing lines. You do not need to write separate lines of assembly.

An accompanying `gpio.h` header file has also been provided. You do not need to edit it.

These standalone files will not function properly. You are responsible for moving the source file into `Core/Src` and the header file into `Core/Inc`. You are also responsible for editing your Makefile to account for a new source file.

Your main function should look like this:

```C
int main(void)
{
  my_gpio_init(GPIOA_BASE, 5, 0x01);

  while(1) {
    my_gpio_toggle(GPIOA_BASE, 5);
    my_hal_delay(100);
  }
}
```

You should then see your LED blink.

What did you learn? Explain each line of assembly (no complete sentences, just what it does and why). Write your response in another file in this directory.

Ensure both compile.

## Exercise 3: Interrupts and Callbacks

Pt 1: Follow this tutorial: https://wiki.st.com/stm32mcu/wiki/Getting_started_with_EXTI

Pt 2: Follow this tutorial: https://community.st.com/t5/stm32-mcus/how-to-use-register-callbacks-in-stm32/ta-p/580499

Do the equivalent for the F030RE8 board, as the tutorials follow intructions for another board.

## Exercise 4: Capture the bug

> [!IMPORTANT]
> This exercise is experimental. You may run into OS-compatibility issues.

Welcome to the last exercise! This is a capture-the-flag style mini-game which will require you to hunt for hidden symbols.

You are given a black-box-esque ELF binary named `vault`. Embedded within the executable and linkable regions is a secret message.

You must extract this secret message and decode it using `gdb`, `nm`, and `objdump`. You are only allowed to use those 3. You will use all 3 binary analysis tools.

Because this was assembled and compiled for x86, you do not need a board for this.

If you are on an ARM based computer (e.g. Macbook), please contact me.

When you find the flag, make a text file in the `exercise4` directory and paste the flag token there. Then, in that same text file, paste all the commands you ran and explain what each one does.

You are now finished with section 2.

> [!IMPORTANT]
> Hints below, attempt at least twice before opening them.

<details>
  <summary>Hint 1</summary>
  
Some keywords to look for: 
`win`, `flag`, `vault`, `printf`
  
</details>

<details>
  <summary>Hint 2</summary>
  
Use pipes and regex checkers to narrow down what you are looking for. These were covered in section 00. Use that in conjunction with `nm` and `objdump`.

From the `grep` manual page:

> Context Line Control :

       `-A NUM, --after-context=NUM` :
              Print NUM lines of trailing context after matching lines.
              Places a line containing a group separator (--) between
              contiguous groups of matches.  With the -o or
              --only-matching option, this has no effect and a warning is
              given.

</details>

<details>
  <summary>Hint 3</summary>
  
You should use `nm` to first list all of your symbols. There are red herrings designed to distract you. The flag message (the one you are looking for) is denoted by `flag{MESSAGE_TO_LOOK_FOR}`.

Then you should use `gdb` to read the disassembly.

</details>
