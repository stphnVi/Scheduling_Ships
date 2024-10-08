CC = gcc
CFLAGS = -Wall -Wextra -g -I./Structs  # Agrega aquí cualquier otro directorio de encabezados que necesites

# Lista de archivos fuente, asegúrate de que NodeList.c esté incluido
SRCS = Equity.c PassageLR.c PassageRL.c main.c Structs/NodeList.c Structs/Boat.c Structs/BoatList.c Structs/BoatFactory.c Structs/NodeFactory.c ThreadsAdapter.c

# Generar archivos objeto
OBJS = $(SRCS:.c=.o)

# Nombre del ejecutable
TARGET = my_program

# Regla por defecto para construir el ejecutable
all: $(TARGET)

# Regla para crear el ejecutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Regla para compilar archivos fuente a archivos objeto
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para limpiar los archivos generados
clean:
	rm -f $(OBJS) $(TARGET)
