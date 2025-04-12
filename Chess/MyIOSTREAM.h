#ifndef MYIOSTREAM_H
#define MYIOSTREAM_H

#include<string>

using std::string;

namespace MyIOSTREAM
{
	void rewind_buffer();
	void enter();
	void print(string _str);
	void println(string _str);
	void print(char _c);
	void println(char _c);
	void get(string msg, int& _target);
	void wait();
	void clear();
	bool comfirm(string _message);
}

#endif MYIOSTREAM_H