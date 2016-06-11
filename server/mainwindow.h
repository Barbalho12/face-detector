#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <QMainWindow>
#include <QLabel>
#include <chrono>

#include <unistd.h>
#include <iostream>
#include <vector>
#include <thread>
#include <stdio.h>  // printf, puts, getline
#include <stdlib.h> // EXIT_SUCCESS, EXIT_FAILURE
#include <fcntl.h>  // open, close
#include <ctime>
#include <fstream>
#include <string>

#include "images.h"


//#include <cstring>
//#include <netinet/in.h>
//#include <sys/socket.h>
//#include <arpa/inet.h>

//#define PORTNUM 4325
//#define IP_SERV "192.168.7.1"
//#define IP_SERV "127.0.0.1"
#define IP_SERV "192.168.0.105"
//#define MAXMSG 1024
//#define MAXNAME 100

using namespace std;
using namespace cv;

typedef struct{
    Mat image;      // Face para registrar
    int id;         // Idetinficaçaõ da camera
    cv::Rect roi_b; // Proporção da tela
}Faces;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void waitClient();
    void update();
    void service();

private slots:
    void on_pushButton_clicked();

private:
    std::thread    threadServer;
    std::thread    updateinterface;
    Ui::MainWindow *ui;
    int  server_sockfd;
    void authenticate();
    int  client_sockfd;
    void table();
    void table_values();
};

#endif // MAINWINDOW_H
