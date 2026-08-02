#ifndef GRAFO_AMISTAD_H
#define GRAFO_AMISTAD_H

#include "Sistema.h"
#include "Listas.h"

// Una sugerencia de amistad: candidato + cuantos amigos en comun tiene
// con el usuario que pide la sugerencia.
struct SugerenciaAmistad {
    long long id_usuario;
    long long amigos_en_comun;
};

// Modulo del grafo de amistades. No guarda datos propios: usa las listas
// de amigos que ya viven dentro de cada Usuario (Sistema no se modifica).
class GrafoAmistad {
public:
    GrafoAmistad(Sistema& sistema);

    // BFS: camino mas corto (en saltos) entre dos usuarios.
    // Devuelve true si existe conexion. camino_salida queda con los ids
    // en orden (incluye origen y destino). distancia_salida = cantidad
    // de saltos (amigos directos = 1).
    bool ruta_amistad(
        long long origen,
        long long destino,
        Lista<long long>& camino_salida,
        long long& distancia_salida
    );

    // Amigos que comparten dos usuarios.
    void amigos_en_comun(
        long long id1,
        long long id2,
        Lista<long long>& salida
    );

    // Amigos de mis amigos que todavia no son mis amigos,
    // ordenados de mayor a menor cantidad de amigos en comun.
    void sugerencias_amistad(
        long long id_usuario,
        long long cantidad,
        Lista<SugerenciaAmistad>& salida
    );

private:
    Sistema& sistema;
    long long capacidad_ids() const;
};

#endif
