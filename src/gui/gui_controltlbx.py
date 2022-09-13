# coding: utf-8
import os
from tkinter import *
from gui_menu import *

dirname = os.path.dirname(__file__)

window = Tk(className="Motion Planning ToolBox")
window.title("Motion Planning ToolBox / v")
window.geometry("1000x760")
window.iconphoto(False, PhotoImage(file=os.path.join(dirname, "assets/icons/rocket.png")))

create_menu(window)

window.mainloop()