# brainfck-c

It is a esoteric programming language, inspired by the original esoteric programming language, named BrainF\*ck

# Instructions

## For Windows (Cygwin, WSL2, MYSYS2, etc.), Linux and MacOS

```bash
# It compiles the program
make

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

| Symbol | Description                                                                         |
| ------ | ----------------------------------------------------------------------------------- |
| <      | Move to the left-side of the cell                                                   |
| >      | Move to the right-side of the cell                                                  |
| +      | Increments 1 value in the current cell                                              |
| -      | Decrements 1 value in the current cell                                              |
| .      | Prints the current cell                                                             |
| ,      | Makes an input in the initial cell                                                  |
| [      | Starting loop                                                                       |
| ]      | Ending loop, acts, as it checks the initial cell is 0. It ends the loop if its true |

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
make

# If the program needs a permission to run, use this command
chmod +x brainfk-gen

# Run
./brainfk-gen
```

# Usage of the Generator

```bash
brainfk-gen [words]
```

# Example

```bash
brainfk-gen Hello World!

# Same as the first line (without any other quote)
brainfk-gen "Hello World!"

# Makes an input, for you to type something
brainfk-gen
```

# Tips

Instead of highlighting and copy, manually, the output in your terminal, use this following command:

```bash
# Write
brainfk-gen Hello World! > sample.b

# Append
brainfk-gen Hello World! >> sample.b

# This works, but this will take also the prompt output
brainfk-gen >> sample.b
```

This almost acts like the original BrainF\*ck

# Disclamer

Imitating this existing program is not my intention to own the idea of the original author. Immitating this is my only purpose to learn a lot in C

For more info about BrainF\*ck, check it out in [Wikipedia](https://en.wikipedia.org/wiki/Brainfuck)
