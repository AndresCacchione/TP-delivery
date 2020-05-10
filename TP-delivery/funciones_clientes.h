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

    gotoxy(1,30);
    cout<<"*                      ~SISTEMA LARA~                         *"<<endl;
    resetColor();
    gotoxy(1,15);
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
            listar_todos_los_clientes();
        } break;
        case 5:
        {
            while (!(eliminar_cliente()))
            {
                if(!(menu_reintentar())) break;
            };
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

bool eliminar_cliente()
{
    int ID, pos;
    Clientes cliente;

    cls();
    setColor(BLUE);
    cout<<"A qué cliente matamos, jefe? Diga un ID -.- : ";
    resetColor();
    if (!(validacion_entero(&ID))) return false;

    pos = buscar_cliente_por_ID(ID);
    if(pos<0) return false;

    FILE*p;
    p=fopen(archivo_clientes, "rb+");
    if(p==NULL) return false;

    fread(&cliente, sizeof (Clientes), 1, p);
    cliente.estado=false;

    fseek(p,pos*sizeof(Clientes),0);

    if(!(fwrite(&cliente, sizeof(Clientes), 1, p)))
    {
        cout<<"No pudimos escribir, somos analfabetos :C "<< endl;
        return false;
    }
    fclose(p);
    setColor(RED);
    cout<<"Cliente eliminado con éxito :) al fondo del rio .-."<<endl;
    resetColor();
return true;
}

bool listar_todos_los_clientes()
{
    cls();
    unsigned int tam=tamanio_archivo(archivo_clientes,sizeof (Clientes));
    Clientes *Todos_los_clientes;

    Todos_los_clientes = (Clientes *) malloc(tam*sizeof(Clientes));
    if(Todos_los_clientes==NULL)
    {
        cout<<"Ejecución interrumpida por falta de memoria."<<endl;
        return false;
    }

    FILE *p;
    p=fopen(archivo_clientes, "rb");
    if (p==NULL)
    {
        cout<<"No se ha podido abrir la base de datos."<<endl;
        return false;
    }

    if((fread(Todos_los_clientes,sizeof (Clientes),tam,p)) != tam)
    {
        cout<<"Error en la lectura de los registros."<<endl;
        return false;
    }
    fclose(p);

    ordenar_por_apellido(Todos_los_clientes, tam);

    for(unsigned int i=0;i<tam;i++)
    {

        if(Todos_los_clientes[i].estado) mostrar_registro(Todos_los_clientes[i]);
    }

free(Todos_los_clientes);
return true;
}

void ordenar_por_apellido(Clientes *cliente, unsigned int tam)
{
    Clientes aux;
    int pos_menor=0;
    for(unsigned int i=0; i<tam-1;i++)
    {
        pos_menor=i;

        for(unsigned int j=i+1;j<tam;j++)
        {
            if((strcmp(cliente[j].apellido,cliente[pos_menor].apellido))<0)
            {
                pos_menor=j;
            }
        }
        aux=cliente[pos_menor];
        cliente[pos_menor]=cliente[i];
        cliente[i]=aux;
    }
}

void mostrar_registro(Clientes cliente)
{
    cout<<"ID:                  ";
    cout<<cliente.ID<<endl;

    cout<<"Apellido:            ";
    cout<<cliente.apellido<<endl;

    cout<<"Nombre:              ";
    cout<<cliente.nombre<<endl;

    cout<<"Mail:                ";
    cout<<cliente.mail<<endl;

    cout<<"Domicilio:           ";
    cout<<cliente.domicilio<<endl;

    cout<<"Código Postal:       ";
    cout<<cliente.codigo_postal<<endl;

    cout<<"Fecha de Nacimiento: ";
    cout<<cliente.fecha.dia<<"/"<<cliente.fecha.mes<<"/"<<cliente.fecha.anio<<endl;

    cout<<"Estado:              ";
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
cout<<"El cliente no existe o está dado de baja.";
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
            cout<<"No se ha podido guardar la dirección del cliente.";
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
    cout<<"Código Postal: "<<endl;
    cout<<"Fecha de nacimiento: "<<endl;

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
