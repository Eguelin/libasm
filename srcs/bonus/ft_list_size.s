;int	ft_list_size(t_list *begin_list);

section .text
	global ft_list_size

		ft_list_size:
			xor eax, eax ; set return value to 0

		.loop:
			test rdi, rdi ; check if list is NULL
			je .end ; if so, jump to end

			inc eax ; eax++

			mov rdi, [rdi + 8] ; rdi = rdi->next
			jmp .loop

		.end:
			ret

section .note.GNU-stack
