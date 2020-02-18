f = open('aplusbb.in', 'r').read()
a = int(f.split(" ")[0])
b = int(f.split(" ")[1])

f = open('aplusbb.out', 'w').write(str(a+b*b))
