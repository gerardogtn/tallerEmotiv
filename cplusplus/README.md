# Ejemplos para programar en C++ usando la API de Emotiv.

## Instrucciones de compilacion.

### Linux
En Linux se tiene que incluir el path al dll que contiene las librerias de
emotiv.

        g++ main.cpp -l../../bin/linux64 -ledk

o para darle un nombre al ejecutable

        g++ main.cpp -o main.o -l../../bin/linux64 -ledk

### Mac OS
Mac OS utiliza un formato llamado framework para manejar las librerias dll, en
este caso se le tiene que dar el path al archivo framework y despues se le tiene
que especificar con la bandera framework el framework a utilizar.

        g++ main.cpp -o main.o -F/Library/Frameworks -framework edk
