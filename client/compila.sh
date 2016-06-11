#g++ -c -pipe -O2 -std=c++0x -Wall -W -D_REENTRANT -fPIC -DQT_NO_DEBUG -DQT_CORE_LIB -I. -I/opt/Qt5.5.1/5.5/gcc_64/include -I/opt/Qt5.5.1/5.5/gcc_64/include/QtCore -I. -I/opt/Qt5.5.1/5.5/gcc_64/mkspecs/linux-g++ -o main.o main.cpp
#g++ -Wl,-O1 -Wl,-rpath,/opt/Qt5.5.1/5.5/gcc_64 -Wl,-rpath,/opt/Qt5.5.1/5.5/gcc_64/lib -o client main.o   `pkg-config opencv --libs` -L/opt/Qt5.5.1/5.5/gcc_64/lib -lQt5Core -lpthread 

g++ -c -pipe -O2 -std=c++0x -Wall -W -D_REENTRANT -fPIC -DQT_NO_DEBUG -DQT_CORE_LIB -I. -I/opt/Qt5.5.1/5.5/gcc_64/include -I/opt/Qt5.5.1/5.5/gcc_64/include/QtCore -I. -I/opt/Qt5.5.1/5.5/gcc_64/mkspecs/linux-g++ -o main.o main.cpp

g++ -c -pipe -O2 -std=c++0x -Wall -W -D_REENTRANT -fPIC -DQT_NO_DEBUG -DQT_CORE_LIB -I. -I/opt/Qt5.5.1/5.5/gcc_64/include -I/opt/Qt5.5.1/5.5/gcc_64/include/QtCore -I. -I/opt/Qt5.5.1/5.5/gcc_64/mkspecs/linux-g++ -o common_dht_read.o libs/common_dht_read.cpp

g++ -c -pipe -O2 -std=c++0x -Wall -W -D_REENTRANT -fPIC -DQT_NO_DEBUG -DQT_CORE_LIB -I. -I/opt/Qt5.5.1/5.5/gcc_64/include -I/opt/Qt5.5.1/5.5/gcc_64/include/QtCore -I. -I/opt/Qt5.5.1/5.5/gcc_64/mkspecs/linux-g++ -o bbb_dht_read.o libs/Beaglebone_Black/bbb_dht_read.cpp

g++ -c -pipe -O2 -std=c++0x -Wall -W -D_REENTRANT -fPIC -DQT_NO_DEBUG -DQT_CORE_LIB -I. -I/opt/Qt5.5.1/5.5/gcc_64/include -I/opt/Qt5.5.1/5.5/gcc_64/include/QtCore -I. -I/opt/Qt5.5.1/5.5/gcc_64/mkspecs/linux-g++ -o bbb_mmio.o libs/Beaglebone_Black/bbb_mmio.cpp

g++ -c -pipe -O2 -std=c++0x -Wall -W -D_REENTRANT -fPIC -DQT_NO_DEBUG -DQT_CORE_LIB -I. -I/opt/Qt5.5.1/5.5/gcc_64/include -I/opt/Qt5.5.1/5.5/gcc_64/include/QtCore -I. -I/opt/Qt5.5.1/5.5/gcc_64/mkspecs/linux-g++ -o BlackCore.o libs/BlackLib/v3_0/BlackCore.cpp

g++ -c -pipe -O2 -std=c++0x -Wall -W -D_REENTRANT -fPIC -DQT_NO_DEBUG -DQT_CORE_LIB -I. -I/opt/Qt5.5.1/5.5/gcc_64/include -I/opt/Qt5.5.1/5.5/gcc_64/include/QtCore -I. -I/opt/Qt5.5.1/5.5/gcc_64/mkspecs/linux-g++ -o BlackGPIO.o libs/BlackLib/v3_0/BlackGPIO/BlackGPIO.cpp

g++ -Wl,-O1 -Wl,-rpath,/opt/Qt5.5.1/5.5/gcc_64 -Wl,-rpath,/opt/Qt5.5.1/5.5/gcc_64/lib -o client main.o common_dht_read.o bbb_dht_read.o bbb_mmio.o BlackCore.o BlackGPIO.o   `pkg-config opencv --libs` -L/opt/Qt5.5.1/5.5/gcc_64/lib -lQt5Core -lpthread 