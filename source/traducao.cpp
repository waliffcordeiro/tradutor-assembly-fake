#include "../include/traducao.hpp"


void print_traducao(vector<string> traducao, string nome_arquivo, vector<string> *bss, vector<string> *data) {
    
    ofstream saida(nome_arquivo);

    saida << "global _start" << endl;

    /* Funções Assembly */

    saida << endl;
    /* Section Data */
    saida << "section .data" << endl;
    vector<string> palavras_data;
    for(auto linha: *data) {
        palavras_data = split(linha, ' ', '\t');
        palavras_data[0].pop_back(); // Retirando :
        saida << palavras_data[0] + " DD " + palavras_data[2] << endl; 
    }
    
    saida << endl;
    /* Section Bss */
    saida << "section .bss" << endl;
    vector<string> palavras_bss;
    for(auto linha: *bss) {
        palavras_bss = split(linha, ' ', '\t');
        palavras_bss[0].pop_back(); // Retirando :
        saida << palavras_bss[0] + " RESB " + palavras_bss[2] << endl; 
    }

    saida << endl;
    /* Section Text */
    saida << "section .text" << endl;
    saida << "_start:" << endl << endl;

    for(auto linha_traduzida: traducao) {
        saida << linha_traduzida + "\n";
    }

    saida << endl << endl;
    saida << input_output();
}

string input_output() {
    return (string("LerChar:\n") +
    string("enter 0,0\n") +
    string("mov eax, 3 ; Código de leitura \n") +
    string("mov ebx, 0 ; STDIN\n") +
    string("mov ecx, [EBP + 8]; Ponteiro baseado na pilha (parâmetro por push)\n") +
    string("mov edx, 1 ; Tamanho em Bytes\n") +
    string("int 80h\n") +
    string("leave\n") +
    string("ret 4\n\n") +

    string("EscreverChar:\n") +
    string("enter 0,0\n") +
    string("mov eax, 4 ; Código de escrita\n") +
    string("mov ebx, 1\n") +
    string("mov ecx, [EBP + 8]; Ponteiro baseado na pilha (parâmetro por push)\n") +
    string("mov edx, 1 ; Tamanho em Bytes\n") + 
    string("int 80h\n") +
    string("leave\n") +
    string("ret 4\n"));
}

vector<string> traducao(vector<string> *text) {
    vector<string> linhas_traduzidas;
    string aux_linha;

    /* Section Data */
    
    /* Section Bss */

    /* Section Text */
    for(auto linha:*text) {
        metodo_equivalente(split(linha, ' ', '\t'), &linhas_traduzidas);    
    }
    return linhas_traduzidas;
}

void metodo_equivalente(vector<string> linha, vector<string> *final) {
    string linha_convertida;
    string acumulador = string("EBX, ");

    /* ADD */
    if(linha[0] == "ADD") {
        if(linha.size() == 2)
            linha_convertida = (string("ADD ") + acumulador + string("[") +
            linha[1] + "]");
        else {
            linha_convertida = (string("ADD ") + acumulador + string("[") +
             linha[1] + linha[2] + linha[3] + string("]"));
        }
        final->push_back(toUpperCase(linha_convertida));
    }
    /******************************/

    /* SUB */
    else if(linha[0] == "SUB") {
        if(linha.size() == 2)
            linha_convertida = (string("SUB ") + acumulador + string("[") +
            linha[1] + "]");
        else {
            linha_convertida = (string("SUB ") + acumulador + string("[") +
            linha[1] + linha[2] + linha[3] + string("]"));
        } 
        final->push_back(toUpperCase(linha_convertida));
    } 
    /******************************/

    /* STORE */
    else if (linha[0] == "STORE") {
        if(linha.size() == 2) {
            linha_convertida = (string("MOV ") + acumulador + string("[") + linha[1] + string("]"));
        } else {
            linha_convertida = (string("MOV ") + acumulador + string("[") + 
            linha[1] + linha[2] + linha[3] + string("]"));
        }
        final->push_back(toUpperCase(linha_convertida));
    }
    /******************************/

    /* COPY */
    else if(linha[0] == "COPY") {
        linha[1].pop_back(); // retirando a vírgula
        linha_convertida = (string("MOV ") + string("[") + 
        linha[1] + "]" + string(", ") + "[" + linha[2] + "]");
        final->push_back(toUpperCase(linha_convertida));
    }
    /******************************/

    /* COPY */
    else if(linha[0] == "LOAD") {
        if(linha.size() == 2) {
            linha_convertida = (string("MOV ") + acumulador + "[" + linha[1] + "]");
        } else {
            linha_convertida = (string("MOV ") + acumulador + "[" + linha[1] +
            linha[2] + linha[3] + "]");
        }
        final->push_back(toUpperCase(linha_convertida));
    }
    /******************************/

    /* JMP */
    else if(linha[0] == "JMP") {
        if(linha.size() == 2) {
            linha_convertida = (string("JMP " + linha[1]));
        } else {
            linha_convertida = (string("JMP " + linha[1] + linha[2] + linha[3]));
        }
        final->push_back(toUpperCase(linha_convertida));
    }
    /******************************/

    /* Jumps */
    else if(linha[0] == "JMPN" || linha[0] == "JMPP" || linha[0] == "JMPZ") {
        // Fazer ADD para jump com offset
        string jump, linha_aux;
        linha_aux = (string("CMP ") + acumulador + string("0"));

        if(linha[0] == "JMPN") 
            jump = "JL ";
        if(linha[0] == "JMPP")
            jump = "JG ";
        if(linha[0] == "JMPZ")
            jump = "JE ";

        if(linha.size() == 2) {
            linha_convertida = jump + linha[1];
        } else {
            linha_convertida = jump + linha[1] + linha[2] + linha[3];
        }

        final->push_back(toUpperCase(linha_aux));
        final->push_back(toUpperCase(linha_convertida));
    }
    /******************************/    

    /* DIV */
    else if(linha[0] == "DIV") {
        vector<string> linha_aux;
        acumulador.pop_back();
        acumulador.pop_back();
        linha_aux.push_back(string("MOV EAX, ") + string("[") + linha[1] + string("]"));
        linha_aux.push_back(string("CDQ"));
        linha_aux.push_back(string("IDIV ") + acumulador);
        final->push_back(toUpperCase(linha_aux[0]));
        final->push_back(toUpperCase(linha_aux[1]));
        final->push_back(toUpperCase(linha_aux[2]));
    }
    /******************************/

    /* MUL */
    else if(linha[0] == "MUL") {
        vector<string> linha_aux;
        acumulador.pop_back(); // Retirando,
        acumulador.pop_back();

        // Salvando 0 no EDX para verificar overflow
        // linha_aux.push_back(string("MOV EDX, 0"));

        linha_aux.push_back(string("MOV EAX, ") + string("[") + linha[1] + string("]"));
        linha_aux.push_back(string("IMUL ") + acumulador);
        
        final->push_back(toUpperCase(linha_aux[0]));
        final->push_back(toUpperCase(linha_aux[1]));

        // TO DO Overflow
    }
    /******************************/

    /* STOP */
    else if(linha[0] == "STOP") {
        vector<string> linha_aux;
        linha_aux.push_back(string("MOV EAX, 1"));
        linha_aux.push_back(string("INT 80h"));
        final->push_back(toUpperCase(linha_aux[0]));
        final->push_back(toUpperCase(linha_aux[1]));
        /* TODO Tratar Overflow*/
    }
    /******************************/

    /* Input e Output de char */
    else if(linha[0] == "C_INPUT") { // Input Char
        vector<string> linha_aux;
        // TO DO add no endereço
        if(linha.size() == 2) {
            linha_aux.push_back(string("push ") + linha[1]);
            linha_aux.push_back(string("CALL LerChar "));
            final->push_back(toUpperCase(linha_aux[0]));
            final->push_back(linha_aux[1]);
        }
    }
    else if(linha[0] == "C_OUTPUT") { // Ouput Char
        vector<string> linha_aux;
        // TO DO add no endereço
        if(linha.size() == 2) {
            linha_aux.push_back(string("push ") + linha[1]);
            linha_aux.push_back(string("CALL EscreverChar "));
            final->push_back(toUpperCase(linha_aux[0]));
            final->push_back(linha_aux[1]);
        }
    }


}
