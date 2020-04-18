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
                    nuevo_plato();
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


void nuevo_plato()
{
    struct Platos plato;
    bool validado = cargar_registro(&plato);

    while(!validado)
    {
         bool reintentar = menu_reintentar();
         if(!reintentar)
         {
             cout<<"El plato no se ha podido cargar exitosamente."<<endl;
             return;
         }
         validado = cargar_registro(&plato);
    }

    bool grabado = grabar_registro(plato);

    if(grabado)
    {
        cout<<"El plato ha sido cargado exitosamente!"<<endl;
    }
    else
    {
        cout<<"Error de archivo. El plato no se ha podido cargar exitosamente."<<endl;
    }
}


bool cargar_registro(Platos *plato)
{
    cout<<"Ingrese un ID: ";
    bool validado_ID = validacion_entero(&(plato->ID));
    if(!validado_ID || plato->ID <= 0)return false;

    validado_ID = ID_unico(plato->ID);
    if(!validado_ID) return false;

    cout<<" Ingrese un nombre: ";
    cin.ignore ();
    cin.getline (plato->nombre, 50);

    cout<<"Ingrese un costo de preparacion: ";
    cin>>plato->costo_prep;

    cout<<"Ingrese un valor de venta: ";
    cin>>plato->valor_venta;

    cout<< "Ingrese un tiempo de preparacion: ";
    cin>>plato->tiempo_prep;

    cout<<"Ingrese un ID del restaurante: ";
    cin>>plato->ID_restaurante;

    cout<<"Ingrese una comision de restaurante: ";
    cin>>plato->comision_restaurante;

    cout<<"Ingrese ID de Categoria: ";
    cin>>plato->ID_categoria;

    plato->estado=true;

return true;
}


bool ID_unico(int ID)
{
    Platos plato;
    FILE *p;

    p=fopen(archivo_platos,"ab+");
    fseek(p,0,0);
    if(p==NULL) return false;

    while (fread(&ID, sizeof Platos, 1, p))
    {
        if(ID == plato.ID)
        {
            fclose(p);
            return false;
        }
    }
fclose(p);
return true;
}






#endif // FUNCIONES_PLATOS_H_INCLUDED
