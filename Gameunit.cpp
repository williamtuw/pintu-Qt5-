#include "Gameunit.h"

Gameunit::Gameunit(QObject *parent)
	: QObject(parent),haspm(true)
{
	
}

Gameunit::~Gameunit()
{
}
void Gameunit::setrc(int i, int j)
{
	r = i;
	c = j;
}
const Gameunit& Gameunit::operator =(const Gameunit& other)
{
	rect = other.rect;
	haspm = other.haspm;
	c = other.c;
	r = other.r;
	return *this;
}