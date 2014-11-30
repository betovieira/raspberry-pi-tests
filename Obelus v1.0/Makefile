#   usado para criar o exe do jogo, neste caso, criaria o game.exe
TARGETS = obelus
#   usado para compilar o codigo no padrão c99, CC é o nome da variavel escolida pra receber o comando gcc
CC = gcc -std=c99
#   usado para buscar todos os arquivos .c na pasta, quando eu uso $(wildcard *.c), eu estou buscando todos os arquivos .c contido na mesma pasta do make
#   se eu usar $(wildcard */*.c), eu vou acessar todas as pastas dentro da pasta do make e procurar por arquivos .c, pra mais niveis, add */
SRC = $(wildcard *.c)
#   usado para gerar os objetos e gerar por fim o exe final, como eu passei SRC como parametro, ele vai buscar os arquivos.o no mesmo local dos .c
OBJ = $(SRC:.c=.o)
#   flags do make (tem varias, sugiro olhar na net), neste caso ele traz alguns warnings basicos, caso ocorra
CFLAGS = -W -Wall -pedantic
#   usado para inserir suas bibliotecas, usem assim msm, tem todas as necessarias para o allegro aqui
LIBS = -lallegro  -lallegro_color -lallegro_audio -lallegro_main -lallegro_image -lallegro_font -lallegro_ttf -lallegro_primitives -lallegro_dialog -lallegro_acodec -lcurl

#   essa parte é mais complicadianha, basicamente ele usa os parametros definidos acima para gerar nosso make, não precisa mudar, independente das pastas
all: $(TARGETS)

obelus: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)
#   usado para o make clean, se digitar o make clean ele cai neste caso e executa o rm, removendo todos os arquivos.o e o targets, neste caso, game.exe
clean:
	rm -f $(TARGETS)
	rm -rf *.o