l = [1,2,3,4,5,6]
a = [6,1,4,3,2,5]

b = []

n=0
for i in a:
	for j in l:
		if i == j:
			l.pop(n)
			b.append(n+1)
			n = 0
		n=n+1
	n = 0

print b
