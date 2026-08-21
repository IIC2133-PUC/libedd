# LibEDD: Standarized Implementation of Data Structures for IIC2133

## About

LibEDD is a C library containing APIs for every data structure and algorithm used in IIC2133. The main objectives are to standarize
the data structures implementation, focus the development efforts to increase code quality, and to simplify the creation and resolution
of the workshops.

This library is _free software_ (as in freedom), and is published under the _GPLv3_ license. The use any LLM or similar generative
AI tool to develop and/or contribute to the LibEDD project is **strictly prohibited**. The documentation can be found under
the `docs` directory of this repository (currently under development).

## Status

Full documentation comming soon...

### Progress

- [x] Error handling module
- [x] Command messages module
- [x] Singly Linked List
- [x] Doubly Linked List
- [x] Sorting Algorithms (Array, SLL, DLL)
- [x] Heap (Min, Max)
- [ ] BST
- [ ] AVL Tree
- [ ] 2-3 Tree
- [ ] Red-Black Tree
- [ ] B+ Tree
- [ ] Hash Tables
- [ ] Graph

## Commands

### Build tester

```bash
$ make
```

### Run tests for EDDs

For all tests:
```bash
$ make test EDD=*edd*
```

For a single test:
```bash
$ make test EDD=*edd* TEST_NUM=*number*
```

For memory errors/leaks use valgrind (no script/make target yet)

### Build Library - Shared objects (.so) + Header files (.h)

For Linux:

```bash
$ make libedd
```

For Apple devices with an M series processor:

```bash
$ make libedd_apple
```

### To clean outputs

```bash
$ make clean
```
