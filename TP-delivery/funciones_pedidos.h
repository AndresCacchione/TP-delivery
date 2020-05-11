#ifndef FUNCIONES_PEDIDOS_H_INCLUDED
#define FUNCIONES_PEDIDOS_H_INCLUDED

void seccion_pedidos()
{
    int op;

    do
    {
        op = menu_pedidos();
        cls();
        switch(op)
        {
        case 1:
        {
            while(!(nuevo_pedido()))
            {
                if(!(menu_reintentar()))
                    break;
            }
        }
        break;
        case 2:
        {
            while(!(modificar_pedido()))
            {
                if(!(menu_reintentar()))break;
            }
        } break;
        case 3:
        {
//                    while(listar_pedido_por_ID())
//                    {
//                        if(!(menu_reintentar()))break;
//                    }
        } break;
        case 4:
        {
            ///listar_todos_pedidos();
        } break;

        case 0:
        {} break;
        default:
        {
            if(!(menu_reintentar()))
                op=0;
        }
        break;
        }
        anykey();

    }
    while(op!=0);
}

bool modificar_pedido()
{
    int ID;
    cout<<"Ingrese el ID de pedido a modificar: ";
    if(!(validacion_ID(&ID)))return false;

    int pos = buscar_pedido(ID);
    if(pos<0)
    {
        if(pos==-1)
        {
            cout<<"El ID buscado no existe o está dado de baja."<<endl;
        }
        return false;
    }

    if(!(modificar_estado_pedido(pos))) return false;

    setColor(BLACK);
    cout << "\n\nEstado del pedido modificado exitosamente!! :D"<<endl;
    resetColor();
return true;
}

bool modificar_estado_pedido(int pos)
{
    Pedidos pedido;
    FILE *p;
    p=fopen(ARCHIVO_PEDIDOS,"rb+");
    if(p==NULL)
    {
        cout<<"Error en apertura de archivo."<<endl;
        return false;
    }

    fseek(p,pos*sizeof(Pedidos),0);
    fread(&pedido,sizeof(Pedidos),1,p);

    cout<<"\nEstados de los pedidos: 1 - EN CURSO."<<endl;
    cout<<"                        2 - COMPLETADO."<<endl;
    cout<<"                        3 - CANCELADO."<<endl<<endl;

    cout<<"Estado del pedido actual: ";
    mostrar_estado(pedido.estado);

    cout<<"\nIngrese el nuevo estado del pedido: ";
    if(!(validacion_entero(&(pedido.estado))))
    {
        cout<<"El estado cargado no es válido. Debe ser 1 (En curso), 2 (completado), o 3 (cancelado)."<<endl;
        return false;
    }

    fseek(p,pos*sizeof(Pedidos),0);
    fwrite(&pedido,sizeof(Pedidos),1,p);
    fclose(p);

return true;
}


int buscar_pedido(int ID)
{
    Pedidos pedido;
    FILE *p;
    p=fopen(ARCHIVO_PEDIDOS, "rb");
    if(p==NULL)
        {
            cout<<"Error en apertura de archivo."<<endl;
            return -2;
        }
    int pos=0;

    while(fread(&pedido,sizeof(Pedidos),1,p))
    {
        if(pedido.ID_pedido == ID) return pos;
        pos++;
    }
    fclose(p);
return -1;
}


bool guardar_pedido(Pedidos pedido)
{
    FILE *p;
    p=fopen(ARCHIVO_PEDIDOS,"ab");
    if (p==NULL)
    {
        cout<<"No se pudo guardar el archivo.";
        return false;
    }

    fwrite(&pedido, sizeof (Pedidos),1,p);

    fclose(p);
    return true;
}

void mostrar_pedido(Pedidos *pedido, int cant)
{
    cls();
    if (pedido->ID_pedido !=0)
    {
        cout<<"ID PEDIDO: ";
        gotoxy(30,1+9*cant);
        cout<<pedido->ID_pedido<<endl;
    }
    else
    {
        return;
    }
    if (pedido->ID_cliente!=0)
    {
        cout<<"ID CLIENTE: ";
        gotoxy(30,2+9*cant);
        cout<<pedido->ID_cliente<<endl;
    }
    else
    {
        return;
    }
    if(pedido->ID_plato!=0)
    {
        cout<<"ID PLATO: ";
        gotoxy(30,3+9*cant);
        cout<<pedido->ID_plato<<endl;
    }
    else
    {
        return;
    }
    if(pedido->cantidad!=0)
    {
        cout<<"CANTIDAD: ";
        gotoxy(30,4+9*cant);
        cout<<pedido->cantidad<<endl;
    }
    else
    {
        return;
    }
    if(pedido->precio_unitario!=0)
    {
        cout<<"PRECIO UNITARIO: ";
        gotoxy(30,5+9*cant);
        cout<<pedido->precio_unitario<<endl;
    }
    else
    {
        return;
    }
    if(pedido->fecha.dia!=0)
    {
        cout<<"FECHA DEL PEDIDO: ";
        gotoxy(30,6+9*cant);
        cout<<pedido->fecha.dia << "/" << pedido->fecha.mes << "/" << pedido->fecha.anio<<endl;
    }
    else
    {
        return;
    }
    if(pedido->valoracion!=0)
    {
        cout<<"VALORACIÓN: ";
        gotoxy(30,7+9*cant);
        cout<<pedido->valoracion<<endl;
    }
    else
    {
        return;
    }
    if(pedido->estado!=0)
    {
        cout<<"ESTADO: ";
        gotoxy(30,8+9*cant);
        mostrar_estado(pedido->estado);
    }
}

void mostrar_estado(int estado)
{
    if(estado==1) cout<<"PEDIDO EN CURSO."<<endl;
    else if(estado==2) cout<<"PEDIDO COMPLETADO."<<endl;
    else
    {
        cout<<"PEDIDO CANCELADO."<<endl;
    }
}


bool cargar_pedido(Pedidos *pedido)
{
    pedido->ID_pedido = 1+tamanio_archivo(ARCHIVO_PEDIDOS, sizeof(Pedidos));
    cout<<"ID PEDIDO: ";
    gotoxy(30,1);
    cout<<pedido->ID_pedido<<endl;

    cout<<"ID CLIENTE: ";
    gotoxy(30,2);
    if (!(validacion_ID(&(pedido->ID_cliente))))
    {
        cout<<"Error en el ingreso. El ID de Cliente debe ser un numero entero positivo."<<endl;
        return false;
    }
    if (buscar_cliente_por_ID(pedido->ID_cliente)<0)
        return false;

    cls();
    gotoxy(1,3);
    listar_ID_nombre_platos();

    gotoxy(1,1);
    cout<<"SELECCIONE UN ID DE PLATO: ";
    gotoxy(30,1);
    if (!(validacion_ID(&(pedido->ID_plato))))
    {
        cout<<"Error en el ingreso. El ID de Plato debe ser un numero entero positivo."<<endl;
        return false;
    }
    int pos_plato= index_plato(pedido->ID_plato);
    if (pos_plato<0)
    {
        if (pos_plato==-1)
            cout<<"El ID del plato inexistente."<<endl;
        if (pos_plato==-3)
            cout<<"El ID del plato esta dado de baja."<<endl;
        return false;
    }

    mostrar_pedido(pedido,0);

    gotoxy(1,4);
    cout<<"CANTIDAD: ";
    gotoxy(30,4);
    if (!(validacion_ID(&(pedido->cantidad))))
        return false;

    pedido->precio_unitario=buscar_precio_plato(pos_plato);
    if(pedido->precio_unitario<0)
        return false;

    gotoxy(1,5);
    cout<<"DÍA DEL PEDIDO: ";
    gotoxy(30,5);
    if(!(validacion_ID(&(pedido->fecha.dia))))
        return false;
    if(pedido->fecha.dia>31)
        return false;

    gotoxy(1,6);
    cout<<"MES: ";
    gotoxy(30,6);
    if(!(validacion_ID(&(pedido->fecha.mes))))
        return false;
    if(pedido->fecha.mes>12)
        return false;

    gotoxy(1,7);
    cout<<"AÑO: ";
    gotoxy(30,7);
    if(!(validacion_ID(&(pedido->fecha.anio))))
        return false;
    if(pedido->fecha.anio<1900)
        return false;
    if(!(validacion_fecha(&(pedido->fecha))))
        return false;

    mostrar_pedido(pedido,0);

    gotoxy(1,7);
    cout<<"VALORACION: ";
    gotoxy(30,7);
    if (!(validacion_flotante(&(pedido->valoracion))))
        return false;
    if (pedido->valoracion <0 || pedido->valoracion >10)
        return false;

    pedido->estado=1;

    return true;
}

float buscar_precio_plato (int pos)
{
    Platos plato;
    FILE *p;
    p=fopen(archivo_platos,"rb");

    if (p==NULL)
        return -2;

    fseek(p,pos*sizeof (Platos),0);
    fread(&plato,sizeof(Platos),1,p);
    fclose(p);

    return plato.valor_venta;
}

void listar_ID_nombre_platos()
{
    Platos plato;
    FILE *p;
    p=fopen(archivo_platos,"rb");
    if(p==NULL)
        return;

    cout<<"Lista de platos disponibles: "<<endl<<endl;
    while(fread(&plato,sizeof(Platos),1,p))
    {
        if(plato.estado)
        {
            cout<<"ID plato: " << plato.ID<<endl;
            cout<<"Nombre plato: "<<plato.nombre<<endl<<endl;
        }
    }
    cout<<"*-----------------------------------*"<<endl;
    fclose(p);
}


bool nuevo_pedido()
{
    Pedidos pedido={0};
    if (!(cargar_pedido(&pedido)))
        return false;
    if (!(guardar_pedido(pedido)))
        return false;

    setColor(BLACK);
    cout<<"\n\nPedido cargado exitosamente !!"<<endl;
    resetColor();

    return true;
}

int menu_pedidos()
{
    int opcion;
    cls();
    setColor (BLACK);
    cout<<"*-    -    -    -    -    -    -    -    -    -    -    -   *"<<endl<<endl;
    resetColor();
    cout<<"*--------------      MENÚ PEDIDOS            ---------------*"<<endl;
    cout<<"*-----------------------------------------------------------*"<<endl;
    cout<<"*-------------- 1) NUEVO PEDIDO              ---------------*"<<endl;
    cout<<"*-------------- 2) MODIFICAR PEDIDO          ---------------*"<<endl;
    cout<<"*-------------- 3) LISTAR PEDIDO POR ID      ---------------*"<<endl;
    cout<<"*-------------- 4) LISTAR TODOS LOS PEDIDOS  ---------------*"<<endl;
    cout<<"*-----------------------------------------------------------*"<<endl;
    cout<<"*-------------- 0) VOLVER AL MENÚ PRINCIPAL  ---------------*"<<endl<<endl;
    setColor (BLACK);
    cout<<"*-    -    -    -    -    -    -    -    -    -    -    -   *"<<endl<<endl;

    gotoxy(1,29);
    cout<<"*                      ~SISTEMA LARA~                         *"<<endl;
    resetColor();
    gotoxy(1,14);
    cout<<"Ingrese una opción: ";
    gotoxy(21,14);
    setColor (BLACK);
    bool validado = validacion_entero (&opcion);
    if (!validado)
        opcion=-1;
    resetColor();
    return opcion;
}


#endif // FUNCIONES_PEDIDOS_H_INCLUDED
