LerChar:
    ENTER 0,0
    PUSHA
    MOV EAX, 3 ; Código de leitura
    MOV EBX, 0 ; STDIN
    MOV ECX, [EBP + 8] ; Referência do char
    MOV EDX, 1 ; Tamanho do char
    INT 80h
    POPA
    LEAVE
    RET

EscreverChar:
    ENTER 0,0
    PUSHA
    MOV EAX, 4 ; Código de escrita
    MOV EBX, 1
    MOV ECX, [EBP + 8] ; Referência do char
    MOV EDX, 1 ; Tamanho em Bytes
    INT 80h
    POPA
    LEAVE
    RET

LerString:
    enter 0,0

    push ebx
    push ecx
    push edx

    mov eax,0
    mov edx, [EBP + 8]
    add edx, 1
Loop_Leitura:
    mov ecx,[EBP + 12]
    mov ebx,eax
    add ecx,ebx
    push ecx
    call LerChar
    add esp,4
    inc eax
    cmp dword [ecx], 0xa
    je  Saida
    cmp eax, edx
    jne Loop_Leitura
Saida:
    mov dword [ecx], 0

    pop edx
    pop ecx
    pop ebx

    add esp, 4
    leave
    ret

EscreverString:
    enter 0,0
    mov eax, 4
    mov ebx, 1
    mov ecx, [EBP + 12]
    mov edx, [EBP + 8]
    int 80h
    leave
    ret

