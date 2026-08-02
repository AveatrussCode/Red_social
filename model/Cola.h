#ifndef COLA_H
#define COLA_H

// Cola generica (FIFO) implementada con lista enlazada propia.
// Se usa para el recorrido BFS del grafo de amistades.
// No utiliza ninguna estructura de la STL.

template <typename T>
class NodoCola {
public:
    T valor;
    NodoCola* siguiente;

    NodoCola(T _valor) {
        valor = _valor;
        siguiente = nullptr;
    }
};

template <typename T>
class Cola {
public:
    NodoCola<T>* frente;
    NodoCola<T>* final;
    long long cantidad;

    Cola();
    ~Cola();

    void encolar(T valor);
    bool desencolar(T& resultado);
    bool esta_vacia() const;
};

template <typename T>
Cola<T>::Cola(){
    frente = nullptr;
    final = nullptr;
    cantidad = 0;
}

template <typename T>
Cola<T>::~Cola(){
    T temporal;
    while(desencolar(temporal)){}
}

template <typename T>
void Cola<T>::encolar(T valor){
    NodoCola<T>* nuevo = new NodoCola<T>(valor);

    if(final == nullptr){
        frente = nuevo;
        final = nuevo;
    } else {
        final->siguiente = nuevo;
        final = nuevo;
    }
    cantidad++;
}

template <typename T>
bool Cola<T>::desencolar(T& resultado){
    if(frente == nullptr){
        return false;
    }

    NodoCola<T>* temporal = frente;
    resultado = temporal->valor;
    frente = frente->siguiente;

    if(frente == nullptr){
        final = nullptr;
    }

    delete temporal;
    cantidad--;
    return true;
}

template <typename T>
bool Cola<T>::esta_vacia() const {
    return frente == nullptr;
}

#endif
