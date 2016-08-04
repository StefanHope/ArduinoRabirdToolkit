# RabirdTookit Programming Guide

## Pointers

Use uintptr_t to store your point value, it's size will changed during different platform, it will take the less space as possible (We always hungry on memory).

You could always use rShortenPtr() and rLengthenPtr() to convert between the short ptr (for storage) and the long ptr (for using).
