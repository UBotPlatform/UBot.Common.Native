#include <string>
#include "StringBox.h"

void* __stdcall ubotStringBoxNew()
{
    return new std::string();
}

void __stdcall ubotStringBoxDelete(void* x)
{
    delete static_cast<std::string*>(x);
}