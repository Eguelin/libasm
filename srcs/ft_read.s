;ssize_t	ft_read(int fd, void *buf, size_t count);

section .text
	global ft_read
	extern __errno_location

		ft_read:
			mov rax, 0 ; syscall number for read
			syscall

			cmp rax, 0 ; check for error
			jl .errno

			ret

		.errno:
			mov rdi, rax ; rdi = error code
			call __errno_location wrt ..plt ; get errno location

			neg rdi ;rid = -error code
			mov [rax], edi ; errno = -error code

			mov rax, -1 ; return -1
			ret

section .note.GNU-stack
