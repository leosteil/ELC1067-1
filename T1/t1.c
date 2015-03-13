#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void le_alunos(int* matriculasAluno, char nomes[][50], int *n){
	int mat;
	char c;
	char nome[50];
	int i,linha = 0;
	FILE*f = fopen("alunos.txt","r");
	if(f == NULL){
	        printf("Não foi possível abrir o arquivo ou o mesmo se encontra vazio\n");
	}else{ 
	while(feof(f) == 0 ){
		if(fscanf(f,"%d",&mat) < 0)//testar se o arquivo terminou 		
			break;//retorna o valor de EOF = -1 se o aquivo acabou
		i=0;
		c=fgetc(f);
		while(c != '\n'){//busca nome até acabar a linha no alunos.txt
			nome[i] = c;
			i++;
			c=fgetc(f);			
		}
		        nome[i]='\0';//delimita o final de cada linha
		        matriculasAluno[linha]= mat;//armazena todas as matriculas no vetor
			strcpy(nomes[linha],nome);
			linha++;			
	}
	        *n = linha;//quantas linhas a busca deve percorrer no arquivo
	        fclose(f);
        }
}

void le_notas(int* matriculasNota, float* media){
        float n1,n2;
        int linha =0,mat;
        FILE *f = fopen("notas.txt","r");
	if(f == NULL){
	        printf("Não foi possível abrir o arquivo ou o mesmo se encontra vazio\n");
	}else{
	        while(feof(f) == 0){
	                if(fscanf(f,"%d %f %f",&mat,&n1,&n2) < 0)//testar se o arquivo terminou EOF = -1 e pega os dados do FILE 	
			        break;  
		        matriculasNota[linha]= mat;//armazena todas as matriculas no vetor
		        media[linha] = (n1 + n2)/2;//calcula as médias e armazena no vetor 
		        linha++;  
	        }  
                
        }
        fclose(f);
}

void media_alunos(int* n, char* busca, char nomes[][50], int* matriculasAlunos, int* matriculasNota, float* media){
  int i,j;
        for(i=0;i<*n;i++){
                j=0; 
             if(strstr(nomes[i],busca) != NULL){//avalia se contém algum nome relacionado com a busca
                while(matriculasAlunos[i] != matriculasNota[j]){//verifica se a matricula é a mesma até achar
                        j++;
             }
                printf("Nome: %s Media: %.3f\n",nomes[i],media[j]); //imprime o vetor de medias correspondente ao nome do aluno
        }  
    }     
} 


int main(int argc, char**argv){//pega a busca em linha de comando
	char nome[50];
	char* busca = nome;
	if(argc > 1){
		busca = argv[1];
}	
	int matriculasAluno[50];
	int matriculasNota[50];
	char nomes[50][50];
	float media[50];
	int n;
	
	le_alunos(matriculasAluno,nomes,&n);
	le_notas(matriculasNota,media);
	media_alunos(&n,busca,nomes,matriculasAluno,matriculasNota,media); 

	return 0;
}
