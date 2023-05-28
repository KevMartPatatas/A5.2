#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include "FileHandler.h"
#include "FileManager.h"
using namespace std;

FileHandler::FileHandler(const std::string& fileName) : FileManager(fileName) {} // constructor de la clase FileHandler

ifstream FileHandler::openFile(string name) { // funcion para abrir el archivo en modo lectura archivo y retorna un objeto ifstream
    char e; // variable para guardar la respuesta del usuario
    ifstream file("files/" + name + ".txt"); // intenta abrir el archivo
    if (!file) { // si el archivo no existe
        // se muestra un mensaje de error y se pregunta si se desea crear el archivo
        cerr << "El archivo no existe. Quieres crearlo? 's' para si i" << endl;
        cin >> e;
        if (e == 's' || e == 'S') { // si la respuesta es 's' o 'S'
            createFile(name); // se llama al metodo createFile de la clase FileManager para crear el archivo
            return file;
        }
    } else {
        return file;
    }
    return {};
}

ofstream FileHandler::openFile(string name, ios_base::openmode mode) { // funcion para abrir un archivo en modo escritura y retorna un objeto ofstream
    char e;
    ofstream file("files/" + name + ".txt", mode); // intenta abrir el archivo para agregar contenido
    if (!file) { // si el archivo no existe se muestra un mensaje de error y se pregunta si se desea crear el archivo
        cerr << "El archivo no existe. Quieres crearlo? 's' para si" << endl;
        cin >> e;
        if (e == 's' || e == 'S') {
            createFile(name); // se llama al metodo createFile de la clase FileManager para crear el archivo
            return file;
        }
    } else {
        return file;
    }
    return file;
} // existe una sobrecarga de la funcion openFile para abrir el archivo en modo escritura y lectura

void FileHandler::showContent(string name) { // funcion para mostrar el contenido del archivo
    ifstream file = openFile(std::move(name)); // se llama al metodo openFile para abrir el archivo en modo lectura
    string line;
    if (!file) { // si el archivo no existe se muestra un mensaje de error
        cerr << "El archivo no existe" << endl;
    } else { // si el archivo existe
        // se lee el archivo linea por linea y se muestra en pantalla
        cout << "\t\tContenido del archivo: " << endl;
        while (getline(file, line)) {
            cout << "\t\t\t" + line << endl; // se muestra la linea
        }
    }
}

void FileHandler::addContent(string name) { // funcion para agregar contenido al archivo
    ofstream file = openFile(std::move(name), ios::app); // se llama al metodo openFile para abrir el archivo en modo escritura y agregar contenido
    string content;
    if (!file) { // si el archivo no existe se muestra un mensaje de error
        cerr << "El archivo no existe" << endl;
    } else { // si el archivo existe
        cout << "Contenido: ";
        cin.ignore();
        getline(cin, content); // se lee el contenido que se desea agregar al archivo
        file << content + "\n"; // se agrega el contenido al archivo
        cout << "Contenido agregado" << endl;
    }
}

void FileHandler::searchContent(std::string name, const string& phrase) { // funcion para buscar una palabra o frase en el archivo
    ifstream file = openFile(std::move(name)); // se llama al metodo openFile para abrir el archivo en modo lectura
    string lineContent; // variable para guardar el contenido de cada linea
    int lineNumber = 0; // variable para guardar el numero de linea
    bool founded = false; // variable para saber si se encontro la frase

    if (!file) { // si el archivo no existe se muestra un mensaje de error
        cerr << "El archivo no existe" << endl;
    } else { // si el archivo existe
        while (getline(file, lineContent)) { // se lee el archivo linea por linea
            lineNumber++; // se aumenta el numero de linea en 1
            if (lineContent.find(phrase) != string::npos) { // si se encuentra la frase en la linea
                cout << "Linea " << lineNumber << ": " << lineContent << endl; // se muestra la linea en la que se encontro la frase y el contenido de la linea
                founded = true; // se cambia el valor de la variable found a true
            }
        }
        if (!founded) { // si no se encontro la frase se muestra un mensaje de error
            cout << "No se encontro la frase" << endl;
        }
    }
}

void FileHandler::modifyLine(const string& name, int lineNumber, const string& newPhrase) { // funcion para modificar una linea del archivo
    ifstream file = openFile(name); // se llama al metodo openFile para abrir el archivo en modo lectura y se guarda en la variable file de tipo ifstream
    ofstream tempFile("files/temp.txt"); // se crea un archivo temporal en modo escritura
    string lineContent; // variable para guardar el contenido de cada linea
    int lineaActual = 0; // variable para guardar el numero de linea
    bool modify = false; // variable para saber si se modifico la linea

    if (!file) { // si el archivo no existe se muestra un mensaje de error
        cerr << "El archivo no existe" << endl;
        return;
    }

    while (getline(file, lineContent)) { // se lee el archivo linea por linea
        lineaActual++; // se aumenta el numero de linea en 1

        if (lineaActual == lineNumber) { // si la linea actual es igual a la linea que se quiere modificar
            tempFile << newPhrase << "\n"; // se agrega la nueva frase al archivo temporal
            modify = true; // se cambia el valor de la variable modify a true
            cout << "\tLinea modificada" << endl;
        } else { // si la linea actual no es igual a la linea que se quiere modificar
            tempFile << lineContent << "\n"; // si agrega el contenido de la linea al archivo temporal
        }
    }
    // se cierran los archivos
    file.close();
    tempFile.close();

    if (!modify) { // si no se modifico la linea se muestra un mensaje de error
        cout << "El numero de linea no existe" << endl;
        remove("files/temp.txt"); // se elimina el archivo temporal
        return;
    }

    remove(("files/" + name + ".txt").c_str()); // se elimina el archivo original
    rename("files/temp.txt", ("files/" + name + ".txt").c_str()); // se renombra el archivo temporal con el nombre del archivo original
}
