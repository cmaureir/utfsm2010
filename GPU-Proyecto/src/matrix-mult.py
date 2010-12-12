from numpy import matrix

#a = matrix([[2,1600,4],[1,1600,5],[2,8,7]])

f = open("1","r")

tmp = 0
a,b = [], []
line = f.readline().split(" ")
for i in range(1600):
	sm = []
	for j in range(1600):
		sm.append(int(line[tmp]))
		tmp = tmp + 1
	a.append(sm)

line = f.readline()
tmp = 0
line = f.readline().split(" ")
for i in range(1600):
	sm = []
	for j in range(1600):
		sm.append(int(line[tmp]))
		tmp = tmp + 1
	b.append(sm)

A = matrix(a)
B = matrix(b)

print A[:1600][0]

#print a
C = A*B
print "===================="
print C[:1600][0]

