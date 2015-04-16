/*
 * principal.c Esse programa testa as TADs implementadas para um jogo
 * solitário.
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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "memo.h"
#include "jogo.h"
#include "vetor.h"
#include "fila.h"
#include "pilha.h"
#include "carta.h"

void inicia_jogo(jogo solit, carta c){
  
   vetor_t* cartas = vetor_cria();
   vetor_t* fora_ordem = vetor_cria();
   srand(time(NULL));
   int i,j;
   
   for(i=0; i<=3; i++){
	  for(j=1; j<=13; j++){
		 c = carta_cria(j,i);
		 vetor_insere_carta(cartas, (i*13)+j-1, c);
	  }
   }
   
   for(i=0; i <52; i++){//retira da sequencia e insere fora de ordem as cartas
	 
	  do{//testa se naquela posição já foi inserido/retirado
	    j = ((int) rand())%vetor_numelem(cartas);
	    c = vetor_remove_carta(cartas, j);
	  }while(c == NULL);
	  vetor_insere_carta(fora_ordem, i, c);//carta removida é inserida no baralho fora_ordem
  }
   
   for(i=0; i<7; i++){
	  for(j=0; j<=i; j++){
		 c = vetor_remove_carta(fora_ordem, 0);
		 pilha_insere_carta(jogo_pilha(solit, i), c);
	  }
	  carta_abre(c);
   }
	for(i=0; i<24; i++){
		 c = vetor_remove_carta(fora_ordem, 0);
		 pilha_insere_carta(jogo_monte(solit), c);
   }   
   vetor_destroi(cartas);
   vetor_destroi(fora_ordem);
}

bool termina_jogo(jogo solit){
  int i,cont=0; 
  for(i=0;i<4;i++){
    if(retorna_topo(jogo_ases(solit,i)) == 13)
      cont++;
  }
  return cont==4;
}

void tela_final(jogo solit, tela t, char tecla){
  if(tecla == 27){
    initscr();
    int x,y;
    tela_muda_cor(t,vermelho);
    getmaxyx(stdscr,y,x);
    move(y/2,x/2);
    printw("GAME OVER");
    getch();
    noecho();
    refresh();
    endwin();
  }else{
    initscr();
    int x,y;
    tela_muda_cor(t,verde);
    getmaxyx(stdscr,y,x);
    move(y/2,x/2);
    printw("CONGRATULATIONS YOU WIN !! :) ");
    getch();
    noecho();
    refresh();
    endwin();
  }
  
}

int main(void){
	carta ct;
	char tecla;
	jogo solit;
	solit = jogo_cria();
	inicia_jogo(solit,ct);	
	jogo_desenha(solit);
	
while(!termina_jogo(solit) && tecla != 27){	
		tecla = tela_le(jogo_tela(solit));
		switch(tecla){
		  case ' ' : //passa as cartas do monte para o descartes
		    if(pilha_vazia(jogo_monte(solit)))
		      descartes_to_monte(solit);
		    monte_to_descartes(solit); 
		    break;
		  case 'd': //passa as cartas do descartes para as pilhas
		    if(pilha_vazia(jogo_descartes(solit)))
		      printw("\n\nJogada Inválida Pilha vazia");
		    else{
		    tecla = tela_le(jogo_tela(solit)); 
		    select_pilhas_descartes(solit,tecla);
		    } 
		  break;
		  case '1'://move da pilha zero para outra pilha qualquer 
		      tecla = tela_le(jogo_tela(solit));
		      select_pilhas(solit,0,tecla);
		  break;  
 		  case '2'://move da pilha 1 para outra pilha qualquer
		     tecla = tela_le(jogo_tela(solit));
		     select_pilhas(solit,1,tecla);
		  break;
		  case '3':
		    tecla = tela_le(jogo_tela(solit));
		    select_pilhas(solit,2,tecla);
		  break;
		  case '4':
		    tecla = tela_le(jogo_tela(solit));
		    select_pilhas(solit,3,tecla);
		  break;
		  case '5':
		    tecla = tela_le(jogo_tela(solit));
		    select_pilhas(solit,4,tecla);
		  break;
		  case '6':
		    tecla = tela_le(jogo_tela(solit));
		    select_pilhas(solit,5,tecla);
		  break;
		  case '7':
		    tecla = tela_le(jogo_tela(solit));
		    select_pilhas(solit,6,tecla);
		  break;
		 case 'q':
		    if(pilha_vazia(jogo_ases(solit,0))){
 		      	printw("\n\nJogada Inválida Pilha vazia");
 		    }else{  
			tecla = tela_le(jogo_tela(solit));
			ct = pilha_remove_carta(jogo_ases(solit,0));
			select_pilhasAses(solit,0,tecla, ct);
		    }
		  break;
		  case 'w':
		     if(pilha_vazia(jogo_ases(solit,1))){
 		      	printw("\n\nJogada Inválida Pilha vazia");
 		    }else{  
			tecla = tela_le(jogo_tela(solit));
			ct = pilha_remove_carta(jogo_ases(solit,1));
			select_pilhasAses(solit,1,tecla, ct);
		    }
		  break;
		  case 'e':
		     if(pilha_vazia(jogo_ases(solit,2))){
 		      	printw("\n\nJogada Inválida Pilha vazia");
 		    }else{  
			tecla = tela_le(jogo_tela(solit));
			ct = pilha_remove_carta(jogo_ases(solit,2));
			select_pilhasAses(solit,2,tecla, ct);
		    }
		  break;
		  case 'r':
		     if(pilha_vazia(jogo_ases(solit,3))){
 		      	printw("\n\nJogada Inválida Pilha vazia");
 		    }else{  
			tecla = tela_le(jogo_tela(solit));
			ct = pilha_remove_carta(jogo_ases(solit,3));
			select_pilhasAses(solit,3,tecla, ct);
		    }
		  break;
		  default:
		    printw("\n\n\nJogada Inválida ou tecla inutilizável\n");
		  break;
	}
}
	tela_limpa(jogo_tela(solit));
	tela_final(solit,jogo_tela(solit),tecla);
	
	jogo_destroi(solit);
	
	/* relatório de memória */
	memo_relatorio();
	return 0;
}