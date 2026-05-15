# laboratorio-programacao-avancada8

## 1. Objetivo

Exercitar a manipulação de arquivos e dados binários através da decodificação de um arquivo de vídeo MPEG para extrair metadados de fluxos (streams), como dimensões da imagem, taxa de quadros e tipos de figuras.

## 2. Lógica de Streams

### 2.1 Identificação de Blocos (Start Code)

Diferente de arquivos com cabeçalhos fixos no início, o MPEG é formado por uma série de streams independentes. Cada bloco é obrigatoriamente iniciado pelo start code prefix `00 00 01` em hexadecimal. O byte que segue este prefixo é o identificador do tipo de stream.

### 2.2 Principais Identificadores
- **Sequence Header (0xB3):** Contém informações globais como largura, altura e frame rate.
- **Picture (0x00):** Contém o tipo de codificação da imagem (I, P ou B).
- **Group of Pictures (0xB8):** Marca o início de uma série de figuras.
- **Slice (0x01 até 0xAF):** Contém informações para decodificar partes da figura atual.

## 3. Manipulação de Bits
### 3.1 Extração de Dimensões (Sequence)

Os dados de tamanho estão "desalinhados" em relação aos bytes do arquivo.

- **Largura (Horizontal Size):** Obtida multiplicando o primeiro byte por 16 e somando aos 4 bits mais significativos do segundo byte (`byte1 * 16 + (byte2 >> 4)`).
- **Altura (Vertical Size):** Obtida usando os 4 bits menos significativos do segundo byte multiplicados por 256, somados ao terceiro byte completo.

### 3.2 Tipo de Figura (Picture)
O tipo de quadro é extraído do segundo byte após o código `0x00`. A lógica consiste em realizar um deslocamento de 3 bits para a direita e aplicar a máscara `0x07` para isolar o valor (1=I, 2=P, 3=B).

## 4. Fluxo de Execução e Interface

O programa opera via terminal e deve processar o arquivo byte a byte em busca dos prefixos de início.

O executável recebe o nome do arquivo de vídeo como primeiro argumento. `./mpeg_info dodo.mpg`.

O programa deve listar sequencialmente cada código encontrado e seus respectivos metadados formatados:

```bash
--> Código: b3 -- Sequence Header -- Width = 360, Height = 288 -- Frame rate = 25.000fps
--> Código: b8 -- Group of Pictures
--> Código: 00 -- Picture -- Tipo: I
--> Código: 01 -- Slice
--> Código: 00 -- Picture -- Tipo: P
--> Código: 01 -- Slice
--> Código: 00 -- Picture -- Tipo: B
--> Código: 01 -- Slice
--> Código: 00 -- Picture -- Tipo: B
--> Código: 01 -- Slice
--> Código: 00 -- Picture -- Tipo: P
--> Código: 01 -- Slice
--> Código: 00 -- Picture -- Tipo: B
--> Código: 01 -- Slice
--> Código: 00 -- Picture -- Tipo: B
--> Código: 01 -- Slice
--> Código: 00 -- Picture -- Tipo: P
--> Código: 01 -- Slice
--> Código: 00 -- Picture -- Tipo: B
--> Código: 01 -- Slice
--> Código: 00 -- Picture -- Tipo: B
--> Código: 01 -- Slice
```

## 5. Limpeza

Execute no terminal: `make clean`