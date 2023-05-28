#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include "FileManager.h"
#include "FileHandler.h"
using namespace std;

FileManager::FileManager(std::string fileName) { // constructor de la clase FileManager
    this->fileName = std::move(fileName);
}

void FileManager::createFile(const string& fileName) { // funcion para crear un archivo
    ofstream file("files/" + fileName + ".txt"); // se crea el archivo
    if (!file) { // si el archivo no se pudo crear se muestra un mensaje de error
        cerr << "Archivo no creado" << endl;
    }
}

