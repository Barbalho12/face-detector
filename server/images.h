#ifndef FILES
#define FILES

#include <iostream>
#include <string>

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

// Formanto padrão para salvar imagens AA.MM.DD.HH.mm.ss.NomeDaPessoa.png

/**
 * Cria um directorio para salvar as imagens.
 */
void create_directory();

/**
 * Salvar imagem.
 */
void save(Mat frame, string path);

/**
 * Ler imagem.
 */
Mat read(string path);

#endif // FILES

