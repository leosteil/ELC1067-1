#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char**argv){//pega a busca em linha de comando
	char nome[50];
	char* busca = nome;
	
	if(argc > 1){
		busca = argv[1];
}
	int n,i,j=0,mat,tam=5,linha=0;
	char c,vet[50];
	float n1,n2;
	
	int* matriculasAluno;
	matriculasAluno = (int*) malloc(5*sizeof(int)); 
  
	char** nomes;
	nomes = (char**) malloc(5*sizeof(char*));
	for(i=0;i < 5; i++)
	  nomes[i] = (char*) malloc(50*sizeof(char));
		
	FILE*f = fopen("alunos.txt","r");
	if(f == NULL){
	        printf("Não foi possível abrir o arquivo ou o mesmo se encontra vazio\n");
	}else{ 
	  while(feof(f) == 0 ){     
	      if(linha == tam){//testa se a alocação foi passada do tamanho original e realloca
		  tam += 1;
		  matriculasAluno = (int*) realloc(matriculasAluno, sizeof(int)*tam);   
		  nomes = (char**) realloc(nomes, tam*sizeof(char*));
		    nomes[linha] = (char*) malloc(50*sizeof(char));
	      }else{ 
		  if(fscanf(f,"%d",&mat) < 0)//testar se o arquivo terminou 		
			break;//retorna o valor de EOF = -1 se o aquivo acabou
		  i=0;
		  c=fgetc(f);
		  while(c != '\n'){//busca nome até acabar a linha no alunos.txt
			vet[i] = c;
			i++;
			c=fgetc(f);			
		  }
		  vet[i]='\0';//delimita o final de cada linha
		  matriculasAluno[linha]= mat;//armazena todas as matriculas no vetor	
		  strcpy(nomes[linha],vet);//copia do vetor para a matriz

		  if( matriculasAluno == NULL || nomes == NULL || vet == NULL ) {
			puts("** Memória Insuficiênte **");
			exit(0);
		    }	
		  linha++;
	      }
	  }
	n = linha;//quantas linhas a busca deve percorrer no arquivo
	fclose(f);
	
	int* matriculasNota;
	matriculasNota = (int*) malloc(5*sizeof(int));
  
	float* media;
	media = (float*) malloc(5*sizeof(float));
	
	tam = 5;linha = 0;
        FILE *f = fopen("notas.txt","r");
	if(f == NULL){
	        printf("Não foi possível abrir o arquivo ou o mesmo se encontra vazio\n");
	}else{
	    while(feof(f) == 0){
	        if(linha == tam){
		    tam +=  1;
		    matriculasNota = (int*) realloc(matriculasNota,tam*sizeof(int));   
		    media = (float*) realloc(media, tam*sizeof(float));
		  }else{      
		    if(fscanf(f,"%d %f %f",&mat,&n1,&n2) < 0)//testar se o arquivo terminou EOF = -1 e pega os dados do FILE 	
			        break;  
		        matriculasNota[linha]= mat;//armazena todas as matriculas no vetor
		        media[linha] = (n1 + n2)/2;//calcula as médias e armazena no vetor 	
			linha++; 
		  }      
	      }
	  }
        for(i=0;i < n;i++){ 
             if(strstr(nomes[i],busca) != NULL){//avalia se contém algum nome relacionado com a busca
                while(matriculasAluno[i] != matriculasNota[j]){//verifica se a matricula é a mesma até achar
                        j++;
             }
                printf("\nNome: %s Media: %.3f\n",nomes[i],media[j]); //imprime o vetor de medias correspondente ao nome do aluno
	  }  
      }
	fclose(f);
	
	free(matriculasNota);
	free(media);
	free(matriculasAluno);
	for(i=0;i < linha ;i++)
	  free(nomes[i]);
	free(nomes);
  }
}