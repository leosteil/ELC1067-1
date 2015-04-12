/*
 * jogo.c TAD que implementa o jogo de cartas "solitaire".
 * 
 * The MIT License (MIT)
 * 
 * Copyright (c) 2014, 2015 João V. Lima, UFSM 2005       Benhur Stein, UFSM
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include <assert.h>

#include "jogo.h"
#include "memo.h"

#define SOLIT_MAGICO 0x50717
#define DESTRUIDO 0x80000000

bool jogo_valido(jogo sol){
  
	if (sol == NULL || sol->magico != SOLIT_MAGICO) {
		return false;
	}
	return true;
}

jogo jogo_cria(void){
  
	jogo sol;
	int  i;

	sol = (jogo) memo_aloca(sizeof(jogo_t));
	assert(sol != NULL);
	sol->magico = SOLIT_MAGICO;

	sol->monte = pilha_cria();
	sol->descartes = pilha_cria();
	for (i = 0; i < 4; i++) {
		sol->ases[i] = pilha_cria();
	}
	for (i = 0; i < 7; i++) {
		sol->pilhas[i] = pilha_cria();
	}
	sol->tela = tela_cria();

	return sol;
}

static void jogo_destroi_pilha(pilha p){
  
	while (!pilha_vazia(p)) {
		carta_destroi(pilha_remove_carta(p));
	}
	pilha_destroi(p);
}

void jogo_destroi(jogo sol){
	
	int i;
	assert(jogo_valido(sol));
	jogo_destroi_pilha(sol->monte);
	jogo_destroi_pilha(sol->descartes);
	for (i = 0; i < 4; i++) {
		jogo_destroi_pilha(sol->ases[i]);
	}
	for (i = 0; i < 7; i++) {
		jogo_destroi_pilha(sol->pilhas[i]);
	}
	tela_destroi(sol->tela);
	sol->magico |= DESTRUIDO;
	memo_libera(sol);
}

/* acessores */
tela jogo_tela(jogo sol){
  
	assert(jogo_valido(sol));
	return sol->tela;
}

pilha jogo_monte(jogo sol){

	assert(jogo_valido(sol));
	return sol->monte;
}

pilha jogo_descartes(jogo sol){
  
	assert(jogo_valido(sol));
	return sol->descartes;
}

pilha jogo_ases(jogo sol, int i){
  
	assert(jogo_valido(sol));
	assert(i >= 0 && i < 4);
	return sol->ases[i];
}

pilha jogo_pilha(jogo sol, int i){
  
	assert(jogo_valido(sol));
	assert(i >= 0 && i < 7);
	return sol->pilhas[i];
}

void desvira_carta(jogo solit, pilha p){
	if(!pilha_vazia(p)){
	  carta c = pilha_remove_carta(p);
	  carta_abre(c);
	  pilha_insere_carta(p,c);
	}  
	  jogo_desenha(solit);
	  tela_atualiza(jogo_tela(solit));
}

void monte_to_descartes(jogo sol){		
	carta c = pilha_remove_carta(jogo_monte(sol));
	carta_abre(c);
	pilha_insere_carta(jogo_descartes(sol), c);
	jogo_desenha(sol);
}

void descartes_to_monte(jogo sol){
    while(!pilha_vazia(jogo_descartes(sol))){
	carta c = pilha_remove_carta(jogo_descartes(sol));
	carta_fecha(c);
	pilha_insere_carta(jogo_monte(sol), c);
	jogo_desenha(sol);
   }
}

void descartes_to_pilha(jogo solit, int nPilha){
	pilha p = jogo_pilha(solit,nPilha);
	carta c = pilha_remove_carta(jogo_descartes(solit));
	if(pilha_vazia(p)){
	    pilha_insere_carta(p, c);
	    jogo_desenha(solit);
	    tela_atualiza(jogo_tela(solit));
	    return;
	}
	carta c1 = pilha_remove_carta(p);
	if(carta_valor(c) == (carta_valor(c1)-1)){
	    pilha_insere_carta(p,c1);
	    pilha_insere_carta(p,c);
	    jogo_desenha(solit);
	    tela_atualiza(jogo_tela(solit));
	}else{
	    pilha_insere_carta(p,c1);
	    pilha_insere_carta(jogo_descartes(solit),c);
	    jogo_desenha(solit);
	    printw("\nJogada Inválida\n");
	    tela_atualiza(jogo_tela(solit));
	}

}


void descartes_to_pilhaAses(jogo solit, int nPilhaAS, carta ct){
	carta as = pilha_remove_carta(jogo_ases(solit,nPilhaAS));
	if(carta_valor(ct) == (carta_valor(as)+1) && carta_naipe(ct) == carta_naipe(as)){
	  pilha_insere_carta(jogo_ases(solit,nPilhaAS),as);
	  pilha_insere_carta(jogo_ases(solit,nPilhaAS),ct);
	  jogo_desenha(solit);
	  tela_atualiza(jogo_tela(solit));
       }else{
	  printw("\nNão é possível mover esta carta!!");
	  tela_atualiza(jogo_tela(solit));
	}
}

void pilha_to_pilha(jogo solit, int nPilha1, int nPilha2){
	pilha p1 = jogo_pilha(solit, nPilha1);//pilha original
	pilha p2 = jogo_pilha(solit, nPilha2);//pilha alvo
	pilha pAux = pilha_cria();
	carta c1 = pilha_remove_carta(p1);
	
  if(pilha_vazia(p2)){
	  while(carta_aberta(c1)){
	    pilha_insere_carta(pAux, c1);
	    c1 = pilha_remove_carta(p1);
	  }
	    pilha_insere_carta(p1,c1);//recolo a carta removida da pilha original
	  while(!pilha_vazia(pAux)){
	    c1 = pilha_remove_carta(pAux);
	    pilha_insere_carta(p2, c1); 
	  }
	    desvira_carta(solit, p1);
  }else{
	  while(carta_aberta(c1)){
	    pilha_insere_carta(pAux, c1);
	    c1 = pilha_remove_carta(p1);
	  }
	    pilha_insere_carta(p1,c1);
	    carta c2 = pilha_remove_carta(p2);
	    c1 = pilha_remove_carta(pAux);    	
	if(carta_valor(c1) == (carta_valor(c2)-1) && carta_naipe(c1) != carta_naipe(c2)){
	    pilha_insere_carta(p2,c2);
	    pilha_insere_carta(p2,c1);
	    desvira_carta(solit,p1);
	  while(!pilha_vazia(pAux)){
	    c1 = pilha_remove_carta(pAux);
	    pilha_insere_carta(p2, c1); 
	  }
	    jogo_desenha(solit);
	}else{
	  while(!pilha_vazia(pAux)){
	    c1 = pilha_remove_carta(pAux);
	    pilha_insere_carta(p1, c1); 
	  }
	    pilha_insere_carta(p2,c2);
	    pilha_insere_carta(p1, c1);
	    jogo_desenha(solit);
	    printw("\nJogada Inválida\n");
	    tela_atualiza(jogo_tela(solit));
	}
 }
}


void pilha_to_pilhaAses(jogo solit,int nPilha1, int nPilhaAS, carta ct){
	if(pilha_vazia(jogo_ases(solit,nPilhaAS))){
	  printw("\nNão é possível mover esta carta!!");
	  pilha_insere_carta(jogo_pilha(solit, nPilha1),ct);
	  jogo_desenha(solit);
	  tela_atualiza(jogo_tela(solit));
	  return;
	}
	carta as = pilha_remove_carta(jogo_ases(solit,nPilhaAS));
	if(carta_valor(ct) == (carta_valor(as)+1) && carta_naipe(ct) == carta_naipe(as)){
	  pilha_insere_carta(jogo_ases(solit,nPilhaAS),as);
	  pilha_insere_carta(jogo_ases(solit,nPilhaAS),ct);
	  desvira_carta(solit,jogo_pilha(solit,nPilha1));
       }else{
	  printw("\nNão é possível mover esta carta!!");
	  tela_atualiza(jogo_tela(solit));
	}
}

void select_pilhas(jogo solit,int nPilha1,char tecla){
	carta ct;
	switch(tecla){
		      case '0':
			if(pilha_vazia(jogo_pilha(solit,nPilha1))){
 		      	     printw("\nJogada Inválida Pilha vazia\n"); 
 		          }else  
 		             pilha_to_pilha(solit,nPilha1,0);
		      break;  
		      case '1':
			  if(pilha_vazia(jogo_pilha(solit,nPilha1))){
 		      	     printw("\nJogada Inválida Pilha vazia\n"); 
 		          }else  
 		             pilha_to_pilha(solit,nPilha1,1);
		      break;
		      case '2':
			  if(pilha_vazia(jogo_pilha(solit,nPilha1))){
 		      	     printw("\nJogada Inválida Pilha vazia\n"); 
 		          }else  
 		             pilha_to_pilha(solit,nPilha1,2);
		      break;
		      case '3':
			  if(pilha_vazia(jogo_pilha(solit,nPilha1))){
 		      	     printw("\nJogada Inválida Pilha vazia\n");
 		          }else  
 		             pilha_to_pilha(solit,nPilha1,3);
		      break;
		      case '4':
			  if(pilha_vazia(jogo_pilha(solit,nPilha1))){
 		      	     printw("\nJogada Inválida Pilha vazia\n");
 		          }else  
 		             pilha_to_pilha(solit,nPilha1,4);
		      break;
		      case '5':
			  if(pilha_vazia(jogo_pilha(solit,nPilha1))){
 		      	     printw("\nJogada Inválida Pilha vazia\n");
 		          }else  
 		             pilha_to_pilha(solit,nPilha1,5);
		      break;
		      case '6':
			  if(pilha_vazia(jogo_pilha(solit,nPilha1))){
 		      	     printw("\nJogada Inválida Pilha vazia\n");
 		          }else  
 		             pilha_to_pilha(solit,nPilha1,6);
		      break;
		      case 'q':
			  ct = pilha_remove_carta(jogo_pilha(solit, nPilha1)); 
			  if(carta_valor(ct) == 1 && pilha_vazia(jogo_ases(solit,0))){
			    pilha_insere_carta(jogo_ases(solit,0),ct);
			    desvira_carta(solit,jogo_pilha(solit, nPilha1));
			  }else
			    pilha_to_pilhaAses(solit,nPilha1,0,ct);
		      break;
		      case 'w':
			  ct = pilha_remove_carta(jogo_pilha(solit, nPilha1)); 
			  if(carta_valor(ct) == 1 && pilha_vazia(jogo_ases(solit,1))){
			    pilha_insere_carta(jogo_ases(solit,1),ct);
			    desvira_carta(solit,jogo_pilha(solit, nPilha1));
			  }else
			    pilha_to_pilhaAses(solit,nPilha1,1,ct);
		      break;
		      case 'e':
			  ct = pilha_remove_carta(jogo_pilha(solit, nPilha1)); 
			  if(carta_valor(ct) == 1 && pilha_vazia(jogo_ases(solit,2))){
			    pilha_insere_carta(jogo_ases(solit,2),ct);
			    desvira_carta(solit,jogo_pilha(solit, nPilha1));
			  }else
			    pilha_to_pilhaAses(solit,nPilha1,2,ct);
		      break;
		      case 'r':
			  ct = pilha_remove_carta(jogo_pilha(solit, nPilha1)); 
			  if(carta_valor(ct) == 1 && pilha_vazia(jogo_ases(solit,3))){
			    pilha_insere_carta(jogo_ases(solit,3),ct);
			    desvira_carta(solit,jogo_pilha(solit, nPilha1));
			  }else
			    pilha_to_pilhaAses(solit,nPilha1,3,ct);
		      break;    
	   }
}