#pragma once
#include <Windows.h>

void SetWindowSize(INT64 width, INT64 height);
void SetScreenBufferSize(INT64 width, INT64 height);
void DisableResizeWindow();
void DisableCtrButton(bool Close, bool Min, bool Max);
void RenderText(char* text, INT64 x, INT64 y, INT64 color);
void clrscr();
INT64 whereX();
INT64 whereY();
void TextColor(INT64 color);
void GotoXY(INT64 x, INT64 y);
void ShowCur(bool CursorVisibility);
void DisableSelection();
void ShowScrollbar(BOOL Show);
