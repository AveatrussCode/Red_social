#ifndef HEAP_TREE_H
#define HEAP_TREE_H

// Max-heap generico implementado sobre un arreglo dinamico.
// La funcion de prioridad debe retornar true si el primer elemento
// debe aparecer antes que el segundo.
template <typename T>
class HeapTree {
private:
    T* elementos;
    long long capacidad;
    long long cantidad;
    bool (*tiene_mayor_prioridad)(T, T);

    void intercambiar(long long a, long long b){
        T temporal = elementos[a];
        elementos[a] = elementos[b];
        elementos[b] = temporal;
    }

public:
    HeapTree(long long capacidad_inicial, bool (*comparador)(T, T)){
        capacidad = (capacidad_inicial > 0) ? capacidad_inicial : 1;
        cantidad = 0;
        elementos = new T[capacidad];
        tiene_mayor_prioridad = comparador;
    }

    ~HeapTree(){
        delete[] elementos;
    }

    bool esta_vacio() const {
        return cantidad == 0;
    }

    long long tamano() const {
        return cantidad;
    }

    void insertar(T valor){
        if(cantidad == capacidad){
            capacidad *= 2;
            T* nuevo = new T[capacidad];
            for(long long i = 0; i < cantidad; i++){
                nuevo[i] = elementos[i];
            }
            delete[] elementos;
            elementos = nuevo;
        }

        long long actual = cantidad;
        elementos[cantidad++] = valor;

        while(actual > 0){
            long long padre = (actual - 1) / 2;
            if(!tiene_mayor_prioridad(elementos[actual], elementos[padre])){
                break;
            }
            intercambiar(actual, padre);
            actual = padre;
        }
    }

    bool extraer_maximo(T& resultado){
        if(esta_vacio()){
            return false;
        }

        resultado = elementos[0];
        cantidad--;
        if(cantidad == 0){
            return true;
        }

        elementos[0] = elementos[cantidad];
        long long actual = 0;

        while(true){
            long long izquierdo = actual * 2 + 1;
            long long derecho = actual * 2 + 2;
            long long mayor = actual;

            if(izquierdo < cantidad &&
               tiene_mayor_prioridad(elementos[izquierdo], elementos[mayor])){
                mayor = izquierdo;
            }
            if(derecho < cantidad &&
               tiene_mayor_prioridad(elementos[derecho], elementos[mayor])){
                mayor = derecho;
            }
            if(mayor == actual){
                break;
            }

            intercambiar(actual, mayor);
            actual = mayor;
        }
        return true;
    }

    HeapTree(const HeapTree&) = delete;
    HeapTree& operator=(const HeapTree&) = delete;
};

#endif
