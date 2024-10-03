CC = gcc             
CFLAGS = -Wall -pthread 

# Archivos fuente
SRCS = interfaceRasp.c   # Archivos fuente .c
OBJS = $(SRCS:.c=.o)

# Nombre del archivo ejecutable
EXEC = raspy

# Regla por defecto (lo que se ejecuta al ejecutar `make` sin argumentos)
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

# Dependencias

