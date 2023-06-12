# cache_friendly_lru_cache

after inserting 1 and 2        -  1 2   
after accessing 1              -  2 1   
after inserting 3              -  1 3   


considerations:  
1 - When key value pairs are expected to be small let them sit next to each other. using list or deque and pointer chasing will scatter the memory all over and spoil the cache locality. Main bottleneck for latency will be memory access and not logic operations so std::find(vector) is less expensive in my opinion.  
2 - storage provided as template argument should have operator [] defined can be validated with concepts and "constexper if" statements ref repo (https://github.com/trkinvincible/Meta-Prog-Cpp)     


https://godbolt.org/z/oxv7xE7Mf  
