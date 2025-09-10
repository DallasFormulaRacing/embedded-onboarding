# Circular Buffer Library

A simple and modular C library for working with circular buffers (ring buffers).  
Implements enqueue/dequeue, size checks, and wraparound handling.

---

## Features
- Dynamically allocated circular buffer
- Functions for:
  - Initialization and cleanup  
  - Put (enqueue) / Get (dequeue)  
  - Check if buffer is empty or full  
  - Read multiple items at once  
- Lightweight, dependency-free, portable C

---


## Project Structure
```
section-01/circular-buffer-lib/
├── inc/ # Header files (public API, function prototypes)
├── src/ # Source files (implementation of circular buffer functions)
├── tests/ # Unit tests (verifies correctness of functions)
├── Makefile # Build automation
└── README.md # Project documentation
```

---

## Build Instructions
```bash
make        # build the library and tests
make clean  # remove build artifacts
make test   # run unit tests (if defined in Makefile)
make run    # alternative test target


