from tkinter import *
from tkinter import ttk
from tkinter import messagebox
import serial
import time 

frame = {
    "DDRA":"58",
    "DDRB":"55",
    "DDRC":"52",
    "DDRD":"49",
    "PORTA":"59",
    "PORTB":"56",
    "PORTC":"53",
    "PORTD":"50",
    "PINA":"57",
    "PINB":"54",
    "PINC":"51",
    "PIND":"48"
}

ser = serial.Serial()
def connect():
    ser.port = "com1"
    ser.baudrate = 9600
    try:
        if not ser.is_open:
            ser.open()
            messagebox.showinfo(title="Info", message="The port is opened!")
            l1.config(text="Connected", fg="green")
    except:
        pass

def disconnect():
    try:
        if ser.is_open:
            ser.close()
            messagebox.showinfo(title="Info", message="The port is closed successfully!")
            l1.config(text="Disconnected", fg="red")
    except:
        pass

def speedUp():
    try:
        if not ser.is_open:
            messagebox.showinfo(title="Warning!!", message="The port is closed, please press on connect button.")
        else:
            ser.write(b"0")
    except:
        pass

def speedDown():
    try:
        if not ser.is_open:
            messagebox.showinfo(title="Warning!!", message="The port is closed, please press on connect button.")
        else:
            ser.write(b"1")
    except:
        pass

def clockWise():
    try:
        if not ser.is_open:
            messagebox.showinfo(title="Warning!!", message="The port is closed, please press on connect button.")
        else:
            ser.write(b"2")
    except:
        pass

def antiClockWise():
    try:
        if not ser.is_open:
            messagebox.showinfo(title="Warning!!", message="The port is closed, please press on connect button.")
        else:
            ser.write(b"3")
    except:
        pass

def lightOn():
    try:
        if not ser.is_open:
            messagebox.showinfo(title="Warning!!", message="The port is closed, please press on connect button.")
        else:
            ser.write(b"4")
    except:
        pass

def lightOff():
    try:
        if not ser.is_open:
            messagebox.showinfo(title="Warning!!", message="The port is closed, please press on connect button.")
        else:
            ser.write(b"5")
    except:
        pass

def write():
    write.compo3 = ttk.Combobox(window, values=["PORTA", "PORTB", "PORTC", "PORTD"])
    write.compo3.set("PORTA")
    write.l3 = Label(text="Select A Port")
    write.compo3.place(x=10, y=230)
    write.l3.place(x=200, y=230)
    
    write.value = StringVar()
    write.data = Entry(textvariable=write.value)
    write.l4 = Label(text="Enter A Value From 0 to 255")
    write.data.place(x=10, y=270)
    write.l4.place(x=200, y=270)
    write.B4 = Button(text="Write", width=15, height=1, activebackground="black", activeforeground="white",command=send_frame)
    write.B4.place(x=110,y=300)

def send_frame():
    selected_port = write.compo3.get()
    port_adress = frame[selected_port]
    if selected_port == "PORTA":
        dir_adress = frame["DDRA"]
    elif selected_port == "PORTB":
        dir_adress = frame["DDRB"]
    elif selected_port == "PORTC":
        dir_adress = frame["DDRC"]
    elif selected_port == "PORTD":
        dir_adress = frame["DDRD"]

    l = f"@w {dir_adress} 255;"
    l2 = f"@w {port_adress} {write.value.get()};"
  

    ser.write(str(l).encode('ascii'))
    time.sleep(1)
    ser.write(str(l2).encode('ascii'))

    




def enter():
    if compo2.get() == "Write":
        write()

window = Tk()
window.geometry("350x350+300+300")
window.title("Debugger")

compo1 = ttk.Combobox(window, values=["com1"])
compo1.set("com1")
compo2 = ttk.Combobox(window, values=["Read", "Write"])
compo2.set("Write")
B1 = Button(text="Connect", command=connect, bg="green",fg="white")
B2 = Button(text="Disconnect", command=disconnect, bg="red", fg="white")
B3 = Button(text="Enter", width=15, height=1, activebackground="black", activeforeground="white", command=enter)
l1 = Label(text="Disconnected", fg="red")
l2 = Label(text="Select Operation")

compo1.place(x=10,y=10)
l1.place(x=200,y=10)
B1.place(x=70,y=50)
B2.place(x=220,y=50)
l2.place(x=200, y= 120)
compo2.place(x=10,y=120)
B3.place(x=110,y=170)
window.mainloop()