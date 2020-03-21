#!/usr/bin/python3
# -*- coding: utf-8 -*-
import os, sys
from random import randrange, randint

def gen_one(sum, op1):
    op2 = sum - op1
    # choose random op1 or op2
    op = [op1, op2][randint(0, 1)]
    # reuse op1 var
    op1 = op
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
    args = [9, 6, 2, 9, 7, 3, 9, 8, 3, 9, 9, 3, 9, 10, 3]
else:
    args = sys.argv[1:]

# support multi-set
while len(args) >= 3:
    count = int(args.pop(0))
    sum = int(args.pop(0))
    op1 = int(args.pop(0))
    for i in range(count):
        gen_one(sum, op1)

