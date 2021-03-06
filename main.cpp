#include <cstdio>
#include <array>
#include <algorithm>
#include <set>
#include <unordered_set>
#include "cths.h"

#define DATA 2, 899, 3, 135, 777, 523, 139, 782, 272, 274, 277, 21, 411, 29, 158, 418,\
	292, 293, 300, 46, 303, 308, 442, 61, 200, 203, 81, 594, 344, 218, 861, 93, 864, 480,\
	227, 740, 869, 486, 359, 744, 504, 623, 497, 241, 628, 374, 247, 120, 250, 126

template <>
constexpr size_t cths_hash<int>(const int& i, size_t idx) {
	return i ^ idx;
}

bool foo_empty(int) {
	return false;
}

bool foo_cths(int i) {
	return cths<5, int, DATA>(i);
}

std::set<int> set {DATA};
bool foo_set(int i) {
	return set.contains(i);
}

std::unordered_set<int> uset {DATA};
bool foo_uset(int i) {
	return uset.contains(i);
}

bool foo_array(int i) {
	constexpr static std::array arr {DATA};
	return std::find(arr.begin(), arr.end(), i) != arr.end();
}

long gettime() {
	timespec t;
	clock_gettime(0, &t);
	return t.tv_sec * long(1e9) + t.tv_nsec;
}

void benchmark(bool(*foo)(int), const char s[]) {
	constexpr size_t times = 1e8;
	static_assert(times % 4 == 0);
	long t = gettime();
	for (size_t i = 0; i < times; i += 4) {
		foo(i + 0);
		foo(i + 1);
		foo(i + 2);
		foo(i + 3);
	}
	t = gettime() - t;
	printf("%gns\t%s\n", (double)t / times, s);
}

#define BENCHMARK(foo) benchmark(foo, #foo)

int main() {
	BENCHMARK(foo_empty);
	BENCHMARK(foo_cths);
	BENCHMARK(foo_set);
	BENCHMARK(foo_uset);
	BENCHMARK(foo_array);
}
