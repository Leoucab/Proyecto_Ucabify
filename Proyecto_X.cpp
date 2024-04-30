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
struct canciones{
    string seccionc;
    canciones *prxcs;
    cancion *dwncs;
};
struct personas{
    string seccionp;
    personas *prxp;
    usuario *dwnp;
};
struct historial{
    string cancion2;
    historial *prxh;
    cancion *dwn;
};
cancion *canciones=NULL; // creacion de la lista vacia
// funciones y algoritmos
void insertarcancion(cancion *&canciones,int fecha,int id,string nombre, string artista, string genero, string mg){
    cancion *nuevo = new cancion();
    nuevo->id = id ;
    nuevo->nombre = nombre ;
    nuevo->artista = artista ;
    nuevo->genero = genero ;
    nuevo->fecha = fecha ;
    nuevo->mg = "no" ;
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
void mostrarcanciones(cancion *&canciones){
    system("cls");
    cancion *actual = canciones;
    while(actual != NULL){
        cout<<"[ID: "<<actual->id<<", Nombre: "<<actual->nombre<<", Artista: "<<actual->artista<<", Genero: "<<actual->genero<<", Fecha: "<<actual->fecha<<", favorito: "<<actual->mg<<"]\n";
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
void eliminarcancion(cancion *&canciones, int id){
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
void insertarUsuario(usuario *&usuarios, int idu, int edad, string nombre, string correo, string cntr, string pais) {
  usuario *nuevo = new usuario();
  nuevo->idu = idu;
  nuevo->edad = edad;
  nuevo->nombre = nombre;
  nuevo->correo = correo;
  nuevo->cntr = cntr;
  nuevo->pais = pais;
  nuevo->prxu = NULL;
  nuevo->prvu = NULL;

  if (usuarios == NULL || usuarios->idu > idu) {
    nuevo->prxu = usuarios;
    if (usuarios != NULL) {
      usuarios->prvu = nuevo;
    }
    usuarios = nuevo;
  } else {
    usuario *actual = usuarios;
    while (actual->prxu != NULL && actual->prxu->idu < idu) {
      actual = actual->prxu;
    }
    nuevo->prxu = actual->prxu;
    if (actual->prxu != NULL) {
      actual->prxu->prvu = nuevo;
    }
    actual->prxu = nuevo;
    nuevo->prvu = actual;
  }
}

void mostrarUsuarios(usuario *&usuarios) {
  system("cls");
  usuario *actual = usuarios;
  while (actual != NULL) {
    cout << "[ID: " << actual->idu << ", Nombre: " << actual->nombre << ", Edad: " << actual->edad
         << ", Correo: " << actual->correo << ", Contraseña: " << actual->cntr << ", País: " << actual->pais << "]\n";
    actual = actual->prxu;
  }
}

void modificarUsuario(usuario *&usuarios) {
  system("cls");
  int idu, edad;
  string nombre, correo, cntr, pais;

  cout << "Ingrese el ID del usuario que desea modificar: ";
  cin >> idu;

  if (!verificarIDUsuario(usuarios, idu)) {
    cout << "El usuario con ID " << idu << " no existe.\n";
    system("pause");
    return;
  }

  cout << "Ingrese la nueva edad del usuario: ";
  cin >> edad;

  cout << "Ingrese el nuevo nombre del usuario: ";
  cin.ignore(); // Ignorar el salto de línea
  getline(cin, nombre);

  cout << "Ingrese el nuevo correo electrónico del usuario: ";
  getline(cin, correo);

  cout << "Ingrese la nueva contraseña del usuario: ";
  getline(cin, cntr);

  cout << "Ingrese el nuevo país del usuario: ";
  getline(cin, pais);

  modificarUsuarioEnLista(usuarios, idu, edad, nombre, correo, cntr, pais);
  cout << "Usuario modificado con éxito.\n";
  system("pause");
}

void modificarUsuarioEnLista(usuario *&usuarios, int idu, int edad, string nombre, string correo, string cntr, string pais) {
  usuario *actual = usuarios;
  while (actual != NULL && actual->idu != idu) {
    actual = actual->prxu;
  }

  if (actual != NULL) {
    actual->edad = edad;
    actual->nombre = nombre;
    actual->correo = correo;
    actual->cntr = cntr;
    actual->pais = pais;
  }
}

// Función para eliminar un usuario
void eliminarUsuario(usuario *&usuarios) {
  system("cls");
  int idu;

  cout << "Ingrese el ID del usuario que desea eliminar: ";
  cin >> idu;

  if (!verificarIDUsuario(usuarios, idu)) {
    cout << "El usuario con ID " << idu << " no existe.\n";
    system("pause");
    return;
//menus
void menucancion(){
    system("cls");
    int fecha, id,opcion2;
    string nombre, artista, genero,rsp,mg;
    do
    {
        cout<<"Ucabify\n";
        cout<<"--------------------------------------\n";
        cout<< "\t\nMenu de canciones\n";
        cout<<"--------------------------------------\n";
        cout<< "1. insertar una nueva cancion \n";
        cout<< "2. ver canciones agregadas y darle me gusta\n";
        cout<< "3. eliminar una cancion \n";
        cout<<"--------------------------------------\n";
        cout<< "0. volver al menu anterior\n";
        cout<< "Indique su opcion->";
        cin >> opcion2;
        switch (opcion2)
        {
            case 1:
                system("cls");
                cout<<"digite el identificador numerico de la cancion: ";
                cin >> id;
                    if(verificarid(canciones, id) == true){
                        system("cls");
                        cout<<"este identificador numerico ya se encuentra en el sistema porfavor vuelva a intentarlo con un idetificador diferente\n";
                        system("pause");
                        break;
                    }
                system("cls");
                cout<<"digite el fecha de la cancion: ";
                cin >> fecha;
                system("cls");
                cout<<"digite el artista de la cancion: ";
                cin >> artista;
                system("cls");
                cout<<"digite el genero de la cancion: ";
                cin >> genero;
                system("cls");
                cout<<"digite el nombre de la cancion: ";
                cin >> nombre;
                system("cls");
                insertarcancion(canciones, fecha , id, nombre, artista, genero,mg);
                cout<<"cancion agregada con exito \n";
                system("pause");
                break;
            case 2:
                mostrarcanciones(canciones);
                cout<<"desea darle me gusta a alguna de estas canciones? y/n: \n";
                cin>>rsp;
                    if(rsp == "y" || rsp == "Y"){
                        cout<<"indique el identificador numerico de la cancion que desea agregar a sus favoritos: ";
                        cin>> id;
                            if(verificarid(canciones, id) == true){
                                megusta(canciones,id);
                                system("cls");
                                cout<<"su cancion fue agregada a favoritos con exito! \n";
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
            case 3:
                system("cls");
                cout<<"indique el identificador numerico de la cancion que desea eliminar: ";
                cin>> id;
                    if(verificarid(canciones, id) == true){
                        eliminarcancion(canciones, id);
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
// funcion principal
int main(){
    system("cls");
    int opcion, dato;
    do
    {
        cout<<"Ucabify\n";
        cout<<"--------------------------------------\n";
        cout<< "\tRealizado por: \n Cesar Machado, 30497388\n Leonel Soares, 30371183\n";
        cout<< "\t\nMenu Principal\n";
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
            case 2:
                cout<<"no disponible aun\n";
                break;
            case 3:
                cout<<"no disponible aun\n";
                break;
        }
    }while (opcion != 0);
}