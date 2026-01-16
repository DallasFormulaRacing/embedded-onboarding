# About

A collection of tutorials to help with the onboarding process for the embedded systems teams. The tutorials serve to familiarize new members to the tools and skills the embedded teams use on a daily basis. All of the concepts in here are something a member should be able to understand to be a successful member on the team.

These were created due to the need for an industry-ready embedded systems tutorial that succinctly provides the necessary context and lays the foundation for systems programming in a sequential and structured manner. They follow a learning progression inspired by Bloom’s Taxonomy, moving from conceptually remembering to understanding to applying, and then, finally, to creating.

#### _Consider giving this repository a ☆ if you found it helpful!_

## Disclosure

1\. This onboarding is designed to guide you and not spoonfeed you. You are encouraged to actively engage with the presented material, look up unfamiliar terms and consult external resources like Google, datasheets, technical manuals, and vendor websites.

2\. Feel free to use ChatGPT or other generative AI assistants WITH DISCRETION. You are only cheating yourself by blindly copy-pasting, and AI is not an acceptable substitute for understanding.

3\. You will not be assigned a project upon completion of this tutorial if

a) your work is not genuinely yours, or

b) you do not pass a knowledge check at the end, or

c) you demonstrate that you should not be allowed to operate independently in this team.

> [!IMPORTANT]
> Make sure you read this:

This tutorial set assumes a \*NIX environment (operating system). This includes:

-   macOS (this tutorial was developed on macOS)
-   all Linux distributions which includes but is not limited to

    -   Arch
    -   Ubuntu
    -   Debian

-   freeBSD and openBSD

All further instructions are written under the assumption that your environment is [POSIX compliant](https://stackoverflow.com/questions/1780599/what-is-the-meaning-of-posix).

If you're using Windows, you'll need a compatible environment to follow along effectively. I recommend one of the following:

1. Using MSYS2's MINGW64 environment: This provides a Unix-like shell for Windows.

2. **Windows Subsystem for Linux (WSL): Provides a native Linux environment on Windows. Suitable for most development workflows. (Recommended) **

3. Dual Boot Setup: Install Linux alongside Windows and choose your operating system at startup.
    > Note: If you are setting up a dual boot alongside Windows, make sure you have access to your Microsoft account because you will need to your Bitlocker decryption key otherwise you will lose all your data.

You can read more [here](https://github.com/DallasFormulaRacing/embedded-onboarding/wiki/DEnvironment).

You can also see the Windows setup [guide](SETUP.md) I wrote when we migrated from CubeIDE to VSCode.

## Table of Contents

| Section | Title                          | Difficulty | Learning Outcomes                                                                                                                                                                                                                      | -        |
| ------- | ------------------------------ | ---------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | -------- |
| 00      | Introduction & Version Control | -          | Basic grasp of embedded programming and an full understanding of git.                                                                                                                                                                  | Required |
| 01      | The C Language                 | +          | Fundamental C programming concepts: control structures, pointers, structs, memory, basic data structures, volatile and weak.                                                                                                           | Required |
| 02      | Computer Architecture          | +++        | Understanding of registers, compiler process, linking, RAM, stack and heap memory, working knowledge of ARMv8 assembly.                                                                                                                | Optional |
| 03      | Peripherals and Protocols      | ++         | Interfacing with external modules. Know and understand CAN, I2C, SPI, GPIO. Know how to utilize DMA. Using the STM32 HAL to interface with peripherals.                                                                                | Required |
| 04      | Operating Systems              | +++        | Understanding of inner workings of operating systems, RTOS. Know how and what a scheduler does and works. Know how processes and threads work with each other. Understand parallelism and concurrency. Understand interrupts.          | Optional |
| 05      | Hardware and Signal Processing | ++++       | Analog and digital signals and converting between the two. Basics of EMI mitigation. Signal processing and filtering basics. Introduction to filtering. CMSIS libraries. Debugging with JTAG and OpenOCD. Creating the IOC and pinout. | Optional |
| 06      | Final Project                  | +++        | Create a rudimentary data acquisition system; no hardware design required. Send information with print over UART.                                                                                                                      | Optional |

## References

\*not in any particular order

[OpenSTM32](https://www.openstm32.org/HomePage)
[CMake]()
[Makefile]()
[]()
[]()
[]()
[]()

## Acknowledgements
