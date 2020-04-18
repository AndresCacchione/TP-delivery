#ifndef PROTOTIPOS_H_INCLUDED
#define PROTOTIPOS_H_INCLUDED

struct Platos
{
    int ID;
    char nombre[50];
    float costo_prep;
    float valor_venta;
    int tiempo_prep;
    int ID_restaurante;
    float comision_restaurante;
    int ID_categoria;
    bool estado;
};

int menu_principal();
void seccion_platos();
int menu_platos();
bool menu_reintentar();
bool validacion_entero(int *);
void nuevo_plato();
bool cargar_registro(Platos *);
bool grabar_registro(Platos);
bool ID_unico(int);
const char archivo_platos[]="Platos.dat";

#endif // PROTOTIPOS_H_INCLUDED
