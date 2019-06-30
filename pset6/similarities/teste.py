def substring(a, n):
	size = len(a)
	list = []
	for i in range(size):
		if len(a[i:n+i]) == n:
			list.append(a[i:n+i])
	return list
	
print(substring('hello',4))