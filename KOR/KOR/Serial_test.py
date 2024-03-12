import serial
import time

# Defina a porta serial do Arduino (ajuste conforme necessário)
porta_serial = "/dev/ttyACM1"  # Linux
# porta_serial = "COM3"         # Windows

# Inicialize a comunicação serial com o Arduino

arduino = serial.Serial(porta_serial, 9600, timeout=1)


while True:

    linha = arduino.readline().decode('utf-8').strip()
    valores = linha.split(",")
    if "" in valores:
        pass
    else:
        valores = [float(valor) for valor in valores]
        print(valores)
