# RabirdTookit Programming Guide

## Pointers

Use uintptr_t to store your point value, it's size will changed during different platform, it will take the less space as possible (We always hungry on memory).

You could always use rShortenPtr() and rLengthenPtr() to convert between the short ptr (for storage) and the long ptr (for using).

You have better use class RRawPointer to manager your pointers for less space wasting.

WARNING: Don't use smart pointers to store your function pointer, they are different size!

## Local Variables

Our default thread stack is very small for local variables, change your algorithm to use local variable as fewer as possiable.

## String

Try to best not use normal string! They will eat stack memory! Our stack size is limit on most environment. Be notice your debug code, if you really want to use string, use F() to surround them for place them into Flash not stack or memory.
