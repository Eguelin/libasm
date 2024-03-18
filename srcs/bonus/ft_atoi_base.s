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

		check_base:
			cmp edx, 1 ; if (strlen(base) <= 1)
			jle return

		start:
			xor r8, r8 ; r8 = 0

		check_sign:
			cmp byte [rdi], 45 ; if (str[0] == '-')
			je negative

			cmp byte [rdi], 43 ; if (str[0] == '+')
			je positive

			jmp loop

		negative:
			inc rdi ; str++
			cmp r8, 1 ; if (r8 == 1)
			je start
			mov r8, 1 ; r8 = 1
			jmp check_sign

		positive:
			inc rdi ; str++
			jmp check_sign

		loop:
			xor rcx, rcx ; ecx = 0
			mov r9b, byte [rdi] ; r9b = *str

		base_loop:
			cmp r9b, byte [rsi + rcx] ; if (*str == base[i])
			je base_end

			inc rcx ; i++
			cmp byte [rsi + rcx], 0 ; if (base[i] == 0)
			je end

			jmp base_loop

		base_end:
			push rdx ; save strlen(base)
			mul edx; eax *= strlen(base)
			pop rdx ; restore strlen(base)

			add eax, ecx ; eax += ecx
			inc rdi ; str++

			cmp byte [rdi], 0 ; if (*str == 0)
			jne loop

		end:
			cmp r8, 1 ; if (r8 == 1)
			jne return

			neg eax ; eax = -eax

		return:
			ret
