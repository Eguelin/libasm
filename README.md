# Libasm

## Résumé
- **Objectives**:
	- Familiarize yourself with assembly language.
- **Skills**:
	- Rigor
	- Imperative programming
- **Tools**:
	<div>
		<svg xmlns="http://www.w3.org/2000/svg" width=50 height=50 viewBox="0 0 128 128"><path fill="#659ad3" d="M115.4 30.7L67.1 2.9c-.8-.5-1.9-.7-3.1-.7s-2.3.3-3.1.7l-48 27.9c-1.7 1-2.9 3.5-2.9 5.4v55.7c0 1.1.2 2.4 1 3.5l106.8-62c-.6-1.2-1.5-2.1-2.4-2.7"/><path fill="#03599c" d="M10.7 95.3c.5.8 1.2 1.5 1.9 1.9l48.2 27.9c.8.5 1.9.7 3.1.7s2.3-.3 3.1-.7l48-27.9c1.7-1 2.9-3.5 2.9-5.4V36.1c0-.9-.1-1.9-.6-2.8z"/><path fill="#fff" d="M85.3 76.1C81.1 83.5 73.1 88.5 64 88.5c-13.5 0-24.5-11-24.5-24.5s11-24.5 24.5-24.5c9.1 0 17.1 5 21.3 12.5l13-7.5c-6.8-11.9-19.6-20-34.3-20c-21.8 0-39.5 17.7-39.5 39.5s17.7 39.5 39.5 39.5c14.6 0 27.4-8 34.2-19.8z"/></svg>
		<svg xmlns="http://www.w3.org/2000/svg" width=50 height=50 viewBox="0 0 256 256"><path fill="#113b6a" d="M230.45 0c-14.117 0-25.557 11.443-25.557 25.554c0 4.962 1.438 9.578 3.885 13.498l-16.27 16.27c-20.44-18.498-47.544-29.768-77.283-29.768C51.59 25.554 0 77.145 0 140.78c0 63.637 51.59 115.223 115.225 115.223s115.224-51.586 115.224-115.223c0-29.738-11.271-56.843-29.77-77.285l16.273-16.27c3.92 2.445 8.537 3.884 13.5 3.884C244.56 51.108 256 39.667 256 25.556S244.56 0 230.45 0"/><path fill="#fff" d="M61.574 160.175q-.267.498-1.34.497h-8.418q-1.684-.001-1.683-1.607q0-3.369.015-6.702l.022-3.325c.026-3.315.036-6.66.036-10.027q0-3.214-1.11-4.553t-3.558-1.339q-1.838 0-3.98.88q-2.141.881-3.52 1.34v23.728q0 .61-.27 1.11q-.267.498-1.339.497h-8.341q-.995 0-1.34-.422c-.23-.278-.344-.676-.344-1.185v-34.445q0-.764.344-1.224q.345-.46 1.34-.46h8.341c.713 0 1.161.182 1.34.537q.27.536.269 1.147v1.838q.048 0 .083.017l.028.021q.04.038.116.037q2.527-1.913 5.894-3.098q3.366-1.186 6.122-1.187q4.058 0 6.39 1.339q2.337 1.34 3.485 3.521t1.415 4.862q.27 2.677.27 5.356v21.739q.005.61-.267 1.108m29.513-4.096a18.7 18.7 0 0 1-3.29 2.372a23 23 0 0 1-3.599 1.646a20 20 0 0 1-3.598.917q-1.762.267-3.214.268q-3.368 0-5.474-.958q-2.106-.956-3.252-2.488q-1.15-1.53-1.568-3.56a20 20 0 0 1-.41-3.512l-.011-.736c-.053-2.347.267-4.334.958-5.97q1.033-2.449 2.946-3.942c1.274-.993 2.832-1.71 4.67-2.143q2.754-.65 6.122-.65h8.803v-1.225c0-.816-.092-1.505-.267-2.066a2.7 2.7 0 0 0-.995-1.378q-.728-.535-2.028-.804q-1.14-.235-2.922-.265l-.522-.004q-.507 0-1.164.029l-3.581.203q-1.38.075-2.757.23q-1.034.116-1.937.187l-1.248.096q-1.06.065-1.445-.053q-.498-.155-.804-1.303l-.841-3.979q-.154-.993.267-1.645q.42-.649 2.182-1.34q1.3-.459 3.023-.804a51 51 0 0 1 3.521-.573a58 58 0 0 1 3.562-.344a47 47 0 0 1 3.061-.114q5.356 0 8.61.995q3.252.994 4.975 2.83c1.149 1.224 1.9 2.733 2.259 4.518q.535 2.678.537 6.123v12.092q-.002 1.226.115 1.914q.112.69.42 1.033c.202.231.482.4.839.497q.43.126 1.103.198l.351.033q.996.079 1.301.344q.308.27.308.957v4.9q-.001 1.42-1.915 1.919l-.306.07q-2.144.538-4.746.538c-1.887 0-3.548-.322-4.976-.957q-2.142-.956-2.908-4.02zM89.94 144.75h-6.887q-2.145 0-3.37.995q-1.225.996-1.225 3.675q0 1.762.727 2.448q.728.688 2.72.69q1.757 0 4.096-.842q2.334-.839 3.94-1.836zm50.293 4.013q0 3.59-1.416 5.993a11 11 0 0 1-3.789 3.857q-2.375 1.45-5.395 2.1q-3.023.646-6.315.647q-1.377 0-2.985-.112a51 51 0 0 1-6.39-.874a23 23 0 0 1-2.642-.684q-1.914-.683-2.447-1.406q-.478-.64-.228-1.91l.915-3.971q.23-1.07.69-1.3q.401-.2 1.448-.05l.313.05q2.676.46 5.815.728q3.14.269 5.13.268q2.906 0 4.133-.653q1.224-.651 1.224-2.187q0-1.688-.916-2.264q-.92-.575-3.37-.881a81 81 0 0 1-5.857-1.074q-2.716-.614-4.781-1.844a8.96 8.96 0 0 1-3.254-3.3q-1.186-2.071-1.185-5.447q-.001-3.069 1.178-5.371a10.9 10.9 0 0 1 3.23-3.834c1.368-1.025 3.006-1.79 4.909-2.305q2.851-.766 6.22-.766q1.302 0 2.873.116a73 73 0 0 1 3.175.308q1.608.195 3.1.501q1.492.31 2.717.773q1.531.539 2.257 1.12q.728.577.344 2.045l-.84 3.935q-.305 1.074-.651 1.306q-.306.203-1.368.106l-2.357-.28l-.75-.093a62 62 0 0 0-3.024-.308l-2.132-.15q-.337-.022-.662-.04l-.98-.049l-.444-.015l-.796-.012q-2.91-.075-3.637.649q-.726.722-.727 1.946q0 1.45 1.346 1.869q1.346.421 3.42.8q2.995.384 5.686.955q2.688.574 4.724 1.871q2.034 1.297 3.266 3.474q1.224 2.174 1.225 5.763m61.506 11.411q-.27.498-1.262.497h-8.418q-.998 0-1.341-.422c-.23-.278-.345-.676-.345-1.185v-20.13q0-3.521-1.072-4.67q-1.07-1.148-3.213-1.148q-1.378.001-3.37.728q-1.988.725-3.444 1.493v23.727q0 .61-.267 1.11q-.266.499-1.34.497h-8.418c-.615 0-1.033-.14-1.264-.422c-.229-.278-.344-.676-.344-1.185v-20.361q.001-3.215-1.039-4.401q-1.043-1.187-3.122-1.187q-1.39 0-3.354.689q-1.967.69-3.584 1.531v23.727q0 .611-.306 1.11q-.301.498-1.367.497h-8.362q-.916 0-1.258-.421c-.229-.278-.339-.677-.339-1.186V124.62c0-.51.11-.918.34-1.224q.34-.46 1.257-.46h8.362c.71 0 1.166.182 1.367.537q.305.535.306 1.147v1.76l.154.077a19.5 19.5 0 0 1 5.355-3.098q2.909-1.11 5.896-1.11q3.442 0 6.046 1.262c1.732.841 3.01 2.158 3.825 3.943q2.68-2.22 6.084-3.712q3.406-1.493 6.85-1.493q4.059 0 6.316 1.34t3.367 3.482q1.11 2.143 1.341 4.822a63 63 0 0 1 .23 5.357v21.816a2.25 2.25 0 0 1-.267 1.11"/></svg>
	</div>

## Table of Contents

1. [Introduction NASM](#i-introduction-nasm)
2. [Mandatory Part](#ii-mandatory-part)
	- [ft_strlen](#ft_strlen)
	- [ft_strcpy](#ft_strcpy)
	- [ft_strcmp](#ft_strcmp)
	- [ft_write](#ft_write)
	- [ft_read](#ft_read)
	- [ft_strdup](#ft_strdup)
3. [Bonus Part](#iii-bonus-part)
	- [ft_atoi_base](#ft_atoi_base)
	- [ft_list_push_front](#ft_list_push_front)
	- [ft_list_size](#ft_list_size)
	- [ft_list_sort](#ft_list_sort)
	- [ft_list_remove_if](#ft_list_remove_if)
4. [Build Project](#iv-build-project)
5. [My Ressurces](#v-my-ressurces)

## I. Introduction NASM

## II. Mandatory Part

The goal of this project is to familiarize yourself with the assembly language.

- The library must be named `libasm.a`.

- Submit a `main` that will test the functions and compile with the library to show that it works.

- the code must be written in 64-bit assembly `syntax Intel` and respect the calling convention.

- The `Makefile` must contain at least the following rules: `$(NAME)`, `all`, `clean`, `fclean`, and `re`.

- Use of the `-no-pie` compilation flag is prohibited.

### Mandatory Functions:

#### ft_strlen:
```c
size_t ft_strlen(const char *s);
```
The `ft_strlen()` function calculates the length of the string `s`, excluding the terminating null byte (`'\0'`).

For more info: `man 3 strlen`

---

#### ft_strcpy:
```c
char *ft_strcpy(char *dst, const char *src);
```
The `ft_strcpy()` function copies the string `src` to `dst` (including the terminating null byte (`'\0'`)).

For more info: `man 3 strcpy`

---

#### ft_strcmp:
```c
int ft_strcmp(const char *s1, const char *s2);
```
The `ft_strcmp()` function compares the two strings `s1` and `s2`. It returns an integer less than, equal to, or greater than zero if `s1` is found, respectively, to be less than, to match, or be greater than `s2`.

For more info: `man 3 strcmp`

---

#### ft_write:
```c
ssize_t ft_write(int fd, const void *buf, size_t count);
```
The `ft_write()` function writes `count` bytes from buffer `buf` to the file descriptor `fd`. On success, the number of bytes written is returned. On error, `-1` is returned, and `errno` is set appropriately.

For more info: `man 2 write`

---

#### ft_read:
```c
ssize_t ft_read(int fd, void *buf, size_t count);
```
The `ft_read()` function reads `count` bytes from file descriptor `fd` into the buffer starting at `buf`. On success, the number of bytes read is returned. On error, `-1` is returned, and `errno` is set appropriately.

For more info: `man 2 read`

---

#### ft_strdup:
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

#### ft_atoi_base:
```c
int ft_atoi_base(const char *str, int base);
```
The `ft_atoi_base()` function converts the initial portion of the string pointed to by `str` to an integer of type `int`, using the base specified by `base`.

---

#### ft_list_push_front:
```c
void ft_list_push_front(t_list **begin_list, void *data);
```
The `ft_list_push_front()` function adds a new element of type `t_list` to the beginning of the list.

---

#### ft_list_size:
```c
int ft_list_size(t_list *begin_list);
```
The `ft_list_size()` function returns the number of elements in the list.

---

#### ft_list_sort:
```c
void ft_list_sort(t_list **begin_list, int (*cmp)());
```
The `ft_list_sort()` function sorts the list’s elements by ascending order using the function `cmp` to compare data.

---

#### ft_list_remove_if:
```c
void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *));
```
The `ft_list_remove_if()` function removes all elements from the list that are equal to `data_ref` using the function `cmp` and frees the corresponding element’s memory using the function `free_fct`.

## IV. Build project

- Mandatory part:
	```bash
	make
	```
- Bonus part:
	```bash
	make bonus
	```
- Clean project:
	```bash
	make clean
	```
- Fclean project:
	```bash
	make fclean
	```
- Rebuild project:
	```bash
	make re
	```
- Run test:
	```bash
	make test
	```
- Run bonus test:
	```bash
	make test_bonus
	```
- Run all test
	```
	make all_test
	```

## V. My Ressurces

- [NASM Tutorial](https://cs.lmu.edu/~ray/notes/nasmtutorial/)
- [x86_64 NASM Assembly Quick Reference](https://www.cs.uaf.edu/2017/fall/cs301/reference/x86_64.html)
- [Linux System Calls](https://filippo.io/linux-syscall-table/)

