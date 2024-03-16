;int	ft_strcmp(const char *s1, const char *s2);

section .text
	global ft_strcmp

		ft_strcmp:
			xor eax, eax

		loop:
			mov ah, byte [rdi]

			cmp ah, byte [rsi]
			jne diff

			test ah, ah
			jz return

			inc rdi
			inc rsi
			jmp loop

		diff:
			sub	ah, byte [rsi]
			movsx eax, ah

		return:
			ret
