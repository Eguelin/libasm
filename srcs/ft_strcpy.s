;char	*ft_strcpy(char *dest, const char *src);

section .text
	global ft_strcpy

		ft_strcpy:
			push rdx ; save rdx
			mov rax, rdi ; return = dest

		loop:
			mov	dl, [rsi] ; dl = *src
			mov [rdi], dl ; *dest = *src

			test dl, dl ; if (*src == 0)
			jz return

			inc rdi ; dest++
			inc rsi ; src++
			jmp loop

		return:
			pop rdx ; restore rdx
			ret
