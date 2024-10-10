# Variables
CC = gcc
CFLAGS = -Wall -Wextra -g -I./Structs

# Lista de archivos fuente
SRCS = Equity.c PassageLR.c PassageRL.c Setup.c main.c ThreadsAdapter.c Tica.c Structs/NodeList.c Structs/Boat.c Structs/BoatList.c Structs/BoatFactory.c

# Lista de archivos objeto
OBJS = $(SRCS:.c=.o)

# Nombre del ejecutable
TARGET = Scheduling_Ships

# Regla por defecto para construir el ejecutable
all: $(TARGET)

# Regla para crear el ejecutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Regla para limpiar los archivos generados
clean:
	rm -f $(OBJS) $(TARGET) *.gch

