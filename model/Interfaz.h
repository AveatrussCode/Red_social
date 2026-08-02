#ifndef INTERFAZ_H
#define INTERFAZ_H

#include "Sistema.h"
#include "Usuario.h"
#include "CreadorBots.h"

// Menu principal.
void menu_principal(Sistema& sistema, CreadorBots& bots);

// Menu de un usuario logueado.
void menu_usuario(Sistema& sistema, CreadorBots& bots, Usuario* usuario);

// Mostrar informacion del perfil.
void mostrar_perfil(Usuario* usuario);

// Mostrar lista de amigos.
void mostrar_amigos(Sistema& sistema, Usuario* usuario);

// Mostrar publicaciones del usuario.
void mostrar_publicaciones(Sistema& sistema, Usuario* usuario);

// Crear una nueva publicacion.
void crear_publicacion(Sistema& sistema, Usuario* usuario);

// Registrar usuario desde terminal.
void registrar_usuario_interfaz(Sistema& sistema);

// Iniciar sesion por ID.
Usuario* iniciar_sesion(Sistema& sistema);

// Personas que quizas conozcas (amigos de mis amigos, via GrafoAmistad).
void ver_sugerencias_amistad(Sistema& sistema, Usuario* usuario);

// Camino mas corto de amistades hacia otro usuario (BFS).
void ver_ruta_amistad(Sistema& sistema, Usuario* usuario);

// Amigos que comparto con otro usuario.
void ver_amigos_en_comun(Sistema& sistema, Usuario* usuario);

#endif
