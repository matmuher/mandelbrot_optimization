g++ no_avx.cpp -o no_avx.exe -O0 -Wall -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -mavx -mavx2

no_avx.exe 