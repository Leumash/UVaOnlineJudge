#!/usr/bin/python

'''

 Power of Cryptography 

 Background

 Current work in cryptography involves (among other things) large prime numbers and computing powers of numbers modulo functions of these primes. Work in this area has resulted in the practical use of results from number theory and other branches of mathematics once considered to be of only theoretical interest.

 This problem involves the efficient computation of integer roots of numbers.

 The Problem

 Given an integer n >= 1 and an integer p >= 1 you are to write a program that determines p ^ (1/n) , the positive nth root of p. In this problem, given such integers n and p, p will always be of the form k^n for an integer k (this integer is what your program must find).

 The Input

 The input consists of a sequence of integer pairs n and p with each integer on a line by itself. For all such pairs 1 <= n <= 200 , 1 <= p < 10^101 and there exists an integer k, 1 <= k <= 10^9 such that k^n = p .

 The Output

 For each integer pair n and p the value p^(1/n) should be printed, i.e., the number k such that k^n = p.

 Sample Input

 2
 16
 3
 27
 7
 4357186184021382204544

 Sample Output

 4
 3
 1234

'''

import sys
import math

def GetK(n,p):
    return (round(pow(p, 1/n)))

try:
    while True:
        n = int(input())
        p = int(input())
        print (GetK(n,p))
except:
    pass

