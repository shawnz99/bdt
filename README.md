# BDT
Binary data tool

This is my attempt to create a version of the unix command diff
with some features that diff may or may not have such as: 
  - Combining it with xxd
  - Coloring the different byte
  - Printing both files at once

# Usage/Installation

## Installation
  - Clone repo, run make and put resulting executable in a bin file of your choice

## Usage
  - type `bdt <file1> <file2>`
  - It will output the 16 byte chunk where the difference resides & color the byte of difference
  
TODO:
  - Make the offset the offset byte not the offset line
  - Have it show more information
