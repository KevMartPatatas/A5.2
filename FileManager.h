#include <iostream>
#include <fstream>

#ifndef A5_2_FILEMANAGER_H
#define A5_2_FILEMANAGER_H

class FileManager { // clase FileManager, esta clase es abstracta y la clase base de la clase FileHandler
private:
    std::string fileName;
public:
    explicit FileManager(std::string fileName); // constructor de la clase FileManager
    static void createFile(const std::string& fileName); // funcion para crear un archivo
    virtual std::ifstream openFile(std::string fileName) = 0; // funcion para abrir el archivo en modo lectura, esta funcion es virtual y es heredada de la clase FileHandler
    virtual std::ofstream openFile(std::string fileName, std::ios_base::openmode mode) = 0; // funcion para abrir el archivo en modo escritura, esta funcion es virtual y es heredada de la clase FileHandler
};

#endif //A5_2_FILEMANAGER_H
