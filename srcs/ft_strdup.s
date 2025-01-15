;char	*ft_strdup(const char *s);

section .text
	global ft_strdup
	extern malloc
	extern ft_strlen
	extern ft_strcpy

	ft_strdup:
		push rdi ; save pointer to string

		call ft_strlen ; ft_strlen(rdi)
		add rax, 1 ; length++

		mov rdi, rax ; rdi = length
		call malloc wrt ..plt ; malloc(rdi)

		pop rsi ; restore pointer to string

		test rax, rax ; check if malloc failed
		jz .end

		mov rdi, rax ; rdi = malloc(length)
		call ft_strcpy ; ft_strcpy(rdi, rsi)

	.end:
		ret
