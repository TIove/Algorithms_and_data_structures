f = open('aplusb.in', 'r').read()
a = int(f.split(" ")[0])
b = int(f.split(" ")[1])
f = open('aplusb.out', 'w').write(str(a+b))



