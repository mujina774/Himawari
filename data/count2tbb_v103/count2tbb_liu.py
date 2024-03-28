#!/usr/bin/env python
# -----------------------------------------------------------------------------
#  Convert AHI counts to physical variables
#   Coded by A.Hamada, Univ. Toyama
# -----------------------------------------------------------------------------
#  2020/09/16: A.Hamada: NC
# -----------------------------------------------------------------------------

import bz2
import numpy as np
import os
import struct
import sys


# fixed parameters
nlut  = 17000
undef = -999.


# check and get command-line arguments
if len(sys.argv) != 2:
    print('Usage: count2tbb.py <input file; CEReS gridded data>')
    sys.exit(1)


# set and check parameters
fn_in = sys.argv[1]
ss = os.path.basename(fn_in)
isCompressed = True if os.path.splitext(ss)[1][1:] == 'bz2' else False
fn_lut = ss[13:19]
band = fn_lut[0:3]
if band == 'ext':
    nx = 24000
elif band == 'vis':
    nx = 12000
elif band == 'sir' or band == 'tir':
    nx = 6000
else:
    print('ERROR: Unknown band: %s (Input file may be wrong)'%(band))
    sys.exit(1)
if isCompressed:
    fn_out = os.path.splitext(ss)[0]+'.grd'
else:
    fn_out = ss+'.grd'

# print status
print('%16s: %s'%('Input file', fn_in))
print('%16s: %s'%('LUT file', fn_lut))
print('%16s: %s'%('Output file', fn_out))
#print(ss, isCompressed, fn_lut, band, nx, fn_out)


# read look-up table
lut = np.full(nlut, undef)
with open(fn_lut, 'rt') as fp:
    for line in fp:
        lut[int(line.split()[0])] = float(line.split()[1])
print(type(lut))
#print(lut)


# read data
if isCompressed:
    with bz2.open(fn_in, 'rb') as fp:
        count = np.frombuffer(fp.read(), dtype='>u2')
else:
    with open(fn_in, 'rb') as fp:
        count = np.frombuffer(fp.read(), dtype='>u2')
print(type(count), count.shape, count.min(), count.max())
#print(count)


# convert count to physical value
#data = np.full_like(count, undef, dtype=np.float)
#for i in range(count.size):
#    data[i] = lut[count[i]]
data = lut[tuple([count])]
#print(type(data), data.shape, data.min(), data.max())
#print(data)


# output
data.astype('f4').tofile(fn_out)

