from random import randint

f15k = open('./not_sorted/15k.txt', 'w')
f40k = open('./not_sorted/40k.txt', 'w')
f80k = open('./not_sorted/80k.txt', 'w')
f150k = open('./not_sorted/150k.txt', 'w')

for i in range(0, 15000):
  f15k.write(str(randint(0, 1000000)) + '\n')

for i in range(0, 40000):
  f40k.write(str(randint(0, 1000000)) + '\n')

for i in range(0, 80000):
  f80k.write(str(randint(0, 1000000)) + '\n')

for i in range(0, 150000):
  f150k.write(str(randint(0, 1000000)) + '\n')

f15k.close()
f40k.close()
f80k.close()
f150k.close()
