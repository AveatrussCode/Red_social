#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include "Listas.h"

class Usuario {
    public:
        static constexpr long long PESO_PUBLICACION = 1;
        static constexpr long long PESO_COMENTARIO = 1;
        static constexpr long long PESO_REACCION = 1;

        std::string name;
        long long id;

        Lista<long long> amigos;
        Lista<long long> publicaciones;
        long long comentarios_realizados;
        long long reacciones_realizadas;

        Usuario(int, std::string);
        void agregar_amigo(long long);
        void eliminar_amigo(long long);
        void agregar_publicacion(long long);
        void registrar_comentario();
        void registrar_reaccion();
        long long calcular_actividad() const;

};



#endif
