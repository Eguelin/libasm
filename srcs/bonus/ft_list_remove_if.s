;void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *));

section .text
	global ft_list_remove_if

		ft_list_remove_if:
			test rdi, rdi ; if(begin_list == NULL)
			je .end

			cmp qword [rdi], 0 ; if (*begin_list == NULL)
			je .end

			test rdx, rdx ; if(cmp == NULL)
			je .end

			test rcx, rcx ; if(free_fct == NULL)
			je .end

			mov r8, rdi ; r8 = begin_list
			mov rdi, [rdi] ; rdi = *begin_list

		.loop:
			push rsi
			push rdx
			push rcx
			push rdi
			push r8

			mov rdi, [rdi] ; rdi = rdi->data
			call rdx ; cmp(rdi, data_ref)

			test eax, eax ; if(cmp(rdi, data_ref) != 0)
			jne .next

			pop r8
			pop rdi
			pop rcx

			cmp rdi, [r8] ; if(rdi != *begin_list)
			jne .free

			mov rsi, [rdi + 8] ; rsi = rdi->next
			mov [r8], rsi ; *begin_list = rsi

		.free:
			mov rsi, [rdi + 8] ; rsi = rdi->next

			push rcx
			push rsi
			push r8

			call rcx ; free_fct(rdi)

		.next:
			pop r8
			pop rdi
			pop rcx
			pop rdx
			pop rsi

			test eax, eax ; if(cmp(rdi, data_ref) == 0)
			je .check_first

			mov r8, rdi ; r8 = rdi
			mov rdi, [rdi + 8] ; rdi = rdi->next

			jmp .end_loop

		.check_first:
			cmp rdi, [r8] ; if(rdi == *begin_list)
			je .end_loop

			mov [r8 + 8], rdi ; r8->next = rdi

		.end_loop:
			test rdi, rdi ; if(rdi != NULL)
			jne .loop

		.end:
			ret

