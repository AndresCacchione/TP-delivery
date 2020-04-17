#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED


int menu_principal()
{
    cls();
    int op;

    cout<<"*-----------------      MEN� PRINCIPAL       -----------------*"<<endl;
    cout<<"*-------------------------------------------------------------*"<<endl;
    cout<<"*-----------------  1) PLATOS                -----------------*"<<endl;
    cout<<"*-----------------  2) CLIENTES              -----------------*"<<endl;
    cout<<"*-----------------  3) PEDIDOS               -----------------*"<<endl;
    cout<<"*-----------------  4) REPORTES              -----------------*"<<endl;
    cout<<"*-----------------  5) CONFIGURACI�N         -----------------*"<<endl;
    cout<<"*-----------------  ---------------------    -----------------*"<<endl;
    cout<<"*-----------------  0) SALIR DEL PROGRAMA    -----------------*"<<endl<<endl;

    cout<<"\nSeleccione una opci�n del men�: ";
    bool validado = validacion_entero(&op);
    if(!validado) op=-1;
    cls();
return op;
}

bool menu_reintentar()
{
    cls();
    cout<<"Opci�n ingresada no v�lida."<<endl;
    bool reintentar;
    cout<<"�Desea reintentar?"<<endl<<endl;

    cout<<"*-- 1 - SI --*"<<endl;
    cout<<"*-- 0 - NO --*"<<endl;

    cout<<"\nIngrese una opci�n: ";

    while(!(cin>>reintentar))
    {
         cin.clear();
         cin.ignore(1000,'\n');

         cls();
         cout<<"Opci�n no v�lida."<<endl;
         cout<<"�Desea reintentar?"<<endl<<endl;

         cout<<"*-- 1 - SI --*"<<endl;
         cout<<"*-- 0 - NO --*"<<endl;

         cout<<"\nIngrese otra opci�n: ";
    }
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





#endif // FUNCIONES_H_INCLUDED
