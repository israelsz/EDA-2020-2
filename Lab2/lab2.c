//Importacion de librerias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Se define un struct cancion
typedef struct cancion cancion;

//Cada cancion tendra las siguientes caracteristicas:
struct cancion{
    char nombreCancion[60];
    int duracionMinutos;
    int duracionSegundos;
    int idArtista;
    int idGenero;
    int popularidad;
};

//Se define un struct artista
typedef struct artista artista;

//Cada artista tiene las siguientes caracteristicas:
struct artista{
    int idArtista;
    char nombreArtista[60];
};

//Se define un struct género
typedef struct genero genero;

//Cada genero tiene las siguientes caracteristicas:
struct genero{
    int idGenero;
    char nombreGenero[60];
};

//TDA Lista Enlazada
typedef struct nodo nodo;

struct nodo{
	cancion cancion;
    artista artista;
    genero genero;
    int preferencia;
	struct nodo *sig; //puntero al siguiente nodo en la lista
};

// TDA Cola mediante lista enlazada
typedef struct cola cola;
struct cola { 
    nodo *inicio;
    nodo *final; 
}; 


//A continuacion las operaciones del TDA lista enlazada:

//Entrada: Ninguna.
//Salida: Un nodo.
//Objetivo: Crea un nuevo nodo que luego podra ser agregado en la lista enlazada.
nodo *crearNodo(){

	nodo *aux;
	
	aux = (nodo *)malloc(sizeof(nodo)); //asigna memoria al nodo
	aux->sig = NULL;			//apunta el siguiente a nulo
	return aux;
}

/* Las siguientes funciones dentro del comentario no forman parte de la creacion de la solucion, pero sirvieron para debuguear la misma.

//Entrada: El puntero al inicio de la lista enlazada.
//Salida: Ninguna.
//Objetivo: Muestra por pantalla la lista enlazada.
void mostrarListaArtistas(nodo *lista){
	nodo *aux;
	
	aux = lista; 	//variable auxiliar para recorrer la lista
	while(aux != NULL){ 	//no se haya llegado al final de la lista
		printf("%d / %s - ", aux->artista.idArtista, aux->artista.nombreArtista);
		aux = aux->sig;		//avanza al siguiente elemento de la lista
	}
}

//Entrada: El puntero al inicio de la lista enlazada.
//Salida: Ninguna.
//Objetivo: Muestra por pantalla la lista enlazada.
void mostrarListaGeneros(nodo *lista){
	nodo *aux;
	
	aux = lista; 	//variable auxiliar para recorrer la lista
	while(aux != NULL){ 	//no se haya llegado al final de la lista
		printf("%d / %s - ", aux->genero.idGenero, aux->genero.nombreGenero);
		aux = aux->sig;		//avanza al siguiente elemento de la lista
	}
}

//Entrada: El puntero al inicio de la lista enlazada.
//Salida: Ninguna.
//Objetivo: Muestra por pantalla la lista enlazada.
void mostrarListaCanciones(nodo *lista){
	nodo *aux;
	
	aux = lista; 	//variable auxiliar para recorrer la lista
	while(aux != NULL){ 	//no se haya llegado al final de la lista
		printf("%s / %d:%d / %d / %d / %d - ", aux->cancion.nombreCancion,aux->cancion.duracionMinutos,aux->cancion.duracionSegundos,aux->cancion.idArtista,aux->cancion.idGenero,aux->cancion.popularidad);
		aux = aux->sig;		//avanza al siguiente elemento de la lista
	}
}

//Entrada: El puntero al inicio de la lista enlazada.
//Salida: Ninguna.
//Objetivo: Muestra por pantalla la lista enlazada.
void mostrarListaPreferencias(nodo *lista){
	nodo *aux;
	
	aux = lista; 	//variable auxiliar para recorrer la lista
	while(aux != NULL){ 	//no se haya llegado al final de la lista
		printf("%d-",aux->preferencia);
		aux = aux->sig;		//avanza al siguiente elemento de la lista
	}
}

//Entrada: El puntero al inicio de la lista enlazada.
//Salida: Ninguna.
//Objetivo: Muestra por pantalla la lista enlazada.
void mostrarListaPlaylist(nodo *lista){
	nodo *aux;
	
	aux = lista; 	//variable auxiliar para recorrer la lista
	while(aux != NULL){ 	//no se haya llegado al final de la lista
        if(aux->sig == NULL){
            printf("%d:%d\n",aux->cancion.duracionMinutos,aux->cancion.duracionSegundos);
            aux = aux->sig;
        } else {
            printf("%s / %d:%d / %d / %d / %d - ", aux->cancion.nombreCancion,aux->cancion.duracionMinutos,aux->cancion.duracionSegundos,aux->cancion.idArtista,aux->cancion.idGenero,aux->cancion.popularidad);
		    aux = aux->sig;		//avanza al siguiente elemento de la lista
        }
	}
}

//Entrada: El puntero al inicio de la lista enlazada.
//Salida: Ninguna.
//Objetivo: Muestra por pantalla la lista enlazada.
void mostrarCola(cola*Q){
	nodo *aux;
	
	aux = Q->inicio; 	//variable auxiliar para recorrer la cola
	while(aux != NULL){ 	//no se haya llegado al final de la Cola
		printf("%d-",aux->preferencia);
		aux = aux->sig;		//avanza al siguiente elemento de la cola
	}
}

*/

//Entrada: El puntero al inicio de la lista enlazada, un entero id.
//Salida: El puntero al nodo encontrado.
//Objetivo: Busca un nodo segun su id de genero.
nodo *encontrarArtistaPorId(nodo *lista, int id){
    nodo* aux;
    aux = lista;
    while(aux != NULL){
        if(aux->artista.idArtista == id){
            return aux; //Retorna el puntero del dato buscado
        }
        aux = aux->sig;
    }
    return NULL; //No se encontro el dato
}

//Entrada: El puntero al inicio de la lista enlazada, un entero id.
//Salida: El puntero al nodo encontrado.
//Objetivo: Busca un nodo segun su id de genero.
nodo *encontrarGeneroPorId(nodo *lista, int id){
    nodo* aux;
    aux = lista;
    while(aux != NULL){
        if(aux->genero.idGenero == id){
            return aux; //Retorna el puntero del dato buscado
        }
        aux = aux->sig;
    }
    return NULL; //No se encontro el dato
}

//Entrada: El puntero al inicio de la lista enlazada, un dato artista.
//Salida: Una nueva lista enlazada.
//Objetivo: Agrega al final de la lista enlazada un nuevo nodo con un dato.
nodo *agregarFinalListaArtistas(nodo* lista , artista artista){
    nodo *aux;
    aux = lista;
    //En caso de que no existan elementos dentro de la lista:
    if(aux == NULL){
        nodo* nuevo;
        nuevo = crearNodo();
	    nuevo->artista = artista;
	    nuevo->sig = lista;
	    return nuevo;
    }
    nodo *nuevo;
    nuevo = crearNodo();
    nuevo->artista = artista;
    while(aux->sig != NULL){
        aux = aux->sig;
    }
    nuevo->sig = NULL;
    aux->sig = nuevo;
    return lista;
}

//Entrada: El puntero al inicio de la lista enlazada, un dato genero.
//Salida: Una nueva lista enlazada.
//Objetivo: Agrega al final de la lista enlazada un nuevo nodo con un dato.
nodo *agregarFinalListaGeneros(nodo* lista ,genero genero){
    nodo *aux;
    aux = lista;
    //En caso de que no existan elementos dentro de la lista:
    if(aux == NULL){
        nodo* nuevo;
        nuevo = crearNodo();
	    nuevo->genero = genero;
	    nuevo->sig = lista;
	    return nuevo;
    }
    nodo *nuevo;
    nuevo = crearNodo();
    nuevo->genero = genero;
    while(aux->sig != NULL){
        aux = aux->sig;
    }
    nuevo->sig = NULL;
    aux->sig = nuevo;
    return lista;
}

//Entrada: El puntero al inicio de la lista enlazada, un dato cancion.
//Salida: Una nueva lista enlazada.
//Objetivo: Agrega al final de la lista enlazada un nuevo nodo con un dato.
nodo *agregarFinalListaCanciones(nodo* lista ,cancion cancion){
    nodo *aux;
    aux = lista;
    //En caso de que no existan elementos dentro de la lista:
    if(aux == NULL){
        nodo* nuevo;
        nuevo = crearNodo();
	    nuevo->cancion = cancion;
	    nuevo->sig = lista;
	    return nuevo;
    }
    nodo *nuevo;
    nuevo = crearNodo();
    nuevo->cancion= cancion;
    while(aux->sig != NULL){
        aux = aux->sig;
    }
    nuevo->sig = NULL;
    aux->sig = nuevo;
    return lista;
}

//Entrada: El puntero al inicio de la lista enlazada.
//Salida: Una nueva lista enlazada.
//Objetivo: Elimina el primer elemento de la lista enlazada.
nodo *eliminarPrimero (nodo* lista){
    nodo* aux;
    aux = lista;
    lista = lista->sig;
    free(aux);
    return lista;
}


//Entrada: El puntero al inicio de la lista enlazada.
//Salida: un entero, con la cantidad de datos de la lista.
//Objetivo: retorna la cantidad de nodos de la lista enlazada.
int longitud_lista_enlazada(nodo* lista){
    nodo *aux;
    int contador = 0;
	aux = lista; 	//variable auxiliar para recorrer la lista
	while(aux != NULL){ 	//no se haya llegado al final de la lista
		contador = contador + 1;
		aux = aux->sig;		//avanza al siguiente elemento de la lista
	}
    return contador;
}

//Entrada: El puntero al inicio de la lista enlazada, un entero posicion.
//Salida: Una nueva lista enlazada.
//Objetivo: Elimina una posicion de la lista enlazada.
nodo *eliminar_nodo_posicion(nodo* lista, int posicion){
    nodo *aux;
    aux = lista; 
    int contador = 1;
    while(contador != posicion-1){
        aux = aux->sig; //Avanza al siguiente elemento de la lista, hasta llegar a la posicion antes de la mitad
        contador = contador+1;
    }
    nodo* aux1 = aux->sig; //La posicion pedida a liberar
    aux->sig = aux1->sig; //Se conecta el nodo al siguiente del nodo a eliminar
    free(aux1); //Se elimina el nodo
    return(lista); //Se retorna la lista actualizada
}


//Funciones del TDA cola:

//Entrada: Ninguna.
//Salida: Una cola.
//Objetivo: Crear una nueva cola vacia.
cola* crearCola(){ 
    cola* Q = (cola*)malloc(sizeof(cola)); 
    Q->inicio = Q->final = NULL; 
    return Q; 
} 


//Entrada: Una cola, un entero.
//Salida: Una cola con el elemento insertado.
//Objetivo: Encolar un elemento a la cola.
void encolar(cola* Q, int preferencia) { 
    // Se crea un nuevo nodo a insertar
    nodo* temporal = crearNodo(); 
    //Se le asigna el dato
    temporal->preferencia = preferencia;

    // Si la cola esta vacia el inicio sera igual al final:
    if (Q->final == NULL) { 
        Q->inicio = Q->final = temporal; 
        return;
    } 
  
    // Se encola el elemento al final de la cola
    Q->final->sig = temporal; 
    Q->final = temporal; 
} 

//Entrada: Una cola.
//Salida: El elemento eliminado de la cola.
//Objetivo: Sacar el primer elemento de la cola, retornandolo para su uso.
int desencolar(cola* Q) { 
    int dato;

    // Si la cola esta vacia, retorna null
    if (Q->inicio == NULL) 
        return -1; 
    
    //Se guarda el inicio anterior
    nodo* temporal = Q->inicio; 
    //Se almacena el dato que contiene el nodo de inicio de la cola
    dato = temporal->preferencia;
    //Se mueve el inicio a la siguiente posicion
    Q->inicio = Q->inicio->sig; 
  
    // Si el inicio pasa a ser nulo, entonces el final igual debe serlo
    if (Q->inicio == NULL) 
        Q->final = NULL; 
    
    //Se libera el nodo desencolado
    free(temporal); 
    //Se retorna el dato desencolado
    return(dato);
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

//Entrada: Un archivo, un puntero al inicio de la lista enlazada.
//Salida: la lista enlazada con los elementos agregados.
//Objetivo: Lee el archivo y almacena cada id y nombre de artista a la lista enlazada.
nodo* leerYAlmacenarArtistas(FILE* archivoArtistas,nodo* listaArtistas){
    int cantidadArtistas;
    char nombreArtistaAuxiliar[60];
    //Se usara la funcion fscanf para leer y almacenar el primer valor que correspondera a la cantidad de artistas
    fscanf(archivoArtistas,"%d",&cantidadArtistas);
    //A continuacion con un ciclo se almacenara el id y nombre de cada artista
    for(int i = 0;i<cantidadArtistas;i++){
        //En primer lugar se crea un tipo de dato artista
        artista nuevoArtista;
        //Se lee y almacena el id del artista en la struct
        fscanf(archivoArtistas,"%d",&nuevoArtista.idArtista);
        //A continuacion se lee y almacena el nombre del artista en la variable axiliar
        fscanf(archivoArtistas,"%s",&nombreArtistaAuxiliar);
        //Se almacena el nombre en el struct
        strcpy(nuevoArtista.nombreArtista,nombreArtistaAuxiliar);
        //Se agrega el tipo de dato artista a la lista enlazada
        listaArtistas = agregarFinalListaArtistas(listaArtistas,nuevoArtista);
    }
    //Una vez agregados todos los artistas se retorna la lista con todos los artistas agregados
    return listaArtistas;
}

//Entrada: Un archivo, un puntero al inicio de la lista enlazada.
//Salida: la lista enlazada con los elementos agregados.
//Objetivo: Lee el archivo y almacena cada id y nombre de los generos a la lista enlazada.
nodo* leerYAlmacenarGeneros(FILE* archivoGeneros,nodo* listaGeneros){
    int cantidadGeneros;
    char nombreGeneroAuxiliar[60];
    //Se usara la funcion fscanf para leer y almacenar el primer valor que correspondera a la cantidad de generos
    fscanf(archivoGeneros,"%d",&cantidadGeneros);
    //A continuacion con un ciclo se almacenara el id y nombre de cada artista
    for(int i = 0;i<cantidadGeneros;i++){
        //En primer lugar se crea un tipo de dato artista
        genero nuevoGenero;
        //Se lee y almacena el id del artista en la struct
        fscanf(archivoGeneros,"%d",&nuevoGenero.idGenero);
        //A continuacion se lee y almacena el nombre del artista en la variable axiliar
        fscanf(archivoGeneros,"%s",&nombreGeneroAuxiliar);
        //Se almacena el nombre en el struct
        strcpy(nuevoGenero.nombreGenero,nombreGeneroAuxiliar);
        //Se agrega el tipo de dato artista a la lista enlazada
        listaGeneros = agregarFinalListaGeneros(listaGeneros,nuevoGenero);
    }
    //Una vez agregados todos los artistas se retorna la lista con todos los artistas agregados
    return listaGeneros;
}

//Entrada: Un archivo, un puntero al inicio de la lista enlazada.
//Salida: la lista enlazada con los elementos agregados.
//Objetivo: Lee el archivo y almacena cada id y nombre de los generos a la lista enlazada.
nodo* leerYAlmacenarCanciones(FILE* archivoCanciones,nodo* listaCanciones){
    int cantidadCanciones;
    char nombreCancionAuxiliar[60];
    char duracionCancion[60];
    //Se usara la funcion fscanf para leer y almacenar el primer valor que correspondera a la cantidad de generos
    fscanf(archivoCanciones,"%d",&cantidadCanciones);
    //A continuacion con un ciclo se almacenara el id y nombre de cada artista
    for(int i = 0;i<cantidadCanciones;i++){
        //En primer lugar se crea un tipo de dato cancion
        cancion nuevaCancion;
        //Se lee y almacena la duracion, id de Artista, id de Genero y popularidad en la struct, el nombre se almacena en la variable auxiliar
        fscanf(archivoCanciones,"%s %s %d %d %d ",&nombreCancionAuxiliar,&duracionCancion,&nuevaCancion.idArtista,&nuevaCancion.idGenero,&nuevaCancion.popularidad);
        //A continuacion se lee y almacena el nombre de la cancion en la struct
        strcpy(nuevaCancion.nombreCancion,nombreCancionAuxiliar);
        //Ya que la duracion fue leida como una string a continuacion se separara para poder ser almacenada como entero
        char *duracion = strtok(duracionCancion,":");
        char minutos[5];
        char segundos[3];
        //Se copian los minutos como string
        strcpy(minutos,duracion);
        duracion = strtok(NULL,":");
        strcpy(segundos,duracion);
        nuevaCancion.duracionMinutos = atoi(minutos);
        nuevaCancion.duracionSegundos = atoi(segundos);
        //Se agrega el tipo de dato cancion a la lista enlazada
        listaCanciones = agregarFinalListaCanciones(listaCanciones,nuevaCancion);
    }
    //Una vez agregados todos los artistas se retorna la lista con todos los artistas agregados
    return listaCanciones;
}

//Entrada: Un archivo, un puntero al inicio de la lista enlazada.
//Salida: la lista enlazada con los elementos agregados.
//Objetivo: Lee el archivo y almacenar cada id los generos a la lista enlazada.
cola* leerYAlmacenarPreferencias(FILE* archivoPreferencias,cola* colaPreferencias){
    int numeroPreferencia;
    //Se leera y almacenara las distintas preferencias
    //Se detendra automaticamente cuando no sea posible seguir leyendo el documento.
    while(fscanf(archivoPreferencias,"%d",&numeroPreferencia) == 1){
        encolar(colaPreferencias,numeroPreferencia);
    }
    //Una vez agregadas todas las preferencias a la cola se retorna la cola
    return colaPreferencias;
}

//Entrada: Dos nodos provenientes de una lista enlazada.
//Salida: Ninguna.
//Objetivo: Efectuar un swap entre los datos de los dos nodos entrantes.
void swapCanciones(nodo* nodo1, nodo* nodo2){ 
    //No se intercambiaran los nodos directamente, para evitar reconectar punteros
    //Se intercambiaran los datos que cada nodo tiene almacenado, en este caso son canciones
    //Se crea una variable auxiliar para almacenar los datos de la cancion del nodo 1
    cancion auxiliar;
    //Se intercambian los datos de las canciones
    auxiliar = nodo1->cancion;
    nodo1->cancion = nodo2->cancion;
    nodo2->cancion = auxiliar;
} 

//Entrada: El arreglo con combinaciones y la cantidad de combinaciones que contiene.
//Salida: Ninguna.
//Objetivo: Ordenar el arreglo respecto a la calificacion de mayor a menor, haciendo uso de BubbleSort.
nodo* ordenarListaCancionesPorPopularidad(nodo* listaCanciones,int longitudListaCanciones){
    for(int i = 0; i < longitudListaCanciones-1; i++){
        nodo* auxiliar1 = listaCanciones; //Se crea un nodo auxiliar apuntando al inicio de la lista enlazada
        nodo* auxiliar2 = auxiliar1->sig; //El segundo nodo auxiliar apuntara al nodo siguiente del que apunte auxiliar1

        //Los ultimos i elementos ya se encuentran ordenados
        for(int j = 0; j < longitudListaCanciones-i-1; j++){
            //Si la popularidad de la cancion de la posicion actual es menor a la de la siguiente posicion
            if (auxiliar1->cancion.popularidad < auxiliar2->cancion.popularidad){
                //Se intercambian los nodos
                swapCanciones(auxiliar1, auxiliar2);
            }
            //Se avanza a la siguiente posicion
            auxiliar1 = auxiliar2;
            auxiliar2 = auxiliar2->sig;
        }
    }
    return listaCanciones;
}

//Entrada: El arreglo con combinaciones y la cantidad de combinaciones que contiene.
//Salida: Ninguna.
//Objetivo: Ordenar el arreglo respecto a la calificacion de mayor a menor, haciendo uso de BubbleSort.
nodo* ordenarListaCancionesMismaPopularidad(nodo* listaCanciones,int longitudListaCanciones,nodo* listaArtistas){
    for(int i = 0; i < longitudListaCanciones-1; i++){
        nodo* auxiliar1 = listaCanciones; //Se crea un nodo auxiliar apuntando al inicio de la lista enlazada
        nodo* auxiliar2 = auxiliar1->sig; //El segundo nodo auxiliar apuntara al nodo siguiente del que apunte auxiliar1

        //Los ultimos i elementos ya se encuentran ordenados
        for(int j = 0; j < longitudListaCanciones-i-1; j++){
            //Si la popularidad de la cancion de la posicion actual es igual a la de la siguiente posicion
            if (auxiliar1->cancion.popularidad == auxiliar2->cancion.popularidad){
                //Se verifica si tienen el mismo artista o no
                if(auxiliar1->cancion.idArtista == auxiliar2->cancion.idArtista){
                    //Si tienen el mismo artista, la cancion que va primera es la cancion con menor duracion
                    //Se obtiene la duracion en segundos de cada cancion
                    int duracionCancion1 = ((auxiliar1->cancion.duracionMinutos*60)+auxiliar1->cancion.duracionSegundos);
                    int duracionCancion2 = ((auxiliar2->cancion.duracionMinutos*60)+auxiliar2->cancion.duracionSegundos);
                    //Si la duracion de la primera cancion es mayor a la segunda
                    //Si no es mayor no se hara nada, debido a que ya se encuentran ordenada
                    if(duracionCancion1 > duracionCancion2){
                        //Se intercambian sus posiciones
                        swapCanciones(auxiliar1,auxiliar2);
                    }
                } else{
                    //No tienen el mismo artista, entonces la cancion que va primera es segun orden alfabetico
                    //Se consigue el nodo del artista de la primera cancion, segun su id buscandola en la listaArtistas
                    nodo* artista1 = encontrarArtistaPorId(listaArtistas,auxiliar1->cancion.idArtista);
                    nodo* artista2 = encontrarArtistaPorId(listaArtistas,auxiliar2->cancion.idArtista);
                    //Se comparan los nombres de los artistas usando strcmp
                    //En caso de cumplirse la condicion significa que se debe aplicar un intercambio
                    if(strcmp(artista1->artista.nombreArtista,artista2->artista.nombreArtista) > 0){
                        swapCanciones(auxiliar1,auxiliar2);
                    }
                }
            }
            //Se avanza a la siguiente posicion
            auxiliar1 = auxiliar2;
            auxiliar2 = auxiliar2->sig;
        }
    }
    return listaCanciones;
}


//Entrada: una cola vacia, la lista enlazada con canciones, la cola con preferencias, los enteros minutos y segundos requeridos para la playlist.
//Salida: Una cola con todo el orden de la playlist incluyendo el tiempo restante en caso de existir.
//Objetivo: Crear la playlist a traves de una cola,las canciones dadas y las preferencias requeridas.
nodo* crearPlaylist(nodo* listaPlaylist,nodo* listaCanciones,cola* colaPreferencias,int playlistMinutos,int playlistSegundos){
    //Para poder crear la playlist se hara uso de encolar y desencolar la cola de preferencias
    //la primera cancion que se encuentre del genero desencolado, en caso de haber encontrado una cancion, se volvera a encolar
    //la preferencia en la cola de preferencias, en caso de no encontrar la cancion no se agregara ni la cancion ni la preferencia.
    //con cada cancion agregada a la lista se verificara si se excede o no el tiempo de la playlist.

    //En primer lugar se transformara a segundos el tiempo total de la playlist
    int segundosRequeridosPlaylist = ((playlistMinutos*60)+playlistSegundos);
    //La variable segundosActuales llevara el tiempo total que se lleve en la playlist actual
    int segundosActuales = 0;
    //Se desencola la primera preferencia
    int preferenciaActual = desencolar(colaPreferencias);
    //Se llevara cuenta de la duracion de la cancion actual
    int duracionCancion;
    //Se llevara la cuenta de la posicion de los nodos
    int contador = 1;
    int romperCiclo;
    //Se desencolara hasta que la cola de preferencias se encuentre vacia o hasta que la sumatoria de tiempo exceda la solicitada
    while(preferenciaActual != -1 && segundosActuales < segundosRequeridosPlaylist){
        //Se buscara la primera cancion que se encuentre en la listaCanciones que sea igual a la preferencia desencolada
        nodo* auxiliar = listaCanciones;
        contador = 1;
        //Se avanzara en la lista hasta encontrar el nodo que tenga la misma preferencia en la cancion
        while((auxiliar->cancion.idGenero != preferenciaActual)){
            if(auxiliar->sig == NULL){
                romperCiclo = 1;
                break;
            }
            auxiliar = auxiliar->sig;
            contador = contador+1;
            romperCiclo = 0;
        }
        //Si se encontro una cancion, se agrega
        if(romperCiclo == 0){
            //Una vez se tiene el nodo, se verifica su duracion
            duracionCancion = ((auxiliar->cancion.duracionMinutos*60)+auxiliar->cancion.duracionSegundos);
            //Se suma el tiempo al actual de la playlist
            segundosActuales = segundosActuales+duracionCancion;
            //Se hace una copia de todos los datos de la cancion en una variable auxiliar
            cancion cancionAuxiliar = auxiliar->cancion;
            //Se agrega a la lista la cancion encontrada
            listaPlaylist = agregarFinalListaCanciones(listaPlaylist,cancionAuxiliar);
            //Como se agrego una cancion de ese genero, se volvera a encolar la preferencia
            encolar(colaPreferencias,preferenciaActual);
            //Se borrara la cancion agregada de la listaCanciones, debido a que se agrego a la playlist:
            if(contador == 1){
                listaCanciones = eliminarPrimero(listaCanciones);
            } else {
                listaCanciones = eliminar_nodo_posicion(listaCanciones,contador);
            }
            //se pasara a la siguiente preferencia
            preferenciaActual = desencolar(colaPreferencias);
        } else {
            //ya que no se encontro una cancion, se desencola la siguiente preferencia
            preferenciaActual = desencolar(colaPreferencias);  
        }
    }
    //Una vez roto el ciclo se debe verificar si fue por que se quedo sin canciones por desencolar o si fue por exceder los segundos de la playlist
    //Si la cola esta vacia
    if(preferenciaActual == -1){
        //Se verifica si aun es posible agregar canciones a la playlist
        if(segundosActuales < segundosRequeridosPlaylist){
            //Al aun poder agregar canciones, pero no haber mas combinaciones por nombre se debe repetir el orden ya hecho hasta dar con el tiempo maximo
            //Se hace un nodo auxiliar apuntando al inicio de la playlist
            nodo* temporal = listaPlaylist;
            //Mientras no se exceda la cantidad de tiempo requerido
            while(segundosActuales < segundosRequeridosPlaylist){
                //Se copia la cancion
                cancion cancionTemporal = temporal->cancion;
                //Se agrega la cancion al final
                agregarFinalListaCanciones(listaPlaylist,cancionTemporal);
                //Se consigue la duracion de la cancion agregada
                duracionCancion = ((cancionTemporal.duracionMinutos*60)+cancionTemporal.duracionSegundos);
                //Se agrega la duracion de la cancion a la variable auxiliar
                segundosActuales = segundosActuales + duracionCancion;
                //Si el siguiente elemento es null, se vuelve al inicio de la playlist
                if(temporal->sig == NULL){
                    temporal = listaPlaylist;
                } else{
                    //En caso de no ser nulo, se avanza al siguiente elemento
                    temporal = temporal->sig;
                }
            }
        }
    }
    //se debe calcular el tiempo sobrante entre el solicitado y el de la ultima cancion
    int segundosSobrantes = segundosActuales-segundosRequeridosPlaylist;
    //Si no sobra tiempo
    if(segundosSobrantes == 0){
        cancion tiempo;
        tiempo.duracionMinutos = 0;
        tiempo.duracionSegundos = 0;
        listaPlaylist = agregarFinalListaCanciones(listaPlaylist,tiempo);
        return listaPlaylist;
    }
    //En caso de sobrar tiempo
    //Se calculara el tiempo sobrante de la cancion, para eso a la duracion de la cancion se debe restar los segundosSobrante
    int segundosCancionSobrantes = duracionCancion - segundosSobrantes;
    //Ahora se calculara en que tiempo debe cortarse la grabacion
    int cortarCancion = duracionCancion - segundosCancionSobrantes;
    //Se transformara a minutos y segundos el tiempo de corte de la ultima cancion:
    int minutoSobrante = (cortarCancion%3600)/60;
    int segundoSobrante = (cortarCancion%3600)%60;
    //Se creara una cancion auxiliar, la cual solo tendra el tiempo restante
    cancion tiempo;
    tiempo.duracionMinutos = minutoSobrante;
    tiempo.duracionSegundos = segundoSobrante;
    //Se agrega el tiempo restante al final de la lista
    listaPlaylist = agregarFinalListaCanciones(listaPlaylist,tiempo);
    //Se retorna la lista con la playlist creada
    return listaPlaylist;
}

//Entrada: la lista enlazada con canciones, la lista enlazada con artistas y la lista enlazada con generos.
//Salida: Ninguna.
//Objetivo: generar el archivo salida.out el cual contiene las canciones ordenadas segun popularidad
void crearArchivoSalida(nodo* listaCanciones,nodo* listaArtistas,nodo* listaGeneros){
    FILE * salida; //Se define un archivo salida
    salida = fopen("salida.out", "w"); //Se abre el archivo salida en modo de escritura y se le asigna el nombre salida.out
    //Se define un nodo auxiliar para recorrer la lista de canciones
    nodo* auxiliar;
    auxiliar = listaCanciones;
    //Mientras no se este en el final de la lista enlazada de canciones
    while(auxiliar != NULL){
        //Se consiguen los nodos de artista y genero para esta cancion
        nodo* artista = encontrarArtistaPorId(listaArtistas,auxiliar->cancion.idArtista);
        nodo* genero = encontrarGeneroPorId(listaGeneros,auxiliar->cancion.idGenero);
        //Se escribe en el documento
        fprintf(salida,"%d;%s;%d:%02d;%s;%s\n",auxiliar->cancion.popularidad,auxiliar->cancion.nombreCancion,auxiliar->cancion.duracionMinutos,auxiliar->cancion.duracionSegundos,artista->artista.nombreArtista,genero->genero.nombreGenero);
        //Se avanza a la siguiente posicion de la lista enlazada de canciones
        auxiliar = auxiliar->sig;
    }
    //Una vez escrito el archivo se cerrara
    fclose(salida);
}

//Entrada: la lista enlazada con canciones de la playlist, la lista enlazada con artistas y la lista enlazada con generos.
//Salida: Ninguna.
//Objetivo: generar el archivo playlist.out el cual contiene las canciones para la playlist segun lo requerido.
void crearArchivoSalidaPlaylist(nodo* listaPlaylist,nodo* listaArtistas,nodo* listaGeneros){
    //En primer lugar se define un archivo de salida
    FILE * salidaPlaylist;
    //Se abre el archivo de salida en modo de escritura y se le asigna el nombre playlist.out
    salidaPlaylist = fopen("playlist.out", "w");
    //Se define un nodo auxiliar para recorrer la lista enlazada playlist
    nodo* auxiliar;
    auxiliar = listaPlaylist;
    //Mientras no se haya llegado al ultimo elemento de la lista enlazada de la playlist
    while(auxiliar->sig != NULL){
        //Se consiguen los nodos de artista y genero para esta cancion
        nodo* artista = encontrarArtistaPorId(listaArtistas,auxiliar->cancion.idArtista);
        nodo* genero = encontrarGeneroPorId(listaGeneros,auxiliar->cancion.idGenero);
        //Se escribe en el documento los datos de la cancion
        fprintf(salidaPlaylist,"%d;%s;%d:%02d;%s;%s\n",auxiliar->cancion.popularidad,auxiliar->cancion.nombreCancion,auxiliar->cancion.duracionMinutos,auxiliar->cancion.duracionSegundos,artista->artista.nombreArtista,genero->genero.nombreGenero);
        //Se avanza a la siguiente posicion de la lista enlazada de playlist
        auxiliar = auxiliar->sig;
    }
    //Una vez escrita la playlist y como el ciclo se detiene en la ultima posicion, la ultima posicion de la lista enlazada contiene los minutos y segundos sobrantes
    //de la ultima cancion de la playlist de acuerdo al tiempo inicialmente requerido
    fprintf(salidaPlaylist,"%d:%02d\n",auxiliar->cancion.duracionMinutos,auxiliar->cancion.duracionSegundos);
    //El archivo de la playlist se encuentra listo, entonces se cierra
    fclose(salidaPlaylist);
}

//Entrada: Una lista enlazada.
//Salida: Ninguna.
//Objetivo: Liberar la memoria de una lista enlazada.
void liberarListaEnlazada(nodo* lista){
    nodo* temporal;
    while (lista != NULL){
        temporal = lista;
        lista = lista->sig;
        free(temporal);
    }
    free(lista);
}

//Entrada: Una cola.
//Salida: Ninguna.
//Objetivo: Liberar la memoria de una cola.
void liberarCola(cola* cola){
    nodo* temporal;
    nodo* temporal2;
    temporal = cola->inicio;
    while (temporal != NULL){
        temporal2 = temporal->sig;
        free(temporal);
        temporal = temporal2;
    }
    free(temporal);
}

int main(){
    //Para empezar se leera el archivo de artistas
    FILE* archivoArtistas = leerArchivo("artistas.in");
    //Si la funcion leerArchivo devuelve un 0 es porque el archivo no existe o el nombre fue mal ingresado.
    if(archivoArtistas == 0){
        printf("Algo fallo, verifique el nombre del archivo por favor\n");
        return 0;
    }
    //Se define una lista que almacenara los datos de los artistas
    nodo* listaArtistas = NULL;
    //A continuacion se leera y almacenaran todos los artistas en la lista enlazada recien creada
    listaArtistas = leerYAlmacenarArtistas(archivoArtistas,listaArtistas);
    //Una vez almacenados los datos en la lista se cierra el archivo ya que no sera ocupado
    fclose(archivoArtistas);

    //A continuacion se leera el archivo de generos
    FILE* archivoGeneros = leerArchivo("generos.in");
    //Si la funcion leerArchivo devuelve un 0 es porque el archivo no existe o el nombre fue mal ingresado.
    if(archivoGeneros == 0){
        printf("Algo fallo, verifique el nombre del archivo por favor\n");
        return 0;
    }
    //Se define una lista que almacenara los datos de los generos
    nodo* listaGeneros = NULL;
    //A continuacion se leera y almacenaran todos los generos en la lista enlazada recien creada
    listaGeneros = leerYAlmacenarGeneros(archivoGeneros,listaGeneros);
    //Una vez almacenados los datos en la lista se cerrara el archivo
    fclose(archivoGeneros);

    //A continuacion se leera el archivo de canciones
    FILE* archivoCanciones = leerArchivo("canciones.in");
    //Si la funcion leerArchivo devuelve un 0 es porque el archivo no existe o el nombre fue mal ingresado.
    if(archivoCanciones == 0){
        printf("Algo fallo, verifique el nombre del archivo por favor\n");
        return 0;
    }
    //Se define una lista que almacenara los datos de las canciones
    nodo* listaCanciones = NULL;
    //A continuacion se leera y almacenaran todas las canciones en la lista enlazada recien creada
    listaCanciones = leerYAlmacenarCanciones(archivoCanciones,listaCanciones);
    //Una vez almacenados los datos en la lista se cerrara el archivo
    fclose(archivoCanciones);

    //Ahora queda por leer el archivo de preferencias
    FILE* archivoPreferencias = leerArchivo("preferencias.in");
    //Si la funcion leerArchivo devuelve un 0 es porque el archivo no existe o el nombre fue mal ingresado.
    if(archivoCanciones == 0){
        printf("Algo fallo, verifique el nombre del archivo por favor\n");
        return 0;
    }
    //Se leera la cantidad de minutos y segundos deseados para la playlist y se almacenaran en dos variables
    char duracionDeseadaPlaylist[10];
    fscanf(archivoPreferencias,"%s",&duracionDeseadaPlaylist);
    //Se lee separando la string
    char *duracionPlaylist = strtok(duracionDeseadaPlaylist,":");
    //Se definen dos variables para almacenar las strings de minutos y segundos
    char minutosPlaylist[5];
    char segundosPlaylist[3];
    //Se copian los minutos como string
    strcpy(minutosPlaylist,duracionPlaylist);
    //Se leen los segundos como string
    duracionPlaylist = strtok(NULL,":");
    //Se copian los segundos como string
    strcpy(segundosPlaylist,duracionPlaylist);
    //Se transforman a numeros enteros los minutos y segundos y se almacenan en nuevas variables
    int playlistMinutos = atoi(minutosPlaylist);
    int playlistSegundos = atoi(segundosPlaylist);
    //A continuacion se definira una cola que almacenara las preferencias para la creacion de la playlist
    cola* colaPreferencias = crearCola();
    //Se encolan las preferencias, quedando asi almacenadas en la cola
    colaPreferencias = leerYAlmacenarPreferencias(archivoPreferencias,colaPreferencias);
    //Se cierra el archivo una vez almacenadas las preferencias
    fclose(archivoPreferencias);

    //A continuacion se ordenara la lista de canciones de menor a mayor segun su popularidad
    //Se hace gracias a un bubble sort adaptado a listas enlazadas
    int longitudListaCanciones = longitud_lista_enlazada(listaCanciones);
    if(longitudListaCanciones == 0){
        printf("No hay canciones en la lista de canciones !");
        return 0;
    }
    listaCanciones = ordenarListaCancionesPorPopularidad(listaCanciones,longitudListaCanciones);
    //Ahora que la lista se encuentra ordenada por popularidad se debe verificar los casos en que hayan dos o mas canciones con la misma popularidad
    //Se volvera a ordenar la lista, pero solo los casos en los cuales hayan canciones con la misma popularidad
    listaCanciones = ordenarListaCancionesMismaPopularidad(listaCanciones,longitudListaCanciones,listaArtistas);
    //Una vez ordenada la lista definitivamente, es posible crear el archivo de salida
    crearArchivoSalida(listaCanciones,listaArtistas,listaGeneros);
    printf("Archivo de salida generado\n");

    //Ahora se procedera a crear la playlist solicitada
    //Se creara una nueva lista auxiliar, la cual almacenara la lista de canciones para la playlist
    nodo* listaPlaylist = NULL;
    listaPlaylist = crearPlaylist(listaPlaylist,listaCanciones,colaPreferencias,playlistMinutos,playlistSegundos);
    //Una vez creada la playlist, es posible crear el archivo de salida de la playlist
    crearArchivoSalidaPlaylist(listaPlaylist,listaArtistas,listaGeneros);
    printf("Playlist generada\n");

    //Finalmente queda liberar la memoria de las listas enlazadas y la cola usadas en la solucion.
    liberarListaEnlazada(listaArtistas);
    liberarListaEnlazada(listaGeneros);
    liberarListaEnlazada(listaCanciones);
    liberarListaEnlazada(listaPlaylist);
    liberarCola(colaPreferencias);

    return 0; 
}