#!/usr/bin/python

uglies = [1]

new = []
for i in range(0, 50):
    for ugly in uglies:
        new.append(ugly * 2 ** i)
uglies = new

new = []
for i in range(0,30):
    for ugly in uglies:
        new.append(ugly * 3 ** i)
uglies = new

new = []
for i in range(0,20):
    for ugly in uglies:
        new.append(ugly * 5 ** i)
uglies = new

uglies = sorted(uglies)

print(uglies[1499])
