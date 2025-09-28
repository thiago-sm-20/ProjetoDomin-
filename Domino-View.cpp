/*
Projeto Dominó 
25/11/2024
Autor: Thiago Salanti Mambrini
*/

#include <stdio.h>
#include "Domino-View.h"

void regras(){
	int i;
    printf("=================== Regras ======================\n");
    printf("28 pecas serao distribuidas entre os jogadores, cada uma com dois numeros nas extremidades das pecas (Exemplo: [3|5])\n");
    printf("O jogador que inicia a partida e o que tem a peca com a maior dupla (Exemplo: [6|6])\n");
	printf("As opcoes de jogada sao: jogar peca, comprar peca e passar a vez\n");
    printf("Uma jogada vai ser considerada valida, caso o valor do lado corresponda ao numero da extremidade\n");
    printf("O jogador pode comprar pecas a qualquer momento, podendo usar isso para criar estrategias ou para receber uma peca de que nao possui, somente quando a loja nao possui mais peca que o jogador podera passar a sua vez.\n\n");
    printf(" A rodada termina quando um dos jogadores nao tiver mais pecas em sua mao, ou se todos os jogadores somente conseguem fazer a jogada de passar, nao tendo nenhuma peca valida para jogar\n");
    printf("Ganha aquele que tiver a menor pontuacao em sua mao, somando os numeros das extremidades das pecas.\n");
    printf("=========================================\n");
    printf("Para voltar ao menu, pressione '1'\n");
    scanf("%d", &i);
    if (i == 1) {
    	exibirMenu();
	}
    else {
    	regras(); 
	}
}

void menuPrincipal() {
	printf("  JOGO DOMINO - GLTV - Menu de Opcoes:\n");
	printf("========================================\n");
    printf("1) Iniciar jogo contra o computador    |\n");
    printf("2) Iniciar jogo com 2 Jogadores        |\n");
    printf("3) Salvar jogo                         |\n");
    printf("4) Carregar ultimo jogo salvo          |\n");
    printf("5) Regras                              |\n");
    printf("0) Sair do jogo                        |\n");
    printf("========================================\n");
    printf("Opcao escolhida\n");
    printf("--> ");
}

void apresentaMensagem(char mens[100]) {
       printf("%s\n", mens); 
}

void aP1() {     //função para apresentar as peças do jogador 1 
	for (int i = 1; i <= 28; i++) {
	 if(pecas[i].status == '1') {
	  printf("Peca %d:[%d|%d]  ", i+1,  pecas[i].lado1, pecas[i].lado2);
      } 
	}
	printf("\n");	 
}

void aP2() {      //função para apresentar as peças do jogador 2
	for (int i = 1; i <= 28; i++) {
	 if(pecas[i].status == '2') {
	  printf("Peca %d:[%d|%d]  ", i+1, pecas[i].lado1, pecas[i].lado2);
      }
	}
	printf("\n");	 
}

void mostrarMesa() {       //função para mostrar a mesa do jogo 
	apresentaMensagem("Mesa: ");
	for(int i = 0; i < qtmesa; i++) {
    	 printf(" [%d|%d] ", Mesa[i].ladoE, Mesa[i].ladoD); 
    }
    printf("\n\n"); 
}

void mostraEstats() {
	printf("\n");
	printf("Total de pecas restantes com o computador: %d\n", PecasJ2);
	printf("Total de pecas restantes na loja: %d\n", totalLivre); 
	printf("\n");
}

void mostraLoja() {
	printf("\n");
	printf("Total de pecas restantes na loja: %d\n", totalLivre); 
	printf("\n");
}

void exibirMenu() { // exibição do menu
    tipoPeca pecas[28];
    int op; //opção
    tipoPeca mesa[28];
    int totalMesa = 0;
    //while(1) {
        limpar();
        menuPrincipal();
        scanf("%d", &op);
        switch (op) {
            case 1:
            	qtj = 1;
            	recomecar();
            	iniciarJogo();
                limpar();
                jogarComp(); 
            case 2:
            	qtj = 2;
            	recomecar();
            	iniciarJogo();
                limpar();
                jogar();
                break;
            case 3:
                salvar(); 
                break;
            case 4:
                carregar();
                iniciaSalvamento(); 
                break;
            case 5:
                regras();
                break;
            case 0:
                printf("Saindo do jogo. Ate mais!\n");
                exit(0); 
                break;
            default:
                printf("Opcao invalida! Escolha um numero de 0 a 6 dentre as opcoes existentes\n");
                break;
        }
        getchar();
}

void jogMenu() {
    printf("J) Jogar\n");
    printf("C) Comprar\n");
    printf("P) Passar a vez\n");
    printf("S) Sair (Interromper jogo atual)\n");
}

void jogar() {
    char op, op2;
    int escolha; 
    while(1){
        limpar();
        mostrarMesa();
        mostraLoja(); 
        verificaVencedor();
        if(jvez == 1){
            printf("Vez do jogador 1: \n");
            aP1();
            printf("\n\n");
            printf("O que deseja fazer: \n");
            jogMenu();
       }else if (jvez == 2){
            printf("Vez do jogador 2: \n");
            aP2(); 
            printf("\n\n");
            printf("O que deseja fazer: \n");
            jogMenu();
        }
        //fclear();
        scanf("%c", &op2); 
        switch (op2) {
            case 'j':
				fjogarPeca();
                jvez = (jvez == 1) ? 2 : 1;
				break;
            case 'c': 
            	verificaLivres(); 
            	comprarPeca();
				limpar(); 
                break;
            case 'p':
            	if(verificaCompra()) {
            		printf("Passando a vez... aguarde\n");
            		ftempo(2); 
                	jvez = (jvez == 1) ? 2 : 1;
                	limpar();
            	}
            	else {
            		printf("Jogue uma peca\n");
            		ftempo(3); 
				}
                break;
            case 's':
                printf("Saindo da partida e retornando ao menu inicial\n");
                limpar(); 
                exibirMenu(); 
                break;
            default:
                printf("Opcao invalida!\n");
                break;
            }
		}
}

void jogarComp() {
	char op, op2;
    int escolha;
    while (1) {
        limpar();  
        printf("\n");
        mostrarMesa();
        mostraEstats();
        verificaVencedor();
        if (jvez == JogContraComp) {
        printf("Sua vez de jogar: \n");
        aP1();
        printf("\n\n");
        printf("O que deseja fazer: (use apenas a letra minuscula, ex 'j') \n");
        jogMenu();
        scanf("%c", &op2); 
        switch (op2) {
            case 'j':
				fjogarPeca();
				printf("Jogada concluida\n"); 
				verificaVencedor();
				printf("\nO computador esta jogando... aguarde\n");
				ftempo(2);
				jvez = computador;
				break;
            case 'c': 
            	verificaLivres();
            	comprarPeca();
				limpar(); 
                break;
            case 'p':
            	if(verificaCompraJOG()) {
            	printf("Passando a vez... aguarde\n");
            	ftempo(2); 
                limpar();
                jvez = computador;
            	}
            	else {
            		printf("Jogue uma peca\n");
            		ftempo(3); 
				}
                break;
            case 's':
                printf("Saindo da partida e retornando ao menu inicial\n");
                limpar();
                exibirMenu(); 
                break;
            default:
                printf("Opcao invalida!\n");
                break;
            }
     }
     if (jvez == computador){
     	jogadaComputador();
     	verificaVencedor();
     	jvez = JogContraComp;
	    }
	}
}


