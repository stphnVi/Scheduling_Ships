import tkinter as tk
from graphic_objects import Canal, Bote, Letrero
import socket
import json
import time

socket_path = "/tmp/ship_socket"


def actualizar_estado(data, botes, letrero, canvas):
    tasks = data.get("tasks", [])
    scheduler = data.get("scheduler", "")
    print(scheduler)
    status=""

      # Si el scheduler es FCFS, invertir las posiciones visuales
    if scheduler == "FCFS" or "Priority":
        status="FCFS"
        # Invertir las posiciones para que la primera tarea se dibuje al final y la última al inicio
        for i, task in enumerate(tasks):
            # Recalcular la posición inversa
            task["position"] = len(tasks) - 1 - i


    for task in tasks:
        task_id = task["task_id"]
        boat_id = task["boat_id"]
        position = task["position"]
        

        # Verificar si el bote ya existe, si no, crearlo usando task_id
        if task_id not in botes:
            if boat_id == 1:  # Cargo ship
                botes[task_id] = Bote(canvas, task_id, "../Assets/cargoShipDer.png", "../Assets/cargoShip.png", 0, 300, velocidad=1, scale=0.1)
            elif boat_id == 2:  # Fishing boat
                botes[task_id] = Bote(canvas, task_id, "../Assets/fisherBoatDer.png", "../Assets/fisherBoat.png", 0, 300, velocidad=3, scale=0.1)
            elif boat_id == 3:  # Tombo boat
                botes[task_id] = Bote(canvas, task_id, "../Assets/tomboBoatDer.png", "../Assets/tomboBoat.png", 0, 300, velocidad=5, scale=0.1)

        # Actualizar la posición del bote existente usando task_id
        bote = botes[task_id]
        
        bote.update_status(status, 0, position)

def leer_desde_socket(client, botes, letrero, canvas):
    try:
        data = client.recv(1024).decode('utf-8').strip()
        if data:
            print(f"Datos recibidos: {data}")
            # Dividir los datos por el delimitador "\n" para manejar múltiples JSON
            mensajes = data.split('\n')
            for mensaje in mensajes:
                if mensaje:
                    try:
                        json_data = json.loads(mensaje)
                        actualizar_estado(json_data, botes, letrero, canvas)
                        time.sleep(0.5)  #Introduce a delay between status updates for visualization
                    except json.JSONDecodeError:
                        print("Error decodificando JSON en mensaje:", mensaje)
    except BlockingIOError:
        pass  # No hay datos disponibles aún, ignorar el error

    # Llamar a esta función de nuevo después de 100 ms para verificar nuevos datos
    root.after(100, leer_desde_socket, client, botes, letrero, canvas)


def main():
    # Crear la ventana principal
    global root
    root = tk.Tk()
    root.title("Canal")
    root.geometry("1600x800")
    root.resizable(False, False)
    
    # Crear un canvas donde dibujar
    canvas = tk.Canvas(root, width=1600, height=800)
    canvas.pack()

    # Crear el canal con el sprite    
    canal = Canal(canvas, 10, canal="../Assets/channelTile.png", fondo="../Assets/waterTile.png")
    
    # Diccionario para almacenar los botes por task_id
    botes = {}

    # Crear letrero
    letrero = Letrero(canvas, 800, 100, scale=0.1)

    # Conectar al socket Unix Domain
    client = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
    client.connect(socket_path)
    client.setblocking(False)  # Establecer el socket en modo no bloqueante

    # Iniciar la lectura del socket
    leer_desde_socket(client, botes, letrero, canvas)
    
    # Iniciar el bucle principal de Tkinter
    root.mainloop()

    # Cerrar el socket al salir
    client.close()

if __name__ == "__main__":
    main()
