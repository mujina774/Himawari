import bz2
import numpy as np
import matplotlib.pyplot as plt

count, value = np.loadtxt('../count2tbb_v103/vis.01', unpack = True)

fn = '201605100300.ext.01.fld.geoss.bz2'
dbuf = bz2.BZ2File(fn).read()
ddn = np.frombuffer(dbuf, dtype='>u2')
ddn.shape
(576000000,)
data = (ddn.reshape(12000, 2, 12000, 2).mean(-1).mean(1) + 0.5).astype('u2')

plt.imshow(data, cmap = 'gray', vmin = 100, vmax=500, extent=(85, 205, -60, 60), interpolation = 'none')
plt.colorbar()
plt.show()

plt.imshow(data, cmap = 'gray', extent=(85, 205, -60, 60), interpolation = 'none')
plt.colorbar()
plt.show()

data.shape
(12000, 12000)
dv = value[data]
plt.imshow(dv, cmap = 'gray', extent=(85, 205, -60, 60), interpolation = 'none')


dv = (dv.reshape(6000, 2, 6000, 2).mean(-1).mean(1)+0.5).astype('u2')
plt.imshow(dv, cmap = 'gray', extent=(85, 205, -60, 60), interpolation = 'none')
plt.colorbar()
plt.show()