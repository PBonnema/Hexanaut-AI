module Z;

import std;
import :B;

//void CA::MyFunc(CB& b)
//{
//    std::cout << "Hello World" << std::endl;
//    b.
//}

void CA::MyFunc(const CB& b) const
{
	std::cout << "Hello World" << std::endl;
	b.MyFunc2();
}
