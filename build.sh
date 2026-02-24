# Compile all source files
gcc -c -I. -Iinclude nsigii-codec/nsigii_codec.c -o nsigii_codec.o -lm
gcc -c -I. -Iinclude rift-000/rift_000_tokenizer.c -o rift_000.o
gcc -c -I. -Iinclude rift-001/rift_001_process.c -o rift_001.o
gcc -c -I. -Iinclude rift-333/rift_333_ast.c -o rift_333.o
gcc -c -I. -Iinclude rift-444/rift_444_target.c -o rift_444.o
gcc -c -I. -Iinclude rift-555/rift_555_bridge.c -o rift_555.o
gcc -c -I. -Iinclude main.c -o main.o

# Link executable
gcc *.o -o rift -lm -lpthread
