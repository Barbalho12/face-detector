# DetectFaces

Sistema de autenticação por identificação facial

### Instalação do OpenCV na BeagleBone Black ###


Configurações de Host

sudo su
iptables --table nat --append POSTROUTING --out-interface wlan0 -j MASQUERADE
iptables --append FORWARD --in-interface eth1 -j ACCEPT
echo 1 > /proc/sys/net/ipv4/ip_forward


Configurações na Beagle
	sudo su
	route add default gw 192.168.7.1
	echo "nameserver 8.8.8.8" >> /etc/resolv.conf
	/etc/init.d/networking restart


Instalação de Dependências 
	sudo apt-get install build-essential
	sudo apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
	udo apt-get install python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev


Download OpenCV: https://sourceforge.net/projects/opencvlibrary/
	opencv-3.1.0.zip


	unzip opencv-3.1.0.zip
	cd opencv-3.1.0/
	mkdir release
	cd release
	cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local ..

	make
	sudo make install


Para a instalação em outra máquina, basta seguir o processo de instalação: 

	http://docs.opencv.org/2.4/doc/tutorials/introduction/linux_install/linux_install.html?highlight=installation

Obs: Para executar o programa ainda é necessário a instação de outras bibliotecas que podem ser encontradas no seguinte endereço:

	https://github.com/Barbalho12/beagleboneblack

### Configurando ambiente ###

Clona esse repositório:

	git clone https://github.com/Barbalho12/DetectFaces.git

Para executar o server, basta compilar o projeto no QT e executar:

	https://www.qt.io/

para executar o projeto no cliente basta executar o "compila.sh":

	./complila.sh

E depois executar passando os parametros:

	./detectFace-client IP_CAM IP_SERV SLEEP_TIME SIZE_FACE_MIN

sendo por padrão: IPCAM=0 IP_SERV=192.168.7.1 SLEEP_TIME=4 SIZE_FACE_MIN=200 