# Hash Table (map) in C
## Test
- Run the following command to test the code.
```terminal
./build/test
```
- If changes are made to src code, run the following command to compile.
```terminal
gcc -o ../build/test main.c map.c prime.c -lm
```

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
index = hash_a(string) + i * (hash_b(string) + 1) % num_buckets`
```

