#include "../include/traducao.hpp"


vector<string> traducao(vector<string> *text, vector<string> *bss, vector<string> *data) {
    vector<string> aux;
    string aux_linha;

    /* Section Data */
    
    /* Section Bss */

    /* Section Text */
    for(auto linha:*text) {
        aux_linha = metodo_equivalente(split(linha, ' ', '\t'));
        
    }

    return aux;
}

string metodo_equivalente(vector<string> linha) {
    string linha_convertida;

    if(linha[0] == "ADD") {
        if(linha.size() == 2)
            linha_convertida = (string("ADD ") + string("EBX, ") + string("[") +
            linha[1] + "]");
        else {
            linha_convertida = (string("ADD ") + string("EBX, ") + string("[") +
             linha[1] + linha[2] + linha[3] + string("]"));
        }
    }


    return linha_convertida;
}

void print_traducao(vector<string> traducao, string nome_arquivo) {
    
    /* Funções Assembly */

    /* Section Data */
    
    /* Section Bss */

    /* Section Text */

}