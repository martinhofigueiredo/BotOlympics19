import serial
ser = serial.Serial('/dev/ttyACM0', 57600)

while True:
    data = ser.readline()
    if data:
        print(data)

if(data == "Direita =0\n"):
	print("tou manel")