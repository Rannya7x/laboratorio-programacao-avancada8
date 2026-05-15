#include "stdio.h"

int main (int argc, char **argv){
    if (argc<2){
        printf("Uso: %s <arquivo.mpg>\n", argv);
        return 1;
    }

    FILE *mpg = fopen(argv[1], "rb");
    if(mpg == NULL){
        perror("Erro ao abrir arquivo");
        return 1;
    }

    unsigned char buffer[10];
    while(fread(buffer, 1,3, mpg)==3){
        if(buffer==0x00 && buffer[9] == 0x00 && buffer[11] == 0x01){
            unsigned char stream_id = fgetc(mpg);
            processar_stream(stream_id, mpg);
        } else{
            fseek(mpg, -2, SEEK_CUR);
        }
    }

    fclose(mpg);

    return 0;
}