#include "../model/GrafoAmistad.h"
#include "../model/Cola.h"
#include "../model/HeapTree.h"
#include "../model/Tabla_hash.h"

namespace {
bool mayor_afinidad(SugerenciaAmistad primero, SugerenciaAmistad segundo){
    if(primero.amigos_en_comun != segundo.amigos_en_comun){
        return primero.amigos_en_comun > segundo.amigos_en_comun;
    }
    return primero.id_usuario < segundo.id_usuario;
}
}

GrafoAmistad::GrafoAmistad(Sistema& _sistema) : sistema(_sistema) {}

long long GrafoAmistad::capacidad_ids() const {
    // Los ids se generan de forma secuencial desde 1, asi que este
    // valor siempre es mayor que cualquier id de usuario existente.
    return sistema.siguiente_usuario_id;
}

bool GrafoAmistad::ruta_amistad(
    long long origen,
    long long destino,
    Lista<long long>& camino_salida,
    long long& distancia_salida
){
    distancia_salida = -1;

    if(sistema.buscar_usuario(origen) == nullptr ||
       sistema.buscar_usuario(destino) == nullptr){
        return false;
    }

    if(origen == destino){
        camino_salida.insert(origen);
        distancia_salida = 0;
        return true;
    }

    long long capacidad = capacidad_ids();
    bool* visitado = new bool[capacidad];
    long long* padre = new long long[capacidad];

    for(long long i = 0; i < capacidad; i++){
        visitado[i] = false;
        padre[i] = -1;
    }

    Cola<long long> pendientes;
    visitado[origen] = true;
    pendientes.encolar(origen);

    bool encontrado = false;

    while(!pendientes.esta_vacia() && !encontrado){
        long long actual;
        pendientes.desencolar(actual);

        Usuario* usuario_actual = sistema.buscar_usuario(actual);
        if(usuario_actual == nullptr){
            continue;
        }

        for(long long i = 0; i < usuario_actual->amigos.current; i++){
            long long vecino = usuario_actual->amigos.lista[i];

            if(vecino < 0 || vecino >= capacidad || visitado[vecino]){
                continue;
            }

            visitado[vecino] = true;
            padre[vecino] = actual;

            if(vecino == destino){
                encontrado = true;
                break;
            }

            pendientes.encolar(vecino);
        }
    }

    if(encontrado){
        Lista<long long> invertido;
        long long paso = destino;

        while(paso != -1){
            invertido.insert(paso);
            paso = padre[paso];
        }

        for(long long i = invertido.current - 1; i >= 0; i--){
            camino_salida.insert(invertido.lista[i]);
        }

        distancia_salida = camino_salida.current - 1;
    }

    delete[] visitado;
    delete[] padre;

    return encontrado;
}

void GrafoAmistad::amigos_en_comun(
    long long id1,
    long long id2,
    Lista<long long>& salida
){
    Usuario* u1 = sistema.buscar_usuario(id1);
    Usuario* u2 = sistema.buscar_usuario(id2);

    if(u1 == nullptr || u2 == nullptr){
        return;
    }

    for(long long i = 0; i < u1->amigos.current; i++){
        long long candidato = u1->amigos.lista[i];
        if(u2->amigos.buscar(candidato) != -1){
            salida.insert(candidato);
        }
    }
}

void GrafoAmistad::sugerencias_amistad(
    long long id_usuario,
    long long cantidad,
    Lista<SugerenciaAmistad>& salida
){
    Usuario* usuario = sistema.buscar_usuario(id_usuario);
    if(usuario == nullptr || cantidad <= 0){
        return;
    }

    // Tabla de conteo: id_candidato -> cantidad de amigos en comun.
    Hash<long long> contador(4096);
    Lista<long long> candidatos;

    for(long long i = 0; i < usuario->amigos.current; i++){
        long long id_amigo = usuario->amigos.lista[i];
        Usuario* amigo = sistema.buscar_usuario(id_amigo);
        if(amigo == nullptr){
            continue;
        }

        for(long long j = 0; j < amigo->amigos.current; j++){
            long long candidato = amigo->amigos.lista[j];

            if(candidato == id_usuario){
                continue;
            }
            if(usuario->amigos.buscar(candidato) != -1){
                continue;
            }

            long long valor_actual = 0;
            bool existia = contador.buscar(candidato, valor_actual);
            if(!existia){
                candidatos.insert(candidato);
            }
            contador.insertar(candidato, valor_actual + 1);
        }
    }

    if(candidatos.current == 0){
        return;
    }

    HeapTree<SugerenciaAmistad> ranking(candidatos.current, mayor_afinidad);

    for(long long i = 0; i < candidatos.current; i++){
        long long id_candidato = candidatos.lista[i];
        long long comunes = 0;
        contador.buscar(id_candidato, comunes);

        SugerenciaAmistad sugerencia;
        sugerencia.id_usuario = id_candidato;
        sugerencia.amigos_en_comun = comunes;

        ranking.insertar(sugerencia);
    }

    long long limite = cantidad;
    if(limite > candidatos.current){
        limite = candidatos.current;
    }

    for(long long i = 0; i < limite; i++){
        SugerenciaAmistad top{0, 0};
        ranking.extraer_maximo(top);
        salida.insert(top);
    }
}
