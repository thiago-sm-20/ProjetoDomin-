/*
Projeto Dominó 
25/11/2024
Autor: Thiago Salanti Mambrini
*/
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "DOM-GLTV-Model.h"

void ftempo(int seg);
void gravar();
void salvar();
void carregar();
void fclear();
void limpar();
void embaralhar();
void criarPecas();
void recomecar();
void iniciarJogo();
void primeiroLance();
void distPecas();
void verificaLivres();
void verificaVencedor();
void comprarPeca();
int verificaCompraJOG();
int verificaCompra();
void criaLivres();
void fjogarPeca();
void comprarComputador();
void jogadaComputador();

#endif
