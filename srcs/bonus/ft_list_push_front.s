;void	ft_list_push_front(t_list **begin_list, void *data);

section .text
	global ft_list_push_front
	extern malloc

	ft_list_push_front:
		cmp rdi, 0 ; if (begin_list == NULL)
		je .end

	.create_elem:
		push rdi
		push rsi

		mov rdi, 16	;size of t_list
		call malloc wrt ..plt ;malloc(sizeof(t_list))

		pop rsi
		pop rdi

		test rax, rax ;check if malloc failed
		jz .end

		mov [rax], rsi ;new_elem->data = data
		mov rsi, [rdi]
		mov [rax + 8], rsi ;new_elem->next = *begin_list
		mov	[rdi], rax ;*begin_list = new_elem

	.end:
		ret
