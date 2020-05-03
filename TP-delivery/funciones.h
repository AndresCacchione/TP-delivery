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





#endif // FUNCIONES_H_INCLUDED
