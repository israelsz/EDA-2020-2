//Importacion de librerias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Se crea una struct la cual se usara para almacenar las distintas combinaciones de postulantes que se vayan generando
typedef struct combinacion combinacion;

struct combinacion{
    int cantidadElementos;
    int pesoTotal;
    int calificacionTotal;
    int *arregloCombinacion;
};

//Entrada: La cantidad de elementos de la nueva combinacion, el arreglo combinacion, el peso total de  la combinacion, la calificacion total.
//Salida: una combinacion.
//Objetivo: Crea una nueva combinacion con todos los elementos de la struct combinacion
combinacion crearCombinacion(int cantidadElementos,int * arregloCombinacion,int pesoTotal,int calificacionTotal){
    combinacion nuevaCombinacion;
    nuevaCombinacion.cantidadElementos = cantidadElementos;
    nuevaCombinacion.pesoTotal = pesoTotal;
    nuevaCombinacion.calificacionTotal = calificacionTotal;
    nuevaCombinacion.arregloCombinacion = malloc(sizeof(int)*cantidadElementos);
    for(int i = 0; i < cantidadElementos; i++){
        nuevaCombinacion.arregloCombinacion[i] = arregloCombinacion[i];
    }
    return (nuevaCombinacion);
}

//Entrada: El nombre del archivo.
//Salida: la lectura del archivo.
//Objetivo: Abrir un archivo en modo lectura y leer su contenido.
FILE * leerArchivo(char* nombreArchivo){
    //Se inicializa archivo como null
    FILE* archivo = NULL;
    archivo = fopen(nombreArchivo, "r"); //Lee el archivo
    if (archivo == NULL){ //Si el archivo no existe.
        return 0;
    } else {
        return(archivo);
    }
}


//Entrada: El arreglo con combinaciones, la cantidad de combinaciones que contiene y la nueva combinacion a agregar.
//Salida: Un nuevo arreglo de combinaciones.
//Objetivo: Agregar una nueva combinacion al arreglo de combinaciones.
combinacion * agregarCombinacion(combinacion * listaCombinaciones, int * cantidadCombinaciones, combinacion nuevaCombinacion){
	combinacion * nuevoArregloCombinaciones = (combinacion *)malloc(sizeof(combinacion)*(*cantidadCombinaciones+1));
	for (int i = 0; i < *cantidadCombinaciones; ++i){
		nuevoArregloCombinaciones[i] = listaCombinaciones[i];
	}
	nuevoArregloCombinaciones[*cantidadCombinaciones] = nuevaCombinacion;
	*cantidadCombinaciones = *cantidadCombinaciones+1;
	free(listaCombinaciones);
	return nuevoArregloCombinaciones;
}

/*
 Funcion usada para debuguear, no se usa formalmente en el programa

//Entrada: El arreglo con combinaciones, la cantidad de combinaciones que contiene
//Salida: Ninguna
//Objetivo: Imprimir por pantalla todas las combinaciones de tripulantes que contiene el arreglo combinacion

void imprimirCombinacion(combinacion * combinaciones, int cantidadCombinaciones){
    for(int i = 0; i < cantidadCombinaciones; i++){
        printf("Imprimiendo combinacion %d \n",i+1);
        for(int j = 0; j < combinaciones[i].cantidadElementos; j++){
            printf("%d \n",combinaciones[i].arregloCombinacion[j]);
        }
    }
}
*/

//Entrada: El arreglo con combinaciones, la cantidad de combinaciones que contiene y una combinacion.
//Salida: Un entero 1 o 0.
//Objetivo: Determinar si la combinacion que ingresa ya se encuentra en el arreglo de combinaciones o no.
//          retorna 1 si ya se encuentra, 0 si no se encuentra.
int estaCombinacion(combinacion *combinaciones, int cantidadCombinaciones, combinacion posibleCombinacion){
    for(int i=0; i < cantidadCombinaciones; i++){
        //Si ambas comparaciones tienen la misma cantidad de elementos dentro de su array de combinatoria
        if(combinaciones[i].cantidadElementos == posibleCombinacion.cantidadElementos){
            //Se chequeara si es la misma combinacion
            int coincidencia = 0;
            for(int j=0; j < posibleCombinacion.cantidadElementos;j++){
                for(int k=0; k < posibleCombinacion.cantidadElementos;k++){
                    if(combinaciones[i].arregloCombinacion[j] == posibleCombinacion.arregloCombinacion[k]){
                        coincidencia = coincidencia + 1;
                    }
                }
            }
            if(coincidencia == posibleCombinacion.cantidadElementos){
                return 1; //La combinacion que se quiere ingresar ya se encuentra
            }
        }
    }
    return 0; //No se encuentra la combinacion que se quiere ingresar
}

//Entrada: una combinacion, el peso de un postulante, el id del postulante y el peso maximo que soporta la nave.
//Salida: Un entero 1 o 0.
//Objetivo: Determinar si es posible crear una nueva combinacion entre una ya existente y un nuevo postulante.
int esPosibleCombinar(combinacion combinacion,int pesoTripulante, int idTripulante, int pesoMaximo){
    for(int i=0; i<combinacion.cantidadElementos; i++){
        if(combinacion.arregloCombinacion[i] == idTripulante){
            return 0; //No es posible combinar, ya que el tripulante ya se encuentra dentro de esta combinacion
        }
    }
    //En caso que el tripulante no se encuentre en la combinacion, se verificara que al ser añadido cumpla el peso maximo
    if((combinacion.pesoTotal + pesoTripulante) <= pesoMaximo){
        return 1; //Si cumple con el peso maximo, es posible hacer la combinacion
    } else {
        return 0; //No cumple con el peso, no es posible hacer esta combinacion
    }
}

//Entrada: una combinacion, el peso, id y calificacion de un tripulante.
//Salida: Una nueva combinacion.
//Objetivo: Crea una nueva combinacion agregando un nuevo tripulante a una combinacion ya creada.
combinacion juntarCombinaciones(combinacion combinacionAntigua, int pesoTripulante, int idTripulante, int calificacionTripulante){
    combinacion nuevaCombinacion;
    nuevaCombinacion.pesoTotal = combinacionAntigua.pesoTotal + pesoTripulante;
    nuevaCombinacion.calificacionTotal = combinacionAntigua.calificacionTotal + calificacionTripulante;
    nuevaCombinacion.cantidadElementos = combinacionAntigua.cantidadElementos + 1;
    nuevaCombinacion.arregloCombinacion = malloc(sizeof(int)*nuevaCombinacion.cantidadElementos);
    //Se copian los tripulantes que estaban en la combinacion antigua
    for(int i=0; i < combinacionAntigua.cantidadElementos;i++){
        nuevaCombinacion.arregloCombinacion[i] = combinacionAntigua.arregloCombinacion[i];
    }
    //Se agrega el nuevo tripulante
    nuevaCombinacion.arregloCombinacion[nuevaCombinacion.cantidadElementos-1] = idTripulante;
    return nuevaCombinacion;
}


//Entrada: Dos combinaciones provenientes de un arreglo de combinaciones.
//Salida: Ninguna.
//Objetivo: Efectuar un swap entre dos posiciones para el algoritmo BubbleSort.
void swap(combinacion *combinacion1, combinacion *combinacion2){ 
    combinacion auxiliar = *combinacion1; 
    *combinacion1 = *combinacion2; 
    *combinacion2 = auxiliar; 
} 

//Entrada: El arreglo con combinaciones y la cantidad de combinaciones que contiene.
//Salida: Ninguna.
//Objetivo: Ordenar el arreglo respecto a la calificacion de mayor a menor, haciendo uso de BubbleSort.
void ordenarListaPorPuntuacion(combinacion *combinaciones,int cantidadCombinaciones){
    for(int i = 0; i < cantidadCombinaciones-1; i++){
        //Los ultimos i elementos ya se encuentran ordenados
        for(int j = 0; j < cantidadCombinaciones-i-1; j++){
            //Si la calificacion de la combinacion de la posicion actual es menor a la de la siguiente posicion
            if (combinaciones[j].calificacionTotal < combinaciones[j+1].calificacionTotal){
                swap(&combinaciones[j], &combinaciones[j+1]);
            }  
        }
    }
}    

//Funcion principal del programa
int main(){
    //En primer lugar se leera el archivo
    FILE* archivo = leerArchivo("entrada.in");
    //Si la funcion leerArchivo devuelve un 0 es porque el archivo no existe o el nombre fue mal ingresado.
    if(archivo == 0){
        printf("Algo fallo, verifique el nombre del archivo por favor\n");
        return 0;
    }
    int cantidadPostulantes;
    int pesoMaximo;
    //Se usara la funcion fscanf para leer y almacenar el primer valor que correspondera a la cantidad de postulantes
    fscanf(archivo,"%d",&cantidadPostulantes);
    //Se vuelve a llamar a fscanf, ahora leera el segundo valor, que es el peso máximo que soporta la nave
    fscanf(archivo,"%d",&pesoMaximo);
    //En caso de que la cantidad de postulantes sea cero, terminara el programa inmediatamente
    if(cantidadPostulantes==0){
        printf("No hay postulantes\n");
        return 0;
    }
    //Luego como ya se sabe la cantidad de postulantes, y se sabe que por cada linea del documento hay 3 datos:
    //Se crean 3 arreglos
    //Tripulantes almacenara los nombres de los tripulantes
    char *tripulantes[cantidadPostulantes];

    //Se le asigna memoria a "cada espacio para que pueda recibir datos"
    for (int j = 0; j < cantidadPostulantes; j++){
        tripulantes[j] = malloc((100) * sizeof(char));
    }
    //Se crea y asigna memoria a los siguientes 3 arreglos que recibiran y guardaran los datos del peso, calificacion de los tripulantes e id de los tripulantes
    int * pesoTripulantes = malloc(sizeof(int)*cantidadPostulantes);
    int * calificacionTripulantes = malloc(sizeof(int)*cantidadPostulantes);
    int * idTripulantes = malloc(sizeof(int)*cantidadPostulantes);

    //Se crea tambien tres variables para almacenar para poder ir leyendo los datos
    char nombreTripulante[100]; //Esta variable almacenara los strings
    int pesoTripulante; //Esta variable almacenara los enteros
    int puntuacionTripulante;
    
    //Se crea Una variable iteradora
    int i = 0;
    //Ahora se ejecutara un ciclo para guardar todo el documento en los 4 arreglos creados anteriormente
    for(i = 0; i < cantidadPostulantes; i++){
        //Se lee y almacena el numero del tripulante en el arreglo.
        fscanf(archivo,"%s",&nombreTripulante);
        strcpy(tripulantes[i], nombreTripulante);
        //Se lee y almacena el peso del tripulante en el arreglo.
        fscanf(archivo,"%d",&pesoTripulante);
        pesoTripulantes[i] = pesoTripulante;
        //Se lee y almacena la calificacion del tripulante en el arreglo.
        fscanf(archivo,"%d",&puntuacionTripulante);
        calificacionTripulantes[i] = puntuacionTripulante;
        //Finalmente se agrega el id del tripulante al arreglo, siendo este la posicion dentro del arreglo
        idTripulantes[i] = i;
    }
    //Una vez almacenada toda la informacion que contiene el archivo, se cierra ya que no se ocupara más
    fclose(archivo);

    //Tambien se creara un arreglo que contendra "Combinaciones"
    int cantidadCombinaciones = 0;
    //Se le asigna memoria y se crea
    combinacion *combinaciones = (combinacion *)malloc(sizeof(combinacion)*cantidadCombinaciones);
    // A continuacion se efectuara la combinatoria para ir creando las distintas combinaciones de tripulantes que puedan abordar
    // Sin embargo esto agregara solo todas las combinaciones de 2 tripulantes al arreglo combinaciones
    for (int i = 0; i < cantidadPostulantes; i++){
        for(int j = i+1; j < cantidadPostulantes; j++){
            if(pesoTripulantes[i]+pesoTripulantes[j] <= pesoMaximo){
                int * arregloCombinacion = malloc(sizeof(int)*2);
                //Se agregan los id de los tripulantes
                arregloCombinacion[0] = i;
                arregloCombinacion[1] = j;
                combinacion nuevaCombinacion = crearCombinacion(2,arregloCombinacion,pesoTripulantes[i]+pesoTripulantes[j],calificacionTripulantes[i]+calificacionTripulantes[j]);
                //Se agrega la combinacion encontrada al arreglo de combinaciones
                combinaciones = agregarCombinacion(combinaciones,&cantidadCombinaciones,nuevaCombinacion);
                free(arregloCombinacion);
            }
        }
    }
 
    //Ahora para añadir las combinaciones restantes se iterara sobre la cantidad de combinaciones
    //Se ira viendo combinacion por combinacion de la lista de combinaciones
    //el ciclo se rompera cuando se hayan recorrido todas las combinaciones y no sea posible crear mas, incluso las que este mismo ciclo crea
    for(int  i = 0; i < cantidadCombinaciones; i++){
        //Se vera si la combinacion seleccionada puede agregar a algun tripulante mas dentro de ella, para eso se recorre todo el arreglo de tripulantes
        for(int j = 0; j < cantidadPostulantes; j ++){
            int sePuedeCombinar = esPosibleCombinar(combinaciones[i],pesoTripulantes[j],idTripulantes[j],pesoMaximo);
            //Si es posible combinar
            if(sePuedeCombinar == 1){
                //Se crea la combinacion con el tripulante añadido a la antigua combinacion
                combinacion nuevaCombinacion = juntarCombinaciones(combinaciones[i],pesoTripulantes[j],idTripulantes[j],calificacionTripulantes[j]);
                //Luego se verifica si la combinacion creada no se encuentra dentro del arreglo de combinaciones
                if(estaCombinacion(combinaciones,cantidadCombinaciones,nuevaCombinacion) == 0){
                    //En caso de no estarlo,se actualiza el arreglo de combinaciones
                    combinaciones = agregarCombinacion(combinaciones,&cantidadCombinaciones,nuevaCombinacion);
                }
            }
        }
    }
    //Ahora finalmente solo queda añadir los postulantes solitarios
    //Se recorre todo el arreglo de tripulantes
    for(int i = 0; i < cantidadPostulantes;i++){
        //Si el peso del tripulante i es menor o igual al peso maximo de la nave
        if(pesoTripulantes[i] <= pesoMaximo){
            //Se agrega al arreglo de combinaciones
            int * arregloCombinacion = malloc(sizeof(int)*1);
            arregloCombinacion[0] = i;
            combinacion nuevaCombinacion = crearCombinacion(1,arregloCombinacion,pesoTripulantes[i],calificacionTripulantes[i]);
            combinaciones = agregarCombinacion(combinaciones,&cantidadCombinaciones,nuevaCombinacion);
        }
    }

    //Una vez que tenemos todas las combinaciones en el arreglo combinaciones, queda ordenar el arreglo segun la calificacion de sus tripulantes
    ordenarListaPorPuntuacion(combinaciones,cantidadCombinaciones);

    //Ahora el arreglo se encuentra ordenado de mayor a menor segun la puntuacion, ahora solo queda escribir el documento
    FILE * salida; //Se define un archivo salida
    salida = fopen("tripulacion.out", "w"); //Se abre salida en modo de escritura y se le asigna el nombre tripulacion.out
    //Se toma una combinacion del arreglo de combinaciones
    for(int i=0; i<cantidadCombinaciones; i++){
        //Se lee el interior de esta combinacion
        for(int j = 0; j < combinaciones[i].cantidadElementos; j++){
            if(combinaciones[i].cantidadElementos == 1){
                //En caso que entre un solo elemento, no escribira la coma, solo un espacio
                fprintf(salida,"%s",tripulantes[combinaciones[i].arregloCombinacion[j]]);
                fprintf(salida," ");
            } else {
                //Se concatena el nombre y la coma para cumplir el formato de salida
                //Se escribe el nombre en el archivo
                fprintf(salida,"%s",tripulantes[combinaciones[i].arregloCombinacion[j]]);
                fprintf(salida,", ");
            }
        }
        //Luego para escribir los siguientes elementos
        //En caso que la combinacion solo tenga un elemento
        if(combinaciones[i].cantidadElementos == 1){
            //Luego se escribira el peso de esa combinacion
            fprintf(salida,"%d ",combinaciones[i].pesoTotal);
            //Finalmente se escribe la puntuacion de esa combinacion
            fprintf(salida,"%d",combinaciones[i].calificacionTotal);
            //Luego se comprueba si aun quedan elementos, si es asi imprime un salto de linea para escribir los siguientes elementos
            if(i+1 != cantidadCombinaciones){
                fprintf(salida,"\n");
            }
        //En caso que la combinacion no tenga un solo elemento
        } else {
            //Luego se escribira el peso de esa combinacion
            fprintf(salida,"%d, ",combinaciones[i].pesoTotal);
            //Finalmente se escribe la puntuacion de esa combinacion
            fprintf(salida,"%d",combinaciones[i].calificacionTotal);
            //Luego se comprueba si aun quedan elementos, si es asi imprime un salto de linea para escribir los siguientes elementos
            if(i+1 != cantidadCombinaciones){
                fprintf(salida,"\n");
            }
        }
    }
    //Una vez escrito el archivo se cierra
    fclose(salida);
    //Se liberara  memoria a "cada espacio" del arreglo tripulantes
    for (int j = 0; j < cantidadPostulantes; j++){
        free(tripulantes[j]);
    }
    //Se libera la memoria de los otros arreglos usados
    free(pesoTripulantes);
    free(calificacionTripulantes);
    free(idTripulantes);
    printf("Archivo de salida generado ! \n");
    return 0;
}