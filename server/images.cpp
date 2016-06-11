#include "images.h"

/**
 * Cria um directorio para salvar as imagens.
 */
void create_directory() {
    // Create the directory
    system("chmod 777 create_directory.sh");
    system("bash create_directory.sh");
}

/**
 * Salvar imagem.
 */
void save(Mat frame, string path) {
    if (!frame.empty()) {
        imwrite(path, frame);
    }
}

/**
 * Ler imagem.
 */
Mat read(string path) {
    return imread(path, 1);
}
