#include "../include/traducao.hpp"


vector<string> traducao(vector<string> *text, vector<string> *bss, vector<string> *data) {
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
        string jump = linha[0] + " ";
        string linha_aux;
        if(linha.size() == 2) {
            linha_aux = (string("CMP ") + acumulador + string("0"));
            linha_convertida = jump + linha[1];
        } else {
            linha_aux = (string("CMP ") + acumulador + string("0"));
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
        linha_aux.push_back(string("IDIV ") + linha[1]);
        final->push_back(toUpperCase(linha_aux[0]));
        final->push_back(toUpperCase(linha_aux[1]));
        final->push_back(toUpperCase(linha_aux[2]));
    }
    /******************************/

    /* MUL */
    else if(linha[0] == "MUL") {
        vector<string> linha_aux;
        acumulador.pop_back();
        acumulador.pop_back();
        linha_aux.push_back(string("MOV EAX, ") + acumulador);
        linha_aux.push_back(string("IMUL ") + linha[1]);
        final->push_back(toUpperCase(linha_aux[0]));
        final->push_back(toUpperCase(linha_aux[1]));
        /* TODO Tratar Overflow*/
    }
    /******************************/

}

void print_traducao(vector<string> traducao, string nome_arquivo) {
    
    /* Funções Assembly */

    /* Section Data */
    
    /* Section Bss */

    /* Section Text */

}