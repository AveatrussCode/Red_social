#ifndef INTERFAZ_H
#define INTERFAZ_H

#include "Sistema.h"
#include "Usuario.h"
#include "CreadorBots.h"

void menu_principal(Sistema& sistema, CreadorBots& bots);

void menu_usuario(Sistema& sistema, CreadorBots& bots, Usuario* usuario);

void mostrar_perfil(Usuario* usuario);

void mostrar_amigos(Sistema& sistema, Usuario* usuario);

void mostrar_publicaciones(Sistema& sistema, Usuario* usuario);

void crear_publicacion(Sistema& sistema, Usuario* usuario);


void registrar_usuario_interfaz(Sistema& sistema);

Usuario* iniciar_sesion(Sistema& sistema);

void ver_sugerencias_amistad(Sistema& sistema, Usuario* usuario);

void ver_ruta_amistad(Sistema& sistema, Usuario* usuario);


void ver_amigos_en_comun(Sistema& sistema, Usuario* usuario);

#endif
