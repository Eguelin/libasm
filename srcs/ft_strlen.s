;size_t	ft_strlen(const char *s);

section .text
	global ft_strlen

		ft_strlen:
			xor	rax, rax ; return = 0

		loop:
			cmp byte [rdi], 0 ; if *s == 0
			je return
			inc rax ; return++
			inc rdi ; s++
			jmp loop

		return:
			ret

