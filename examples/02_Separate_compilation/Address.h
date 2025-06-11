#pragma once
#ifndef ADDRESS_H
#define ADDRESS_H

struct Address
{
	char city[24];
	char street[20];
	unsigned number;
	char entrance;
};

void read(Address& a);
void print(const Address& a);

#endif // ADDRESS_H
