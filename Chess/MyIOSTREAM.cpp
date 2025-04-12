#include<iostream>
#include"MyIOSTREAM.h"

using std::cout;
using std::cin;
using std::endl;

namespace MyIOSTREAM
{
	void enter()
	{
		cout << endl;
	}

	void print(string _str)
	{
		cout << _str;
	}

	void println(string _str)
	{
		cout << _str << endl;
	}

	void print(char _c)
	{
		cout << _c;
	}

	void println(char _c)
	{
		cout << _c << endl;
	}

	void get(string msg, int& _target)
	{
		print(msg + ": ");
		cin >> _target;
		rewind_buffer();
	}

	void rewind_buffer()
	{
		cin.clear();            // �÷��׵��� �ʱ�ȭ �ϰ�
		cin.ignore(100, '\n');  // ���๮�ڰ� ���� �� ���� �����Ѵ�
	}

	void wait()
	{
		//�� ������ ���� ���߿� �ٽ� ����
		system("pause");
	}

	void clear()
	{
		system("cls");
	}

	bool comfirm(string _message)
	{
		int selection = 0;
		println(_message);
		println("1: comfirm");
		println("2: cancel");

		get("Answer", selection);

		switch (selection)
		{
		case 1:
			return true;
		case 2:
			return false;
		}
	}
}
