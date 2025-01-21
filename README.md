# BingShell

A simple shell implementation in C with basic features including process management, I/O redirection, and command history.

## Features

### Basic Shell Functions
- Command execution with arguments
- Built-in commands (cd, pwd, exit)
- Command history
- Simple prompt interface

### Process Handling
- Background process execution using &
- Job control (jobs command)
- Basic signal handling (Ctrl-C, Ctrl-Z)

### I/O Features
- Input/output redirection (>, <)
- Simple pipe support (|)

## Building

To build the shell:
```bash
make
```

To build and run tests:
```bash
make test
```

To clean build files:
```bash
make clean
```

## Usage

### Running the Shell
```bash
./bingshell
```

### Basic Commands
- `cd [directory]` - Change current directory
- `pwd` - Print working directory
- `exit` - Exit the shell
- `history` - Show command history
- `jobs` - List background processes

### Special Features
- Run process in background: `command &`
- Redirect output: `command > file`
- Redirect input: `command < file`
- Use pipe: `command1 | command2`

## Project Structure
- `shell.h` - Header file with declarations
- `main.c` - Core shell loop and initialization
- `execute.c` - Command execution and built-ins
- `io.c` - I/O redirection and pipe handling
- `globals.c` - Global variables
- `test_shell.c` - Test suite

## Team Members
1. [Member 1] - Core shell implementation
2. [Member 2] - Process control
3. [Member 3] - I/O features
4. [Member 4] - Testing and documentation

## File Manifest
- Source Files:
  - shell.h
  - main.c
  - execute.c
  - io.c
  - globals.c
- Test Files:
  - test_shell.c
- Build Files:
  - Makefile
- Documentation:
  - README.md
