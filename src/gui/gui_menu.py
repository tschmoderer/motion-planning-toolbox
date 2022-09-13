from tkinter import *
from tkinter import messagebox

def alert():
    messagebox.showinfo("alerte", "Bravo!")

def create_menu(window):
    menubar = Menu(window)

    menu1 = Menu(menubar, tearoff=0)
    menu1.add_command(label="New project", command=alert)
    menu1.add_command(label="Open project", command=alert)
    menu1.add_command(label="Recent project", command=alert)
    menu1.add_separator()
    menu1.add_command(label="Save", command=alert)
    menu1.add_command(label="Save as...", command=alert)
    menu1.add_command(label="Recent project", command=alert)
    menu1.add_separator()
    menu1.add_command(label="Quit", command=window.quit)
    menubar.add_cascade(label="File", menu=menu1)

    menu2 = Menu(menubar, tearoff=0)
    menu2.add_command(label="Undo", command=alert)
    menu2.add_command(label="Redo", command=alert)
    menu2.add_separator()
    menu2.add_command(label="Cut", command=alert)
    menu2.add_command(label="Copy", command=alert)
    menu2.add_command(label="Paste", command=alert)
    menu2.add_separator()
    menu2.add_command(label="Preferences", command=alert)
    menubar.add_cascade(label="Edit", menu=menu2)

    menu4 = Menu(menubar, tearoff=0)
    menu4.add_command(label="Launch program", command=alert)
    menubar.add_cascade(label="Execute", menu=menu4)

    menu3 = Menu(menubar, tearoff=0)
    menu3.add_command(label="Documentation", command=alert)
    menu3.add_command(label="About", command=alert)
    menubar.add_cascade(label="Help", menu=menu3)

    window.config(menu=menubar)