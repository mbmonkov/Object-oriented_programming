#pragma once

#ifndef STRING_H
#define STRING_H

class String
{
public:
	String(const char* = "");

	String(const String& other);
	String& operator=(const String& other);

	String(String&& other) noexcept;
	String& operator=(String&& other) noexcept;

	~String() noexcept;

	char& at(size_t index);
	const char& at(size_t index) const;

	size_t length() const;

	bool empty() const { return data[0] == '\0'; }

	void print() const;

private:
	static bool isValid(const char*);

private:
	char* data;
};

#endif // !STRING_H

