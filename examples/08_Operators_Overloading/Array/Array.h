#pragma once

#ifndef ARRAY_H
#define ARRAY_H

class Array
{
	public:
		explicit Array(size_t cap = 32);

		Array(const Array& other);
		Array& operator=(const Array&);

		Array(Array&& other) noexcept;
		~Array() noexcept;

		Array& operator += (int elem);
		Array& operator += (const Array& other);

		int& operator[] (size_t index);
		const int& operator[] (size_t index) const;

		int& at(size_t index);
		const int& at(size_t index) const;

		int operator()(int elem) const;
		Array operator()(size_t start, size_t end) const;

		size_t size() const { return this->used; }

		class Iterator
		{
			friend class Array;

		public:
			Iterator& operator++();
			Iterator operator++(int);

			bool operator==(const Iterator& other) const;
			bool operator!=(const Iterator& other) const;

			int operator*() const;
			int& operator*();

		private:
			Iterator(int* pos) : position{ pos } {};
		
		private:
			int* position;
		};

		Iterator begin();
		Iterator end();

	private:
		void append(int elem);

	private:
		const size_t allocated;
		size_t used;
		int* data;
};

#endif // !ARRAY_H
