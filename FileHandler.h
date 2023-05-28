#include <iostream>
#include "FileManager.h"

#ifndef A5_2_FILEHANDLER_H
#define A5_2_FILEHANDLER_H

class FileHandler : public FileManager{ // clase FileHandler que hereda de FileManager
    private: // atributos privados
        std::string fileName;
    public: // metodos publicos
        explicit FileHandler(const std::string& fileName); // constructor de la clase FileHandler
        void showContent(std::string name); // funcion para mostrar el contenido del archivo
        void addContent(std::string name); // funcion para agregar contenido al archivo
        void searchContent(std::string name, const std::string& prhase); // funcion para buscar contenido en el archivo
        void modifyLine(const std::string& name, int line, const std::string& phrase); // funcion para modificar una linea del archivo
        std::ifstream openFile(std::string name) override; // funcion para abrir el archivo en modo lectura, esta funcion es virtual y es heredada de la clase FileManager
        std::ofstream openFile(std::string name, std::ios_base::openmode mode) override; // funcion para abrir el archivo en modo escritura, esta funcion es virtual y es heredada de la clase FileManager
};

#endif //A5_2_FILEHANDLER_H
