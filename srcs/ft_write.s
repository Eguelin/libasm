;ssize_t	ft_write(int fd, const void *buf, size_t count);

section .text
	global ft_write
	extern __errno_location

		ft_write:
			mov rax, 1 ; syscall number for write
			syscall

			cmp rax, 0 ; check for error
			jl errno

			ret

		errno:
			mov rdi, rax ; save error code
			call __errno_location wrt ..plt ; get errno location

			neg rdi ; negate error code
			mov [rax], edi ; store error code in errno

			mov rax, -1 ; return -1
			ret
