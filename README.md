![GameBoyFuck](http://voidptr.io/dev/gameboy-brainfuck.gif)

Brainfuck Interpreter for Game Boy
==================================

Simple implementation of a [Brainfuck](https://en.wikipedia.org/wiki/Brainfuck) interpreter written in Z80-ish assembly for the Game Boy.
It's limited because of the platform. For example the amount of nested loops depend on the stack size. This implementation also has a reduced memory for brainfuck operations. Instead of the 30000 cells generally seen in interpreters this one has only 3072 cells.

