import time
from tkinter import *
import serial.tools.list_ports
import logging

window = Tk()
window.configure(background='white')
window.geometry("1000x400")
window.title("Temp")

def start():
    print(">>> Start GUI <<<\n")
    window.mainloop()

x=0
y=0
val=0
t=0
prevt=0
mxval=0
mnval=0
def readCom():
    global x,y,val,t,prevt,mxval,mnval

    for i in range(100):
        while ser.in_waiting:
            temp = ord(ser.read())

            if temp == ord('@'):
                val = ord(ser.read())
                p = int(ord(ser.read()) / 255 * 1000)
                if val>mxval:
                    mxval=val
                if val<mnval:
                    mnval=val
                prevt = t
                t+=1
                canvas.create_line(prevt, 300 - y, t, 300 - val, fill='white')
                y = val
                if t >= 1000 or prevt>t:
                    t = 0
                    prevt=0
                    am = str((mxval/255*5)-(mnval/255*5))
                    print(am)
                    v.set("Amplitude = "+am+" V")
                    mxval = val
                    mnval =val
                    canvas.delete("all")
                    canvas.create_line(0, 152, 1000, 152, fill='red')
                    canvas.create_line(0, 300, 1000, 300, fill='red')
                    canvas.create_line(0, 5, 1000, 5, fill='red')


    window.after(1, readCom)



logger = logging.getLogger('ftpuploader')

canvas = Canvas(window,width=1000, height=350,bg='black')

canvas.grid(row=1, column=1, sticky=W, pady=4)

v=StringVar()
l = Label(window, textvariable=v,font = "Verdana 16 bold")
l.grid(row=2, column=1, sticky=W, pady=4)


# open serial port
try:
    #port_name = ports[0].device
    ser = serial.Serial("COM1", baudrate=9600, timeout=5, bytesize=8, parity=serial.PARITY_NONE, stopbits=1)
    time.sleep(2)
    readCom()
    start()

except Exception as e:
    logger.error(str(e))
    print("error")
    window.title("Not Available")
    window.mainloop()
