//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#include <string>
#pragma hdrstop

#include "MainFrm.h"
#include "View2dFrm.h"
#include "ScanParFrm.h"
#include "GraphFrm.h"
#include "View3dFrm.h"
#include "Plot.h"
#include "log.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

View2d::View2d(ScanData* scan_data) {
	Application->CreateForm (__classid(TfrmView2d), &_form);
	_form->scan_data = scan_data;
	_form->_view = this;
	scan_data->addView(this);
}

/*View2d::View2d(TForm3* form) {
	_form = form;
	form->view = this;
}*/

void View2d::setData(ScanData* data) {
	_form->scan_data = data;
	data->addView(this);
}

void View2d::update() {
	_form->RefreshField();
}

ScanData* View2d::getData() {
	return _form->scan_data;
}

//---------------------------------------------------------------------------
__fastcall TfrmView2d::TfrmView2d(TComponent* Owner)
  : TForm(Owner),
  scan_data(NULL),
  Scale(8),
  _view(0)
{
}
//---------------------------------------------------------------------------

void __fastcall TfrmView2d::FormClose(TObject *Sender, TCloseAction &Action) {
  if (scan_data != 0) delete scan_data;
  Action = caFree;
}
//---------------------------------------------------------------------------

void TfrmView2d::Load() {
  	if (MainForm->OpenDialog->Execute()) {
   	if (scan_data != NULL)
      	delete scan_data;
      scan_data = new ScanData(MainForm->OpenDialog->FileName.c_str());
   }
}

void TfrmView2d::Save() {
	if (MainForm->SaveDialog->Execute())
  		scan_data->Save(MainForm->SaveDialog->FileName.c_str());
}

void __fastcall TfrmView2d::FormActivate(TObject *Sender) {
	MainForm->Action3d->Enabled = true;
	MainForm->ActionKorrelat->Enabled = true;
	MainForm->ActionSave->Enabled = true;
	MainForm->ActionZoomIn->Enabled = true;
	MainForm->ActionZoomOut->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmView2d::FormDeactivate(TObject *Sender) {
	MainForm->Action3d->Enabled = false;
	MainForm->ActionKorrelat->Enabled = false;
	MainForm->ActionSave->Enabled = false;
	MainForm->ActionZoomIn->Enabled = false;
	MainForm->ActionZoomOut->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmView2d::FormResize(TObject *Sender) {
  RefreshField();
}
//---------------------------------------------------------------------------


void TfrmView2d::ZoomIn() {
	Scale *= 2;
	RefreshField();
}

void TfrmView2d::ZoomOut() {
	Scale /= 2;
	RefreshField();
}

void TfrmView2d::RefreshField() {
	if (scan_data == 0) return;

	double len = scan_data->getLSteps()*scan_data->getLStep();
	double wid = scan_data->getWSteps()*scan_data->getWStep();
	Shape1->Left = (Width - len*Scale)/2;
	Shape1->Top = (Height - wid*Scale)/2;
	Shape1->Width = len*Scale;
	Shape1->Height = wid*Scale;
	Shape1->Visible = true;
}

void __fastcall TfrmView2d::Shape1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y) {
  if (trace.tracing) {
	 Shape1->Canvas->Pen->Mode = pmNot;

	 Shape1->Canvas->MoveTo(startX, startY);
	 Shape1->Canvas->LineTo(oldX, oldY);

	 Shape1->Canvas->MoveTo(startX, startY);
	 Shape1->Canvas->LineTo(X, Y);
	 oldX = X;
	 oldY = Y;
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmView2d::Shape1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y) {
	if (Button == mbLeft) {
		if (trace.valid) {
			Shape1->Canvas->Pen->Mode = pmNot;
			Shape1->Canvas->MoveTo(startX, startY);
			Shape1->Canvas->LineTo(endX, endY);
		}
		trace.tracing = true;
		trace.valid = false;
		startX = X;
		startY = Y;
		oldX = X;
		oldY = Y;
		trace.sx = startX/Scale;
		trace.sy = scan_data->getWSteps()*scan_data->getWStep() - startY/Scale;
		log("Выбор трассы:");
		log("  Начальная точка - (X=%.2f;Y=%.2f)", trace.sx, trace.sy);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmView2d::Shape1MouseUp(TObject *Sender, TMouseButton Button,
		TShiftState Shift, int X, int Y)
{
	if (Button == mbLeft) {
		double wid = scan_data->getWSteps()*scan_data->getWStep();
		endX = X;
		endY = Y;
		trace.tracing = false;
		trace.valid = true;
		trace.ex = endX/Scale;
		trace.ey = wid - endY/Scale;
		log("  Конечная точка - (X=%.2f;Y=%.2f)", trace.ex, trace.ey);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmView2d::Shape1Paint(TObject *Sender) {
  if (Shape1->Visible) {
	 Shape1->Canvas->Pen->Mode = pmCopy;
	 Shape1->Canvas->Rectangle(0, 0, Shape1->Width , Shape1->Height);

	 // рисование сетки
	 double dw = scan_data->getWStep(), dl = scan_data->getLStep();
	 int deltay = dw*Scale;
	 int deltax = dl*Scale;
	 if (!(deltax <= 2 || deltay <= 2))
		for (int y = 0; y < Shape1->Height; y += deltay)
		  for (int x = 0; x < Shape1->Width; x += deltax)
			 Shape1->Canvas->Pixels[x][y] = clBlack;

	 if (trace.valid) {
		Shape1->Canvas->MoveTo(startX, startY);
		Shape1->Canvas->LineTo(endX, endY);
	 }
  }
}
//---------------------------------------------------------------------------

//#include "korrelat.cpp"

void CorrectData(double data[], int len) {
	double sxy=0, sxx = 0;
	double ax = 0, ay = 0;

	{for (int i = 0; i < len; i++) {
		ax += i;
		ay += data[i];
	}}
	ax /= len;
	ay /= len;

	{for (int i = 0; i < len; i++) {
		sxy += (i - ax)*(data[i] - ay);
		sxx += (i - ax)*(i - ax);
	}}

	double a,b;
	a = sxy/sxx;
	b = ay - a*ax;

	{for (int i = 0; i < len; i++) {
		data[i] -= a*i + b;
	}}
}

void getParameters(double data[], int len, int& n0, int& m, int& s) {
	n0 = 0;
	m = 0;
	s = 0;
	for (int i = 0; i < len-1; i++) {
		if ((data[i] < 0 && data[i+1] >= 0) || (data[i] > 0 && data[i+1] <= 0))
			n0++;
		if (i >= 1 && data[i-1] < data[i] && data[i] >= data[i+1])
			m++;
		if (i >= 2 && fabs(data[i] - data[i-1]) > fabs(data[i+1] - data[i]) && fabs(data[i+1] - data[i]) < fabs(data[i+2] - data[i+1]))
			s++;
	}
	log("n0 = %i;m = %i;s = %i", n0, m, s);
}

int getFunctionTypeII(double l, double ls) {
	if ((l >= 0.5 && l < 0.82 && ls >= 0.1)
		|| (l >= 0.82 && l < 1.0 && ls >= 0.1 && -.3*l + .68*ls + .0692 < 0))
	{
		return 1;
	}
	else if (l >= 1.0 && l < 1.5 && ls >= 0.1 && -.3*l + .68*ls + .0692 < 0) {
		return 2;
	}
	else if ((l >= 0.82 && l < 1.15 && -.3*l + .68*ls + .0692 >= 0)
		|| (l >= 1.15 && l < 1.5 && -.3*l + .68*ls + .0692 >= 0 && -.1*l + .36*ls - .0516 < 0))
	{
		return 3;
	}
	else if (l >= 1.15 && l < 1.5 && -.1*l + .36*ls - .0516 >= 0) {
		return 4;
	}
	else {
		log("getFunctionTypeII: Function not exist, l=%f, ls=%f.", l, ls);
		//exit(1);
	}
   return 0;   // disables warning "function should return a value"
}

void CalcParams(int ft, double l, double n0, double& a, double& w) {
	float an, wn;

	switch (ft)
	{
	case 1:
	case 2:
		an = 0.5;
		break;

	case 3:
		an = .5f/l*sqrt(3*l*l + 4) - 1;
		wn = sqrt(3 - sqrt(3*l*l + 4));
		break;

	case 4:
		an = .5f - .25f/l*sqrt(6*l*l - 8);
		wn = sqrt(0.5f/l*sqrt(6*l*l - 8));
		break;

	default:
		log("CalcParams: Wrong function: %i", ft);
		//exit(1);
	}
	a = M_PI_2*n0*n0*an;
	w = M_PI*n0*wn;
}

#include "..\common\pirson.cpp"

double sqr(double x) {
  return x*x;
}

/*void graphData(AnsiString cap, float data[], int num, float length, TColor color) {
  TGraph* frm;
  Application->CreateForm(__classid(TGraph),&frm);
  float* dataX = new float[num];
  for (int i = 0; i < num; i++)
	 dataX[i] = i*length/num;
  frm->AddTrace(dataX, data, num, color);
  frm->scaleX = 1000/length;
  frm->scaleY = 4;
  frm->offsX = 1;
  frm->offsY = 50;
  frm->sizeX = length;
  frm->sizeY = 100;
  frm->Caption = cap;
  frm->Update();
}*/

void TfrmView2d::Korrelat() {
	if (!trace.valid) {
		log("Ошибка: Для корреляционного анализа нужно выбрать трассу.");
		return;
	}

	double *profile, *xx;
	int profilenum;
	int wsteps = scan_data->getWSteps();
	int lsteps = scan_data->getLSteps();
	double dw = scan_data->getWStep();
	double dl = scan_data->getLStep();
	double wid = wsteps*dw;
	double len = lsteps*dl;
	profilenum = wsteps >= lsteps ? wsteps : lsteps;
	profile = new double[profilenum];
   xx = new double[profilenum];
	double profilelength;

	//Shape1->Canvas->Pen->Mode = pmCopy;

	log("Начало корреляционного анализа для выбранной трассы...");

	if (fabs(trace.ex - trace.sx) > fabs(trace.ey - trace.sy)) {
		//по длине
		log("  по длине");
		if (trace.sx > trace.ex) {
			//нормализовать
			double temp;
			temp = trace.ex;
			trace.ex = trace.sx;
			trace.sx = temp;
			temp = trace.ey;
			trace.ey = trace.sy;
			trace.sy = temp;
		}
		double dx, dy, b;
		dx = trace.ex - trace.sx;
		dy = trace.ey - trace.sy;
		//b = trace.sx*dy/dx;
		profilelength = sqrt(sqr((lsteps-1)*dl*dy/dx) + sqr(len));
		for (int l = 0; l < lsteps; l++) {
			double y;
			y = trace.sy + (l*dl - trace.sx)*dy/dx;
			Shape1->Canvas->Pixels[l*dl*Scale][(wid - y)*Scale] = clRed;
			{
				int w = floor(y/dw);
				double dord = scan_data->Mass(w, l) - scan_data->Mass(w + 1, l);
				profile[l] = scan_data->Mass(w, l) + (y - w*dw)*dord/dw;
			}
		}
	}
	else {
		//по ширине
		log("  по ширине");
		if (trace.sy > trace.ey) {
			//нормализовать
			double temp;
			temp = trace.ex;
			trace.ex = trace.sx;
			trace.sx = temp;
			temp = trace.ey;
			trace.ey = trace.sy;
			trace.sy = temp;
		}
		double dx, dy, b;
		dx = trace.ex - trace.sx;
		dy = trace.ey - trace.sy;
		//b = trace.sx*dy/dx;
		profilelength = sqrt(sqr((wsteps-1)*dw*dx/dy) + sqr(wid));
		//profiledelta = fabs(dy/dx);
		for (int w = 0; w < wsteps; w++) {
			double x;
			x = trace.sx + (w*dw - trace.sy)*dx/dy;
			Shape1->Canvas->Pixels[x*Scale][(wid - w*dw)*Scale] = clRed;
			{
				int l = floor(x/dl);
				double dord;
				dord = scan_data->Mass(w, l) - scan_data->Mass(w, l+1);
				profile[w] = scan_data->Mass(w, l) + (x - l*dl)*dord/dl;
			}
		}
	}

   for (int i = 0; i < profilenum; i++)
   	xx[i] = i*profilelength/profilenum;

	//graphData("Профиль", profile, len, profilelength, clBlue);
   TfrmPlot* plot = new TfrmPlot(this, xx, profile, profilenum, "Выбранный профиль");
   plot->setScaleX(10);
   plot->setScaleY(10);
	CorrectData(profile, profilenum);
	//graphData("Скорректированный профиль", profile, len, profilelength, clBlack);
	//tabData();
	/*if (PirsonTest(data, len, 0.05f))
		log("Распределение нормальное.");
	else
		log("Предупреждение: Распределение не удовлетворяет критерию Пирсона!");*/
	int n0, m, s;
	getParameters(profile, profilenum, n0, m, s);
	double l, ls;
	l = n0/m;
	ls = n0/s;
	int ft = getFunctionTypeII(l, ls);
	double a, w;
	CalcParams(ft, l, n0, a, w);

	log("Корреляционная функция: №%i", ft);
	switch (ft)
	{
	case 1:
		log("  1/(1+at^2)");
		break;
	case 2:
		log("  exp(-at^2)");
		break;
	case 3:
		log("  cos(wt)/(1+at^2)");
		break;
	case 4:
		log("  exp(-at^2)*cos(wt)");
		break;
	}
	log("  a = %f;w = %f", a, w);

   delete [] xx;
   delete [] profile;
}

ScanDataView* TfrmView2d::getView() {
	return _view;
}
