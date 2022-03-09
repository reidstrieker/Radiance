# everything you need to compile is here in the Radiance folder, including SDL2
# run the following command in the folder to create a .exe
g++ -Isrc/include -Lsrc/lib -o Radiance *.cpp -lmingw32 -lSDL2main -lSDL2