#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct No {
    int valor;
    struct No *prox;
} No;

typedef struct List{
    No *comeco;
} List;

List *InstList(void){
    List *list;
    list = (List*)malloc(sizeof(List));
    list->comeco = NULL;
    return list;
}

No *InstNo(int num){
    No *novoNo;
    novoNo = (No*)malloc(sizeof(No));
    novoNo->valor = num;
    return novoNo;
}

void PrintNo(No No){
    printf("%d", No.valor);
}

void PrintList(List list){
    No *noAux = list.comeco;
    while(noAux != NULL){
        PrintNo(*noAux);
        noAux = noAux->prox;
    }

}

void InsList(List *list, No *no){
    No *noAux = list->comeco;
    while(noAux->prox != NULL){
        noAux = noAux->prox;
    }
    noAux->prox = no;    
}

void DividirList(No *no, No **noDir, No **noEsq){
    No *devagar, *rapido;
    devagar = no;
    rapido = no->prox;
    while (rapido != NULL){
        rapido = rapido->prox;
        if(rapido != NULL){
            devagar = devagar->prox;
            rapido = rapido->prox;
        }
    }
    *noDir = devagar->prox;
    *noEsq = no;
    devagar->prox = NULL;
    return;
}

No *Mesclagem(No *noEsq, No *noDir);

No *MergeSort(No *no){
    No *noDir, *noEsq;
    noDir = NULL;
    noEsq = NULL;
    if(no->prox == NULL){
        return no;
    }
    DividirList(no, &noDir, &noEsq);
    noEsq = MergeSort(noEsq);
    noDir = MergeSort(noDir);
    // Mesclar
    return Mesclagem(noEsq, noDir);
}

No *Mesclagem(No *noEsq, No *noDir){
    No *comeco, *fim;
    comeco = NULL;
    fim = comeco;
    while(noEsq != NULL && noDir != NULL){
        No *novoNo;
        if(noEsq->valor < noDir->valor){
            novoNo = noEsq;
            noEsq = noEsq->prox;
        }
        else if(noDir->valor < noEsq->valor){
            novoNo = noDir;
            noDir = noDir->prox;
        } 
        if(fim == NULL){
            fim = novoNo;
            comeco = novoNo;
        }
        else{
            fim->prox = novoNo;
        }
    }
    if(noEsq == NULL){
        fim->prox = noDir;
    }
    else{
        fim->prox = noEsq;
    }
    return comeco;
}

int main(void){
    int tam, i, num; 
    List *list;
    No *no;
    scanf("%d", &tam);
    list = InstList();
    for(i=0; i<tam; i++){
        scanf("%d", &num);
        no = InstNo(num);
        if(list->comeco == NULL){
            list->comeco = no;
        }
        else{
           InsList(list, no); 
        }
    }
    list->comeco = MergeSort(list->comeco);
    PrintList(*list);
    return 0;
}