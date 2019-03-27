bed2vcf: Convert a BED file (and a FASTA reference) to a valid VCF file
----------------------------------------------------------------------
Eric T Dawson  
March 2019

## Intro
bed2vcf is a C++ script that convert a BED file into the most basic VCF possible by doing
the following operations:  
- Add a valid header with source, data, spec, etc
- Add the reference base at the position in the bed file to the REF field.
- Add a dummy "N" base to the ALT field.
- Write a valid VCF line for each bed record in the input.

## building
Building bed2vcf should be as easy as:
```
make
```

If this doesn't work, please post an issue [on the github](https://github.com/edawson/bed2vcf).

In the future, we may support brew installation.

## Usage
```
bed2vcf <bed_file> <fasta_file> > my.vcf
```
