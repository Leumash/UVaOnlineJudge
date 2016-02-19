#!/usr/bin/python

import sys

def OrderOfMagnitude(t, a, b):
    return (a - b) * len(str(t))

def ProcessInput(tab):
    t = tab[0]
    a = tab[1]
    b = tab[2]

    val = ""

    if (t == 1):
        # Divide by 0
        val = "is not an integer with less than 100 digits."
    elif (a == b):
        val = "1"
    elif (a < b):
        # Fraction
        val = "is not an integer with less than 100 digits."
    elif (OrderOfMagnitude(t, a, b) >= 1000):
        val = "is not an integer with less than 100 digits."
    else:
        top = (t ** a - 1)
        bottom = (t ** b - 1)
        if (top % bottom != 0):
            val = "is not an integer with less than 100 digits."
        else:
            division = top // bottom
            count = len(str(division))
            if (count >= 100):
                val = "is not an integer with less than 100 digits."
            else:
                val = str(division)

    formula = "(" + str(t) + "^" + str(a) + "-1)/(" + str(t) + "^" + str(b) + "-1)"
    print (formula + ' ' + val)

for line in sys.stdin:
    tab = [int(x) for x in line.split()]
    ProcessInput(tab)

