//Importacion de librerias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h> //Usada para definir infinito dentro del algoritmo de dijkstra
#include <stdbool.h> //Usara para definir true y false dentro del algoritmo de dijkstra


typedef struct conexion conexion;
struct conexion{
    int gasolina, tiempo, idInicio, idFin;
    char nombreInicio[100], nombreFinal[100];
};

typedef struct nodo nodo;
struct nodo{
    int esGasolinera, gasolina, tiempo;
    char nombre[100];
};

typedef struct recorrido recorrido;
struct recorrido{
    int distancia[500];
    int padre[500];
    bool visitados[500];
    int gasolina[500];
};

typedef struct Camino Camino;
struct Camino{
    int numeroNodos;
    int * camino;
    int distancia;
};

//Entrada: 
//Salida: Un nuevo nodo con informacion inicial.
//Objetivo: Crear un nuevo nodo en el cual se almacenara informacion.
nodo crearNodoVacio(){
    nodo nuevoNodo;
    nuevoNodo.esGasolinera = 0;
    nuevoNodo.gasolina = -1;
    nuevoNodo.tiempo = -1;
    strcpy(nuevoNodo.nombre,"");
    return nuevoNodo;
}

//Entrada: Entero que contiene la cantidad de nodos totales y un arreglo de dos dimensiones representando a la matriz de adyacencia 
//Salida:
//Objetivo: Iniciar la matriz de adyacencia creando todos los nodos con informacion inicial vacia.
void iniciarMatriz(int cantidadNodos,nodo arr[][cantidadNodos]){
    int i,j;
    for(i = 0; i < cantidadNodos; i++)
        for(j = 0; j < cantidadNodos; j++)
            arr[i][j] = crearNodoVacio();
}

//Entrada: Entero con la cantidad de nodos, la matriz de adyacencia
//Salida: 
//Objetivo: mostrar por pantalla la matriz de adyacencia con sus distintos datos
void printearMatriz(int cantidadNodos,nodo arr[][cantidadNodos]){
     int i, j;

     for(i = 0; i < cantidadNodos; i++){
         for(j = 0; j < cantidadNodos; j++){
             printf("(%s) %d/%d gasolinera?:%d | ",arr[i][j].nombre,arr[i][j].tiempo,arr[i][j].gasolina,arr[i][j].esGasolinera);
         }
         printf("\n");
     }
}

//Entrada: Arreglo con informacion de las aristas, entero con la cantidad de aristas, entero con la cantidad de nodos y la matriz de adyacencia.
//Salida: 
//Objetivo: Leer y copiar los datos recolectados en el arreglo de aristas a la matriz de adyacencia.
void agregarInfoNodos(conexion * aristas,int * cantidadAristas,int cantidadNodos, nodo arreglo[][cantidadNodos]){
    for(int i = 0; i < cantidadNodos; i++){
        //i correspondera al id del nodo, entonces se buscara ese nodo en las aristas
        for(int j = 0; j < *cantidadAristas; j++){
            //Si se encuentra un nodo de inicio igual al del id
            if(aristas[j].idInicio == i){
                //Se modifica la matriz de adyacencia con los datos de la arista
                arreglo[i][aristas[j].idFin].tiempo = aristas[j].tiempo;
                arreglo[i][aristas[j].idFin].gasolina = aristas[j].gasolina;
                strcpy(arreglo[i][aristas[j].idFin].nombre,aristas[j].nombreFinal);
            }
        }
    }
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

//Entrada: Un archivo, entero con la cantidad maxima de aristas, y entero que llevara la cuenta de la cantidad de aristas
//Salida: un arreglo que contiene toda la informacion de las aristas presentes en el archivo leido
//Objetivo: leer y almacenar toda la informacion del archivo en forma de aristas.
conexion * almacenarInformacionAristas(FILE *mapa, int cantidadMaximaAristas, int *cantidadAristas){
    //se asigna memoria a un arreglo considerando la maxima cantidad de aristas posiblemente existentes
    conexion * aristas = (conexion*)malloc(sizeof(conexion)*cantidadMaximaAristas);
    char nombreInicio[100], nombreFinal[100];
    int cantidadTiempo,cantidadGasolina;
    //Se almacena toda la informacion del archivo en el arreglo
    while(fscanf(mapa,"%s %s %d %d",&nombreInicio,&nombreFinal,&cantidadTiempo,&cantidadGasolina) == 4){
        conexion nuevaArista;
        strcpy(nuevaArista.nombreInicio,nombreInicio);
        strcpy(nuevaArista.nombreFinal,nombreFinal);
        nuevaArista.tiempo = cantidadTiempo;
        nuevaArista.gasolina = cantidadGasolina;
        nuevaArista.idFin = -1;
        nuevaArista.idInicio = -1;
        aristas[*cantidadAristas] = nuevaArista;
        *cantidadAristas = *cantidadAristas + 1;
    }
    return aristas;
}

//Entrada: Arreglo con la informacion de las aristas, la cantidad de aristas
//Salida: 
//Objetivo: mostrar por pantalla la informacion de todas las aristas encontradas.
void printAristas(conexion* aristas, int * cantidadAristas){
    for(int i = 0 ; i < *cantidadAristas; i++){
        printf("%s (%d), %s (%d), tiempo: %d, gas: %d \n",aristas[i].nombreInicio,aristas[i].idInicio,aristas[i].nombreFinal,aristas[i].idFin,aristas[i].tiempo,aristas[i].gasolina);
    }
}

//Entrada: Arreglo con la informacion de aristas, la cantidad de aristas
//Salida: El arreglo modificado.
//Objetivo: generarId's para cada parada presente en las aristas leídas, las cuales se generan segun su nombre
conexion * crearIds(conexion* aristas,int * cantidadAristas){
    //En primer lugar se fijara el id al primer destino de las aristas como cero
    aristas[0].idInicio = 0;
    //Ahora se recorrera para generar todos los id
    for(int i = 0; i < *cantidadAristas; i++){
        //si no tiene id
        if(aristas[i].idInicio == -1){
            //Se verificara si alguno de los id asignados anteriores esta vinculado a su nombre
            for(int j = 0; j < *cantidadAristas; j++){
                //Si coinciden sus nombres y el id de aristas j no es -1
                if(strcmp(aristas[i].nombreInicio,aristas[j].nombreInicio) == 0 && aristas[j].idInicio != -1){
                    aristas[i].idInicio = aristas[j].idInicio;
                }
            }
        }
        //Si aun no tiene id, se le creara uno
        if(aristas[i].idInicio == -1){
            //Se consigue el id mayor existente actualmente
            int mayor = -1;
            for(int j = 0; j < *cantidadAristas; j++){
                if(aristas[j].idInicio > mayor){
                    mayor = aristas[j].idInicio;
                }
            }
            //Luego se asiganara el nuevo id que sera mayor +1 a la arista de inicio
            aristas[i].idInicio = mayor+1;
        }
    }
    //Ahora todos los id de inicio estan generados, entonces para generar los id de llegada se ejecutara el siguiente ciclo
    for(int i = 0; i < *cantidadAristas; i++){
        for(int j = 0; j < *cantidadAristas; j++){
            if(strcmp(aristas[i].nombreFinal,aristas[j].nombreInicio) == 0){
                aristas[i].idFin = aristas[j].idInicio;
                j = *cantidadAristas;
            }
        }
    }
    //Generados todos los id se retorna el arreglo de aristas
    return aristas;
}

//Entrada: Un archivo, entero con la cantidad de nodos y entero con la cantidad de gasolineras
//Salida: un arreglo que contiene todas las gasolineras encontradas y su informacion
//Objetivo: Leer del archivo las gasolineras existentes
nodo * leerGasolineras(FILE *archivoGasolinera, int cantidadNodos, int* cantidadGasolineras){
    //Se asigna memoria considerando el peor caso: todos los nodos son gasolineras
    nodo * gasolineras = (nodo*)malloc(sizeof(nodo)*cantidadNodos);
    char nombreGasolinera[100];
    //Parara automaticamente al haber terminado de leer todo el documento
    while(fscanf(archivoGasolinera,"%s",&nombreGasolinera) == 1){
        nodo nuevoNodo;
        strcpy(nuevoNodo.nombre,nombreGasolinera);
        gasolineras[*cantidadGasolineras] = nuevoNodo;
        *cantidadGasolineras = *cantidadGasolineras + 1;
    }
    //Una vez almacenadas todas las gasolineras se retorna al arreglo con gasolineras
    return gasolineras;
}

//Entrada: Entero con el numero de nodos, la matriz de adyacencia, arreglo con la informacion de gasolineras, entero con la cantidad de gasolineras
//Salida: 
//Objetivo: Agregar la informacion de las gasolineras a la matriz de adyacencia
void agregarGasolineras(int numeroNodos, nodo matriz[][numeroNodos], nodo * gasolineras, int * cantidadGasolineras){
    //Se recorrera toda la matriz de adyacencia, si se encuentra una similitud de nombre en un nodo, se marcara como que ese nodo es gasolinera
    for(int i = 0; i < *cantidadGasolineras; i++){
        for(int j = 0; j < numeroNodos; j++){
            for(int k = 0; k < numeroNodos; k++){
                if(strcmp(gasolineras[i].nombre,matriz[j][k].nombre) == 0){
                    matriz[j][k].esGasolinera = 1;
                }
            }
        }
    }

}

//Entrada: Entero con la cantidad de nodos, arreglo con las distintas distancias de un nodo a otro, arreglo que dice que nodos han sido visitados
//Salida: Un entero que representa cual es la posicion que tiene un menor tiempo, usada en dijkstra
//Objetivo: Encontrar el camino mas corto, parte del algoritmo de dijkstra.
int distanciaMinima(int cantidadNodos,int distancia[], bool visitados[]) { 
      
    // Initialize min value 
    int min = INT_MAX, indiceMasCorto; 
  
    for (int v = 0; v < cantidadNodos; v++) 
        if (visitados[v] == false && 
                   distancia[v] <= min) 
            min = distancia[v], indiceMasCorto = v; 
  
    return indiceMasCorto; 
} 

//Entrada: Entero con la cantidad de nodos, la matriz de adyacencia, entero que representa al nodo de origen
//Salida: Un tipo de dato recorrido que contiene toda la información conseguida del algoritmo de dijkstra(distancia minima a cualquier otro punto y cantidad de combustible a usar hasta cualquier punto)
//Objetivo: Ejecutar el algoritmo de dijkstra en el nodo de origen seleccionado.
recorrido dijkstra(int cantidadNodos,nodo grafo[cantidadNodos][cantidadNodos], int origen) {
    recorrido nuevoRecorrido;

    nuevoRecorrido.distancia[cantidadNodos];  

    nuevoRecorrido.visitados[cantidadNodos]; 
  
    //El arreglo padre contendra el nodo previo desde donde se llego
    nuevoRecorrido.padre[cantidadNodos]; 
    
    nuevoRecorrido.gasolina[cantidadNodos];

    //Se inicializan los arreglos antes definidos
    for (int i = 0; i < cantidadNodos; i++) 
    { 
        nuevoRecorrido.padre[0] = -1; 
        nuevoRecorrido.distancia[i] = INT_MAX; 
        nuevoRecorrido.visitados[i] = false;
        nuevoRecorrido.gasolina[i] = INT_MAX;
    } 
  
    // La distancia desde el vertice de origen a si mismo siempre es cero, asi mismo la cantidad de combustible a usar
    nuevoRecorrido.distancia[origen] = 0;
    nuevoRecorrido.gasolina[origen] = 0;
    
    //Se consigue el camino mas corto para todos los vertices

    for (int count = 0; count < cantidadNodos - 1; count++){ 
        //Se elige el nodo con la minima distancia o tiempo, que no haya sido procesado, o sea tenga un false en el arreglo visitados
        int u = distanciaMinima(cantidadNodos, nuevoRecorrido.distancia, nuevoRecorrido.visitados); 
  
        //Se marca el nodo visitado como true, lo que significa que ya fue procesado por el algoritmo
        nuevoRecorrido.visitados[u] = true; 

        //Se actualiza el valor de distancia y combustible a los nodos adyacentes al recien procesado
        for (int v = 0; v < cantidadNodos; v++) 

            //Se actualizan los nodos adyacentes, verificando que exista una conexion, que no hayan sido procesados y si la distancia es mas pequeña a la ya ingresada actualmente
            if (!nuevoRecorrido.visitados[v] && grafo[u][v].tiempo &&  nuevoRecorrido.distancia[u] + grafo[u][v].tiempo < nuevoRecorrido.distancia[v] && grafo[u][v].tiempo != -1){ 
                nuevoRecorrido.padre[v] = u;
                nuevoRecorrido.distancia[v] = nuevoRecorrido.distancia[u] + grafo[u][v].tiempo;
                nuevoRecorrido.gasolina[v] = nuevoRecorrido.gasolina[u] + grafo[u][v].gasolina;
            }  
    } 
    //Se retorna el resultado de dijkstra
    return nuevoRecorrido;
}

//Entrada: Entero que representa el nodo de inicio, el nodo de destino, el arreglo padre conseguido en dijkstra, la cantidad de nodos y un entero que almacenara la cantidad de nodos que tenga el camino
//Salida: Un entero que representa cual es la posicion que tiene un menor tiempo, usada en dijkstra
//Objetivo: Encontrar el camino mas corto, parte del algoritmo de dijkstra.
int * guardarCamino(int inicio, int destino, int padre[], int cantidadNodos, int *cantNodosCamino){
    int * camino = (int*)malloc(sizeof(int)*cantidadNodos);
    int idActual;
    idActual = padre[destino];
    camino[*cantNodosCamino] = destino;
    *cantNodosCamino = *cantNodosCamino + 1;
    while(idActual != padre[inicio]){
        camino[*cantNodosCamino] = idActual;
        *cantNodosCamino = *cantNodosCamino +1;
        idActual = padre[idActual];
    }
    return camino;
}

//Entrada: Arreglo que contiene el camino mas corto a un nodo, entero con la cantidad de nodos de ese camino, arreglo que contiene la distancia/tiempo mas corta a cualquier otro nodo, entero con el nodo de destino
//Salida: 
//Objetivo: Mostrar por pantalla el camino a seguir mas corto desde un nodo de inicio a un nodo final
void printearCamino(int * camino, int *cantNodosCamino, int distancia[], int destino){
    printf("Camino:\n");
    for(int i = *cantNodosCamino-1; i >= 0; i--){
        printf("%d ",camino[i]);
    }
    printf("\nTiempo: %d\n",distancia[destino]);
}

//Entrada: Entero con el numero de nodos, entero con el combustible inicial, entero con la cantidad de gasolineras, la matriz de adyacencia, dos variables que almacenaran por referencia el numero total de nodos del camino finalmente generado y el tiempo/distancia de ese camino
//Salida: Arreglo que contiene el camino nodo por nodo mas corto desde la tierra hasta pizza planet
//Objetivo: Conseguir el camino mas corto desde la tierra hasta pizza planet, tomando en consideracion el gasto de combustible y las gasolineras para rellenar el mismo
int * conseguirCaminoMasCorto(int numeroNodos, int combustibleInicial, int * cantidadGasolineras, nodo matriz[numeroNodos][numeroNodos], int * numeroTotalNodos,int * tiempoMasCorto){
    //Se debe conseguir el camino mas corto desde la tierra hasta pizza planeta, entonces
    //En primer lugar se conseguira el id de la tierra y el id de pizza planeta leyendo la matriz de adyacencia
    //Tambien se leeran los id de las gasolineras y se almacenaran en un arreglo
    int idTierra, idPizzaPlanet;
    int numeroGasolinerasEncontradas = 0;
    int * idBencineras = (int*)malloc(sizeof(int)*numeroNodos);
    for(int i = 0; i < numeroNodos; i++){
        for(int j = 0; j < numeroNodos; j++){
            if(strcmp(matriz[i][j].nombre,"tierra") == 0){
                idTierra = j;
            }
            if(strcmp(matriz[i][j].nombre,"pizza_planet") == 0){
                idPizzaPlanet = j;
            }
            if(matriz[i][j].esGasolinera == 1){
                int seEncuentra = 0;
                for(int k = 0; k < numeroGasolinerasEncontradas; k++){
                    if(idBencineras[k] == j){
                        seEncuentra = 1;
                    }
                }
                if(seEncuentra == 0){
                    idBencineras[numeroGasolinerasEncontradas] = j;
                    numeroGasolinerasEncontradas = numeroGasolinerasEncontradas + 1;
                }
            }
        }
    }
    //Se correra el algoritmo de dijkstra para conseguir el camino mas corto midiendo el tiempo desde la tierra a todas las otras paradas
    //t inicial
    matriz[1][idBencineras[1]].tiempo = 50;
    recorrido camino = dijkstra(numeroNodos,matriz,idTierra);
    int numeroNodosCamino = 0;
    //De todos los caminos conseguidos de correr dijkstra sobre la tierra se conseguira el recorrido a seguir desde la tierra a pizza planet
    int * recorridoMasCorto = guardarCamino(idTierra,idPizzaPlanet,camino.padre,numeroNodos,&numeroNodosCamino);

    //En primer lugar se verificara si es posible llegar de la tierra a pizza planet directamente
    //Se consulta si el camino mas corto desde la tierra hasta pizza planet gasta menos combustible que el disponible inicialmente
    if(camino.gasolina[idPizzaPlanet] <= combustibleInicial){
        //Si efectivamente gasta menos combustible que el combustible inicial
        //Se retorna el recorrido mas corto encontrado inicialmente con dijkstra, debido a que alcanza el combustible
        return recorridoMasCorto;
    }
    Camino * arregloCaminos = (Camino*)malloc(sizeof(Camino)*numeroGasolinerasEncontradas);
    int k = 0;
    //En caso de que no haya alcanzado el combustible, sera necesario el conseguir la distancia de la tierra hacia todas las bencineras disponibles
    //y de las bencineras hasta pizza planet, para luego seleccionar la suma de recorridos que tenga una menor cantidad de tiempo
    //Para ello se ejecutara dijkstra para todas las gasolineras que se busco inicialmente
    for(int i = 0; i < numeroGasolinerasEncontradas; i++){
        Camino nuevoTrayecto;
        recorrido nuevoCamino = dijkstra(numeroNodos,matriz,idBencineras[i]);
        int numNodosNuevoCamino = 0;
        nuevoTrayecto.camino = guardarCamino(idBencineras[i],idPizzaPlanet,nuevoCamino.padre,numeroNodos,&numNodosNuevoCamino);
        nuevoTrayecto.numeroNodos = numNodosNuevoCamino;
        nuevoTrayecto.distancia = nuevoCamino.distancia[idPizzaPlanet];
        arregloCaminos[k] = nuevoTrayecto;
        k = k + 1;
    }
    //Ahora se tienen almacenados todos los posibles caminos desde las gasolineras hasta pizza planet, entonces se calculara cual de todos los caminos de:
    // tierra -> gasolinera -> pizza_planet es el mas corto
    //se fija el menor tiempo en infinito inicialmente
    int menorTiempo = INT_MAX;
    int idBencineraConMenorTiempo;
    int idArregloBencineraConMenorTiempo;
    for(int i = 0; i < numeroGasolinerasEncontradas; i++){
        //Primero se verifica que el camino encontrado es valido, para ello se mide la gasolina, en caso de no hacerlo se vbuscara un nuevo camino haciendo dijskstra
        if(camino.distancia[idBencineras[i]] > camino.distancia[idBencineras[i+1]]){
            for(int i = 0; i < numeroGasolinerasEncontradas; i++){
                Camino nuevoTrayecto;
                recorrido nuevoCamino = dijkstra(numeroNodos,matriz,idBencineras[i]);
                int numNodosNuevoCamino = 0;
                nuevoTrayecto.camino = guardarCamino(idBencineras[i],idPizzaPlanet,nuevoCamino.padre,numeroNodos,&numNodosNuevoCamino);
                nuevoTrayecto.numeroNodos = numNodosNuevoCamino;
                nuevoTrayecto.distancia = nuevoCamino.distancia[idPizzaPlanet];
                arregloCaminos[k] = nuevoTrayecto;
                k = k + 1;
            }
        }
        
        //Se consigue la cantidad de tiempo invertida desde la gasolinera hasta pizza planet
        //Se suma el tiempo que tarda la tierra a la gasolinera con el de la gasolinera a pizza planet
        int tiempo1 = arregloCaminos[i].distancia;
        int tiempo2 = camino.distancia[idBencineras[i]];
        int tiempoCalculado = tiempo1+tiempo2;
        if(tiempoCalculado < menorTiempo){
            menorTiempo = tiempoCalculado;
            idBencineraConMenorTiempo = idBencineras[i];
            idArregloBencineraConMenorTiempo = i;
        }
    }
    //Ahora se tiene la minima distancia posible, entonces se procedera a generar el camino final:
    //Se generara el camino mas corto desde la tierra hasta la bencinera seleccionada anteriormente
    numeroNodosCamino = 0;
    int * recorridoMasCortoGasolinera = guardarCamino(idTierra,idBencineraConMenorTiempo,camino.padre,numeroNodos,&numeroNodosCamino);
    //Ahora se conseguiora el camino desde la gasolinera hasta pizza planet
    arregloCaminos[idBencineraConMenorTiempo].camino;
 
    *numeroTotalNodos = numeroNodosCamino + arregloCaminos[idArregloBencineraConMenorTiempo].numeroNodos;
    //Se generara un arreglo con el camino Final
    int  *arregloCaminoFinal = (int*)malloc(sizeof(int)* *numeroTotalNodos);
    k = 0;
    //Se agrega el recorrido desde la tierra hasta la gasolinera
    for(int i = numeroNodosCamino-1; i >= 0 ; i--){
        arregloCaminoFinal[k] = recorridoMasCortoGasolinera[i];
        k = k + 1;
    }
    //Se agrega el recorrido desde la gasolinera hasta pizza planet
    for(int i = arregloCaminos[idArregloBencineraConMenorTiempo].numeroNodos-2; i >= 0; i--){
        arregloCaminoFinal[k] = arregloCaminos[idArregloBencineraConMenorTiempo].camino[i];
        k = k + 1;
    }
    //Finalmente se retorna el recorrido del camino mas corto
    *numeroTotalNodos = *numeroTotalNodos -1;
    *tiempoMasCorto = menorTiempo;
    return arregloCaminoFinal;
    
}

//Entrada: Arreglo que contiene el camino a seguir, Entero con la cantidad de nodos del recorrido a seguir, Entero con el tiempo que toma el recorrido, Entero con la cantidad de aristas del grafo y el arreglo de Aristas
//Salida: 
//Objetivo: Generar el archivo "ruta.out" con el camino mas corto desde la tierra a pizza planet
void crearArchivoSalida(int * caminoFinal, int numNodosRecorrido, int tiempoMasCorto, int cantidadAristas, conexion * infoAristas){
    //En primer lugar se define un archivo de salida
    FILE * salida;
    //Se define una variable que almacenara a los nombres de los id
    char nombreId[500];
    //Se abre el archivo de salida en modo de escritura y se le asigna el nombre ruta.out
    salida = fopen("ruta.out", "w");
    fprintf(salida,"%d\n",tiempoMasCorto);
    for(int i = 0; i < numNodosRecorrido; i++){
        //En primer lugar se busca el nombre del id a escribir en la informacion de las aristas
        for(int j = 0; j < cantidadAristas; j++){
            //Si se encuentran ids que sean iguales
            if(caminoFinal[i] == infoAristas[j].idInicio){
                //Se consigue el nombre de la parada y se almacena en el id
                strcpy(nombreId,infoAristas[j].nombreInicio);
            }
        }
        //Si es la ultima iteracion:
        if(i+1 == numNodosRecorrido){
            fprintf(salida,"%s",nombreId);
        } else {
            fprintf(salida,"%s->",nombreId);
        }
    }
    //Finalmente se cierra el documento, debido a que ya se escribio toda la información necesaria
    fclose(salida);
}

//Funcion principal
int main(int argc, char* argv[]){
    //Para empezar se leera el archivo de artistas
    FILE* archivoArtistas = leerArchivo(argv[1]);
    //Si la funcion leerArchivo devuelve un 0 es porque el archivo no existe o el nombre fue mal ingresado.
    if(archivoArtistas == 0){
        printf("Algo fallo, verifique el nombre del archivo por favor, debe ser mapa.in\n");
        return 0;
    }
    // A continuacion se conseguira el numero de nodos:
    int numeroNodos;
    fscanf(archivoArtistas,"%d",&numeroNodos);
    //Luego que se tiene la cantidad de nodos se leeran las aristas junto a sus propiedades
    //la cantidad maxima de aristas que puede existir en un grafo no dirigido como el del problema es de n*(n-1)
    int cantidadMaximaAristas = numeroNodos*(numeroNodos-1);
    //cantidadAristas almacenara la cantidad de aristas presentes en el archivo
    int cantidadAristas = 0;
    //A continuacion se consigue toda la informacion del documento
    conexion * informacionAristas = almacenarInformacionAristas(archivoArtistas,cantidadMaximaAristas,&cantidadAristas);
    //Se cierra el archivo debido a que se encuentra toda su informacion almacenada
    fclose(archivoArtistas);
    //printAristas(informacionAristas,&cantidadAristas);
    //Ahora se procedera a crear los nodos y el grafo 
    informacionAristas = crearIds(informacionAristas,&cantidadAristas);
    printAristas(informacionAristas,&cantidadAristas);
    //Se inicializa la matriz de adyacencia
    nodo matriz[numeroNodos][numeroNodos];
    iniciarMatriz(numeroNodos,matriz);
    agregarInfoNodos(informacionAristas,&cantidadAristas,numeroNodos,matriz);
    //A continuacion se leera el segundo archivo
    FILE* archivoCombustible = leerArchivo(argv[2]);
    //Si la funcion leerArchivo devuelve un 0 es porque el archivo no existe o el nombre fue mal ingresado.
    if(archivoCombustible == 0){
        printf("Algo fallo, verifique el nombre del archivo por favor, debe ser combustible.in \n");
        return 0;
    }
    int cantidadCombustible;
    //Se leera y almacenara la cantidad inicial de combustible disponible
    fscanf(archivoCombustible,"%d",&cantidadCombustible);
    int cantidadGasolineras = 0;
    nodo * gasolineras = leerGasolineras(archivoCombustible,numeroNodos,&cantidadGasolineras);
    //Se cerrara el archivo, ya que se almaceno toda su informacion
    fclose(archivoCombustible);
    //Una vez cerrado el documento se debe agregar los nodos que son gasolineras a la matriz de adyacencia
    agregarGasolineras(numeroNodos,matriz,gasolineras,&cantidadGasolineras);
    printf("\nMatriz:\n");
    printearMatriz(numeroNodos,matriz);
    recorrido camino = dijkstra(numeroNodos,matriz,0);
    int numeroNodosCamino = 0;
    int * recorrido = guardarCamino(0,6,camino.padre,numeroNodos,&numeroNodosCamino);
    int numNodosRecorrido = 0;
    int tiempoMasCorto = 0;
    int * caminoFinal = conseguirCaminoMasCorto(numeroNodos,cantidadCombustible,&cantidadGasolineras,matriz,&numNodosRecorrido,&tiempoMasCorto);
    crearArchivoSalida(caminoFinal,numNodosRecorrido,tiempoMasCorto,cantidadAristas,informacionAristas);
    printf("\nArchivo generado!\n");
    return 0;
}
