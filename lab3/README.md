# Hash Hash Hash
In this lab, we make a hash table implementation safe to use concurrently.

## Building
To build, navigate to the lab3 directory and run:
```shell
make
```

## Running
The executable takes two command link arguments: -t changes the number of threads to use (default 4), and -s changes the number of hash table entries to add per thread (default 25,000).
For example, you can run:
```shell
/hash-table-tester -t 8 -s 50000
```
Here is an example of what the output might look like after running the program:
```shell
Generation: 20,316 usec
Hash table base: 53,285 usec
  - 0 missing
Hash table v1: 171,627 usec
  - 0 missing
Hash table v2: 25,352 usec
  - 0 missing
```
The results note how many hash table entries are missing based off of race conditions in the two implementations 

## First Implementation
In the `hash_table_v1_add_entry` function, I added TODO

### Performance
```shell
TODO how to run and results
```
Version 1 is a little slower/faster than the base version. As TODO

## Second Implementation
In the `hash_table_v2_add_entry` function, I TODO

### Performance
```shell
TODO how to run and results
```

TODO more results, speedup measurement, and analysis on v2

## Cleaning up
To clean up the executable and any other binary files created during the build process, run:
```shell
make clean
```