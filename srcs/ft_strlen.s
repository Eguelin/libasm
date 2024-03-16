;size_t	ft_strlen(const char *s);

section .text
	global ft_strlen

		ft_strlen:
			xor	rax, rax

		loop:
			cmp byte [rdi], 0
			je return
			inc rax
			inc rdi
			jmp loop

		return:
			ret

