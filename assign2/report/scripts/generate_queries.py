import sys
import os
import numpy as np
import pandas as pd
import random

def main():
    fastas = [
        "Chlamydia",
        "Coxiella",
        "Caulobacter",
        "Ecoli",
        "Pseudomonas",
    ]
    for fasta in fastas:
        referencePath = '../../data/fasta/' + fasta + '.fasta'
        for length in [32, 64, 96, 128]:
            outputPath = '../../data/query/' + fasta + '.' + str(length) + '.query'
            generate_queries(referencePath, length, 1000, outputPath)

def generate_queries(referencePath, length, num, outputPath):
    reference = ""
    with open(referencePath) as file:
        lines = file.readlines()
        for line in lines:
            if line != "":
                reference += line[:-1]
    # print(reference)
    n = len(reference)
    with open(outputPath, 'w+') as file:
        for i in range(0, num):
            pos = random.randint(0, n - length - 1)
            file.write(">" + str(i) + '\n')
            file.write(reference[pos: pos + length] + '\n')

if __name__ == "__main__":
    pass
    main()
