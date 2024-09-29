CC = gcc             
CFLAGS = -Wall -pthread 

# Archivos fuente
SRCS = A_Scheduling.c   # Archivos fuente .c

# Archivos que se generarán a partir de los archivos fuente
OBJS = $(SRCS:.c=.o)

# Nombre del archivo ejecutable
EXEC = scheduler

# Regla por defecto (lo que se ejecuta al ejecutar `make` sin argumentos)
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

# Dependencias: A_Scheduling.o depende de scheduling.h
A_Scheduling.o: scheduling.h
