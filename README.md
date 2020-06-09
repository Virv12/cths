# cths
Compile Time HashSet

# Usage
```cpp
// Hash function
template <>
constexpr size_t cths_hash<int>(const int& i, size_t idx) {
	return i ^ idx;
}

bool find_in_set(int i) {
	//          K  TYPE [     VALUES IN THE SET     ]  ELEMENT TO SEARCH
	return cths<5, int, 2, 899, 3, 135, 777, 523, 139>(i);
}
```

# Performance
N: # of elements in the set  
RAM usage: `N*K*sizeof(TYPE) + N`  
Time complexity: `O(1) + O(cths_hash<TYPE>) + O(operator==(TYPE, TYPE))`
