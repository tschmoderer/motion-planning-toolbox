# Configuration file 
BUILD_DIR="/home/tschmoderer/Documents/projets/test/motion-planning-toolbox/build" 
SOURCE_DIR="/home/tschmoderer/Documents/projets/test/motion-planning-toolbox/app"
BIN_DIR="/home/tschmoderer/Documents/projets/test/motion-planning-toolbox/app/bin/"

LIB_VERSION       = "0.5.0"
LIB_DOCUMENTATION = "https://tschmoderer.github.io/motion-planning-toolbox/html/index.html"
LIB_CODE_LINK     = "https://github.com/tschmoderer/motion-planning-toolbox"

GUI_AUTHOR  = "T. Schmoderer"
GUI_EMAIL   = "iathena@mailo.com"
GUI_LICENSE = "GNU GENERAL PUBLIC LICENSE"
GUI_YEAR    = "2022"
GUI_STATUS  = "Dev"
GUI_VERSION = "1.0.0"

# --
# Configuration of UI
# --

UI_WIDTH  = 1600
UI_HEIGHT = 900

# General parameters
UI_EXP_TYPES = ["ODE", "Retarded ODE"]
UI_MAX_NAME_LEN  = 10

## State dimensions
UI_MIN_STATE_DIM = 1
UI_MAX_STATE_DIM = 10

## Time parameters
UI_TIME_STEP     = 0.01
UI_MIN_TIME      = -100


## Trajectories parameters
UI_TRAJECTORY_METHODS = ["Linspace"]
UI_TRAJECTORY_LINSPACE_MIN = 2
UI_TRAJECTORY_LINSPACE_MAX = 1025

## Methods parameters
UI_METHODS_ODE = ["RK1", "RK4"]
UI_METHODS_INTERPOLATION = ["linear"]
