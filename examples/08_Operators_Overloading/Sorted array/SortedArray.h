#pragma once

#ifndef ARRAY_H
#define ARRAY_H

class SortedArray
{
	public:
		explicit SortedArray(size_t cap = 32);

		SortedArray(const SortedArray& other);
		SortedArray& operator=(const SortedArray&);

		SortedArray(SortedArray&& other) noexcept;
		~SortedArray() noexcept;

		SortedArray& operator += (int elem);
		SortedArray& operator += (const SortedArray& other);

		class Proxy
		{
			friend class SortedArray;

		public:
			operator int();
			Proxy& operator=(int);

		private:
			Proxy(SortedArray& owner, size_t index)
				: owner{ owner }, currentIndex{ index }
			{}

		private:
			SortedArray& owner;
			size_t currentIndex;
		};

		Proxy operator[] (size_t index);
		const int& operator[] (size_t index) const;

		Proxy at(size_t index);
		const int& at(size_t index) const;

		int operator()(int elem) const;
		SortedArray operator()(size_t start, size_t end) const;

		size_t size() const { return this->used; }

		class Iterator
		{
			friend class SortedArray;

		public:
			Iterator& operator++();
			Iterator operator++(int);

			bool operator==(const Iterator& other) const;
			bool operator!=(const Iterator& other) const;

			int operator*() const;
			// може сортирането да се развали
			int& operator*();

		private:
			Iterator(int* pos) : position{ pos } {};
		
		private:
			int* position;
		};

		Iterator begin();
		Iterator end();

	private:
		void add(int elem);

		void shiftRight(int elem, size_t pos);
		void shiftLeft(int elem, size_t pos);

	private:
		const size_t allocated;
		size_t used;
		int* data;
};

#endif // !ARRAY_H
