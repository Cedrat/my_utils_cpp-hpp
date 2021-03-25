#include "Test.hpp"

Test::Test(void)
{

}

Test::Test(Test const & src)
{
	*this = src;
}

Test::~Test()
{

}

Test &Test::operator=(Test const & rhs)
{
	this->[...] = rhs.[...]();
	return *this;
}

