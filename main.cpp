#include <iostream>
#include <cassert>
#include <fstream>
using namespace std;
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

    int n, res, p;
    bool clip = true;
    Linea *linea;
    void (*ptr[])(Linea*,int)={IniciarTurno, TerminarTurno};
do{
    Menu();
    cin>>res;
    if(res<0||res>3){
        cout<<"Respuesta no valida "<<endl;
    }
     if(res==1||res==2){
        if(res==1){

            cout<<"Cuantas lineas son ";
            cin>>n;
            linea=new(nothrow) Linea[n];
        }

        ptr[res-1](linea,n);
        endClip(clip);
    }else{
        clip=false;
    }

}while(clip==true);
delete[]linea;
return 0;
}
void endClip(bool &clip){
    bool Clip=true;
    char cl;
    do{
    cout<<"\nDesea Continuar y/n ";
        cin>>cl;
        if(cl=='y'||cl=='Y'){
            clip= true;
            Clip= false;
        }
        else if(cl=='n'||cl=='N'){
            clip= false;
            Clip= false;
        }else{
            cout<<"Lo siento no entendi, vuelve a intentarlo"<<endl;
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
