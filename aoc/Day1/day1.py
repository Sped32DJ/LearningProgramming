# A yes, day 1, lets see how this goes :)

# How many calories each elf is carrying
# food is important
Elfne   =   [1000, 2000, 3000]   # = 6000
Elfwo   =   [4000]               # = 4000
Elfree  =   [5000, 6000]         # = 11000
Elfour  =   [7000, 8000, 9000]   # = 24000
Elfive  =   [10000]              # = 10000

sum(Elfne)
sum(Elfwo)
sum(Elfree)
sum(Elfour)
sum(Elfive)

print("lol")
print("ignore above, that is useless")
print("The real resolution is down here :)")

# How I solved it lol (Yes, I used vim macros/sed/python)
# curl https://adventofcode.com/2022/day/1/input >> input.txt
# vim, recorded macro (editing input.txt)
#    0j bckspc +
#$ sed 's/++/\n/g' test.txt >> workable.py
# This only works because there is double ++ for every white space XD

# 0i print ( esc A ) esc 0 j i
#$ python3 workable.txt >> numbers.py
# 0ji esc bckspc , space
# Then, I wrote real code in numbers.py, and got my solution after running it!
