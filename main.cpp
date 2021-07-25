#include "Channel.h"
#include <iostream>
class A{

};

class B{
	public:
	B(A a){}
};

class C{
	public:
	C(B b){}
};
class D{
	public:
	D(C c){}
};

void kek(C c){}
int main(int argc, char const *argv[])
{
	std::vector<Channel::BanMask> _ban_list;

	_ban_list.push_back((Channel::BanMask){"mask[0]","mask[1]","mask[2]","client.get_nickname()",time(NULL)});
	std::cout << _ban_list[0].time;
	return 0;
}

