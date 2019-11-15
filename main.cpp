#include <iostream>
#include <cassert>
#include "SerialClass.h"
using namespace std;
struct Linea{
    string Product;
    int Num_Linea, Producto_a_realizar, Producto_realizado, num_vueltas;
};
void IniciarTurno(Linea *linea, int n);
void TerminarTurno(Linea *linea, int n);
void endClip(bool & clip);
void Menu();

int main(){
    Serial* Arduino = new Serial("COM7");
    if( Arduino->IsConnected() ) cout<<"Arduino Conectado";
    char lectura[50];
    Arduino->ReadData(lectura,50);
    int n=0, res=0;
    bool clip = true;
    Linea *linea;
    void (*ptr[])(Linea *linea, int n)={IniciarTurno, TerminarTurno};
do{
    Menu();
    cin>>res;
    if(res<=0||res>=4){
        cout<<"Respuesta no valida "<<endl;
    }
    else if(res>=1||res<=2){
        if(res==1){
            cout<<"Cuantas lineas son ";
            cin>>n;
            linea=new(nothrow) Linea[n];
        }
        ptr[n-1](linea,n);
        endClip(clip);
    }
    else{
        clip=false;
    }

}while(clip);
delete[]linea;
return 0;
}
void endClip(bool &clip){
    bool Clip=true;
    char cl;
    do{
    cout<<"Desea Continuar y/n ";
        cin>>cl;
        if(cl=='y'||cl=='Y'){
            clip= true;
            Clip= false;
        }
        else if(cl=='n'||cl=='N'){
            clip= false;
            Clip= false;
        }
        else{
            cout<<"Lo sieto no entendi, vuelve a intentarlo"<<endl;
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
        cout<<"Linea :";
        cin>> linea[i].Num_Linea;
		cout<<"Producto :";
		cin>> linea[i].Product;
		cout<<"Planeado :";
		cin>> linea[i].Producto_a_realizar;
        }
}

void TerminarTurno(Linea * linea, int n){
    for(int i=0;i<n;i++){
        cout<<"Producto realizado:";
        cin>> linea[i].Producto_realizado;
		cout<<"num vueltas :";
		cin>> linea[i].num_vueltas;
        }

        for(int i=0;i<n;i++){
        cout<<"Linea: "<<linea[i].Num_Linea;
		cout<<"Producto: "<<linea[i].Product;
		cout<<"Planeado: "<< linea[i].Producto_a_realizar;
        cout<<"Producto realizado: "<<linea[i].Producto_realizado;
		cout<<"num vueltas: "<<linea[i].num_vueltas;
        }
}
