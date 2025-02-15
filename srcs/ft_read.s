;ssize_t	ft_read(int fd, void *buf, size_t count);

section .text
	global ft_read
	extern __errno_location

	ft_read:
		xor rax, rax ; rax = 0 (syscall number for read)
		syscall

		test rax, -1 ; check for error
		js .errno

		ret

	.errno:
		mov rdi, rax ; rdi = error code
		call __errno_location wrt ..plt ; get errno location

		neg rdi ;rid = -error code
		mov [rax], edi ; errno = -error code

		mov rax, -1 ; return -1
		ret
