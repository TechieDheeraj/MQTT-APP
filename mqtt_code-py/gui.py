#!/usr/bin/python3
from tkinter import *

window = Tk()
window.geometry('400x300')
window.title("Dheeraj Chat")

lbl = Label(window, text = "WELCOME TO MY APP")
#lbl.grid(column=0, row=0)
lbl.pack(side=TOP, fill=X)

messages_frame = Frame(window)
messages_frame.pack(side=TOP, fill=X)

scrollbar = Scrollbar(window)  # To navigate through past messages.

def select_text_or_copy_text(e):
	#e.widget.select_range(0, 'end')
	e.widget.delete(0, 'end')

def send(event):
	print(entry_field.get())
	#lbl.configure(text = entry_field.get())
	#msg_list.insert(END, entry_field.get())
	msg_list.insert(END, my_msg.get())

# To Read Msg in Text Form
my_msg=StringVar()
my_msg.set("Type your message here")

btn_fr = Frame(window)
btn_fr.pack(side=TOP, fill=X)

btn = Button(btn_fr, text="send", fg="green", bg="black", width=5)
btn.bind('<Button-1>', send)
#btn.grid(column=2, row=2)
btn.pack(anchor=NE, padx=5)

msg_list = Listbox(window, height=10, width=40, yscrollcommand=scrollbar.set)
scrollbar.pack(side=RIGHT, fill=Y)
#scrollbar.grid(column=4, row=1)
msg_list.pack(anchor=CENTER, fill=Y, expand=True)


lbl1 = Label(messages_frame, text="Message Box", width=11)
lbl1.pack(side=LEFT, padx=0, pady=0)

entry_field = Entry(messages_frame, textvariable=my_msg, width=25)
entry_field.bind("<Return>", send)
#entry_field.bind('<Control-a>', select_text_or_copy_text)
#entry_field.bind("<Control-c>", select_text_or_copy_text)
entry_field.bind('<Delete>', select_text_or_copy_text)
entry_field.focus()
entry_field.pack(side=TOP, padx=5, fill=X, expand=True)


window.mainloop()
