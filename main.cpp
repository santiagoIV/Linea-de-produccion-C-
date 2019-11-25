#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <cstdlib>
#include <thread>
#include <ctime>


using namespace std;
/***********************************************
 *  STRUCT                                     *
 * Estructura que hereda las cualidades de     *
 * exception y arroja una cadena de caracteres *
 * cuando se inserta un numero negativo        *
 **********************************************/
struct InNegativCase: public exception{
	const char* what() const throw(){
		return  "\nIngreso de numero negativo no permitido\n";
	}
};
/***********************************************
 *  STRUCT                                     *
 * Estructura que hereda las cualidades de     *
 * exception y arroja una cadena de caracteres *
 * cuando se inserta un Argumento invalido     *
 **********************************************/
struct InInvalidArgument: public exception{
	const char* what() const throw(){
		return  "\nArgumento invalido\n";
	}
};
/*****************************************************************************
 *  STRUCT                                                                   *
 * estructura de tipo Linea donde guardaremos  todos los datos vitales       *  
 * @Product: Cadena de caracteres que guarda el nombre del producto          *
 * @Num_Linea: De tipo entero que guarda el numero de la linea de produccion *
 * @Producto_a_realizar: De tipo entero que guarda el producto a realizar    *
 * @Producto_realizado: De tipo entero que guarda el producto realizado      *
 * @num_vueltas: De tipo entero guarda el numero de vueltas que dio la lina  *                                
 ****************************************************************************/
struct Linea{
    string Product;
    int Num_Linea;
    int Producto_a_realizar;
    int Producto_realizado;
    int num_vueltas;
    };
/************************************************************************************
 *  Funciones declaradas                                                            *
 * @IniciarTurno: Funcion vacia que recibe tipo de dato Linea, entero y booleana    *
 * y es mandada traer cuando el usuario inicia el turno                             *
 * @TerminarTurno: Funcion vacia que recibe tipo de dato Linea, entero y booleana   *
 * y es mandada traer cuando el usuario termina el turno                            *
 * @endClip: Funcion que se manda traer cuando El bucle do/while necesita confirmar *
 * si termina o no                                                                  *
 * @Menu: Funcion vacia y que no recibe nada muestra el menu                        *
 * @counter:Funcion vacia que recibe una direccion de memoria de un entero que      *
 * lleva un contador de cuantos turnos han sido procesados                          *
 ***********************************************************************************/
void IniciarTurno(Linea *linea, int n, bool&);
void TerminarTurno(Linea *linea, int n, bool&);
void endClip(bool & clip);
void Menu();
void counter(int &u);

int main(){
/**********************************************************************************************
 *  Variables del subprograma principal                                                       *
 * @time: Variable de tipo clock_t para contar el tiempo de ejecucion/duracion de turno       *
 * @numLineas: Variable de tipo entero que nos dice la cantidad de lineas a guardar           *
 * @respuesta: Variable de tipo entero que guarda la opcion del menu a seguir                 *
 * @opcion: Cadena de texto que guarda la respuesta del menu en caracteres                    *
 * @un: Cadena de texto que guarda la respuesta del numero de lineas en caracteres            *
 * @clip: Variable de tipo booleana que nos ayuda a terminar el bucle do/while                *
 * @clipTurno: Variable de tipo booleana que no permite que un turno termine sin haber        *
 *  antes iniciado                                                                            *
 * @archive: Variable de tipo booleana que no permite si el archivo de texto ya fue creado    *
 * @linea: Variable de tipo Linea                                                             *
 * @ptr: Arreglo de apuntador a funciones que tiene las funciones de iniciar y terminar turno *
 * @CounterTurns: Variable de tipo entero que nos permite Saber cuantos turnos han iniciado   *
 *********************************************************************************************/
    clock_t time = clock();
    int CounterTurns=0;
    int numLineas, respuesta;
    string opcion, un;
    bool clip = true;
    bool clipTurno=false;
    bool archive=false;
    Linea *linea;
    void (*ptr[])(Linea*,int, bool&)={IniciarTurno, TerminarTurno};
    // thread th(&ejec);
    // th.join();
/***********************************************
 *  Bucle do/while                             *
 * Permite repetir la veces necesarias todos   *
 * los pasos por si el usuario se equivoca     *
 **********************************************/
    do{
        Menu();
        try{
            /************************************************************
            *  stoi e isdigital                                         *
            * logica del codigo para verificar que el resultado no      *
            * sean caracteres y arroje sus correspondientes excepciones *
            * @stoi: Combierte de string a entero                       *
            * @isdigital: Verifica que sea un entero                    *
            * Esta logica se repetira varias veces durante el codigo    *
            ************************************************************/
            cin>>opcion;
            respuesta=(stoi(opcion));
            //if(isdigit(res)){
            //  throw invalid_argument("\nargumento invalido\n");
            //}
            isdigit(respuesta);
            }catch(out_of_range &ii){
                cout<<"Fuera de rango";
            }catch(overflow_error &overfl){
                cout<<overfl.what();
               // return -3;
            }catch(invalid_argument &argume){
                cout<<"\nArgumento invalido\n";
              //  return -4;
            }
/***********************************************
 *  Switch                                     *
 * Para utilizar la funcion correspondiente de *
 * la respuesta                                *
 **********************************************/
         switch(respuesta){
            case 1:
                cout<<"Cuantas lineas son ";
                try{
                    try{
                        cin>>un;
                        numLineas=(stoi(un));
                        isdigit(numLineas);
                        if(numLineas>32767){
                            throw overflow_error("\nError de desbordamiento\n");
                            }
                        }catch(out_of_range &ii){
                            cout<<"Fuera de rango";
                        }catch(overflow_error &overfl){
                            cout<<overfl.what();
                        }catch(invalid_argument &argume){
                            cout<<"\nArgumento invalido\n";
                        }
                    linea=new Linea[numLineas];
                    ptr[respuesta-1](linea,numLineas, archive);
                    endClip(clip);
                }catch(bad_alloc &mem){
                    cout<<"\nNo se pudo alojar la memoria\n";
                    return -2;
                }catch(invalid_argument &argume){
                    cout<<"\n\nArgumento invalido\n";
                    //return -4;
                }catch(overflow_error &overfl){
                    cout<<overfl.what();
                    return -3;
                }catch (InInvalidArgument &invc){
                    cout<<invc.what()<<endl;
                }catch(InNegativCase &numn){
                    cout<<numn.what()<<endl;
                }
                clipTurno=true;

            break;
            case 2:
                if(clipTurno==true){
                try{
                    ptr[respuesta-1](linea,numLineas, archive);
                    endClip(clip);
                    thread thh(&counter,ref(CounterTurns));
                    thh.join();
                }catch(overflow_error &overfl){
                cout<<overfl.what();
                return -3;
                }catch(invalid_argument &argume){
                cout<<"\nArgumento invalido\n";
                //return -4;
                }catch (InInvalidArgument &invc){
                    cout<<invc.what()<<endl;
                }catch(InNegativCase &numn){
                    cout<<numn.what()<<endl;
                }
                }else{
                cout<<"\nPrimero se necesita iniciar turno\n\n";
                }
            break;
            case 3:
                clip=false;
            break;
            default:
                 cout<<"\nOpcion no valida\n"<<endl;
            break;
        }



    }while(clip);
    time = (clock() - time)/1000;
    cout<<"\n\nTiempo de ejecucion: "<<time<<"segs"<<endl;
    cout<<CounterTurns<<"  Turno iniciados"<<endl;
    delete[]linea;
    return 0;
}

void endClip(bool &clip){
/***********************************************
 *  Variables de el subprograma endClip        *
 * @mainClip: variable de tipo booleano que    *
 * nos ayuda a detener el ciclo do/while       *
 * @clip: direccion de memoria de la variable  *
 * clip del subprograma princial               *
 * @respuesta:Cadena de caracteres que guarda  *
 * la respuesta ingresada por el usuario       *
 * @opcion:Variable de tipo entero que tiene el*
 * numero que decide si continuara o           *
 * no el programa                              *
 **********************************************/
    bool mainClip=true;
    string opcion;
    int respuesta;
    do{
        cout<<"\nDesea Continuar 1 si/ 2 no ";
        try{
            cin>>opcion;
            respuesta=(stoi(opcion));
            isdigit(respuesta);
            }catch(out_of_range &ii){
                cout<<"Fuera de rango";
            }catch(overflow_error &overfl){
                cout<<overfl.what();
            }catch(invalid_argument &argume){
                cout<<"\nArgumento invalido\n";
            }
        switch(respuesta){
        case 1:
            clip= true;
            mainClip= false;
        break;
        case 2:
            clip= false;
            mainClip= false;
        break;
        default:
            cout<<"Lo siento no entendi, vuelve a intentarlo"<<endl;
        break;

        }

    }while(mainClip);
}
void Menu(){
    cout<<"1.- Iniciar turno"<<endl
        <<"2.- Terminar turno "<<endl
        <<"3.- Salir "<<endl;

}
void IniciarTurno(Linea * linea, int n, bool &archive){
    string opcion,opcion2;
    for(int i=0;i<n;i++){
        do{
        cout<<"\nNumero Linea :";
        cin>> opcion;
        linea[i].Num_Linea=(stoi(opcion));
        isdigit(linea[i].Num_Linea);
        if(linea[i].Num_Linea<1){
            throw InNegativCase();
        }
        }while(linea[i].Num_Linea<1);
		cout<<"Nombre del Producto que se realiza:";
		cin>> linea[i].Product;
		cout<<"Cantidad de producto planeado :";
		cin>> opcion2;
        linea[i].Producto_a_realizar=(stoi(opcion2));
		isdigit(linea[i].Producto_a_realizar);
		if(linea[i].Producto_a_realizar>32767){
            throw overflow_error("\nError de desbordamiento\n");
        }
        if(linea[i].Producto_a_realizar<1){
            throw InNegativCase();
        }
		cout<<"\n";
        }
}
void counter(int &CounterTurns){
       CounterTurns++;
}
void TerminarTurno(Linea * linea, int n, bool &archive){
        string opcion,opcion2;
        for(int i=0;i<n;i++){
        cout<<"\nLinea "<<linea[i].Num_Linea<<endl;
        cout<<"Numero de producto realizado:";
        cin>> opcion;
        linea[i].Producto_realizado=(stoi(opcion));
        isdigit(linea[i].Producto_realizado);
		if(linea[i].Producto_realizado>32767){
            throw overflow_error("\nError de desbordamiento\n");
        }
        if(linea[i].Producto_realizado<1){
            throw InNegativCase();
        }
		cout<<"Numero de cilos terminados por la linea :";
		cin>> opcion2;
        linea[i].num_vueltas=(stoi(opcion2));
        isdigit(linea[i].num_vueltas);
		if(linea[i].num_vueltas>32767){
            throw overflow_error("\nError de desbordamiento\n");
        }
        if(linea[i].num_vueltas<1){
            throw InNegativCase();
        }
        }
        cout<<"\n"<<endl;
/***********************************************
 *  if para ver si ya existe un archivo        *
 * si no existe crea un archivo .txt para      *
 * guardar todos los datos recopilados         *
 * en el turno                                 *
 **********************************************/
        if(archive==false){
        ofstream archivo("Reporte.txt");
        for(int i=0;i<n;i++){
        cout<<"\n\nNumero linea: "<<linea[i].Num_Linea<<endl;
		cout<<"Producto: "<<linea[i].Product<<endl;
		cout<<"Numero producto planeado: "<< linea[i].Producto_a_realizar<<endl;
        cout<<"Numero de producto realizado: "<<linea[i].Producto_realizado<<endl;
		cout<<"Numero vueltas: "<<linea[i].num_vueltas<<endl;

        archivo<<"\n\nNumero linea: "<<linea[i].Num_Linea<<endl;
        archivo<<"Producto: "<<linea[i].Product<<endl;
		archivo<<"Numero producto planeado: "<< linea[i].Producto_a_realizar<<endl;
        archivo<<"Numero de producto realizado: "<<linea[i].Producto_realizado<<endl;
		archivo<<"Numero vueltas: "<<linea[i].num_vueltas<<endl;

        }

        archivo.close();
        archive=true;
        }
 /***********************************************
 *  Si el archivo ya estaba creado solo lo sobre*
 * escribe, ya no lo crea                       *
 ***********************************************/       
        else{

        fstream archivo("Datos.txt",ios::app);
        for(int i=0;i<n;i++){
        cout<<"\n\nNumero linea: "<<linea[i].Num_Linea<<endl;
		cout<<"Producto: "<<linea[i].Product<<endl;
		cout<<"Numero producto planeado: "<< linea[i].Producto_a_realizar<<endl;
        cout<<"Numero de producto realizado: "<<linea[i].Producto_realizado<<endl;
		cout<<"Numero vueltas: "<<linea[i].num_vueltas<<endl;

        archivo<<"\n\nNumero linea: "<<linea[i].Num_Linea<<endl;
        archivo<<"Producto: "<<linea[i].Product<<endl;
		archivo<<"Numero producto planeado: "<< linea[i].Producto_a_realizar<<endl;
        archivo<<"Numero de producto realizado: "<<linea[i].Producto_realizado<<endl;
		archivo<<"Numero vueltas: "<<linea[i].num_vueltas<<endl;
        archivo.close();

        }

        archivo.close();
        }
}
