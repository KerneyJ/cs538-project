#!/bin/python3
import random
import argparse

parser = argparse.ArgumentParser(
                    prog='gendata.py',
                    description='Generate random data for combinatorics project')
parser.add_argument('--stud', metavar='STUDENTS', type=int,
                    dest='students', action='store', default=5)
parser.add_argument('--class', metavar='CLASSES', type=int,
                    dest='classes', action='store', default=5)
parser.add_argument('--stud_cap', metavar='STUDENT_CAPACTIY', type=int,
                    dest='scapacity', action='store', default=5)
parser.add_argument('--class_cap', metavar='ClASS_CAPACITY', type=int,
                    dest='ccapacity', action='store', default=1)
args = parser.parse_args()

# Students can pick at most 5 classes
# Rows are students columns are classes
costs = [[0 for __ in range(1 + args.students + args.classes + 1)] for _ in range(1 + args.students + args.classes + 1)]
cap = [[0 for __ in range(1 + args.students + args.classes + 1)] for _ in range(1 + args.students + args.classes + 1)]

# Initialize the capacities of source and sink
for i in range(1, args.students+1):
    cap[0][i] = args.scapacity

for i in range(args.students+1, args.students+args.classes+1):
    cap[i][-1] = args.ccapacity

for s in range(args.students):
    rankings = random.sample(range(args.classes), args.scapacity)
    for i, r in enumerate(rankings):
        costs[1+s][1+args.students+r] = i+1
        cap[1+s][1+args.students+r] = 1

with open(f"classes{args.classes}_students{args.students}_s{args.scapacity}c{args.ccapacity}.data", "w") as f:
    lines = []
    for s in range(len(costs)):
        line = ""
        for c in range(len(costs[s])):
            line += str(costs[s][c]) + ","
        line = line[:len(line)-1]
        line += "\n"
        lines.append(line)
    lines.append("-\n") # delimeter
    for s in range(len(cap)):
        line = ""
        for c in range(len(cap[s])):
            line += str(cap[s][c]) + ","
        line = line[:len(line)-1]
        line += "\n"
        lines.append(line)
    f.writelines(lines)
