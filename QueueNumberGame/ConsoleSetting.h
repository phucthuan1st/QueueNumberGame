#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>

HANDLE stdInp = GetStdHandle(STD_INPUT_HANDLE);
HANDLE stdOut = GetStdHandle(STD_OUTPUT_HANDLE);

void SetWindowSize(SHORT width, SHORT height);
