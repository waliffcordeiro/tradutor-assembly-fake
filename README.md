# Tradutor do Assembly Inventado para Assembly IA-32

O programa tradutor.cpp deve receber como entrada um arquivo .asm na linguagem
hipotética de sala de aula, seguindo a especificação do trabalho e retornar um arquivo .s traduzindo para o assembly IA-32

____
## Montagem
nasm -f elf -o arquivo.o arquivo.s
____

## Ligação
ld -m elf_i386 -o nome_executavel arquivo.o
____