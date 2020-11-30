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
        final->push_back(linha_convertida);
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
        final->push_back(linha_convertida);
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
        final->push_back(linha_convertida);
    }
    /******************************/

    /* COPY */
    else if(linha[0] == "COPY") {
        linha[1].pop_back(); // retirando a vírgula
        linha_convertida = (string("MOV ") + string("[") + 
        linha[1] + "]" + string(", ") + "[" + linha[2] + "]");
        final->push_back(linha_convertida);
    }
    /******************************/

    else if(linha[0] == "LOAD") {
        if(linha.size() == 2) {
            linha_convertida = (string("MOV ") + acumulador + "[" + linha[1] + "]");
        } else {
            linha_convertida = (string("MOV ") + acumulador + "[" + linha[1] +
            linha[2] + linha[3] + "]");
        }
        final->push_back(linha_convertida);
    }

}

void print_traducao(vector<string> traducao, string nome_arquivo) {
    
    /* Funções Assembly */

    /* Section Data */
    
    /* Section Bss */

    /* Section Text */

}