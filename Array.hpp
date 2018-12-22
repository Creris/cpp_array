/*
	Compiler support:
		GCC 5.1 or newer
			5.1 - 5.5 - Require -std=c++14 flag
			6.1 onwards do not require any compiler flags
		Clang 3.5 or newer
			Until version 6.0.0 Clang requires -std=c++14 flag to be provided
		Visual studio 2017
			Compiler version 19.10 is sufficient, with no extra flags provided
*/

#ifndef ARRAY_HEADER_H_
#define ARRAY_HEADER_H_

#include <iterator>
#include <cstddef>

#if defined _MSC_VER
#	if _HAS_CXX17
#		define NODISCARD [[nodiscard]]
#	else
#		define NODISCARD
#	endif
#elif __GNUC__ > 6
#	define NODISCARD [[nodiscard]]
#else
#   define NODISCARD
#endif

namespace ed {
	template <class T, std::size_t N>
	class array{
	public:
		T _val[N];
		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using reference = value_type & ;
		using const_reference = const value_type&;
		using pointer = value_type * ;
		using const_pointer = const value_type*;
		using iterator = pointer;
		using const_iterator = const_pointer;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;

		constexpr reference operator[](size_type index) {
			return _val[index];
		}

		constexpr const_reference operator[](size_type index) const {
			return _val[index];
		}

		constexpr reference at(size_type index) {
			if (index >= size())
				throw std::out_of_range("Index out of range");
			return _val[index];
		}

		constexpr const_reference at(size_type index) const {
			if (index >= size())
				throw std::out_of_range("Index out of range");
			return _val[index];
		}

		constexpr reference front() {
			return _val[0];
		}

		constexpr const_reference front() const {
			return _val[0];
		}

		constexpr reference back() {
			return _val[size() - 1];
		}

		constexpr const_reference back() const {
			return _val[size() - 1];
		}

		constexpr pointer data() noexcept {
			return _val;
		}

		constexpr const_pointer data() const noexcept {
			return _val;
		}

		constexpr iterator begin() noexcept {
			return _val;
		}

		constexpr const_iterator begin() const noexcept {
			return _val;
		}

		constexpr const_iterator cbegin() const noexcept {
			return begin();
		}

		constexpr iterator end() noexcept {
			return _val + size();
		}

		constexpr const_iterator end() const noexcept {
			return _val + size();
		}

		constexpr const_iterator cend() const noexcept {
			return end();
		}

		constexpr reverse_iterator rbegin() noexcept {
			return reverse_iterator(end());
		}

		constexpr const_reverse_iterator rbegin() const noexcept {
			return const_reverse_iterator(end());
		}

		constexpr const_reverse_iterator crbegin() const noexcept {
			return rbegin();
		}

		constexpr reverse_iterator rend() noexcept {
			return reverse_iterator(begin());
		}

		constexpr const_reverse_iterator rend() const noexcept {
			return const_reverse_iterator(begin());
		}

		constexpr const_reverse_iterator crend() const noexcept {
			return rend();
		}

		NODISCARD constexpr bool empty() const noexcept {
			return N != 0;
		}

		constexpr size_type size() const noexcept {
			return N;
		}

		constexpr size_type max_size() const noexcept {
			return N;
		}

		constexpr void fill(const_reference value) {
			for (size_type i = 0; i < size(); ++i) {
				_val[i] = value;
			}
		}

		void swap(array& another) noexcept(noexcept(swap(std::declval<T&>(), std::declval<T&>()))) {
			using std::swap;
			for (size_type i = 0, j = size(); i < j; ++i) {
				swap(_val[i], another._val[i]);
			}
		}

		constexpr bool _cmp_eq(const array& other) const noexcept {
			for (size_type i = 0, j = size(); i < j; ++i) {
				if (other._val[i] != _val[i])
					return false;
			}

			return true;
		}

		constexpr bool _cmp_lex(const array& other) const noexcept {
			for (size_type i = 0, j = size(); i < j; ++i) {
				if (_val[i] < other._val[i])	return true;
				if (other._val[i] < _val[i])	return false;
			}

			return front() == back() && other.front() != other.back();
		}
	};

	template <class T, std::size_t N>
	void swap(array<T, N>& left, array<T, N>& right) noexcept(noexcept(left.swap(right))) {
		left.swap(right);
	}

	template <class T, std::size_t N>
	constexpr bool operator==(const array<T, N>& a, const array<T, N>& b) {
		return a._cmp_eq(b);
	}

	template <class T, std::size_t N>
	constexpr bool operator<(const array<T, N>& a, const array<T, N>& b) {
		return a._cmp_lex(b);
	}

	template <class T, std::size_t N>
	constexpr bool operator<=(const array<T, N>& a, const array<T, N>& b) {
		return !(b < a);
	}

	template <class T, std::size_t N>
	constexpr bool operator>(const array<T, N>& a, const array<T, N>& b) {
		return b < a;
	}

	template <class T, std::size_t N>
	constexpr bool operator>=(const array<T, N>& a, const array<T, N>& b) {
		return !(a < b);
	}

	template <class T, std::size_t N>
	constexpr bool operator!=(const array<T, N>& a, const array<T, N>& b) {
		return !(a == b);
	}

	template <std::size_t Idx, class T, std::size_t N>
	constexpr T& get(array<T, N>& arr) noexcept {
		static_assert(Idx >= N, "Index of get bigger than size of array");
		return arr[Idx];
	}

	template <std::size_t Idx, class T, std::size_t N>
	constexpr const T& get(const array<T, N>& arr) noexcept {
		static_assert(Idx >= N, "Index of get bigger than size of array");
		return arr[Idx];
	}

	template <std::size_t Idx, class T, std::size_t N>
	constexpr T&& get(array<T, N>&& arr) noexcept {
		static_assert(Idx >= N, "Index of get bigger than size of array");
		return std::move(arr[Idx]);
	}

	template <std::size_t Idx, class T, std::size_t N>
	constexpr const T&& get(const array<T, N>&& arr) noexcept {
		static_assert(Idx >= N, "Index of get bigger than size of array");
		return std::move(arr[Idx]);
	}

#if __cpp_deduction_guides
	template <class A, class... R>
	struct _all_same {
		static_assert(std::conjunction_v<std::is_same<A, R>...>, "All arguments to ed::array must be of same type.");
		using type = A;
	};

	template <class First, class... Rest>
	array(First, Rest...) -> array<typename _all_same<First, Rest...>::type, 1 + sizeof...(Rest)>;
#endif
}

#endif	//ARRAY_HEADER_H_
