#ifndef LISTAS_H 
#define LISTAS_H

class Lista {
    public:
        int current;
        int size;
        int *lista;
    
        Lista();
        ~Lista();
        
        void insert(int);
        void eliminar(int);
        int buscar(int);
};



Lista::Lista(){
    size = 2;
    current = 0;
    lista = new int[size];
}
Lista::~Lista() {
    delete[] lista;
}

void Lista::insert(int data){
    if (current == size){
        size = size *2;
        int* nuevo = new int[size];
        for (int i =0; i< current; i ++){
            nuevo[i] = lista[i];
        }
        delete[] lista;
        lista = nuevo;
    }
    lista[current] = data;
    current ++;
}
int Lista::buscar(int data){
    for (int i =0; i< current; i++){
        if (lista[i] == data){
            return i;
        }
    }
    return -1;
}
void Lista::eliminar(int data){
    int a_eliminar = buscar(data);
    if (a_eliminar>-1){
        for (int i =a_eliminar; i<current -1 ; i++){
            lista[i] = lista[i+1];
        }
        current --;
    }
}


#endif