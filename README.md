# Fudge Compiler

Fudge Compiler is a compiler for the esoteric language "Brainf\*ck". It translates valid Brainf\*ck code into
NASM x86-64 assembly code.

Brainf*ck is a minimalist programming language invented by Urban Miller in 1993. Originally made as a challenge to write
the smallest possible compiler for a language that is fully Turing-complete, it is now rather well known for being
a nonsensical language that is extremely difficult to write in.

Despite that, perhaps you would like to take the challenge. Brainf*ck is comprised of only eight single character commands,
plus a data pointer which points to a single index of a 30,000 byte array. The commands are as follows:

- "+"   Increments the byte at the current data pointer by one
- "-"   Decrements the byte at the current data pointer by one
- ">"   Move the data pointer once to the right
- "<"   Move the data pointer once to the left
- "."   Output the byte at the data pointer as an ASCII character
- ","   Accept one byte of input, storing it at the location of the data pointer
- "["   If the byte at the current pointer is zero, jump to after the matching "]"
- "]"   If the byte at the current pointer is not zero, jump back to the matching "["

And that's all there is! Any characters not a part of this set will be ignored, so you can easily leave comments,
newlines, etc.

If you don't want to write your own just yet, try this example program and see what it says!
`>++++++++[<+++++++++>-]<.>++++[<+++++++>-]<+.+++++++..+++.>>++++++[<+++++++>-]<+
+.------------.>++++++[<+++++++++>-]<+.<.+++.------.--------.>>>++++[<++++++++>-
]<+.`

As of now, the compiler will theoretically accept any file extension, but I would suggest using a .txt file.

Current version does not include the commands ",", still working on them.


# Run instructions

You will need:
 - NASM - The Netwide Assembler
 - GCC - GNU Compiler Collection
Add both to your system enviornment variables before proceeding.

- Download the latest Fudge release (x86-64 Executable, windows only as of the moment.)
- Create your Brainf\*ck program (.txt)
- Run: .\fudge.exe (File to compile)
- After completion, Fudge will have generated an assembly file (In this example, helloWorld.asm).
- Then:
  `nasm -f win64 helloWorld.asm -o helloWorld.obj`
  `gcc helloWorld.obj -o helloWorld.exe`
  `.\helloWorld.exe`


# If you would like to build the program yourself, download the fudge.c file and run the following instructions in terminal/command prompt:

You will need:
 - NASM - The Netwide Assembler
 - GCC - GNU Compiler Collection
Add both to your system enviornment variables before proceeding.

1. In the file location of fudge.c, open the path in terminal
2. Execute "gcc -o fudge.exe fudge.c" (This only needs to be run once)
3. Create your Brainf*ck program (helloWorld.txt for this example)
4. Execute ".\fudge.exe helloWorld.txt"
5. After execution, Fudge Compiler will have generated "helloWorld.asm"
6. Execute "nasm -f win64 helloWorld.asm -o helloWorld.obj"
7. Execute "gcc helloWorld.obj -o helloWorld.exe"
8. Finally, execute your program with ".\helloWorld.exe"


# Future Plans:
- Input during runtime rather than through a command line argument
- Built in linking (So no command line required)
- Program flags (-c for compile-only, -f for FASM syntax maybe?)



