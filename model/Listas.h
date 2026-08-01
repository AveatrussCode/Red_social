#ifndef LISTAS_H 
#define LISTAS_H


template <typename T>
class Lista {
    public:
        long long current;
        long long size;
        T *lista;
    
        Lista();
        ~Lista();
        
        void insert(T);
        void eliminar(T);
        int buscar(T);
};


template <typename T>
Lista<T>::Lista(){
    size = 2;
    current = 0;
    lista = new T[size];
}
template <typename T>
Lista<T>::~Lista() {
    delete[] lista;
}
template <typename T>
void Lista<T>::insert(T data){
    if (current == size){
        size = size *2;
        int* nuevo = new T[size];
        for (int i =0; i< current; i ++){
            nuevo[i] = lista[i];
        }
        delete[] lista;
        lista = nuevo;
    }
    lista[current] = data;
    current ++;
}
template <typename T>
int Lista<T>::buscar(T data){
    for (int i =0; i< current; i++){
        if (lista[i] == data){
            return i;
        }
    }
    return -1;
}
template <typename T>
void Lista<T>::eliminar(T data){
    int a_eliminar = buscar(data);
    if (a_eliminar>-1){
        for (int i =a_eliminar; i<current -1 ; i++){
            lista[i] = lista[i+1];
        }
        current --;
    }
}

#endif