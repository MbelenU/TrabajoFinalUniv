//Universidad Pronvicial de Ezeiza
//Tecnicatura en desarrollo de software
//URSINO MARIA BELEN


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//declaro las funciones a utilizar
void imprimirMenu(void);
void tomarValorMenu(int opcion);
void ingresoManual();
void km_Cable(char *ruta);
void ordLista(char *ruta);


struct registro { //struct para manipular los datos mas facilmente
  char loc_1[100];
  char loc_2[100];
  float dist_KM;
  int abon_1;
  int abon_2;
};

struct registroString {   //struct para manipular los datos mas facilmente
  char loc_1[100];
  char loc_2[100];
  char dist_KM[15];
  char abon_1[15];
  char abon_2[15];
};

int main() {
  char *ruta = "abonados.txt";  //puntero a la ruta del archivo

  int opcion;
  do {
    imprimirMenu();
    tomarValorMenu( &opcion);

    switch (opcion) {  //menu con sus respectivos cases y funciones
    case 1:
      printf("Opcion 1\n");
      ingresoManual();
      break;

    case 2:
      printf("Opcion 2\n");
      km_Cable(ruta);
      break;

    case 3:
      printf("Opcion 4\n");
      ordLista(ruta);
      break;

    case 4:
      printf("Salir del programa\n");
      break;

    default:
      printf("Por favor ingrese una opcion valida\n");
      break;
    }
  } while (opcion != 4);

}

//funcion para las opciones del menu
void imprimirMenu(void) {
  printf("\nBIENVENIDO!\n\nSeleccione una opcion: \n");
  printf("1 - Ingresar datos de forma manual\n");
  printf("2 - Mostrar KM de cable utilizado\n");
  printf("3 - Mostrar listado de distancias (descendiente) \n");
  printf("4 - Salir del programa\n");
}

void tomarValorMenu(int opcion) {
  fflush(stdin);
  scanf("%d", opcion);
}

//CASE 1
void ingresoManual() {

  FILE *archivo;
  archivo = fopen("abonados.txt", "a+");   //creo archivo en modo lectura y escritura
  int cont = 0;
  int opcion = 1;
  struct registro Dato_grabar;

  if ((archivo = fopen("abonados.txt", "a+")) == NULL) {      //Si el archivo no existe
    printf("\nNo se ha podido abrir el archivo.\n");
    printf("Verifique la existencia.\n");
  } else {                      //si el archivo fue creado correctamente
    do {
//Ingresar datos y los guardo en la struct
      printf("\nIngrese Localidad 1:");

      scanf("%s", &Dato_grabar.loc_1);
      fflush(stdin);
      printf("\nIngrese cantidad de abonados de la localidad: ");

      scanf("%d", &Dato_grabar.abon_1);
      fflush(stdin);
      printf("\nIngrese Localidad 2: ");

      scanf("%s", &Dato_grabar.loc_2);
      fflush(stdin);
      printf("\nIngrese cantidad de abonados de la localidad: ");

      scanf("%d", &Dato_grabar.abon_2);
      fflush(stdin);
      printf("\nIngrese distancia entre localidades en KM: ");

      scanf("%f", &Dato_grabar.dist_KM);
      fflush(stdin);

      char str[100];
      sprintf(str, "%s,%i,%s,%i,%.2f\n", Dato_grabar.loc_1, Dato_grabar.abon_1, Dato_grabar.loc_2, Dato_grabar.abon_2, Dato_grabar.dist_KM);
      fputs(str, archivo);  //imprime en el archivo directamente los datos
      printf("\nDesea ingresar otro par de localidades?\n 1=si/0=no:");
      scanf("%d", &opcion);

    } while (opcion == 1);

    fclose(archivo);
  }

}

void ordLista(char *ruta) {
  FILE *archivo;
  char buffer[60], *ptr, *var_ptr, temporal[25];
  struct registroString Datoagrabar;   //utilizo la otra struct con solo strings
  int cont_campo, conteo_iteracion = 0;
  if ((archivo = fopen(ruta, "r")) == NULL) {
    printf("No se ha podido abrir el archivo.\n");
    printf("Verifique la existencia...\n");
  } else {
    int cantRegistros = devuelveCantCampos(archivo);
    rewind(archivo);
    struct registroString ListaReg[cantRegistros];
    while (!(conteo_iteracion == cantRegistros)) {
      conteo_iteracion++;
      cont_campo = 1;
      ptr = buffer;
      fgets(buffer, 60, archivo);
      var_ptr = temporal;                // inicializo puntero a la variable temporal
      while ( *ptr != '\0') {
        if ( *ptr != ',') {
          *var_ptr = *ptr;        //se copian los caracteres y se incrementan los punteros
          var_ptr++;
          ptr++;
        } else {
          *var_ptr = '\0';           // finalizo cadena que apunta a variable temporal
          ptr++;                //puntero a buffer
          switch (cont_campo) {
          case 1:
            strcpy(Datoagrabar.loc_1, temporal);     //copio los datos de la struct en una variable temporal
            break;
          case 2:
            strcpy(Datoagrabar.abon_1, temporal);
            break;
          case 3:
            strcpy(Datoagrabar.loc_2, temporal);
            break;
          case 4:
            strcpy(Datoagrabar.abon_2, temporal);
            break;

          }

          cont_campo++;

          var_ptr = temporal;       //se posiciona puntero en variable temporal
        }
      }
      strcpy(Datoagrabar.dist_KM, temporal);            //copio los datos de la struct en una variable temporal

      ListaReg[conteo_iteracion - 1] = Datoagrabar;                   //agrego el item que se esta iterando a la lista de los registros

    }
    int i, j;
    struct registroString t;
    printf("\nLISTADO DE DISTANCIAS(KM) EN FORMA DESCENDIENTE:\n");
   //se realiza ordenamiento
    for (i = 1; i < cantRegistros; i++) {
      for (j = 0; j < cantRegistros - i; j++)
      {
        if (atof(ListaReg[j].dist_KM) < atof(ListaReg[j + 1].dist_KM)) //condicion mayor-menor
        {
          t = ListaReg[j];
          ListaReg[j] = ListaReg[j + 1];
          ListaReg[j + 1] = t;
        }
      }
    }
    //muestro por consola
    for (i = 0; i < cantRegistros; i++) {
      printf("\n %.2f|%s|%s \n", atof(ListaReg[i].dist_KM), ListaReg[i].loc_1, ListaReg[i].loc_2);   //convierto string en float con atof
    }

  }
  fclose(archivo);
}
 //devuelve la cantidad de filas registradas del archivo principal
int devuelveCantCampos(FILE *archivo) {
  int cont_saltos = 0;
  char c = fgetc(archivo);
  while (c != EOF) {    //mientras que no sea end of file
    c = fgetc(archivo);
    if (c == '\n') {
      cont_saltos++;     //que incremente
    }
  }
  return cont_saltos;
}


void km_Cable(char *ruta) {
  FILE *archivo;
  char buffer[60], *ptr, *var_ptr, temporal[25];
  struct registroString Datoagrabar;
  int cont_campo, conteo_iteracion = 0;
  int acum = 0;
  if ((archivo = fopen(ruta, "r")) == NULL) {
    printf("No se ha podido abrir el archivo.\n");
    printf("Verifique la existencia...\n");
  } else {
    int cantRegistros = devuelveCantCampos(archivo);
    rewind(archivo);
    struct registroString ListaReg[cantRegistros];
    while (!(conteo_iteracion == cantRegistros)) {
      conteo_iteracion++;
      cont_campo = 1;
      ptr = buffer;
      fgets(buffer, 60, archivo);
      var_ptr = temporal; //inicializo puntero a la variable temporal
      while ( *ptr != '\0') {
        if ( *ptr != ',') {
          *var_ptr = *ptr; //se copian los caracteres y se incrementan los punteros
          var_ptr++;
          ptr++;
        } else {
          *var_ptr = '\0'; //finalizo cadena que apunta a variable temporal
          ptr++; // Puntero a buffer
          var_ptr = temporal;
          //se posiciona puntero en variable temporal
        }
      }

      strcpy(Datoagrabar.dist_KM, temporal);

      //agrego el item que se esta iterando a la lista de los registros
      ListaReg[conteo_iteracion - 1] = Datoagrabar;

    }

    // Muestro por consola

    int i, j;
    float km_total = 0;
    struct registroString t;

    for (i = 0; i < cantRegistros; i++) {
      km_total += atof(ListaReg[i].dist_KM);   //acumulador para que muestre el total de km acumulados
                                                  //atof para convertir el string a float
    }
    printf("\n %.2f KM DE CABLE UTILIZADOS PARA UNIR LAS LOCALIDADES\n", km_total);
    free(ListaReg);
  }
  fclose(archivo);

}
