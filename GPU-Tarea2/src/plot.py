#!/usr/bin/env python
# encoding: utf-8

from __future__ import division
from numpy import *
import scipy.integrate
import pylab

def k(x):
    return .5 + 1.5 / (1 + 50 * x**2)

def f(x):
    xs = [-3.3 + i * 0.7 for i in range(10)]
    return sum(k(x - x0) for x0 in xs) / len(xs)

def g(x):
    return exp(-x/16) * cos(2 * pi * f(x) * x)**2

a, b = -4.0, 4.0
n = 2**22          # número de intervalos
x = linspace(a, b, n + 1).astype(float32)

# compute integral using Simpson's rule
integral = scipy.integrate.simps(g(x), x)
print('{0:.5f}'.format(float(integral)))

# plot the function
pylab.plot(x, g(x))
pylab.show()

