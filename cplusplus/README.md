# Ejemplos para programar en C++ usando la API de Emotiv.

## Instrucciones de compilacion.

### Linux
En Linux se tiene que incluir el path al dll que contiene las librerias de
emotiv.

        g++ main.cpp -l../../bin/linux64 -ledk

o para darle un nombre al ejecutable

        g++ main.cpp -o main.o -l../../bin/linux64 -ledk



### Mac OS

*Se recomienda mover la carpeta edk.framework en tallerEmotiv/lib/Mac/edk.framework a /Library/Frameworks*

Mac OS utiliza un formato llamado framework para manejar las librerias dll, en
este caso se le tiene que dar el path al archivo framework y despues se le tiene
que especificar con la bandera framework el framework a utilizar.

        g++ main.cpp -o main.o -F/Library/Frameworks -framework edk


### Makefile
En este proyecto tambien se incluye una plantilla de Makefile
para compilar proyectos más fácilmente, la única modificación que se
tiene que realizar es el PATH a dónde se encuentra ya sea el dll de linux
o el framework de Mac,

Por ejemplo:

En Linux,

        PATH_TO_EDK_LINUX = /usr/home/@user/tallerEmotiv/bin/linux64

En Mac,

        PATH_TO_FRAMEWORK = /Library/Frameworks

### Xcode
Los proyectos en este repositorio pueden ser compilados en Xcode, estos archivos se pueden usar de base para futuros proyectos.

También se puede realizar un nuevo proyecto de Xcode; para ello, seguir los siguientes pasos:

1. Crear un nuevo proyecto de C++ en Xcode.

2. En la barra de navegación izquierda, seleccionar la raíz del proyecto (un ícono azul).

3. En la parte principal de Xcode, se mostrarán las configuraciones del proyecto; escoger la sección de targets.

4. En la sección general de targets; la última sección tiene nombre "Linked Frameworks and Libraries", agregar el archivo edk.framework a esta sección.

5. Pasar a la sección Build Settings (seguimos configurando el target), buscar la subsección Search Paths.

6. En la subsección de Search Paths, agregar un nuevo Header Search Path al camino donde se encuentran los headers de las librerias. Nota, la carpeta edk.framework tiene una copia de los headers; por tanto se puede incluir /Library/Frameworks/edk.framework/Headers
