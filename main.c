#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Arvore{
    char cor;
    int valor;
    struct Arvore *esq;
    struct Arvore *dir; 
}Arvore;

Arvore *InstArv(int v){
    Arvore *novaArv = (Arvore*)malloc(sizeof(Arvore));
    novaArv->valor = v;
    novaArv->cor = 'r';
    novaArv->dir = NULL;
    novaArv->esq = NULL;
    return novaArv;
}

int AlturaAvr(Arvore *arv){
    if(arv == NULL){
        return 0;
    }
    int noD, noE;
    noE = AlturaAvr(arv->esq) + 1;
    noD = AlturaAvr(arv->dir) + 1;
    if(noD > noE){
        return noD;
    }
    else{
        return noE;
    }   
}

void RecolorirNo(Arvore *arv){
    if(arv->cor == 'r'){
        arv->cor = 'n';
    }
    else{
        arv->cor = 'r';
    }
    return;
}

Arvore *RotacaoEsq(Arvore *arv){ //rr
    Arvore *aux = (Arvore*)malloc(sizeof(Arvore));
    aux = arv->dir;
    arv->dir = aux->esq;
    aux->esq = arv;
    return aux;
}

Arvore *RotacaoDir(Arvore *arv){ //ll
    Arvore *aux = (Arvore*)malloc(sizeof(Arvore));
    aux = arv->esq;
    arv->esq = aux->dir;
    aux->dir = arv;
    return aux;
}

Arvore *RotacaoEsqDir(Arvore *arv){ //lr
    Arvore *aux; 
    arv->esq = RotacaoEsq(arv->esq); 
    aux = RotacaoDir(arv); 
    return aux;
}

Arvore *RotacaoDirEsq(Arvore *arv){ // rl
    Arvore *aux; 
    arv->dir = RotacaoEsq(arv->dir); 
    aux = RotacaoEsq(arv); 
    return aux;
}

void InsArv(Arvore **parv, Arvore *novaArv, Arvore *raiz, Arvore **pvo, Arvore **ppai){
    Arvore *pai = NULL, *vo = NULL , *tio = NULL;
    if(pvo != NULL){
        vo = *pvo;
    }
    if(ppai != NULL){
        pai = *ppai;
    }
    Arvore *arv = *parv;
    Arvore **pesq = &arv->esq;
    Arvore **pdir = &arv->dir;
    if(arv->valor > novaArv->valor){
        if(arv->esq == NULL){
            arv->esq = novaArv;
        }
        else{
            InsArv(pesq, novaArv, raiz, ppai, parv);
        }
    }
    if(arv->valor < novaArv->valor){
        if(arv->dir == NULL){
            arv->dir = novaArv;
        }
        else{
            
            InsArv(pdir, novaArv, raiz, ppai, parv);
        }
    }
    pvo = ppai;
    ppai = parv;
    if(pvo != NULL){
        vo = *pvo;
    }
    if(ppai != NULL){
        pai = *ppai;
    }
    if(vo != NULL){
        if(vo->esq != pai){
            tio=vo->esq;
        }    
        else{
            tio=vo->dir;
        } 
    }       
    // if(pai != NULL && vo != NULL){
    //    printf("pai %c", pai->cor); 
    //    printf("vo %c", vo->cor);
    // }
    if(vo != NULL){
        if(tio == NULL || tio->cor == 'n'){
            if(vo->dir == pai && pai->dir){
                *pvo = RotacaoEsq(vo); //rr
            }
            else if(vo->esq == pai && pai->esq){
                *pvo = RotacaoDir(vo); //ll
            }
            else if(vo->dir == pai && pai->esq){
                *pvo = RotacaoDirEsq(vo); //rl
            }
            else if(vo->esq == pai && pai->dir){
                *pvo = RotacaoEsqDir(vo); //lr
            }
        }
    }
    // if(tio != NULL && tio->cor == 'r'){
    //         RecolorirNo(tio); 
    //         RecolorirNo(pai);
    //         RecolorirNo(vo);
    // }
    // if(raiz->cor == 'r'){
    //     raiz->cor = 'n';
    // } 

}


Arvore *BuscArv(Arvore *arv, int busca){
    Arvore *aux;
    aux = NULL;
    if(arv->valor == busca){
        return arv;
    }
    else if(arv->valor > busca){
        aux = BuscArv(arv->esq, busca);
    }
    else if(arv->valor < busca){
        aux = BuscArv(arv->dir, busca);
    }
    return aux;
}

void PrintArv(Arvore *arv){
    if(arv == NULL){
        return;
    }
    else{
        PrintArv(arv->esq); 
        printf("%c", arv->cor);
        printf("%d", arv->valor);
        printf(" ");
        PrintArv(arv->dir);
    }    
}

int main (void){
    Arvore *arv;
    int valor, altura;
    arv = NULL;
    scanf("%d", &valor);
    while(valor > 0){
        if(arv == NULL){
            arv = InstArv(valor);
        }
        else{
            Arvore *novaArv;
            scanf("%d", &valor);
            if(valor < 0){
                break;
            }
            else{
                novaArv = InstArv(valor); 
                InsArv(&arv, novaArv, arv, NULL, NULL);
            }
        }
    }
    PrintArv(arv);
    printf("\nraiz: %d", arv->valor);
    altura = AlturaAvr(arv);
    //printf("%d", altura - 1);
}