CC = gcc              
CFLAGS = -Wall -pthread 

# Archivos fuente
SRCS_SCHEDULER = A_Scheduling.c   # Archivos fuente de scheduling
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
$(OBJS_SCHEDULER): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para compilar interfaceRasp con wiringPi
$(OBJS_INTERFACE): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -lwiringPi

# Limpiar los archivos generados
clean:
	rm -f $(OBJS_SCHEDULER) $(OBJS_INTERFACE) $(EXEC)

