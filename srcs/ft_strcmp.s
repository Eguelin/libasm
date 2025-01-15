;int	ft_strcmp(const char *s1, const char *s2);

section .text
	global ft_strcmp

	ft_strcmp:
		xor eax, eax ; eax = 0
		xor rcx, rcx ; rcx = 0

	.loop:
		mov al, [rdi + rcx] ; al = *s1

		cmp al, [rsi + rcx] ; if (*s1 == *s2)
		jne .diff

		test al, al ; if (*s1 == 0)
		jz .end

		inc rcx ; rcx++
		jmp .loop

	.diff:
		xor edx, edx ; edx = 0
		mov dl, [rsi + rcx] ; dl = *s2
		sub eax, edx ; eax = (int)al - (int)dl

	.end:
		ret

section .note.GNU-stack
