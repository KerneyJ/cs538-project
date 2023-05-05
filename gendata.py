#!/bin/python3
import random
import argparse

parser = argparse.ArgumentParser(
                    prog='gendata.py',
                    description='Generate random data for combinatorics project')
parser.add_argument('students', metavar='STUDENTS', type=int,
                    help='number of students')
parser.add_argument('classes', metavar='CLASSES', type=int,
                    help='number of classes')
parser.add_argument('capacity', metavar='CAPACITY', type=int,
                    help='number of students a class can fit')
args = parser.parse_args()

# Students can pick at most 5 classes
# Rows are students columns are classes
T = args.classes * args.capacity
costs = [[0 for __ in range(args.classes)] for _ in range(args.students)]
cap = [[0 for __ in range(args.classes)] for _ in range(args.students)]

for s in range(args.students):
    rankings = random.sample(range(args.classes), 5)
    for i, r in enumerate(rankings):
        costs[s][r] = i+1

with open(f"classes{args.classes}_students{args.students}_capacity{args.capacity}.data", "w") as f:
    lines = [f"{T}\n"]
    for s in range(args.students):
        line = ""
        for c in range(args.classes):
            line += str(costs[s][c]) + ","
        line = line[:len(line)-1]
        line += "\n"
        lines.append(line)
    f.writelines(lines)
