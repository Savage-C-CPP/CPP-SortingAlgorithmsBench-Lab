import itertools
import random

def random_gen(low, high):
    while True:
        yield random.randrange(low, high)


def gen_n_numbers(filepath, n, unique = False):

  gen = random_gen(0, 1000000)
  items = set()
  for x in itertools.takewhile(lambda x: len(items) < n, gen):
      items.add(x)


  with open(filepath, 'w') as f:
    for item in items:
      f.write(str(item) + '\n')


gen_n_numbers('./not_sorted/40k_unique.txt', 40000, True)
