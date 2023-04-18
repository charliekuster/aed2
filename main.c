#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int Particao(int array[], int esq, int dir, int recur[], int flag, int min[]){
    int pivo = array[dir];
    int i = esq - 1;
    for (int j = esq; j < dir; j++) {
        if (array[j] < pivo) {
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    int temp = array[i + 1];
    array[i + 1] = array[dir];
    array[dir] = temp;

    return i + 1;
}

int Mediana(int array[], int esq, int dir){
    int meio = (esq + dir)/2, aux;
    if(array[esq] > array[meio]){
        aux = array[esq];
        array[esq] = array[meio];
        array[meio] = aux;
    }
    if(array[meio] > array[dir]){
        aux = array[dir];
        array[dir] = array[meio];
        array[meio] = aux;        
    }
    if(array[esq] > array[meio]){
        aux = array[esq];
        array[esq] = array[meio];
        array[meio] = aux;
    }
    return meio;    
}

int ParticaoMediana(int array[], int esq, int dir, int recur[], int flag, int min[]){
    int meio = Mediana(array, esq, dir); // indice do meio
    //printf("  mediana = %d", meio);
    int i = esq - 1, aux, pivo;
    aux = array[meio];
    array[meio] = array[dir - 1];
    array[dir - 1] = aux;
    pivo = dir - 1;
    for (int j = esq; j < dir-1; j++) {
        if (array[j] < array[pivo]) {
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    int temp = array[i + 1];
    array[i + 1] = array[dir - 1];
    array[dir - 1] = temp;
   
    
    return i + 1;
}

int QuickSortMediana(int array[], int esq, int dir, int recur[], int *flag, int min[]){
    int minesq, mindir;
    if(esq >= dir){
        (*flag) += 1;
        return 0;
    }
    int pivo = ParticaoMediana(array, esq, dir, recur, *flag, min);
    minesq = QuickSortMediana(array, esq, pivo - 1, recur, flag, min);
    mindir = QuickSortMediana(array, pivo + 1, dir, recur, flag, min);
    (*recur)++;
    if(minesq > mindir){
        return mindir +1;
    }
    else{
        return minesq +1;
    }
}


int QuickSort(int array[], int esq, int dir, int recur[], int *flag, int min[]){
    int minesq, mindir;
    if(esq >= dir){
        (*flag) += 1;
        return 0;
    }
    int pivo = Particao(array, esq, dir, recur, *flag, min);
    minesq = QuickSort(array, esq, pivo - 1, recur, flag, min);
    mindir = QuickSort(array, pivo + 1, dir, recur, flag, min);
    (*recur)++;
    if(minesq > mindir){
        return mindir +1;
    }
    else{
        return minesq +1;
    }
}

int main (void){
    int *array, *array2, tam, i, *recur, *recur2, *min, flag = 0;
    scanf("%d", &tam);
    array = (int*)malloc(tam * sizeof(int));
    array2 = (int*)malloc(tam * sizeof(int));
    recur = (int*)malloc(sizeof(int));
    recur2 = (int*)malloc(sizeof(int));
    min = (int*)malloc(sizeof(int));
    for(i=0; i<tam; i++){
        scanf("%d", &array[i]);
        array2[i] = array[i];
    }
    *min = QuickSort(array, 0, tam - 1, recur, &flag, min);
    printf("%d\n", *recur - *min);
    // printf("min = %d\n", *min); 
    // printf("reur = %d\n", *recur);  
    *recur2 = 0;
    flag = 0;
    *min = 0; 
    *min = QuickSortMediana(array2, 0, tam - 1, recur2, &flag, min);
    printf("%d\n", *recur2 - *min);  
    printf("flag: %d", flag);
    return 0;
}