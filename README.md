# SAU 2023/2024 Spring - System Programming (BSM308) Project

## Project Objective
This project parses a given input file and converts it to a character array then writes that to an output file.

Input file must be in a specific format which every line must consist of one of these four commands:

1. `yaz:` - write to the content, from the cursor position
2. `sil:` - delete from the content, from the cursor position (sweeping backwards)
3. `sonagit:` - move cursor to the end of the content
4. `dur:` - stop parsing

Following `yaz:` and `sil:` commands there should be parameters seperated by space in pairs. The first parameter of a pair is an integer and the latter is a character. The pair indicates either write or delete, based on the command, given character to the content given number of times.

If the input file contains any inconsistancy with the required format program detects prints the error and exits.

Example input file:
```
yaz: 1 a 3 b 3 c
sil: 1 b
sonagit:
yaz: 4 d
dur:
```

## Implementation Details

Libfdr library is used for input processing as stated in the document.

Folder structure:
```
/bin
  - executable file
/include
  - project header files
/lib
  /libfdr
    - header files and .a file
/obj
  - .o files
/src
  - C source code files
/txt
  - input and output files
- makefile
```

Makefile organized to compile, link and run the executable. So only invoking `make` command from the base folder is enough.
