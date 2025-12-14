import serial
from tkinter import Tk, Button

# Configura el puerto serial (ajusta el puerto según tu sistema)
arduino = serial.Serial(port='COM6', baudrate=9600, timeout=1)  
# Funciones para encender y apagar el LED
def turn_on():
    arduino.write(b'1')  # Enviar '1' para encender el LED

def turn_off():
    arduino.write(b'0')  # Enviar '0' para apagar el LED

# Configuración de la interfaz gráfica
root = Tk()
root.title("Controlar LED con Arduino")

Button(root, text="Encender LED", command=turn_on, width=40, height=4, bg="green", fg="white").pack(pady=10)
Button(root, text="Apagar LED", command=turn_off, width=40,height=4, bg="red", fg="white").pack(pady=10)

# Cerrar la aplicación y liberar el puerto serial
def on_closing():
    arduino.close()
    root.destroy()

root.protocol("WM_DELETE_WINDOW", on_closing)

# Iniciar la interfaz gráfica
root.mainloop()
