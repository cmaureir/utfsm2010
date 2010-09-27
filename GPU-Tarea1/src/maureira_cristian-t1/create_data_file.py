#!/usr/bin/env python

import sys

try:
    n = int(sys.argv[1])
except IndexError:
    sys.stdout.write("Usage: %s n > file\n" % sys.argv[0])
    sys.exit(-1)

try:
    import numpy.random
except ImportError:
    sys.stdout.write("You have to install NumPy\n")
    sys.exit(-2)

x = numpy.random.random_sample(n).astype('float32')
x.tofile(sys.stdout)
