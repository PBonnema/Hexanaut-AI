module Z:B;

import std;

void CB::MyFunc2() const
{
    std::cout << "Hello World B" << std::endl;
}


CB::CB(CA* a)
    : a(a)
{
}
