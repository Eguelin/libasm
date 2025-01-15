;size_t	ft_strlen(const char *s);

section .text
	global ft_strlen

	ft_strlen:
		xor rax, rax ; rax = 0

	.loop:
		cmp byte [rdi + rax], 0 ; if (s[rax] == '\0')
		je .end
		inc rax ; rax++
		jmp .loop

	.end:
		ret
