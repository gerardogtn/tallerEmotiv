# Facial Expression Logger

El facialExpressionLogger es un ejemplo simple que obtiene datos de expresiones
faciales de un dispositivo Emotiv e imprime en consola los datos obtenidos. Estos
datos son: estaParpadeando, estaGuiñandoIzquierdo, estaGuiñandoDerecho,
estanOjosAbiertos, estanOjosCerrados, poderSorpresa, poderFruncirCeño,
poderSonrisa, poderDientesApretados.

## Variables de 'poder'
Las variables de poder representan el grado de certeza de que un usuario de Emotiv
este realizando una accion. Se puede pensar en ellos como una probabilidad; por
ejemplo, el poderSonrisa es un valor entre 0 y 1 que representa que tan probable
es que el usuario este sonriendo. Es importante hacer notar que el Emotiv Engine,
solo puede detectar entre sorpresa xor ceñoFruncido y sonrisa xor dientesApretados.
Esto quiere decir que si el emotiv detecta un gesto de sorpresa, no detectará un
gesto de ceño fruncido y viceversa.

## Notas del código.

Se necesitan dos tipos de variables básicas: EmoEngineEventHandle y EmoStateHandle.
El EmoEngineEventHandle obtiene el evento recibido por el Emotiv Engine (por
    ello, se utiliza para *filtrar* por el tipo de evento que te interesa). Por
otro lado el EmoStateHandle obtiene información de un tipo de evento en particular,
y te regresa (a ti como programador) los datos de dicho evento.
