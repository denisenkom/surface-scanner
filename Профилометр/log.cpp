#include <vcl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#pragma hdrstop

#include "MainFrm.h"

void log(char * fmt, ...) {
	char str[256];
	va_list ap;

	va_start(ap, fmt);
	vsprintf(str,fmt,ap);
	va_end(ap);
	MainForm->Memo1->Lines->Add(str);
}
