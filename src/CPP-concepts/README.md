## Compile
On Mac, first check your compiler with ```g++ --version```. 
If it's `clang`, you need the `-std=c++11` switch for some of the examples.
If it's `GCC`, in addition to that switch, you probably need `-lstdc++` as well,
since it's possible that the linker is actually `GCC` (for C) and not `G++` (for C++).

So, in short:   

With clang:   
```g++ -std=c++11 example.cpp```   

With GCC:   
```gcc -std=c++11 -lstdc++ example.cpp```
