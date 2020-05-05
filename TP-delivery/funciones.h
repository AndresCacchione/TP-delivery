#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED


bool validacion_ID(int *ID)
{
    while (!(validacion_entero(ID)) || (*ID <= 0))
    {
        bool reintentar= menu_reintentar();
        if (!reintentar)
            {
                 Sleep(1000);
                 return false;
            }
        cls();
        cout<<"Reingrese el ID: ";
    }
return true;
}


int menu_principal()
{

    cls();
    int op;
    system ("color 8E");
    saveDefaultColor();
    cout<<endl;
    cout<<"                     BIENVENIDO A LARA                         \n"<<endl;
    setColor (BLACK);
    cout<<"*-    -    -    -    -    -    -    -    -    -    -    -     *"<<endl<<endl;
    resetColor();
    cout<<"*-----------------      MENÚ PRINCIPAL       -----------------*"<<endl;
    cout<<"*-------------------------------------------------------------*"<<endl;
    cout<<"*-----------------  1) PLATOS                -----------------*"<<endl;
    cout<<"*-----------------  2) CLIENTES              -----------------*"<<endl;
    cout<<"*-----------------  3) PEDIDOS               -----------------*"<<endl;
    cout<<"*-----------------  4) REPORTES              -----------------*"<<endl;
    cout<<"*-----------------  5) CONFIGURACIÓN         -----------------*"<<endl;
    cout<<"*-----------------  ---------------------    -----------------*"<<endl;
    cout<<"*-----------------  0) SALIR DEL PROGRAMA    -----------------*"<<endl<<endl;
    setColor(BLACK);
    cout<<"*-    -    -    -    -    -    -    -    -    -    -    -     *"<<endl<<endl;
    resetColor();

    cout<<"\nSeleccione una opción del menú: ";
    gotoxy(1,30);
    setColor (BLACK);
    cout<<"*                      ~SISTEMA LARA~                         *"<<endl;
    gotoxy(33,19);
    bool validado = validacion_entero(&op);
    if(!validado) op=-1;
    cls();
return op;
}

bool menu_reintentar()
{
    cls();
    cin.clear();
    cin.ignore(1000,'\n');
    bool reintentar;

    setColor (RED);
    cout<<"Opción ingresada no válida.\n"<<endl;

    resetColor();
    cout<<"¿Desea reintentar?"<<endl<<endl;

    cout<<"*-- 1 - SI --*"<<endl;
    cout<<"*-- 0 - NO --*"<<endl;

    cout<<"\nIngrese una opción: ";

    while(!(cin>>reintentar))
    {
         cin.clear();
         cin.ignore(1000,'\n');
         cls();

         setColor (RED);
         cout<<"Opción no válida.\n"<<endl;

         resetColor();
         cout<<"¿Desea reintentar?"<<endl<<endl;

         cout<<"*-- 1 - SI --*"<<endl;
         cout<<"*-- 0 - NO --*"<<endl;

         cout<<"\nIngrese otra opción: ";
    }
    cls();
return reintentar;
}

bool validacion_entero(int *entero)
{
    bool validado;
    if(cin>>*entero)
        {
            validado=true;
        }
    else
        {
            validado=false;
        }
return validado;
}

bool validacion_cadena(char *cad)
{
    bool valida=false;
    for(unsigned int i=0;i<strlen(cad);i++)
    {
        if(cad[i]!='\0'&& cad[i]!=32)valida=true;
    }
return valida;
}

bool validacion_flotante(float *flotante)
{
    bool validado;
    if(cin>>*flotante)
        {
            validado=true;
        }
    else
        {
            validado=false;
        }
return validado;
}

long tamanio_archivo(const char *nombre_archivo,int tamanio_estructura)
{
    FILE *p;
    p=fopen(nombre_archivo,"ab+");
    if(p==NULL) return -1;

    fseek(p,0,2);
    long tamanio= ftell(p)/tamanio_estructura;

    fclose(p);

return tamanio;
}

bool validacion_mail(char *cad)
{
    int arroba=0;
    int punto=0;
    if(cad[0]=='\0' ||
       cad[0]==64   ||
       cad[0]==46 ) return false;

    for(unsigned int i=0;i<strlen(cad);i++)
    {
        if( cad[i]==46 && cad[i+1]==46 ) return false;
        if( cad[i]==46 && cad[i+1]=='\0') return false;

        if( cad[i] <46 ||
            cad[i] ==47 ||
           (cad[i] >57 && cad[i]<64) ||
           (cad[i] >90 && cad[i]<95) ||
            cad[i] == 96 ||
            cad[i] > 122 ) return false;

        if( cad[i]==46) punto ++;
        if( cad[i]==64) arroba++;
    }

    if(arroba==1 && punto>0)
    {
        return validacion_caracteres_antes_y_despues_arroba(cad);
    }
return false;
}

bool validacion_caracteres_antes_y_despues_arroba(char *cad)
{
    bool anterior=false, posterior=false;
    int pos;
    for(unsigned int i=0;i<strlen(cad);i++)
    {
        if(cad[i]==64)
        {
            pos=i;
            break;
        }
    }

    for(int i=0;i<pos;i++)
    {
        if((cad[i] > 47 && cad[i] < 58) ||
           (cad[i] > 64 && cad[i] < 91) ||
           (cad[i] > 96 && cad[i] < 123))
        {
            anterior=true;
        }
    }

    for(unsigned int i=pos+1;i<strlen(cad);i++)
    {
        if((cad[i] > 47 && cad[i] < 58) ||
           (cad[i] > 64 && cad[i] < 91) ||
           (cad[i] > 96 && cad[i] < 123))
        {
            posterior=true;
        }
    }
if(anterior && posterior) return true;
return false;
}

bool validacion_fecha(Fechas *fecha)
{
    int dias_por_mes[12]= {31,0,31,30,31,30,31,31,30,31,30,31};

    if(fecha->mes!=2)
    {
        if(fecha->dia<=dias_por_mes[fecha->mes-1])
            return true;
    }
    else if((fecha->anio%4 == 0 && fecha->anio%100 != 0) ||
            (fecha->anio%400 == 0))
    {
        if(fecha->dia <= 29)
            return true;
    }
    else
    {
        if(fecha->dia <= 28)
            return true;
    }
return false;
}

#endif // FUNCIONES_H_INCLUDED
