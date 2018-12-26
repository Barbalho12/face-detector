# Face Detector

Authentication system with facial identification

### Network settings on host 

```bash
sudo su
iptables --table nat --append POSTROUTING --out-interface wlan0 -j MASQUERADE
iptables --append FORWARD --in-interface eth1 -j ACCEPT
echo 1 > /proc/sys/net/ipv4/ip_forward
```

### Network settings on Beagle 

```bash
sudo su
route add default gw 192.168.7.1
echo "nameserver 8.8.8.8" >> /etc/resolv.conf
/etc/init.d/networking restart
```

### Installing OpenCV on BeagleBone Black

####  Dependency Installation:

```bash
sudo apt-get install build-essential
sudo apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
udo apt-get install python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev
```

```bash
# Download OpenCV: 
wget https://sourceforge.net/projects/opencvlibrary/opencv-3.1.0.zip

# Finalizado o download execute: 
unzip opencv-3.1.0.zip
cd opencv-3.1.0/
mkdir release
cd release
cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local ..
make
sudo make install
```

Note: To run the program you still need to install other libraries that can be found at the repository [algorithm-analysis-in-beagle]:

### Configurando ambiente

To run the server, just compile the project in [QT] and run it.
	
To run the project on the client, run the script `compila.sh`:
	
```bash
./complila.sh
```

And then execute passing the parameters:

- `IPCAM` (camera IP or 0 case connected via usb)
- `IP_SERV` (server IP) 
- `SLEEP_TIME` (wait time between each read) 
- `SIZE_FACE_MIN` (minimum face size detected in pixels)

```bash
./detectFace-client IP_CAM IP_SERV SLEEP_TIME SIZE_FACE_MIN
```

By default: 

- IPCAM=0 
- IP_SERV=192.168.7.1 
- SLEEP_TIME=4 
- SIZE_FACE_MIN=200 

### Print screen of the system in operation

![F1](images/cliente.jpg?raw=true "Execution on the client")
	
![F2](images/config.jpg?raw=true "Server network information")
	
![F3](images/infos.jpg?raw=true "Log of registered people")
	
![F4](images/save.jpg?raw=true "Directory with photos of the registered")
	
![F5](images/updates.png?raw=true "Update screen of last registered")


 [QT]: <https://www.qt.io/>
 [algorithm-analysis-in-beagle]: <https://github.com/Barbalho12/algorithm-analysis-in-beagle>

