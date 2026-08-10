# LibEDD: Standarized Implementation of Data Structures for IIC2133

## Status

Full documentation comming soon...

### Completion progress

- [x] Error handling module
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

```bash
$ make libedd
```

### Clean outputs

```bash
$ make clean
```
