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
        if(palavras_bss[0].back() == ':') {
            palavras_bss[0].pop_back(); // Retirando :
        }
        saida << palavras_bss[0] + " RESB " + palavras_bss[2] << endl; 
    }
    saida << "aux resb 12\naux_size EQU 12" << endl;

    saida << endl;
    /* Section Text */
    saida << "section .text" << endl;
    saida << "_start:" << endl << endl;

    for(auto linha_traduzida: traducao) {
        saida << linha_traduzida + "\n";
    }

    saida << endl << endl;

    /* Pegando funções assembly de input e output */

    ifstream funcoes("assembly-code/IO_functions.asm");
    string linha;

    if (!funcoes) {
        cout << "Erro ao abrir o arquivo com as funções de IO." << endl;
        exit(1);
    }
    while(getline(funcoes, linha)) {
        saida << linha;
        saida << endl;
    }
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
        string aux_acumulador = acumulador;
        aux_acumulador.pop_back();
        aux_acumulador.pop_back();
        if(linha.size() == 2) {
            linha_convertida = (string("MOV ") + string("[") + linha[1] + string("], ") + aux_acumulador);
        } else {
            linha_convertida = (string("MOV ") + string("[") + 
            linha[1] + linha[2] + linha[3] + string("], ") + aux_acumulador);
        }
        final->push_back(toUpperCase(linha_convertida));
    }
    /******************************/

    /* COPY */
    else if(linha[0] == "COPY") {
        linha[1].pop_back(); // retirando a vírgula
        linha_convertida = (string("MOV ") + string("[") + 
        linha[2] + "]" + string(", ") + "[" + linha[1] + "]");
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
        linha_aux.push_back(string("MOV EAX, ") + acumulador);
        linha_aux.push_back(string("CDQ"));
        linha_aux.push_back(string("IDIV DWORD ") + string("[") + linha[1] + string("]"));
        linha_aux.push_back(string("MOV ") + acumulador + string(", EAX"));
        final->push_back(toUpperCase(linha_aux[0]));
        final->push_back(toUpperCase(linha_aux[1]));
        final->push_back(toUpperCase(linha_aux[2]));
        final->push_back(toUpperCase(linha_aux[3]));
    }
    /******************************/

    /* MUL */
    else if(linha[0] == "MULT") {
        vector<string> linha_aux;
        acumulador.pop_back(); // Retirando,
        acumulador.pop_back();

        // Salvando 0 no EDX para verificar overflow
        // linha_aux.push_back(string("MOV EDX, 0"));

        linha_aux.push_back(string("MOV EAX, ") + string("[") + linha[1] + string("]"));
        linha_aux.push_back(string("IMUL DWORD ") + acumulador);
        linha_aux.push_back(string("MOV ") + acumulador + string(", EAX"));
        final->push_back(toUpperCase(linha_aux[0]));
        final->push_back(toUpperCase(linha_aux[1]));
        final->push_back(toUpperCase(linha_aux[2]));

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
            linha_aux.push_back(string("PUSH ") + linha[1]);
            linha_aux.push_back(string("CALL LerChar "));
            final->push_back(toUpperCase(linha_aux[0]));
            final->push_back(linha_aux[1]);
        }
    }
    else if(linha[0] == "C_OUTPUT") { // Ouput Char
        vector<string> linha_aux;
        // TO DO add no endereço
        if(linha.size() == 2) {
            linha_aux.push_back(string("PUSH ") + linha[1]);
            linha_aux.push_back(string("CALL EscreverChar "));
            final->push_back(toUpperCase(linha_aux[0]));
            final->push_back(linha_aux[1]);
        }
    }
    /******************************/

    /* Input e Output de string */
    else if(toUpperCase(linha[0]) == "S_INPUT") { // Input string
        vector<string> linha_aux;
        // TO DO add no endereço
        if(linha.size() == 3) {
            linha[1].pop_back(); // Retirando a vírgula
            linha_aux.push_back(string("PUSH ") + linha[1]);
            linha_aux.push_back(string("PUSH DWORD ") + linha[2]);
            linha_aux.push_back(string("CALL LerString "));
            final->push_back(toUpperCase(linha_aux[0]));
            final->push_back(linha_aux[1]);
            final->push_back(linha_aux[2]);
        }
    }
    else if(toUpperCase(linha[0]) == "S_OUTPUT") { // Ouput string
        vector<string> linha_aux;
        // TO DO add no endereço
        if(linha.size() == 3) {
            linha[1].pop_back(); // Retirando a vírgula
            linha_aux.push_back(string("PUSH ") + linha[1]);
            linha_aux.push_back(string("PUSH DWORD ") + linha[2]);
            linha_aux.push_back(string("CALL EscreverString "));
            final->push_back(toUpperCase(linha_aux[0]));
            final->push_back(linha_aux[1]);
            final->push_back(linha_aux[2]);
        }
    }
    /******************************/

    /* Input e Output de Inteiro */
    else if(linha[0] == "INPUT") { // Input Inteiro
        vector<string> linha_aux;
        string aux_acumulador; 
        aux_acumulador = acumulador;
        acumulador.pop_back();
        acumulador.pop_back();
        // TO DO add no endereço
        if(linha.size() == 2) {
            linha_aux.push_back(string("CALL LerInteiro "));
            linha_aux.push_back(string("MOV ") + "["+ linha[1] + "]" + string(", EAX"));
        }
        final->push_back(linha_aux[0]);
        final->push_back(linha_aux[1]);
    }
    else if(linha[0] == "OUTPUT") { // Output Inteiro
        vector<string> linha_aux;
        // TO DO add no endereço
        if(linha.size() == 2) {
            linha_aux.push_back(string("PUSH DWORD [") + linha[1] + "]");
            linha_aux.push_back(string("CALL EscreverInteiro"));
        }
        final->push_back(toUpperCase(linha_aux[0]));
        final->push_back(linha_aux[1]);
    }
    /******************************/
}

