;char	*ft_strcpy(char *dest, const char *src);

section .text
	global ft_strcpy

		ft_strcpy:
			mov rax, rdi

		loop:
			mov	dl, byte [rsi]
			mov byte [rdi], dl

			test dl, dl
			jz return

			inc rdi
			inc rsi
			jmp loop

		return:
			ret
