import tkinter as tk
from PIL import Image, ImageTk

class Bote:
    def __init__(self, canvas, task_id, spriteDer, spriteIzq, posX, posY, velocidad, scale):
        self.canvas = canvas
        self.task_id = task_id
        self.spriteDer = spriteDer
        self.spriteIzq = spriteIzq
        self.current_sprite = spriteDer
        self.posX = posX
        self.posY = posY
        self.velocidad = velocidad

        # Cargar y redimensionar los sprites para ambos sentidos
        original_image_der = Image.open(spriteDer)
        resized_image_der = original_image_der.resize(
            (int(original_image_der.width * scale), int(original_image_der.height * scale)), Image.Resampling.LANCZOS)
        self.sprite_image_der = ImageTk.PhotoImage(resized_image_der)

        original_image_izq = Image.open(spriteIzq)
        resized_image_izq = original_image_izq.resize(
            (int(original_image_izq.width * scale), int(original_image_izq.height * scale)), Image.Resampling.LANCZOS)
        self.sprite_image_izq = ImageTk.PhotoImage(resized_image_izq)

        # Establecer el sprite actual en el canvas
        self.sprite = self.sprite_image_der
        self.id = self.canvas.create_image(posX, posY, image=self.sprite, anchor=tk.NW)
        self.move_direction = 1  # 1: derecha, -1: izquierda

    def update_status(self, status, duration, position):
        print(f"Updating position for boat {self.task_id}: position={position}")        
        adjusted_posY = self.posY - (self.sprite_image_der.height() / 2)
        boat_width = self.sprite_image_der.width()
            # Ajuste para FCFS: reducir el espacio para el primer barco
        if status=="FCFS" and position==0:
            self.posX = 50  # Posición inicial para el primer barco en FCFS, más cerca del borde
        else:
            # Ajustar la posición X con un espacio estándar para los demás barcos
            self.posX = (position * (boat_width + 30)) + 100  # Ajuste de 30px como espacio adicional entre barcos

        self.canvas.coords(self.id, self.posX, adjusted_posY)

    def mover(self):
        # Mover el barco en el canvas en la dirección actual
        self.canvas.move(self.id, self.velocidad * self.move_direction, 0)
        pos = self.canvas.coords(self.id)
        
        # Si toca el borde derecho (mayor que 1500), cambia a la izquierda
        if pos[0] > 1600 and self.move_direction == 1:
            self.move_direction = -1
            self.sprite = self.sprite_image_izq
            self.canvas.itemconfig(self.id, image=self.sprite)

        # Si toca el borde izquierdo (menor que 0), cambia a la derecha
        elif pos[0] < 0 and self.move_direction == -1:
            self.move_direction = 1
            self.sprite = self.sprite_image_der
            self.canvas.itemconfig(self.id, image=self.sprite)


class Letrero:
    def __init__(self, canvas, posX, posY, scale=1):
        self.canvas = canvas
        self.posX = posX 
        self.posY = posY 
        
        # Redimensionar la imagen del letrero con Pillow
        original_image = Image.open("../Assets/rightArrow.png")
        resized_image = original_image.resize((int(original_image.width * scale), int(original_image.height * scale)), Image.Resampling.LANCZOS)
        self.sprite = ImageTk.PhotoImage(resized_image)

        self.id = self.canvas.create_image(posX, posY, image=self.sprite, anchor=tk.NW)
        self.text_id = self.canvas.create_text(posX + 50, posY + 80, text="", font=("Arial", 20), fill="black")

    
class Canal:
    def __init__(self, canvas, largo, canal, fondo):
        self.canvas = canvas
        self.largo = largo 
        self.tile_sprite = tk.PhotoImage(file=canal)
        self.fondo_sprite = ImageTk.PhotoImage(Image.open(fondo))
        self.tiles = []
        self.crear_fondo()
       # self.crear_canal()

    def crear_fondo(self):
        canvas_width = 1600  # Ancho del canvas
        canvas_height = 800  # Alto del canvas
        tile_width = 100
        tile_height = 100

        # Rellenar el fondo con tiles de agua
        for x in range(0, canvas_width, tile_width):
            for y in range(0, canvas_height, tile_height):
                self.canvas.create_image(x, y, image=self.fondo_sprite, anchor=tk.NW)
    
    
