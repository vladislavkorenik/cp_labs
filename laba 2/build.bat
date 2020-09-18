g++ -c -DBUILD_DLL logger.cpp
g++ -shared -o logger.dll logger.o -Wl,--out-implib,liblogger.a