#ifndef PROTOTIPOS_H_INCLUDED
#define PROTOTIPOS_H_INCLUDED

///PROTOTIPO CLIENTES///
/////-------------------------------///////

struct Fechas
{
    int dia,mes,anio;
};

struct Clientes
{
    int ID;
    char apellido[50];
    char nombre[50];
    char mail[50];
    char domicilio[100];
    int codigo_postal;
    Fechas fecha;
    bool estado;
};

long tamanio_archivo(const char *,int);
void seccion_clientes();
int menu_clientes();
bool ingresar_cliente();
const char *archivo_clientes="Clientes.dat";
bool validacion_mail(char *);
bool validacion_caracteres_antes_y_despues_arroba(char *);
bool validacion_fecha(Fechas *);
bool cargar_cliente(Clientes *);
bool modificar_cliente ();
int buscar_cliente_por_ID(int);
bool modificar_domicilio (int, int);
bool listar_cliente_por_ID();
void mostrar_registro(Clientes);







/////-------------------------------///////
/// PROTOTIPO PLATOS ////

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
