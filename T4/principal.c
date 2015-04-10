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

#include "memo.h"
#include "jogo.h"
#include "vetor.h"
#include "fila.h"
#include "pilha.h"

void inicia_jogo(jogo solit){
  
   vetor_t* cartas = vetor_cria();
   vetor_t* fora_ordem = vetor_cria();
   srand(time(NULL));
   int i,j;
   carta c;
   
   for(i=0; i<=3; i++){
	  for(j=1; j<=13; j++){
		 c = carta_cria(j,i);
		 vetor_insere_carta(cartas, (i*13)+j-1, c);
	  }
   }
   
   for(i=0; i < 52; i++){//retira da sequencia e insere fora de ordem as cartas
	 
	  do{//testa se naquela posição já foi inserido/retirado
	    j = ((int) rand())%vetor_numelem(cartas);
	    c = vetor_remove_carta(cartas, j);
	  }while(c == NULL);
	  vetor_insere_carta(fora_ordem, i, c);//carta removida é inserida no baralho fora_ordem
  }
   
   for(i=0; i<7; i++){
	  for(j=0; j<=i; j++){
		 c= vetor_remove_carta(fora_ordem, 0);
		 pilha_insere_carta(jogo_pilha(solit, i), c);
	  }
	  carta_abre(c);
   }
	for(i=0; i<vetor_numelem(fora_ordem); i++){
		 c = vetor_remove_carta(fora_ordem, 0);
		 pilha_insere_carta(jogo_monte(solit), c);
   }   
   vetor_destroi(cartas);
   vetor_destroi(fora_ordem);
}

int main(void){
	jogo solit;
	solit = jogo_cria();
	inicia_jogo(solit);	
	jogo_desenha(solit);
	
	while(pilha_vazia(jogo_ases(solit,0))){	
		char tecla = tela_le(jogo_tela(solit));
		switch(tecla){
		  case ' ' : //passa as cartas do monte para o descartes
		    monte_to_descartes(solit);
		    if(pilha_vazia(jogo_monte(solit)))
		      descartes_to_monte(solit); 
		    break;
		  case 'd': //passa as cartas do descartes para as pilhas
		    tecla = tela_le(jogo_tela(solit));
		    switch(tecla){
		      case '0':   
			  descartes_to_pilha(solit,0);
		      break;
		      case '1':
			  descartes_to_pilha(solit,1);
		      break;
		      case '2':
			  descartes_to_pilha(solit,2);
		      break;
		      case '3':
			  descartes_to_pilha(solit,3);
		      break;
		      case '4':
			  descartes_to_pilha(solit,4);
		      break;
		      case '5':
			  descartes_to_pilha(solit,5);
		      break;
		      case '6':
			  descartes_to_pilha(solit,6);
		      break;
		   }
		  case '0'://move da pilha zero para outra pilha qualquer 
		      tecla = tela_le(jogo_tela(solit));
		      select_pilhas(solit,0,tecla);
		  break;  
 		  case '1'://move da pilha 1 para outra pilha qualquer
		     tecla = tela_le(jogo_tela(solit));
		     select_pilhas(solit,1,tecla);
		  break;
		  case '2':
		    tecla = tela_le(jogo_tela(solit));
		    select_pilhas(solit,2,tecla);
		  break;
		  case '3':
		    tecla = tela_le(jogo_tela(solit));
		    select_pilhas(solit,3,tecla);
		  break;
		  case '4':
		    tecla = tela_le(jogo_tela(solit));
		    select_pilhas(solit,4,tecla);
		  break;
		  case '5':
		    tecla = tela_le(jogo_tela(solit));
		    select_pilhas(solit,5,tecla);
		  break;
		  case '6':
		    tecla = tela_le(jogo_tela(solit));
		    select_pilhas(solit,6,tecla);
		  break;
	}
    }
	tela_le(jogo_tela(solit));
	jogo_destroi(solit);
	
	/* relatório de memória */
	memo_relatorio();
	return 0;
}