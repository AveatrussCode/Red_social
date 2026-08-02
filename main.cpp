#include "model/Sistema.h"
#include "model/CreadorBots.h"
#include "model/Interfaz.h"

int main(){

    Sistema sistema;

    CreadorBots generador(sistema);

    generador.generarAutomaticamente();

    menu_principal(sistema, generador);

    return 0;
}
