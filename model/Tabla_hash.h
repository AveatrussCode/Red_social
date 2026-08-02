#ifndef TABLA_HASH_H
#define TABLA_HASH_H


#include "Lista_enlazada.h"
#define SIZE 100000

template <typename V>
class Hash{

    public:
        Lista_enlazada<V>* id_list;
        long long size;
        long long cantidad; 

        Hash(long long capacidad = SIZE);
        ~Hash();
        long long hash_funcion(long long);

        void insertar(long long id, V valor);
        bool buscar(long long id, V& resultado);
        bool eliminar(long long id);
        bool contiene(long long id);

        long long tamano() const;

};

template <typename V>
Hash<V>::Hash(long long capacidad){
    size = capacidad;
    cantidad = 0;
    id_list = new Lista_enlazada<V>[size];
}

template <typename V>
Hash<V>::~Hash(){
    delete[] id_list;
}

template <typename V>
long long Hash<V>::hash_funcion(long long id){
    return id % size;
}

template <typename V>
void Hash<V>::insertar(long long id, V valor){
    long long posicion = hash_funcion(id);
    bool nuevo = id_list[posicion].insert(id, valor);
    if(nuevo){
        cantidad++;
    }
}

template <typename V>
bool Hash<V>::buscar(long long id, V& resultado){
    long long posicion = hash_funcion(id);
    return id_list[posicion].buscar(id, resultado);
}

template <typename V>
bool Hash<V>::eliminar(long long id){
    long long posicion = hash_funcion(id);
    bool ok = id_list[posicion].eliminar(id);
    if(ok){
        cantidad--;
    }
    return ok;
}

template <typename V>
bool Hash<V>::contiene(long long id){
    long long posicion = hash_funcion(id);
    return id_list[posicion].existe(id);
}

template <typename V>
long long Hash<V>::tamano() const {
     return cantidad; }



#endif
