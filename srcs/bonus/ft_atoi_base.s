;int	ft_atoi_base(char *str, char *base);

section .text
	global	ft_atoi_base
	extern	ft_strlen

		ft_atoi_base:
			push rdi

			mov rdi, rsi ; rdi = base
			call ft_strlen ; eax = strlen(base)
			mov edx, eax ; edx = eax

			pop rdi

			xor eax, eax ; set return value to 0

		.check_base:
			cmp edx, 1 ; if (strlen(base) <= 1)
			jle .end

			xor r8, r8 ; r8 = 0

		.loop_check:
			cmp byte [rsi + r8], 0 ; if (base[i] == 0)
			je .start_atoi

			xor r9, r9 ; r9 = 0

			mov r10b, byte [rsi + r8] ; r10b = base[i]

			cmp r10b, 43 ; if (base[i] == '+')
			je .end

			cmp r10b, 45 ; if (base[i] == '-')
			je .end

			cmp r10b, 32 ; if (base[i] == ' ')
			je .end

			cmp r10b, 9 ; if (base[i] < '\t') else if (base[i] == '\t')
			jl .loop_check
			je .end

			cmp r10b, 13 ; if (base[i] <= '\r')
			jle .end

		.check_duplicate:

			cmp byte [rsi + r9], 0 ; if (base[j] == 0)
			je .check_duplicate_end

			cmp r9, r8 ; if (j == i)
			je .check_duplicate_inc

			cmp r10b , byte [rsi + r9] ; if (base[i] == base[j])
			je .end

		.check_duplicate_inc:
			inc r9 ; j++
			jmp .check_duplicate

		.check_duplicate_end:
			inc r8 ; i++
			jmp .loop_check

		.start_atoi:
			xor r8, r8 ; r8 = 0

		.skip_spaces:
			mov r9b, byte [rdi] ; r9b = *str

			cmp r9b, 32 ; if (base[i] == ' ')
			je .inc_str

			cmp r9b, 9 ; if (base[i] < '\t') else if (base[i] == '\t')
			jl .check_sign
			je .inc_str

			cmp r9b, 13 ; if (base[i] <= '\r')
			jle .inc_str

			jmp .check_sign

		.inc_str :
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
			xor rcx, rcx ; ecx = 0
			mov r9b, byte [rdi] ; r9b = *str

		.loop_base:
			cmp r9b, byte [rsi + rcx] ; if (*str == base[i])
			je .base_end

			inc rcx ; i++
			cmp byte [rsi + rcx], 0 ; if (base[i] == 0)
			je .end_atoi

			jmp .loop_base

		.base_end:
			push rdx ; save strlen(base)
			mul edx; eax *= strlen(base)
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

section .note.GNU-stack
