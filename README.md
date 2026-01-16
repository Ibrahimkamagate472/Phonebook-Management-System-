# Project Management System
Designed and implemented a modular phonebook application using a hash table for efficient data storage and retrieval. The 
Phonebook Management System supports insertion, deletion, updating of previous entries, searching, and file preservation 
while handling collisions and lazy deletion. The project was structured across multiple source files to emphasize clean 
architecture, encapsulation, and maintainability. Performance considerations, such as load factor tracking and rehashing, 
were incorporated to ensure scalability as the dataset grows.

## Table of Contents
- [Build With](#build-with)
- [System Desgin](#system-desgin)
  - [Hash Function](#hash-function)
  - [Collision Resolution](#collision-resolution)
  - [Rehashing](#rehashing)
  - [Deletion](#deletion)
- [Executing program](#executing-program)
- [Contact](#contact)
  

## Build With
![C++](https://img.shields.io/badge/C%2B%2B-17-blue?logo=c%2B%2B)

## System Desgin

### Hash Function 

I implemented a custom hash function without using any STL hashing utilities.

#### <ins>Hashing String:</ins>
Designing an efficient string hash required balancing randomness and performance. I chose a custom polynomial hash function that operates on only the first three characters of the string to keep the computation inexpensive.

The hash is computed as:

h = k₂ + 37(k₁ + 37k₀)

- where k₀, k₁, and k₂ represent the ASCII values of the first three characters in the string.

Although hashing strings can be computationally expensive, limiting the input to three characters significantly reduces cost while still providing sufficient dispersion for this application.

Since many English words share the same first 3 characters, there is an increased the likelihood of collisions. To mitigate this, I implemented double hashing as the [collision resolution](#collision-resolution) strategy. This ensures better key distribution across the table and maintains efficient lookup, insertion, and deletion performance even when collisions occur.

### Collision Resolution
I use double hashing for collision resolution to eliminate both primary and secondary clustering, resulting in a more evenly distributed hash table.

The probe sequence is defined as:

index = (hash1 + j * hash2) % capacity

hash1 = hashed_string % capacity

hash2 = R - (hashed_string % R)

- hashed_string is the value produced by the polynomial string hash function.

- R is a prime number that is always less than the table capacity.

- j is the probe count, incremented when the computed index is already occupied.

This approach ensures that each collision follows a unique probe sequence, improving insertion and lookup performance compared to linear or quadratic probing.


### Rehashing
When designing the rehashing logic, I focused on modularity and how a real-world system behaves. In real-life applications, such as a company’s employee directory, the number of entries grows and shrinks over time. To reflect this, the phonebook dynamically resizes to efficiently manage memory and performance.

Because I implemented a custom hash function, I also designed custom rehashing triggers based on the table’s load factor and deletion behavior.

#### <ins>Rehash Up:</ins>
When the load factor exceeds 0.6, the table is rehashed to a larger size.

The new capacity is the next prime number that is at least twice the previous capacity.

The secondary hash value R is also updated to the largest prime number less than the new capacity to maintain good distribution.

#### <ins>Rehash Down:</ins>
When the load factor drops to 0.25, the table is rehashed to reduce wasted space.

The capacity is cut in half and then adjusted to the nearest prime number.

The value of R is recalculated using the same rule: the next prime number less than the new capacity.

#### <ins>Lazy Deletion Rehashing:</ins>
If rehashing is triggered due to an excessive number of lazy-deleted entries, the table is rebuilt without changing the capacity or R. Since the number of active entries has not changed significantly, resizing is unnecessary; rehashing simply cleans the table and restores performance.

This approach ensures the phonebook remains space-efficient, scalable, and performant as entries are added and removed over time.


### Deletion

For deletion, I use lazy deletion. Instead of immediately removing an entry, the program marks the slot with a flag to indicate that the position is no longer active.

This approach preserves the probe sequence used by double hashing, ensuring that searches and insertions continue to function correctly. Slots marked as deleted are skipped during lookup but can be reused during future insertions or cleaned up during rehashing.


## Executing program
The project is built using a custom Makefile and executed through the terminal.
Running 'make' compiles the program, and the generated executable can then be run with './main'.


## Contact
[Email 1](mailto:ibrahim.kamagate.code@gmail.com)
[Email 2](mailto:ibrahim.kamagate472@myhunter.cuny.edu)
