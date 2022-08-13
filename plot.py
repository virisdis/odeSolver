# --------------------------------------------------

import numpy as np

from mpl_toolkits.mplot3d import axes3d
import matplotlib.pyplot as plt

# --------------------------------------------------

def loadplot(filename):
  data = np.loadtxt(filename, delimiter=' ', dtype=float)

  t = []
  x = []
  y = []
  z = []

  l = len(data)-1

  while(l+1):
    t.append(data[l][0])
    x.append(data[l][1])
    y.append(data[l][2])
    z.append(data[l][3])
    l = l-1
  
  fig = plt.figure(figsize = (12, 8))
 
  ax1 = fig.add_subplot(2, 1, 1, projection ='3d')
  ax1.title.set_text(filename)
  ax1.set_zlabel("f(t)", fontsize = 15, fontweight ='bold')
  ax1.plot3D(x, y, z, 'black')
  
  ax2 = fig.add_subplot(2, 3, 4)
  ax2.set_xlabel("x(t)", fontsize = 15, fontweight ='bold')
  ax2.plot(t, x, 'red')
  
  ax3 = fig.add_subplot(2, 3, 5)
  ax3.set_xlabel("y(t)", fontsize = 15, fontweight ='bold')
  ax3.plot(t, y, 'blue')
  
  ax4 = fig.add_subplot(2, 3, 6)
  ax4.set_xlabel("z(t)", fontsize = 15, fontweight ='bold')
  ax4.plot(t, z, 'green')
  
  plt.show()
  
# --------------------------------------------------

loadplot('result_eu_ex.txt')
loadplot('result_eu_im.txt')
loadplot('result_rk4_co.txt')
loadplot('result_rk4_ad.txt')

# --------------------------------------------------
