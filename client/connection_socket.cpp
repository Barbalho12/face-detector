#include <iostream>
#include <fcntl.h>
#include <fstream>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>  //inet_addr
#define PORTNUM 12345u

using namespace std;

bool connectSocket(int *socketId, string SERVER_IP){
    struct sockaddr_in endereco;

    endereco.sin_family = AF_INET;
    endereco.sin_port = htons(PORTNUM);
    endereco.sin_addr.s_addr = inet_addr(SERVER_IP.data());
    memset(endereco.sin_zero, '\0', sizeof(endereco.sin_zero));//NEW
    *socketId = socket(AF_INET, SOCK_STREAM, 0); //NEW

    if (*socketId == -1){
        close(*socketId);
        return false;
    }

    if ( connect (*socketId, (struct sockaddr *)&endereco, sizeof(struct sockaddr)) == -1 ){
        close(*socketId);
        return false;
    }
    return true;
}

void sendMensage(const char* file_path, string SERVER_IP){
    //Pega o tamanho do arquivo
    ifstream file(file_path, std::ios::binary | std::ios::ate);
    int size = file.tellg();
    cout << "Image Size: " <<size << endl;
    char buffer[BUFSIZ];
    int filefd;

    filefd = open(file_path, O_RDONLY);
    if (filefd == -1) {
        perror("Open File");
        exit(EXIT_FAILURE);
    }

    int socketId;
    int bytesenviados;
    if (connectSocket(&socketId, SERVER_IP)){
        cout << "Quantidade de dados que serão enviados: " << size << endl;
        bytesenviados = write(socketId, &size, 4);
        if (bytesenviados == -1){
            cout << "Falha ao Enviar tamanho do arquivo" << endl;
            return;
        }

        ssize_t read_return;
        while (true) {
            read_return = read(filefd, buffer, BUFSIZ);
            if (read_return == 0)
                break;
            if (read_return == -1) {
                perror("read");
                exit(EXIT_FAILURE);
            }
            if (write(socketId, buffer, read_return) == -1) {
                perror("write");
                exit(EXIT_FAILURE);
            }
        }
    }
    close(filefd);
}


