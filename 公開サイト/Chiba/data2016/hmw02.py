import bz2
import numpy as np
import matplotlib.pyplot as plt

count, value = np.loadtxt('../count2tbb_v103/vis.01', unpack = True)

fb = '201605100300.vis.01.fld.geoss.bz2'
fg = '201605100300.vis.02.fld.geoss.bz2'
fr = '201605100300.ext.01.fld.geoss.bz2'
bfb = np.frombuffer(bz2.BZ2File(fb).read())
bfb = (bfb.reshape(3000, 2, 3000, 2).mean(-1).mean(1) + 0.5).astype('u2')
bfg = np.frombuffer(bz2.BZ2File(fg).read())
bfg = (bfg.reshape(3000, 2, 3000, 2).mean(-1).mean(1) + 0.5).astype('u2')
bfr = np.frombuffer(bz2.BZ2File(fr).read())
bfr = (bfr.reshape(3000, 4, 3000, 4).mean(-1).mean(1) + 0.5).astype('u2')

vb = value[bfb]
vg = value[bfg]
vr = value[bfr]

plt.imshow(vr, cmap = 'gray', extent=(85, 205, -60, 60), interpolation = 'none')
plt.colorbar()
plt.show()