# DES decrypting with OpenMP

## About The Project
This project has been realized as a mid-term work for the Parallel Computing course at the University of Florence. \
The code implements a DES password decrypter in a sequential version in C++ and a parallel variant through the **OpenMP framework**. \
Using a dictionary taken as input, the *sequential version* applies the classic approach of a brute force algorithm to decode a string encrypted with the [DES algorithm](https://en.wikipedia.org/wiki/Data_Encryption_Standard). \
The *parallel variant* is implemented in a similiar manner but parallelizing the code by means of an approach that divides the data to be processed in chunks based on the number of threads generated. \
The two versions are then compared through two differents testing phases: one on words placed in particular positions of the dataset and one on randomly chosen words. The resulting speeedup were finally calculated and displayed in output. 

Results and other implementation details are available in the [paper](DES_password_decryption_paper.pdf) located in the repo root.

## Prerequisites
To reproduce this project the following libraries are required:
* [OpenMP](https://www.openmp.org)
* [OpenSSL](https://www.openssl.org/)

## Usage
Run ```main.cpp``` and follow the instructions, specifying the number of tests to perform for each phase.
