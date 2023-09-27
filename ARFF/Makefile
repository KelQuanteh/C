# Especifica o compilador C (GCC)
CC = gcc

# Opções de compilação, -Wall ativa avisos e -g inclui informações de depuração
CFLAGS = -Wall -g

# Lista de arquivos-fonte do programa
SRCS = main.c arff.c log.c

# Lista de arquivos-objeto gerados a partir dos arquivos-fonte
OBJS = $(SRCS:.c=.o)

# Nome do arquivo executável a ser gerado
EXEC = program

# Regra padrão: constrói o programa
all: $(EXEC)

# Regra para construir o arquivo executável
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

# Regra genérica para gerar arquivos-objeto a partir dos arquivos-fonte
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar arquivos gerados
clean:
	rm -f $(OBJS) $(EXEC)
