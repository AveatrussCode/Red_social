#ifndef TABLA_HASH_H
#define TABLA_HASH_H


#include "Lista_enlazada.h"
#define SIZE 100000

class Hash{

    public:
        Lista_enlazada* id_list;
        long long size;

        Hash();
        ~Hash();
        long long hash_funcion(long long);
        void insertar(long long);

};

Hash::Hash(){
    size = SIZE;
    id_list = new Lista_enlazada[size];
}

Lista_enlazada::~Lista_enlazada(){
    Nodo* actual = heap;
    while(actual){
        Nodo* siguiente = actual->next;
        delete actual;
        actual = siguiente;
    }
}

long long Hash::hash_funcion(long long id){
    return id % size;
}

void Hash::insertar(long long data){
    long long posicion = hash_funcion(data);
    id_list[posicion].insert(data);

}


#endif