# DiskBloom

## Fast Disk Based Bloom Filter

### Research

This high performing bloom filter takes inspiration from the research work by [Biplob Debnath et. al.](https://ieeexplore.ieee.org/document/5961740).

Essentially, Debnath et. al. noted that bloom filter is slow on SSD disks because writing on SSD disks is done in the unit of a whole block, which is usually contains more than 1 disk page (4096 bytes of data). 

The bloom filter algorithm requires mutating single bits at different locations of the disk, so it requires mutating many blocks of data. The mutation of each bit requires rewriting at least 4096 bytes of data, which makes it inefficient. 

Debnath et. al. proposed that we can break a single bloom filter down into many bloom filters--each spanning a contigious region of disk space of around 4096 bytes or 32678 bits. And we match each element with a bloom filter through a top-level hash function. The advantage of this design is that now the bits corresponding to each element are all contained within a couple of pages of data. So updating those bits to 1 would require us to only mutate 1 or 2 blocks of the disk.  

It's fairly straightforward to prove that the error rate of a bunch of bloom filters is essentially equivalent to having a single bloom filter. 

### Implementation

I found Debnath et. al.'s optimization to be effective. In this repository, I implemented the approach they proposed in their paper (they didn't provide an implementation). And I confirmed that using multiple bloom filters is significantly faster than a single one. 

Debnath et. al. also proposed using buffering for further speedup. I implemented a buffer-enabled version of bloom filter under the `buffer` branch. But I do not find it to be worth the overhead when the bloom filter is large. So, the version inside the `main` branch does not have buffering.

I use `fread` to read files. I also considered `mmap` and found that `mmap` (memory mapped file) can some times provide minor speedup. But the performance gain is minor, so I decided to stay with the more solid `fopen`, `fread` framework for file I/O. 

I implemented parallel bloom filter containment checks, and observe several times of speedup resulting from that on my 12 core machine. The parallel code draws on the Parlay library, developed by the lab I worked at for my previous parallel computing projects. I parallelized the hashing computation. 

I thought it would be unwise to parallelize `fread` operations because that would cause the file pointer to jump around all over the disk, and will probably slow things down instead of speeding things up (it would also cause dramatic slow down in hard disk drives because moving the mechanical pointer has high latency). 

I attempted to use `mmap` for parallel reading, but I find that it is not very compatible with C++'s threading system. It seems that it produces some determinacy race condition that causes the bloom filter to return the wrong result slightly more frequent than expected based on theoretical results and the sequential algorithm. It's possible that the race condition arise due to concurrent page faults and the processors trying to concurrently read disk data into the same memory address. I am not really sure. So I only parallelized hashing but not data reading. 

Finally, I provided python library bindings through the `diskbloom.cpython-39-x86_64-linux-gnu.so` file. I use pybind11 for generating the binding. Note that M1 and M2 Mac may not be compatible with pybind11 (at least mine wasn't, I had to hop onto a linux server to generate functionable bindings). 

### Getting Started (Cpp)

All user functions are in `bloom.h` file. Refer to `test_bloom.cpp`, `accuracy_bloom.cpp` (benchmark accuracy), and `benchmark_bloom.cpp` (benchmark performance) for examples about how to use DiskBloom.

To create a bloom filter:
```cpp
Bloom(std::string _filename, std::string _meta_filename, uint64_t _expected_num_elements, double _error_order, uint32_t _block_size = 4096, int64_t _memory_limit = 2*1e9);
```
where `_error_order = -10` means that the program should have a false positive rate less than $10^{-10}$. `_block_size` controls the number of bytes of each individual bloom filter. This constructor will create the bloom filter at `_filename` and a corresponding meta file at `_meta_filename`.

After you have created a bloom filter, you can read it in again by:
```cpp
Bloom(std::string _filename, std::string _meta_filename);
```

To add an element,
```cpp
Bloom* bloom_filter = new Bloom("data/test_bloom.bin", "data/test_bloom.meta");

bloom_filter->add("https://www.daylightreveries.org");
```

To query if an element exists,
```cpp
Bloom* bloom_filter = new Bloom("data/test_bloom.bin", "data/test_bloom.meta");

bloom_filter->contains("https://www.daylightreveries.org");
```

If you have a lot of elements, to query them, use
```cpp
Bloom* bloom_filter = new Bloom("data/test_bloom.bin", "data/test_bloom.meta");

bloom_filter->batchContains({"https://www.daylightreveries.org", "https://www.facebook.com"});
```

Make sure to call `delete bloom_filter` before you finish, or else the update will not be all flushed to disk. 

### Getting Started (Python)

Just put `diskbloom.cpython-39-x86_64-linux-gnu.so` in your project directory. And call `import diskbloom`. All the function calls are the same.

If your architecture is different, you will need to recompile the cmake project and the python `.so` file will be generated. 

### Performance

When the bloom filter permits 10 billion urls, and an error rate of $10^{-10}$, to add 10000 urls takes 189ms. To check 10000 urls take 53ms. And to batch check them take 25ms. 

When the bloom filter is smaller (100 million urls), and an error rate of $10^{-10}$, we can add 1 million urls in 5.8 seconds. We can check them in 4.3 seconds. And batch checking takes 1.6 seconds. 

Notice that this is only about 1 order of magnitude slower than c++'s in-memory hashtable `unordered_set`, which takes 300ms to add 1 million urls and 200ms to check them. 


