#!/usr/bin/env python
# -*- coding: utf-8 -*-

#         012345678901234
parrot = "Norwegian Blue"
letters = "abcdefghijklmnopqrstuvwsyz"

print(parrot[0:6]) # Norweg
print(parrot[-14:-8])

print( )
print(parrot[-4:-2])    #Bl
print(parrot[-4:12])    #Bl
print(parrot[-4:12])    #BL

print(letters[-4:12])    #BL

print(parrot[0:6:2]) #slice starts at 0 and goes to 6 in steps of 2 (every other word)
print(parrot[0:6:3])

number = "9,223;372:036 854,775;807"
seperators = number[1::4] # 3rd colon shows stop value (skip value)
print(seperators)

values = " ".join(char if char not in seperators else " " for char in number).split()
print([int(val) for val in values])

