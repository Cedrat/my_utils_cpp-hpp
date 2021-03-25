#ifndef TEST_HPP
# define TEST_HPP

#include <string>

class Test
{
	public : 
		Test(void);
		Test(Test const & src);
		~Test();

		Test	&operator=(Test const & rhs);
};

#endif
