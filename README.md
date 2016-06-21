# km-std
A drop-in replacement for the C++ STL for kernel mode Windows drivers. The goal is to have implementations for things like the standard algorithms that don't require memory allocations or exceptions, and for implementations of type traits and other compile-time related headers. Full implementation of the STL is a non-goal.

## Unique Considerations
* Paged vs. non-paged memory
* Similarly, passive vs. dispatch level
* Exceptions

Lack of exceptions automatically disqualifies some STL from being included, primarily collections like std::vector.

## Supported APIs

| Header     | API          | Supported |
| ---------- | ------------ | --------: |
| \<utility> | std::move    |         ✓ |
|            | std::forward |         ✓ |