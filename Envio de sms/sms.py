#coding:utf-8
import time
import serial

for n in range(0,10):
        # Conexão com a porta serial
        dongle = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)
        print "pegou"

        # Escreve o comando que será enviado para o chip
        dongle.write('ATZ\r')
        dongle.write('AT+CMGF=1\r')
        dongle.write('AT+CMGS="+5511987379974"\r')
        dongle.write('Ble ble ble Mensagem ! by: Raspberry do Humberto!\n')

        print "pegou1"
        
        
        dongle.write(chr(26))
        print "pegou2"

        # Executa efetivamente o comando
        line = dongle.readline()

        print line

        # Close the connection
        dongle.close()
        time.sleep(5)

