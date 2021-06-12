import itertools
import random

def random_gen(low, high):
    while True:
        yield random.randrange(low, high)


def gen_n_rand_nums(filepath, n, min, max, sorted=False, descending=False):
    items = []
    for i in range(0, n):
        items.append(random.randint(min, max))

    if sorted:
        items.sort(reverse=descending)

    with open(filepath, 'w') as f:
        for item in items:
            f.write(str(item) + '\n')


def gen_n_unique_rand_nums(filepath, n, min, max, sorted=False, descending=False):
    gen = random_gen(min, max)
    items = set()

    for x in itertools.takewhile(lambda x: len(items) < n, gen):
        items.add(x)

    items = list(items)
    if sorted:
        items.sort(reverse=descending)

    with open(filepath, 'w') as f:
        for item in items:
            f.write(str(item) + '\n')


# gen_n_unique_rand_nums('./not_sorted/test_unique.txt', 10, 0, 200, True, True)
# gen_n_rand_nums('./not_sorted/test_sorted.txt', 10, 0, 200, True, False)
