//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#include <string>
#pragma hdrstop

#include "Plot.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TfrmPlot::TfrmPlot(TComponent* Owner, const double _datax[], const double _datay[], int _len, std::string _caption)
	: TForm(Owner),
   scalex(1), scaley(1), len(_len),
   datax(new double[_len]), datay(new double[_len])
{
   for (int i = 0; i < len; i++) {
      datax[i] = _datax[i];
   	datay[i] = _datay[i];
      if (_datax[i] > maxx)
      	maxx = _datax[i];
      if (_datax[i] < minx)
      	minx = _datax[i];
      if (_datay[i] < miny)
      	miny = _datay[i];
      if (_datay[i] > maxy)
      	maxy = _datay[i];
   }
   Caption = AnsiString(_caption.c_str());
}
//---------------------------------------------------------------------------
__fastcall TfrmPlot::~TfrmPlot()
{
	delete [] datax;
   delete [] datay;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPlot::FormPaint(TObject *Sender)
{
	int ofsx=5, ofsy=10, height = 200;
   double logx = 0.5;
   int i;
   // draw ox
   Canvas->Pen->Color = clBlack;
   Canvas->MoveTo(ofsx+(int)floor(minx*scalex), height-ofsy);
   Canvas->LineTo(ofsx+(int)floor(maxx*scalex), height-ofsy);
   double acc(0);
   int logs;
   logs = (int)((maxx-minx)/logx);
   for (i = 1; i <= logs; i++, acc+=logx) {
   	Canvas->MoveTo(ofsx+(int)floor(acc*scalex), height-ofsy-2);
      Canvas->LineTo(ofsx+(int)floor(acc*scalex), height-ofsy+2);
   }
   // draw oy
   Canvas->MoveTo(ofsx, height-ofsy-(int)floor(miny*scaley));
   Canvas->LineTo(ofsx, height-ofsy-(int)floor(maxy*scaley));
   // draw plot
   Canvas->Pen->Color = clRed;
   Canvas->MoveTo(ofsx+(int)floor(datax[0]*scalex), height-ofsy-(int)floor(datay[0]*scaley*3/4));
   for (i = 1; i < len; i++)
		Canvas->LineTo(ofsx+(int)floor(datax[i]*scalex), height-ofsy-(int)floor(datay[i]*scaley*3/4));
}
//---------------------------------------------------------------------------
void __fastcall TfrmPlot::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree;		
}
//---------------------------------------------------------------------------
void TfrmPlot::setScaleX(double _scalex)
{
	scalex = _scalex;
   Repaint();
}
//---------------------------------------------------------------------------
void TfrmPlot::setScaleY(double _scaley)
{
	scaley = _scaley;
   Repaint();
}
