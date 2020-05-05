#ifndef FUNCIONES_CLIENTES_H_INCLUDED
#define FUNCIONES_CLIENTES_H_INCLUDED

int menu_clientes()
{
int opcion;
    cls();
    setColor (BLACK);
    cout<<"*-    -    -    -    -    -    -    -    -    -    -    -   *"<<endl<<endl;
    resetColor();
    cout<<"*--------------      MENÚ CLIENTES           ---------------*"<<endl;
    cout<<"*-----------------------------------------------------------*"<<endl;
    cout<<"*-------------- 1) NUEVO CLIENTE             ---------------*"<<endl;
    cout<<"*-------------- 2) MODIFICAR CLIENTE         ---------------*"<<endl;
    cout<<"*-------------- 3) LISTAR CLIENTE POR ID     ---------------*"<<endl;
    cout<<"*-------------- 4) LISTAR TODOS LOS CLIENTES ---------------*"<<endl;
    cout<<"*-------------- 5) ELIMINAR CLIENTE          ---------------*"<<endl;
    cout<<"*-----------------------------------------------------------*"<<endl;
    cout<<"*-------------- 0) VOLVER AL MENÚ PRINCIPAL  ---------------*"<<endl<<endl;
    setColor (BLACK);
    cout<<"*-    -    -    -    -    -    -    -    -    -    -    -   *"<<endl<<endl;
    resetColor();
    cout<<"Ingrese una opción: ";
    gotoxy(21,15);
    setColor (BLACK);
    bool validado = validacion_entero (&opcion);
    if (!validado) opcion=-1;
    resetColor();
return opcion;
}


void seccion_clientes()
{
    int op=1;

    while(op!=0)
    {
        op = menu_clientes();

        switch(op)
        {
        case 1:
        {
            while(!(ingresar_cliente()))
            {
                if(!(menu_reintentar())) break;
            }
        } break;
        case 2:
        {
            //modificar_cliente();
        } break;
        case 3:
        {
            //listar_cliente_por_ID();
        } break;
        case 4:
        {
            //listar_todos_los_clientes();
        } break;
        case 5:
        {
            //eliminar_cliente();
        } break;
        case 0:
        {} break;
        default:
        {
            if(!menu_reintentar()) return;
        }break;
        }

        anykey();
    }
}

bool ingresar_cliente()
{
    Clientes cliente;
    if(!cargar_cliente(&cliente)) return false;

    FILE *p;
    p=fopen(archivo_clientes,"ab");
    if(p==NULL)
    {
        cout<<"El archivo no se ha podido abrir."<<endl;
        return false;
    }

    if(!(fwrite(&cliente, sizeof (Clientes),1,p)))
    {
        cout<<"El archivo no se ha podido leer."<<endl;
        return false;
    }
    fclose(p);

    setColor(LIGHTBLUE);
    cout<<"\nCliente cargado exitosamente!! =D"<<endl;
    resetColor();
return true;
}

bool cargar_cliente(Clientes *cliente)
{
    cliente->ID= 1+tamanio_archivo(archivo_clientes,sizeof(Clientes));
    cls();

    cout<<"ID de cliente:"<<endl;
    cout<<"Apellido: "<<endl;
    cout<<"Nombre: "<<endl;
    cout<<"Mail: "<<endl;
    cout<<"Domicilio: "<<endl;
    cout<<"Código Postal: "<<endl;
    cout<<"Fecha de nacimiento: "<<endl;

    ///Hacer el gotoxys ///
    gotoxy(23,1);
    cout<<cliente->ID<<endl;

    gotoxy(23,2);
    cin.ignore();
    cin.getline(cliente->apellido,50);
    if(!(validacion_cadena(cliente->apellido))) return false;

    gotoxy(23,3);
    cin.getline(cliente->nombre,50);
    if(!(validacion_cadena(cliente->nombre))) return false;

    gotoxy(23,4);
    cin.getline(cliente->mail,50);
    if(!(validacion_mail(cliente->mail))) return false;

    gotoxy(23,5);
    cin.getline(cliente->domicilio,100);
    if(!(validacion_cadena(cliente->domicilio))) return false;

    gotoxy(23,6);
    if(!(validacion_entero(&(cliente->codigo_postal))))return false;
    if(cliente->codigo_postal <1000 || cliente->codigo_postal >9999) return false;

    gotoxy(23,7);
    if(!(validacion_entero(&(cliente->fecha.dia))))return false;
    if(cliente->fecha.dia <1 || cliente->fecha.dia>31) return false;
    gotoxy(25,7);
    cout<<"/";

    gotoxy(26,7);
    if(!(validacion_entero(&(cliente->fecha.mes))))return false;
    if(cliente->fecha.mes <1 || cliente->fecha.mes>12) return false;
    gotoxy(28,7);
    cout<<"/";

    gotoxy(29,7);
    if(!(validacion_entero(&(cliente->fecha.anio))))return false;
    if(cliente->fecha.anio<1900) return false;
    if(!(validacion_fecha(&(cliente->fecha)))) return false;

    cliente->estado=true;
return true;
}













#endif // FUNCIONES_CLIENTES_H_INCLUDED
