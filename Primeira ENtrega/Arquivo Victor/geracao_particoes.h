#ifndef GERACAO_PARTICOES_H
#define GERACAO_PARTICOES_H

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "nomes.h"
#include "cliente.h"
#include "stdbool.h"

#include "nomes.h"


// Executa o algoritmo de geracao de particoes por Classificacao Interna
// nome_arquivo_entrada: nome do arquivo de entrada
// nome_arquivo_saida: lista encadeada com nomes de arquivos de saida
// M: tamanho do array em memoria para manipulacao dos registros
void classificacao_interna(char *nome_arquivo_entrada, Nomes *nome_arquivos_saida, int M) {

    int fim = 0; //variável de controle para saber se arquivo de entrada terminou
    FILE *arq; //declara ponteiro para arquivo

    //abre arquivo para leitura
    if ((arq = fopen(nome_arquivo_entrada, "rb")) == NULL) {
        printf("Erro ao abrir arquivo de entrada\n");
    } else {

        //le primeiro cliente
        TCliente *cin = le_cliente(arq);
        
        while (!(fim)) {
            //le o arquivo e coloca no vetor
            TCliente *v[6];

            int i = 0;
            while (!feof(arq) && i < M) {
                v[i] = cin;
                cin = le_cliente(arq);
                i++;
            }

            //ajusta tamanho M caso arquivo de entrada tenha terminado antes do vetor
            if (i != M) {
                M = i;
            }

            //faz ordenacao
            for (int j = 1; j < M; j++) {
                TCliente *c = v[j];
                i = j - 1;
                while ((i >= 0) && (v[i]->cod_cliente > c->cod_cliente)) {
                    v[i + 1] = v[i];
                    i = i - 1;
                }
                v[i + 1] = c;
            }

            //cria arquivo de particao e faz gravacao
            char *nome_particao = nome_arquivos_saida->nome;
            nome_arquivos_saida = nome_arquivos_saida->prox;

            FILE *p;
            if ((p = fopen(nome_particao, "wb")) == NULL) {
                printf("Erro criar arquivo de saida\n");
            } else {
                for (int i = 0; i < M; i++) {
                    salva_cliente(v[i], p);
                }
                fclose(p);
            }
            if (feof(arq)) {
                fim = 1;
            }
        }
    }
}
int posicao_menor_valor(TCliente* array[ ], int m){
    int posicao_menor = -1;
    int menorValor = 0;
    printf("%d",sizeof(array));
    for (int a = 0; a < m; a++)
    {
        if (a == 0)
        {
            posicao_menor = a;
            menorValor = array[a]->cod_cliente;
        }
        else
        {
            if (array[a]->cod_cliente < menorValor)
            {
                posicao_menor = a;
                menorValor = array[a]->cod_cliente;
            }
        }
    }
    return posicao_menor;
}
int esta_cheio(FILE *arquivo_entrada,int M){
    int i=0;
    TCliente *cliente = (TCliente *) malloc(sizeof(TCliente));
    while(!feof(arquivo_entrada)){
        fread(cliente->nome, sizeof(char), sizeof(cliente->nome), arquivo_entrada);
        i++;
        free(cliente);
    }
    if(i<M){
        return 1;
    }
    else{
        return 0;
    }
    
}
// Executa o algoritmo de geracao de particoes por Selecao com Substituicao
// nome_arquivo_entrada: nome do arquivo de entrada
// nome_arquivo_saida: lista encadeada com nomes de arquivos de saida
// M: tamanho do array em memoria para manipulacao dos registros
void selecao_com_substituicao(char *nome_arquivo_entrada, Nomes *nome_arquivos_saida, int M) {
    //inserir codigo
  
}


// Executa o algoritmo de geracao de particoes por Selecao Natural
// nome_arquivo_entrada: nome do arquivo de entrada
// nome_arquivo_saida: lista encadeada com nomes de arquivos de saida
// M: tamanho do array em memoria para manipulacao dos registros
// n: tamanho do reservatorio
void selecao_natural(char *nome_arquivo_entrada, Nomes *nome_arquivos_saida, int M, int n) {
    //TODO: Inserir aqui o codigo do algoritmo de geracao de particoes
    FILE *arq; //declara ponteiro para arquivo
   //abre arquivo para leitura
   //

   if ((arq = fopen(nome_arquivo_entrada, "rb")) == NULL)
   {
       printf("Erro ao abrir arquivo de entrada\n");
   }
   else
   {
                char *nome_particao = nome_arquivos_saida->nome;
                nome_arquivos_saida = nome_arquivos_saida->prox;
                FILE *reservatorio;
                
                if(reservatorio = fopen("reservatorio.dat","wb")==NULL){
                    printf("Erro ao abrir reservatório\n");
                }

                FILE *particao_saida;



                if(particao_saida= fopen(nome_particao, "wb")){
                    printf("Abriu arquivo de Partição %s \n\n",nome_particao);
                }
                    TCliente *cin=(TCliente *) malloc(sizeof(TCliente));

                TCliente *v= (TCliente *)malloc(sizeof(TCliente) * M);
                fread(cin, sizeof(TCliente),1, arq);
                        // Pega M registros do arquivo de entrada e coloca-os no array
                        for(int i=0;i<M;i++){
                                fread(&v[i], sizeof(TCliente), 1, arq);
                            }
                        printf("ARRAY em memoria \n");
                        for(int j=0;j<M;j++){
                            printf("%s \n",v[j].nome);
                        }
                do{

                        // aloca memoria para variavel auxiliar cliente
                        TCliente chave_recem_gravada ;
                        int i = 0, posicao_menor=0;
                        // TCliente *posicao = (TCliente *)malloc(sizeof(TCliente));

                            // executa passo 2, procura o posicao com menor valor e grava na particao de saida
                            // depois lê o proximo registro do arquivo e coloca na antiga posicao do array em memoria
                        // procura menor valor no array
                            int menorValor=0;
                            for (int a = 0; a < M; a++){
                                        if (a == 0)
                                        {
                                            posicao_menor = a;
                                            menorValor = v[a].cod_cliente;
                                        }
                                        else
                                        {
                                            if (v[a].cod_cliente < menorValor)
                                            {
                                                posicao_menor = a;
                                                menorValor = v[a].cod_cliente;
                                            }
                                        }
                                    }
                                printf("Menor valor=%s",v[posicao_menor].nome);
                               // posicao_menor = posicao_menor_valor(v, M); 
                                salva_cliente(&v[posicao_menor],particao_saida);  
                                // existe um erro de gravacao aqui    
                                chave_recem_gravada=v[posicao_menor];  
                                fread(&v[posicao_menor], sizeof(TCliente),1, arq);


                        //caso a chave do ultimo seja menor do que a chave recem gravada
                        if(chave_recem_gravada.cod_cliente < v[posicao_menor].cod_cliente){
                            salva_cliente(&v[posicao_menor],reservatorio);
                            fread(&v[posicao_menor], sizeof(TCliente), 1, arq);
                        }
                        // testa se o reservatorio esta cheio
                        if(esta_cheio(reservatorio,M)){


                            // fecha o arquivo de particao atual
                            fclose(particao_saida);
                            // limpa o array em memoria
                            free(v);
                            int cont=0;
                            //copia os registros do reservatorio para o array em memoria
                            while(!feof(reservatorio)){
                                fread(&v[cont], sizeof(TCliente), 1, reservatorio);
                                fread(&v[posicao_menor], sizeof(TCliente), 1, reservatorio);
                                cont++;
                            }
                            fclose(reservatorio);
                            particao_saida= fopen(nome_arquivos_saida->nome, "wb");
                            nome_arquivos_saida = nome_arquivos_saida->prox;

                        }
                }
                while(!feof(arq));

                       
    }

    
}



#endif