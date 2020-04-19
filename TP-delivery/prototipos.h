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
    int comision_restaurante;
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
bool validacion_cadena(char *);
bool validacion_flotante(float *);
int modificar_plato();
int modifica_plato_por_ID(int);
void mostrar_resultado(int);
void listar_plato_por_ID();
bool validacion_ID(int *);
int buscar_plato(int, Platos *);
void mostrar_plato(struct Platos);
void listar_platos_por_restaurant();
int mostrar_platos_por_restaurant(int, Platos *);
void listar_todos_los_platos();
int eliminar_plato();
int eliminando_plato(int);

#endif // PROTOTIPOS_H_INCLUDED
