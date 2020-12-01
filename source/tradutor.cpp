#include "../include/classes.hpp"
#include "../include/pre-processamento.hpp"
#include "../include/traducao.hpp"


// Waliff Cordeiro Bandeira - 17/0115810

using namespace std;


int main(int argc, char **argv) {

    vector<string> bss, data, text, traduzido;
    string nome_arquivo;

    nome_arquivo = pre_processamento(argv[1], &text, &bss, &data);

    traduzido = traducao(&text);

    print_traducao(traduzido, (nome_arquivo + ".s"), &bss, &data);

    return 0;
}