#ifndef TRADUCAO_H
#define TRADUCAO_H

#include "classes.hpp"

vector<string> traducao(vector<string> *text, vector<string> *bss, vector<string> *data);

string metodo_equivalente(vector<string> linha);

void print_traducao(vector<string> traducao, string nome_arquivo);

#endif /* TRADUCAO_H */