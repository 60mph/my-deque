#include <iostream>

template <typename T>
class DEQ {
private:
	const size_t sizeX = 4;
	T** arr;
	size_t sz;
	size_t sizeY;
	size_t fr;
	size_t bc;
public:
	DEQ() : sz(0), sizeY(4), bc(0), fr(0) {
		arr = new T * [sizeY];
		for (size_t i = 0; i < sizeY; ++i) {
			arr[i] = new T[sizeX];
		}
	}
	DEQ(size_t n, const T& value = T()) {
		sizeY = n / 32 + 1;
		for (size_t i = 0; i < sizeY; ++i) {
			arr[i] = new T[sizeX];
			for (size_t j = 0; j < sizeX; ++j) {
				arr[i][j] = value;
			}
		}
	}
	~DEQ() {
		for (size_t i = 0; i < sizeY; ++i) {
			delete arr[i];
		}
		delete arr;
	}

	size_t size() const {
		return sz + bc;
	}

	T& operator[](size_t index) {
		size_t i = index - bc + fr * sizeX;
		size_t pointX = i / sizeX;
		size_t pointY = i % sizeX;
		return arr[pointX][pointY];
	}
	const T& operator[](size_t index) const {
		size_t i = index - bc + fr * sizeX;
		size_t pointX = i / sizeX;
		size_t pointY = i % sizeX;
		return arr[pointX][pointY];
	}

	T& back() {
		size_t i = sz + fr * sizeX - 1;
		size_t pointX = i / sizeX;
		size_t pointY = i % sizeX;
		return arr[pointX][pointY];
	}

	T& back() const {
		size_t i = sz + fr * sizeX - 1;
		size_t pointX = i / sizeX;
		size_t pointY = i % sizeX;
		return arr[pointX][pointY];
	}

	T& front() {
		size_t i = fr * sizeX - bc;
		size_t pointX = i / sizeX;
		size_t pointY = i % sizeX;
		return arr[pointX][pointY];
	}

	T& front() const {
		size_t i = fr * sizeX - bc;
		size_t pointX = i / sizeX;
		size_t pointY = i % sizeX;
		return arr[pointX][pointY];
	}

	bool empty() const {
		return(sz + bc == 0);
	}

	void Print() {
		for (int i = 0; i < sizeY; ++i)
		{
			for (int j = 0; j < sizeX; ++j)
				std::cout << arr[i][j] << "         ";
			std::cout << std::endl;
		}

	}

	void push_back(const T& value) {
		if (sz >= sizeY * sizeX - fr * sizeX) {
			T** newarr = new T * [sizeY * 3];
			for (size_t i = 0; i < sizeY; ++i) {
				newarr[i] = new T[sizeX];
			}
			for (size_t i = sizeY; i < sizeY * 2; ++i) {
				new (newarr + i) T* (arr[i - sizeY]);
			}
			for (size_t i = sizeY * 2; i < sizeY * 3; ++i) {
				newarr[i] = new T[sizeX];
			}
			delete arr;
			fr += sizeY;
			sizeY *= 3;
			arr = newarr;
		}
		arr[sz / sizeX + fr][sz % sizeX] = value;
		sz++;
	}

	void pop_back() {
		sz--;
	}

	void push_front(const T& value = T()) {
		if (fr == 0 || fr - (bc / sizeX) - 1 == 0) {
			T** newarr = new T * [sizeY * 3];
			for (size_t i = 0; i < sizeY; ++i) {
				newarr[i] = new T[sizeX];
			}
			for (size_t i = sizeY; i < sizeY * 2; ++i) {
				new (newarr + i) T* (arr[i - sizeY]);
			}
			for (size_t i = sizeY * 2; i < sizeY * 3; ++i) {
				newarr[i] = new T[sizeX];
			}
			delete arr;
			fr += sizeY;
			sizeY *= 3;
			arr = newarr;

		}
		arr[fr - (bc / sizeX) - 1][sizeX - (bc % sizeX) - 1] = value;
		bc++;
	}
	class Iterator : std::iterator<std::random_access_iterator_tag, T> {
	private:
		T** ptr;
		size_t indexX;
		size_t indexY;
		size_t sizeX = 4;
	public:
		Iterator(T** p, size_t iX, size_t iY) : ptr(p), indexX(iX), indexY(iY) {}
		Iterator& operator++() {
			++indexX;
			if (indexX == sizeX) {
				indexX = 0;
				indexY++;
			}
			return *this;
		}
		Iterator operator++(int) {
			Iterator tmp = *this;
			++indexX;
			if (indexX == sizeX) {
				indexX = 0;
				indexY++;
			}
			return tmp;
		}
		Iterator& operator--() {
			--indexX;
			if (indexX < 0) {
				indexX = sizeX - 1;
				indexY--;
			}
			return *this;
		}
		Iterator operator--(int) {
			Iterator tmp = *this;
			--indexX;
			if (indexX < 0) {
				indexX = sizeX - 1;
				indexY--;
			}
			return tmp;
		}
		T& operator*() const {
			return *(ptr[indexY] + indexX);
		}
		T* operator->() const {
			return (ptr[indexY] + indexX);
		}
		bool operator==(const Iterator& other) const {
			return (indexX == other.indexX) && (ptr == other.ptr) && (indexY == other.indexY);
		}
		bool operator!=(const Iterator& other) const {
			return !(*this == other);
		}
	};
	Iterator begin() {
		return Iterator(arr, sizeX - (bc % sizeX), fr - (bc / sizeX) - 1);
	}
	Iterator end() {
		return Iterator(arr, sz % sizeX, (sz != 0 ? (sz / sizeX + fr) : fr - 1));
	}
	Iterator cbegin() const {
		return Iterator(arr, sizeX - (bc % sizeX), fr - (bc / sizeX) - 1);
	}
	Iterator rbegin() {
		return Iterator(arr, sz != 0 ? (sz % sizeX - 1) : (sizeX - 1), sz != 0 ? (sz / sizeX + fr) : fr - 1);
	}
	Iterator rend() {
		return Iterator(arr, sizeX - (bc % sizeX) - 1, fr - (bc / sizeX) - 1);
	}
};