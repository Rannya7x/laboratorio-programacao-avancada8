#include "stdio.h"
#include "mpeg.h"

int main (int argc, char **argv){
    if (argc<2){
        printf("Uso: %s <arquivo.mpg>\n", *argv);
        return 1;
    }

    FILE *mpg = fopen(argv[1], "rb");
    if(mpg == NULL){
        perror("Erro ao abrir arquivo");
        return 1;
    }

    unsigned char buffer[3];
    while(fread(buffer, sizeof(unsigned char), 3, mpg)==3){
        if(buffer[0]==0x00 && buffer[1] == 0x00 && buffer[2] == 0x01){
            unsigned char stream_id = fgetc(mpg);
            processar_stream(stream_id, mpg);
        } else{
            fseek(mpg, -2, SEEK_CUR);
        }
    }

    fclose(mpg);

    return 0;
}