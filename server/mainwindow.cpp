#include <QtWidgets/QTableView>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "common.h"
#include "showip.cpp"

/**
 * Construtor.
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    // GUI
    ui->setupUi(this);
    // Inicialização do servidor para escutar o cliente
    threadServer = std::thread(&MainWindow::waitClient, this);
    // Espera o envio de dados do cliente
    updateinterface = std::thread(&MainWindow::update, this);
    table();
    table_values();
}

/**
 * Tabela.
 */
void MainWindow::table() {
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->verticalHeader()->setVisible(false);

    QTableWidgetItem *header1 = new QTableWidgetItem();
    header1->setText("Usuário");
    ui->tableWidget->setHorizontalHeaderItem(0, header1);

    QTableWidgetItem *header2 = new QTableWidgetItem();
    header2->setText("Data");
    ui->tableWidget->setHorizontalHeaderItem(1, header2);

    QTableWidgetItem *header3 = new QTableWidgetItem();
    header3->setText("Horário");
    ui->tableWidget->setHorizontalHeaderItem(2, header3);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);


    vector<string> temp = getInterfaceNetworks();
    string ips = "";
    for(string s : temp){
        ips += s+"\n";
    }
    ui->lnetworks->setText(QString::fromStdString(ips));
}

/**
 * Destrutor.
 */
MainWindow::~MainWindow() {
    delete ui;
    threadServer.detach();
    updateinterface.detach();
    ::close(client_sockfd);
    ::close(server_sockfd);
}

/**
 * Autenticaçao.
 */
void MainWindow::authenticate() {
    // Retona o tempo atual
    time_t now = time(0);

    // Formata o nome do arquivo
    struct tm * timeinfo;
    char buffer[80];
    time (&now);
    timeinfo = localtime(&now);
    strftime(buffer, 80, "log_authentication/%Y-%m-%d.%I:%M:%S.unknown.png", timeinfo);
    string str(buffer);

    string reicevedImage = "pessoa.png";

    // Salva imagem
    save(read(reicevedImage), str);
}



/**
 * .
 */
void MainWindow::waitClient() {
    char *file_path = "pessoa.png";
    char buffer[BUFSIZ];
    char protoname[] = "tcp";
    int filefd;
    socklen_t client_len;
    ssize_t read_return;
    struct sockaddr_in client_address;
    unsigned short server_port = 12345u;

    server_sockfd = listen_port(protoname, server_port);
    while (1) {
        client_len = sizeof(client_address);
        cout << "waiting for client" << endl;
        client_sockfd = accept(
            server_sockfd,
            (struct sockaddr*)&client_address,
            &client_len
        );
        print_client_address(client_sockfd);
        filefd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        if (filefd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }

        int size = 0;
        read_return = read(client_sockfd, &size, 4);
        cout << size << endl;

        while (size > 0) {
            read_return = read(client_sockfd, buffer, BUFSIZ);
            //cout << read_return << endl;
            if (read_return == 0){
                break;
            }if (read_return == -1) {
                perror("read");
                exit(EXIT_FAILURE);
            }
            if (write(filefd, buffer, read_return) == -1) {
                perror("write");
                exit(EXIT_FAILURE);
            }
            size -= read_return;
        }
        ::close(filefd);
        authenticate();
        ::close(client_sockfd);
    }
    ::close(server_sockfd);
    return;
}

/**
 * Atualiza.
 */
void MainWindow::update() {
    while(true){
        QPixmap pixmapObject("pessoa.png");
        ui->la_image_view->setPixmap(pixmapObject);
        // ui->la_image_view->show();
        ui->la_image_view->update();
        sleep(1);
    }
}


/**
 * Le os valores da tabela.
 */
void MainWindow::on_pushButton_clicked() {
    table_values();
}

/**
 * Valores da tabela.
 */
void MainWindow::table_values() {
    // Lendo as imagens
    system("chmod 777 files_in_directory.sh");
    system("bash files_in_directory.sh");
    ifstream file;
    file.open("files.txt");

    // Cria o vetor de imagens
    vector<string> images;

    // Recebe os nomes das imagens
    string line;
    if (file.is_open()) {
        while (getline(file,line)) {
            images.push_back(line);
        }
    }
    file.close();

    // Imprime na tabela
    ui->tableWidget->setRowCount(images.size());

    // Adiciona os itens
    for (int i = 0; i < images.size(); i++) {
        QTableWidgetItem *item0 = new QTableWidgetItem();
        item0->setText(QString::fromStdString(images[i].substr(20, 7)));
        QTableWidgetItem *item1 = new QTableWidgetItem();
        item1->setText(QString::fromStdString(images[i].substr(0, 10)));
        QTableWidgetItem *item2 = new QTableWidgetItem();
        item2->setText(QString::fromStdString(images[i].substr(11, 8)));

        ui->tableWidget->setItem(i, 0, item0);
        ui->tableWidget->setItem(i, 1, item1);
        ui->tableWidget->setItem(i, 2, item2);
    }
}

//vector<string> MainWindow::getInterfaceNetworks(){
//    vector<string> ips;
//    struct ifaddrs * ifAddrStruct=NULL;
//    struct ifaddrs * ifa=NULL;
//    void * tmpAddrPtr=NULL;

//    getifaddrs(&ifAddrStruct);

//    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
//        if (!ifa->ifa_addr) {
//            continue;
//        }
//        if (ifa->ifa_addr->sa_family == AF_INET) { // check it is IP4
//            // is a valid IP4 Address
//            tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
//            char addressBuffer[INET_ADDRSTRLEN];
//            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
//            string str(addressBuffer);
//            ips.push_back(str);
//            printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer);
//        }
//    }
//    if (ifAddrStruct!=NULL) freeifaddrs(ifAddrStruct);
//    return ips;
//}
