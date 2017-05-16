Este programa funciona de la siguiente manera:

1. Se ejecuta como sigue: 
	"sudo ./p5 config.txt"

	Donde debe ejecutarse como administrador pues el montar en RAM no es accesible 
	para el usuario normal. 

	"p5" es el nombre del ejecutable.

	"config.txt" es el nombre del archivo de configuracion que contiene el path completo
	a los directorios "fuente" y "destino". Este tiene el siguiente formato:
		/home/path/a/fuente
		/home/path/a/destino

2. Una vez corriendo el programa, este monta en "destino" el sist. de archivos de "fuente" y 
   copia sus contenidos. El programa se queda latente hasta que el usuario termine de trabajar 
   sobre "destino" y presione <enter>. Una vez hecho esto, el programa sobreescribe los archivos
   que se modificaron en "destino" a la carpeta "fuente". Tras realizar esta accion, se desmonta 
   el sist. de archivos previamente montado sobre "destino" y se termina la ejecucion. 


Equipo: 

- Mauricio Esquivel Reyes
- Andres Lopez Martinez
- Ulises Manuel Cardenas
