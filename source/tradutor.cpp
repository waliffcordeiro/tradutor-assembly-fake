#include "../include/classes.hpp"
#include "../include/pre-processamento.hpp"


// Waliff Cordeiro Bandeira - 17/0115810

using namespace std;


int main(int argc, char **argv) {

    vector<Linha> linhas;
    vector<Linha>::iterator it_linha;

    linhas = pre_processamento(argv[1]);

    for(it_linha=linhas.begin(); it_linha != linhas.end(); it_linha++) {
        Linha linha_refatorada = (Linha)*it_linha;
        if(it_linha->rotulo != "") {
            cout << it_linha->rotulo<<" ";
        }
        if(it_linha->comando != "") {
            cout << it_linha->comando<<" ";
        }
        if(it_linha->operador1 != "") {
            cout << it_linha->operador1<<" ";
        }
        if(it_linha->operador2 != "") {
            cout << it_linha->operador2<<" ";
        }
        if(it_linha->rotulo != "" || it_linha->comando != "" || it_linha->operador1 != "" || it_linha->operador2 != "") {
            // Se tiver pelo menos um elemento, printa a quebra de linha
            cout << endl; 
        }
    }
        
    return 0;
}