.code
DirectNtCreateProcess PROC
	mov r10, rcx
	mov eax, 0BEh
	syscall
	ret
DirectNtCreateProcess ENDP
END