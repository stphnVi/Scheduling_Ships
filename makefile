CC = gcc              
CFLAGS = -Wall -pthread 
CFLAGS += -Wall -Wextra -g -I.Canal/Structs 
CFLAGS += -Wall -Wextra -g -I.Canal/Control 

# Archivos fuente
SRCS_SCHEDULER = A_Scheduling.c \
                 Canal/Control/Equity.c \
                 Canal/Control/PassageLR.c \
                 Canal/Control/PassageRL.c \
                 Canal/Control/Setup.c \
                 Canal/Control/ThreadsAdapter.c \
                 Canal/Control/Tica.c \
                 Canal/Control/Time.c \
                 Canal/Structs/NodeList.c \
                 Canal/Structs/Boat.c \
                 Canal/Structs/BoatList.c \
                 Canal/Structs/BoatFactory.c  # Archivos fuente de scheduling

SRCS_INTERFACE = interfaceRasp.c  # Archivo fuente para interfaceRasp

# Archivos objeto
OBJS_SCHEDULER = $(SRCS_SCHEDULER:.c=.o)
OBJS_INTERFACE = $(SRCS_INTERFACE:.c=.o)

# Nombre del archivo ejecutable
EXEC = scheduler

# Regla por defecto (lo que se ejecuta al ejecutar `make` sin argumentos)
all: $(EXEC)

# Enlace final de los archivos
$(EXEC): $(OBJS_SCHEDULER) $(OBJS_INTERFACE)
	$(CC) $(CFLAGS) -o $@ $(OBJS_SCHEDULER) $(OBJS_INTERFACE) -lwiringPi  # Enlazar los archivos de interfaceRasp con wiringPi

# Regla para compilar A_Scheduling sin wiringPi
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar los archivos generados
clean:
	rm -f $(OBJS_SCHEDULER) $(OBJS_INTERFACE) $(EXEC)
