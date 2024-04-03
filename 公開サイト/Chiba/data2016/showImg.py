import bz2
import numpy as np
import matplotlib.pyplot as plt

count,value = np.loadtxt('../count2tbb_v103/vis.01', unpack = True)

fn = '201605100300.vis.01.fld.geoss.bz2'
ddn = np.frombuffer(bz2.BZ2File(fn).read(), dtype='>u2')
ddn.shape
# (144000000,)

ddn = ddn.reshape(12000,12000)
vb = value[ddn]
plt.imshow(vb, cmap = 'gray', extent=(85, 205, -60, 60), interpolation='none')
plt.colorbar()
plt.show()