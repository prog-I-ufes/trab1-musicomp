/* 
Trabalho de Programação II _ Ciência da Computação 2018/2 - Universidade Federal do Espírito Santo. 
Professora Jordana Sarmengui Salamon 
Luana Gabriele de Sousa Costa 
*/ 
 
 
 
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include <math.h> 
 
 
// Obtem informacoes sobre o total de linhas e o maximo de colunas por linha de um arquivo com separacao de virgulas 
void obtemInfoArquivo(FILE *file, int *total_linhas, int *total_colunas){ 
    rewind(file); 
    char *valor, line[4000]; // maximo tamanho possivel de uma linha, em caracteres 
    int linhas = 0, colunas, max_colunas = 0; 
 
 
    while (fgets(line, sizeof(line), file)) 
        { 
     linhas ++; 
         colunas = 0; 
         valor = strtok (line, ","); 
     while (valor != NULL){ 
                colunas ++; 
                    valor = strtok (NULL, ","); 
            //        printf("%i %i %s\n", linhas, colunas, valor); 
           } 
 
             if (colunas > max_colunas){ 
                    max_colunas = colunas; 
             } 
 
         } 
    *total_linhas = linhas; 
        *total_colunas = max_colunas; 
} 
 
// aloca os vetores das variaveis K, TIPO e R para carga a partir do arquivo Config 
void alocaVetoresConfig (int linhas, int *k, char *tipo, float *r) { 
 
    k = (int *) malloc(linhas * sizeof(int*)); 
  tipo = (char *) malloc(linhas * sizeof(char*)); 
  r = (float *) malloc(linhas * sizeof(float*)); 
} 
 
 
// Obtem e retorna o conteudo de uma linha informada do arquivo Config 
char* obtemLinhaArqConfig (FILE *file, int linha_informada){ 
    rewind(file); 
    int tamanho_linha[3], linha = 0, max_string; 
    char caracter; 
 
    // Primeiro loop - obtencao da quantidade de caracteres da linha informada 
//    printf ("\nLOOP 1 - INICIAL - Linha informada [%i]\n", linha_informada); 
    while (linha < linha_informada){ 
       linha ++; 
             tamanho_linha[linha] = 1; 
             caracter = ' '; 
 
             while (caracter != '\n'){ 
                   fscanf(file, "%c", &caracter); 
//            printf ("NORMAL - Caracteres [%i] - caracter [%c]\n", tamanho_linha[linha], caracter); 
                   if (caracter != '\n'){ 
                       tamanho_linha[linha] ++; 
                    } 
                 } 
//            printf ("\nLOOP 1 - FINAL - Linhas [%i] Caracteres [%i]\n", linha, tamanho_linha[linha]); 
         } 
// 
    // Segundo loop - obtencao dos conteudos da linha informada 
     rewind(file); 
         linha = 0; 
         while (linha < linha_informada + 1){ 
                 linha ++; 
//                     printf ("\nLOOP 2 - INICIAL - Linhas [%i] Caracteres [%i] caracter [%c]\n", linha, tamanho_linha[linha], caracter); 
                 max_string = tamanho_linha[linha]; 
         char sString [max_string]; 
                    fgets (sString, max_string, file); 
                        fscanf(file, "%c", &caracter); // avanca um caracter, para considerar quebra de linha 
 
                 if (linha == linha_informada) { //  linha informada do arquivo Config 
//                        printf ("sString ____: %s\n\n\n", sString); 
            char * msg = (char*) malloc( (max_string) * sizeof(char) ); 
            strncpy( msg, sString, max_string); 
            return msg; 
                        break;   // forca a saida do while, para continuar no trecho de informacoes 
                 } 
//                printf ("\n\nLOOP 2 - FINAL - Linhas [%i] Caracteres [%i]\n", linha, tamanho_linha[linha]); 
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
// aloca uma matriz generica baseada em float, que servirah para carga dos arquivos Treino e Teste 
float** alocaMatrizFloat (int *linhas, int *colunas){ 
        float **matrizGenerica; 
        int i; 
 
        matrizGenerica = (float **) malloc(*linhas * sizeof(float*)); 
        for (i = 0; i < *linhas; i++){ 
            matrizGenerica[i] = (float*) malloc (*colunas * sizeof(float)); 
        } 
        return matrizGenerica; 
    } 
 
// aloca uma matriz generica baseada em int 
int** alocaMatrizInt (int *linhas, int *colunas){ 
        int **matrizGenerica; 
        int i; 
 
        matrizGenerica = (int **) malloc(*linhas * sizeof(int*)); 
        for (i = 0; i < *linhas; i++){ 
            matrizGenerica[i] = (int*) malloc (*colunas * sizeof(int)); 
        } 
        return matrizGenerica; 
    } 
  
 
 
 
// Função que aloca uma matriz int inicializada com zeros; 
int** alocaMatrizConfusao (int *linhas){ 
        int **matrizConfusao; 
        int i; 
        matrizConfusao = (int **) malloc(*linhas * sizeof(int*)); 
        for (i = 0; i < *linhas; i++){ 
            matrizConfusao[i] = (int*) calloc (*linhas, sizeof(int)); 
        } 
        return matrizConfusao; 
  } 
 
 
// Carrega com os valores as matrizes de teste e treino; 
float** carregaMatrizGenerica (FILE *file, float **matriz, int linhas, int colunas){ 
    int i, j; 
    float aux; 
 
 
    rewind(file); 
    //printf("%i %i AAAAAA\n", linhas, colunas); 
 
    for(i = 0; i < linhas; i++){ 
        for(j = 0; j < colunas; j++){ 
            fscanf(file, "%f,", &aux); 
            //printf("%f oi\n", aux); 
            matriz[i][j] = aux; 
 
        } 
    } 
    // for(i = 0; i < linhas; i++){ 
    //     for(j = 0; j < colunas; j++){ 
    //         //printf("%.2f ", matriz[i][j]); 
    //     } 
    //     //printf("\n"); 
    // 
    // } 
 
 
    return matriz; 
} 
 
void desalocaMatrizFloat (float **matriz, int *linhas){ 
    int i; 
 
    for (i = 0; i < *linhas; i++){ 
        free(matriz[i]); 
    } 
 
    free(matriz); 
}


void desalocaMatrizConfusao (int **matriz, int *linhas){ 
    int i; 
 
    for (i = 0; i < *linhas; i++){ 
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
 
 
 
// Calcula a distancia euclidiana 
void distEuc(float **matrizTreino, float **matrizTeste, float **dist, int colunas, int linhasTreino, int linhasTeste, int i){ 
        int j, k; 
        float soma = 0, potencia, euclidiana, rotulo; 
 
            for(j = 0; j < linhasTreino; j++){ 
                for(k = 0; k < (colunas - 1); k++){ 
                    potencia = pow((matrizTeste[i][k] - matrizTreino[j][k]),2); 
                    soma = soma + potencia; 
 
                } 
 
                euclidiana = sqrt(soma); 
                rotulo = matrizTreino[j][colunas - 1]; 
            //    printf("i[%i],j[%i],k[%i] - euclidiana [%.2f] rotulo [%.2f]\n", i,j,k,euclidiana, rotulo); 
                        dist[j][0] = euclidiana; 
                        dist[j][1] = rotulo; 
                        soma = 0; 
                    } 
} 
 
// Calcula a distancia de Minkowsky 
void distMkw(float **matrizTreino, float **matrizTeste, float **dist, int colunas, int linhasTreino, int linhasTeste, int i, float r){ 
        int j, k; 
        float soma = 0, potencia, delta, Minkowsky, rotulo; 
 
//      printf("LinhasTreino [%i] - Minkowsky \n", linhasTreino); 
            for(j = 0; j < linhasTreino; j++){ 
                for(k = 0; k < (colunas - 1); k++){
				    if (matrizTeste[i][k] > matrizTreino[j][k]) {
                        delta = matrizTeste[i][k]  - matrizTreino[j][k];
                    } else {
                        delta = matrizTreino[j][k] - matrizTeste[i][k];						
					};					
                    potencia = pow(delta,r); 
                    soma = soma + potencia; 
 
                } 
 
                Minkowsky = pow(soma, 1/r); 
                rotulo = matrizTreino[j][colunas - 1]; 
          //      printf("i[%i],j[%i],k[%i] - Minkowsky [%.2f] rotulo [%.2f]\n", i,j,k,Minkowsky, rotulo); 
                        dist[j][0] = Minkowsky; 
                        dist[j][1] = rotulo; 
                        soma = 0; 
                    } 
} 
 
 
// Calcula a distancia de Chebyshev 
void distChb(float **matrizTreino, float **matrizTeste, float **dist, int colunas, int linhasTreino, int linhasTeste, int i){ 
        int j, k; 
        float soma = 0, delta, Chebyshev = 0, rotulo; 

//      printf("LinhasTreino [%i] - Chebyshev \n", linhasTreino); 		
            for(j = 0; j < linhasTreino; j++){ 
                for(k = 0; k < (colunas - 1); k++){ 
				    if (matrizTeste[i][k] > matrizTreino[j][k]) {
                        delta = matrizTeste[i][k]  - matrizTreino[j][k];
                    } else {
                        delta = matrizTreino[j][k] - matrizTeste[i][k];						
					};
                    if (delta > Chebyshev) {  // considera o maior valor
                           Chebyshev = delta; 
                    }; 
 
                } 
 
                rotulo = matrizTreino[j][colunas - 1]; 
          //      printf("i[%i],j[%i],k[%i] - Chebyshev [%.2f] rotulo [%.2f]\n", i,j,k,Chebyshev, rotulo); 
                        dist[j][0] = Chebyshev; 
                        dist[j][1] = rotulo;
                        Chebyshev = 0; 
                    } 
} 
 
 
 
// Ordena a matriz dada com base na primeira coluna
float** bubbleSort(float **matriz, int linhas){ 
        int i, j; 
        float aux, aux1; 
 
 
        for(j = (linhas - 1); j > -1; j--){ 
            for(i = 0; i < j; i++){ 
                if(matriz[i][0] > matriz[i + 1][0]){ 
                    aux = matriz[i][0]; 
                    matriz[i][0] = matriz[i + 1][0]; 
                    matriz[i + 1][0] = aux; 
                    aux1 = matriz[i][1]; 
                    matriz[i][1] = matriz[i + 1][1]; 
                    matriz[i + 1][1] = aux1; 
                    } 
            } 
        } 
 /*
        for(i = 0; i < linhas; i++){ 
                printf("BUBBLE: %.2f oi %.2f\n", matriz[i][0], matriz[i][1]); 
        } 
 */
        return matriz; 
} 
 
 
 
// Compara os rótulos retornando apenas a quantidade de vezes que foi igual e a que foi diferente. 
int compRotulos(int *vetorRotulo, float **matrizTeste, int linhasTeste,int colunasTeste){ 
  int i, ok = 0, rotuloTeste; 
  
  printf ("Teste [%i] [%i] [%i]\n", ok, linhasTeste, colunasTeste); 
  for(i = 0; i < linhasTeste; i++){ 
    rotuloTeste = (int)matrizTeste[i][colunasTeste - 1] - 1; // a coluna de rotulo da matriz teste foi convertida em int e subtraida de 1 para ficar no mesmo padrao que o vetorRotulo
    if(vetorRotulo[i] == rotuloTeste) 
      { 
        ok++;
      } 
//  printf ("Teste ok[%i] Vrotulo[%i] Mteste[%i]\n", ok, vetorRotulo[i], rotuloTeste); 
  }
//  printf ("OIIIIII\n"); 
  return ok;
} 
 
 
// Calcula a acurácia 
float fazAcuracia(int total, int ok){ 
  float acc = (float) ok / (float) total; 
//  printf("fazAcuracia [%f] = [%i] / [%i] \n", acc, ok, total); 
  return acc; 
} 
//  Conta o numero de rotulos distintos 
int contaRotulos(int *vetorRotulo, int tamanhoVetorRotulo){ 

    int linRotulo=100, iRotulo, n, numDistintos = 0; 
    int *rotulo; // armazena os rotulos (no maximo 100)
	rotulo = (int*) calloc (tamanhoVetorRotulo, sizeof(int)); 
	printf ("contaRotulos - tamanhoVetorRotulo [%i]\n", tamanhoVetorRotulo);
   	for(n = 0; n < tamanhoVetorRotulo; n++){ 
		 for (iRotulo = 0; iRotulo < 100; iRotulo ++ ){ 
//				printf ("iROTULO [%i]: rotulo[%i]\n", iRotulo, rotulo[iRotulo]); 
			  if (rotulo[iRotulo] == 0){ // Compara com o valor inicial 
					 printf ("INICIA CONT [%i]\n", vetorRotulo[n]); 
					 rotulo[iRotulo] = vetorRotulo[n] + 1; // armazena rotulo (acrescido de 1 para evitar zero) 
					 numDistintos ++;
					 break; // sai 
					 }
			  else 
				 { if (rotulo[iRotulo] == vetorRotulo[n] + 1){ // armazena rotulo (acrescido de 1 para evitar zero) 
//					   printf ("EXISTENTE [%i]\n", vetorRotulo[n]); 
					   break; 
					}
				 }									 
		 } 
   } 
    free(rotulo); 
    return numDistintos;
} 
 
 
 
 
// Carrega a matriz de Confusão; 
// n = classificados, m = dados; 
int ** fazMatrizConfusao(int ** matrizConfusao, float ** matrizTeste, int * vetKNN, int numRotulos, int linhasTeste, int colunasTeste) {
  int m, n, classificado, dado, rotuloTeste, rotuloKNN;
  printf("fazMatrizConfusao numRotulos [%i] linhasTeste [%i]\n", numRotulos, linhasTeste);
  for (m = 0; m < linhasTeste; m++) { // Percorre os rótulos de matriz teste; 
       rotuloTeste = (int)matrizTeste[m][colunasTeste - 1] - 1; // a coluna de rotulo da matriz teste foi convertida em int e  subtraida de 1 para ficar no mesmo padrao que o vetorRotulo
	   rotuloKNN = vetKNN[m];
	   matrizConfusao [rotuloTeste][rotuloKNN] ++;
  }
  for (m = 0; m < numRotulos; m++) {
      for (n = 0; n < numRotulos; n++) {
		  printf ("%i ", matrizConfusao [m][n]);
	  }
	  printf ("\n");
  } 
  return matrizConfusao; //Retorna a matriz; 
}

// Printa os rotulos; 
void printPredicoes(char *dirPredicoes, int sufArqPred, float acc, int **matrizConfusao, int *retKNN, int linhasTeste, int numRotulos){ 
    char nomeArq[]="predicao_", msg[]="Falha no arquivo", extArq[] = ".txt"; 
    int sufArq = sufArqPred, tamSufArq = 0, n, m; 
    FILE *saida; 
    //Transformando o número em uma string 
    while (sufArq > 0){ 
        sufArq = sufArq/10; 
        tamSufArq++; 
    } 
 
    char sSufArq[tamSufArq]; 
    sprintf(sSufArq, "%i", sufArqPred); 
    char sNomeCompletoArq[strlen(dirPredicoes) + strlen(nomeArq) + tamSufArq + strlen(extArq)]; 
 
    strcpy(sNomeCompletoArq, dirPredicoes); 
    strcat(sNomeCompletoArq, nomeArq); 
    strcat(sNomeCompletoArq, sSufArq); 
    strcat(sNomeCompletoArq, extArq); 
 
 
    // Trata arquivo de configuracao 
    printf ("sNomeCompletoArq [%s]\n", sNomeCompletoArq); 
    saida = fopen(sNomeCompletoArq, "w"); 
        // Verificar se o arquivo tem conteúdo. 
 
    if (saida == NULL){ 
        printf (msg, sufArq); 
        exit(1); 
    } 
 	  fprintf (saida, "%.2f\n",acc);
 	  fprintf (saida, "\n");
  for (m = 0; m < numRotulos; m++) {
      for (n = 0; n < numRotulos; n++) {
		  fprintf(saida, "%i ", matrizConfusao [m][n]);
	  }
	  fprintf (saida, "\n");
  }  
	  fprintf (saida, "\n"); 
    for(int i = 0; i < linhasTeste; i++){ 
        fprintf(saida, "%i\n", retKNN[i]); 
//        printf ("printPredicoes [%i]\n", retKNN[i]); 
    } 
 
    fclose (saida); 
} 
 
void makeKNN(float **matrizTeste, float **matrizTreino, int parK, char parTipo, float parR, int colunas, int lTes, int lTre, int *retKNN, char *dirPredicoes, int sufArqPred){ 
    int i, n, linRotulo=100, colResult = 2,iRotulo, iR, ok = 0, notOk = 0, numRotulos, **matrizConfusao; 
    float acc, **dist = 0, **distOrd, **nprox, **rotulo; // armazena os rotulos na primeira coluna (no maximo 100) e quantidade de ocorrencias na segunda coluna 
//loop enquanto nao percorre todas as linhas da matrizTeste; 
    rotulo = 0; 
 
	int varK     = parK;    //7; 
	char varTipo = parTipo; // 'E'; 
	float varR   = parR;    // 0.0; 


	rotulo = alocaMatrizFloat(&linRotulo, &colResult); 
	dist = alocaMatrizFloat(&lTre, &colResult); 
	distOrd = alocaMatrizFloat(&lTre, &colResult); 
	nprox = alocaMatrizFloat(&varK, &colResult); 

 
            for (i = 0; i < lTes; i++){ 
//        printf ("parametros LINHA_TESTE[%i] varK[%i] varTipo[%c] varR[%f] lTes[%i]\n", i, varK, varTipo, varR, lTes); 
 
                if(varTipo == 'E'){             // redireciona pra Euclides; 
                   distEuc(matrizTreino, matrizTeste, dist, colunas, lTre, lTes, i); 
                } 
                  else { 
                    if(varTipo == 'M'){        //redireciona pra Minkowsky; 
                      //dist = distEuc(matrizTreino, matrizTeste, colunas, lTre, lTes, i); 
                      distMkw(matrizTreino, matrizTeste, dist, colunas, lTre, lTes, i, varR); 
                    } 
                    else { 
                        if(varTipo == 'C'){    //redireciona pra Chebychev; 
                          distChb(matrizTreino, matrizTeste, dist, colunas, lTre, lTes, i); 
                        } 
                    } 
            } 
/* 
                  for(n = 0; n < lTre; n++){ 
                        printf("Mostra_DESOrdenado: [%f] [%f]\n", dist[n][0], dist[n][1]); 
                  } 
*/ 
                // printf("oe\n"); 
            // ordena; 
        distOrd = bubbleSort(dist, lTre); // ordena a matriz pela primeira coluna (distancia) 
/* 
                  for(n = 0; n < varK; n++){ // n < lTre; n++){ 
                        printf("Mostra_Ordenado: [%f] [%f]\n", distOrd[n][0], distOrd[n][1]); 
                  } 
*/ 
                  // return; 
 
 
            // zera matriz rotulo (apenas a primeira coluna) 
            for (iRotulo = 0; iRotulo < 100; iRotulo ++ ){ 
                  rotulo[iRotulo][0] = 0; 
            } 
 
            // forma matriz com os k mais proximos, incluindo quantidade [primeira coluna] e  rotulo [segunda coluna]; 
            for(n = 0; n < varK; n++){ 
                     for (iRotulo = 0; iRotulo < 100; iRotulo ++ ){ 
//                            printf ("iROTULO [%i]: rotulo[%f]\n", iRotulo, rotulo[iRotulo][1]); 
                          if (rotulo[iRotulo][0] == 0){ 
//                                 printf ("INICIA CONT [%f]\n", distOrd[n][0]); 
                                 rotulo[iRotulo][0] = 1;   // inicia a contagem         [primeira coluna] 
                                 rotulo[iRotulo][1] = distOrd[n][1]; // armazena rotulo [segunda coluna] 
                                 break; // sai 
                                 } 
                            else { if (rotulo[iRotulo][1] == distOrd[n][1]){ 
                                                rotulo[iRotulo][0] = rotulo[iRotulo][0] + 1;   // incrementa a quantidade de ocorrencias 
//                                    printf ("ADICIONA CONT [%f]\n", distOrd[n][0]); 
                                         break; 
                                     } 
                            } 
//                            printf ("iROTULO [%i]: cont[%f], rotulo[%f], n[%i]\n", iRotulo, rotulo[iRotulo][0], rotulo[iRotulo][1], n); 
                     } 
           } 
 
        for (iRotulo = 0; iRotulo < 100; iRotulo ++ ){ 
                if (rotulo[iRotulo][0] == 0){ 
                    break; 
                } 
//                printf("Mostra_ROTULO [%i]: cont[%.2f] rotulo[%f] \n", iRotulo,rotulo[iRotulo][0],rotulo[iRotulo][1]); 
        } 
 
		distOrd = bubbleSort(rotulo, iRotulo); 
        for (iRotulo = 0; iRotulo < 100; iRotulo ++ ) { 
                if (rotulo[iRotulo][0] == 0) { 
                    break; 
                } 
//                printf("Mostra_ROTULO_ORDENADO [%i]: cont[%.2f] rotulo[%f] \n", iRotulo,distOrd[iRotulo][0],distOrd[iRotulo][1]); 
        } 
 
// Obtencao do rotulo mais frequente e de menor valor (comeca considerando que o ultimo atende a esse criterio) 
     float menor_rotulo = 0, maior_cont = 0; 
     iR = iRotulo - 1; 
     maior_cont   = rotulo[iR][0]; // quantidade [primeira coluna] 
     menor_rotulo = rotulo[iR][1]; // rotulo     [segunda coluna]
//         printf("maior_cont [%f] \n", rotulo[iR][0]); 
//         printf("PRIMEIRO menor_rotulo [%f] \n", menor_rotulo); 
 
          for (iR = iRotulo - 1; iR > 0; iR -- ){ 
                     if (rotulo[iR][0] == maior_cont){ 
              if (rotulo[iR][1] < menor_rotulo){ 
                         menor_rotulo = rotulo[iR][1]; 
 
//                         printf("NOVO menor_rotulo [%f] \n", menor_rotulo); 
                             } 
                         }    else{ 
                                             break; 
                 } 
         } 
        retKNN[i] = (int)menor_rotulo - 1;  // Converte menor rotulo em inteiro e subtrai 1 (2.0 vai ficar 1, 3.0 vai ficar 2, etc.)
//        printf("Mostra_MENOR_ROTULO_DE_INTERESSE LINHA_TESTE[%i] rotulo[%i] cont[%f] \n", iR, retKNN[i], maior_cont); 

 
 
            // for(m = 0; m < varK; m++){ 
            //     for(n = 0; n < colResult; n++){ 
            //         printf("%.2f ", nprox[m][n]); 
            //     } 
            //     printf("\n"); 
            // } 
 
 
        // desalocaMatrizFloat(nprox, &varK); 
    } 
//        printf("FINAL KNN \n"); 
        desalocaMatrizFloat(rotulo, &linRotulo); 
//        printf("APOS KNN - desaloca rotulo \n"); 
        desalocaMatrizFloat(dist, &lTre); 
//        printf("APOS KNN - desaloca dist \n"); 
//        desalocaMatrizFloat(distOrd, &lTre); 
//        printf("APOS KNN - desaloca distOrd \n"); 
        desalocaMatrizFloat(nprox, &varK); 
//        printf("APOS KNN - desaloca nprox \n"); 
 
// Chama a função que retorna o numero de rotulos que sao iguais aos reais; 
        ok = compRotulos(retKNN, matrizTeste, lTes, colunas); 
//         printf("APOS KNN - compRotulos [%i] [%i] \n", ok, lTes); 
// Chama a função que calcula a acuracia; 
        acc = fazAcuracia(lTes, ok); 
//          printf("APOS KNN - fazAcuracia [%f] \n", acc); 
		  
        numRotulos = contaRotulos(retKNN, lTes);
//          printf("APOS KNN - contaRotulos [%i] \n", numRotulos); 		
 
        matrizConfusao = alocaMatrizConfusao(&numRotulos); 
//          printf("APOS KNN - matrizConfusao \n"); 		
 
// Chama a função que calcula e carrega a matriz de confusão; 
        fazMatrizConfusao(matrizConfusao, matrizTeste, retKNN, numRotulos, lTes, colunas);
//          printf("APOS KNN - fazMatrizConfusao \n"); 			

    printPredicoes(dirPredicoes, sufArqPred, acc, matrizConfusao, retKNN, lTes, numRotulos); 		   
                desalocaMatrizConfusao(matrizConfusao, &numRotulos); 
//           printf("APOS KNN - desalocaMatrizConfusao \n");
	} 
 
 
// Obtem informacoes do arquivo Config contendo os parametros de predicoes e processa as predicoes 
void carregaParamProcessaPredicoes (FILE *file, int linhas, float **matrizTeste, float **matrizTreino, int colunasTeste, int linhasTeste, int linhasTreino, char *dirPredicoes){ 
    rewind(file); 
    int tamanho_linha[3], lK[1000], linha = 0, i = 0, sufArqPred=0, *retKNN; 
  float lR[1000]; 
  char lTipo[1000], caracter; 
 
    while (linha < 3){ 
       linha ++; 
             tamanho_linha[linha] = 1; 
             caracter = ' '; 
 
             while (caracter != '\n'){ 
                   fscanf(file, "%c", &caracter); 
//            printf ("NORMAL - Caracteres [%i] - caracter [%c]\n", tamanho_linha[linha], caracter); 
                   if (caracter != '\n'){ 
             tamanho_linha[linha] ++; 
                    } 
                 } 
//            printf ("FINAL - Linhas [%i] Caracteres [%i]\n", linha, tamanho_linha[linha]); 
         } 
 
    for (i = linha; i < linhas; i++){ 
 
        // Obtem K e Tipo (M, E ou C) 
//        printf ("ANTES ------\n"); 
        fscanf(file, "%i, %c, ", &lK[i], &lTipo[i]); 
 
        if (lTipo[i] == 'M'){  // Compara o primeiro byte com o caracter 1 
             fscanf(file, "%f", &lR[i]); 
        } 
            sufArqPred ++;  // Define sufixo do arquivo de predicoes 
//    printf ("carregaParamProcessaPredicoes - Linha_Config [%i], K[%i], TIPO[%c] e R[%f] \n",  i, lK[i], lTipo[i], lR[i]); 
 
        retKNN = (int*) malloc (linhasTeste * sizeof(int)); 
        makeKNN(matrizTeste, matrizTreino, lK[i], lTipo[i], lR[i], colunasTeste, linhasTeste, linhasTreino, retKNN, dirPredicoes, sufArqPred); 
        // printf ("APOS KNN K [%i], TIPO [%c] E R [%f] \n",  lK[i], lTipo[i], lR[i]); 
    free(retKNN); 
    } 
 
} 
 
 
 
 
 
int main(){ 
    FILE *file, *teste, *treino; 
    int linhas = 0, colunas = 0, *k = NULL, linhasTreino = 0, linhasTeste = 0, colunasTreino = 0, colunasTeste = 0; 
    float **matrizTreino = 0, **matrizTeste = 0, *r = NULL; 
         char *tipo = NULL, *arq_Treino, *arq_Teste, *dir_Predicoes; 
 
 
// Trata arquivo de configuracao 
    file = fopen("config.txt", "r"); 
        // Verificar se o arquivo tem conteúdo. 
 
    if (file == NULL){ 
        printf("Erro ao abrir o arquivo config.txt!\n"); 
        exit(1); 
    } 
    obtemInfoArquivo(file, &linhas, &colunas); 
    // printf("Total_linhas: %i - Maximo_colunas: %i\n", linhas, colunas); 
  alocaVetoresConfig (linhas - 3, k, tipo, r); // serao alocadas n - 3 linhas, sendo que 3 sao destinadas indicar treino, teste e predicoes 
    // carregaArqConfigPaths (file, linhas - 3, arq_Treino, arq_Teste, dir_Predicoes, k, tipo, r); // serao carregadas n - 3 linhas nos vetores k, tipo e r 
    arq_Treino = obtemLinhaArqConfig (file, 1); 
    arq_Teste = obtemLinhaArqConfig (file, 2); 
    dir_Predicoes = obtemLinhaArqConfig (file, 3); 
//    printf ("arq_Treino: [%s]\n", arq_Treino); 
//    printf ("arq_Teste: [%s]\n", arq_Teste); 
//    printf ("dir_Predicoes: [%s]\n", dir_Predicoes); 
 
// Trata arquivo de Treino 
//  treino = fopen("/Users/luanacosta/Desktop/UFES/2º Período/Programação II.c/Trabson/bateria_validacao/iris/dataset/iris_treino.csv", "r"); 
    treino = fopen(arq_Treino, "r"); 
    if (treino == NULL){ 
        printf("Erro ao abrir o arquivo [%s]!\n", arq_Treino); 
        exit(1); 
    } 
 
    obtemInfoArquivo(treino, &linhasTreino, &colunasTreino); 
 
    // printf(" %i %i\n", linhasTreino, colunasTreino); 
    matrizTreino = alocaMatrizFloat(&linhasTreino, &colunasTreino); 
    matrizTreino = carregaMatrizGenerica(treino, matrizTreino, linhasTreino, colunasTreino); 
 
    // for(i = 0; i < linhasTreino; i++){ 
    //     for(j = 0; j < colunasTreino; j++){ 
    //         printf("%.2f ", matrizTreino[i][j]); 
    //     } 
    //     printf("\n"); 
    // } 
 
    //carregaMatriz(treino, matrizTreino); 
 
        //vetoresConfig(file, linhas, colunas, k, tipo, r); 
 
 
// Trata arquivo de Teste 
 
    teste = fopen(arq_Teste, "r"); 
    if (treino == NULL){ 
        printf("Erro ao abrir o arquivo [%s]!\n", arq_Teste); 
        exit(1); 
    } 
//    teste = fopen("/Users/luanacosta/Desktop/UFES/2º Período/Programação II.c/Trabson/bateria_validacao/iris/dataset/iris_teste.csv", "r"); 
    obtemInfoArquivo(teste, &linhasTeste, &colunasTeste); 
     //printf(" %i %i\n", linhasTeste, colunasTeste); 
 
    matrizTeste = alocaMatrizFloat(&linhasTeste, &colunasTeste); 
    matrizTeste = carregaMatrizGenerica(teste, matrizTeste, linhasTeste, colunasTeste); 
    //carregaMatriz(teste, matrizTeste); 
        /*for(i = 0; i < linhasTeste; i++){ 
            printf("\nluanaTeste %i\n", i); 
            for(j = 0; j < colunasTeste; j++){ 
                printf("%.2f ", matrizTeste[i][j]); 
            } 
        }*/ 
 
    carregaParamProcessaPredicoes (file, linhas, matrizTeste, matrizTreino, colunasTeste, linhasTeste, linhasTreino, dir_Predicoes); 
    fclose(file); 
 
    return 0; 
}
