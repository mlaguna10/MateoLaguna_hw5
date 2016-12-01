animaciones.py : coeficientes.dat
	python animaciones.py

coeficientes.dat : a.out
	./a.out > coeficientes.dat

a.out : sismo.c
	gcc sismo.c -lm 

clean:
	rm -f a.out coeficientes.dat grafica.pdf
