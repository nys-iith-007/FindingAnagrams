# Finding Anagrams

C++17 command-line project using a custom hash function and hash table to index dictionary words
by canonical letter signatures. Matching words are returned in lexicographical order.

## Build
`g++ -std=c++17 -O2 src/main.cpp -o anagrams`

## Run
`./anagrams data/words.txt listen`

## Complexity
For a word of length k, signature construction is O(k log k). Dictionary lookup is expected O(1)
average after hashing.
