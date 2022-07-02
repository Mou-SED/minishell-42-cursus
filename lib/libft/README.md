
<div align="center">
<img width=1000 hiegth=400 src="https://github.com/Mou-SED/LogosD/blob/master/LibftD.png">
</div>

<hr/>

This project gives the opportunity to recode functions that already exist in different libraries in c programming language and others that are not. the goal is to take in hand some functions that will help us in the next projects of the 42 cursus.

<hr/>

# > About!

<h3 align="center">Mandatory Part</h3>

## Functions from [![<ctype.h>](https://img.shields.io/badge/-%3Cctype.h%3E-blue)](https://devdocs.io/c/string/byte) library

- [`ft_isascii`](https://github.com/Mou-SED/libft-42-cursus/blob/main/src/ft_isascii.c) ~ is it ASCII character?
- [`ft_isalnum`](https://github.com/Mou-SED/libft-42-cursus/blob/main/src/ft_isalnum.c) ~ is it alphanumber character?
- [`ft_isalpha`](https://github.com/Mou-SED/libft-42-cursus/blob/main/src/ft_isalpha.c) ~ is it alphabetic character?
- [`ft_isdigit`](https://github.com/Mou-SED/libft-42-cursus/blob/main/src/ft_isdigit.c) ~ is it decimal-digit character?
- [`ft_isprint`](https://github.com/Mou-SED/libft-42-cursus/blob/main/src/ft_isprint.c) ~ is it printing character? (space character inclusive).
- [`ft_tolower`](https://github.com/Mou-SED/libft-42-cursus/blob/main/src/ft_tolower.c) ~ upper case to lower case letter conversion.
- [`ft_toupper`](https://github.com/Mou-SED/libft-42-cursus/blob/main/src/ft_toupper.c) ~ lower case to upper case letter conversion.

## Functions from [![<stdlib.h>](https://img.shields.io/badge/-%3Cstdlib.h%3E-blue)](https://devdocs.io/c/memory) library

- [`ft_atoi`](https://github.com/Mou-SED/libft-42-cursus/blob/main/src/ft_atoi.c) ~ convert ASCII string to integer.
- [`ft_calloc`](https://github.com/Mou-SED/libft-42-cursus/blob/main/src/ft_calloc.c) ~ memory allocation initialize with zeros.

## Functions from [![<strings.h>](https://img.shields.io/badge/-%3Cstrings.h%3E-blue)](https://fr.wikipedia.org/wiki/String.h) library

- [`ft_bzero`](https://github.com/Mou-SED/libft-42-cursus/blob/main/src/ft_bzero.c) ~ write zeros to a byte string.
- [`ft_memset`](https://github.com/Mou-SED/libft-42-cursus/blob/main/src/ft_memset.c) ~ write a byte to a byte string.
- [`ft_memchr`](https://github.com/Mou-SED/libft-42-cursus/blob/main/src/ft_memchr.c) ~ locate byte in byte string.
- [`ft_memcmp`](https://github.com/Mou-SED/libft-42-cursus/blob/main/src/ft_memcmp.c) ~ compare byte string.
- [`ft_memmove`](https://github.com/Mou-SED/libft-42-cursus/blob/main/src/ft_memmove.c) ~ copy byte string.
- [`ft_memcpy`](https://github.com/Mou-SED/libft-42-cursus/blob/main/src/ft_memcpy.c) ~ copy memory area.

## Functions from [![<string.h>](https://img.shields.io/badge/-%3Cstring.h%3E-blue)](https://devdocs.io/c/string/byte) library

- [`ft_strlen`](https://github.com/Mou-SED/libft-42-cursus/blob/main/src/ft_strlen.c) ~ find out the length of the string.
- [`ft_strchr`](https://github.com/Mou-SED/libft-42-cursus/blob/main/src/ft_strchr.c) ~ locate character in string (first occurrence).
- [`ft_strrchr`](https://github.com/Mou-SED/libft-42-cursus/blob/main/src/ft_strrchr.c) ~ locate character in string (last occurrence).
- [`ft_strnstr`](https://github.com/Mou-SED/libft-42-cursus/blob/main/src/ft_strnstr.c) ~ locate a substring in a string (of limited size).
- [`ft_strncmp`](https://github.com/Mou-SED/libft-42-cursus/blob/main/src/ft_strncmp.c) ~ compare strings (of limited size).
- [`ft_strlcpy`](https://github.com/Mou-SED/libft-42-cursus/blob/main/src/ft_strlcpy.c) ~ copy strings (of limited size).
- [`ft_strdup`](https://github.com/Mou-SED/libft-42-cursus/blob/main/src/ft_strdup.c) ~ save a copy of a string (using malloc).
- [`ft_strlcat`](https://github.com/Mou-SED/libft-42-cursus/blob/main/src/ft_strlcat.c) ~ concatenate strings of limited size (second argument of the function into the first one).

## Non-standard functions

- [`ft_putchar_fd`](https://github.com/Mou-SED/libft-42-cursus/blob/main/src/ft_putchar_fd.c) ~ output a character to given file.
- [`ft_putstr_fd`](https://github.com/Mou-SED/libft-42-cursus/blob/main/src/ft_putstr_fd.c) ~ output string to given file.
- [`ft_putendl_fd`](https://github.com/Mou-SED/libft-42-cursus/blob/main/src/ft_putendl_fd.c) ~ output string to given file with newline.
- [`ft_putnbr_fd`](https://github.com/Mou-SED/libft-42-cursus/blob/main/src/ft_putnbr_fd.c) ~ output integer to given file.
- [`ft_itoa`](https://github.com/Mou-SED/libft-42-cursus/blob/main/src/ft_itoa.c) ~ convert integer to ASCII string.
- [`ft_substr`](https://github.com/Mou-SED/libft-42-cursus/blob/main/src/ft_substr.c) ~ extract substring from string.
- [`ft_strtrim`](https://github.com/Mou-SED/libft-42-cursus/blob/main/src/ft_strtrim.c) ~ trim beginning and end of string with the specified characters.
- [`ft_strjoin`](https://github.com/Mou-SED/libft-42-cursus/blob/main/src/ft_strjoin.c) ~ concatenate two strings into a new string (using malloc).
- [`ft_split`](https://github.com/Mou-SED/libft-42-cursus/blob/main/src/ft_split.c) ~ split string, with specified character as delimiter, into an array of strings.
- [`ft_strmapi`](https://github.com/Mou-SED/libft-42-cursus/blob/main/src/ft_strmapi.c) ~ create new string from modifying string with specified function.
- [`ft_striteri`](https://github.com/Mou-SED/libft-42-cursus/blob/main/src/ft_striteri.c) ~ modify the string with the specified function if necessary. using the current character address.

<h3 align="center">Bonus Part</h3>

## Linked list functions

- [`ft_lstnew`](https://github.com/Mou-SED/libft-42-cursus/blob/main/src/bonus/single_linked_list/ft_lstnew.c) ~ create new list.
- [`ft_lstsize`](https://github.com/Mou-SED/libft-42-cursus/blob/main/src/bonus/single_linked_list/ft_lstsize.c) ~ count elements of a list.
- [`ft_lstlast`](https://github.com/Mou-SED/libft-42-cursus/blob/main/src/bonus/single_linked_list/ft_lstlast.c) ~ find last element of list.
- [`ft_lstadd_back`](https://github.com/Mou-SED/libft-42-cursus/blob/main/src/bonus/single_linked_list/ft_lstadd_back.c) ~ add new element at end of list.
- [`ft_lstadd_front`](https://github.com/Mou-SED/libft-42-cursus/blob/main/src/bonus/single_linked_list/ft_lstadd_front.c) ~ add new element at beginning of list.
- [`ft_lstdelone`](https://github.com/Mou-SED/libft-42-cursus/blob/main/src/bonus/single_linked_list/ft_lstdelone.c) ~ delete element from list.
- [`ft_lstclear`](https://github.com/Mou-SED/libft-42-cursus/blob/main/src/bonus/single_linked_list/ft_lstclear.c) ~ delete sequence of elements of list from a starting point.
- [`ft_lstiter`](https://github.com/Mou-SED/libft-42-cursus/blob/main/src/bonus/single_linked_list/ft_lstiter.c) ~ apply function to content of all list's elements.
- [`ft_lstmap`](https://github.com/Mou-SED/libft-42-cursus/blob/main/src/bonus/single_linked_list/ft_lstmap.c) ~ apply function to content of all list's elements into new list.
  
# > Usage!

### Compilation

To make a library without the linked list functions (bonus part) :

```c
make
```
or
```c
make all
```
if you need to use linked list functions, you can make it with a bonus target like this :
```c
make bonus
```

### Linking the library

To use libft in your code, you must add the include header to your code :

```c
#include "libft.h"
```
and add the libft folder to your directory and when you compile your code, just link it like this:

```c
gcc your "file .c" -lft -L path/to/libft.a -I path/to/libft.h
```

# > Testing!

You can use these testers to test the functionality of functions :

[![Tripouille](https://img.shields.io/badge/-Tripouille%2FTester-green)](https://github.com/Tripouille/libftTester) [![libft-unit-test](https://img.shields.io/badge/-alelievr%20%2F%20libft--unit--test-green)](https://github.com/alelievr/libft-unit-test) [![jtoty/libfttest](https://img.shields.io/badge/-jtoty%2FLibftest-green)](https://github.com/jtoty/Libftest)

# > Goal!

After completing this project, I learned a lot of information about the basics of coding using C programming. Ultimately, the goal of this library is to be able to write clean code and know how to protect my functions and, of course, to familiarize myself with the library, which will help me a lot in future projects.
