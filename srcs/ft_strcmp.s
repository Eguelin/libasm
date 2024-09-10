;int	ft_strcmp(const char *s1, const char *s2);

section .text
	global ft_strcmp

	ft_strcmp:
		mov ah, [rdi] ; ah = *s1

		cmp ah, [rsi] ; if (*s1 == *s2)
		jne .diff

		test ah, ah ; if (*s1 == 0)
		jz .end

		inc rdi ; s1++
		inc rsi ; s2++
		jmp ft_strcmp

	.diff:
		sub	ah, [rsi] ; ah = *s1 - *s2

	.end:
		movsx eax, ah ; eax = (int)ah
		ret

section .note.GNU-stack
