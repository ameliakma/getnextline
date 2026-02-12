_This project has been created as part of the 42 curriculum by akhalfou._

---

# Description
getnextline is a C funcition that reads and returns a single line from a file descriptor. This project focuses on file manipulation, static variables, and memory management. The main challenge of this project is to create a function that can read from any file descriptor (files, standard input, network connections, etc.) while efficiently managing memory and handling various edge cases. The function must work with any buffer size defined at compilation time, from very small (1 byte) to very large values.

# Instructions:

## Compilation:
gcc -Wall -Wextra -Werror -D BUFFER-SIZE=42 getnextline.c getnextlineutils.c main.c -o gnl

## Usage:
int fd = open("file.txt", OrRDONLY);

## Algorithm Explanation

The implementation uses a static buffer with read-join-extract pattern:

Static buffer - Stores leftover data between function calls to handle multiple lines per read
readstash() - Reads chunks of BUFFER-SIZE bytes until finding \n or EOF
extractline() - Extracts one complete line from the buffer
newstr() - Updates buffer with remaining unread content.

Why this approach?
- Efficient: Minimizes system calls by reading in chunk.s
- Flexible: Works with any buffer size and line length.
- Memory safe: Proper allocation/deallocation, no leaks.
Alternatives considered:
Character-by-character: Too many system calls
Read entire file: Memory inefficient for large files.

# Ressources:

### documentation:
- read(2) man page
- Static variables in C.
- Youtube : gnl explication
- Geeksforgeeks : to understand Open, Fd and Read.

---

**AI Usage:
Code optimization: Splitting read_stash() into helper functions for norminette compliance
Documentation: README structure and algorithm explanation. AI was only for purpose comprehension**
