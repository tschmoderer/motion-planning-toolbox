# -*- coding: utf-8 -*-

from PyQt6.QtGui import QIcon
import qtawesome as qta

from .config import *

class IconPlus(QIcon): 
    def __init__(self) -> None:
        super().__init__(qta.icon(ICON_PLUS))

class IconMinus(QIcon): 
    def __init__(self) -> None:
        super().__init__(qta.icon(ICON_MINUS))

class IconRun(QIcon): 
    def __init__(self) -> None:
        super().__init__(qta.icon(ICON_RUN))

class IconPostProcess(QIcon): 
    def __init__(self) -> None:
        super().__init__(qta.icon(ICON_POSTPROCESS))   

class IconNewFile(QIcon): 
    def __init__(self) -> None:
        super().__init__(qta.icon(NEW_FILE))       

class IconCheck(QIcon): 
    def __init__(self) -> None:
        super().__init__(qta.icon(CHECK_MARK))    

class IconGear(QIcon):
    def __init__(self) -> None:
        super().__init__(qta.icon(CONFIGURATION))   

class IconUpdate(QIcon):
    def __init__(self) -> None:
        super().__init__(qta.icon(UPDATE))

class IconPaint(QIcon):
    def __init__(self) -> None:
        super().__init__(qta.icon(PAINT))