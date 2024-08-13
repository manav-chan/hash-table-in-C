# Hash Table (map) in C
## Test
- Run the following command to test the code.
```terminal
./build/test
```
- If changes are made to src, run the following command to compile.
```terminal
gcc -o ../build/test main.c map.c prime.c -lm
```

## Introduction
1. Implemented a map data structure which is an array of key-value pairs (both strng types) using hash table and hashing function.
1. map data structure has the following functions.
    - search(a, k): return the value v associated with key k from the associative array a, or NULL if the key does not exist.
    - insert(a, k, v): store the pair k-v into the associative array a, updates value if finds key already present.
    - delete(a, k): delete the k-v pair associated with k.
1. Implemented Double Hashing for resolving collisions.
1. Map is resized automatically according to the `load` of the map, which is defined as count of elements divided by the total size of map.

## Hash Function
Generic string hashing function
```
function hash(string, a, num_buckets):
    hash = 0
    string_len = length(string)
    for i = 0, 1, ..., string_len:
        hash += (a ** (string_len - (i+1))) * char_code(string[i])
    hash = hash % num_buckets
    return hash
```
This hash function has two steps:

1. Convert the string to a large integer
2. Integer mod m

`a` should be a prime number larger than 128 as we are dealing with ASCII string type for keys.

## Collision Handling
### Double Hashing
The index that should be used after `i` collisions is given by:
```
index = hash_a(string) + i * (hash_b(string) + 1) % num_buckets
```
To prevent hash collisions from repeatedly targeting the same bucket, add 1 to the second hash result to ensure it's never 0.

