;void	ft_list_sort(t_list **begin_list, int (*cmp)());

section .text
	global ft_list_sort

		ft_list_sort:
			test rdi, rdi ; if (begin_list == NULL)
			je .end

			cmp qword [rdi], 0 ; if (*begin_list == NULL)
			je .end

			test rsi, rsi ; if (cmp == NULL)
			je .end

			push rbx
			push r12
			push r13
			push r14
			mov rbx, rdi ; rbx = begin_list
			mov r12, rsi ; r12 = cmp

		.start:
			xor r14, r14 ; r14 = 0
			mov r13, [rbx] ; r13 = *begin_list

		.sort:
			cmp qword [r13 + 8], 0 ; if (r13->next == NULL)
			je .restore

			mov rdi, [r13] ; rdi = r13->data
			mov rsi, [r13 + 8] ; rsi = r13->next
			mov rsi, [rsi] ; rsi = rsi->data
			call r12 ; cmp(r13->data, r13->next->data)

			cmp eax, 0 ; if (rax <= 0)
			jle .next

			mov rdi, r13 ; rdi = r13
			mov r13, [r13 + 8] ; r13 = r13->next

			test r14, r14 ; if (r14 == 0)
			je .swap_first

			mov [r14 + 8], r13 ;r14->next = r13

			jmp .swap

		.swap_first:
			mov [rbx], r13 ; begin_list = r13

		.swap:
			mov rsi, [r13 + 8] ; rsi = r13->next
			mov [rdi + 8], rsi ; rdi->next = rsi
			mov [r13 + 8], rdi ; r13->next = rdi
			jmp .start

		.next:
			mov r14, r13 ; r14 = list
			mov r13, [r13 + 8] ; r13 = list->next
			jmp .sort

		.restore:
			pop r14
			pop r13
			pop r12
			pop rbx

		.end:
			ret
