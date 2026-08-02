#ifndef GRAFO_AMISTAD_H
#define GRAFO_AMISTAD_H

#include "Sistema.h"
#include "Listas.h"


struct SugerenciaAmistad {
    long long id_usuario;
    long long amigos_en_comun;
};


class GrafoAmistad {
public:
    GrafoAmistad(Sistema& sistema);

    // BFS
    bool ruta_amistad(long long origen, long long destino, Lista<long long>& camino_salida, long long& distancia_salida);

    void amigos_en_comun(  long long id1, long long id2, Lista<long long>& salida);


    void sugerencias_amistad( long long id_usuario,  long long cantidad,Lista<SugerenciaAmistad>& salida);

private:
    Sistema& sistema;
    long long capacidad_ids() const;
};

#endif
