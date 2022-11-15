#!/usr/bin/env python
# -*- coding: utf-8 -*-

letters = "abcdefghijklmnopqrstuvwsyz"

backwards = letters[::-1]
print(backwards)

print(letters[-10:-13:-1]) # qpo
print(letters[16:13:-1]) #qpo
print(letters[4::-1]) # edbca
print(letters[7::-1]) # last 8 letters
print(letters[:-9:-1]) # last 8 letters

print(letters[-4:])
print(letters[-1:])
print(letters[:1])
print(letters[0])
