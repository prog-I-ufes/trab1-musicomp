# trab1-musicomp
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


/*void carregaMatriz(FILE *file, int **linhas, int *colunas, float **matriz){
    int i = 0, j = 0;
    float valor, line[4000];

   // while(!feof(file)){
     //   i++;
//}
    while (fgets(line, sizeof(line), file))
    {
        i++;

        //Pega o primeiro elemento separado por uma virgula.
        valor = strtok(line,",");

        //Obtem os outros elementos até o fim da linha.
        while (valor != NULL)
        {
            j++;

            //printf("%s\n",valor);
            matriz[i][j] = valor;

            valor = strtok(NULL, ",");

        }
    }

} */

// Obtem informacoes sobre o total de linhas e o maximo de colunas por linha de um arquivo com separacao de virgulas
void obtemInfoArquivo(FILE *file, int *total_linhas, int *total_colunas){
	rewind(file);
	char line[4000]; // maximo tamanho possivel de uma linha, em caracteres
	char *valor;
	char caracter;
	int linhas, colunas, max_colunas = 0;
	linhas = 0;
	while (fgets(line, sizeof(line), file))
		{
     linhas ++;
		 colunas = 0;
			valor = strtok (line, ",");
      while (valor != NULL)
			{
			    colunas ++;
					valor = strtok (NULL, ",");
			//		printf("%i %i %s\n", linhas, colunas, valor);
		   }
			 if (colunas > max_colunas) {
					max_colunas = colunas;
			 }

		}
    *total_linhas = linhas;
		*total_colunas = max_colunas;
}

// aloca os vetores das variaveis K, TIPO e R para carga a partir do arquivo Config
void alocaVetoresConfig (int linhas, int *k, char *tipo, float *r) {
	int i;

	k = (int *) malloc(linhas * sizeof(int*));
  tipo = (char *) malloc(linhas * sizeof(char*));
  r = (float *) malloc(linhas * sizeof(float*));
}


// Obtem informacoes sobre o total de linhas e o maximo de colunas por linha de um arquivo com separacao de virgulas
void carregaArqConfig(FILE *file, int linhas, char *arq_Treino, char *arq_Teste, char *dir_Predicoes, int *k, char *tipo, float *r){
	rewind(file);
	char line[4000]; // maximo tamanho possivel de uma linha, em caracteres
	char *valor;
	int tamanho_linha[3];
	int max_string;
	char caracter;
	int linha = 0, num_caracteres = 0, i = 0;
	//*arq_Treino = '';
	//*arq_Teste = '';
	//*dir_Predicoes = '';
	// Primeiro loop - obtencao da quantidade de caracteres das 3 primeiras linhas
	while (linha < 4)
	   {
       linha ++;
			 tamanho_linha[linha] = 1;
			 caracter = ' ';
			  while (caracter != '\n')
				 {
		 		  fscanf(file, "%c", &caracter);
//	        printf ("NORMAL - Caracteres [%i] - caracter [%c]\n", tamanho_linha[linha], caracter);
		 		  if (caracter != '\n')
				    {
              tamanho_linha[linha] ++;

				    }
				 }
				 printf ("FINAL - Linhas [%i] Caracteres [%i]\n", linha, tamanho_linha[linha]);
		 }

    // Segundo loop - obtencao dos conteudos das 3 primeiras linhas
     rewind(file);
		 linha = 0;
		 while (linha < 4)
	 	   {
				 linha ++;
					 printf ("INICIAL - Linhas [%i] Caracteres [%i] caracter [%c]\n", linha, tamanho_linha[linha], caracter);
				 if (linha == 1) { // primeira linha do arquivo Config - nome do arquivo treino
					  // memcpy (arq_Treino, &line, sizeof(line));
						max_string = tamanho_linha[linha] + 1;
						char sArq_Treino[max_string];
					//	fscanf(file, "%c", &caracter);
					//	printf ("INTERMED - Linhas [%i] Caracteres [%i] caracter [%c]\n", linha, tamanho_linha[linha], caracter);
					//	fscanf(file, "%c", &caracter);
          //  printf ("INTERMED - Linhas [%i] Caracteres [%i] caracter [%c]\n", linha, tamanho_linha[linha], caracter);


					  fgets (sArq_Treino, max_string, file);
						printf ("sArq_Treino___: %s", sArq_Treino);
						//*arq_Treino = &sArq_Treino;
				 }
				 if (linha == 2) { // segunda linha do arquivo Config - nome do arquivo teste
					  // memcpy (arq_Teste, &line, sizeof(line));
					  // fgets (arq_Teste, tamanho_linha[linha] - 10, file);
//						printf ("arq_Treino: %s", arq_Teste);
				 }
				 if (linha == 3) { // terceira linha do arquivo Config - nome do diretorio para armazenamento dos arquivos de predicoes
		        // memcpy (dir_Predicoes, &line, sizeof(line));
						// fgets (dir_Predicoes, tamanho_linha[linha] - 10, file);
//						printf ("dir_Predicoes: %s", dir_Predicoes);
						break;   // forca a saida do while, para continuar no trecho de informacoes
				 }
				printf ("NORMAL - SEGUNDO LOOP  - Linhas [%i] Caracteres [%i]\n", linha, tamanho_linha[linha]);
				caracter = ' ';
		    while (caracter != '\n')
					 {
			 		  fscanf(file, "%c", &caracter);
	//	        printf ("NORMAL - Caracteres [%i] - caracter [%c]\n", tamanho_linha[linha], caracter);
/*			 		  if (caracter != '\n')
					    {
	              tamanho_linha[linha] ++;

					    }
*/
					 }
					 printf ("FINAL - Linhas [%i] Caracteres [%i]\n", linha, tamanho_linha[linha]);
			 }
// return;
	// Terceiro loop - obtencao das demais linhas e vetores de configuracao
     rewind(file);
	for (i = 1; i <= linhas; i++)
	{
		// Obtem K e Tipo (M, E ou C)
		fscanf(file, "%i, %c,", &k[i], &tipo[i]);

		// Obtem R, caso Tipo seja M
		if (strncmp (&tipo[i], "M", 1) == 0) {  // Compara o primeiro byte com o caracter 1
			 fscanf(file, "%f", &r[i]);
	  }
	}
}

/*
void vetoresConfig (FILE *file, int linhas, int colunas){
	int i, j, k1[linhas-3];

	for(i = 3; i < feof(file); i++){
		for(j = 0; j < colunas; j++){
			if(j == 0){ fscanf(file, "%i", k);}
			if(j == 1){ fscanf(file, "%c", tipo);}
			if(j == 2){ fscanf(file, "%f", r);}
		}
	}

}
*/
// aloca uma matriz generica baseada em flat, que servirah para carga dos arquivos Treino e Teste
float** alocaMatrizGenerica (int *linhas, int *colunas){
		float **matrizGenerica;
		int i;
		matrizGenerica = (float **) malloc(*linhas * sizeof(float*));
		for (i = 0; i < *linhas; i++){
			matrizGenerica[i] = (float*) malloc (*colunas * sizeof(float));
		}
		return matrizGenerica;
	}


void carregaMatrizGenerica (FILE *file, float **matriz, int linhas, int colunas){
	int i, j;
	float matrizAux[linhas][colunas];


	for(i = 0; i < feof(file); i++){
		for(j = 0; j < colunas; j++){
			fscanf(file, "%f", &matriz[i][j]);
		}
	}

}

void desalocaMatrizGenerica (float **matriz, int *linhas)
{
	int i;

	for (i = 0; i < *linhas; i++)
	{
		free(matriz[i]);
	}

	free(matriz);
}

/*void obtemInfoArquivo1(FILE *file, int ***linhas, int *colunas){
	rewind(file);
	char caracter;
        int iniciaDado = 0;

	//Usando -1 para desativar a contagem de *colunas
	if (*colunas == -1) {
		while (!feof(file))
		{
			fscanf(file, "%c", &caracter);

			if (caracter == '\n') {**linhas = **linhas + 1;}
		}}

	else {
		while (!feof(file))
		{
			fscanf(file, "%c", &caracter);

			//Conta quantidade de dados por linha
			if (caracter != ' ') {
				if (caracter != '\n') {
					if (caracter != ',') {
						if (iniciaDado != 1) {
							iniciaDado = 1;
						}
					}
				}
			}
			if (**linhas == 0) {if (caracter == ',' || caracter == '\n') {if (iniciaDado == 1) {*colunas = *colunas + 1; iniciaDado = 0;}}}
			if (caracter == '\n') {**linhas = **linhas + 1;}
		}
			}

	**linhas--;
}
*/



int main(){
    FILE *file, *teste, *treino;
    int linhas = 0, colunas = 0, *k, linhasTreino = 0, linhasTeste = 0, colunasTreino = 0, colunasTeste = 0, i, j;
    float **matrizTreino, **matrizTeste, *r;
		char *tipo, *arq_Treino, *arq_Teste, *dir_Predicoes;


// Trata arquivo de configuracao
    file = fopen("config.txt", "r");
		// Verificar se o arquivo tem conteúdo.

		    if (file == NULL){
		        printf("Erro ao abrir o arquivo!\n");
		        exit(1);
		    }
		obtemInfoArquivo(file, &linhas, &colunas);
		printf("Total_linhas: %i - Maximo_colunas: %i\n", linhas, colunas);
    alocaVetoresConfig (linhas - 3, k, tipo, r); // serao alocadas n - 3 linhas, sendo que 3 sao destinadas indicar treino, teste e predicoes
		carregaArqConfig (file, linhas - 3, arq_Treino, arq_Teste, dir_Predicoes, k, tipo, r); // serao carregadas n - 3 linhas nos vetores k, tipo e r
    printf ("arq_Treino: [%s]\n", arq_Treino);
		printf ("arq_Treino: [%s]\n", arq_Teste);
		printf ("arq_Treino: [%s]\n", dir_Predicoes);
    fclose(file);

// Trata arquivo de Treino





  treino = fopen("/Users/luanacosta/Desktop/UFES/2º Período/Programação II.c/Trabson/bateria_validacao/iris/dataset/iris_treino.csv", "r");
	obtemInfoArquivo(treino, &linhasTreino, &colunasTreino);
	matrizTreino = alocaMatrizGenerica(&linhasTreino, &colunasTreino);
	carregaMatrizGenerica(treino, matrizTreino, linhasTreino, colunasTreino);

	for(i = 0; i < linhas; i++){
		for(j = 0; j < colunas; j++){
			printf("%.2f ", matrizTreino[i][j]);
		}
		printf("\n");

	}

    //carregaMatriz(treino, matrizTreino);

		//vetoresConfig(file, linhas, colunas, k, tipo, r);


// Trata arquivo de Teste

   teste = fopen("/Users/luanacosta/Desktop/UFES/2º Período/Programação II.c/Trabson/bateria_validacao/iris/dataset/iris_teste.csv", "r");
	 obtemInfoArquivo(teste, &linhasTeste, &colunasTeste);
	 printf(" %i %i\n", linhasTeste, colunasTeste);
    //carregaMatriz(teste, matrizTeste);


}
