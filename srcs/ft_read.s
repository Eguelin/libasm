;ssize_t	ft_read(int fd, void *buf, size_t count);

section .text
	global ft_read
	extern __errno_location

		ft_read:
			mov rax, 0
			syscall

			cmp rax, 0
			jl errno

			ret

		errno:
			mov rdi, rax
			call __errno_location wrt ..plt

			neg rdi
			mov dword [rax], edi

			mov rax, -1
			ret
