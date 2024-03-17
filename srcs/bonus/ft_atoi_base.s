;int	ft_atoi_base(char *str, char *base);

section .text
	global	ft_atoi_base
		ft_atoi_base:
			xor rax, rax ; set return value to 0

		start:
			xor rdx, rdx ; rdx = 0

		check_sign:
			cmp byte [rdi], 45 ; if (str[0] == '-')
			je negative
			cmp byte [rdi], 43 ; if (str[0] == '+')
			je positive
			jmp loop

		negative:
			cmp rdx, 1 ; if (rdx == 1)
			je start
			mov rdx, 1 ; rdx = 1

		positive:
			inc rdi ; str++
			jmp check_sign

		loop:
			push rsi ; save base

			xor rcx, rcx ; ecx = 0
			mov r8b, byte [rsi] ; r8b = *base

		base_loop:
			cmp r8b, byte [rdi] ; if (r8b == *str)
			je base_end

			inc rsi ; base++
			inc rcx ; i++
			cmp r8b, 0 ; if (*base == 0)
			je end

			jmp base_loop

		base_end:
			imul rax, rax, 10 ; rax *= 10
			add rax, rcx ; rax += rcx
			inc rdi ; str++

			pop rsi ; restore base

			cmp byte [rdi], 0 ; if (*str == 0)
			jne loop

		end:
			cmp rdx, 1 ; if (rdx == 1)
			jne return

			neg rax ; rax = -rax

		return:
			ret
