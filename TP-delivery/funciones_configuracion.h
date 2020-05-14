#ifndef FUNCIONES_CONFIGURACION_H_INCLUDED
#define FUNCIONES_CONFIGURACION_H_INCLUDED

void seccion_configuracion()
{
    int op;

    do
    {
        op = menu_configuracion();
        cls();
        switch(op)
        {
        case 1:
        {
            while(!(crear_backup()))
            {
                if(!(menu_reintentar())) break;
            }
        }
        break;
        case 2:
        {
            while(!(restaurar_backup()))
            {
                if(!(menu_reintentar())) break;
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

bool restaurar_backup()
{
    setBackgroundColor(WHITE);
    setColor (1);
    cls();
    cout<<"¿Realmente desea restaurar los archivos del backup?:"<<endl<<endl;
    cout<<"*-- 1 --> SI  --*"<<endl;
    cout<<"*-- 0 --> NO  --*"<<endl;
    bool confirmacion;

    cout<<"\nIngrese su elección: ";
    if(!(validacion_booleano(&confirmacion))) return false;
    resetColor ();
    if(!confirmacion)
    {
        cout<<"\nRestauracion no realizada."<<endl;
        return true;
    }

    if((!(restaurar_platos())) || (!(restaurar_clientes())) || (!(restaurar_pedidos())))
    {
        cout<<"Error: la restauracion de archivos no se ha podido realizar."<<endl;
        return true;
    }

    setColor(BLACK);
    cout<<"\nRestauracion realizada con éxito!!"<<endl;
    resetColor();
return true;
}

bool restaurar_pedidos()
{
    int tam= tamanio_archivo(ARCHIVO_PEDIDOS_BACKUP, sizeof (Pedidos));
    if (tam==-1)
    {
        cout<<"No se pudo abrir el Archivo Pedidos.bkp."<<endl;
        return false;
    }

    Pedidos *todos_los_pedidos;
    todos_los_pedidos= (Pedidos *)malloc(sizeof (Pedidos)*tam);

    if (todos_los_pedidos==NULL)
    {
        cout<<"Memoria insuficiente."<<endl;
        return false;
    }
    FILE *p;
    p=fopen(ARCHIVO_PEDIDOS_BACKUP,"rb");
    if (p==NULL)return false;

    if (!((fread(todos_los_pedidos, sizeof (Pedidos),tam,p))==(unsigned int)tam))
    {
        fclose(p);
        return false;
    }
    fclose(p);

    FILE *a;
    a=fopen(ARCHIVO_PEDIDOS,"wb");
    if (a==NULL)return false;

    if (!((fwrite(todos_los_pedidos, sizeof (Pedidos), tam,a))==(unsigned int)tam))
    {
        fclose(a);
        cout<<"Backup imcompleto."<<endl;
        return false;
    }

fclose(a);
free(todos_los_pedidos);
return true;
}

bool restaurar_clientes()
{
    int tam= tamanio_archivo(ARCHIVO_CLIENTES_BACKUP, sizeof (Clientes));
    if (tam==-1)
    {
        cout<<"No se pudo abrir el Archivo Clientes.bkp."<<endl;
        return false;
    }

    Clientes *todos_los_clientes;
    todos_los_clientes= (Clientes *)malloc(sizeof (Clientes)*tam);

    if (todos_los_clientes==NULL)
    {
        cout<<"Memoria insuficiente."<<endl;
        return false;
    }
    FILE *p;
    p=fopen(ARCHIVO_CLIENTES_BACKUP,"rb");
    if (p==NULL)return false;

    if (!(fread(todos_los_clientes, sizeof (Clientes),tam,p)))
    {
        fclose(p);
        return false;
    }
    fclose(p);

    FILE *a;
    a=fopen(ARCHIVO_CLIENTES,"wb");
    if (a==NULL)return false;

    if (!((fwrite(todos_los_clientes, sizeof (Clientes), tam,a))==(unsigned int)tam))
    {
        fclose(a);
        cout<<"Backup imcompleto."<<endl;
        return false;
    }

fclose(a);
free(todos_los_clientes);
return true;
}


bool restaurar_platos()
{
    int tam= tamanio_archivo(ARCHIVO_PLATOS_BACKUP, sizeof (Platos));
    if (tam==-1)
    {
        cout<<"No se pudo abrir el Archivo Platos.bkp."<<endl;
        return false;
    }

    Platos *todos_los_platos;
    todos_los_platos= (Platos *)malloc(sizeof (Platos)*tam);

    if (todos_los_platos==NULL)
    {
        cout<<"Memoria insuficiente."<<endl;
        return false;
    }
    FILE *p;
    p=fopen(ARCHIVO_PLATOS_BACKUP,"rb");
    if (p==NULL)return false;

    if (!(fread(todos_los_platos, sizeof (Platos),tam,p)))
    {
        fclose(p);
        return false;
    }
    fclose(p);

    FILE *a;
    a=fopen(archivo_platos,"wb");
    if (a==NULL)return false;

    if (!((fwrite(todos_los_platos, sizeof (Platos), tam,a))==(unsigned int)tam))
    {
        fclose(a);
        cout<<"Backup imcompleto."<<endl;
        return false;
    }

fclose(a);
free(todos_los_platos);
return true;
}


bool crear_backup()
{
    setBackgroundColor(WHITE);
    setColor (1);
    cls();
    cout<<"¿Realmente desea realizar un backup de los archivos?:"<<endl<<endl;
    cout<<"*-- 1 --> SI  --*"<<endl;
    cout<<"*-- 0 --> NO  --*"<<endl;
    bool confirmacion;

    cout<<"\nIngrese su elección: ";
    if(!(validacion_booleano(&confirmacion))) return false;
    resetColor();
    if(!confirmacion)
    {
        cout<<"\nBackup no realizado."<<endl;
        return true;
    }

    if((!(backup_platos())) || (!(backup_clientes())) || (!(backup_pedidos())))
    {
        cout<<"Error: el Backup no se ha podido realizar."<<endl;
        return true;
    }

    setColor(BLACK);
    cout<<"\nBackup creado con éxito!!"<<endl;
    resetColor();
return true;
}

bool backup_pedidos()
{
    int tam = tamanio_archivo(ARCHIVO_PEDIDOS, sizeof(Pedidos));
    Pedidos *todos_los_pedidos;
    todos_los_pedidos=(Pedidos *) malloc(sizeof(Pedidos)*tam);
    if(todos_los_pedidos==NULL)
    {
        cout<<"Error: imposible asignar memoria para realizar el backup."<<endl;
        return false;
    }

    FILE *p;
    p=fopen(ARCHIVO_PEDIDOS,"rb");
    if(p==NULL)
    {
        cout<<"Error: imposible leer el archivo de Pedidos.dat."<<endl;
        return false;
    }
    if(!(fread(todos_los_pedidos,sizeof(Pedidos),tam,p)))
    {
        fclose(p);
        return false;
    }
    fclose(p);

    FILE *P;
    P=fopen(ARCHIVO_PEDIDOS_BACKUP, "wb");
    if(P==NULL)
    {
        cout<<"Error: no se puede crear el archivo de backup."<<endl;
        return false;
    }

    if(!(fwrite(todos_los_pedidos,sizeof(Pedidos),tam,P)))
    {
        fclose(P);
        return false;
    }
    fclose(P);
    free(todos_los_pedidos);
return true;
}

bool backup_clientes()
{
    int tam = tamanio_archivo(ARCHIVO_CLIENTES, sizeof(Clientes));
    Clientes *todos_los_clientes;
    todos_los_clientes=(Clientes *) malloc(sizeof(Clientes)*tam);
    if(todos_los_clientes==NULL)
    {
        cout<<"Error: imposible asignar memoria para realizar el backup."<<endl;
        return false;
    }

    FILE *p;
    p=fopen(ARCHIVO_CLIENTES,"rb");
    if(p==NULL)
    {
        cout<<"Error: imposible leer el archivo de Clientes.dat."<<endl;
        return false;
    }
    if(!(fread(todos_los_clientes,sizeof(Clientes),tam,p)))
    {
        fclose(p);
        return false;
    }
    fclose(p);

    FILE *P;
    P=fopen(ARCHIVO_CLIENTES_BACKUP, "wb");
    if(P==NULL)
    {
        cout<<"Error: no se puede crear el archivo de backup."<<endl;
        return false;
    }

    if(!(fwrite(todos_los_clientes,sizeof(Clientes),tam,P)))
    {
        fclose(P);
        return false;
    }
    fclose(P);
    free(todos_los_clientes);
return true;
}


bool backup_platos()
{
    int tam = tamanio_archivo(archivo_platos, sizeof(Platos));
    Platos *todos_los_platos;
    todos_los_platos=(Platos *) malloc(sizeof(Platos)*tam);
    if(todos_los_platos==NULL)
    {
        cout<<"Error: imposible asignar memoria para realizar el backup."<<endl;
        return false;
    }

    FILE *p;
    p=fopen(archivo_platos,"rb");
    if(p==NULL)
    {
        cout<<"Error: imposible leer el archivo de Platos.dat."<<endl;
        return false;
    }
    if(!(fread(todos_los_platos,sizeof(Platos),tam,p)))
    {
        fclose(p);
        return false;
    }
    fclose(p);

    FILE *P;
    P=fopen(ARCHIVO_PLATOS_BACKUP, "wb");
    if(P==NULL)
    {
        cout<<"Error: no se puede crear el archivo de backup."<<endl;
        return false;
    }

    if(!(fwrite(todos_los_platos,sizeof(Platos),tam,P)))
    {
        fclose(P);
        return false;
    }
    fclose(P);
    free(todos_los_platos);
return true;
}


int menu_configuracion()
{
    int opcion;
    cls();
    setColor (BLACK);
    cout<<"*-    -    -    -    -    -    -    -    -    -    -    -   *"<<endl<<endl;
    resetColor();
    cout<<"*--------------       MENÚ CONFIGURACIÓN         ---------------*"<<endl;
    cout<<"*---------------------------------------------------------------*"<<endl;
    cout<<"*--------------  1) REALIZAR COPIA DE SEGURIDAD  ---------------*"<<endl;
    cout<<"*--------------  2) RESTAURAR COPIA DE SEGURIDAD ---------------*"<<endl;
    cout<<"*---------------------------------------------------------------*"<<endl;
    cout<<"*--------------  0) VOLVER AL MENÚ PRINCIPAL     ---------------*"<<endl<<endl;
    setColor (BLACK);
    cout<<"*-    -    -    -    -    -    -    -    -    -    -    -    -  *"<<endl<<endl;

    gotoxy(1,30);
    cout<<"*                       ~SISTEMA LARA~                          *"<<endl;
    resetColor();
    gotoxy(1,13);
    cout<<"Ingrese una opción: ";
    gotoxy(21,13);
    setColor (BLACK);
    bool validado = validacion_entero (&opcion);
    if (!validado) opcion=-1;
    resetColor();
return opcion;
}


#endif // FUNCIONES_CONFIGURACION_H_INCLUDED
