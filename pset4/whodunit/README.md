# Questions

## What's `stdint.h`?
The <stdint.h> header shall declare sets of integer types having specified widths, and shall define corresponding
sets of macros. It shall also define macros that specify limits of integer types corresponding to types defined in
other standard headers.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?
It makes it easier to work with specific data types that have different sizes in bytes.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?
BYTE: 1
DWORD: 32
LONG: 32
WORD: 16

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."
424D in Hex.

## What's the difference between `bfSize` and `biSize`?
bfSize is the size of the whole bmp file, which includes the headerfiles, while biSize is the size of the
BITMAPINFOHEADER header file. biSize is constant and it equals 54 bytes.

## What does it mean if `biHeight` is negative?
If biHeight is negative, the bitmap is a top-down DIB and its origin is the upper-left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?
The biBitCount member of the BITMAPINFOHEADER structure determines
the number of bits that define each pixel and the maximum number of colors in the bitmap.

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?
If the file doesn't exist or if the user doesn't have write permission's on the current directory.

## Why is the third argument to `fread` always `1` in our code?
It's the number of elements of that size we're reading at a time.

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?
3 bytes to extend the scanline’s length to a multiple of 4.

## What does `fseek` do?
fseek() function is used to move file pointer position to the given location.

## What is `SEEK_CUR`?
Is a function to file handling in C programming language, It moves file pointer position to given location.
