#ifndef FUNCIONES_PLATOS_H_INCLUDED
#define FUNCIONES_PLATOS_H_INCLUDED

int menu_platos()
{

    int op;
    cls();

    cout<<"*--------------      MENÚ PLATOS             ---------------*"<<endl;
    cout<<"*-----------------------------------------------------------*"<<endl;
    cout<<"*-------------- 1) NUEVO PLATO               ---------------*"<<endl;
    cout<<"*-------------- 2) MODIFICAR PLATO           ---------------*"<<endl;
    cout<<"*-------------- 3) LISTAR PLATO POR ID       ---------------*"<<endl;
    cout<<"*-------------- 4) PLATOS POR RESTAURANT     ---------------*"<<endl;
    cout<<"*-------------- 5) LISTAR TODOS LOS PLATOS   ---------------*"<<endl;
    cout<<"*-------------- 6) ELIMINAR PLATO            ---------------*"<<endl;
    cout<<"*-----------------------------------------------------------*"<<endl;
    cout<<"*-------------- 0) VOLVER AL MENÚ PRINCIPAL  ---------------*"<<endl<<endl;

    cout<<"Ingrese una opción: ";
    bool validado = validacion_entero (&op);
    if (!validado) op=-1;
return op;
}


void seccion_platos()
{
int op;

    do{
        op = menu_platos();

        switch(op)
        {
            case 1:
                {
                    //nuevo_plato();
                }break;
            case 2:
                {
                    ///modificar_plato();
                }break;
            case 3:
                {
                    ///listar_plato_por_ID();
                }break;
            case 4:
                {
                    ///listar_plato_por_restaurant();
                }break;
            case 5:
                {
                    ///listar_todos_los_platos();
                }break;
            case 6:
                {
                    ///eliminar_plato();
                }break;

            case 0:{}break;
            default:
                {
                    cout<<"Opción ingresada no válida."<<endl;
                    bool reintentar = menu_reintentar();
                    if(!reintentar)op=0;
                }break;
        }
        anykey();

    }while(op!=0);
}

#endif // FUNCIONES_PLATOS_H_INCLUDED
