#ifndef LISTA_ENLAZADA_H
#define LISTA_ENLAZADA_H



template <class V>
class Nodo{

public:
    long long id;
    V valor;
    Nodo* next;
    Nodo(long long _id, V _valor){
        id = _id;
        valor = _valor;
        next = nullptr;
    }
};

template <class V>
class Lista_enlazada{
    public:
        Nodo<V> *heap;
        Lista_enlazada();
        ~Lista_enlazada();

    
        bool insert(long long id, V valor);

        bool eliminar(long long id);
        bool buscar(long long id, V& resultado);
        bool existe(long long id);
        bool find(Nodo<V>**&p, long long id);
};


template <class V>
Lista_enlazada<V>::Lista_enlazada(){
    heap = nullptr;
}

template <class V>
Lista_enlazada<V>::~Lista_enlazada(){
    Nodo<V>* actual = heap;
    while(actual){
        Nodo<V>* siguiente = actual->next;
        delete actual;
        actual = siguiente;
    }
}

template <class V>
bool Lista_enlazada<V>::insert(long long id, V valor){
   
    Nodo<V>* actual = heap;
    while(actual){
        if (actual->id == id){
            actual->valor = valor;
            return false; 
        }
        actual = actual->next;
    }
    Nodo<V> * nuevo = new Nodo<V>(id, valor);
    nuevo->next = heap;
    heap = nuevo;
    return true; 
}

template <class V>
bool Lista_enlazada<V>::eliminar(long long id){
    Nodo<V> **p;
    if (!find(p, id)){
        return false;
    }
    Nodo<V> *tmp = *p;
    *p = (*p)->next;
    delete tmp;
    return true;
}

template <class V>
bool Lista_enlazada<V>::buscar(long long id, V& resultado){
    Nodo<V>* actual = heap;
    while(actual){
        if (actual->id == id){
            resultado = actual->valor;
            return true;
        }
        actual = actual->next;
    }
    return false;
}

template <class V>
bool Lista_enlazada<V>::existe(long long id){
    Nodo<V>* actual = heap;
    while(actual){
        if (actual->id == id) return true;
        actual = actual->next;
    }
    return false;
}

template <class V>
bool Lista_enlazada<V>::find(Nodo<V>**&p, long long id){
    p = &heap;
    while(*p && (*p)->id != id){
        p = &((*p)->next);
    }
    return *p != nullptr;
}

#endif
