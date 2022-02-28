# bit-algorithms

![Actions](https://github.com/bkille/TheBitLibrary/actions/workflows/main.yml/badge.svg)

An exploratory implementation of bit overloads of the C++ standard algorithms.

## Description
While [bit iterators](https://github.com/vreverdy/bit) are currently being proposed and reviewed by the ISO C++ Standards Committee, this repository is intended for practical use of bit containers and algorithms based on bit iterators. Primarily, this repository acts as an efficient replacement of `std::vector<bool>`. It provides implementations of many of the functions in `<algorithms>` optimized for containers of bits, in addition to providing a `bitvector` class, which has the same interface as `std::vector<bool>`.

Many of the implementations in `include/bit-algorithms` come from some of my previous work [here](https://github.com/vreverdy/bit-algorithms), however that repository is also somewhat frozen, as it is tied to the ISO C++ Standards Committee proposal as well. In addition, it contains many overloads that are likely less practical (like forward lists of bits). 

## Example
```
#include <iostream>
#include "bit-iterator/bit.hpp"
#include "bit-algorithms/bit_algorithm.hpp"
#include "bit-containers/bitvector.hpp"


int main() {
    bit::bit_vector<unsigned char> bv1 {"01001010010"};
    std::cout << bv1 << std::endl;
    return 0;
}

// Will output
// 01001010 010
```


## Performance Benchmarks
I used Google's [benchmark](https://github.com/google/benchmark) library for computing benchmarks. Each benchmark is formatted as `{bit, std}::function` (size) [(alignment-tags)].

* `bit` is for this library, `std` is the standard library operating on the infamous `vector<bool>`. 
* (size) denotes the size of the container in bits. `small = 1 << 4`, `large = 1 << 16`
* (alignment-tags) refers to the memory alignment of the bit-iterators. `U` means the iterator does not fall on a word boundary, `R` means the iterator is placed at random, and `A` means the iterator is aligned with a word boundary.

For example, `bit::rotate (large) (ARA)` refers to our library's implementation of the `rotate` algorithm operating on a container of 32768 bits, where `first` and `last` are aligned but `n_first` is selected at random.

```
Run on (64 X 2300 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x32)
  L1 Instruction 32 KiB (x32)
  L2 Unified 1024 KiB (x32)
  L3 Unified 22528 KiB (x2)
Load Average: 0.41, 0.67, 0.73
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
--------------------------------------------------------------------
Benchmark                          Time             CPU   Iterations
--------------------------------------------------------------------
bit::shift_left (small) (UU)        3.77 ns         3.77 ns    185649261
std::shift_left (small)             45.6 ns         45.6 ns     15359502
bit::shift_left (large) (AA)         254 ns          254 ns      2760779
std::shift_left (large)           195023 ns       195021 ns         3590
bit::shift_right (small) (UU)       3.77 ns         3.77 ns    185654156
std::shift_right (small)            34.6 ns         34.6 ns     20218713
bit::shift_right (large) (AA)        240 ns          240 ns      2921340
std::shift_right (large)          131946 ns       131946 ns         5294
bit::reverse (small) (UU)           8.87 ns         8.87 ns     78851173
std::reverse (small)                39.1 ns         39.1 ns     17922588
bit::reverse (large) (AA)            962 ns          962 ns       727702
std::reverse (large)              246764 ns       246770 ns         2844
bit::rotate (small) (ARA)           6.76 ns         6.76 ns    105597804
std::rotate (small)                 71.5 ns         71.5 ns      8798226
bit::rotate (large) (ARA)           7577 ns         7577 ns        93948
std::rotate (large)               505214 ns       505212 ns         1383
bit::count (small) (AA)             1.16 ns         1.16 ns    603331880
std::count (small)                  17.9 ns         17.9 ns     39219825
bit::count (large) (AA)              664 ns          664 ns      1054400
std::count (large)                 72859 ns        72860 ns         9610
```

| Benchmark | Size  | Speedup |
|-----------|-------|---------|
| shift     | small | 10.6x   |
| shift     | large | 662x    |
| reverse   | small | 4.4x    |
| reverse   | large | 258x    |
| rotate    | small | 9.7x    |
| rotate    | large | 66.7x   |
| count     | small | 15.4x   |
| count     | large | 110x    |


## Structure
The structure of the repository is the following:
* **`bit-algorithms`**: main project directory
    * **`bin`**: all compiled executable files, including tests and benchmarks
    * **`build`**: temporary files generated by the compilation process, including tests and benchmarks
    * **`config`**: configuration files
    * **`data`**: data files, inputs and outputs
      * **`input`**: input files
      * **`output`**: output files
    * **`doc`**: all documents on the projects including papers, standardization documents, documentation and tutorials
        * **`papers`**: 
            * **`pdf`**: pdf files of technical and scientific papers
            * **`src`**: source files of technical and scientific papers
               * **`figures`**: figures to be included in documents
               * **`packages`**: additional latex packages
        * **`wg21`**: standardization documents for the ISO WG21 standards committee
            * **`html`**: html files of standardization documents
            * **`pdf`**: pdf files of standardization documents
            * **`src`**: source files of standardization documents
               * **`figures`**: figures to be included in documents
               * **`packages`**: additional latex packages
    * **`ext`**:
        * **`bit`**: a local copy of the bit library
        * **`cplusplus`**: a local copy of the required files from the C++ standard
    * **`include`**: main directory, containing the implementation of all the bit algorithms as header files
    * **`lib`**: library files, if any
    * **`src`**: source files including examples, tests, and benchmarks
        * **`benchmarks`**: benchmarking utilities
        * **`examples`**: examples of use of bit algorithms
        * **`manager`**: project manager to automatically generate algorithms files
        * **`tests`**: unit tests for the algorithms
    * `LICENSE`: information on the licensing terms of the project
    * `make.sh`: main makefile to compile different components of the project
    * `README.md`: this file, with the main basic documentation
    
## Style
Every source file follows a strict layout. If you are a contributor please make sure you follow this common style.
* C++ files
    * Indentation: 4 spaces
    * Line width: 80 characters
    * Separators: every file is divided in parts, these parts being delimited by separators
        * Separator styles:
            * 1: `// ========================================================================== //`
            * 2: `/* ************************************************************************** */`
            * 3: `// -------------------------------------------------------------------------- //`
        * Separator styles description:
            * 1: general purpose
            * 2: declarations and types, classes, structures
            * 3: implementation
        * Each section begins with a separator and a title
        * The title is in capital letters, centered, with a white space before and after, without underscores
        * Each section ends with a separator
        * Sections are separated by 3 lines
    * Class members: class members are grouped together
        * Each group corresponds to a category of members (eg: `Types`, `Lifecycle`, `Access`, `Operators`...)
        * In the class definition, each group starts with a comment with the name of the group
        * Each group specifies the class access modifier (eg: public, protected, private)
        * Groups related to implementation details are marked by `Implementation details`
        * The separator titles should specify the path of the group they correspond to:
            * `CLASS NAME: GROUP NAME`, `
            * `CLASS NAME: IMPLEMENTATION DETAILS: GROUP NAME`
    * Every file starts with the following information:
        * `// =============================== FILE NAME ================================ //`
        * `// Project:         The Experimental Bit Algorithms Library`
        * `// Name:            file_name.hpp`
        * `// Description:     1 line description of the file`
        * `// Creator:         Vincent Reverdy`
        * `// Contributor(s):  Vincent Reverdy [2019]`
        * `//                  ContributorFirstName ContributorLastName [FirstYear-LastYear]`
        * `// License:         BSD 3-Clause License`
        * `// ========================================================================== //`
        * `#ifndef _FILE_NAME_HPP_INCLUDED`
        * `#define _FILE_NAME_HPP_INCLUDED`
        * `// ========================================================================== //`
        * The alignment of the second column is 20
    * Every file is followed by a preamble, typically for file inclusion:
        * `// ================================ PREAMBLE ================================ //`
        * `// C++ standard library`
        * `#include <something>` (if any)
        * `// Project sources`
        * `#include "something.hpp` (if any)
        * `// Third-party libraries`
        * `#include "ext/something.hpp` (if any)
        * `// Miscellaneous`
        * `#define something` (if any)
        * `namespace something {` (if any)
        * `// ========================================================================== //`
    * Every file ends with:
        * `// ========================================================================== //`
        * `} // namespace something` (if any)
        * `#endif // _FILE_NAME_HPP_INCLUDED`
        * `// ========================================================================== //`
        
        
    
    


    



