#ifndef DATA_H
#define DATA_H
#define MAX_LEN 50
#define CLAVE 'K'

struct Contrasena{
	char plataforma[MAX_LEN];
	char usuario[MAX_LEN];
	char contrasena[MAX_LEN];
};

void agregarContrasena(struct Contrasena *c[], short *);
void imprimirUsuarios(struct Contrasena *c[], short);
void mostrarUsuario(struct Contrasena *c[], short);
void borrarUsuario(struct Contrasena *c[], short *, char[], char);
void manual_ayuda();
void encriptarDesencriptarArchivo(char[]);
struct Contrasena *ingresarDatos();
char *encriptar(char *);

#endif
