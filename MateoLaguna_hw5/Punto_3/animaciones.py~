import numpy as np
import matplotlib.pyplot as plt
import corner 

a = np.loadtxt("coeficientes.dat")

fig = plt.figure()
corner.corner(a, show_titles=True)
plt.savefig("grafica.pdf")
plt.show()
plt.close()
