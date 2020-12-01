#ifndef TRADUCAO_H
#define TRADUCAO_H

#include "classes.hpp"

vector<string> traducao(vector<string> *text);

void metodo_equivalente(vector<string> linha, vector<string> *final);

void print_traducao(vector<string> traducao, string nome_arquivo, vector<string> *bss, vector<string> *data);

#endif /* TRADUCAO_H */