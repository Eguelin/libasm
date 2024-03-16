;char	*ft_strdup(const char *s);

section .text
	global ft_strdup
	extern malloc
	extern ft_strlen
	extern ft_strcpy

		ft_strdup:
			push rdi

			call ft_strlen
			add rax, 1

			mov rdi, rax
			call malloc wrt ..plt

			test rax, rax
			jz return

			pop rdi

			mov rsi, rdi
			mov rdi, rax

			call ft_strcpy

		return:
			ret

