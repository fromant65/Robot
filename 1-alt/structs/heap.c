#include "heap.h"
#include <stdlib.h>

Heap* new_heap(int size){
    Heap* h=malloc(sizeof(Heap));
    h->buffer=malloc(sizeof(Nodo*)*size);
    h->buffer[0]=NULL;
    h->size=size;
    h->length=0;
    return h;
}

void free_heap(Heap* h){
    free(h->buffer);
    free(h);
}


Nodo* heap_dequeue(Heap* h){
    if(h->length==0) return NULL;
    Nodo* first = h->buffer[1];
    h->buffer[1]=h->buffer[h->length];
    h->buffer[h->length--]=NULL;
    heap_sink(h,1);
    return first;
}

void heap_enqueue(Heap* h, Nodo* elem){
    h->length++;
    h->buffer[h->length]=elem;
    heap_float(h, h->length);
}

void swap(Heap* h, int i1, int i2){
    Nodo *aux = h->buffer[i1];
    h->buffer[i1]=h->buffer[i2];
    h->buffer[i2]=aux;
}

void heap_float(Heap* h, int index){
    if(index <= 1 || index > h->length) return;
    if(h->buffer[index]->distancia<h->buffer[index/2]->distancia){
        swap(h,index, index/2);
        heap_float(h,index/2);
    }
}

void heap_sink(Heap* h, int index){
    if(index<1||index*2>h->length) return;
    int smallerChild = index * 2;
    if (index * 2 + 1 <= h->length && h->buffer[index * 2 + 1]->distancia < h->buffer[index * 2]->distancia) {
        smallerChild = index * 2 + 1;
    }
    if (h->buffer[index]->distancia > h->buffer[smallerChild]->distancia) {
        swap(h, index, smallerChild);
        heap_sink(h, smallerChild);
    }
}