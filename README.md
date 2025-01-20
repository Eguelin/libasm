# Libasm

## Résumé

- **Objectives:**
	- Familiarize yourself with assembly language.
- **Skills:**
	- Rigor
	- Imperative programming
- **Tools:**
	- C
	- NASM
	- Makefile

## Table of Contents

1. [Introduction NASM](#i-introduction-nasm)
	- [Assembly Language](#assembly-language)
	- [Registers](#registers)
	- [Memory Addresses](#memory-addresses)
	- [Instructions](#instructions)
	- [Sections](#sections)
	- [Calling Convention](#calling-convention)
	- [System Calls](#system-calls)
	- [Call shared library functions](#call-shared-library-functions)
2. [Mandatory Part](#ii-mandatory-part)
	- [Mandatory Functions](#mandatory-functions)
3. [Bonus Part](#iii-bonus-part)
	- [Bonus Functions](#bonus-functions)
4. [Build Project](#iv-build-project)
5. [My Ressurces](#v-my-ressurces)

## I. Introduction NASM

### Assembly Language

Assembly language is a low-level programming language that is specific to a particular computer architecture. It is used to write programs that are executed by the CPU. Assembly language is a human-readable representation of machine code, which is the set of instructions that a CPU can execute directly.

### Registers

Registers are small storage locations built directly into the CPU. They are used to store data temporarily while the CPU is processing it. The x86-64 architecture has 16 general-purpose registers, each of which is 64-bits wide.

The following table shows the general-purpose registers in the x86-64 architecture:
| Name | Notes                                                         | Type      | 64-bit | 32-bit  | 16-bit  | 8-bit     |
|------|---------------------------------------------------------------|-----------|--------|---------|---------|-----------|
| rax  | Values are returned from functions in this register.          | scratch   | rax    | eax     | ax      | ah and al |
| rcx  | Function argument #4 (Linux) or typically counter.            | scratch   | rcx    | ecx     | cx      | ch and cl |
| rdx  | Function argument #3 (Linux).                                 | scratch   | rdx    | edx     | dx      | dh and dl |
| rbx  | Preserved register: don't use without saving!                 | preserved | rbx    | ebx     | bx      | bh and bl |
| rsp  | The stack pointer. Points to the top of the stack.            | preserved | rsp    | esp     | sp      | spl       |
| rbp  | Preserved register. Often stores old value of the stack ptr.  | preserved | rbp    | ebp     | bp      | bpl       |
| rsi  | Function argument #2 (Linux).                                 | scratch   | rsi    | esi     | si      | sil       |
| rdi  | Function argument #1 (Linux).                                 | scratch   | rdi    | edi     | di      | dil       |
| r8   | Scratch register.                                             | scratch   | r8     | r8d     | r8w     | r8b       |
| r9   | Scratch register.                                             | scratch   | r9     | r9d     | r9w     | r9b       |
| r10  | Scratch register.                                             | scratch   | r10    | r10d    | r10w    | r10b      |
| r11  | Scratch register.                                             | scratch   | r11    | r11d    | r11w    | r11b      |
| r12  | Preserved register. Save and restore before use.              | preserved | r12    | r12d    | r12w    | r12b      |
| r13  | Preserved register. Save and restore before use.              | preserved | r13    | r13d    | r13w    | r13b      |
| r14  | Preserved register. Save and restore before use.              | preserved | r14    | r14d    | r14w    | r14b      |
| r15  | Preserved register. Save and restore before use.              | preserved | r15    | r15d    | r15w    | r15b      |

To move data between registers, the `mov` instruction is used. The following table shows the different forms of the `mov` instruction for moving data between registers of different sizes.

Moving data between registers of different sizes:
| Destination / Source | 64-bit       | 32-bit          | 16-bit       | 8-bit         | Notes                   |
|----------------------|--------------|-----------------|--------------|---------------|-------------------------|
| 64-bit               | mov rax, rcx | movsxd eax, ecx | movsx ax, cx | movsx rax, cl | Write to whole register |
| 32-bit               | mov eax, ecx | mov eax, ecx    | movsx ax, cx | movsx eax, cl | Top 32 bits zeroed      |
| 16-bit               | mov ax, cx   | mov ax, cx      | mov ax, cx   | movsx ax, cl  | Only lower 16 bits used |
| 8-bit                | mov al, cl   | mov al, cl      | mov al, cl   | mov al, cl    | Only lower 8 bits used  |

### Memory Addresses

Memory addresses are used to access data stored in memory.

Memory addresses can be accessed using the following syntax:
| C/C++ type | Size (bytes) | x86-64 register | Access memory | Allocate memory |
|------------|--------------|-----------------|---------------|-----------------|
| char       | 1            | al              | BYTE [ptr]    | db              |
| short      | 2            | ax              | WORD [ptr]    | dw              |
| int        | 4            | eax             | DWORD [ptr]   | dd              |
| long       | 8            | rax             | QWORD [ptr]   | dq              |

### Instructions

Instructions are the basic building blocks of assembly language programs. They tell the CPU what operations to perform, such as moving data between registers, performing arithmetic operations, or branching to different parts of the program.

The following table shows some common x86-64 instructions and their meanings:
| Instruction | Description                                                                                                                                                  |
|-------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------|
| mov         | Move data between registers or memory locations.                                                                                                             |
| lea         | Load the effective address of a memory location into a register.                                                                                             |
| push        | Push a value onto the stack.                                                                                                                                 |
| pop         | Pop a value from the stack.                                                                                                                                  |
| add         | Add two values.                                                                                                                                              |
| sub         | Subtract one value from another.                                                                                                                             |
| inc         | Increment a value by one.                                                                                                                                    |
| dec         | Decrement a value by one.                                                                                                                                    |
| neg         | Negate a value (i.e., change its sign).                                                                                                                      |
| jmp         | Unconditionally jump to a different part of the program.                                                                                                     |
| cmp         | Compare two values. Sets flags that are used by conditional jump instructions.                                                                               |
| je          | Jump if : je (jump if equal), jne (jump if not equal), jg (jump if greater), jge (jump if greater or equal), jl (jump if less), jle (jump if less or equal). |

### Sections

Sections are used to organize the different parts of an assembly language program. The following sections are commonly used in x86-64 assembly programs:

- `.data`: Contains initialized data, such as variables and constants.
- `.bss`: Contains uninitialized data, such as variables that are initialized at runtime.
- `.text`: Contains the program instructions.

### Calling Convention

The calling convention is a set of rules that determine how functions are called and how arguments are passed between functions. The x86-64 architecture uses the System V AMD64 ABI calling convention, which specifies the following:

- The first six integer or pointer arguments are passed in registers `rdi`, `rsi`, `rdx`, `rcx`, `r8`, and `r9`.
- Additional arguments are passed on the stack.
- The return value is stored in register `rax`.

### System Calls

System calls are used to interact with the operating system. They allow programs to perform tasks such as reading from a file, writing to the console, or allocating memory. System calls are invoked by placing the system call number in register `rax` and the arguments in other registers, then executing the `syscall` instruction.

The following table shows some common system calls and their numbers:
| System Call | Number | Description                                                                 |
|-------------|--------|-----------------------------------------------------------------------------|
| read        | 0      | Read data from a file descriptor.                                           |
| write       | 1      | Write data to a file descriptor.                                            |
| exit        | 60     | Terminate the program.                                                      |

### Call shared library functions

Shared libraries are collections of precompiled code that can be linked to a program at runtime. They allow programs to reuse code that has already been written and tested.
When calling a shared library function, the address of the function is not known at compile time. Instead, the program calls a procedure linkage table (PLT) entry, which contains a jump instruction to the actual function address. The PLT entry is resolved at runtime by the dynamic linker.

```assembly
section .data
	msg db "Hello, world!", 0

section .text
	global _start
	Extren printf

	_start:
		push msg
		call printf wrt ..plt

		mov eax, 60
		xor edi, edi
		syscall
```

## II. Mandatory Part

The goal of this project is to familiarize yourself with the assembly language.

- The library must be named `libasm.a`.

- Submit a `main` that will test the functions and compile with the library to show that it works.

- the code must be written in 64-bit assembly `syntax Intel` and respect the calling convention.

- The `Makefile` must contain at least the following rules: `$(NAME)`, `all`, `clean`, `fclean`, and `re`.

- Use of the `-no-pie` compilation flag is prohibited.

### Mandatory Functions:

- **`ft_strlen`:**
	```c
	size_t ft_strlen(const char *s);
	```
	The `ft_strlen()` function calculates the length of the string `s`, excluding the terminating null byte (`'\0'`).

	For more info: `man 3 strlen`

- **`ft_strcpy`:**
	```c
	char *ft_strcpy(char *dst, const char *src);
	```
	The `ft_strcpy()` function copies the string `src` to `dst` (including the terminating null byte (`'\0'`)).

	For more info: `man 3 strcpy`

- **`ft_strcmp`:**
	```c
	int ft_strcmp(const char *s1, const char *s2);
	```
	The `ft_strcmp()` function compares the two strings `s1` and `s2`. It returns an integer less than, equal to, or greater than zero if `s1` is found, respectively, to be less than, to match, or be greater than `s2`.

	For more info: `man 3 strcmp`

- **`ft_write`:**
	```c
	ssize_t ft_write(int fd, const void *buf, size_t count);
	```
	The `ft_write()` function writes `count` bytes from buffer `buf` to the file descriptor `fd`. On success, the number of bytes written is returned. On error, `-1` is returned, and `errno` is set appropriately.

	For more info: `man 2 write`

- **`ft_read`:**
	```c
	ssize_t ft_read(int fd, void *buf, size_t count);
	```
	The `ft_read()` function reads `count` bytes from file descriptor `fd` into the buffer starting at `buf`. On success, the number of bytes read is returned. On error, `-1` is returned, and `errno` is set appropriately.

	For more info: `man 2 read`

- **`ft_strdup`:**
	```c
	char *ft_strdup(const char *s);
	```
	The `ft_strdup()` function returns a pointer to a new string that is a duplicate of the string `s`. Memory for the new string is obtained with `malloc`, and can be freed with `free`.

	For more info: `man 3 strdup`

## III. Bonus Part

The functions related to linked lists use the following structure:

```c
typedef struct s_list {
	void          *data;
	struct s_list *next;
} t_list;
```

### Bonus Functions:

- **`ft_atoi_base`:**
	```c
	int ft_atoi_base(const char *str, int base);
	```
	The `ft_atoi_base()` function converts the initial portion of the string pointed to by `str` to an integer of type `int`, using the base specified by `base`.

- **`ft_list_push_front`:**
	```c
	void ft_list_push_front(t_list **begin_list, void *data);
	```
	The `ft_list_push_front()` function adds a new element of type `t_list` to the beginning of the list.

- **`ft_list_size`:**
	```c
	int ft_list_size(t_list *begin_list);
	```
	The `ft_list_size()` function returns the number of elements in the list.

- **`ft_list_sort`:**
	```c
	void ft_list_sort(t_list **begin_list, int (*cmp)());
	```
	The `ft_list_sort()` function sorts the list’s elements by ascending order using the function `cmp` to compare data.

- **`ft_list_remove_if`:**
	```c
	void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *));
	```
	The `ft_list_remove_if()` function removes all elements from the list that are equal to `data_ref` using the function `cmp` and frees the corresponding element’s memory using the function `free_fct`.

## IV. Build project

- **Mandatory part:**
	```bash
	make
	```
- **Bonus part:**
	```bash
	make bonus
	```
- **Clean project:**
	```bash
	make clean
	```
- **Fclean project:**
	```bash
	make fclean
	```
- **Rebuild project:**
	```bash
	make re
	```
- **Run test:**
	```bash
	make test
	```
- **Run bonus test:**
	```bash
	make test_bonus
	```
- **Run all test:**
	```
	make all_test
	```

## V. Resources and Recommendations

- [NASM Tutorial](https://cs.lmu.edu/~ray/notes/nasmtutorial/)
- [x86_64 NASM Assembly Quick Reference](https://www.cs.uaf.edu/2017/fall/cs301/reference/x86_64.html)
- [Linux System Calls](https://filippo.io/linux-syscall-table/)
- [WRT ..plt](https://www.tortall.net/projects/yasm/manual/html/objfmt-elf64.html)
