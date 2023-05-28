#include <iostream>
#include <string>
#include <dirent.h>
#include "FileHandler.h"
#include "FileManager.h"
using namespace std;

void showFiles(); // prototipo de la funcion para mostrar la lista de archivos
void openFile(const string& fileName); // prototipo de la funcion para abrir el submenu de un archivo

int main() {
    int opcion;
    do {
        cout << "<------------------------------------------------------------->" << endl;
        cout << "Lista de archivos: " << endl;
        showFiles(); // funcion para mostrar la lista de archivos
        cout << endl;
        cout << "\nMenu principal" << endl;
        cout << "\t1. Crear un nuevo archivo de texto." << endl;
        cout << "\t2. Abrir un archivo existente." << endl;
        cout << "\t0. Salir" << endl;
        cout << "Opcion: "; cin >> opcion;
        cin.ignore(); // para evitar que getline() tome el salto de linea de la opcion

        switch (opcion) { // switch para el menu principal, se evalua la opcion ingresada
            case 1: {
                // en caso de que la opcion sea 1 se crea un nuevo archivo
                string fileName; // variable para guardar el nombre del archivo
                cout << "Nombre del archivo: ";
                getline(cin, fileName); // se guarda el nombre del archivo
                FileManager* file = new FileHandler(fileName); // se crea un puntero de tipo FileHandler de la clase abstracta FileManager
                file->createFile(fileName); // se llama al metodo createFile de la clase FileManager
                break;
            }
            case 2: {
                // en caso de que la opcion sea 2 se abre un archivo existente
                string fileName; // variable para guardar el nombre del archivo
                cout << "Nombre del archivo: ";
                getline(cin, fileName); // se guarda el nombre del archivo
                FileHandler file(fileName); // se crea un objeto de tipo FileHandler y se le pasa el nombre del archivo
                file.openFile(fileName); // se llama al metodo openFile de la clase FileHandler y se le pasa el nombre del archivo
                openFile(fileName); // se llama a la funcion openFile y se le pasa el nombre del archivo
                break;
            }
            default:
                // en caso de que la opcion sea diferente de 0, 1 o 2 se muestra un mensaje de error
                cout << "Opcion invalida" << endl << endl << endl;
                break;
        }
    } while (opcion != 0); // el ciclo se repite mientras la opcion sea diferente de 0
    return 0;
}

void showFiles() { // funcion para mostrar la lista de archivos
    int i = 0;
    string path = "./files/", fileName; // se guarda la ruta de la carpeta donde se guardan los archivos
    DIR *pathDir; // se crea un puntero de tipo DIR
    struct dirent *files; // se crea un puntero de tipo dirent

    pathDir = opendir(path.c_str()); // se abre la carpeta y se guarda en el puntero pathDir
    if (pathDir) { // si la carpeta existe
        files = readdir(pathDir); // se lee la carpeta y se guarda en el puntero files
        while (files) { // mientras existan archivos en la carpeta
            if (strcmp(files->d_name, ".") != 0 && strcmp(files->d_name, "..") != 0) { // ignorar los archivos . y ..
                cout << "\t" << files->d_name << endl; // mostrar el nombre del archivo
                i += 1;
            }
            files = readdir(pathDir); // se lee la carpeta y se guarda en el puntero files
        }
        closedir(pathDir); // se cierra la carpeta
        cout << "Total de archivos: " << i << endl; // se muestra el total de archivos
    }
}

void openFile(const string& fileName) { // funcion para abrir el submenu de un archivo
    int opcion;
    do {
        cout << "\nEstas en el archivo: " << fileName << endl;
        cout << "\t1. Mostrar el contenido del archivo en la consola." << endl;
        cout << "\t2. Agregar texto al archivo."<< endl;
        cout << "\t3. Buscar una palabra o frase en el archivo." << endl;
        cout << "\t4. Modificar una linea especifica del archivo." << endl;
        cout << "\tOpcion: "; cin >> opcion;
        cin.ignore(); // para evitar que getline() tome el salto de linea de la opcion

        switch (opcion) {
            case 1: {
                // en caso de que la opcion sea 1 se muestra el contenido del archivo
                FileHandler file(fileName); // se crea un objeto de tipo FileHandler y se le pasa el nombre del archivo
                file.openFile(fileName); // se llama al metodo openFile de la clase FileHandler y se le pasa el nombre del archivo
                file.showContent(fileName); // se llama al metodo showContent de la clase FileHandler y se le pasa el nombre del archivo
                break;
            }
            case 2: {
                // en caso de que la opcion sea 2 se agrega texto al archivo
                FileHandler file(fileName); // se crea un objeto de tipo FileHandler y se le pasa el nombre del archivo
                file.openFile(fileName, ios::app); // se llama al metodo openFile de la clase FileHandler y se le pasa el nombre del archivo y el modo de apertura
                file.addContent(fileName); // se llama al metodo addContent de la clase FileHandler y se le pasa el nombre del archivo
                break;
            }
            case 3: {
                // en caso de que la opcion sea 3 se busca una palabra o frase en el archivo
                string phrase; // variable para guardar la palabra o frase a buscar
                cout << "Palabra o frase a buscar: ";
                cin.ignore();
                getline(cin, phrase);
                FileHandler file(fileName); // se crea un objeto de tipo FileHandler y se le pasa el nombre del archivo
                file.openFile(fileName); // se llama al metodo openFile de la clase FileHandler y se le pasa el nombre del archivo
                file.searchContent(fileName, phrase); // se llama al metodo searchContent de la clase FileHandler y se le pasa el nombre del archivo y la palabra o frase a buscar
                break;
            }
            case 4: {
                // en caso de que la opcion sea 4 se modifica una linea especifica del archivo
                int line;
                string content;
                cout << "Linea a modificar: ";
                cin >> line; // se guarda el numero de la linea a modificar
                cout << "Nuevo contenido: ";
                cin.ignore();
                getline(cin, content); // se guarda el nuevo contenido
                FileHandler file(fileName); // se crea un objeto de tipo FileHandler y se le pasa el nombre del archivo
                file.openFile(fileName); // se llama al metodo openFile de la clase FileHandler y se le pasa el nombre del archivo
                file.modifyLine(fileName, line, content); // se llama al metodo modifyLine de la clase FileHandler y se le pasa el nombre del archivo, el numero de la linea y el nuevo contenido
                break;
            }
            default:
                // en caso de que la opcion sea diferente de 0, 1, 2, 3 o 4 se muestra un mensaje de error
                cout << "Opcion invalida" << endl;
                break;
        }
    } while (opcion != 0); // el ciclo se repite mientras la opcion sea diferente de 0
}