import matplotlib.pyplot as p
from pylab import *

block_sizes = [2,4,5,8,10,16,20,25,32,40]
times = [44.009,9.27,6.521,5.139,5.991,4.659,4.499,1.986,2.002,2.087]
cpu = [52.881,52.881,52.881,52.881,52.881,52.881,52.881,52.881,52.881,52.881]

plot1 = p.plot(block_sizes,times,label='...')
plot2 = p.plot(block_sizes,cpu,label='....')

title('Time vs BLOCK_SIZE')
legend((plot1,plot2),('GPU','CPU'),loc='center right')
grid(True)
p.axis([2,40,1,55],0.01)
xlabel('BLOCK_SIZE')
ylabel('Time [s]')
p.show()

