g++ -Wall -D__WINDOWS_WASAPI__ -Iinclude -o main main.cpp RtAudio.cpp -lole32 -lwinmm -lksuser -lmfplat -lmfuuid -lwmcodecdspuuid -lsndfile