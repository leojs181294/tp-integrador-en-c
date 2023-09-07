#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CARACTER 20
#define CANTIDA_NOTEBOOK 50

struct NOTEBOOK
{
	int id;
	char marca[MAX_CARACTER];
	char modelo[MAX_CARACTER];
	char sist_operativo[10];
	char procesador[MAX_CARACTER];
	int nucleos;
	float velocidad_procesadora;
	int memoria_ram;
	int hdd;
	int sdd;
	int memoria_video;
	int puertos_usb;
	bool red_rj45;
	int cantidad_adquiridas;
	int cantidad_vendidas;
	int stock;
	long precio_unitario;
	long stock_valorizado;
};
//Ponemos variables globales del indice y string_check para poder utulizarlas en funciones y el main 
int indice_notebook=0;
char string_check[100] = " ";

//		Funciones de manipulacion de registros

//Funcion que chequea si existe el archivo, si no existe lo crea y si existe toma los datos del archivo para el array de estructuras.
int chequeo_lectura(struct NOTEBOOK notebook[]){
    int iterativo=0;
    FILE *archivo;
    archivo = fopen("PAPF.dat", "rb");
    if(archivo == NULL){
        fclose(archivo);
        archivo = fopen("PAPF.dat", "wb");
        fclose(archivo);
        printf("Archivo creado...");
    }
    else{
		fclose(archivo);
		archivo = fopen("PAPF.dat", "rb");
        while(!feof(archivo)){
		   fread(&notebook[iterativo], sizeof(notebook[iterativo]), iterativo+1, archivo);
            iterativo++;
        }
		fclose(archivo);
		iterativo--;
		printf("\nLectura realizada elemento: %i\n", iterativo);         
    }
	return iterativo;
}
//Funcion para guardar elementos del array en un archivo, en este caso el archivo se va a llamar "PAPF.dat"
void guardado(struct NOTEBOOK notebook[],int indice){
    FILE *archivo;
    archivo = fopen("PAPF.dat", "ab");
    if (archivo == NULL){
        printf("\nEl archivo no existe...");
    }
    else{
        fwrite(&notebook[indice], sizeof(notebook[indice]), indice+1, archivo);
    }
    fclose(archivo); 
}
//Funcion para realizar la modificacion de un registro
void modificar_registro(struct NOTEBOOK notebook, int recibo) {
	struct NOTEBOOK carga;
	int id_mod=recibo;
	FILE *archivo;
    archivo = fopen("PAPF.dat", "r+b");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
		fclose(archivo);
        return;
    }
    while (fread(&carga, sizeof(struct NOTEBOOK), 1, archivo)) {
		if (carga.id == id_mod) {
			printf("\nDato cargado exitosamente..");
			fseek(archivo, -(int)sizeof(struct NOTEBOOK), SEEK_CUR);
			fwrite(&notebook, sizeof(struct NOTEBOOK), 1, archivo);
			break;
        }
    }
    fclose(archivo);
}
//Funcion para eliminar un registro
void eliminar_registro(struct NOTEBOOK notebook[], int indice){
    int check;
    FILE *archivo;
	archivo = fopen("PAPF.dat", "wb");
	for(int x= 0; x<indice; x++){
		check = fwrite(&notebook[x], sizeof(notebook[x]), x+1, archivo);
	}
	fclose(archivo);
}

//		Funciones de validacion de datos

//Funcion que chequea longitudes de caracteres de una variable
void check_longitud(char variable[],int longitud){
	 while ( strlen(variable)>longitud)
      {
        printf("\n Longitud invalida \n Ingrese nuevamente:\t");
        scanf("%s",variable);
      }
}
//Funcion que chequea la variable ingresada como string y nos retorna distintos valores dependiendo de lo que contenga para luego implementar funciones de check int\float
int check_numero(char string_a_chequear[]){
    int contf = 0;
    int contc = 0;   
    for(int i= 0;i<strlen(string_a_chequear);i++){
        if (!((string_a_chequear[i]>='0')&&(string_a_chequear[i]<='9'))){
            if (string_a_chequear[i]=='.'){
                contf++;
            }
            else{
                contc++;
            }
        }
    }
    if(string_a_chequear[0]=='.'){
        return 4;
    }
    else if(contc>0 || contf>1){
        return 4;
    }
    else if (contf == 1 && contc == 0){
        return 2;
    }
    else if (contc>0){
        return 3;
    }
    else if(contc == 0 && contf == 0){
        return 1;
    }
}
//Funcion para validar que el dato ingresado sea un entero
int ver_entero(char string_a_chequear[]){
    int numero_verificado = 0;
    while(check_numero(string_a_chequear) != 1){
        printf("\nEl dato cargado no es de un formato valido, por favor vuelva a intentarlo: ");
        scanf("%s", string_a_chequear);
    }
    numero_verificado = atoi(string_a_chequear);
	return numero_verificado;
}
//Funcion para validar que el dato ingresado sea un float
float ver_float(char string_a_chequear[]){
	float numero_verificado = 0.00;
	while(check_numero(string_a_chequear) != 1 && check_numero(string_a_chequear) != 2){
        printf("\nEl dato cargado no es de un formato valido, por favor vuelva a intentarlo: ");
        scanf("%s", string_a_chequear);
    }
    numero_verificado = atof(string_a_chequear);
	return numero_verificado;
}

//Funcion para visualizar los datos de una notebook
void mostrar_notebook(struct NOTEBOOK notebook[], int indice_notebook){
	printf("============================");
	printf("\n\tid: %i\n\tmarca: %s\n\tmodelo: %s\n",notebook[indice_notebook].id,notebook[indice_notebook].marca,notebook[indice_notebook].modelo);
    printf("\tSistema Operativo: %s\n\tprocesador: %s\n",notebook[indice_notebook].sist_operativo,notebook[indice_notebook].procesador);
    printf("\tcantidad de nucleos: %i\n\tVelocidad del procesador: %.2f\n",notebook[indice_notebook].nucleos,notebook[indice_notebook].velocidad_procesadora);
    printf("\tcapacidad de memoria RAM: %iGB\n\tcapacidad de memoria hdd: %iGB\n",notebook[indice_notebook].memoria_ram,notebook[indice_notebook].hdd);
    printf("\tcapacidad de memoria sdd: %iGB\n\tcapacidad de memoria de video: %iGB\n",notebook[indice_notebook].sdd,notebook[indice_notebook].memoria_video);
    printf("\tcantidad de puertos usb: %i\n\tcantidad adquiridas: %i\n",notebook[indice_notebook].puertos_usb,notebook[indice_notebook].cantidad_adquiridas);
    printf("\tcantidad vendidas: %i\n\tStock diponible: %i\n",notebook[indice_notebook].cantidad_vendidas,notebook[indice_notebook].stock);
    printf("\tPrecio unitario: $%i\n\tStock valorizado: $%i\n",notebook[indice_notebook].precio_unitario,notebook[indice_notebook].stock_valorizado);
	printf("\tEntrada de red rj-45: %d\n",notebook[indice_notebook].red_rj45);
	printf("============================");
}

//Funcion para esperar y borrar pantallla
void esp_limp(){	
	system("pause");
	system("cls");
}

//Funcion para inicializar los valores de una notebook
void iniciar_notebook(struct NOTEBOOK notebook[], int posicion){
	notebook[posicion].id=0;
	strcpy(notebook[posicion].marca,"  ");
    strcpy(notebook[posicion].modelo,"  ");
    strcpy(notebook[posicion].sist_operativo,"  ");
    strcpy(notebook[posicion].procesador,"  ");
    notebook[posicion].nucleos=0;
    notebook[posicion].velocidad_procesadora=0.0;
    notebook[posicion].memoria_ram=0;
    notebook[posicion].hdd=0;
    notebook[posicion].sdd=0;
    notebook[posicion].memoria_video=0;
    notebook[posicion].puertos_usb=0;
    notebook[posicion].red_rj45=0;
    notebook[posicion].cantidad_adquiridas=0;
    notebook[posicion].cantidad_vendidas=0;
    notebook[posicion].stock=0;
    notebook[posicion].precio_unitario=0;
    notebook[posicion].stock_valorizado=0;
}

//		Funciones para la manipulacion de los productos

//Funcion para agregar una nueva notebook
void agregar_notebook(struct NOTEBOOK notebook[],int* indice_notebook) {
	struct NOTEBOOK nueva_notebook;
	int opc,opc1,opc2;
	nueva_notebook.id=(*indice_notebook+1);
	printf("\n Ingrese marca: \t");
	scanf("%s",nueva_notebook.marca);
	check_longitud(nueva_notebook.marca,MAX_CARACTER);
	printf("\n Ingrese modelo:\t");
	scanf("%s",nueva_notebook.modelo);
	check_longitud(nueva_notebook.modelo,MAX_CARACTER);
	do{	
		printf("\n Sistema Operativo:\n opcion 1: Windows \n opcion 2: Linux \n");
		scanf("%s",&string_check);
		opc= ver_entero(string_check);
		switch (opc){
			case 1:{
				strcpy(nueva_notebook.sist_operativo, "Windows");
				break;
			}
			case 2:{
				strcpy(nueva_notebook.sist_operativo, "Linux");
				break;
			}
			default:{printf("\tOpcion no valida\n\nintente nuevamente \n");}
		}
	}while(opc!=1 && opc!=2);

	printf("\n Ingrese Procesador:\t \n");
	fflush(stdin);
	gets(nueva_notebook.procesador);
	printf("\n Cantidad de nucleos:\t \n");
	scanf("%s",&string_check);
	nueva_notebook.nucleos=ver_entero(string_check);
	printf("\n velocidad procesador:\t \n");
	scanf("%s",&string_check);
	nueva_notebook.velocidad_procesadora=ver_float(string_check);
	printf("\n capacidad de memoria RAM:\t \n");
	scanf("%s",&string_check);
	nueva_notebook.memoria_ram=ver_entero(string_check);
	printf("\n capacidad de memoria HDD en GB:\t \n");
	scanf("%s",&string_check);
	nueva_notebook.hdd=ver_entero(string_check);
	printf("\n capacidad de memoria SDD en GB:\t \n");
	scanf("%s",&string_check);
	nueva_notebook.sdd=ver_entero(string_check);
	printf("\n capacidad de memoria de video en GB:\t \n");
	scanf("%s",&string_check);
	nueva_notebook.memoria_video=ver_entero(string_check);
	printf("\n cantidad de puertos usb:\t \n");
	scanf("%s",&string_check);
	nueva_notebook.puertos_usb=ver_entero(string_check);
	do{
		printf("Tiene entrada de red rj-45:\t\nopcion 1:si\nopcion 2:no\n");
		scanf("%s",&string_check);
		opc1=ver_entero(string_check);
		if(opc1==1){
			nueva_notebook.red_rj45=1;
		}else{
			nueva_notebook.red_rj45=0;
		}
	}while(opc1!=1 && opc1!=2);
	printf("\n cantidad adquiridas:\t \n");
	scanf("%s",&string_check);
	nueva_notebook.cantidad_adquiridas=ver_entero(string_check);
	printf("\n cantidad vendidas:\t \n");
	scanf("%s",&string_check);
	nueva_notebook.cantidad_vendidas=ver_entero(string_check);
	nueva_notebook.stock=nueva_notebook.cantidad_adquiridas-nueva_notebook.cantidad_vendidas;
	printf("\n precio unitario:\t \n");
	scanf("%s",&string_check);
	nueva_notebook.precio_unitario=ver_entero(string_check);
	nueva_notebook.stock_valorizado=nueva_notebook.precio_unitario*nueva_notebook.stock;
	
    notebook[*indice_notebook] = nueva_notebook;
    mostrar_notebook(notebook,*indice_notebook);
    guardado(notebook,*indice_notebook);
    (*indice_notebook)++;
	esp_limp();
}
// Función para modificar un producto por su ID
void modificar_notebook(struct NOTEBOOK notebook[], int indice_notebook) {
    int id_modificar=0;
    int opc,opc1;
    char opc2[1];
	struct NOTEBOOK nueva_notebook;
    do{
	    printf("\nIngrese el ID del producto que desea modificar:\t");
	    scanf("%s",&string_check);
	    id_modificar=ver_entero(string_check);
		for (int x=0;x<indice_notebook;x++){
			if (notebook[x].id==id_modificar){
				mostrar_notebook(notebook,x);
				printf("\nEs el producto correcto? s/n:\t");
				scanf("%s",opc2); 
				if(strcmp(opc2,"s")==0){
					do{
						printf("Que dato desea modificar\n1-marca\n2-modelo\n3-sistema operativo\n");
						printf("4-procesador\n5-cantidad de nucleos\n6-velocidad de procesamiento\n7-memoria ram\n");
						printf("8-memoria HDD\n9-memoria SDD\n10-memoria video\n11-cantidad de puertos usb\n");
						printf("12-entrada de red rj-45\n13-cantidad adquiridas\n14-cantidad vendidas\n15-precio unitario\n");
						printf("Ingrese opcion:\t");
						scanf("%s",&string_check);
						opc=ver_entero(string_check);
						system("cls");
						// Desplegamos un switch para elegir el dato que se desea modificar de un producto
						switch(opc){
							case 1:{
								strcpy(notebook[x].marca, "  ");
								printf("Marca: ");
	    						scanf("%s",notebook[x].marca);
								check_longitud(notebook[x].marca,MAX_CARACTER);
								break;
							}
							case 2:{
								strcpy(notebook[x].modelo, "  ");
								printf("Modelo: ");
	    						scanf("%s", notebook[x].modelo);
	    						check_longitud(notebook[x].modelo,MAX_CARACTER);
								break;
							}
							case 3:{
								strcpy(notebook[x].sist_operativo, "  ");
								do{	
									printf("\n Sistema Operativo:\n opcion 1: Windows \n opcion 2: Linux \n");
									scanf("%s",&string_check);
									opc1=ver_entero(string_check);
									switch (opc1){
										case 1:{
											strcpy(notebook[x].sist_operativo, "Windows");
											break;
										}
										case 2:{
											strcpy(notebook[x].sist_operativo, "Linux");
											break;
										}
										default:{printf("\tOpcion no valida\n\nintente nuevamente \n");}
									}
								}while(opc1!=1 && opc1!=2);
								opc1=0;
								break;
							}
							case 4:{
								strcpy(notebook[x].procesador, "  ");
								printf("\n Ingrese Procesador:\t \n");
								fflush(stdin);
								gets(notebook[x].procesador);
								break;
							}
							case 5:{
								notebook[x].nucleos = 0;
								printf("\n Cantidad de nucleos:\t \n");
								scanf("%s",&string_check);
								notebook[x].nucleos=ver_entero(string_check);
								break;
							}
							case 6:{
								notebook[x].velocidad_procesadora = 0.0;
								printf("\n velocidad procesador:\t \n");
								scanf("%s",&string_check);
								notebook[x].velocidad_procesadora=ver_float(string_check);
								break;
								
							}
							case 7:{
								notebook[x].memoria_ram = 0;
								printf("\n capacidad de memoria RAM:\t \n");
								scanf("%s",&string_check);
								notebook[x].memoria_ram=ver_entero(string_check);
								break;
							}
							case 8:{
								notebook[x].hdd = 0;
								printf("\n capacidad de memoria HDD en GB:\t \n");
								scanf("%s",&string_check);
								notebook[x].hdd=ver_entero(string_check);
								break;
							}
							case 9:{
								notebook[x].sdd = 0;
								printf("\n capacidad de memoria SDD en GB:\t \n");
								scanf("%s",&string_check);
								notebook[x].sdd=ver_entero(string_check);
								break;
							}
							case 10:{
							    notebook[x].memoria_video = 0;
							   	printf("\n capacidad de memoria de video en GB:\t \n");
								scanf("%s",&string_check);
								notebook[x].memoria_video=ver_entero(string_check);
								break;
							}
							case 11:{
								notebook[x].puertos_usb = 0;
								printf("\n cantidad de puertos usb:\t \n");
								scanf("%s",&string_check);
								notebook[x].puertos_usb=ver_entero(string_check);
								break;
							}
							case 12:{
							    notebook[x].red_rj45 = 0;
						    	do{
									printf("Tiene entrada de red rj-45:\t\nopcion 1:si\nopcion 2:no\n");
									scanf("%s",&string_check);
									opc1=ver_entero(string_check);
									if(opc1==1){
										notebook[x].red_rj45=1;
									}else{
										notebook[x].red_rj45=0;
									}         
								}while(opc1!=1 && opc1!=2);
								opc1=0;
								break;
							}
							case 13:{
								notebook[x].cantidad_adquiridas = 0;
								printf("\n cantidad adquiridas:\t \n");
								scanf("%s",&string_check);
								notebook[x].cantidad_adquiridas=ver_entero(string_check);
								break;
							}
							case 14:{
								notebook[x].cantidad_vendidas = 0;
								printf("\n cantidad vendidas:\t \n");
								scanf("%s",&string_check);
								notebook[x].cantidad_vendidas=ver_entero(string_check);
								break;
							}
							case 15:{
								notebook[x].precio_unitario = 0;
								printf("\n precio unitario:\t \n");
								scanf("%s",&string_check);
								notebook[x].precio_unitario=ver_entero(string_check);
								break;
							}
							default:{
								printf("Opcion invalida\n");
								opc=0;
								break;
							}
						}
						notebook[x].stock=notebook[x].cantidad_adquiridas-notebook[x].cantidad_vendidas;
						notebook[x].stock_valorizado=notebook[x].precio_unitario * notebook[x].stock;	;
						modificar_registro(notebook[x], id_modificar);
					}while(opc==0);
				}
				break;
			}
		}
	}while(strcmp(opc2,"n")==0);
    esp_limp();
}
//Funcion para eliminar un producto

int eliminar(struct NOTEBOOK notebook[],int indice_notebook){
	char continuar[1];
	// do while para eliminar mas de un elemento, preguntando al usuario si desea continuar
	do{
		// declarar variables
		int id_eliminar = 0;
		int id_existente = 0;
		// funcion de eliminacion por ID
		printf("\ninserte el ID del producto que desea eliminar:\t");
		scanf("%i",&id_eliminar);
		for (int x=0;x<indice_notebook;x++){
			if (notebook[x].id==id_eliminar){
				notebook[x] = notebook[indice_notebook-1];
				notebook[x].id = id_eliminar;
				iniciar_notebook(notebook,indice_notebook-1);
				//aca va para vaciar notebook[i]
				indice_notebook=indice_notebook-1;
				id_existente = 1;
				break; 
			}
		}		
		if(id_existente == 1){
			printf("\nEl elemento se ha eliminado de manera exitosa\n");
			printf("\nDesea eliminar otro producto? s/n:\t ");
		}
		else{
			("\nLa id no se ha podido eliminar debido a que no existe... Desea volver a intentarlo?\t");
		}
		/*Ingresar la eliminacion de un producto aqui*/
		scanf("%s",continuar);
	}while (strcmp(continuar, "s") == 0);
	eliminar_registro(notebook, indice_notebook);
	return indice_notebook;
}
//Funcion que nos da el listado total de los productos
void lista_producto(struct NOTEBOOK notebook[],int indice_notebook){
	printf("lista productos\n");
	for (int x=0;x<indice_notebook;x++){
		mostrar_notebook(notebook,x);	
	}
	esp_limp();
}
//Funcion de ordenamiento
void ordenamiento(struct NOTEBOOK notebook[],int indice_notebook){
	struct NOTEBOOK aux;
	int i=0,opc,opc1;
	printf("Por que desea ordenar?\n1-marca\n2-memoria ram\n3-procesador\n4-precio\n0-Volver al menu anterior\nIngrese una opcion:\t");
    scanf("%s",&string_check);
	opc=ver_entero(string_check);
	system("cls");
	switch(opc){
		case 1:{
			for(int x=0;x<indice_notebook;x++){
			    for(int i=0;i<indice_notebook-1;i++){
			        if (strcasecmp(notebook[i].marca, notebook[i+1].marca)>0){
		                aux= notebook[i];
		                notebook[i]= notebook[i+1];
		                notebook[i+1]= aux;
		            }
			    }
			}		
			lista_producto(notebook,indice_notebook);
			break;
		}
		case 2:{
			do{			
			printf("1-de menor a mayor memoria ram\n2-de mayor a menor memoria ram\nEliga una opcion:\t ");
		    scanf("%s",&string_check);
			opc1=ver_entero(string_check);
			system("cls");
			for(int x=0;x<indice_notebook;x++){
			    for(int i=0;i<indice_notebook-1;i++){
			    	if(opc1==1){
				    	if (notebook[i].memoria_ram > notebook[i+1].memoria_ram){
			                aux= notebook[i];
			                notebook[i]= notebook[i+1];
			                notebook[i+1]= aux;
			            }	
					}else{
						if (notebook[i].memoria_ram < notebook[i+1].memoria_ram){
			                aux= notebook[i];
			                notebook[i]= notebook[i+1];
			                notebook[i+1]= aux;
			            }
					}
			    }
			}
			if(opc1!=1&&opc1!=2){
				printf("Opcion invalida\n");
			}
			}while(opc1!=1&&opc1!=2);		
			lista_producto(notebook,indice_notebook);		
			break;
		}
		case 3:{
			for(int x=0;x<indice_notebook;x++){
			    for(int i=0;i<indice_notebook-1;i++){
			        if (strcasecmp(notebook[i].procesador, notebook[i+1].procesador)>0){
		                aux= notebook[i];
		                notebook[i]= notebook[i+1];
		                notebook[i+1]= aux;
		            }
			    }
			}		
			lista_producto(notebook,indice_notebook);
			break;
		}
		case 4:{
			do{			
			printf("1-Precio de menor a mayor\n2-Precio de mayor a menor\nEliga una opcion:\t ");
		    scanf("%s",&string_check);
			opc1=ver_entero(string_check);
			system("cls");
			for(int x=0;x<indice_notebook;x++){
			    for(int i=0;i<indice_notebook-1;i++){
			    	if(opc1==1){
				    	if (notebook[i].precio_unitario > notebook[i+1].precio_unitario){
			                aux= notebook[i];
			                notebook[i]= notebook[i+1];
			                notebook[i+1]= aux;
			            }	
					}else{
						if (notebook[i].precio_unitario < notebook[i+1].precio_unitario){
			                aux= notebook[i];
			                notebook[i]= notebook[i+1];
			                notebook[i+1]= aux;
			            }
					}
			    }
			}
			if(opc1!=1&&opc1!=2){
				printf("Opcion invalida\n");
			}
			}while(opc1!=1&&opc1!=2);		
			lista_producto(notebook,indice_notebook);		
			break;
		}
		case 0:
            break;
		default:
            printf("\nLa opcion elegida no es valida...");
            break;
	}
}
//Funcion para listar notebook 
void tipos_listado(struct NOTEBOOK notebook[], int indice_notebook){
    int id_lista=0;
    char marca[MAX_CARACTER] = " ";
    int opcion = 0;
    do{
    	printf("\n1.Mostrar un producto especifico por ID.\n2.Mostrar todos los productos de una determinada marca.\n3.Mostrar lista completa.\n4.Ordenamiento de productos\n0.Volver al menu anterior.\nIngrese su opcion:\t");
    	scanf("%s",&string_check);
    	opcion=ver_entero(string_check);
        switch (opcion){
            case 1:{
                printf("\nIngrese el ID del producto:\n");
                scanf("%i",&id_lista);
                for (int x=0;x<indice_notebook;x++){
                    if (notebook[x].id==id_lista){
                    mostrar_notebook(notebook,x);
                    esp_limp();
                    break;
                    }
                }
            	break;
			}
            case 2:{
                printf("\nIngrese la marca producto:\n");
                scanf("%s",marca);
                for (int x=0;x<indice_notebook;x++){
                    if (strcmp(notebook[x].marca, marca)==0){
                    mostrar_notebook(notebook,x);
                    }
                }
                esp_limp();
            	break;
			}
			case 3:{
				lista_producto(notebook,indice_notebook);
				break;
			}
			case 4:{
				ordenamiento(notebook,indice_notebook);
				break;
			}
            case 0:
                break;
            default:
                printf("\nLa opcion elegida no es valida...");
                break;
        }
    } while (opcion != 0);    
    esp_limp();
    fflush(stdin);
}
//Funcion para ver minimos y maximos
void min_max(struct NOTEBOOK notebook[], int indice_notebook){
	void mostrar(struct NOTEBOOK notebook[],int pos_max,int pos_min){
		printf("\n\tEl producto maximo es:\n");
		printf("============================");
		printf("\n\tid: %i\n\tmarca: %s\n\tmodelo: %s\n",notebook[pos_max].id,notebook[pos_max].marca,notebook[pos_max].modelo);
	    printf("\tcantidad vendidas: %i\n\tStock diponible: %i\n",notebook[pos_max].cantidad_vendidas,notebook[pos_max].stock);
	    printf("\tPrecio unitario: $%i\n\tStock valorizado: $%i\n",notebook[pos_max].precio_unitario,notebook[pos_max].stock_valorizado);
		printf("============================");
		printf("\n\tEl producto minimo es:\n");
		printf("\n\tid: %i\n\tmarca: %s\n\tmodelo: %s\n",notebook[pos_min].id,notebook[pos_min].marca,notebook[pos_min].modelo);
    	printf("\tcantidad vendidas: %i\n\tStock diponible: %i\n",notebook[pos_min].cantidad_vendidas,notebook[pos_min].stock);
	    printf("\tPrecio unitario: $%i\n\tStock valorizado: $%i\n",notebook[pos_min].precio_unitario,notebook[pos_min].stock_valorizado);
		printf("============================");
	}
	int pos_max=0,pos_min=0,mayor=0,menor=0,opc;
	printf("Por que quisiera visualizar maximo y minimo\n");
	printf("1:Cantidad vendidas\n2:Cantidad en stock\n3:Stock valorizado\nIngrese una opcion:\t");
	scanf("%s",&string_check);
	opc=ver_entero(string_check);
	system("cls");
	switch (opc){
		case 1:{
			for(int i=0;i<indice_notebook;i++){
				if (notebook[i].cantidad_vendidas > mayor){	
					mayor=notebook[i].cantidad_vendidas;
					pos_max=i;
				}
			}
			menor=notebook[0].cantidad_vendidas;
			for(int i=0;i<indice_notebook;i++){
				if (notebook[i].cantidad_vendidas < menor){
					menor=notebook[i].cantidad_vendidas;
					pos_min=i;
				}				
			}
			mostrar(notebook,pos_max,pos_min);
			break;
		}
		case 2:{
			for(int i=0;i<indice_notebook;i++){
				if (notebook[i].stock > mayor){	
					mayor=notebook[i].stock;
					pos_max=i;
				}
			}
			menor=notebook[0].stock;
			for(int i=0;i<indice_notebook;i++){
				if (notebook[i].stock < menor){
					menor=notebook[i].stock;
					pos_min=i;
				}				
			}
			mostrar(notebook,pos_max,pos_min);
			break;
		}
		case 3:{
			for(int i=0;i<indice_notebook;i++){
				if (notebook[i].stock_valorizado > mayor){	
					mayor=notebook[i].stock_valorizado;
					pos_max=i;
				}
			}
			menor=notebook[0].stock_valorizado;
			for(int i=0;i<indice_notebook;i++){
				if (notebook[i].stock_valorizado < menor){
					menor=notebook[i].stock_valorizado;
					pos_min=i;
				}				
			}
			mostrar(notebook,pos_max,pos_min);
			break;
		}
		default:{
			system("cls");
			printf("\nOpcion no valida\n");
			break;
		}
	}
}

void imprimir_isaac(){
	printf("\033[0;31m");
	printf("                             @@@@@@@@@@@@@@@@@                                  \n");
	printf("                         @@@@@@@@@@@@@@@@@@@@@@@@@                              \n");
	printf("                     @@@@@@@@*****************@@@@@@@@                          \n");
	printf("                   @@@@@@**.....................**@@@@@@                        \n");
	printf("                 @@@@**.............................**@@@@                      \n");
	printf("             @@@@**.....................................**@@@@@@@@@@@@          \n");
	printf("             @@@@.........................................@@@@**..**@@@@        \n");
	printf("           @@@@**.........................................@@@@......@@@@        \n");
	printf("           @@@@...........................................@@**......@@@@        \n");
	printf("         @@@@**..,,@@@@@@@@,*................,,/@@@@@@@@**@@**....*,@@@@        \n");
	printf("         @@@@**..@@    @@@@@@................/@&    @@@@@@@@****@@@@@@@@@@      \n");
	printf("         @@@@*,**@@    @@@@@@................/@&    @@@@@@****@@@@@@@@@@@@@@    \n");
	printf("         @@@@/***@@@@@@@@@@@@..@@@@@@@@@@@@/./@@@@@@@@@@@@****@@,*....**@@@@    \n");
	printf("           @@@@***/********//..@@        &@/.,********@@@@**@@**........**@@@@  \n");
	printf("             @@@@**............**@@@@@@@@**,......@@@@@@****/*............@@@@  \n");
	printf("             @@@@****.............................@@*/@@******............@@@@  \n");
	printf("               @@@@****........................,@@@@....********..........@@@@  \n");
	printf("                 @@@@//**....................,*/@@**....***,****..........@@@@  \n");
	printf("                     @@@@@@@@**,,,,,,,,,,,,**#@@@@****..**@@@@*******/@@@@@@    \n");
	printf("                       @@@@@@@@@@@@@@@@@@@@@@@@@@@**********@@@@@@@@@@@@@@      \n");
	printf("                       @@@@**@@@@@@@@@@@@@@@@@@@@@@@******@@@@@@@@@@@@@@        \n");
	printf("                     @@@@**....*****************@@@@@@@@@@@@@@                  \n");
	printf("                     @@@@**..@@**............,**@@@@@@@@@@@@                    \n");
	printf("                       @@@@@@@@....**@@@@**....,@@@@                            \n");
	printf("                         @@@@@@......@@@@**....,@@@@                            \n");
	printf("                           @@@@@@....@@@@**,./@@@@@@                            \n");
	printf("                             @@@@@@@@@@@@@@@@@@@@@                              \n");
	printf("\033[0m");
}

//			Inicio al programa
	
void main(){
	
	//Declaracion de array y variables locales
	struct NOTEBOOK notebook[CANTIDA_NOTEBOOK];
	int opc,opc1,opc3;
	
	//Inicializamos el array de las notebook 
	int x=0;
	while(x==0){
		for (x; x < CANTIDA_NOTEBOOK; x++){
	       iniciar_notebook(notebook,x); 
	    }
	    x++;
	}
	// Usamos la funcion de chequeo la cual verifica la exitencia de registros y nos devuelve la cantidad encontrada
	indice_notebook = chequeo_lectura(notebook);
	
	printf("\t\tBienvenido al sistema.\n");
	//	Inicio de menu de opciones
	do{
		printf("\nQue accion desea realizar \nopcion 1: insertar,modificar o eliminar producto \nopcion 2: lista de productos \nopcion 3: Minimos y Maximos\nopcion 0: Salir del programa\nIngrese su opcion:\t ");
		scanf("%s",&string_check);
		opc = ver_entero(string_check);
		system("cls");
		// Iniciamos un switch para realizar una accion de listar o manipulacion del producto	
		switch (opc){
			case 1:{	
				do{	
					printf("Que accion desea realizar \nopcion 1: ingresar nuevo producto \nopcion 2: modificar un producto \nopcion 3: eliminar un producto \nopcion 0: volver al menu principal\nIngrese su opcion:\t ");
					scanf("%s",&string_check);
					opc1 = ver_entero(string_check);
					// Iniciamos un switch para realizar ingreso/modificacion/eliminacion de un producto
					switch (opc1){	//Caso para ingresar nuevos datos 
						case 1:{   
							do{
								agregar_notebook(notebook,&indice_notebook);					
								printf("\nQuiere cargar otro producto\nopcion 1: SI\nopcion 2: NO\nIngrese una opcion:\t");
								scanf("%s",&string_check);
								opc3 = ver_entero(string_check);	
								while(opc3!=1 && opc3!=2){
									printf("Opcion no valida\nintente nuevamente \n");
									scanf("%i",&opc3);
								}
								//validamos si quiere seguir cargando datos
								if (opc3!=1){
									system("cls");
								}
							}while(opc3==1);
							break;
						}
						// Caso Modificacion
						case 2:{
							modificar_notebook(notebook,indice_notebook);
							break;
						}
						// Caso Eliminacion
						case 3:{
							indice_notebook = eliminar(notebook,indice_notebook);
							break;
							}
						//Caso vuelta al menu
						case 0:{
							printf("\nVolviendo al menu principal...\n");
							break;
						}
						default:{
							system("cls");
							printf("\tOpcion no valida\n\nintente nuevamente \n");
						}
					}	
				}while(opc1!=0);
				break;
			}
			case 2:{
				tipos_listado(notebook,indice_notebook);
				break;
			}
			case 3:{
				min_max(notebook,indice_notebook);
				break;
			}
			case 0:{
				imprimir_isaac();
				printf("\n\t\tGracias por usar nuestro programa!");
				break;
			}
			default:{
				system("cls");
				printf("\nOpcion no valida\nintente nuevamente \n");
			}
		}
	}while(opc!=0);
}
