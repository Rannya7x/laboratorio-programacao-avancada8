#include "stdio.h"
//função para processar o sequence header
static void processar_sequence_header(FILE *mpg_file){
    //leitura dos 4 bytes do sequence header
    unsigned char b1=fgetc(mpg_file);
    unsigned char b2=fgetc(mpg_file);
    unsigned char b3=fgetc(mpg_file);
    unsigned char b4=fgetc(mpg_file);

    //calculo da largura, altura e fr_code conforme roteiro
    unsigned int largura = b1 * 16 + (b2 >> 4); 
    unsigned int altura = (b2 & 0x0F) * 256 + b3; 
    unsigned int fr_code = b4 & 0x0f;

    
    double frame_rate[] = {0, 23.976, 24.0, 25.0, 29.97, 30.0, 50.0, 59.94, 60.0};
    double fr = (fr_code >= 1 && fr_code <=8) ? frame_rate[fr_code]:0;

    printf("--> Código: b3 -- Sequence Header -- Width = %d, Height = %d -- Frame rate = %.3ffps\n", largura, altura, fr);
}

static void processar_picture(FILE *mpg_file){
    fgetc(mpg_file); //leitura do byte de temporal_reference
    unsigned char b2 = fgetc(mpg_file); 
    unsigned int tipo_code = (b2>>3) & 0x07;
    char tipo = (tipo_code == 1)? 'I':(tipo_code == 2)? 'P': (tipo_code == 3)? 'B':'?';
    printf("--> Código: 00 -- Picture -- Tipo: %c\n", tipo);
}


//função principal para processar os diferentes tipos de stream
void processar_stream(unsigned char stream_id, FILE *mpg_file){
    if (stream_id == 0xb3){
        processar_sequence_header(mpg_file);
    } else if (stream_id ==0x00){
        processar_picture(mpg_file);
    } else if (stream_id == 0xb8){
    printf("--> Código: b8 -- Group of Pictures\n");
    } else if (stream_id >= 0x01 && stream_id <= 0xaf){
        printf("--> Código: %.2x -- Slice\n", stream_id);
    } else{
        printf("--> Código: %.2x -- Tipo de stream não implementado\n", stream_id);
    }
}