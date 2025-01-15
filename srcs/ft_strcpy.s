;char	*ft_strcpy(char *dest, const char *src);

section .text
	global ft_strcpy

	ft_strcpy:
		mov rax, rdi ; return = dest
		xor rcx, rcx ; rcx = 0

	.loop:
		mov	dl, [rsi + rcx] ; dl = *src
		mov [rdi + rcx], dl; *dest = *src

		test dl, dl ; if (*src == 0)
		jz .end

		inc rcx ; rcx++
		jmp .loop

	.end:
		ret

section .note.GNU-stack
