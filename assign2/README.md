## 858D Assignment 2

### Language
I'm using C++

### Resources
#### Libraries
I'm using SDSL for building the suffix array.
I'm using cereal for serializing/deserializing my data structure.
These two libraries are installed to /usr/local on my machine. So make sure you have them installed when running the code on your machine.
Other than these I didn't refer to any existing code.

#### Data
I downloaded 5 reference sequences from NCMI GenBank: Chlamydia (1.1MB), Coxiella (2MB), Caulobacter (4.1MB), Ecoli (4.7MB), Pseudomonas (6.4MB)

### Directory Structure

#### include
Contains header files of suffix_array, utils.

#### src
Source code contains implementations of suffix_array, buildsa, querysa, and evaluations.

#### data
- CMSC858D_S22_Project2_sample: the provided sample files
- fasta: reference files of different sizes downloaded from NCBI genbank
- query: queries of different sizes generated based on corresponding references
- serial: serialized suffix_array binary files build from references above with different preftab sizes.

#### report
- data: performance data generated from evaluate.cpp for report.
- figs: figures that plots performance data.
- scripts: python scripts for generating plots and queries.
- text: report.

#### Makefile
Compile the assignment.

### References
- compact_vector: https://github.com/gmarcais/compact_vector
