# -*- coding: utf-8 -*-

d2 = [0.0, 1.0, 3.0, 6.0, 9.0, 14.0, 20.0, 24.0, 32.0, 40.0, 46.0, 53.0, 60.0, 67.0, 70.0, 76.0, 76.0, 84.0, 94.0, 99.0, 103.0, 111.0, 115.0, 118.0, 120.0, 121.0, 117.0, 119.0, 124.0, 125.0, 125.0, 124.0, 128.0, 129.0, 129.0, 128.0, 128.0, 130.0, 128.0, 120.0, 126.0, 130.0, 133.0, 135.0, 126.0, 127.0, 125.0, 129.0, 131.0, 139.0, 142.0, 149.0, 144.0, 144.0, 149.0, 147.0, 141.0, 143.0, 143.0, 147.0, 148.0, 146.0, 142.0, 142.0, 147.0, 134.0, 136.0, 132.0, 131.0, 130.0, 135.0, 147.0, 138.0, 142.0, 132.0, 145.0, 140.0, 141.0, 146.0, 141.0, 139.0, 136.0, 133.0, 137.0, 145.0, 140.0, 139.0, 139.0, 144.0, 141.0, 146.0, 151.0, 145.0, 156.0, 157.0, 164.0, 153.0, 146.0, 152.0, 156.0, 160.0, 163.0, 159.0, 169.0, 161.0, 169.0, 167.0, 168.0, 172.0, 176.0, 171.0, 168.0, 173.0, 167.0, 166.0, 167.0, 167.0, 182.0, 182.0, 187.0, 195.0, 192.0, 194.0, 189.0, 182.0, 180.0, 167.0, 180.0, 181.0, 194.0, 198.0, 193.0, 199.0, 188.0, 197.0, 189.0, 192.0, 198.0, 203.0, 206.0, 214.0, 215.0, 219.0, 213.0, 206.0, 208.0, 213.0, 221.0, 219.0, 227.0, 238.0, 244.0, 239.0, 230.0, 242.0, 248.0, 243.0, 243.0, 233.0, 253.0, 249.0, 237.0, 251.0, 249.0, 249.0, 255.0, 251.0, 239.0, 242.0, 244.0, 249.0, 239.0, 242.0, 249.0, 252.0, 242.0, 234.0, 234.0, 227.0, 231.0, 223.0, 215.0, 209.0, 200.0, 209.0, 193.0, 212.0, 215.0, 214.0, 210.0, 221.0, 219.0, 218.0, 212.0, 215.0, 203.0, 189.0, 193.0, 175.0, 182.0, 183.0, 179.0, 177.0, 182.0, 174.0, 188.0, 196.0, 174.0, 168.0, 177.0, 188.0, 196.0, 186.0, 186.0, 183.0, 188.0, 178.0, 211.0, 216.0, 225.0, 228.0, 228.0, 235.0, 222.0, 229.0, 227.0, 224.0, 231.0, 246.0, 256.0, 243.0, 250.0, 243.0, 223.0, 224.0, 215.0, 218.0, 210.0, 215.0, 219.0, 228.0, 217.0, 225.0, 233.0, 228.0, 225.0, 220.0, 225.0, 237.0, 255.0, 259.0, 263.0, 262.0, 261.0, 277.0, 268.0, 274.0, 289.0, 274.0, 287.0, 281.0, 285.0, 278.0, 278.0, 281.0, 281.0, 291.0, 279.0, 278.0, 269.0, 275.0, 278.0, 285.0, 287.0, 290.0, 299.0, 298.0, 296.0, 279.0, 248.0, 245.0, 251.0, 249.0, 229.0, 224.0, 234.0, 220.0, 224.0, 219.0, 209.0, 205.0, 205.0, 200.0, 200.0, 198.0, 195.0, 198.0, 206.0, 193.0, 195.0, 169.0]


import matplotlib.pyplot as p
from pylab import *


m = 300
m_list = []
for i in range(m+1):
    m_list.append(i)

plot1 = p.plot(m_list,d2)
title(u'Distancia entre secuencias vs Número de mutaciones')
grid(True)
p.axis([0,m,0,max(d2)+1],0.01)
xlabel(u'Número de mutaciones')
ylabel('Distancia entre secuencias')
p.show()
