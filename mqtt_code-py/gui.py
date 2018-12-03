#!/usr/bin/python3
from tkinter import *

window = Tk()
window.geometry('350x200')
window.title("Dheeraj Chat")

lbl = Label(window, text = "WELCOME TO MY APP")
#lbl.grid(column=0, row=0)
lbl.pack(side=TOP)

messages_frame = Frame(window)
messages_frame.pack(fill=X)


#my_msg = StringVar()  # For the messages to be sent.
#my_msg.set("Type your messages here.")
scrollbar = Scrollbar(window)  # To navigate through past messages.

def send(event):
	print(entry_field.get())
	#lbl.configure(text = entry_field.get())
	msg_list.insert(END, entry_field.get())

####
msg_list = Listbox(window, height=15, width=50, yscrollcommand=scrollbar.set)
scrollbar.pack(side=RIGHT, fill=Y)
#scrollbar.grid(column=4, row=1)
msg_list.pack(side=TOP, fill=Y)
####

#entry_field = Entry(window, textvariable=my_msg, width=30)

lbl1 = Label(messages_frame, text="Message Box", width=11)
lbl1.pack(side=LEFT, padx=0, pady=0)

entry_field = Entry(messages_frame, width=20)
#entry_field = Entry(window, width=30)
entry_field.bind("<Return>", send)
#entry_field.grid(column=0, row=2)
entry_field.focus()
#entry_field.pack(side=TOP, fill=Y)
entry_field.pack(side=LEFT, padx=5, fill=X)


#btn = Button(window, text="send", command=send)
btn = Button(window, text="send")
btn.bind('<Button-1>', send)
#btn.grid(column=2, row=2)
btn.pack(side=RIGHT, fill=None)


window.mainloop()



















#messages_frame = tkinter.Frame(top)
#my_msg = tkinter.StringVar()  # For the messages to be sent.
#my_msg.set("Type your messages here.")
#scrollbar = tkinter.Scrollbar(messages_frame)  # To navigate through past messages.

#msg_list = tkinter.Listbox(messages_frame, height=15, width=50, yscrollcommand=scrollbar.set)
#scrollbar.pack(side=tkinter.RIGHT, fill=tkinter.Y)
#msg_list.pack(side=tkinter.LEFT, fill=tkinter.BOTH)
#msg_list.pack()
#messages_frame.pack()

#entry_field = tkinter.Entry(top, textvariable=my_msg)
#entry_field.bind("<Return>", send)
#entry_field.pack()
#send_button = tkinter.Button(top, text="Send", command=send)
#send_button.pack()
#top.protocol("WM_DELETE_WINDOW", on_closing)

