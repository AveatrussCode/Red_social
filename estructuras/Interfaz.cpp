#include "../model/Interfaz.h"
#include "../model/GrafoAmistad.h"

#include <iostream>

namespace {

const char* MESES[] = {
    "", "enero", "febrero", "marzo", "abril", "mayo", "junio",
    "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre"
};

// Convierte fechas guardadas como AAAAMMDD (ej. 20260802) en texto
// legible ("2 de agosto de 2026"). Si el formato no calza, avisa
// en vez de mostrar un numero crudo.
std::string formatear_fecha(int fecha){
    int anio = fecha / 10000;
    int mes = (fecha / 100) % 100;
    int dia = fecha % 100;

    if(anio == 0 || mes < 1 || mes > 12 || dia < 1 || dia > 31){
        return "fecha no disponible";
    }

    std::string resultado = std::to_string(dia);
    resultado += " de ";
    resultado += MESES[mes];
    resultado += " de ";
    resultado += std::to_string(anio);

    return resultado;
}

// Traduce el numero crudo de actividad a una etiqueta entendible.
std::string nivel_actividad(long long actividad){
    if(actividad == 0) return "recien llegado";
    if(actividad < 10) return "empezando a moverse";
    if(actividad < 50) return "activo";
    if(actividad < 150) return "muy activo";
    return "superusuario de la comunidad";
}

std::string plural(long long cantidad, std::string singular, std::string en_plural){
    return cantidad == 1 ? singular : en_plural;
}

void separador(){
    std::cout << "----------------------------------------\n";
}

// Dispara actividad de bots en segundo plano despues de una accion
// real del usuario, para que la comunidad se sienta viva. Solo avisa
// algo al usuario cuando hay un cambio visible (usuarios nuevos), para
// no saturar la pantalla con ruido en cada paso.
void activar_vida_de_fondo(Sistema& sistema, CreadorBots& bots){
    long long usuarios_antes = sistema.usuarios.tamano();

    bots.ejecutarActividadAleatoria(100);

    long long usuarios_despues = sistema.usuarios.tamano();

    if(usuarios_despues > usuarios_antes){
        long long nuevos = usuarios_despues - usuarios_antes;
        std::cout << "\n(mientras tanto, " << nuevos << " "
                  << plural(nuevos, "persona nueva se unio", "personas nuevas se unieron")
                  << " a la comunidad)\n";
    }
}

}

void menu_principal(Sistema& sistema, CreadorBots& bots){

    int opcion;

    do{
        std::cout << "\n===== FACEBOOK 2 =====\n";
        std::cout << "1. Registrar usuario\n";
        std::cout << "2. Iniciar sesion\n";
        std::cout << "3. Usuarios mas activos\n";
        std::cout << "4. Posts mas populares\n";
        std::cout << "0. Salir\n";

        std::cout << "Opcion: ";
        std::cin >> opcion;

        switch(opcion){

            case 1:
                registrar_usuario_interfaz(sistema);
                activar_vida_de_fondo(sistema, bots);
                break;

            case 2:
            {
                Usuario* usuario = iniciar_sesion(sistema);

                if(usuario != nullptr){
                    sistema.usuario_actual = usuario;
                    menu_usuario(sistema, bots, usuario);
                    sistema.usuario_actual = nullptr;
                }

                break;
            }

            case 3:
                sistema.mostrar_usuarios_activos(10);
                break;

            case 4:
                sistema.mostrar_posts_mas_reaccionados(10);
                break;

            case 0:
                std::cout << "Hasta pronto!\n";
                break;

            default:
                std::cout << "Opcion invalida\n";
        }

    }while(opcion != 0);

}

void menu_usuario(Sistema& sistema, CreadorBots& bots, Usuario* usuario){

    int opcion;

    do{
        std::cout << "\n===== MENU USUARIO =====\n";
        std::cout << "Hola, " << usuario->name << "\n\n";

        std::cout << "1. Ver perfil\n";
        std::cout << "2. Crear publicacion\n";
        std::cout << "3. Ver amigos\n";
        std::cout << "4. Ver publicaciones\n";
        std::cout << "5. Personas que quizas conozcas\n";
        std::cout << "6. Ver mi conexion con otro usuario\n";
        std::cout << "7. Ver amigos en comun con otro usuario\n";
        std::cout << "0. Cerrar sesion\n";

        std::cout << "Opcion: ";
        std::cin >> opcion;

        switch(opcion){

            case 1:
                mostrar_perfil(usuario);
                break;

            case 2:
                crear_publicacion(sistema, usuario);
                activar_vida_de_fondo(sistema, bots);
                break;

            case 3:
                mostrar_amigos(sistema, usuario);
                break;

            case 4:
                mostrar_publicaciones(sistema, usuario);
                break;

            case 5:
                ver_sugerencias_amistad(sistema, usuario);
                activar_vida_de_fondo(sistema, bots);
                break;

            case 6:
                ver_ruta_amistad(sistema, usuario);
                break;

            case 7:
                ver_amigos_en_comun(sistema, usuario);
                break;

            case 0:
                std::cout << "Cerrando sesion\n";
                break;

            default:
                std::cout << "Opcion invalida\n";
        }

    }while(opcion != 0);

}

void mostrar_perfil(Usuario* usuario){

    std::cout << "\n===== PERFIL =====\n";
    separador();

    std::cout << "ID: " << usuario->id << "\n";
    std::cout << "Nombre: " << usuario->name << "\n";
    std::cout << "Correo: " << usuario->Correo << "\n";

    std::cout << usuario->cantidad_amigos << " "
              << plural(usuario->cantidad_amigos, "amigo", "amigos") << "\n";

    std::cout << usuario->seguidores << " "
              << plural(usuario->seguidores, "seguidor", "seguidores") << "\n";

    std::cout << usuario->publicaciones.current << " "
              << plural(usuario->publicaciones.current, "publicacion", "publicaciones") << "\n";

    std::cout << "Nivel de actividad: " << nivel_actividad(usuario->calcular_actividad())
              << " (" << usuario->calcular_actividad() << " puntos)\n";

    separador();
}

void mostrar_amigos(Sistema& sistema, Usuario* usuario){

    std::cout << "\n===== AMIGOS =====\n";

    if(usuario->amigos.current == 0){
        std::cout << "Todavia no tienes amigos. Anima a alguien a conectarse contigo.\n";
        return;
    }

    for(long long i = 0; i < usuario->amigos.current; i++){
        long long id = usuario->amigos.lista[i];
        Usuario* amigo = sistema.buscar_usuario(id);

        if(amigo != nullptr){
            std::cout << "- " << amigo->name << " (ID " << amigo->id << ")\n";
        }
    }
}

void mostrar_publicaciones(Sistema& sistema, Usuario* usuario){

    std::cout << "\n===== PUBLICACIONES =====\n";

    if(usuario->publicaciones.current == 0){
        std::cout << "Todavia no has publicado nada.\n";
        return;
    }

    for(long long i = 0; i < usuario->publicaciones.current; i++){
        long long idPost = usuario->publicaciones.lista[i];
        Post* post = sistema.buscar_post(idPost);

        if(post != nullptr){
            std::cout << "\n" << formatear_fecha(post->fecha) << "\n";
            std::cout << post->cabecera << "\n";
            std::cout << post->like << " " << plural(post->like, "like", "likes")
                      << ", " << post->dislike << " " << plural(post->dislike, "dislike", "dislikes")
                      << ", " << post->comentarios.current << " "
                      << plural(post->comentarios.current, "comentario", "comentarios") << "\n";
        }
    }
}

void crear_publicacion(Sistema& sistema, Usuario* usuario){

    std::string texto;

    std::cout << "Escribe tu publicacion: ";
    std::cin.ignore();
    std::getline(std::cin, texto);

    Post* nuevo = sistema.crear_post(usuario->id, 20260802, texto, "");

    if(nuevo != nullptr){
        std::cout << "Publicacion creada ID: " << nuevo->id_post << "\n";
    }
}

void registrar_usuario_interfaz(Sistema& sistema){

    std::string nombre;

    std::cout << "Nombre del usuario: ";
    std::cin.ignore();
    std::getline(std::cin, nombre);

    Usuario* nuevo = sistema.registrar_usuario(nombre);

    if(nuevo){
        std::cout << "Listo, " << nuevo->name << ". Tu ID es " << nuevo->id << "\n";
    }
}

Usuario* iniciar_sesion(Sistema& sistema){

    long long id;

    std::cout << "Ingrese ID: ";
    std::cin >> id;

    Usuario* usuario = sistema.buscar_usuario(id);

    if(usuario == nullptr){
        std::cout << "Usuario no encontrado\n";
    } else {
        std::cout << "Bienvenido " << usuario->name << "\n";
    }

    return usuario;
}

void ver_sugerencias_amistad(Sistema& sistema, Usuario* usuario){

    GrafoAmistad grafo(sistema);
    Lista<SugerenciaAmistad> sugerencias;

    grafo.sugerencias_amistad(usuario->id, 5, sugerencias);

    std::cout << "\n===== PERSONAS QUE QUIZAS CONOZCAS =====\n";

    if(sugerencias.current == 0){
        std::cout << "Por ahora no tenemos sugerencias para ti. "
                  << "Agrega algunos amigos y vuelve a intentarlo.\n";
        return;
    }

    for(long long i = 0; i < sugerencias.current; i++){
        SugerenciaAmistad sugerencia = sugerencias.lista[i];
        Usuario* candidato = sistema.buscar_usuario(sugerencia.id_usuario);

        if(candidato == nullptr){
            continue;
        }

        std::cout << (i + 1) << ". " << candidato->name
                  << " (ID " << candidato->id << ") - "
                  << sugerencia.amigos_en_comun << " "
                  << plural(sugerencia.amigos_en_comun, "amigo en comun", "amigos en comun")
                  << "\n";
    }
}

void ver_ruta_amistad(Sistema& sistema, Usuario* usuario){

    long long idDestino;

    std::cout << "\nID del usuario con quien quieres ver tu conexion: ";
    std::cin >> idDestino;

    Usuario* destino = sistema.buscar_usuario(idDestino);
    if(destino == nullptr){
        std::cout << "No encontramos a ese usuario.\n";
        return;
    }

    GrafoAmistad grafo(sistema);
    Lista<long long> camino;
    long long distancia;

    bool encontrado = grafo.ruta_amistad(usuario->id, idDestino, camino, distancia);

    if(!encontrado){
        std::cout << "\nTodavia no hay una cadena de amistades que los conecte.\n";
        return;
    }

    if(distancia == 0){
        std::cout << "\nEse eres tu mismo :)\n";
        return;
    }

    std::cout << "\nEstas a " << distancia << " "
              << plural(distancia, "conexion", "conexiones")
              << " de " << destino->name << ":\n\n";

    for(long long i = 0; i < camino.current; i++){
        Usuario* persona = sistema.buscar_usuario(camino.lista[i]);
        if(persona == nullptr){
            continue;
        }

        std::cout << "  " << persona->name;
        if(i < camino.current - 1){
            std::cout << "  ->  ";
        }
    }
    std::cout << "\n";
}

void ver_amigos_en_comun(Sistema& sistema, Usuario* usuario){

    long long idOtro;

    std::cout << "\nID del otro usuario: ";
    std::cin >> idOtro;

    Usuario* otro = sistema.buscar_usuario(idOtro);
    if(otro == nullptr){
        std::cout << "No encontramos a ese usuario.\n";
        return;
    }

    GrafoAmistad grafo(sistema);
    Lista<long long> comunes;

    grafo.amigos_en_comun(usuario->id, idOtro, comunes);

    if(comunes.current == 0){
        std::cout << "\nNo tienen amigos en comun todavia.\n";
        return;
    }

    std::cout << "\nTienen " << comunes.current << " "
              << plural(comunes.current, "amigo en comun", "amigos en comun")
              << ":\n";

    for(long long i = 0; i < comunes.current; i++){
        Usuario* persona = sistema.buscar_usuario(comunes.lista[i]);
        if(persona != nullptr){
            std::cout << "  - " << persona->name << "\n";
        }
    }
}
