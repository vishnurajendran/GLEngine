#pragma once
#include<string>

#define GLUE(a,b) a##b 
#define ToString(data) (std::to_string(data).c_str())
#define ArrayLength(arr) (int)(sizeof(arr)/sizeof(arr[0]))