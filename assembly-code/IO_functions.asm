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

LerInteiro:
    enter 0,0
    push ebx
    push ecx
    push edx
    push edi

    mov eax, 3
    mov ebx, 0
    mov ecx, aux
    mov edx, aux_size
    int 80h

    xor ecx, ecx
    xor eax, eax
    mov ebx, aux

LerInteiro_Loop:
    mov dl, 0x0a
    cmp dl, [ebx + ecx]
    je Ler_Cont
    push eax
    shl eax, 3
    add eax, [esp]
    add eax, [esp]
    mov dl, 0x2d
    cmp dl, [ebx + ecx]
    je Ler_Negativo
    sub edx, edx
    mov dl, [ebx + ecx]
    sub edx, 0x30
    add eax, edx

Ler_Negativo:
    inc ecx
    jmp LerInteiro_Loop

Ler_Cont:
    mov dl, 0x2d
    cmp byte dl, [ebx]
    jne Ler_Positivo
    push eax
    xor eax, eax
    sub eax, [esp]
    add esp, 4

Ler_Positivo:
    pop edi
    pop edx
    pop ecx
    pop ebx
    leave
    ret

EscreverInteiro:
    enter 0,0
    pusha

    xor eax, eax
    xor edx, edx
    xor ecx, ecx
    xor edi, edi
    mov ebx, aux
    mov eax, [EBP + 8]

    cmp eax, 0
    jne Print_Negativo
    mov dl, 0
    add dl, 0x30
    mov byte [ebx], dl
    mov dl, [ebx]
    inc ecx
    jmp Print_Cont3

Print_Negativo:  
    test eax, 0x80000000
    je Print_Positivo
    xor eax, eax
    sub eax, [EBP + 8]
    mov byte [ebx], 0x2d 
    inc ebx
    mov edi, 1
    jmp Print_Loop

Print_Positivo:
    mov eax, [EBP + 8]

Print_Loop:
    xor edx, edx
    push ebx
    mov ebx, 10
    div ebx
    pop ebx

    cmp eax, 0
    jne Print_Cont
    cmp edx, 0
    je Print_Cont3

Print_Cont:  
    add edx, 0x30

    push ecx

PI32_Shift_R:
    cmp ecx, 0
    je Print_Cont2
    mov byte dh, [ebx + ecx - 1]
    mov byte [ebx + ecx], dh 
    dec ecx
    jmp PI32_Shift_R

Print_Cont2:  
    mov byte [ebx], dl
    pop ecx
    inc ecx
    jmp Print_Loop

Print_Cont3:
    cmp edi, 1
    jne Inteiro_Print
    inc ecx
    dec ebx

Inteiro_Print:  
    push ebx
    push ecx
    call Print_String
    add esp, 8
    popa
    leave
    ret