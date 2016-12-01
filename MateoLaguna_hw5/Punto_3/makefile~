animaciones.py : coeficientes.dat
	python animaciones.py

coeficientes.dat : a.out
	./a.out > coeficientes.dat

a.out : planetas.c
	gcc planetas.c -lm 

clean:
	rm -f a.out coeficientes.dat grafica.pdf
