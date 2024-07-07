#include <stdio.h>
#include <stdlib.h>
#include "./structs/program_data.h"
#include "./lectura/leer_archivo.h"

int main(int argc, char** argv){
    ProgramData* data;
    if(argc>0){
        FILE* input = fopen(argv[1], "r");
        data = leer_archivo(input);
    }
    print_data(data);
    return 0;
}
