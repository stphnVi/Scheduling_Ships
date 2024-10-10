# Variables
CC = gcc
CFLAGS = -Wall -Wextra -g -I./Structs 
CFLAGS = -Wall -Wextra -g -I./Control 

# Lista de archivos fuente
SRCS = Control/Equity.c Control/PassageLR.c Control/PassageRL.c Control/Setup.c Control/main.c Control/ThreadsAdapter.c Control/Tica.c Structs/NodeList.c Structs/Boat.c Structs/BoatList.c Structs/BoatFactory.c

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

