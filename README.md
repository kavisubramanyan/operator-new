# Operator New
Practicing my understanding of the `new` operator in C++. We'll see how this goes...

# Roadmap

### PHASE 0: SETUP
[ ] Create repo with src/ and tests/   
[ ] Define Block header (size, free flag)   
[ ] Stub functions: allocate(), deallocate(), dump()   
[ ] dump() prints "empty arena"

### PHASE 1: FIXED BUFFER, FIXED BLOCKS
[ ] Use std::array<byte, N> as arena   
[ ] Divide arena into equal chunks (e.g. 64B each)   
[ ] Keep free list as simple stack   
[ ] allocate() pops from list   
[ ] deallocate() pushes back to list   
[ ] Test: allocate/free multiple blocks   
[ ] Test: over-allocate should fail   

### PHASE 2: VARIABLE-SIZE BLOCKS

[ ] Support arbitrary sizes   
[ ] Layout: [Header][Payload][Header][Payload]...   
[ ] Single free block at start   
[ ] allocate() scans for first free block of exact size   
[ ] deallocate() marks block free   
[ ] Test: allocate/free 128B, 512B, 4KB   

### PHASE 3: SPLITTING

[ ] If block is larger than request, split into two blocks   
[ ] One block marked used, remainder marked free   
[ ] Test: allocate small from large block, leftover is free   
[ ] Test: multiple small allocs from one large block   


### PHASE 4: COALESCING

[ ] Track prev/next pointers in each block   
[ ] On free, merge with neighbors if they are free   
[ ] Test: free adjacent blocks → merged into one   
[ ] Test: free all → single large free block again   


### PHASE 5: EXPLICIT FREE LIST

[ ] Maintain linked list of free blocks   
[ ] allocate() unlinks from free list   
[ ] deallocate() pushes onto free list   
[ ] Coalescing removes neighbor from list   
[ ] Test: allocations use free list, not full scan   


### PHASE 6: OS-BACKED ARENA

[ ] Replace fixed buffer with mmap() segments   
[ ] Keep list of all mapped segments   
[ ] If no free block, map new segment and retry   
[ ] Optionally munmap() entire free segment   
[ ] Test: allocate until multiple mmap calls happen   


### PHASE 7: HOOK INTO C++

[ ] Override global operator new/delete   
[ ] Forward to allocate()/deallocate()   
[ ] Test: new int[100] goes through custom allocator   


### PHASE 8: DIAGNOSTICS

[ ] Add magic number in header for corruption checks   
[ ] Track stats: mapped, live, free, block count   
[ ] dump() prints arena + free list   
[ ] Test: double free triggers assert   
[ ] Test: invalid pointer triggers assert   


### PHASE 9: FUZZ TESTING

[ ] Random sequence of alloc/free   
[ ] Maintain set of live pointers   
[ ] Use memset with patterns to check overlap   
[ ] Run under ASan/UBSan   
[ ] Test: long random run without crash   


### PHASE 10: SMALL-OBJECT BINS

[ ] Add bins for small sizes (16, 32, 64, 128, 256B)   
[ ] allocate(): round to bin size, pop from bin   
[ ] If empty, carve page into blocks for that bin   
[ ] deallocate(): push back into bin   
[ ] Test: many small allocs run in O(1)   


### PHASE 11: LARGE ALLOCATIONS

[ ] Define threshold (e.g. >128KB)   
[ ] Large requests go directly to mmap()   
[ ] Free calls munmap()   
[ ] Test: big allocs bypass general heap   


### PHASE 12: THREAD SAFETY

[ ] Add global mutex around allocate/free   
[ ] Later: per-bin locks   
[ ] Optionally: thread-local caches   
[ ] Test: multi-threaded alloc/free without corruption   


### PHASE 13: DEBUG FEATURES

[ ] Optional canaries/guard zones   
[ ] Optional zero-on-free   
[ ] Quarantine freed blocks briefly   
[ ] Test: buffer overflow or use-after-free detected   


### PHASE 14: BENCHMARKS

[ ] Write microbenchmarks: small, mixed, large allocs   
[ ] Compare against malloc   
[ ] Measure ops/sec and latency   
[ ] Test: allocator is stable under stress   


### PHASE 15: POLISH

[ ] Config struct for thresholds + growth size   
[ ] Document all invariants   
[ ] Clean file structure   
[ ] Final README with usage instructions   
