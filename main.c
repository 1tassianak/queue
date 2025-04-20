#include "main.h"

#define MAX_STRING 100

int main(int argc, char *argv[]) {
    
    //Inicializa a estrutura
    pQueue fila = NULL;

    //inicializa as variáveis
    int tipo, qtd;
    char buffer[MAX_STRING];
    int val_int;
    float val_float;
    int sizedata = 0;
    int result = 0;

    //testando as funções da fila

    //levando em consideração que o usuário indica qtd de elementos e os elementos
    printf("Digite a quantidade de dados a serem inseridos na fila:\n");
    //ao invés de usar fscanf e ter que limpa o buffer com while (getchar() != '\n'); usa fgets para ler e sscanf para pegar o dado e armazenar na variável
    fgets(buffer, MAX_STRING, stdin); //armazena o que o usuário digitou no buffer
    //verifica se a leitura do que o usuário digitou falhou
    if (sscanf(buffer, "%d", &qtd) != 1) {
        printf("Erro ao ler quantidade.\n");
        return 1;
    }

    //solicitar ao usuário o tipo de elemento a ser enfileirado
    printf("Digite o tipo de dado (0=int, 1=float, 2=string):\n");
    fgets(buffer, MAX_STRING, stdin);
    //verifica se a leitura do que o usuário digitou falhou
    if (sscanf(buffer, "%d", &tipo) != 1) {
        printf("Erro ao ler tipo de dado.\n");
        return 1;
    }

    //verificando o tamanho por tipo de dado
    if(tipo == 0){
        sizedata = sizeof(int);
    }else if(tipo == 1){
        sizedata = sizeof(float);
    }else{
        sizedata = sizeof(char) * MAX_STRING;
    }

    // "Construtor": aloca memória e inicializa as variáveis
    result = cQueue(&fila, qtd, sizedata);
    //verifica se falhar
    if(result != SUCCESS){
        printf("Erro ao criar fila\n");
        return 1;
    }

    // Enfilerar elementos
    //i < qtd, pois se for i <= qtd, tentará enfileirar um a mais
    for(int i = 0; i < qtd; i++){
        printf("Digite o valor:\n");
        //lê uma linha do usuário e armazena em buffer (suporta espaços, diferente do scanf)
        fgets(buffer, MAX_STRING, stdin);
        
        //função rápida para substituir o \n, que fgets coloca, por \0, precisa de string.h
        buffer[strcspn(buffer, "\n")] = '\0';

        //verifica o tipo de dado e enfileira
        if(tipo == 0){
            //tenta extrair um int do que o usuário digitou
            if(sscanf(buffer, "%d", &val_int) == 1){
                //se for int, enfileira
                queue(fila, &val_int);
            }else{
                printf("Valor inválido para tipo int. Ignorado.\n");
            }
        }else if(tipo == 1){
            //tenta extrair um float do que o usuário digitou
            if(sscanf(buffer, "%f", &val_float) == 1){
                //se for float, enfileira
                queue(fila, &val_float);
            }else{
                printf("Valor inválido para tipo float. Ignorado.\n");
            }
        }else{
            queue(fila, buffer);
        }

    }

    // Retorna o máximo da fila antes de desenfileirar
    int tamanho_fila = sizeQueue(fila);
    printf("Tamanho máximo da fila: %d\n", tamanho_fila);

    // Desenfilera um elemento
    printf("Desenfileirando...\n");

    //enquanto tiver o que desenfileirar
    while (1){
        //verifica o tipo e desenfileira
        if(tipo == 0){
            int valor;
            if(unqueue(fila, &valor) != SUCCESS) break;
            printf("unqueue: %d\n", valor);
        }else if(tipo == 1){
            float valor;
            if(unqueue(fila, &valor) != SUCCESS) break;
            printf("unqueue: %.2f\n", valor);
        }else{
            char valor[MAX_STRING];
            if (unqueue(fila, valor) != SUCCESS) break;
            printf("unqueue: %s\n", valor);
        }
    }
    
    // Remove todos os dados da fila mantendo o descritor alocado.
    //fila, pois espera o p de fila (pQueue)
    cleanQueue(fila);

    // "Destrutor": libera memória da estrutura
    //&fila pois espera o pp de fila (ppQueue)
    dQueue(&fila);

  
    return 0;
}