;int	ft_atoi_base(char *str, char *base);
section .rodata
	white_space:
		times 9 db 0
		db 1, 1, 1, 1, 1 ; '\t', '\n', '\v', '\f', '\r'
		times 18 db 0
		db 1 ; ' '
		times 223 db 0

section .bss
	base_set resb 256

section .text
	global	ft_atoi_base
	extern	ft_strlen

	ft_atoi_base:
		xor eax, eax ; set return value to 0
		test rdi, rdi ; if (str == NULL)
		jz .end
		test rsi, rsi ; if (base == NULL)
		jz .end

		push rdi

		mov rdi, rsi ; rdi = base
		call ft_strlen ; eax = strlen(base)
		mov edx, eax ; edx = eax

		pop rdi

		xor rax, rax ; set return value to 0

		cmp edx, 1 ; if (strlen(base) <= 1)
		jle .end

		xor r8, r8 ; r8 = 0
		xor r9, r9 ; r9 = 0
		lea r11 , [rel base_set] ; r11 = base_set
		lea r10, [rel white_space] ; r10 = white_space

	.reset_base_set:
		cmp r9, 256 ; if (r9 == 256)
		je .loop_check

		mov byte [r11 + r9], -1 ; base_set[i] = -1
		inc r9 ; i++
		jmp .reset_base_set

	.loop_check:
		cmp byte [rsi + r8], 0 ; if (base[i] == 0)
		je .start_atoi

		xor r9, r9 ; r9 = 0

		mov r9b, byte [rsi + r8] ; r9b = base[i]
		cmp byte [r10 + r9], 1 ; if (white_space[base[i]] == 0)
		je .end

		cmp r9b, 45 ; if (str[0] == '-')
		je .end

		cmp r9b, 43 ; if (str[0] == '+')
		je .end

		cmp byte [r11 + r9], -1 ; if (base_set[base[i]] == 1)
		jne .end

		mov byte [r11 + r9], r8b ; base_set[base[i]] = 1

		inc r8 ; i++
		jmp .loop_check

	.start_atoi:
		xor r8, r8 ; r8 = 0

	.skip_spaces:
		mov r9b, byte [rdi] ; r9b = *str
		cmp byte [r10 + r9], 0 ; if (white_space[*str] == 0)
		je .check_sign

		inc rdi ; str++
		jmp .skip_spaces

	.check_sign:
		cmp byte [rdi], 45 ; if (str[0] == '-')
		je .negative

		cmp byte [rdi], 43 ; if (str[0] == '+')
		je .positive

		jmp .loop_atoi

	.negative:
		inc rdi ; str++
		cmp r8, 1 ; if (r8 == 1)
		je .start_atoi
		mov r8, 1 ; r8 = 1
		jmp .check_sign

	.positive:
		inc rdi ; str++
		jmp .check_sign

	.loop_atoi:
		xor ecx, ecx ; ecx = 0
		mov r9b, byte [rdi] ; r9b = *str
		mov cl, byte [r11 + r9] ; cl = base_set[*str]
		cmp cl, -1 ; if (base_set[*str] == -1)
		je .end_atoi

	.base_end:
		push rdx ; save strlen(base)
		mul edx; ea\dx *= strlen(base)
		pop rdx ; restore strlen(base)

		add eax, ecx ; eax += ecx
		inc rdi ; str++

		cmp byte [rdi], 0 ; if (*str == 0)
		jne .loop_atoi

	.end_atoi:
		cmp r8, 1 ; if (r8 == 1)
		jne .end

		neg eax ; eax = -eax

	.end:
		ret
