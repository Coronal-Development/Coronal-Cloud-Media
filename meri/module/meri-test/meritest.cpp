#include <Windows.h>
#include <iostream>
typedef void(*RegisterMeri)();
typedef void(*EncodeFrame)();
typedef void(*UnRegisterMeri)();

RegisterMeri start = nullptr;
EncodeFrame encode = nullptr;
UnRegisterMeri stop = nullptr;
int main()
{
    auto dll = LoadLibrary("meri.dll");
    auto rr = GetLastError();
    if (dll != NULL)
    {
        std::cout << "!!!!!!!!!!!!!" << std::endl;
    }
    start = (RegisterMeri)GetProcAddress(dll, "RegisterMeri");
    encode = (EncodeFrame)GetProcAddress(dll, "EncodeFrame");
    stop = (UnRegisterMeri)GetProcAddress(dll, "UnRegisterMeri");
    start();
    return 0;
}


