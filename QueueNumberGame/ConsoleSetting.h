#pragma once
#include "library.h"

void SetWindowSize(SHORT width, SHORT height);
void SetScreenBufferSize(SHORT width, SHORT height);
void DisableResizeWindow();
void DisableCtrButton(bool Close, bool Min, bool Max);
void RenderText(char* text, int x, int y, int color);
void clrscr();
int whereX();
int whereY();
void TextColor(int color);
