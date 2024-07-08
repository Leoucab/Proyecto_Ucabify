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
    cancion *prxc,*prvc;
};
struct cancionduplic{
    int fecha;
    int id;
    string nombre;
    string artista;
    string genero;
    string mg;
    int rp;
    cancionduplic *prx1,*prv1;
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
cancionduplic *temp=NULL;
struct user{
    int id1;
    int edad1;
    string nombre1;
    string correo1;
    string cntr1;
    string pais1;
    user *prx1;
    cancionduplic *temp;
};
cancion *canciones=NULL; // creacion de la lista vacia
usuario *usuarios=NULL; // creacion de la lista vacia
user *users=NULL;//creacion de multilista vacia
cancionduplic *cancionesduplic=NULL;//creacion duplic vacia

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
void insertarcancion(cancion *&canciones,int fecha,int id,string nombre, string artista, string genero){
    cancion *nuevo = new cancion();
    nuevo->id = id ;
    nuevo->nombre = nombre ;
    nuevo->artista = artista ;
    nuevo->genero = genero ;
    nuevo->fecha = fecha ;
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
            archivo << actual->nombre << "-" << actual->artista << "-" << actual->genero << "-" << actual->fecha << "-" << actual->id<<"\n";
            actual = actual->prxc;
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo\n";
    }
}
void insertararch(cancion *&canciones,string nombreArchivo,int fecha,int id,string nombre, string artista, string genero){
    insertarcancion(canciones, fecha , id, nombre, artista, genero);
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
    string lineamod= nombrea+"-"+artistaa+"-"+generoa+"-"+fecha_str+"-"+id_str;
    aux << lineamod << endl;

    archivo.close();
    aux.close();

    remove(nombreArchivo.c_str());
    rename("temp.txt", nombreArchivo.c_str());
}
void cargararchivocanciones(string nombreArchivo) {
    ifstream archivo(nombreArchivo);
    string linea;
    char chrnombre[50], chrartista[50], chrgenero[50];
    int fecha, id;

    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            if (!linea.empty()) {
                sscanf(linea.c_str(), "%[^-]-%[^-]-%[^-]-%d-%d", &chrnombre[0], &chrartista[0], &chrgenero[0], &fecha, &id);
                string nombre = string(chrnombre);
                string artista = string(chrartista);
                string genero = string(chrgenero);
                insertarcancion(canciones, fecha , id, nombre, artista, genero);
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
        cout<<"cancion #"<<actual->id<<":\n"<<"["<<actual->nombre<<"-"<<actual->artista<<"-"<<actual->genero<<"-"<<actual->fecha<<"]\n\n";
        actual = actual->prxc;
    }
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
string encontrarnombre(usuario *&usuarios,string correo){
    usuario *actual = usuarios;
    while(actual){
        if( correo == actual->correo){
            return actual->nombreu;
        }
        actual = actual->prxu;
    }
    return actual->nombreu;
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
 insertarusuario(usuarios, edad , idu, nombreu, correo, cntr,pais);
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
                insertarusuario(usuarios,edad,idu,nombreu,correo,cntr,pais);
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
        cout<<"id de usuario #"<<actual->idu<<":\n"<<"["<<actual->nombreu<<"-"<<actual->correo<<"-"<<actual->pais<<"-"<<actual->edad<<"]\n\n";
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
//funciones y algoritmos de user
void historial(int fecha, int id, string nombre, string correo, string artista, string genero, string mg, int rp) {
    string nombrearch = "historial de-" + correo + ".txt";
    ifstream archivo(nombrearch);
    string contenido;
    int maxRp = 0; 

    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            contenido += linea + "\n";
            size_t found = linea.find("-" + to_string(id) + "-");
            if (found != -1) {
                size_t posRp = linea.find("-no-");
                if (posRp != -1) {
                    string rpStr = linea.substr(posRp + 4); 
                    int currentRp = stoi(rpStr);
                    if (currentRp > maxRp) {
                        maxRp = currentRp; 
                    }
                }
            }
        }
        archivo.close();
    }
    rp = maxRp + 1; 
    ofstream aux(nombrearch);
    if (aux.is_open()) {
        string nuevaLinea = nombre + "-" + artista + "-" + genero + "-" + to_string(fecha) + "-" + to_string(id) + "-" +mg + "-" + to_string(rp);
        aux << nuevaLinea << endl << contenido;
        aux.close();
    } else {
        cout << "no se pudo abrir el archivo." << endl;
    }
}
void verHistorial(string correo) {
    string nombrearch = "historial de-" + correo + ".txt";
    ifstream archivo(nombrearch);
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            cout << linea << endl;
        }
        archivo.close();
    } else {
        cout << "no ha escuchado ninguna cancion!"<< endl;
    }
}
void reproducir(user *&users, string correo,int id1) {
    user *actual = users;
    while (actual) {
        if (correo == actual->correo1) {
            cancionduplic *cancion = actual->temp;
            while (cancion) {
                if (id1 == cancion->id) {
                    cancion->rp++;
                    string songName = cancion->nombre;
                    string artistName = cancion->artista;
                    cout << "(" << songName <<"-"<< artistName <<")"<< endl;
                    cout << "   |-------------|" << endl;
                    cout << "       <-- II -->" << "\n";
                    cout<<"si desea terminar de escuchar esta cancion presione cualquier tecla!";
                    system("pause");
                    historial(cancion->fecha, cancion->id, cancion->nombre,correo,cancion->artista,cancion->genero,cancion->mg,cancion->rp);
                }
                cancion = cancion->prx1;
            }
        }
        actual = actual->prx1;
    }
    
    return; 
}
void insertarsongarch(string nombreArchivo,int fecha,int id,string nombre, string artista, string genero){
    ifstream archivo;
    ofstream aux;
    string linea;
    int x = 0,y=0;

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
    string rp = to_string(y);
    string lineamod= nombrea+"-"+artistaa+"-"+generoa+"-"+fecha_str+"-"+id_str+"-no-"+rp;
    aux << lineamod << endl;

    archivo.close();
    aux.close();

    remove(nombreArchivo.c_str());
    rename("temp.txt", nombreArchivo.c_str());
}
void insertarduplic(user *&users, cancionduplic *&cancionesduplic, int fecha, int id, string nombre, string artista, string genero, string mg, int rp) {
    cancionduplic *nuevo = new cancionduplic();
    nuevo->id = id;
    nuevo->nombre = nombre;
    nuevo->artista = artista;
    nuevo->genero = genero;
    nuevo->fecha = fecha;
    nuevo->mg = mg;
    nuevo->rp = rp;
    nuevo->prx1 = NULL;
    nuevo->prv1 = NULL;

    if (cancionesduplic == NULL || cancionesduplic->id > id) {
        nuevo->prx1 = cancionesduplic;
        if (cancionesduplic != NULL) {
            cancionesduplic->prv1 = nuevo;
        }
        cancionesduplic = nuevo;
    } else {
        cancionduplic *actual = cancionesduplic;
        while (actual->prx1 != NULL && actual->prx1->id < id) {
            actual = actual->prx1;
        }
        nuevo->prx1 = actual->prx1;
        if (actual->prx1 != NULL) {
            actual->prx1->prv1 = nuevo;
        }
        actual->prx1 = nuevo;
        nuevo->prv1 = actual;
    }
    user *act = users;
    while (act != NULL) {
        act->temp = cancionesduplic;
        act = act->prx1;
    }
}
void insertarduplic2(user *user_node, int fecha, int id, string nombre, string artista, string genero) {
    int rp=0;
    cancionduplic *cancionesduplic = user_node->temp;
    cancionduplic *nuevo = new cancionduplic();
    nuevo->id = id;
    nuevo->nombre = nombre;
    nuevo->artista = artista;
    nuevo->genero = genero;
    nuevo->fecha = fecha;
    nuevo->mg = "no";
    nuevo->rp = rp;
    nuevo->prx1 = NULL;
    nuevo->prv1 = NULL;

    if (cancionesduplic == NULL) {
        user_node->temp = nuevo;
    } else {
        cancionduplic *ultimo = NULL;
        while (cancionesduplic != NULL && cancionesduplic->id != id) {
            ultimo = cancionesduplic;
            cancionesduplic = cancionesduplic->prx1;
        }
        if (cancionesduplic != NULL && cancionesduplic->id == id) {
            delete nuevo;
        } else {
            if (ultimo == NULL) {
                user_node->temp = nuevo;
                nuevo->prx1 = cancionesduplic;
                if (cancionesduplic != NULL) {
                    cancionesduplic->prv1 = nuevo;
                }
            } else {
                ultimo->prx1 = nuevo;
                nuevo->prv1 = ultimo;
                nuevo->prx1 = cancionesduplic;
                if (cancionesduplic != NULL) {
                    cancionesduplic->prv1 = nuevo;
                }
            }
        }
    }
}
void insertinuser(user *&users, int fecha, int id, string nombre, string artista, string genero){
    user *inicio = users;
    while(inicio){
        insertarduplic2(inicio, fecha, id, nombre, artista, genero);
        inicio = inicio->prx1;
    }
}
void cargararchivocancionesuni(string nombreArchivo2, user *&users, cancionduplic *&cancionesduplic) {
    ifstream archivo(nombreArchivo2);
    string linea;
    char chrnombre[50], chrartista[50], chrgenero[50], chrmg[50];
    int fecha, id,rp;
    if (archivo.is_open()) {
        cancionduplic *temp = NULL;
        while (getline(archivo, linea)) {
            if (!linea.empty()) {
                sscanf(linea.c_str(), "%[^-]-%[^-]-%[^-]-%d-%d-%[^-]-%d\n", &chrnombre[0], &chrartista[0], &chrgenero[0], &fecha, &id, &chrmg[0], &rp);
                string nombre = string(chrnombre);
                string artista = string(chrartista);
                string genero = string(chrgenero);
                string mg = string(chrmg);
                insertarduplic(users, temp, fecha, id, nombre, artista, genero, mg, rp);
            } else {
                cout << "No se pudo abrir el archivo\n";
            }
        }
    }
}
void insertaruser(user *&users, cancionduplic *&cancionesduplic, string nombrearchivo2, int edad1, int id1, string nombre1, string correo1, string cntr1, string pais1) {
    user *nuevo = new user();
    nuevo->id1 = id1;
    nuevo->edad1 = edad1;
    nuevo->nombre1 = nombre1;
    nuevo->correo1 = correo1;
    nuevo->cntr1 = cntr1;
    nuevo->pais1 = pais1;
    nuevo->prx1 = users; 
    nuevo->temp = nullptr;

    if (users == nullptr || users->id1 > id1) {
        users = nuevo;
    } else {
        user *actual = users;
        while (actual->prx1 != nullptr && actual->prx1->id1 < id1) {
            actual = actual->prx1;
        }
        nuevo->prx1 = actual->prx1;
        actual->prx1 = nuevo;
    }
    cancionduplic *temp = nullptr;
    cargararchivocancionesuni(nombrearchivo2, users, cancionesduplic);
}
void cargararchivouser(string nombreArchivo, string nombrearchivo2, user *&users, usuario *&usuarios, cancionduplic *&cancionesduplic) {
    ifstream archivo(nombreArchivo);
    string linea;
    char chrnombre[50], chrcorreo[50], chrcntr[50], chrpais[50];
    int edad1, id1;
    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            if (!linea.empty()) {
                sscanf(linea.c_str(), "%[^-]-%[^-]-%[^-]-%d-%d-%[^\n]", &chrnombre[0], &chrcorreo[0], &chrcntr[0], &edad1, &id1, &chrpais[0]);
                string nombre1 = string(chrnombre);
                string correo1 = string(chrcorreo);
                string cntr1 = string(chrcntr);
                string pais1 = string(chrpais);
                insertaruser(users, cancionesduplic, nombrearchivo2, edad1, id1, nombre1, correo1, cntr1, pais1);
            }
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo\n";
    }
}
void eliminaruser(user* users, int id1) {
    if (users->id1 == id1) {
        user* temp = users;
        users = users->prx1; 
        delete temp;
        return;
    }
    user* act = users;
    while (act->prx1) {
        if (act->prx1->id1 == id1) {
            user* temp = act->prx1;
            act->prx1 = act->prx1->prx1; 
            delete temp;
            return;
        }
        act = act->prx1;
    }
}
void eliminarduplic2(user *users, int id) {
    cancionduplic *cancionesduplic = users->temp;
    cancionduplic *anterior = NULL;

    while (cancionesduplic != NULL && cancionesduplic->id != id) {
        anterior = cancionesduplic;
        cancionesduplic = cancionesduplic->prx1;
    }

    if (cancionesduplic != NULL && cancionesduplic->id == id) {
        if (anterior == NULL) {
            users->temp = cancionesduplic->prx1;
            if (cancionesduplic->prx1 != NULL) {
                cancionesduplic->prx1->prv1 = NULL;
            }
        } else {
            anterior->prx1 = cancionesduplic->prx1;
            if (cancionesduplic->prx1 != NULL) {
                cancionesduplic->prx1->prv1 = anterior;
            }
        }
        delete cancionesduplic;
    }
}
void eliminarduplic(user *&users, int id) {
    user *inicio = users;
    while (inicio) {
        eliminarduplic2(inicio, id);
        inicio = inicio->prx1;
    }
}
void eliminarsongarch(string nombreArchivo2, int id) {
    ifstream archivo;
    ofstream aux;
    string linea;

    archivo.open(nombreArchivo2);
    aux.open("temp.txt");

    while (getline(archivo, linea)) {
        string idStr = to_string(id);
        if (linea.find(idStr) == string::npos) {
            aux << linea << endl;
        }
    }

    archivo.close();
    aux.close();

    remove(nombreArchivo2.c_str());
    rename("temp.txt", nombreArchivo2.c_str());
}
//funciones extra
void historialmg(string correo, int id1) {
  string nombrearch = "historial de-" + correo + ".txt";
  ifstream archivo(nombrearch);
  string linea;
  ofstream archivoNuevo("temp.txt");
  while (getline(archivo, linea)) {
    int id;
    char idStr[10];
    sscanf(linea.c_str(), "%*[^-]-%*[^-]-%*[^-]-%*[^-]-%d-%*[^-]-%*[^-]",&id);
    if (id == id1) {
      size_t pos = linea.find("no");
      if (pos!= -1) {
        linea.replace(pos, 3, "si-");
      }
    }
    archivoNuevo << linea << "\n";
  }
  archivo.close();
  archivoNuevo.close();
  remove((nombrearch).c_str());
  rename("temp.txt", (nombrearch).c_str());

  cout << "Canciones marcadas como me gusta con exito." << endl;
}
void megusta(user *&users, string correo,int id1){
    user *actual = users;
    while (actual) {
        if (correo == actual->correo1) {
            cancionduplic *cancion = actual->temp;
            while (cancion) {
                if (id1 == cancion->id) {
                    cancion->mg="si";
                    historialmg(correo,id1);                
                    }
                cancion = cancion->prx1;
            }
        }
        actual = actual->prx1;
    }
    
    return; 
}
//menu cancionadmin
void menucancionadmin(){
    int fecha, id,opcion2;
    string nombre, artista, genero,rsp,rutacancion,rutacancion2;
    rutacancion="C:\\Users\\cesar\\Desktop\\c\\ucabifydat.txt";
    rutacancion2="C:\\Users\\cesar\\Desktop\\c\\songdat.txt";
    do
    {
        system("cls");
        cout<<"Ucabify\n";
        cout<<"--------------------------------------\n";
        cout<< "\tMenu de canciones\n";
        cout<<"--------------------------------------\n";
        cout<< "1. mostrar canciones agregadas\n";
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
                insertararch(canciones,rutacancion, fecha , id, nombre, artista, genero);
                insertarsongarch(rutacancion2, fecha, id, nombre,  artista,  genero);
                insertinuser(users,  fecha,  id,  nombre,  artista,  genero);
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
                        eliminarsongarch(rutacancion2,id);
                        eliminarduplic(users,id);
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
void menuusuarioadmin(){
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
        cout<< "2. eliminar un usuario \n";
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
                cout<<"indique el correo del usuario que desea eliminar: ";
                cin >> correo;
                    if(verificarcorreo(usuarios, correo) == true){
                        system("cls");
                            idu=encontrarid(usuarios,correo);
                            eliminaruser(users,idu);
                            eliminarusuariosarch(usuarios,rutausuario,idu);
                            ordenararchu(usuarios,rutausuario);
                            ultimoIDu=valoridu(usuarios);
                            cout<<"el usuario ha sido eliminado con exito! \n ";
                            system("pause");
                        break;
                        }
                        else{
                        cout<<"el correo indicado no se encuentra en el sistema intente denuevo! \n ";
                        system("pause");
                        break;
                    }
                    }     
    }while (opcion3 != 0);
}
// menu admin
void menuadmin(){
    int opcion4;
    do
    {
        system("cls");
        cout<<"Ucabify\n";
        cout<<"--------------------------------------\n";
        cout<< "\tbienvenido administrador\n";
        cout<<"--------------------------------------\n";
        cout<< "\taccede a la base de datos de:\n";
        cout<<"--------------------------------------\n";
        cout<< "1. canciones\n";
        cout<< "2. usuarios\n";
        cout<<"--------------------------------------\n";
        cout<< "0. cerrar sesion\n";
        cout<< "Indique su opcion->";
        cin >> opcion4;
        switch (opcion4)
        {
            case 1:
                menucancionadmin();
                break;
            case 2:
                menuusuarioadmin();
                break;
        }
    }while (opcion4 != 0);
}
//menu user individual
void menuuser(string nombre1,string correo){
    int opcion4,id3,linea;
    string rspu;
    do
    {
        system("cls");
        cout<<"Ucabify\n";
        cout<<"--------------------------------------\n";
        cout<< "\tbienvenido "<<nombre1<<"!\n";
        cout<<"--------------------------------------\n";
        cout<< "1. reproducir una cancion\n";
        cout<< "2. ver el historial de canciones reproducidas\n";
        cout<< "3. agregar canciones a tus me gusta\n";
        cout<< "4. top 5 canciones mas reproducidas\n";
        cout<< "5. top 3 artistas mas escuchados\n";
        cout<< "6. encuentra tu alma gemela musical\n";
        cout<<"--------------------------------------\n";
        cout<< "0. cerrar sesion\n";
        cout<< "Indique su opcion->";
        cin >> opcion4;
        switch (opcion4)
        {
            case 1:
            system("cls");
                cout<<"indique el identificador numerico de la cancion que desea escuchar: ";
                cin>>id3;
                system("cls");
                reproducir(users,correo,id3);
                system("pause");
                break;
            case 2:
                system("cls");
                verHistorial(correo);
                system("pause");
                break;
            case 3:
                system("cls");
                cout<<"indique el id de la cancion que deseas agregar a tus me gusta: ";
                cin>>id3;
                megusta(users,correo,id3);
                system("pause");
                break;
            case 4:
                system("cls");
                system("pause");
                break;
            case 5:
                system("cls");
                system("pause");
                break;
            case 6:
                system("cls");
                system("pause");
                break;
        }
    }while (opcion4 != 0);
}
void imprimirMultilista(user *&users) {
    user* tempUser = users;
    while (tempUser != nullptr) {
        cout << "--------------------------------------\n";
        cout << "Usuario: " << tempUser->nombre1 << " (" << tempUser->id1 << ")" << endl;
        cout << "  Edad: " << tempUser->edad1 << endl;
        cout << "  Correo: " << tempUser->correo1 << endl;
        cout << "  Contrasena: " << tempUser->cntr1 << endl;
        cout << "  Pais: " << tempUser->pais1 << endl;
        cout << "estas son las canciones:\n";
        cancionduplic* tempCancion = tempUser->temp; // Access the temp list of the current user
        while (tempCancion != nullptr) {
            cout << "  Cancion: " << tempCancion->nombre << " (" << tempCancion->id << ")" << endl;
            cout << "    Artista: " << tempCancion->artista << endl;
            cout << "    Genero: " << tempCancion->genero << endl;
            cout << "    MG: " << tempCancion->mg << endl;
            cout << "    RP: " << tempCancion->rp << endl;
            tempCancion = tempCancion->prx1;
        }
        cout << "--------------------------------------\n";
        tempUser = tempUser->prx1;
    }
}
//mfuncion principal
int main(){
    int opcion,edad1,dato,idu1;
    string nombre1,correo1, cntr1,alt1,pais1,admin,rutacancion,rutacanciondupli,rutausuario;
    rutacancion="C:\\Users\\cesar\\Desktop\\c\\ucabifydat.txt";
    rutacanciondupli="C:\\Users\\cesar\\Desktop\\c\\songdat.txt";
    rutausuario="C:\\Users\\cesar\\Desktop\\c\\usuariosdat.txt";
    cargararchivocanciones(rutacancion);
    cargararchivousuarios(rutausuario);
    cargararchivouser(rutausuario,rutacanciondupli,users,usuarios,cancionesduplic);
    ultimoIDu=valoridu(usuarios);
    ultimoIDc=valoridc(canciones);
     do
    {
        system("cls");
        cout<<"Ucabify\n";
        cout<<"--------------------------------------\n";
        cout<< "\tRealizado por: \n Cesar Machado, 30497388\n Leonel Soares, 30371183\n";
        cout<<"--------------------------------------\n";
        cout<< "1. Iniciar sesion \n";
        cout<< "2. Crear una cuenta \n";
        cout<< "3. eliminar una cuenta\n";
        cout<< "4. acceder como administrador\n";
        cout<< "5. multi\n";
        cout<<"--------------------------------------\n";
        cout<< "0. Salir de la aplicacion\n";
        cout<< "Indique su opcion->";
        cin >> opcion;
        switch (opcion)
        {
            case 1:
                system("cls");
                cout<<"indique el correo de su cuenta ";
                cin >> correo1;
                    if(verificarcorreo(usuarios, correo1) == true){
                        cout<<"indique su contraseña: ";
                        cin>>cntr1;
                        if(verificarcntr(usuarios,cntr1,correo1)== true){
                            system("cls");
                            idu1=encontrarid(usuarios,correo1);
                            nombre1=encontrarnombre(usuarios,correo1);
                            menuuser(nombre1,correo1);
                        }
                        else{
                        cout<<"el correo indicado no se encuentra en el sistema intente denuevo! \n ";
                        system("pause");
                        break;
                    }
            break;
            case 2:
                system("cls");
                cout<<"digite el correo de la cuenta: ";
                cin >> correo1;
                    if(verificarcorreo(usuarios, correo1) == true){
                        system("cls");
                        cout<<"este correo ya se encuentra en el sistema porfavor vuelva a intentarlo con un correo diferente\n";
                        system("pause");
                        break;
                    }
                    cout<<"digite la clave del usuario: ";
                    cin >> cntr1;
                    system("cls");
                    cout<<"usuario creado con exito porfavor llene estos datos para registrarlo en el sistema\n";
                    system("pause");
                    system("cls");
                    cout<<"digite el nombre de usuario: ";
                    cin >> nombre1;
                    cout<<"digite la edad del usuario: ";
                    cin >> edad1;
                    cout<<"digite el pais de origen del usuario: ";
                    cin >> pais1;
                    ultimoIDu=valoridu(usuarios);
                    idu1=generarNuevoIDu();
                    insertararchu(usuarios,rutausuario, edad1 , idu1, nombre1, correo1, cntr1,pais1);
                    ordenararchu(usuarios,rutausuario);
                    insertaruser(users,cancionesduplic,rutacanciondupli,edad1 , idu1, nombre1, correo1, cntr1,pais1);
                    ultimoIDu=valoridu(usuarios);
                    system("cls");
                    cout<<"usuario registrado en el sistema con exito \n";
                    system("pause");
            break;
            case 3:
                system("cls");
                cout<<"indique el correo del usuario que desea eliminar: ";
                cin >> correo1;
                    if(verificarcorreo(usuarios, correo1) == true){
                        system("cls");
                        cout<<"indique la clave del usuario que desea eliminar: ";
                        cin >> cntr1;
                        if(verificarcntr(usuarios,cntr1,correo1)== true){
                            idu1=encontrarid(usuarios,correo1);
                            eliminaruser(users,idu1);
                            eliminarusuariosarch(usuarios,rutausuario,idu1);
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
                        }
                        system("pause");               
            break;
            case 4:
                system("cls");
                cout<<"porfavor ingrese la contraseña para acceder el menu de administradores (case sensitive): ";
                cin>>admin;
                if(admin == "joker5"){
                    menuadmin();
                }
                else
                cout<<"la contrase indicada no es correcta!porfavor intente nuevamente";
                system("pause");
            break;
            case 5:
                system("cls");
                imprimirMultilista(users);
                system("pause");
            break;      
        }
        }
    }while (opcion!= 0);
    delete users; 
    return 0;
}