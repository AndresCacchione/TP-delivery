#ifndef FUNCIONES_PLATOS_H_INCLUDED
#define FUNCIONES_PLATOS_H_INCLUDED

int menu_platos()
{

    int op;
    cls();
    setColor (BLACK);
    cout<<"*-    -    -    -    -    -    -    -    -    -    -    -   *"<<endl<<endl;
    resetColor();
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
    setColor (BLACK);
    cout<<"*-    -    -    -    -    -    -    -    -    -    -    -   *"<<endl<<endl;
    gotoxy(1,30);
    cout<<"*                      ~SISTEMA LARA~                         *"<<endl;
    resetColor();
    gotoxy(1,16);
    cout<<"Ingrese una opción: ";
    gotoxy(21,16);
    setColor (BLACK);
    bool validado = validacion_entero (&op);
    if (!validado)
        op=-1;
    resetColor();
    return op;
}


void seccion_platos()
{
    int op;

    do
    {
        op = menu_platos();
        cls();
        switch(op)
        {
        case 1:
        {
            nuevo_plato();
        }
        break;
        case 2:
        {
            while(modificar_plato())
            {
                if(!(menu_reintentar()))
                    break;
            }
        }
        break;
        case 3:
        {
            listar_plato_por_ID();
        }
        break;
        case 4:
        {
            listar_platos_por_restaurant();
        }
        break;
        case 5:
        {
            listar_todos_los_platos();
        }
        break;
        case 6:
        {
            while(eliminar_plato())
            {
                if(!(menu_reintentar()))
                    break;
            }
        }
        break;

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

int eliminar_plato()
{
    int borra;
    cout<<"Ingrese el ID del plato a eliminar: ";
    if(!(validacion_ID(&borra)))
    {
        cout<<"No se ha eliminado ningún registro."<<endl;
        return 0;
    }

    int resultado = eliminando_plato(borra);
    if(resultado==0)
        cout<<"Plato eliminado con éxito!";
    if(resultado==1)
        cout<<"Error al abrir el archivo, no se ha podido eliminar el plato.";
    if(resultado==2)
        cout<<"El plato ha sido eliminado previamente.";
    if(resultado==3)
        cout<<"El plato no existe, imposible eliminar.";
    return resultado;
}


int eliminando_plato(int borra)
{
    Platos plato;
    FILE *p;

    p = fopen(archivo_platos,"rb+");
    if(p==NULL)
        return 1; // error al abrir el archivo.

    while(fread(&plato,sizeof (Platos),1,p))
    {
        if(plato.ID==borra)
        {
            if(plato.estado)
            {
                plato.estado=false;
                fseek(p,(ftell(p)-sizeof(Platos)),0);
                fwrite(&plato, sizeof (Platos),1,p);
                fclose(p);
                return 0; //plato eliminado con éxito.
            }
            fclose(p);
            return 2; //plato ya eliminado.
        }
    }
    fclose(p);
    return 3; //plato no existe.
}


void listar_todos_los_platos()
{
    Platos plato;
    FILE *p;
    p = fopen(archivo_platos,"rb");
    if(p==NULL)
        cout<<"El archivo no se pudo abrir correctamente.. :( llame al programador :D $$";

    while(fread(&plato,sizeof (Platos),1,p))
    {
        if(plato.estado)
        {
            mostrar_plato(plato);
            cout<<endl<<endl;
        }
    }
    fclose(p);
}


void listar_platos_por_restaurant()
{
    int ID_rest;
    cout<<"Ingrese el ID del restaurante buscado: ";
    bool valida = validacion_ID(&ID_rest);
    if(!valida)
    {
        cout<<"El ID del restaurante no ha sido ingresado correctamente."<<endl;
        return;
    }

    Platos plato;
    int validado = mostrar_platos_por_restaurant(ID_rest, &plato);

    if(validado==0)
        cout<<"Estos son todos los platos del restaurante.";
    if(validado==1)
        cout<<"No existen platos para el restaurante ingresado.";
    if(validado==2)
        cout<<"Error al abrir el archivo.";
}

int mostrar_platos_por_restaurant(int ID_rest,Platos *plato)
{
    int retorno=1;
    FILE *p;
    p= fopen(archivo_platos, "rb");
    if (p == NULL)
    {
        return 2;
    }

    while(fread(plato,sizeof (Platos), 1, p))
    {
        if(plato->ID_restaurante==ID_rest && plato->estado)
        {
            mostrar_plato(*plato);
            cout<<endl<<endl;
            retorno=0;
        }
    }
    fclose(p);

    return retorno;
}


void listar_plato_por_ID()
{
    int ID;
    cout<<"Ingrese el ID de un plato: ";
    bool valida = validacion_ID(&ID);
    if(!valida)
    {
        cout<<"Su plato no ha podido ser listado."<<endl;
        return;
    }
    Platos plato;
    int validado = buscar_plato(ID, &plato);
    if(!validado)
    {
        cls();
        cout<<"El plato buscado es el siguiente:"<<endl<<endl;
        mostrar_plato(plato);
        return;
    }
    if(validado==1)
        cout<<"El plato buscado no existe en la base de datos.";
    if(validado==2)
        cout<<"Error en la lectura del archivo.";
    if(validado==3)
        cout<<"El plato no se encuentra activo.";
}


void mostrar_plato(Platos plato)
{
    cout<<"El ID: "<< plato.ID <<endl;
    cout<<"Nombre: "<< plato.nombre <<endl;
    cout<<"Costo de preparación: $ "<< plato.costo_prep <<endl;
    cout<<"Valor de venta: $ "<< plato.valor_venta <<endl;
    cout<<"Tiempo de preparación en minutos: "<< plato.tiempo_prep <<endl;
    cout<<"ID del restaurante: "<< plato.ID_restaurante <<endl;
    cout<<"Comisión del restaurante: "<< plato.comision_restaurante <<"%" <<endl;
    cout<<"ID Categaría: "<< plato.ID_categoria <<endl;
    cout<<"Estado: "<<plato.estado<<endl; ///  Solo para nosotros, luego borrar esta linea  ///
}


int buscar_plato(int ID,Platos *plato)
{
    FILE *p;
    p= fopen(archivo_platos, "rb");

    if (p == NULL)
    {
        return 2;
    }

    while(fread(plato,sizeof (Platos), 1, p))
    {
        if(plato->ID==ID)
        {
            if(plato->estado)
            {
                fclose(p);
                return 0;
            }
            fclose(p);
            return 3;
        }
    }
    fclose(p);

    return 1;
}


int modificar_plato()
{
    int ID;
    cout<<"Ingrese un ID de Plato a modificar: ";
    if(!(validacion_ID(&ID)))
    {
        cout<<"El plato no ha sido modificado"<<endl;
        return 0;
    }
    int resultado = modifica_plato_por_ID(ID);
    mostrar_resultado(resultado);
    if(resultado==-4)
        resultado=0;
    return resultado;
}


void mostrar_resultado(int resultado)
{
    switch(resultado)
    {
    case 0:
    {
        cout<<"Los valores fueron modificados exitosamente! :D Very good muy bien 10!"<<endl;
        anykey();
    }
    break;
    case -1:
    {
        cout<<"Tipo de dato cargado no validado."<<endl;
        anykey();
    }
    break;
    case -2:
    {
        cout<<"El ID del plato no fue cargado o no existe."<<endl;
        anykey();
    }
    break;
    case -3:
    {
        cout<<"Error al guardar el cambio."<<endl;
        anykey();
    }
    break;
    case -4:
    {
        cout<<"Error al abrir el archivo."<<endl;
        anykey();
    }
    break;
    case -5:
    {
        cout<<"El plato a modificar se encuentra inactivo"<<endl;
        anykey();
    }
    break;
    default:
    {
        cout<<"El valor de venta no puede ser menor al costo de preparación de $ "<<resultado<<endl;
        anykey();
    }
    break;
    }
}

int modifica_plato_por_ID(int ID)
{
    Platos plato;
    FILE *p;
    p=fopen(archivo_platos,"rb+");
    if(p==NULL)
    {
        return -4;
    }
    while(fread(&plato,sizeof (Platos),1,p))
    {
        if(plato.ID==ID)
        {
            if(plato.estado)
                break;
            return -5;
        }
    }
    if(feof(p))
        return -2;
    fseek(p,ftell(p)-sizeof (Platos),0);

    cout<<"Ingrese el nuevo valor de venta: ";

    if(!validacion_flotante(&(plato.valor_venta)))
        return -1;
    if(plato.valor_venta < plato.costo_prep)
        return plato.costo_prep;

    cout<<"Ingrese el nuevo tiempo de preparación en minutos: ";

    bool validado = validacion_entero(&(plato.tiempo_prep));
    if(!validado || (plato.tiempo_prep <= 0))
        return -1;

    if(!(fwrite(&plato,sizeof (Platos),1,p)))
        return -3;

    fclose(p);
    return 0;
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
        cout<<"\nEl plato ha sido cargado exitosamente!"<<endl;
    }
    else
    {
        cls();
        cout<<"Error de archivo. El plato no se ha podido cargar exitosamente."<<endl;
    }
}


bool cargar_registro(Platos *plato)
{
    cout<<"1.Ingrese ID: ";
    gotoxy(40, 1);
    bool validado = validacion_entero(&(plato->ID));
    if(!validado || (plato->ID <= 0))
        return false;

    validado = ID_Plato_unico(plato->ID);
    if(!validado)
    {
        cout<<"ID de plato duplicado.";
        anykey();
        return false;
    }

    cout<<"2.Ingrese nombre del plato: ";
    cin.ignore();
    gotoxy(40,2);
    cin.getline(plato->nombre, 50);
    validado = validacion_cadena(plato->nombre);
    if(!validado)
        return false;

    cout<<"3.Ingrese costo de preparacion: ";
    gotoxy(38,3);
    cout<<"$";
    gotoxy(40,3);
    validado = validacion_flotante(&(plato->costo_prep));
    if(!validado || (plato->costo_prep <= 0))
        return false;

    cout<<"4.Ingrese valor de venta: ";
    gotoxy(38,4);
    cout<<"$";
    gotoxy(40,4);
    validado = validacion_flotante(&(plato->valor_venta));
    if(!validado || (plato->valor_venta < plato->costo_prep))
        return false;

    cout<<"5.Ingrese tiempo de preparacion(min):";
    gotoxy(40,5);
    validado = validacion_entero(&(plato->tiempo_prep));
    if(!validado || (plato->tiempo_prep <= 0))
        return false;

    cout<<"6.Ingrese ID del restaurante: ";
    gotoxy(40,6);
    validado = validacion_entero(&(plato->ID_restaurante));
    if(!validado || (plato->ID_restaurante <= 0))
        return false;

    cout<<"7.Ingrese comision de restaurante(%): ";
    gotoxy(40,7);
    validado = validacion_entero(&(plato->comision_restaurante));
    if(!validado || (plato->comision_restaurante<0) || (plato->comision_restaurante>100))
        return false;

    cout<<"8.Ingrese ID de Categoria: ";
    gotoxy(40,8);
    validado = validacion_entero(&(plato->ID_categoria));
    if(!validado || (plato->ID_categoria <= 0))
        return false;

    plato->estado=true;

    return true;
}


bool ID_Plato_unico(int ID)
{
    Platos plato;
    FILE *p;

    p=fopen(archivo_platos,"ab+");
    if(p==NULL)
        return false;

    while (fread(&plato, sizeof (Platos), 1, p))
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

bool grabar_registro(Platos plato)
{
    FILE *p;
    p= fopen(archivo_platos, "ab");

    if (p == NULL)
    {
        return false;
    }

    bool grabado = fwrite(&plato, sizeof (Platos), 1, p);

    fclose(p);
    return grabado;
}

int index_plato(int ID)
{
    int pos=0;
    Platos plato;
    FILE *p;
    p=fopen(archivo_platos, "rb");
    if (p==NULL)
        return -2;

    while (fread(&plato, sizeof (Platos),1,p))
    {
        if (ID == plato.ID)
            {
               if(plato.estado)
                return pos;
                else{return -3;}
            }
        pos++;
    }
fclose(p);
return -1;
}

#endif // FUNCIONES_PLATOS_H_INCLUDED
