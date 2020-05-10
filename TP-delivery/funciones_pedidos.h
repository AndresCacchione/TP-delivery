#ifndef FUNCIONES_PEDIDOS_H_INCLUDED
#define FUNCIONES_PEDIDOS_H_INCLUDED

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
mostrar_pedido (Pedidos *pedido)
{
    if (pedido.ID !=0)cout<<"ID PEDIDO: "<<pedido->ID_pedido<<endl;
    {
        else return;
    }
     if (pedido.ID_cliente!=0)cout<<"ID PEDIDO: "<<pedido
    {
        else return;
    }

}




bool cargar_pedido(Pedidos *pedido)
{
    pedido->ID_pedido = 1+tamanio_archivo(ARCHIVO_PEDIDOS, sizeof(Pedidos));
    cout<<"ID PEDIDO: "<<pedido->ID_pedido<<endl;

    cout<<"ID CLIENTE: ";
    if (!(validacion_ID(&(pedido->ID_cliente))))
    {
        cout<<"Error en el ingreso. El ID de Cliente debe ser un numero entero positivo."<<endl;
        return false;
    }
    if (buscar_cliente_por_ID(pedido->ID_cliente)<0)return false;

    cls();
    listar_ID_nombre_platos();
    cout<<"SELECCIONE UN ID DE PLATO: ";
    if (!(validacion_ID(&(pedido->ID_plato))))
    {
        cout<<"Error en el ingreso. El ID de Plato debe ser un numero entero positivo."<<endl;
        return false;
    }
    int pos_plato= index_plato(pedido->ID_plato);
    if (pos_plato<0)
    {
        if (pos_plato==-1) cout<<"El ID del plato inexistente."<<endl;
        if (pos_plato==-3) cout<<"El ID del plato esta dado de baja."<<endl;
        return false;
    }
    cls();
    cout<<"CANTIDAD: ";
    if (!(validacion_ID(&(pedido->cantidad))))return false;

    pedido->precio_unitario=buscar_precio_plato(pos_plato);
    if(pedido->precio_unitario<0) return false;

    cls();
    cout<<"DÍA DEL PEDIDO: ";
    if(!(validacion_ID(&(pedido->fecha.dia))))return false;
    if(pedido->fecha.dia>31) return false;
    cout<<"MES: ";

    if(!(validacion_ID(&(pedido->fecha.mes))))return false;
    if(pedido->fecha.mes>12) return false;
    cout<<"AÑO: ";

    if(!(validacion_ID(&(pedido->fecha.anio))))return false;
    if(pedido->fecha.anio<1900) return false;
    if(!(validacion_fecha(&(pedido->fecha)))) return false;

    cout<<"VALORACION: ";
    if (!(validacion_flotante(&(pedido->valoracion))))return false;
    if (pedido->valoracion <0 || pedido->valoracion >10) return false;

    pedido->estado=1;

    return true;
}

float buscar_precio_plato (int pos)
{
    Platos plato;
    FILE *p;
    p=fopen(archivo_platos,"rb");

    if (p==NULL)return -2;

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
    if(p==NULL)return;
    cls();
    while(fread(&plato,sizeof(Platos),1,p))
    {
        if(plato.estado)
        {
            cout<<"ID plato: " << plato.ID<<endl;
            cout<<"Nombre plato: "<<plato.nombre<<endl;
            cout<<"*-----------------------------------*"<<endl;
        }
    }
    fclose(p);
}


bool nuevo_pedido()
{
    Pedidos pedido;
    if (!(cargar_pedido(&pedido)))return false;
    if (!(guardar_pedido(pedido)))return false;

    cout<<"Pedido cargado exitosamente."<<endl;

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
    if (!validado) opcion=-1;
    resetColor();
return opcion;
}

void seccion_pedidos()
{
int op;

    do{
        op = menu_pedidos();
        cls();
        switch(op)
        {
            case 1:
                {
                    while(!(nuevo_pedido()))
            {
                if(!(menu_reintentar())) break;
            }
                }break;
            case 2:
                {
//                    while(modificar_pedido())
//                    {
//                        if(!(menu_reintentar()))break;
//                    }
                }break;
            case 3:
                {
//                    while(listar_pedido_por_ID())
//                    {
//                        if(!(menu_reintentar()))break;
//                    }
                }break;
            case 4:
                {
                    ///listar_todos_pedidos();
                }break;

            case 0:{}break;
            default:
                {
                    if(!(menu_reintentar()))op=0;
                }break;
        }
        anykey();

    }while(op!=0);
}
#endif // FUNCIONES_PEDIDOS_H_INCLUDED
