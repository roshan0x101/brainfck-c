# brainfck-c

It is an esoteric programming language, inspired by the original esoteric programming language, named BrainF\*ck

# Quick Start

To get yourself started to try this program, use this following commands:

```bash
git clone https://github.com/arleydev0x101/brainfck-c
cd brainfck-c
make
./brainfk samples/hello-world.bf
```

# Pre-requisites

This are the following requirements:

## Windows

| Requirements                                                                                                                                                                        | Description                                                    |
| ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | -------------------------------------------------------------- |
| **[Make GNU](https://www.gnu.org/software/make/)**                                                                                                                                  | For quick compiling a software                                 |
| **[g++](https://gcc.gnu.org/) or [clang](https://clang.llvm.org/)**                                                                                                                 | Our C/C++ Compiler                                             |
| **[Git](https://git-scm.com/)**                                                                                                                                                     | For cloning/fetching the repository                            |
| **[Cygwin](https://www.cygwin.com/), [MSYS2](https://www.msys2.org/), [WSL2](https://learn.microsoft.com/en-us/windows/wsl/install) or [Git Bash](https://git-scm.com) (Optional)** | For more flexible in performing this task (supported in Linux) |

In Linux and MacOS, everything was already provided.

I recommend MSYS2 to download and install, since some other tools that we need is already provided.
If Make, git, and g++ or clang, isn't there, you can use this following command:

## For g++

If you prefer "g++" as our C/C++ compiler, this following command;

```bash
pacman -Syu

pacman -S mingw-w64-ucrt-x86_64-gcc

# This will check if "g++" is already exist
g++ --version
```

## For clang

```bash
pacman -Syu

# I suggest to add "mingw-w64-ucrt-x86_64-gcc", toensure "clang" will work
pacman -S mingw-w64-ucrt-x86_64-gcc clang

# This will check if "clang" is already exist
clang --version
```

# Instructions

## For Windows (Cygwin, WSL2, MYSYS2, etc.), Linux and MacOS

```bash
# It compiles the main program
make main

# If the program needs a permission to run, use this command
chmod +x brainfck

# Run
./brainfck
```

# Usage

```bash
brainfk <filename> [options]

Options:
	-s	ASCII number for separation of digits
	-c	It prints the output as decimal (separated by space), instead of character
	-h	It prints the help message
```

# Example

```bash
./brainfck main.bf				# The file that you wanted to run its code
./brainfck -c main.bf			# It prints as decimal value, instead of a character
./brainfck -c main.bf -s 42		# It Adds separation, as it prints the decimal value outputs
```

# Usage of Brainfck

This is the following symbols that you can use:

| Symbol | Description                                                                            |
| ------ | -------------------------------------------------------------------------------------- |
| <      | Move to the left-side of the cell                                                      |
| >      | Move to the right-side of the cell                                                     |
| +      | Increments 1 value in the current cell                                                 |
| -      | Decrements 1 value in the current cell                                                 |
| .      | Prints the current cell                                                                |
| ,      | Makes an input in the initial cell                                                     |
| [      | Starting loop                                                                          |
| ]      | Ending loop. It acts, as it checks the initial cell is 0. It ends the loop if its true |

# Example

This code, shows the output, "Hello World!"

```
++>+++++++[<++++++++++>-]<.
++++>+++++[<+++++>-]<.
+++++++.
.
+++.
+>++++++++[<---------->-]<.
+++++>+++++[<++++++++++>-]<.
------>+++[<++++++++++>-]<.
+++.
------.
--------.
+++>+++++++[<---------->-]<.
```

# Using the Generator

## For Windows (Cygwin, WSL2, MYSYS2, etc.), Linux and MacOS

```bash
# It compiles the program
make generator

# If the program needs a permission to run, use this command
chmod +x brainfk-gen

# Run
./brainfk-gen
```

# Usage of the Generator

```bash
./brainfk-gen [words]
```

# Example

```bash
./brainfk-gen Hello World!

# Same as the first line (without any other quote)
./brainfk-gen "Hello World!"

# Makes an input, for you to type something
./brainfk-gen
```

# Tips

Instead of highlighting and copy, manually, the output in your terminal, use this following command:

```bash
# Write
./brainfk-gen Hello World! > sample.b

# Append
./brainfk-gen Hello World! >> sample.b

# This works, but this will take also the prompt output
./brainfk-gen >> sample.b
```

This almost acts like the original BrainF\*ck

# Troubleshooting

## For "make"

If this error occurred in your terminal, as you use "make" command:

```bash
make: *** [makefile:6: all] Error 127
```

Open the filename "makefile". If clang is exist (to find out the existence of clang, find out in **[For clang section](#for-clang)**), but g++ is not, change the value of COMPILER variable in that file (in default, this was located in line 3):

```bash
# Before the value
COMPILER = g++

# This should be the value after
COMPILER = clang
```

Then run this command:

```bash
# This should work
make
```

If you don't prefer some other compiler, more than that default, follow the instructions in **[Pre-requisites section](#pre-requisites)**

# Disclamer

Imitating this existing program is not my intention to own the idea of the original author. It is my only purpose to learn a lot in C.

For more info about BrainF\*ck, check it out in [Wikipedia](https://en.wikipedia.org/wiki/Brainfuck)
