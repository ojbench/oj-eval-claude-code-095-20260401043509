# Problem 095 Solution Summary

## Problem Description
Implement permutation, transposition, and cycle operations in C++ with proper memory management.

## Solution Overview

### Key Components Implemented

1. **Permutation Class**
   - Constructors: identity permutation and from array
   - Copy constructor and assignment operator (Rule of Three)
   - Destructor with proper memory cleanup
   - `apply()`: Apply permutation to an array
   - `operator*`: Compose two permutations (this * other means apply this, then other)
   - `inverse()`: Compute inverse permutation

2. **Transposition Class**
   - Constructors: identity transposition and swap(a, b)
   - `apply()`: Swap two elements in array
   - `toPermutation()`: Convert to permutation representation

3. **Cycle Class**
   - Constructor and destructor with dynamic memory
   - Copy constructor and assignment operator (Rule of Three)
   - `apply()`: Apply cyclic permutation (elements rotate forward)
   - `toPermutation()`: Convert to permutation representation

### Critical Implementation Details

1. **Permutation Application**: `result[i] = original[mapping[i]]`
   
2. **Permutation Composition**: `(p * q)[i] = q[p[i]]`
   - This means: apply p first, then apply q
   
3. **Permutation Inverse**: If `p[j] = i`, then `inv[i] = j`

4. **Cycle Direction**: For cycle {e0, e1, ..., ek}:
   - Mapping: `m[ei] = e(i+1) mod k`
   - Application moves values forward: `pos[ei] ← value[e(i+1)]`

### Memory Management
- Implemented copy constructors and assignment operators for classes with dynamic memory
- Proper cleanup in destructors
- All 10 test points passed including memory management tests

## Submission Results
- **Score**: 100/100
- **Status**: Accepted
- **Attempts Used**: 4/5
- **Time**: ~3.1s across all test cases
- **Memory**: ~46MB for larger test cases

## Key Debugging Steps
1. Initial implementation had shallow copy issues (double free)
2. Fixed with proper copy constructor and assignment operator
3. Corrected permutation multiplication order
4. Fixed cycle apply direction to match toPermutation behavior

