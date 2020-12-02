# Tradutor do Assembly Inventado para Assembly IA-32

O programa tradutor.cpp deve receber como entrada um arquivo .asm na linguagem
hipotética de sala de aula, seguindo a especificação do trabalho e retornar um arquivo .s traduzindo para o assembly IA-32

____
## Compilar e Traduzir
make
./tradutor nome_arquivo.asm
____
## Montar
nasm -f elf -o nome_arquivo.o nome_arquivo.s
____

## Ligar
ld -m elf_i386 -o nome_executavel nome_arquivo.o
____