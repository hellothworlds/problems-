import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import Rbf
#Declaration of variables
lon=[121.39,126.19,130.27,127.42,126.14,125.96,123.15,130.5,129.08,122.74,]
lat=[13.51,12.02,13.11,10.09,15.33,14,10.88,11.18,15.78,15.82,]
val=[1.494,1.934,2.148,9.155,2.221,8.1,2.039,1.916,3.729,7.137,]
#This function calculates the constants for the two dimensional spline it is importaed from scipy.interpolate  
kern = Rbf(lon, lat, val)
lonn=[]
latn=[]
# generates a mesh for the graph
X, Y = np.meshgrid(np.linspace(121,131,50), np.linspace(10,16,70))
for i in range(0,50):
    for j in range(0,70):
        lonn.append(121+i*(131-121)/50)
        latn.append(10+j*(16-10)/70)
#calculates the Z coordinates
zn=kern(X,Y)
print(zn)
lims = dict(cmap='RdBu_r', vmin=1, vmax=10)
#this renders the graph using matplotlib
plt.pcolormesh(X,Y,zn, vmin=1, vmax=10)

plt.colorbar()

plt.title("Interpolated function.")

plt.show()

