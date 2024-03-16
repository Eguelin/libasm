;ssize_t	ft_write(int fd, const void *buf, size_t count);

section .text
	global ft_write
	extern __errno_location

		ft_write:
			mov rax, 1
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
