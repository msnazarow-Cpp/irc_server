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
	A a;
	D d(a);
	return 0;
}

