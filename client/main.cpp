#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "connection_socket.cpp"
#include "libs/Beaglebone_Black/bbb_dht_read.h"
#include "libs/BlackLib/v3_0/BlackGPIO/BlackGPIO.h"
#include <iostream>
#include <unistd.h>
#include <thread>
#include <sstream>
#include <csignal>

#define CAMERA_IP_STATIC "http://192.168.0.101/mjpg/video.mjpg"
#define FACE_CASCADE_NAME "/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml"
#define SLEEP_TIME_STATIC 4
#define SIZE_FACE_MIN_STATIC 200
#define SERVER_IP_STATIC "192.168.7.1"

using namespace std;
using namespace cv;

string CAMERA_IP = CAMERA_IP_STATIC;
string SERVER_IP = SERVER_IP_STATIC;
int SLEEP_TIME = SLEEP_TIME_STATIC;
int SIZE_FACE_MIN = SIZE_FACE_MIN_STATIC;

CascadeClassifier face_cascade; //padrão de detecção de faces
vector<Rect> faces; //vetor de faces capturado

VideoCapture capture;   //VideoCapture capture(0); para webcam
Mat frame;  // Read the video stream

#define RED 'R'
#define GREEN 'G'
#define BLUE 'B'

BlackLib::BlackGPIO   *ledR;
BlackLib::BlackGPIO   *ledG;
BlackLib::BlackGPIO   *ledB;

void apagaled(){

    ledR->setValue(BlackLib::low);
    ledG->setValue(BlackLib::low);
    ledB->setValue(BlackLib::low);
}

void led(char cor){
//    BlackLib::BlackGPIO   ledR(BlackLib::GPIO_60,BlackLib::output, BlackLib::SecureMode);
//    BlackLib::BlackGPIO   ledG(BlackLib::GPIO_50,BlackLib::output, BlackLib::SecureMode);
//    BlackLib::BlackGPIO   ledB(BlackLib::GPIO_51,BlackLib::output, BlackLib::SecureMode);

    apagaled();

    switch (cor) {
        case RED:
            ledR->setValue(BlackLib::high);
            break;
        case GREEN:
            ledG->setValue(BlackLib::high);
            break;
        case BLUE:
            ledB->setValue(BlackLib::high);
            break;
        default:
            break;
    }

}

void saveImage(Mat frame, string imagePath){
    if (!frame.empty()){
        imwrite(imagePath, frame);
    }
}

Mat readImage(string imagePath){
    Mat image;
    image = imread(imagePath, 1 );
    return image;
}

// Function to count the detected faces in your image
void detectFacesInImage(){
    face_cascade.detectMultiScale(frame, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
}

void drawFaces(){
    if (faces.size() == 1){
        Mat crop;
        Mat res;
        Mat gray;

        cv::Rect roi_b;
        cv::Rect roi_c;

        size_t ic = 0; // ic is index of current element
        int ac = 0; // ac is area of current element

        size_t ib = 0; // ib is index of biggest element
        int ab = 0; // ab is area of biggest element

        // Iterate through all current elements (detected faces)
        //for (ic = 0; ic <  1; ic++){//faces.size(); ic++){
        ic = 0;
        roi_c.x = faces[ic].x;
        roi_c.y = faces[ic].y;
        roi_c.width = (faces[ic].width);
        roi_c.height = (faces[ic].height);

        ac = roi_c.width * roi_c.height; // Get the area of current element (detected face)

        roi_b.x = faces[ib].x;
        roi_b.y = faces[ib].y;
        roi_b.width = (faces[ib].width);
        roi_b.height = (faces[ib].height);

        ab = roi_b.width * roi_b.height; // Get the area of biggest element, at beginning it is same as "current" element

        if (ac > ab){
            ib = ic;
            roi_b.x = faces[ib].x;
            roi_b.y = faces[ib].y;
            roi_b.width = (faces[ib].width);
            roi_b.height = (faces[ib].height);
        }
        if(roi_b.width < SIZE_FACE_MIN){
            cout << "menor" << endl;
            return;
        }

        led(BLUE);

        crop = frame(roi_b);
        resize(crop, res, Size(128, 128), 0, 0, INTER_LINEAR); // This will be needed later while saving images
        cvtColor(crop, gray, CV_BGR2GRAY); // Convert cropped image to Grayscale

        cout << "vai enviar" << endl;
        saveImage(crop, "face.png");
        sendMensage("face.png", SERVER_IP);
        cout << "Enviou" << endl;
        sleep(SLEEP_TIME);

        led(RED);

    }else if (faces.size() > 1){
        cout << "Duas faces detectadas, apenas uma é permitida" << endl;

    }

}

Mat frame2;

void captura(){
    while(true){
        capture >> frame2;
        usleep(100);
    }
}


void testeIpCam(char *argv[]){

    char str[80];
    strcpy (str,"http://");
    strcat (str, argv[1]);
    strcat (str,"/mjpg/video.mjpg");

    try{
        if(str[7] == '0'){
            capture.open(0);
            CAMERA_IP = "0";
        }else{
            capture.open(str);
            for(int i = 0; i < 80; i++){  if(str[i]=='\0') break; CAMERA_IP.push_back(str[i]);}
            CAMERA_IP.push_back('\0');
        }
        if (!capture.isOpened()){
            throw(1);
        }

    }catch (int e){
        if(e==1){
            cout << "Ocorreu um erro com o IP da câmera: " << CAMERA_IP << endl;
        }
        exit(0);
    }
}

thread *t1;

void funcaoSignalHandler (int sig){
    t1->detach();
    apagaled();
    exit(EXIT_SUCCESS);
}

// Function main
int main(int argc, char *argv[]){
    ledR = new BlackLib::BlackGPIO(BlackLib::GPIO_60,BlackLib::output, BlackLib::SecureMode);
    ledG = new BlackLib::BlackGPIO(BlackLib::GPIO_50,BlackLib::output, BlackLib::SecureMode);
    ledB = new BlackLib::BlackGPIO(BlackLib::GPIO_51,BlackLib::output, BlackLib::SecureMode);
    signal(SIGINT, funcaoSignalHandler);


    cout << "Parâmetros esperados: IP_CAM IP_SERV SLEEP_TIME SIZE_FACE_MIN" << endl;
    cout << "Por Padrão: IPCAM=0 IP_SERV=192.168.7.1 SLEEP_TIME=4 SIZE_FACE_MIN=200" << endl;
    cout << "----------------------------------------------------------------------" << endl;

    if (!face_cascade.load(FACE_CASCADE_NAME)){
        cout << "Ocorreu um erro com a localização do arquivo de padrão de detecção facial: " << FACE_CASCADE_NAME << endl;
        return -1;
    }

    if(argc == 1){
        try{
            capture.open(0);
            if (!capture.isOpened()){
                throw(1);
            }
        }catch (int e){
            if(e==1){
                cout << "Não há webcam configurada: " << endl;
            }
            return -1;
        }
    }else if(argc == 2){
        testeIpCam(argv);

    }else if(argc == 3){
        testeIpCam(argv);

        string temp(argv[2]);
        SERVER_IP = temp;

    }else if(argc == 4){
        testeIpCam(argv);

        string temp(argv[2]);
        SERVER_IP = temp;

        istringstream sTEMP(argv[3]);
        int TEMP;
        if (!(sTEMP >> TEMP)){
            cout << "Tempo de sleep inválido" << argv[3] << endl;
        }
        SLEEP_TIME = TEMP;

    }else if(argc == 5){
        testeIpCam(argv);

        string temp(argv[2]);
        SERVER_IP = temp;

        istringstream sTEMP(argv[3]);
        int TEMP;
        if (!(sTEMP >> TEMP)){
            cout << "Tempo de sleep inválido: " << argv[3] << endl;
            return -1;
        }
        SLEEP_TIME = TEMP;

        istringstream sTEMP2(argv[4]);
        int TEMP2;
        if (!(sTEMP2 >> TEMP2)){
            cout << "Tamanho de face mínimo inválido: " << argv[4] << endl;
            return -1;

        }else if(TEMP2 <0 || TEMP2 > 400){
            cout << "Tamanho de face mínimo inválido: " << argv[4] << endl;
            return -1;
        }
        SIZE_FACE_MIN = TEMP;
    }

    cout << "----------------------------------------------------------------------" << endl;
    cout << "IP SERVER      = " << SERVER_IP << endl;
    cout << "CAMERA IP      = " << CAMERA_IP << endl;
    cout << "SLEEP TIME     = " << SLEEP_TIME << endl;
    cout << "SIZE FACE_MIN  = " << SIZE_FACE_MIN << endl;
    cout << "----------------------------------------------------------------------" << endl;

    led(RED);

    //Fica verificando por faces no frame
    t1 = new thread(captura);

    while(true){
        frame = frame2;
        if (!frame.empty()){
            cout << "Frame capturado" << endl;
            detectFacesInImage();
            cout << "Análise de faces realizadas [resultado "<< faces.size() << "]" << endl;
            drawFaces();
        }
    }

    t1->join();
    return 0;
}
