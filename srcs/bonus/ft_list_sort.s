;void	ft_list_sort(t_list **begin_list, int (*cmp)());

section .text
	global ft_list_sort

		ft_list_sort:
			cmp rdi, 0 ; if (begin_list == NULL)
			je .end

			cmp qword [rdi], 0 ; if (*begin_list == NULL)
			je .end

			cmp rsi, 0 ; if (cmp == NULL)
			je .end

		.start:
			push rdi
			mov rdx, [rdi] ; rdx = *begin_list

		.sort:
			cmp qword [rdx + 8], 0 ; if (begin_list->next == NULL)
			je .restore

			mov rcx, [rdx + 8] ; rcx = *begin_list->next

			push rsi
			mov rax, rsi ; rax = *cmp

			mov rdi, [rdx] ; rdi = *begin_list->data
			mov rsi, [rcx] ; rsi = *begin_list->next->data

			push rdx
			push rcx
			call rax ; cmp(begin_list->data, begin_list->next->data)
			pop rcx
			pop rdx
			pop rsi

			cmp eax, 0 ; if (rax <= 0)
			jle .next

			mov rax, [rdx] ; rax = *begin_list->data
			mov r8, [rcx] ; r8 = *begin_list->next->data

			mov [rdx], r8 ; *begin_list->data = *begin_list->next->data
			mov [rcx], rax ; *begin_list->next->data = *begin_list->data

			pop rdi
			jmp .start

		.next:
			mov rdx, rcx ; begin_list = begin_list->next
			jmp .sort

		.restore:
			pop rdi

		.end:
			ret
