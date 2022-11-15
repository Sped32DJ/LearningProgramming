#!/usr/bin/env python3
# -*- coding: utf-8 -*-

for i in range(1, 13):
    print("No. {0:2} squared is {1:<3} and cubed is {2:^4}".format(i, i** 2, i ** 3))

print()

for i in range(1, 13):
    print("No. {0:2} squared is {1:<3} and cubed is {2:^4}".format(i, i ** 2, i **3))

print()

# the 12 under is to show the precision of the value
print("Pi is approximately {0:12}".format(22/7))
print("Pi is approximately {0:12f}".format(22/7))
print("Pi is approximately {0:12.50f}".format(22/7))
print("Pi is approximately {0:52.50f}".format(22/7))
print("Pi is approximately {0:62.50f}".format(22/7))
print("Pi is approximately {0:72.50f}".format(22/7))
print("Pi is approximately {0:<72.54f}".format(22/7))
# the < is to left align the value since it autos to right aligned
# then ^ means middle align
# f is necessary for floating point value
# .50 means how many places the number ends at
# the number after .50 is how many spaces before the value
