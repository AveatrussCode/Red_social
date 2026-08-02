#ifndef CREADOR_BOTS_H
#define CREADOR_BOTS_H

#include "Sistema.h"
#include "Listas.h"

class CreadorBots {
private:
    Sistema& sistema;

    Lista<long long> idsBots;
    Lista<long long> idsPosts;

    unsigned long long estadoRandom;
    long long siguienteComentarioId;

    unsigned long long siguienteRandom();
    long long randomEntre(long long minimo, long long maximo);

    std::string generarNombre(long long numeroBot);
    std::string generarTextoPost();
    std::string generarComentario();

    void crearBots(long long cantidad);
    void crearAmistades();
    void crearPublicaciones();
    void crearInteracciones();

    bool conectarUsuarios(long long idUsuario1, long long idUsuario2);

public:
    CreadorBots(
        Sistema& sistema,
        unsigned long long semilla = 88172645463325252ULL
    );

    void generarAutomaticamente();
    void generar(long long cantidad);

    long long cantidadBots() const;
    long long cantidadPosts() const;
};

#endif