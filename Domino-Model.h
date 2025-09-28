/*
Projeto Dominó 
25/11/2024
Autor: Thiago Salanti Mambrini
*/

#ifndef MODEL_H
#define MODEL_H

typedef struct stpeca{    //estrutura da peça 
    int lado1; //esquerda
    int lado2; //direita
    char status; //status da peca: 'N' = NULL, '1', '2' e 'M'
} tipoPeca;

typedef struct stmesa    //estrutura da mesa 
{
	int ladoE;
	int ladoD;	
} mesa;

//variáveis globais do jogo: 

int JogContraComp; 
int computador;
int totalLivre;
int PecasJ1, PecasJ2;  
mesa Mesa[28]; 
char jvez;
tipoPeca pecas[28];
int qtmesa; 
tipoPeca pecaaux; 
int qtj = 0; 

typedef struct Jogo{    //estrutura para gravar a situação atual do jogo  
    int qtmesaJogo;
    int jogadorJogo;
    int Jog; 
    int jogadorComp;
    int total1;
    int total2;
    int livres;
    int qtjsalvar; 
}sitJogo;

sitJogo estadoJogo;
  

#endif
