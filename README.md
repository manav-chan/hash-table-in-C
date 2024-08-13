# Hash Table (map) in C

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
2. Reduce the size of the integer to a fixed range by taking its remainder mod m
