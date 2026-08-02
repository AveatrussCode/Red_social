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

    void reaccionAleatoria();
    void comentarioAleatorio();
    void amistadAleatoria();
    void publicacionAleatoria(); 
    
    void nuevoBotAleatorio();

public:
    CreadorBots(
        Sistema& sistema,
        unsigned long long semilla = 88172645463325252ULL
    );

    void generarAutomaticamente();
    void generar(long long cantidad);

    // Ejecuta "cantidadAcciones" acciones aleatorias de bots (likes,
    // comentarios, nuevas amistades, publicaciones y, ocasionalmente,
    // nuevos bots). Pensado para llamarse despues de cada accion real
    // del usuario, para que la comunidad se sienta activa todo el tiempo.
    void ejecutarActividadAleatoria(long long cantidadAcciones = 100);

    long long cantidadBots() const;
    long long cantidadPosts() const;
};

#endif