# Modifica esta variable para hacer referencia al archivo con tu codigo fuente.
SOURCE_FILE = main.cpp

# Modifica esta variable para cambiar el nombre del ejecutable
TARGET_NAME = main.o

# Modifica esta variable para indicar donde se encuentra el dll de linux
PATH_TO_EDK_LINUX = /usr/home/@user/tallerEmotiv/bin/linux64

# Modifica esta variable para indicar donde se encuentre el framework edk
PATH_TO_FRAMEWORK = /Users/@user/tallerEmotiv/lib/Mac

# Obtener uname_s para determinar el sistema operativo.
UNAME_S := $(shell uname -s)


# Ajustar las banderas de compilacion con base en el sistema operativo.
# Asume que el sistema operativo es o linux o mac.
CFLAGS :=
ifeq ($(UNAME_S),Linux)
  CFLAGS += -L$(PATH_TO_EDK_LINUX) -ledk
else
  CFLAGS += -F$(PATH_TO_FRAMEWORK) -framework edk
endif


$(TARGET_NAME) : $(SOURCE_FILE)
	g++ $(SOURCE_FILE) $(CFLAGS) -o $(TARGET_NAME)
