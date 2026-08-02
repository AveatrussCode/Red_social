#include "../model/CreadorBots.h"

#include <string>

CreadorBots::CreadorBots( Sistema& sistema, unsigned long long semilla) : sistema(sistema) {
    if (semilla == 0) {
        semilla = 88172645463325252ULL;
    }
    estadoRandom = semilla;
    siguienteComentarioId = 1;
}

unsigned long long CreadorBots::siguienteRandom() {
    estadoRandom ^= estadoRandom << 13;
    estadoRandom ^= estadoRandom >> 7;
    estadoRandom ^= estadoRandom << 17;

    return estadoRandom;
}

long long CreadorBots::randomEntre( long long minimo,long long maximo) {
    if (maximo <= minimo) {
        return minimo;
    }

    unsigned long long rango = static_cast<unsigned long long>(maximo - minimo + 1);

    return minimo + static_cast<long long>(siguienteRandom() % rango);
}

std::string CreadorBots::generarNombre(long long numeroBot) {
    static const char* nombres[] = {
        "Ana", "Luis", "Carlos", "Maria",
        "Lucia", "Pedro", "Valeria", "Diego",
        "Camila", "Jose", "Daniel", "Andrea",
        "Sofia", "Miguel", "Renata", "Jorge"
    };

    static const char* apellidos[] = {
        "Quispe", "Flores", "Rojas", "Torres",
        "Mendoza", "Vargas", "Castro", "Ramirez",
        "Huaman", "Salazar", "Paredes", "Chavez",
        "Condori", "Lopez", "Sanchez", "Medina"
    };

    const long long cantidadNombres = 16;
    const long long cantidadApellidos = 16;

    long long posicionNombre = randomEntre(0, cantidadNombres - 1);

    long long posicionApellido = randomEntre(0, cantidadApellidos - 1);

    std::string resultado;

    resultado += nombres[posicionNombre];
    resultado += " ";
    resultado += apellidos[posicionApellido];
    resultado += " Bot";
    resultado += std::to_string(numeroBot);

    return resultado;
}

std::string CreadorBots::generarTextoPost() {
    static const char* textos[] = {
        "Hoy fue un buen dia para aprender algo nuevo.",
        "Trabajando en un nuevo proyecto.",
        "Que opinan sobre las estructuras de datos?",
        "Acabo de publicar mi primera actualizacion.",
        "Programar tambien es resolver problemas.",
        "Saludos a todos mis amigos.",
        "Hoy estoy practicando algoritmos.",
        "Me gusta conocer personas nuevas.",
        "Terminando algunas tareas pendientes.",
        "Preparandome para una nueva semana.",
        "Alguien mas esta aprendiendo C++?",
        "Las tablas hash son bastante interesantes.",
        "Un cafe y a seguir programando.",
        "Compartiendo un poco de mi dia.",
        "Espero que todos tengan un excelente dia."
    };

    const long long cantidadTextos = 15;

    return textos[randomEntre(0, cantidadTextos - 1)];
}

std::string CreadorBots::generarComentario() {
    static const char* comentarios[] = {
        "Excelente publicacion.",
        "Estoy de acuerdo.",
        "Muy interesante.",
        "Gracias por compartir.",
        "Que buena idea.",
        "Me gusto bastante.",
        "Buen trabajo.",
        "Pienso algo parecido.",
        "Saludos.",
        "Interesante punto de vista.",
        "Totalmente cierto.",
        "Espero ver mas publicaciones."
    };

    const long long cantidadComentarios = 12;

    return comentarios[randomEntre(0, cantidadComentarios - 1)];
}

void CreadorBots::generarAutomaticamente() {
    long long cantidad = randomEntre(1000, 20000);
    generar(cantidad);
}

void CreadorBots::generar(long long cantidad) {
    if (cantidad < 1) {
        cantidad = 1;
    }

    if (cantidad > 20000) {
        cantidad = 20000;
    }

    crearBots(cantidad);
    crearAmistades();
    crearPublicaciones();
    crearInteracciones();
}

void CreadorBots::crearBots(long long cantidad) {
    for (long long i = 0; i < cantidad; i++) {
        std::string nombre = generarNombre(i + 1);

        Usuario* nuevoBot = sistema.registrar_usuario(nombre);

        if (nuevoBot != nullptr) {
            idsBots.insert(nuevoBot->id);
        }
    }
}

bool CreadorBots::conectarUsuarios(
    long long idUsuario1,
    long long idUsuario2
) {
    if (idUsuario1 == idUsuario2) {
        return false;
    }

    Usuario* usuario1 = sistema.buscar_usuario(idUsuario1);

    Usuario* usuario2 = sistema.buscar_usuario(idUsuario2);

    if (usuario1 == nullptr || usuario2 == nullptr) {
        return false;
    }

    if (usuario1->amigos.buscar(idUsuario2) != -1) {
        return false;
    }

    usuario1->agregar_amigo(idUsuario2);
    usuario2->agregar_amigo(idUsuario1);

    return true;
}

void CreadorBots::crearAmistades() {
    if (idsBots.current < 2) {
        return;
    }

    for (long long i = 0; i < idsBots.current; i++) {
        long long idBotActual = idsBots.lista[i];

        long long cantidadAmigos =
            randomEntre(2, 15);

        for (long long j = 0; j < cantidadAmigos; j++) {
            long long posicionAleatoria =
                randomEntre(0, idsBots.current - 1);

            long long idOtroBot =
                idsBots.lista[posicionAleatoria];

            conectarUsuarios(idBotActual, idOtroBot);
        }
    }
}

void CreadorBots::crearPublicaciones() {
    for (long long i = 0; i < idsBots.current; i++) {
        long long idBot = idsBots.lista[i];

        long long cantidadPublicaciones =
            randomEntre(1, 5);

        for ( long long publicacion = 0; publicacion < cantidadPublicaciones; publicacion++) {

            int dia = static_cast<int>(randomEntre(1, 28));
            int fecha = 20260800 + dia;

            std::string texto = generarTextoPost();

            std::string imagen;

            if (randomEntre(0, 3) == 0) {
                imagen = "Fotografia simulada del bot";
            } else {
                imagen = "";
            }

            Post* nuevoPost = sistema.crear_post( idBot, fecha, texto, imagen);

            if (nuevoPost != nullptr) {
                idsPosts.insert(nuevoPost->id_post);

                Usuario* propietario = sistema.buscar_usuario(idBot);
      
                if (propietario != nullptr) {
                    if ( propietario->publicaciones.buscar( nuevoPost->id_post ) == -1) {
                        propietario->agregar_publicacion(
                            nuevoPost->id_post
                        );
                    }
                }
            }
        }
    }
}

void CreadorBots::crearInteracciones() {
    if (  idsBots.current == 0 || idsPosts.current == 0) {
        return;
    }
    long long cantidadInteracciones =
        idsBots.current * 8;

    for ( long long i = 0; i < cantidadInteracciones; i++) {
        long long posicionUsuario = randomEntre(0, idsBots.current - 1);

        long long posicionPost = randomEntre(0, idsPosts.current - 1);

        long long idUsuario = idsBots.lista[posicionUsuario];

        long long idPost = idsPosts.lista[posicionPost];

        Post* post = sistema.buscar_post(idPost);

        if (post == nullptr) {
            continue;
        }

        long long tipoInteraccion = randomEntre(0, 9);

        if (tipoInteraccion <= 5) {
            post->like++;
            sistema.registrar_reaccion_usuario(idUsuario);
        }
        else if (tipoInteraccion == 6) {
            post->dislike++;
            sistema.registrar_reaccion_usuario(idUsuario);
        }
        else {
            Comentario nuevoComentario(idUsuario,generarComentario());

            post->new_comentario(nuevoComentario);
            sistema.registrar_comentario_usuario(idUsuario);
        }
    }
}

long long CreadorBots::cantidadBots() const {
    return idsBots.current;
}

long long CreadorBots::cantidadPosts() const {
    return idsPosts.current;
}

void CreadorBots::reaccionAleatoria() {
    if (idsPosts.current == 0 || idsBots.current == 0) {
        return;
    }

    long long idPost =
        idsPosts.lista[randomEntre(0, idsPosts.current - 1)];

    long long idUsuario =
        idsBots.lista[randomEntre(0, idsBots.current - 1)];

    Post* post = sistema.buscar_post(idPost);
    if (post == nullptr) {
        return;
    }

    if (randomEntre(0, 5) == 0) {
        post->dislike++;
    } else {
        post->dar_like();
    }

    sistema.registrar_reaccion_usuario(idUsuario);
}

void CreadorBots::comentarioAleatorio() {
    if (idsPosts.current == 0 || idsBots.current == 0) {
        return;
    }

    long long idPost =
        idsPosts.lista[randomEntre(0, idsPosts.current - 1)];

    long long idUsuario =
        idsBots.lista[randomEntre(0, idsBots.current - 1)];

    Post* post = sistema.buscar_post(idPost);
    if (post == nullptr) {
        return;
    }

    Comentario nuevo(idUsuario, generarComentario());
    post->new_comentario(nuevo);
    sistema.registrar_comentario_usuario(idUsuario);
}

void CreadorBots::amistadAleatoria() {
    if (idsBots.current < 2) {
        return;
    }

    long long id1 = idsBots.lista[randomEntre(0, idsBots.current - 1)];
    long long id2 = idsBots.lista[randomEntre(0, idsBots.current - 1)];

    conectarUsuarios(id1, id2);
}

void CreadorBots::publicacionAleatoria() {
    if (idsBots.current == 0) {
        return;
    }

    long long idBot = idsBots.lista[randomEntre(0, idsBots.current - 1)];

    int dia = static_cast<int>(randomEntre(1, 28));
    int fecha = 20260800 + dia;

    std::string imagen;
    if (randomEntre(0, 3) == 0) {
        imagen = "Fotografia simulada del bot";
    }

    Post* nuevoPost =
        sistema.crear_post(idBot, fecha, generarTextoPost(), imagen);

    if (nuevoPost != nullptr) {
        idsPosts.insert(nuevoPost->id_post);
    }
}

void CreadorBots::nuevoBotAleatorio() {
    std::string nombre = generarNombre(idsBots.current + 1);

    Usuario* nuevoBot = sistema.registrar_usuario(nombre);
    if (nuevoBot == nullptr) {
        return;
    }

    idsBots.insert(nuevoBot->id);

    if (idsBots.current > 1) {
        long long cantidadAmigos = randomEntre(1, 4);
        for (long long i = 0; i < cantidadAmigos; i++) {
            long long idOtroBot =
                idsBots.lista[randomEntre(0, idsBots.current - 2)];
            conectarUsuarios(nuevoBot->id, idOtroBot);
        }
    }
}

void CreadorBots::ejecutarActividadAleatoria(long long cantidadAcciones) {
    if (cantidadAcciones < 1) {
        return;
    }

    if (idsBots.current == 0) {
        crearBots(50);
        crearAmistades();
        crearPublicaciones();
    }

    for (long long i = 0; i < cantidadAcciones; i++) {
        long long tipoAccion = randomEntre(0, 99);

        if (tipoAccion < 55) {
            reaccionAleatoria();
        }
        else if (tipoAccion < 80) {
            comentarioAleatorio();
        }
        else if (tipoAccion < 92) {
            amistadAleatoria();
        }
        else if (tipoAccion < 98) {
            publicacionAleatoria();
        }
        else {

            nuevoBotAleatorio();
        }
    }
}
