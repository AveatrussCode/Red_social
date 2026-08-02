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
        std::string Correo;
        std::string fecha;
        int seguidores;
        int cantidad_amigos;
        long long reacciones_resividas;

        long long id;

        Lista<long long> amigos;
        Lista<long long> publicaciones;
        long long comentarios_realizados;
        long long reacciones_realizadas;

        Usuario(long long, std::string, std::string = "");
        void agregar_amigo(long long);
        void eliminar_amigo(long long);
        void agregar_publicacion(long long);
        void registrar_comentario();
        void registrar_reaccion();
        long long calcular_actividad() const;
        void nuevo_seguidor();
        void agregar_reacciones();
        void mostrar();

};



#endif
