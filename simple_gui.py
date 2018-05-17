#simple GUI
#input from SD card is an array with time, speed, other values on there


from Tkinter import *

#create the window

root = Tk()
root.configure(background='black')
#modify root window
root.title("Simple GUI")
root.geometry("1000x650+0+0")

#set background to black
frame_1=Frame(root, width=1000, height=650, bg = "black", relief=SUNKEN)
frame_1.pack(side = TOP)

title_label= Label(frame_1, font = ("arial", 20, 'bold'), text = "Bike Speedometer Statistics", fg = "crimson", bg = frame_1['bg'],bd=10, anchor = 'w') 

title_label.grid(row = 0, columnspan = 3);

root.mainloop()
