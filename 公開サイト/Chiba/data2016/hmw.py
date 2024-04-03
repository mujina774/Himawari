import bz2
import numpy as np
import matplotlib.pyplot as plt

count, value = np.loadtxt('../count2tbb_v103/vis.01', unpack = True)

fb = '201605100300.vis.01.fld.geoss.bz2'
fg = '201605100300.vis.02.fld.geoss.bz2'
fr = '201605100300.ext.01.fld.geoss.bz2'

bfb = bz2.BZ2File(fb).read()
bfb = (np.frombuffer(bfb, dtype = '>u2').reshape(4, 2, 4, 2).mean(-1).mean(1) + 0.5).astype('u2')

bfg = bz2.BZ2File(fg).read()
dfg = np.frombuffer(bfg, dtype = '>u2')

bfr = bz2.BZ2File(fb).read()
bfr = np.frombuffer(bfr, dtype = '>u2')

