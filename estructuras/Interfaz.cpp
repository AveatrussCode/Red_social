#include "../model/Interfaz.h"

#include <iostream>


void menu_principal(Sistema& sistema){

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
                break;


            case 2:
            {
                Usuario* usuario =
                    iniciar_sesion(sistema);


                if(usuario != nullptr){

                    sistema.usuario_actual = usuario;

                    menu_usuario(
                        sistema,
                        usuario
                    );

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

                std::cout<<"Saliendo...\n";

                break;


            default:

                std::cout<<"Opcion invalida\n";
        }


    }while(opcion != 0);

}



void menu_usuario(
    Sistema& sistema,
    Usuario* usuario
){

    int opcion;


    do{

        std::cout << "\n===== MENU USUARIO =====\n";

        std::cout 
        << "Usuario: "
        << usuario->name
        << "\n\n";


        std::cout << "1. Ver perfil\n";
        std::cout << "2. Crear publicacion\n";
        std::cout << "3. Ver amigos\n";
        std::cout << "4. Ver publicaciones\n";
        std::cout << "0. Cerrar sesion\n";


        std::cout<<"Opcion: ";
        std::cin>>opcion;



        switch(opcion){

            case 1:

                mostrar_perfil(usuario);

                break;



            case 2:

                crear_publicacion(
                    sistema,
                    usuario
                );

                break;



            case 3:

                mostrar_amigos(
                    sistema,
                    usuario
                );

                break;



            case 4:

                mostrar_publicaciones(
                    sistema,
                    usuario
                );

                break;



            case 0:

                std::cout<<"Cerrando sesion\n";

                break;



            default:

                std::cout<<"Opcion invalida\n";
        }



    }while(opcion != 0);

}





void mostrar_perfil(
    Usuario* usuario
){

    std::cout<<"\n===== PERFIL =====\n";


    std::cout
    <<"ID: "
    <<usuario->id
    <<"\n";


    std::cout
    <<"Nombre: "
    <<usuario->name
    <<"\n";


    std::cout
    <<"Correo: "
    <<usuario->Correo
    <<"\n";


    std::cout
    <<"Amigos: "
    <<usuario->cantidad_amigos
    <<"\n";


    std::cout
    <<"Seguidores: "
    <<usuario->seguidores
    <<"\n";


    std::cout
    <<"Publicaciones: "
    <<usuario->publicaciones.current
    <<"\n";


    std::cout
    <<"Actividad: "
    <<usuario->calcular_actividad()
    <<"\n";

}





void mostrar_amigos(
    Sistema& sistema,
    Usuario* usuario
){

    std::cout<<"\n===== AMIGOS =====\n";


    for(
        long long i = 0;
        i < usuario->amigos.current;
        i++
    ){

        long long id =
            usuario->amigos.lista[i];


        Usuario* amigo =
            sistema.buscar_usuario(id);


        if(amigo != nullptr){

            std::cout
            <<"- "
            <<amigo->name
            <<" (ID "
            <<amigo->id
            <<")\n";

        }

    }

}





void mostrar_publicaciones(
    Sistema& sistema,
    Usuario* usuario
){

    std::cout<<"\n===== PUBLICACIONES =====\n";


    for(
        long long i = 0;
        i < usuario->publicaciones.current;
        i++
    ){

        long long idPost =
            usuario->publicaciones.lista[i];


        Post* post =
            sistema.buscar_post(idPost);



        if(post != nullptr){

            std::cout
            <<"\nPost ID: "
            <<post->id_post
            <<"\n";


            std::cout
            <<"Texto: "
            <<post->cabecera
            <<"\n";


            std::cout
            <<"Likes: "
            <<post->like
            <<" Dislikes: "
            <<post->dislike
            <<"\n";

        }

    }

}





void crear_publicacion(
    Sistema& sistema,
    Usuario* usuario
){

    std::string texto;


    std::cout
    <<"Escribe tu publicacion: ";


    std::cin.ignore();


    std::getline(
        std::cin,
        texto
    );


    Post* nuevo =
        sistema.crear_post(
            usuario->id,
            20260802,
            texto,
            ""
        );


    if(nuevo != nullptr){

        std::cout
        <<"Publicacion creada ID: "
        <<nuevo->id_post
        <<"\n";

    }

}





void registrar_usuario_interfaz(
    Sistema& sistema
){

    std::string nombre;


    std::cout
    <<"Nombre del usuario: ";


    std::cin.ignore();


    std::getline(
        std::cin,
        nombre
    );


    Usuario* nuevo =
        sistema.registrar_usuario(nombre);



    if(nuevo){

        std::cout
        <<"Usuario creado\n";


        std::cout
        <<"ID: "
        <<nuevo->id
        <<"\n";

    }

}





Usuario* iniciar_sesion(
    Sistema& sistema
){

    long long id;


    std::cout
    <<"Ingrese ID: ";


    std::cin>>id;



    Usuario* usuario =
        sistema.buscar_usuario(id);



    if(usuario == nullptr){

        std::cout
        <<"Usuario no encontrado\n";

    }
    else{

        std::cout
        <<"Bienvenido "
        <<usuario->name
        <<"\n";

    }


    return usuario;

}