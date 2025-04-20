#ifndef QUEUE_PRI_H
#define QUEUE_PRI_H

//Precisa ser Queue porque no pub está declarado com este nome
typedef struct Queue{
    void *dados; //ponteiro para o array de dados
    int inicio; //índice do início da fila, onde desenfileira
    int fim; //índice do fim da fila, onde enfileira
    int qtd; //quantidade atual de elementos na fila
    int size; //tamanho máximo
    int size_data; //tamanho do dado
}Queue;


#endif /*QUEUE_PRI_H*/