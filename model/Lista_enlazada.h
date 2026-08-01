#ifndef LISTA_ENLAZADA_H
#define LISTA_ENLAZADA_H


class Nodo{

public:
    long long data;
    Nodo* next;
    Nodo(long long _data){
        data = _data;
        next = nullptr;
    }
};
class Lista_enlazada{
    public:
        Nodo *heap;
        Lista_enlazada();
        void insert(long long data);
        bool eliminar(long long data);
        bool find(Nodo**&p, long long);
};



Lista_enlazada::Lista_enlazada(){
    heap = nullptr;
}
void Lista_enlazada::insert(long long data){
    Nodo * nuevo = new Nodo(data);
    nuevo->next = heap;
    heap = nuevo;
}

bool Lista_enlazada::eliminar(long long data){
    Nodo **p;
    if (!find(p,data)){
        return false;
    }
    Nodo *tmp = *p;
    *p = (*p)->next;
    delete tmp;
    return true;


}
bool Lista_enlazada::find(Nodo**&p, long long data){
    p = &heap;
    while(*p && (*p)->data != data){
        p = &((*p)->next);
    }
    return *p != nullptr;

}

#endif