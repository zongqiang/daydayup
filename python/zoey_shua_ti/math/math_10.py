#!/usr/bin/python3
# -*- coding: utf-8 -*-
import os, sys
from random import randrange, randint

target = 0
seeds = []
def get_rand_op1(max):
    # at least 1
    if max < 1:
        max = 1
    
    global seeds
    global target
    # init seeds
    if len(seeds) == 0 or target != max:
        target = max
        seeds = list(range(target))

    # extract one seed randomly
    idx = randrange(0, len(seeds))
    op1 = seeds.pop(idx)
    return op1

def gen_n_of_sum(n, sum):
    for i in range(n):
        op1 = get_rand_op1(sum)
        display = randint(1, 4)
        # @note: use Yu Gothic font to get bigger squre mark
        blank = '▢'
        if display == 1:
            print('{0}－{1}＝{2}'.format(sum, op1, blank))
        elif display == 2:
            print('{0}－{2}＝{1}'.format(sum, op1, blank))
        elif display == 3:
            print('{1}＋{2}＝{0}'.format(sum, op1, blank))
        else:
            print('{2}＋{1}＝{0}'.format(sum, op1, blank))


# Main logic start here
# argument format: count sum count sum ...
if len(sys.argv) == 1:
    args = [5, 4, 5, 5, 10, 6, 10, 7, 20, 8, 20, 9, 20, 10]
else:
    args = sys.argv[1:]

# support multi-set
while len(args) >= 2:
    count = int(args.pop(0))
    sum = int(args.pop(0))
    gen_n_of_sum(count, sum)

