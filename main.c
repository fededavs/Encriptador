#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

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

int main(void)
{
    SetConsoleTitle("GESTOR/ENCRIPTADOR");
	struct Contrasena *contrasenas[100];
	short numContrasenas = 0;
	short i;

	char plataforma[MAX_LEN];
	char usuario[MAX_LEN];
	char contrasena[MAX_LEN];
	char borrado[MAX_LEN];
	char *encriptado = NULL;
	char *desencriptado = NULL;
	char pin[5] = "2024";
	char input_pin[5];
	char opcion;
	char confirmaborrado;
	char nombrearchivo[MAX_LEN];
	char buscar;
	char *extension = NULL;

	FILE *archivo = NULL;
	archivo = fopen("contrasenas.txt", "rt"); //abro el archivo

	if(archivo != NULL) //verifico q haya abierto correctamente
	{
	    while(!feof(archivo))
        {
           if(fgets(plataforma, sizeof(plataforma), archivo) != NULL && fgets(usuario, sizeof(usuario), archivo) != NULL &&
              fgets(contrasena, sizeof(contrasena), archivo) != NULL){

                struct Contrasena *nuevaContrasena = (struct Contrasena *)malloc(sizeof(struct Contrasena));

                if(nuevaContrasena == NULL)
                {
                    printf("\t\t\t\t\tError: no se pudo asignar memoria\n");
                    exit(0);
                }
                plataforma[strcspn(plataforma, "\n")]= '\0';
                usuario[strcspn(usuario, "\n")]= '\0';
                contrasena[strcspn(contrasena, "\n")]= '\0';

                strcpy(nuevaContrasena->plataforma, plataforma);
                strcpy(nuevaContrasena->usuario, usuario);
                strcpy(nuevaContrasena->contrasena, contrasena);

                contrasenas[numContrasenas] = nuevaContrasena;
                numContrasenas++;
           }
        }
        fclose(archivo);
    }
	else{
        printf("\t\t\t\t\tERROR: el archivo no se pudo leer");
        exit(0);
	}

	do{
		printf("\033[1;32m");
        printf("\t\t*\t\t\t--------------------------------\t\t\t*\n");
        printf("\t\t\t\t\t\t  ENCRIPTADOR\n");
        printf("\t\t*\t\t\t--------------------------------\t\t\t*\n\n");
		printf("\033[1;34m");
        printf("\n\t\t*\t\t\tMenu:\t\t\t\t\t\t\t*\n\n");
        printf("\033[1;36m");
        printf("\t\t*\t\t\t1. Agregar contrasena\t\t\t\t\t*\n\n");
        printf("\033[1;33m");
        printf("\t\t*\t\t\t2. Mostrar contrasenas\t\t\t\t\t*\n\n");
        printf("\033[1;31m");
        printf("\t\t*\t\t\t3. Eliminar contrasenas\t\t\t\t\t*\t\t\t\n\n");
		printf("\033[1;36m");
        printf("\t\t*\t\t\t4. Manual de ayuda\t\t\t\t\t*\n\n");
        printf("\033[1;33m");
		printf("\t\t*\t\t\t5. Encriptar/Desencriptar archivo por nombre\t\t*\n\n");
		printf("\033[1;31m");
		printf("\t\t*\t\t\t6. Salir\t\t\t\t\t\t*\t\t\t\n\n");
		printf("\033[1;32m");
		printf("\t\t\t\t\t--------------------------------\n");
		printf("\t\t\t\t\tSeleccione una opcion: ");
		scanf(" %c", &opcion);
		fflush(stdin);
		printf("\t\t\t\t\t--------------------------------\n");

		switch(opcion)
		{
        case '1':
            system("cls");
            printf("\t\t\t\t\t--------------------------------\t\t\n");
            printf("\t\t\t\t\t\t  CONTRASENA\n");
            printf("\t\t\t\t\t--------------------------------\t\t\n\n");
            agregarContrasena(contrasenas, &numContrasenas);

            break;
        case '2':
            system("cls");
            printf("\t\t\t\t\t--------------------------------\t\t\n");
            printf("\t\t\t\t\t\t  CONTRASENAS\n");
            printf("\t\t\t\t\t--------------------------------\t\t\n\n");
            printf("\n\t\t\t\tSeleccione una opcion:\n");
            printf("\n\t\t\t\t1. Ver todos los usuarios registrados.");
            printf("\n\t\t\t\t2. Ver informacion completa de un usuario.\n\t\t\t\t");
            scanf("%c", &buscar);
            fflush(stdin);

            if(buscar == '1')
                imprimirUsuarios(contrasenas, numContrasenas);
            else if(buscar == '2')
            {
                printf("\t\t\t\tIngrese el pin para ver la contrasena: ");
                scanf("%4s", input_pin);
                fflush(stdin);

                if(strcmp(pin, input_pin) == 0)
                {
                    for(i=0; i<numContrasenas; i++)
                    {
                        desencriptado = encriptar(contrasenas[i]->contrasena);
                        strcpy(contrasenas[i]->contrasena, desencriptado);
                        free(desencriptado);
                    }
                    mostrarUsuario(contrasenas, numContrasenas);

                    for(i=0; i<numContrasenas; i++)
                    {
                        encriptado = encriptar(contrasenas[i]->contrasena);
                        strcpy(contrasenas[i]->contrasena, encriptado);
                        free(encriptado);
                    }
                }
            }
            else
                printf("\n\t\t\t\tOpcion invalida.\n");

            printf("\n\t\t\t\tPresione cualquier tecla para continuar...");
            getch();
            system("cls");

            break;
        case '3':
            system("cls");
            printf("\t\t\t\t\t--------------------------------\t\t\n");
            printf("\t\t\t\t\t\t   ELIMINAR\n");
            printf("\t\t\t\t\t--------------------------------\t\t\n\n");
            printf("\t\t\t\tIngrese el nombre de usuario que desea borrar: \n\n\t\t\t\t");
            fgets(borrado, sizeof(borrado), stdin);
			fflush(stdin);

            borrarUsuario(contrasenas, &numContrasenas, borrado, confirmaborrado);

            break;
        case '4':
            system("cls");
            printf("\t\t\t\t\t--------------------------------\t\t\n");
            printf("\t\t\t\t\t\t     AYUDA\n");
            printf("\t\t\t\t\t--------------------------------\t\t\n\n");
            manual_ayuda();

            break;
        case '5':
            system("cls");
            printf("\t\t\t\t\t--------------------------------\t\t\n");
            printf("\t\t\t\t\t\t  ENCRIPTADOR\n");
            printf("\t\t\t\t\t--------------------------------\t\t\n\n");
            printf("\t\t\t\tIngrese el nombre del archivo con su extension al final(.txt): \n\t\t\t\t");
            scanf(" %49[^\n]s", nombrearchivo);
            fflush(stdin);

            printf("\t\t\t\tIngrese el pin de seguridad: ");
            scanf("%4s", input_pin);
            fflush(stdin);

            if(strcmp(pin, input_pin) == 0)
            {
                //verifico el nombre contenga la extension .txt
                extension = strstr(nombrearchivo, ".txt");

                if(extension != NULL){
                    encriptarDesencriptarArchivo(nombrearchivo);
                    break;
                }
                printf("\t\t\t\tEl nombre del archivo debe tener la extension .txt");
                printf("\n\n\t\t\t\tPresione cualquier tecla para continuar...");
                getch();
                system("cls");
            }
            else{
                printf("\n\t\t\t\tEl pin es incorrecto.\n");
                printf("\n\n\t\t\t\tPresione cualquier tecla para continuar...");
                getch();
                system("cls");
            }

            break;
        case '6':
            system("cls");
            printf("\t\t\t\t\t--------------------------------\t\t\n");
            printf("\t\t\t\t\t\t  ENCRIPTADOR\n");
            printf("\t\t\t\t\t--------------------------------\t\t\n\n");
            printf("\t\t\t\tSaliendo del programa...\n");

            break;
        default:
            printf("\t\t\t\tOpcion no valida. Por favor, seleccione una opcion valida.\n");

            printf("\n\t\t\t\tPresione cualquier tecla para continuar...");
            getch();
            system("cls");

            break;
        }
	}while(opcion != '6');

	//libero la memoria
	for(i=0; i<numContrasenas; i++)
		free(contrasenas[i]);

	return 0;
}

void agregarContrasena(struct Contrasena *contrasenas[], short *numContras)
{
	char *encriptado = NULL;
	struct Contrasena *nuevaContrasena = ingresarDatos();

	//encriptado de contraseña
	encriptado = encriptar(nuevaContrasena->contrasena);
	strcpy(nuevaContrasena->contrasena, encriptado);
	free(encriptado);

	contrasenas[*numContras] = nuevaContrasena;
	(*numContras)++;

	//guardar la nueva contrasena en un archivo
	char *modo = (*numContras == 1) ? "wt" : "at";
	FILE *archivo = fopen("contrasenas.txt", modo);

	if(archivo == NULL){
		printf("\t\t\t\t\tError al abrir el archivo\n");
		exit(0);
	}
	fprintf(archivo, "%s\n%s\n%s\n", nuevaContrasena->plataforma, nuevaContrasena->usuario, nuevaContrasena->contrasena);
	fclose(archivo);

	printf("\n\t\t\t\t\tUsuario registrado.\n");

	printf("\n\t\t\t\tPresione cualquier tecla para continuar...");
	getch();
	system("cls");
}

struct Contrasena *ingresarDatos()
{
	struct Contrasena *datos = (struct Contrasena *)malloc(sizeof(struct Contrasena));

	if(datos == NULL){
		printf("\t\t\t\t\tError al asignar memoria\n");
		exit(0);
	}

	printf("\n\t\t\t\tIngrese el nombre de la plataforma: ");
	scanf(" %49[^\n]", datos->plataforma); //acepta hasta 49 caracteres menos el "\n"
	fflush(stdin);

	printf("\n\t\t\t\tIngrese el nombre de usuario: ");
    scanf(" %49[^\n]", datos->usuario);
	fflush(stdin);

	printf("\n\t\t\t\tIngrese la contrasena: ");
	scanf(" %49[^\n]", datos->contrasena);
	fflush(stdin);

	return datos;
}

void imprimirUsuarios(struct Contrasena *contrasenas[], short numContras)
{
	short i;

	printf("\n\t\t\t\t\tLos usuarios registrados son:\n");
	printf("\t\t\t-----------------------------------------------------------------------------\n");

	for(i=0; i<numContras; i++)
	{
		printf("\t\t\t\tPlataforma: %-30s \n\t\t\t\tUsuario: %-30s \n\t\t\t\tContrasena: %-30s\n",
			contrasenas[i]->plataforma, contrasenas[i]->usuario, contrasenas[i]->contrasena);
		printf("\t\t\t-----------------------------------------------------------------------------\n");
	}
}

void mostrarUsuario(struct Contrasena *contrasenas[], short numContras)
{
    short i, longitud;
    short encontrado = 0;
    char nombreUsuario[MAX_LEN];

    printf("\n\t\t\t\tIngrese el nombre del usuario:\n\t\t\t\t");
    fgets(nombreUsuario, sizeof(nombreUsuario), stdin);
    fflush(stdin);

    longitud = strlen(nombreUsuario);
    if(longitud>0 && nombreUsuario[longitud-1] == '\n')
        nombreUsuario[longitud-1] = '\0';

    for(i=0; i<numContras; i++)
    {
        if(strcmp(contrasenas[i]->usuario, nombreUsuario) == 0)
        {
            printf("\n\t\t\t\tPlataforma: %-30s \n\t\t\t\tUsuario: %-30s \n\t\t\t\tContrasena: %-30s\n",
                contrasenas[i]->plataforma, contrasenas[i]->usuario, contrasenas[i]->contrasena);
            printf("\t\t\t-----------------------------------------------------------------------------\n");
            encontrado = 1;
        }
    }
    if(!encontrado)
         printf("\n\t\t\t\tEl usuario no se encontro en el registro.\n");
}

void borrarUsuario(struct Contrasena *contrasena[],short *numContras, char borrado[], char confirmacion)
{
	short i, j, encontrado = 0;
    borrado[strcspn(borrado, "\n")]= '\0'; //eliminar salto de linea

	// buscar y eliminar el usuario del array en memoria
	for(i=0; i<*numContras; i++)
	{
		if(strcmp(contrasena[i]->usuario, borrado) == 0)
		{
		    printf("\t\t\t\tEsta seguro de que desea borrar el usuario '%s'?\n\t\t\t\t si o no(S/N): ", borrado);
            scanf("%1s", &confirmacion);

            if(confirmacion == 's' || confirmacion == 'S')
            {
                free(contrasena[i]);

                for(j=i; j<*numContras-1; j++)
                    contrasena[j] = contrasena[j+1];

                (*numContras)--;
                encontrado = 1;
                i--;
            }
            else{
                printf("\n\t\t\t\tPresione cualquier tecla para continuar...");
                getch();
                system("cls");
                return;
            }
		}
	}

    if(!encontrado){
        printf("\n\t\t\t\tUsuario no encontrado.\n");
        printf("\n\t\t\t\tPresione cualquier tecla para continuar...");
        getch();
        system("cls");
    }
    else{
        // abrir el archivo para reescribirlo
        FILE *archivo = fopen("contrasenas.txt", "wt");

        if(archivo == NULL){
            printf("\t\t\t\t\tError al abrir el archivo\n");
            exit(0);
        }
        // escribir las contraseñas restantes en el archivo
        for(i=0; i<*numContras; i++){
            fprintf(archivo,"%s\n%s\n%s\n", contrasena[i]->plataforma, contrasena[i]->usuario, contrasena[i]->contrasena);
        }

        fclose(archivo);
        printf("\n\t\t\t\tUsuario borrado correctamente.\n");

        printf("\n\t\t\t\tPresione cualquier tecla para continuar...");
        getch();
        system("cls");
    }
}

void manual_ayuda()
{
    FILE *manual = NULL;
    manual = fopen("manual.txt", "rt");
    char instructivo[150];

    if(manual == NULL)
    {
        printf("\t\t\t\t\tError al leer el archivo");
        exit(0);
    }

    while(fgets(instructivo, sizeof(instructivo), manual))
        printf("\t\t%s", instructivo);

    fclose(manual);

    printf("\n\t\t\t\tPresione cualquier tecla para continuar...");
    getch();
    system("cls");
}

void encriptarDesencriptarArchivo(char nombreArchivo[])
{
	char *contenido = NULL;
	char *encriptado = NULL;
	short longitud;

	FILE *archivo = fopen(nombreArchivo, "rt");
	if(archivo != NULL)
    {
		fseek(archivo, 0, SEEK_END); //coloco posicion de lectura al final del archivo
		longitud = ftell(archivo); //guardo el tamaño total del archivo
        fseek(archivo, 0, SEEK_SET); //posicion de lectura desde el principio

		contenido = (char*)malloc((longitud + 1) * sizeof(char));

		if(contenido == NULL){
			printf("\t\t\t\tError al asignar memoria.\n");
			exit(0);
		}

		fread(contenido, 1, longitud, archivo);
		contenido[longitud]= '\0';
		fclose(archivo);
	}
	else{
		printf("\t\t\t\tError al abrir el archivo.\n");
		exit(0);
	}

    encriptado = encriptar(contenido);
    free(contenido);

    archivo = fopen(nombreArchivo, "wt");
    if(archivo != NULL)
    {
        fprintf(archivo, "%s", encriptado);
        fclose(archivo);
        free(encriptado);
        printf("\t\t\t\tArchivo modificado correctamente.\n");

        printf("\n\t\t\t\tPresione cualquier tecla para continuar...");
        getch();
        system("cls");
    }
    else{
        printf("\t\t\t\tError al abrir el archivo\n");
        exit(0);
    }
}

char *encriptar(char *contra)
{
    short i;
	short longitud = strlen(contra);
	char *encriptado = (char *)calloc(longitud+1, sizeof(char));

	if(encriptado == NULL)
	{
		printf("\t\t\t\t\tError: no se pudo asignar memoria\n");
		exit(0);
	}

	for(i=0; i<longitud; i++)
		encriptado[i] = contra[i] ^ CLAVE%125;

	encriptado[longitud]= '\0';
	return encriptado;
}
