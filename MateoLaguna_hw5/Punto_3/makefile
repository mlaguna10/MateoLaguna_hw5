animaciones.py : coeficientes.dat
	python animaciones.py

coeficientes.dat : a.out
	./a.out > coeficientes.dat

a.out : Lotka_Volterra.c
	gcc Lotka_Volterra.c -lm 

clean:
	rm -f a.out coeficientes.dat grafica.pdf
