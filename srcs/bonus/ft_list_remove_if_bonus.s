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

		push rbx
		push r12
		push r13
		push r14
		push r15

		mov rbx, rdi ; rbx = begin_list
		mov r12, [rdi] ; r12 = *begin_list
		mov r13, rdx ; r13 = cmp
		mov r14, rcx ; r14 = free_fct
		xor r15, r15 ; r15 = NULL

	.loop:
		push rsi

		mov rdi, [r12] ; rdi = rdi->data
		call r13 ; cmp(rdi, data_ref)

		test eax, eax ; if(cmp(rdi, data_ref) != 0)
		jne .no_free

		mov rdi, r12 ; rdi = r12
		mov r12, [r12 + 8] ; r12 = r12->next

		test r15, r15 ; if(r15 != NULL)
		jne .free

		mov [rbx], r12 ; *begin_list = r12
		call r14 ; free_fct(rdi)

		jmp .next

	.free:
		call r14 ; free_fct(rdi)

		mov [r15 + 8], r12 ; r15->next = r12

		jmp .next

	.no_free:
		mov r15, r12 ; r15 = r12
		mov r12, [r12 + 8] ; r12 = r12->next

	.next:
		pop rsi

		test r12, r12 ; if(r12 != NULL)
		jne .loop

		pop r15
		pop r14
		pop r13
		pop r12
		pop rbx

	.end:
		ret
