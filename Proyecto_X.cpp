#include <fstream>
#include <stdio.h>
#include <string>
#include <iostream>
using namespace std; 
// creacion de structuras
struct cancion{
    int fecha;
    int id;
    string nombre;
    string artista;
    string genero;
    string mg;
    cancion *prxc,*prvc;
};
struct usuario{
    int idu;
    int edad;
    string nombreu;
    string correo;
    string cntr;
    string pais;
    usuario *prxu,*prvu;
};
cancion *canciones=NULL; // creacion de la lista vacia
usuario *usuarios=NULL; // creacion de la lista vacia
// funciones y algoritmos de canciones
int ultimoIDc;
int valoridc(cancion *canciones){
    if(!canciones){
        return 0;
    }
    system("cls");
    cancion *actual = canciones;
    cancion *previo = NULL;
    while(actual != NULL){
        previo = actual;
        actual = actual->prxc;
    }
    return previo->id;
}
int generarNuevoIDc() {
    ultimoIDc++;
    return ultimoIDc;
}
void insertarcancion(cancion *&canciones,int fecha,int id,string nombre, string artista, string genero, string mg){
    cancion *nuevo = new cancion();
    nuevo->id = id ;
    nuevo->nombre = nombre ;
    nuevo->artista = artista ;
    nuevo->genero = genero ;
    nuevo->fecha = fecha ;
    nuevo->mg = "no";
    nuevo->prxc=NULL;
    nuevo->prvc=NULL;

    if(canciones == NULL || canciones->id > id){
        nuevo->prxc = canciones;
        if(canciones != NULL){
            canciones->prvc = nuevo;
        }
        canciones = nuevo;
    } else {
        cancion *actual = canciones;
        while(actual->prxc != NULL && actual->prxc->id < id){
            actual = actual->prxc;
        }
        nuevo->prxc = actual->prxc;
        if(actual->prxc != NULL){
            actual->prxc->prvc = nuevo;
        }
        actual->prxc = nuevo;
        nuevo->prvc = actual;
    }
}
void insertarcancionb(cancion *&canciones,int fecha,int id,string nombre, string artista, string genero, string mg){
    cancion *nuevo = new cancion();
    nuevo->id = id ;
    nuevo->nombre = nombre ;
    nuevo->artista = artista ;
    nuevo->genero = genero ;
    nuevo->fecha = fecha ;
    nuevo->mg = mg;
    nuevo->prxc=NULL;
    nuevo->prvc=NULL;

    if(canciones == NULL || canciones->id > id){
        nuevo->prxc = canciones;
        if(canciones != NULL){
            canciones->prvc = nuevo;
        }
        canciones = nuevo;
    } else {
        cancion *actual = canciones;
        while(actual->prxc != NULL && actual->prxc->id < id){
            actual = actual->prxc;
        }
        nuevo->prxc = actual->prxc;
        if(actual->prxc != NULL){
            actual->prxc->prvc = nuevo;
        }
        actual->prxc = nuevo;
        nuevo->prvc = actual;
    }
}
void ordenararch(cancion *canciones, string nombreArchivo) {
    ofstream archivo(nombreArchivo);
    cancion *actual = canciones;

    if (archivo.is_open()) {
        while (actual != NULL) {
            archivo << actual->nombre << "-" << actual->artista << "-" << actual->genero << "-" << actual->fecha << "-" << actual->id << "-" << actual->mg << "\n";
            actual = actual->prxc;
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo\n";
    }
}
void insertararch(cancion *&canciones,string nombreArchivo,int fecha,int id,string nombre, string artista, string genero, string mg){
    insertarcancion(canciones, fecha , id, nombre, artista, genero,mg);
    ifstream archivo;
    ofstream aux;
    string linea;
    int x = 0;

    archivo.open(nombreArchivo);
    aux.open("temp.txt");

    while (getline(archivo, linea)) {
        x++;
            aux << linea << endl;
    }
    string nombrea = string(nombre);
    string artistaa = string(artista);
    string generoa = string(genero);
    string fecha_str = to_string(fecha); 
    string id_str = to_string(id); 
    string lineamod= nombrea+"-"+artistaa+"-"+generoa+"-"+fecha_str+"-"+id_str+"-"+mg;
    aux << lineamod << endl;

    archivo.close();
    aux.close();

    remove(nombreArchivo.c_str());
    rename("temp.txt", nombreArchivo.c_str());
}
void cargararchivocanciones(string nombreArchivo) {
    ifstream archivo(nombreArchivo);
    string linea;
    char chrnombre[50], chrartista[50], chrgenero[50], chrmg[50];
    int fecha, id;

    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            if (!linea.empty()) {
                sscanf(linea.c_str(), "%[^-]-%[^-]-%[^-]-%d-%d-%[^\n]", &chrnombre[0], &chrartista[0], &chrgenero[0], &fecha, &id, &chrmg[0]);
                string nombre = string(chrnombre);
                string artista = string(chrartista);
                string genero = string(chrgenero);
                string mg = string(chrmg);
                insertarcancionb(canciones, fecha , id, nombre, artista, genero,mg);
            }
        }
        archivo.close();
    } else {
        cout<<"No se pudo abrir el archivo\n";
    }
}

void mostrarlistacanciones(cancion *&canciones){
    system("cls");
    cancion *actual = canciones;
    while(actual != NULL){
        cout<<"cancion #"<<actual->id<<":\n"<<"["<<actual->nombre<<"-"<<actual->artista<<"-"<<actual->genero<<"-"<<actual->fecha<<"]"<<"("<<actual->mg<<" esta en tus me gusta)\n";
        actual = actual->prxc;
    }
}
void megusta(cancion *&canciones,int id){
    cancion *actual = canciones;
    while(actual){
        if( id == actual->id){
            actual -> mg = "si";
        }
        actual = actual->prxc;
    }
}
void megustaarch(cancion *canciones,string nombreArchivo,int id){
    megusta(canciones,id);
    ifstream archivo;
    ofstream aux;
    string linea,lineamod;
    char chrnombre[50], chrartista[50], chrgenero[50], chrmg[50];
    int fecha;
    int y=0,x = 0;

    archivo.open(nombreArchivo);
    aux.open("temp.txt");

    while (getline(archivo, linea)) {
        y++;
        if (y != id)
            aux << linea << endl;
    }
    archivo.close(); 

    archivo.open(nombreArchivo); 
    while (getline(archivo, linea)) {
        x++;
        if (x == id){
            sscanf(linea.c_str(), "%[^-]-%[^-]-%[^-]-%d-%[^\n]", &chrnombre[0], &chrartista[0], &chrgenero[0], &fecha, &chrmg[0]);
            string nombre = string(chrnombre);
            string artista = string(chrartista);
            string genero = string(chrgenero);
            string mg = string(chrmg);
            string fecha_str = to_string(fecha); 
            string id_str = to_string(id); 
            string lineamod= nombre+"-"+artista+"-"+genero+"-"+fecha_str+"-"+id_str+"-si";
            aux << lineamod << endl;
        }
    }
    archivo.close();
    aux.close();

    remove(nombreArchivo.c_str());
    rename("temp.txt", nombreArchivo.c_str());
}
bool verificarid(cancion *&canciones, int id){
    cancion *actual = canciones;
    while(actual){
        if( id == actual->id){
            actual = canciones;
            return true;
        }
        actual = actual->prxc;
    }
    return false;
}
void eliminarcancionlista(cancion *&canciones, int id){
    cancion *actual = canciones;
    cancion *prev = NULL;
    while(actual != NULL){
        if(actual->id == id){
            if(prev == NULL){
                canciones = actual->prxc;
                if(canciones != NULL){
                    canciones->prvc = NULL;
                }
            }
            else{
                prev->prxc = actual->prxc;
                if(actual->prxc != NULL){
                    actual->prxc->prvc = prev;
                }
            }
            delete actual;
            return;
        }
        prev = actual;
        actual = actual->prxc;
    }
}
void eliminarcancionarch(cancion *&canciones,string nombreArchivo,int id) {
    eliminarcancionlista(canciones,id);
    ifstream archivo;
    ofstream aux;
    string linea;
    int x = 0;

    archivo.open(nombreArchivo);
    aux.open("temp.txt");

    while (getline(archivo, linea)) {
        x++;
        if (x != id)
            aux << linea << endl;
    }

    archivo.close();
    aux.close();

    remove(nombreArchivo.c_str());
    rename("temp.txt", nombreArchivo.c_str());
}
//funciones y algoritmos de usuarios
int ultimoIDu;
int valoridu(usuario *usuarios){
    if(!usuarios){
        return 0;
    }
    system("cls");
    usuario *actual = usuarios;
    usuario *previo = NULL;
    while(actual != NULL){
        previo = actual;
        actual = actual->prxu;
    }
    return previo->idu;
}
int generarNuevoIDu() {
    ultimoIDu++;
    return ultimoIDu;
}
int encontrarid(usuario *&usuarios,string correo){
     usuario *actual = usuarios;
    while(actual){
        if( correo == actual->correo){
            return actual->idu;
        }
        actual = actual->prxu;
    }
    return actual->idu;
}
void insertarusuario(usuario *&usuarios,int edad,int idu,string nombreu, string correo, string cntr, string pais){
    usuario *nuevo = new usuario();
    nuevo->idu = idu;
    nuevo->edad = edad ;
    nuevo->nombreu = nombreu ;
    nuevo->correo = correo ;
    nuevo->cntr = cntr ;
    nuevo->pais = pais;
    nuevo->prxu=NULL;
    nuevo->prvu=NULL;

    if(usuarios == NULL || usuarios->idu > idu){
        nuevo->prxu = usuarios;
        if(usuarios != NULL){
            usuarios->prvu = nuevo;
        }
        usuarios = nuevo;
    } else {
        usuario *actual = usuarios;
        while(actual->prxu != NULL && actual->prxu->idu < idu){
            actual = actual->prxu;
        }
        nuevo->prxu = actual->prxu;
        if(actual->prxu != NULL){
            actual->prxu->prvu = nuevo;
        }
        actual->prxu = nuevo;
        nuevo->prvu = actual;
    }
}
void insertarusuariob(usuario *&usuarios,int edad,int idu,string nombreu, string correo, string cntr, string pais){
    usuario *nuevo = new usuario();
    nuevo->idu = idu;
    nuevo->edad = edad ;
    nuevo->nombreu = nombreu ;
    nuevo->correo = correo ;
    nuevo->cntr = cntr ;
    nuevo->pais = pais;
    nuevo->prxu=NULL;
    nuevo->prvu=NULL;

    if(usuarios == NULL || usuarios->idu > idu){
        nuevo->prxu = usuarios;
        if(usuarios != NULL){
            usuarios->prvu = nuevo;
        }
        usuarios = nuevo;
    } else {
        usuario *actual = usuarios;
        while(actual->prxu != NULL && actual->prxu->idu < idu){
            actual = actual->prxu;
        }
        nuevo->prxu = actual->prxu;
        if(actual->prxu != NULL){
            actual->prxu->prvu = nuevo;
        }
        actual->prxu = nuevo;
        nuevo->prvu = actual;
    }
}
void ordenararchu(usuario *usuarios, string nombreArchivo) {
    ofstream archivo(nombreArchivo);
    usuario *actual = usuarios;

    if (archivo.is_open()) {
        while (actual != NULL) {
            archivo << actual->nombreu << "-" << actual->correo << "-" << actual->cntr << "-" << actual->edad << "-" << actual->idu << "-" << actual->pais << "\n";
            actual = actual->prxu;
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo\n";
    }
}
void insertararchu(usuario *&usuarios,string nombreArchivo,int edad,int idu,string nombreu, string correo, string cntr, string pais){
 insertarusuariob(usuarios, edad , idu, nombreu, correo, cntr,pais);
    ifstream archivo;
    ofstream aux;
    string linea;
    int x = 0;

    archivo.open(nombreArchivo);
    aux.open("temp.txt");

    while (getline(archivo, linea)) {
        x++;
            aux << linea << endl;
    }
    string nombreuu = string(nombreu);
    string correou = string(correo);
    string cntru = string(cntr);
    string paisu = string(pais);
    string edad_str = to_string(edad); 
    string idu_str = to_string(idu); 
    string lineamod= nombreuu+"-"+correou+"-"+cntru+"-"+edad_str+"-"+idu_str+"-"+paisu;
    aux << lineamod << endl;

    archivo.close();
    aux.close();

    remove(nombreArchivo.c_str());
    rename("temp.txt", nombreArchivo.c_str());
}
void cargararchivousuarios(string nombreArchivo) {
    ifstream archivo(nombreArchivo);
    string linea;
    char chrnombre[50], chrcorreo[50], chrcntr[50], chrpais[50];
    int edad, idu;

    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            if (!linea.empty()) {
                sscanf(linea.c_str(), "%[^-]-%[^-]-%[^-]-%d-%d-%[^\n]", &chrnombre[0], &chrcorreo[0], &chrcntr[0], &edad, &idu, &chrpais[0]);
                string nombreu = string(chrnombre);
                string correo = string(chrcorreo);
                string cntr = string(chrcntr);
                string pais = string(chrpais);
                insertarusuariob(usuarios,edad,idu,nombreu,correo,cntr,pais);
            }
        }
        archivo.close();
    } else {
        cout<<"No se pudo abrir el archivo\n";
    }
}
void mostrarlistausuarios(usuario *&usuarios){
    system("cls");
    usuario *actual = usuarios;
    while(actual != NULL){
        cout<<"id de usuario #"<<actual->idu<<":\n"<<"["<<actual->nombreu<<"-"<<actual->correo<<"-"<<actual->pais<<"-"<<actual->edad<<"]\n";
        actual = actual->prxu;
    }
}
bool verificarcorreo(usuario *&usuarios, string correo){
    usuario *actual = usuarios;
    while(actual){
        if( correo == actual->correo){
            actual = usuarios;
            return true;
        }
        actual = actual->prxu;
    }
    return false;
}
bool verificarcntr(usuario *&usuarios, string cntr,string correo){
    usuario *actual = usuarios;
    while(actual){
        if( correo == actual->correo){
            if(cntr == actual->cntr){
            actual = usuarios;
            return true;}
        }
        actual = actual->prxu;
    }
    return false;
}
void eliminarusuariolista(usuario *&usuarios, int idu){
    usuario *actual = usuarios;
    usuario *prev = NULL;
    while(actual != NULL){
        if(actual->idu == idu){
            if(prev == NULL){
                usuarios = actual->prxu;
                if(usuarios != NULL){
                    usuarios->prvu = NULL;
                }
            }
            else{
                prev->prxu = actual->prxu;
                if(actual->prxu != NULL){
                    actual->prxu->prvu = prev;
                }
            }
            delete actual;
            return;
        }
        prev = actual;
        actual = actual->prxu;
    }
}
void eliminarusuariosarch(usuario *&usuarios,string nombreArchivo,int idu) {
    eliminarusuariolista(usuarios,idu);
    ifstream archivo;
    ofstream aux;
    string linea;
    int x = 0;

    archivo.open(nombreArchivo);
    aux.open("temp.txt");

    while (getline(archivo, linea)) {
        if (!linea.empty()) {
        x++;
        if (x != idu)
            aux << linea << endl;
        }
    }

    archivo.close();
    aux.close();

    remove(nombreArchivo.c_str());
    rename("temp.txt", nombreArchivo.c_str());
}
//menu cancion
void menucancion(){
    int fecha, id,opcion2;
    string nombre, artista, genero,rsp,mg,rutacancion;
    rutacancion="c:\\Users\\cesar\\Desktop\\c\\ucabifydat.txt";
    do
    {
        system("cls");
        cout<<"Ucabify\n";
        cout<<"--------------------------------------\n";
        cout<< "\tMenu de canciones\n";
        cout<<"--------------------------------------\n";
        cout<< "1. mostrar canciones agregadas y darles me gusta\n";
        cout<< "2. insertar una nueva cancion \n";
        cout<< "3. eliminar una cancion \n";
        cout<<"--------------------------------------\n";
        cout<< "0. volver al menu anterior\n";
        cout<< "Indique su opcion->";
        cin >> opcion2;
        switch (opcion2)
        {
            case 1:
                system("cls");
                mostrarlistacanciones(canciones);
                cout<<"desea darle me gusta a alguna de estas canciones? y/n: \n";
                cin>>rsp;
                    if(rsp == "y" || rsp == "Y"){
                        cout<<"indique el identificador numerico de la cancion que desea agregar a tus me gusta: ";
                        cin>> id;
                            if(verificarid(canciones, id) == true){
                                megustaarch(canciones,rutacancion,id);
                                ordenararch(canciones,rutacancion);
                                system("cls");
                                cout<<"su cancion fue agregada a tus me gusta con exito! \n";
                                system("pause");
                                break;
                            }
                            else
                            system("cls");
                            cout<<"el identificador proporcionado no se encuentra en su lista de canciones agregadas porfavor intente con un identificador numerico distinto\n ";
                            system("pause");
                            break;
                    }
                system("pause");
                break;
            case 2:
                system("cls");
                ultimoIDc=valoridc(canciones);
                id=generarNuevoIDc();
                cout<<"digite el nombre de la cancion: ";
                cin >> nombre;
                cout << "digite el año de la cancion: ";
                cin >> fecha;
                cout<<"digite el artista de la cancion: ";
                cin >> artista;
                cout<<"digite el genero de la cancion: ";
                cin >> genero;
                system("cls");
                insertararch(canciones,rutacancion, fecha , id, nombre, artista, genero,mg);
                ordenararch(canciones,rutacancion);
                cout<<"cancion agregada con exito \n";
                system("pause");
                break;
            case 3:
                system("cls");
                cout<<"indique el identificador numerico de la cancion que desea eliminar: ";
                cin>> id;
                    if(verificarid(canciones, id) == true){
                        eliminarcancionarch(canciones,rutacancion,id);
                        ordenararch(canciones,rutacancion);
                        cout<<"su cancion fue eliminada con exito! \n ";
                        system("pause");
                        break;
                    }
                    else{
                        system("cls");
                        cout<<"el identificador proporcionado no se encuentra en su lista de canciones agregadas porfavor intente con un identificador numerico distinto\n";
                        system("pause");
                        break;
                    }
        }       
    }while (opcion2 != 0);
}
// menu usuario
void menuusuario(){
    int edad, idu,opcion3;
    string nombreu, correo, cntr,alt,pais,rutausuario;
    rutausuario="C:\\Users\\cesar\\Desktop\\c\\usuariosdat.txt";
    do
    {
        system("cls");
        cout<<"Ucabify\n";
        cout<<"--------------------------------------\n";
        cout<< "\tMenu de usuarios\n";
        cout<<"--------------------------------------\n";
        cout<< "1. mostrar usuarios en el sistema\n";
        cout<< "2. insertar una nuevo usuario \n";
        cout<< "3. eliminar un usuario \n";
        cout<<"--------------------------------------\n";
        cout<< "0. volver al menu anterior\n";
        cout<< "Indique su opcion->";
        cin >> opcion3;
        switch (opcion3)
        {
            case 1:
                system("cls");
                mostrarlistausuarios(usuarios);
                system("pause");
                break;
            case 2:
                system("cls");
                cout<<"digite el correo de la cuenta: ";
                cin >> correo;
                    if(verificarcorreo(usuarios, correo) == true){
                        system("cls");
                        cout<<"este correo ya se encuentra en el sistema porfavor vuelva a intentarlo con un correo diferente\n";
                        system("pause");
                        break;
                    }
                cout<<"digite la clave del usuario: ";
                cin >> cntr;
                system("cls");
                cout<<"usuario creado con exito porfavor llene estos datos para registrarlo en el sistema\n";
                system("pause");
                system("cls");
                cout<<"digite el nombre de usuario: ";
                cin >> nombreu;
                cout<<"digite la edad del usuario: ";
                cin >> edad;
                cout<<"digite el pais de origen del usuario: ";
                cin >> pais;
                ultimoIDu=valoridu(usuarios);
                idu=generarNuevoIDu();
                insertararchu(usuarios,rutausuario, edad , idu, nombreu, correo, cntr,pais);
                ordenararchu(usuarios,rutausuario);
                ultimoIDu=valoridu(usuarios);
                system("cls");
                cout<<"usuario registrado en el sistema con exito \n";
                system("pause");
                break;
            case 3:
                system("cls");
                cout<<"indique el correo del usuario que desea eliminar: ";
                cin >> correo;
                    if(verificarcorreo(usuarios, correo) == true){
                        system("cls");
                        cout<<"indique la clave del usuario que desea eliminar: ";
                        cin >> cntr;
                        if(verificarcntr(usuarios,cntr,correo)== true){
                            idu=encontrarid(usuarios,correo);
                            eliminarusuariosarch(usuarios,rutausuario,idu);
                            ordenararchu(usuarios,rutausuario);
                            ultimoIDu=valoridu(usuarios);
                            cout<<"el usuario ha sido eliminado con exito! \n ";
                            system("pause");
                        break;
                        }
                        else{
                            cout<<"contraseña incorrecta intente denuevo! \n ";
                            system("pause");
                            break;
                        }
                        }
                        else{
                        cout<<"el correo indicado no se encuentra en el sistema intente denuevo! \n ";
                        system("pause");
                        break;
                    }
                    }     
    }while (opcion3 != 0);
}
// funcion principal
int main(){
    int opcion, dato;
    string rutacancion,rutausuario;
    rutacancion="c:\\Users\\cesar\\Desktop\\c\\ucabifydat.txt";
    rutausuario="C:\\Users\\cesar\\Desktop\\c\\usuariosdat.txt";
    cargararchivocanciones(rutacancion);
    cargararchivousuarios(rutausuario);
    ultimoIDu=valoridu(usuarios);
    do
    {
        system("cls");
        cout<<"Ucabify\n";
        cout<<"--------------------------------------\n";
        cout<< "\tRealizado por: \n Cesar Machado, 30497388\n Leonel Soares, 30371183\n";
        cout<<"--------------------------------------\n";
        cout<< "\tMenu Principal\n";
        cout<<"--------------------------------------\n";
        cout<< "1. seccion de canciones \n";
        cout<< "2. seccion de usuarios \n";
        cout<< "3. Historial de reproduccion \n";
        cout<<"--------------------------------------\n";
        cout<< "0. Salir de la aplicacion\n";
        cout<< "Indique su opcion->";
        cin >> opcion;
        switch (opcion)
        {
            case 1:
                menucancion();
                break;
            case 2:
                menuusuario();
                break;
            case 3:
                cout<<"no disponible aun\n";
                break;
        }
    }while (opcion != 0);
}