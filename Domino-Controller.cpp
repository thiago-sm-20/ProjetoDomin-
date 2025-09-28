/*
Projeto Dominó 
25/11/2024
Autor: Thiago Salanti Mambrini
*/
#include "Domino-View.h"
#include "Domino-Controller.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

void ftempo(int seg) 
{ 
    time_t  lt1, lt2; 
	lt1 = time(NULL); 
	lt2 = lt1; 
    while (difftime(lt2, lt1) < seg) 
    	lt2 = time(NULL); 
} 

void gravar() {
	estadoJogo.qtmesaJogo = qtmesa;
    estadoJogo.jogadorJogo = jvez;
    estadoJogo.Jog = JogContraComp; 
    estadoJogo.jogadorComp = computador;
    estadoJogo.total1 = PecasJ1;
    estadoJogo.total2 = PecasJ2;
    estadoJogo.livres = totalLivre;
    estadoJogo.qtjsalvar = qtj; 
}

void salvar(){
	gravar(); 
    FILE *fp, *fpm, *fps; //definindo os ponteiros que serão usados
	time_t registrarhora;
	struct tm *horariolocal;
    fp = fopen("GUARDA_PECAS", "w");
    fpm = fopen("GUARDA_MESA", "w");
    fps = fopen("GUARDA_JOGO", "w");
    if (fp == NULL || fpm == NULL || fps == NULL){
        printf("Erro ao abrir o arquivo\n");
        return;
    }
    for (int i = 1; i <= 28; i++)
 		{
 		if (fwrite(&pecas[i], sizeof(struct stpeca), 1, fp)  != 1)
 		{
 		printf("Erro na gravacao do arquivo GUARDA_PECAS");
 		break;
 		}
 	}
 	for (int i = 1; i <= 28; i++)
 		{
 		if (fwrite(&Mesa[i], sizeof(struct stmesa), 1, fpm)  != 1)
 		{
 		printf("Erro na gravacao do arquivo GUARDA_MESA");
 		break;
 		}
 	}
    fwrite(&estadoJogo, sizeof(struct Jogo), 1, fps);

	time(&registrarhora);
	horariolocal = localtime(&registrarhora);
	printf("Salvo em: %02d:%02d:%02d\n", horariolocal->tm_hour, horariolocal->tm_min, horariolocal->tm_sec);

	ftempo(3);

    fclose(fp);
    fclose(fpm);
    fclose(fps);
	
	ftempo(3);
}

void carregar() { //definindo os ponteiros que serão usados
    FILE *fp = NULL, *fpm = NULL, *fps = NULL;
    fp = fopen("GUARDA_PECAS", "r");
    fpm = fopen("GUARDA_MESA", "r");
    fps = fopen("GUARDA_JOGO", "r");
    if (fp == NULL || fpm == NULL || fps == NULL){
        printf("Erro ao abrir o arquivo\n");
        if (fp != NULL) fclose(fp);
        if (fpm != NULL) fclose(fpm);
        if (fps != NULL) fclose(fps);
        return;
    }
    for(int i = 1; i <= 28; i++)
 	{
	 if(fread(&pecas[i], sizeof(struct stpeca), 1, fp)  != 1)
 	{
 	printf("Erro na leitura do arquivo GUARDA_PECAS");
 	break;
 	}
 }
    for(int i = 1; i <= 28; i++)
 	{
	 if(fread(&Mesa[i], sizeof(struct stmesa), 1, fpm)  != 1)
 	{
 	printf("Erro na leitura do arquivo GUARDA_MESA");
 	break;
 	}
 }
    fread(&estadoJogo, sizeof(struct Jogo), 1, fps);

    fclose(fp);
    fclose(fpm);
    fclose(fps);
    
    qtmesa = estadoJogo.qtmesaJogo;
    jvez = estadoJogo.jogadorJogo;
    JogContraComp = estadoJogo.Jog; 
    computador = estadoJogo.jogadorComp;
    PecasJ1 = estadoJogo.total1;
    PecasJ2 = estadoJogo.total2;
    totalLivre = estadoJogo.livres; 
    qtj = estadoJogo.qtjsalvar;
}

void iniciaSalvamento() {
	if (qtj == 1) {
    	jogarComp();
	}
	else if (qtj == 2) {
		jogar(); 
	}
}

void fclear() 
{ 
    int ch; 
    while((ch = fgetc(stdin)) != EOF && ch != '\n'); 
}
  
void limpar(){
    system("cls");
}

void embaralhar() { // função de embaralhamento das peças
    srand(time(NULL));
    for (int i=0; i < 28; i++) {
        int j=rand() % 28;
        pecaaux = pecas[i];
        pecas[i] = pecas[j];
        pecas[j] = pecaaux;
    }
}

void criarPecas() {  //função para criação das peças do jogo 
	int k = 0;
    for (int i = 0; i < 7; i++) {
        for (int j = i; j < 7; j++) {
            pecas[k].lado1 = i;
            pecas[k].lado2 = j;
            k++;
        }
    }
    for (int z = 1; z <= 28; z++) {
    	pecas[z].status = 'N'; 
	}
}

void recomecar() {    //função para recomeçar o jogo, zerando todas as variáveis globais para contar 
	qtmesa = 0;
	PecasJ1 = 0;
	PecasJ2 = 0;
	totalLivre = 0; 
	qtj = 0;
} 

void iniciarJogo() { // função que inicializa as peças do jogo
    criarPecas();
    embaralhar();
    distPecas();
    primeiroLance();
    criaLivres();
}

void primeiroLance() { // função que realiza o primeiro lance da partida automaticamente
	int i, pj, dupla;
	pj = -1; 
	dupla = -1;
	for(i = 1; i <= 14; i++){
		if (pecas[i].lado1 == pecas[i].lado2){
			if (pecas[i].lado1 > dupla){
				dupla = pecas[i].lado1;
				pj = i;
			}
		}
	}
	if (pj == -1) {
		dupla = 0;
		for(i = 1; i <= 14; i++) {
		if (pecas[i].lado1 + pecas[i].lado2 > dupla) {
 			dupla = pecas[i].lado1 + pecas[i].lado2;
			pj = i;
 			}
 		}
	}
	if (pecas[pj].status == '1') {
		jvez = 2;
		PecasJ1--; 
		computador = jvez; 
	}
	else if (pecas[pj].status == '2') {
		jvez = 1; 
		PecasJ2--; 
		JogContraComp = jvez; 
	}
	Mesa[0].ladoE = pecas[pj].lado1;
	Mesa[0].ladoD = pecas[pj].lado2;
	pecas[pj].status = 'M';
	qtmesa++;
}

void distPecas() { //função que distribui as peças
    for (int i = 1; i <= 7; i++){
        pecas[i].status = '1';
        PecasJ1++;
    }
    for (int i = 8; i <= 14; i++){
		pecas[i].status = '2';	
		PecasJ2++;
   }  
}

void verificaLivres() {    //função que verifica a situação de peças disponíveis para compra no jogo, sendo necessário finalizar ou não 
	if (totalLivre == 0) {
		if(PecasJ2 > PecasJ1) {
			limpar();
			apresentaMensagem("Acabaram as pecas disponiveis para compra, o jogo sera finalizado");
			apresentaMensagem("O jogador 1 venceu o jogo!");
			apresentaMensagem("Voltando ao menu inicial...");
			recomecar();
			ftempo(6);
			exibirMenu();
		} 
		else if (PecasJ1 > PecasJ2) {
			limpar();
			apresentaMensagem("Acabaram as pecas disponiveis para compra, o jogo sera finalizado");
			apresentaMensagem("O jogador 2 (ou computador no caso de jogo solo) venceu o jogo!");
			apresentaMensagem("Voltando ao menu inicial...");
			recomecar();
			ftempo(6);
			exibirMenu();
		}
		else if (PecasJ2 == PecasJ1) {
			limpar();
			apresentaMensagem("Acabaram as pecas disponiveis para compra, o jogo sera finalizado");
			apresentaMensagem("O jogo terminou em empate");
			apresentaMensagem("Voltando ao menu inicial...");
			recomecar();
			ftempo(6);
			exibirMenu();
		}	
	}
}

void verificaVencedor() {     //função que verifica o vencedor do jogo 
	if (PecasJ1 == 0) {
		limpar();
		apresentaMensagem("O jogador 1 venceu o jogo!");
		apresentaMensagem("Voltando ao menu inicial...");
		recomecar();
		ftempo(6);
		exibirMenu();
	} 
	if (PecasJ2 == 0) {
		limpar();
		apresentaMensagem("O jogador 2 (ou computador no caso jogo solo) venceu o jogo!");
		apresentaMensagem("Voltando ao menu inicial...");
		recomecar(); 
		ftempo(6);
		exibirMenu();
	}
}

void comprarPeca() {     //função para comprar uma peça 
	if (jvez == 1 || jvez == JogContraComp) {
	  for (int i = 15; i <= 28; i++) {
		 if(pecas[i].status == 'N') { 
		  pecas[i].status = '1';
		  PecasJ1++;
		  totalLivre--;
		 if(pecas[i].status == '1' || pecas[i].status == '2') 
		   break; 
		}
	}
}
	if (jvez == 2) {
		for (int i = 15; i <= 28; i++) {
		 if(pecas[i].status == 'N') { 
		  pecas[i].status = '2';
		  PecasJ2++;
		  totalLivre--;  
		 if(pecas[i].status == '2' || pecas[i].status == '1')
		   break; 
	       }
		}	
	}
}

int verificaCompraJOG() {       //função que verifica se jogador pode comprar uma peça (exclusivamente para jogo contra o computador) 
	for(int i = 1; i <= 28; i++) {
			if(pecas[i].status == '1') {
				if(pecas[i].lado2 == Mesa[qtmesa-qtmesa].ladoE || pecas[i].lado1 == Mesa[qtmesa-qtmesa].ladoE 
			|| pecas[i].lado2 == Mesa[qtmesa-1].ladoD || pecas[i].lado1 == Mesa[qtmesa-1].ladoD) {
					return 0;
				}
			} 
		}
		return 1;
}

int verificaCompra() {    //função para verificar se os jogadores podem realizar uma compra (exclusivamente para jogador vs jogador)
	if (jvez == 1) {
		for(int i = 1; i <= 28; i++) {
			if(pecas[i].status == '1') {
				if(pecas[i].lado2 == Mesa[qtmesa-qtmesa].ladoE || pecas[i].lado1 == Mesa[qtmesa-qtmesa].ladoE 
			|| pecas[i].lado2 == Mesa[qtmesa-1].ladoD || pecas[i].lado1 == Mesa[qtmesa-1].ladoD) {
					return 0;
				}
			} 
		}
		return 1;
	}
	else if (jvez == 2) {
		for(int i = 1; i <= 28; i++) {
			if(pecas[i].status == '2') {
				if(pecas[i].lado2 == Mesa[qtmesa-qtmesa].ladoE || pecas[i].lado1 == Mesa[qtmesa-qtmesa].ladoE 
			|| pecas[i].lado2 == Mesa[qtmesa-1].ladoD || pecas[i].lado1 == Mesa[qtmesa-1].ladoD) {
					return 0;
				}
			} 
		}
		return 1;
	}
}

void criaLivres() {     //função para contabilizar o total inicial de peças disponíveis para compra
	for (int i = 15; i <= 28; i++) {
		if(pecas[i].status == 'N') {
			totalLivre++; 
		}
	pecas[28] = pecas[0]; 
	pecas[28].status = 'N'; 
	}
}

void fjogarPeca() {    //função que permite realizar uma jogada de uma peça 
        int pj, i;
        int opcao;
        apresentaMensagem("Escolha a peca para jogar:");
        fclear();
        scanf("%d", &pj);
        printf("Peca jogada: [%d|%d]\n", pecas[pj].lado1, pecas[pj].lado2); 
        if(pecas[pj].lado1 != Mesa[qtmesa-qtmesa].ladoE && pecas[pj].lado2 != Mesa[qtmesa-qtmesa].ladoE) {
        	if(pecas[pj].lado1 == Mesa[qtmesa-1].ladoD) {
        		Mesa[qtmesa].ladoE = pecas[pj].lado1;
    			Mesa[qtmesa].ladoD = pecas[pj].lado2;
    			qtmesa++;
   	 		 	pecas[pj].status = 'M';
   	 		 	if(jvez == 1 || jvez == JogContraComp){
					PecasJ1--;
				} 
				 else if (jvez ==2) {
					PecasJ2--;
				}
			} else if(pecas[pj].lado2 == Mesa[qtmesa-1].ladoD) {
				Mesa[qtmesa].ladoE = pecas[pj].lado2;
    			Mesa[qtmesa].ladoD = pecas[pj].lado1;
    			qtmesa++;
    			pecas[pj].status = 'M';
    			if(jvez == 1 || jvez == JogContraComp){
					PecasJ1--; 
					} 
				else if (jvez ==2) {
					PecasJ2--; 
					}
			}
		ftempo(2);
		return; 
		} else if(pecas[pj].lado1 != Mesa[qtmesa-1].ladoD && pecas[pj].lado2 != Mesa[qtmesa-1].ladoD) {
			if(pecas[pj].lado1 == Mesa[qtmesa-qtmesa].ladoE) {
				for (int i = qtmesa; i > 0; i--) {
        			Mesa[i] = Mesa[i - 1];
        		}
    			Mesa[0].ladoE = pecas[pj].lado2;
    			Mesa[0].ladoD = pecas[pj].lado1;
    			qtmesa++;
    			pecas[pj].status = 'M';
				if(jvez == 1 || jvez == JogContraComp){
					PecasJ1--; 
				} else if (jvez ==2) {
					PecasJ2--; 
				}  
			} else if (pecas[pj].lado2 == Mesa[qtmesa-qtmesa].ladoE) {
				for (int i = qtmesa; i > 0; i--) {
        			Mesa[i] = Mesa[i - 1];
        		}
    			Mesa[0].ladoE = pecas[pj].lado1;
    			Mesa[0].ladoD = pecas[pj].lado2;
    			qtmesa++;
    			pecas[pj].status = 'M';
				if(jvez == 1 || jvez == JogContraComp){
					PecasJ1--; 
					} 
				else if (jvez == 2) {
					PecasJ2--;  
				}
			}
		ftempo(2);	
		return;	
	}
        apresentaMensagem("Em qual lado da mesa quer jogar? (0 para esquerda e 1 para direita)");
        fclear();
        scanf("%d", &opcao);
        	if (opcao == 0) { 
				if (pecas[pj].lado2 == Mesa[qtmesa-qtmesa].ladoE) {     		        		 		
					for (int i = qtmesa; i > 0; i--) {
        			Mesa[i] = Mesa[i - 1];
        			}
    				Mesa[0].ladoE = pecas[pj].lado1;
    				Mesa[0].ladoD = pecas[pj].lado2;
    				qtmesa++;
    				pecas[pj].status = 'M';
					 if(jvez == 1 || jvez == JogContraComp){
					 	PecasJ1--; 
					 } 
					 else if (jvez == 2) {
					 	PecasJ2--;  
					 }
    			} else if(pecas[pj].lado1 == Mesa[qtmesa-qtmesa].ladoE) {
				 	for (int i = qtmesa; i > 0; i--) {
        			Mesa[i] = Mesa[i - 1];
        			}
    				Mesa[0].ladoE = pecas[pj].lado2;
    				Mesa[0].ladoD = pecas[pj].lado1;
    				qtmesa++;
    				pecas[pj].status = 'M';
					if(jvez == 1 || jvez == JogContraComp){
					 	PecasJ1--; 
					 } else if (jvez ==2) {
					 	PecasJ2--; 
					 }  
			    } else {
    	    	 apresentaMensagem("Jogada invalida, jogue novamente");
    	    	 apresentaMensagem(" ");
    	    	 ftempo(2);
    	    	 fjogarPeca();
			    }
		    }
        	else if (opcao == 1) {
        		if (pecas[pj].lado2 == Mesa[qtmesa-1].ladoD) { 
				Mesa[qtmesa].ladoE = pecas[pj].lado2;
    			Mesa[qtmesa].ladoD = pecas[pj].lado1;
    			qtmesa++;
    			pecas[pj].status = 'M';
    			if(jvez == 1 || jvez == JogContraComp){
					 	PecasJ1--; 
					 } 
					 else if (jvez ==2) {
					 	PecasJ2--; 
					 }
					} else if (pecas[pj].lado1 == Mesa[qtmesa-1].ladoD) {
						Mesa[qtmesa].ladoE = pecas[pj].lado1;
    					Mesa[qtmesa].ladoD = pecas[pj].lado2;
    					qtmesa++;
   	 		 			pecas[pj].status = 'M';
   	 		 			if(jvez == 1 || jvez == JogContraComp){
					 	PecasJ1--;
					} 
					 else if (jvez ==2) {
					 	PecasJ2--; 
					}
       					} else {
        	apresentaMensagem("Jogada invalida, jogue novamente"); 
        	apresentaMensagem(" ");
        	ftempo(2);
        	fjogarPeca();
        }
    }
}

void comprarComputador() {       //função que permite o computador comprar uma peça 
	for (int j = 15; j <= 28; j++) {
	 	if(pecas[j].status == 'N') { 
			pecas[j].status = '2';
			PecasJ2++;
		    totalLivre--;  
			 if(pecas[j].status == '2' || pecas[j].status == '1') {
	    		break;
				}
	   	}
	}
}
	
void jogadaComputador() {      //função que permite o computador realizar uma jogada 
	for (int k = 1; k <= 28; k++) {
		if (pecas[k].status == '2') {
			if (pecas[k].lado2 == Mesa[qtmesa-qtmesa].ladoE) {     		        		 		
				for (int i = qtmesa; i > 0; i--) {
        		Mesa[i] = Mesa[i - 1];
        		}
    			Mesa[0].ladoE = pecas[k].lado1;
    			Mesa[0].ladoD = pecas[k].lado2;
    			qtmesa++;
    			pecas[k].status = 'M';	
    			PecasJ2--;
	    		return;
			}
		    else if (pecas[k].lado1 == Mesa[qtmesa-1].ladoD) {
				Mesa[qtmesa].ladoE = pecas[k].lado1;
    			Mesa[qtmesa].ladoD = pecas[k].lado2;
    			qtmesa++;
   	 		 	pecas[k].status = 'M';
   	 		 	PecasJ2--;
				return;
    		}
    		else if (pecas[k].lado2 == Mesa[qtmesa-1].ladoD) { 
				Mesa[qtmesa].ladoE = pecas[k].lado2;
    			Mesa[qtmesa].ladoD = pecas[k].lado1;
    			qtmesa++;
    			pecas[k].status = 'M';
    			PecasJ2--; 
    		    return;
    		}
    		else if(pecas[k].lado1 == Mesa[qtmesa-qtmesa].ladoE) {
				for (int i = qtmesa; i > 0; i--) {
        		Mesa[i] = Mesa[i - 1];
        		}
    			Mesa[0].ladoE = pecas[k].lado2;
    			Mesa[0].ladoD = pecas[k].lado1;
    			qtmesa++;
    			pecas[k].status = 'M';
    			PecasJ2--;
    		 	return;
   	 		}
   	 		else {
   	 		 continue;
   	 		}
   	 	}
	}
	verificaLivres();
	comprarComputador(); 
	jogadaComputador(); 
}		

