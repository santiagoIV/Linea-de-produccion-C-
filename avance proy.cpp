#include <iostream>
#include <cassert>
#include <fstream>
#include <cctype>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;
//struct : public exception{
	//const char* what() const throw(){
		//return  "opcion no valida";
	//}
//};
struct Linea{
    string Product;
    int Num_Linea;
    int Producto_a_realizar;
    int Producto_realizado;
    int num_vueltas;
    };
void IniciarTurno(Linea *linea, int n);
void TerminarTurno(Linea *linea, int n);
void endClip(bool & clip);
void Menu();

int main(){
    clock_t time = clock();
    int n,res,  p;
    string opc;
    bool clip = true;
    Linea *linea;
    void (*ptr[])(Linea*,int)={IniciarTurno, TerminarTurno};
    do{
        Menu();
        try{
            cin>>opc;
            res= (stoi(opc));
        //if(isdigit(res)){
          //  throw invalid_argument("\nargumento invalido\n");
        //}
            isdigit(res);
            if(res>32767){
                throw overflow_error("\nerror de desbordamiento\n");
            }
            }catch(overflow_error &overfl){
                cout<<overfl.what();
                return -3;
            }catch(invalid_argument &argume){
                cout<<"\nargumento invalido\n";
                return -4;
            }
         switch(res){

            case 1:
                cout<<"Cuantas lineas son ";
                cin>>n;
                try{
                    linea=new Linea[n];
                    ptr[res-1](linea,n);
                    endClip(clip);
                }catch(bad_alloc &mem){
                    cout<<"\nno se pudo alojar la memoria\n";
                    return -2;
                }catch(overflow_error &overfl){
                    cout<<overfl.what();
                    return -3;
                }catch(invalid_argument &argume){
                    cout<<"\nargumento invalido\n";
                    return -4;
            }
            break;
            case 2:
                ptr[res-1](linea,n);
                try{
                    endClip(clip);
                }catch(overflow_error &overfl){
                cout<<overfl.what();
                return -3;
                }catch(invalid_argument &argume){
                cout<<"\nargumento invalido\n";
                return -4;
                }
            break;
            case 3:
                clip=false;
            break;
            default:
                 cout<<"\nopcion no valida\n"<<endl;
            break;
        }



    }while(clip==true);
    time = (clock() - time)/1000;
    cout<<"Tiempo de ejecucion: "<<time<<"segs"<<endl;
    delete[]linea;
    return 0;
}
void endClip(bool &clip){

    bool Clip=true;
    string tinue;
    int con;
    do{
        cout<<"\nDesea Continuar 1 si/ 2 no ";
        cin>>tinue;
        int con= (stoi(tinue));
        isdigit(con);
        if(con>32767){
            throw overflow_error("\nerror de desbordamiento\n");
        }
        switch(con){
        case 1:
            clip= true;
            Clip= false;
        break;
        case 2:
            clip= false;
            Clip= false;
        break;
        default:
            cout<<"Lo siento no entendi, vuelve a intentarlo"<<endl;
        break;

        }

    }while(Clip);
}
void Menu(){
    cout<<"1.- Iniciar turno"<<endl
        <<"2.- Terminar turno "<<endl
        <<"3.- Salir "<<endl;

}
void IniciarTurno(Linea * linea, int n){
    for(int i=0;i<n;i++){
        cout<<"\nnumero Linea :";
        cin>> linea[i].Num_Linea;
		cout<<"Producto :";
		cin>> linea[i].Product;
		cout<<"numero producto planeado :";
		cin>> linea[i].Producto_a_realizar;
		cout<<"\n";
        }
}

void TerminarTurno(Linea * linea, int n){


        for(int i=0;i<n;i++){
        cout<<"\nlinea "<<linea[i].Num_Linea<<endl;
        cout<<"Numero de producto realizado:";
        cin>> linea[i].Producto_realizado;
		cout<<"numero vueltas :";
		cin>> linea[i].num_vueltas;
        }
        cout<<"\n"<<endl;
        ofstream archivo("Datos.txt");
        for(int i=0;i<n;i++){
        cout<<"\n\nnumero linea: "<<linea[i].Num_Linea<<endl;
		cout<<"Producto: "<<linea[i].Product<<endl;
		cout<<"numero producto planeado: "<< linea[i].Producto_a_realizar<<endl;
        cout<<"numero de producto realizado: "<<linea[i].Producto_realizado<<endl;
		cout<<"numero vueltas: "<<linea[i].num_vueltas<<endl;

        archivo<<"\n\nnumero linea: "<<linea[i].Num_Linea<<endl;
        archivo<<"Producto: "<<linea[i].Product<<endl;
		archivo<<"numero producto planeado: "<< linea[i].Producto_a_realizar<<endl;
        archivo<<"numero de producto realizado: "<<linea[i].Producto_realizado<<endl;
		archivo<<"numero vueltas: "<<linea[i].num_vueltas<<endl;

        }
        archivo.close();
}
