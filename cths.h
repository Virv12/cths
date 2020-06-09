#include <cstddef>
#include <array>
#include <algorithm>

template <class T>
constexpr size_t cths_hash(const T&, size_t);

template <size_t X, class T, T... t>
[[nodiscard]] bool cths(const T& oth) noexcept {
	constexpr static auto hash_idx = []() -> size_t {
		for (size_t i = 0; true; i++) {
			std::array<bool, sizeof...(t) * X> arr {};
			bool b = true;

			for (auto& x : std::array{ t... }) {
				auto h = cths_hash(x, i) % arr.size();
				b &= !arr[h];
				arr[h] = true;
			}

			if (b) return i;
		}
	} ();

	constexpr static auto arr = [] {
		std::array<T, sizeof...(t) * X> arr {};
		((arr[cths_hash<T>(t, hash_idx)  % arr.size()] = t),...);
		return arr;
	} ();

	constexpr static auto isv = [] {
		std::array<bool, sizeof...(t) * X> arr {};
		((arr[cths_hash<T>(t, hash_idx)  % arr.size()] = true),...);
		return arr;
	} ();

	auto h = cths_hash<T>(oth, hash_idx) % arr.size();
	if constexpr (std::is_trivial_v<T>)
		return isv[h] & (arr[h] == oth);
	else
		return isv[h] && (arr[h] == oth);
}

