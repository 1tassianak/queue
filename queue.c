#include "queue_pub.h"
#include "queue_pri.h"
#include <string.h>  // memcpy

// "Construtor": aloca memória e inicializa as variáveis
int cQueue(ppQueue pf, int size, int sizedata){

    //aloca memória para a estrutura
    *pf = malloc(sizeof(Queue));
    //verifica se o ponteiro *pf é null
    if(*pf == NULL) return FAIL;

    //aloca memória para os dados
    (*pf)->dados = malloc(size * sizedata);
    if((*pf)->dados == NULL){
        free(*pf); //falhou, libera o ponteiro da estrutura
        return FAIL;
    }

    //inicializa as variáveis da estrutura
    (*pf)->inicio = 0;
    (*pf)->fim = 0;
    (*pf)->qtd = 0;
    (*pf)->size = size;
    (*pf)->size_data = sizedata;

    return SUCCESS;
}

// "Destrutor": libera memória da estrutura
int dQueue(ppQueue pf){

    //verificar se o ponteiro da fila e o conteúdo que o ponteiro pf da fila aponta não são null
    if(pf == NULL || *pf == NULL) return FAIL;

    //usar cleanQueue para prevenir de usar dQueue sem dar o clean, não é correto, pois ela recebe um ponteiro f, e aqui pede ponteiro do ponteiro, e pode liberar coisas q não queremos
    // Verifica se a estrutura apontada por *pf é válida
    if (*pf != NULL) {
        //garante que os dados internos sejam liberados
        if ((*pf)->dados != NULL) {
            free((*pf)->dados);
            (*pf)->dados = NULL;
        }

        //libera o ponteiro do ponteiro da estrutura
        free(*pf);

        //atribui NULL ao ponteiro da estrutura
        *pf = NULL;
    }

    return SUCCESS;

}

// **** "Operações de manipulação" ****
// Enfileirar elementos
int queue(pQueue f, void *element){

    //verificar se a fila e o elemento não são null
    if(f == NULL || element == NULL) return FAIL;

    //verificar se a fila está cheia
    if(f->qtd == f->size) return FAIL;

    //calcular o índice real de inserção circular que é o fim, para calcular o espaço do destino na memória
    int indice = (f->inicio + f->qtd) % f->size;
    //% p->size: Quando o inicio + qtd ultrapassar o fim do array, volta para o começo.

    //calcula o espaço do destino na memória
    void *destino = (char *)f->dados + (indice * f->size_data);

    //copia o dado da main para a posição calculada na fila
    memcpy(destino, element, f->size_data);

    //incrementa a quantidade de elementos atuais na fila
    f->qtd++;

    return SUCCESS;

}

// Desenfilera um elemento
int unqueue(pQueue f, void *element){

    //verificar se a fila e o elemento não são null
    if(f == NULL || element == NULL) return FAIL;

    //verificar se a fila está vazia
    if(f->qtd == 0) return FAIL;

    //o início é o índice real para remoção, então não precisa calcular onde está
    //basta calcular o espaço da memória de onde está o elemento que será removido
    void *remove = (char *)f->dados + (f->inicio * f->size_data);

    //copia o elemento removido para a variável element da main
    memcpy (element, remove, f->size_data);

    //atualiza o índice do início, pois o elemento que estava no início foi removido
    f->inicio = (f->inicio + 1) % f->size;

    //decrementa a quantidade de elementos atuais na fila
    f->qtd--;

    return SUCCESS;
}

// Remove todos os dados da fila mantendo o descritor alocado.
int cleanQueue(pQueue f){

    //verifica se a fila está vazia
    if(f == NULL) return FAIL;

    //libera os dados sem liberar o ponteiro f (pois é solcitado que mantenha o descritor alocado)
    free(f->dados);

    //atribui null aos dados e define os campos em 0
    f->dados = NULL;
    f->inicio = 0;
    f->fim = 0;
    f->qtd = 0;

    return SUCCESS;
}

// **** "Operações de acesso" ****
// Retorna o máximo da fila
int sizeQueue(pQueue f){

    //verifica se a fila está vazia
    if(f == NULL) return FAIL;
    
    //retorna a capacidade máxima
    return f->size;

}