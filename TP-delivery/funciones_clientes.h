#ifndef FUNCIONES_CLIENTES_H_INCLUDED
#define FUNCIONES_CLIENTES_H_INCLUDED

int menu_clientes()
{
int opcion;
    cls();
    setColor (BLACK);
    cout<<"*-    -    -    -    -    -    -    -    -    -    -    -   *"<<endl<<endl;
    resetColor();
    cout<<"*--------------      MEN� CLIENTES           ---------------*"<<endl;
    cout<<"*-----------------------------------------------------------*"<<endl;
    cout<<"*-------------- 1) NUEVO CLIENTE             ---------------*"<<endl;
    cout<<"*-------------- 2) MODIFICAR CLIENTE         ---------------*"<<endl;
    cout<<"*-------------- 3) LISTAR CLIENTE POR ID     ---------------*"<<endl;
    cout<<"*-------------- 4) LISTAR TODOS LOS CLIENTES ---------------*"<<endl;
    cout<<"*-------------- 5) ELIMINAR CLIENTE          ---------------*"<<endl;
    cout<<"*-----------------------------------------------------------*"<<endl;
    cout<<"*-------------- 0) VOLVER AL MEN� PRINCIPAL  ---------------*"<<endl<<endl;
    setColor (BLACK);
    cout<<"*-    -    -    -    -    -    -    -    -    -    -    -   *"<<endl<<endl;
    resetColor();
    cout<<"Ingrese una opci�n: ";
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
            while (!(modificar_cliente()))
            {
                if(!(menu_reintentar())) break;
            };
        } break;
        case 3:
        {

             while (!(listar_cliente_por_ID()))
            {
                if(!(menu_reintentar())) break;
            };
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

void mostrar_registro(Clientes cliente)
{
    cout<<"ID:";
    gotoxy(25,3);
    cout<<cliente.ID<<endl;

    cout<<"Apellido:";
    gotoxy(25,4);
    cout<<cliente.apellido<<endl;

    cout<<"Nombre:";
    gotoxy(25,5);
    cout<<cliente.nombre<<endl;

    cout<<"Mail:";
    gotoxy(25,6);
    cout<<cliente.mail<<endl;

    cout<<"Domicilio:";
    gotoxy(25,7);
    cout<<cliente.domicilio<<endl;

    cout<<"C�digo Postal:";
    gotoxy(25,8);
    cout<<cliente.codigo_postal<<endl;

    cout<<"Fecha de Nacimiento:";
    gotoxy(25,9);
    cout<<cliente.fecha.dia<<"/"<<cliente.fecha.mes<<"/"<<cliente.fecha.anio<<endl;

    cout<<"Estado:";
    gotoxy(25,10);
    cout<<cliente.estado<<endl;

    setColor (BLACK);
    cout<<"*--------------------------------------------------------*"<<endl;
    resetColor();
}

bool listar_cliente_por_ID()
{
 Clientes cliente;
 int ID,pos;

 cls();
 cout<<"Ingrese el ID del Cliente buscado: ";
 if (!(validacion_entero(&ID)))return false;
 cout<<endl;

 pos= buscar_cliente_por_ID(ID);
 if (pos<0) return false;

 FILE *p;
 p= fopen(archivo_clientes, "rb");
 if (p==NULL)
 {
     cout<<"El archivo no se ha podido abrir.";
     return false;
 }
 fseek(p, pos*sizeof (Clientes),0);
 fread(&cliente, sizeof (Clientes),1,p);

fclose(p);
mostrar_registro(cliente);
anykey();
return true;
}

int buscar_cliente_por_ID(int ID)
{
    Clientes cliente;
    FILE *p;
    p= fopen(archivo_clientes, "rb");

    if (p == NULL)
    {
        cout<<" No pudo abrir el archivo.";
        anykey();
        return -2;
    }

    while (fread(&cliente, sizeof (Clientes), 1, p))
    {
        if (ID == cliente.ID && cliente.estado)
        {
            fseek(p,(ftell (p)-sizeof (Clientes)),0);
            return ftell(p)/sizeof (Clientes);
        }
    }

fclose(p);
cout<<"El cliente no existe o est� dado de baja.";
anykey();
return -1;
}

bool modificar_domicilio (int ID, int pos)
{
    Clientes cliente;
    FILE *p;
    p=fopen(archivo_clientes, "rb+");

    if (p==NULL)
    {
        cout<<" No pudo abrir el archivo.";
        anykey();
        return false;
    }

    fseek(p,pos*sizeof(Clientes),0);
    fread(&cliente, sizeof (Clientes),1, p);
    cout<<"El domicilio ha modificar es: "<<cliente.domicilio<<endl;
    cout<<"Ingrese el nuevo domicilio: ";
    gotoxy(31,4);
    cin.ignore();
    cin.getline (cliente.domicilio,100);
    if (!(validacion_cadena(cliente.domicilio)))
    {
        cout<<"El domicilio no es valido.";
        anykey();
        return false;
    }
    else
    {
        fseek(p,pos*sizeof (Clientes),0);
        if (!(fwrite(&cliente, sizeof(Clientes),1,p)))
        {
            cout<<"No se ha podido guardar la direcci�n del cliente.";
            anykey();
            return false;
        }
    }
    fclose(p);
    cout<<"\nEl domicilio ha sido modificado exitosamente.";
    anykey();
    return true;
}

bool modificar_cliente()
{
    int ID, pos;

    cls();
    cout<<"Ingrese el ID del cliente a modificar: ";
    if (!validacion_entero(&ID))
    {
        cout<<"Tipo de dato incorrecto.";
        anykey();
        return false;
    }
    cout<<endl;
    pos= buscar_cliente_por_ID(ID);
    if (pos <0)return false;
    return modificar_domicilio(ID,pos);
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
    cout<<"C�digo Postal: "<<endl;
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
