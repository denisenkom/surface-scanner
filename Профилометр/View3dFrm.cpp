//---------------------------------------------------------------------------

#include <vcl.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <math.h>
#include <string>
#pragma hdrstop

#include "ScanData.h"
#include "View3dFrm.h"
#include "Plot.h"
#include "log.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#define PI  3.141

View3d::View3d(ScanData* scan_data) {
	Application->CreateForm(__classid(TfrmView3d), &_form);
	_form->_view = this;
	_form->scan_data = scan_data;
	_form->maxdist = scan_data->getLSteps()*scan_data->getLStep()*2;
	_form->dispz = 1;
	scan_data->addView(this);
}

void View3d::setData(ScanData* scan_data) {
	_form->scan_data = scan_data;
	scan_data->addView(this);
}

void View3d::update() {
}

ScanData* View3d::getData() {
	return _form->scan_data;
}

//---------------------------------------------------------------------------
__fastcall TfrmView3d::TfrmView3d(TComponent* Owner)
  : TForm(Owner) {
  rollz = 45;
  maxrollz = 180;
  tilt = 10;
  initialized = false;
  scan_data = 0;
  dispz = .1;
  dist = maxdist;
  _view = 0;
}
//---------------------------------------------------------------------------

void gl_perror(char * msg) {
  //log(msg, );
}

void __fastcall TfrmView3d::FormCreate(TObject *Sender) {
	hdc = GetDC(Handle);
	if (hdc == NULL) {
		log("ERROR: GetDC returned NULL");
		return;
	}
	log("GetDC: OK");

	PIXELFORMATDESCRIPTOR pfd = {0};
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.iLayerType = PFD_MAIN_PLANE;
	int i;
	i = ChoosePixelFormat(hdc, &pfd);
	if (i == 0) {
		log("ERROR: ChoosePixelFormal returned zero");
		return;
	}
	log("OK: ChoosePixelFormat");

	if (!SetPixelFormat(hdc, i, &pfd)) {
		log("ERROR: SetPixelFormat returned false");
		return;
	}
	log("SetPixelFormat: OK");

	hgl = wglCreateContext(hdc);
	if (hgl == NULL) {
		log("ERROR: wglCreateContext returned NULL");
		return;
	}
	log("wglCreateContext: OK");

	if (!wglMakeCurrent(hdc, hgl)) {
		log("ERROR: wglMakeCurrent returned false");
		return;
	}
	log("wglMakeCurrent: OK");

	glEnable(GL_DEPTH_TEST);
   glClearColor(1, 1, 1, 1);
	initialized = true;
}

//---------------------------------------------------------------------------
void __fastcall TfrmView3d::FormDestroy(TObject *Sender) {
	initialized = false;
	if (!wglDeleteContext(hgl)) {
		log("ERROR: wglDeleteContext");
		return;
	}
	log("wglDeleteContext: OK");

	if (!ReleaseDC(Handle, hdc)) {
		log("ERROR: ReleaseDC returned 0");
		return;
	}
	log("ReleaseDC: OK");
}

//---------------------------------------------------------------------------

float trunc(float x) {
	if (x > 0)
		return x;
	else
		return 0.0f;
}

void TfrmView3d::Draw()
{
	if (!initialized || scan_data == 0)
   	return;

	if (scan_data->getWSteps()*scan_data->getLSteps() > 20000) glDisable(GL_DEPTH_TEST);

   glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//log("Drawing");
	gluPerspective(50, 2, 0.1, maxdist*2);
	gluLookAt(dist*sin(rollz/180*PI)*cos(tilt/180*PI),
		dist*cos(rollz/180*PI)*cos(tilt/180*PI),
		0.05+dist*sin(tilt/180*PI), 0, 0, 0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glColor3f(0, 0, 0);
   int w;
	for (w = 0; w < scan_data->getWSteps(); w++)
	{
		glBegin(GL_LINE_STRIP);
		for (int l = 0; l < scan_data->getLSteps(); l++) {
			float col = scan_data->Mass(w, l)*180/dispz;
			glColor3f(trunc(sin((col-90)/180*PI)),trunc(sin((col-0)/180*PI)),trunc(sin((col+90)/180*PI)));
			glVertex3f((w-scan_data->getWSteps()/2)*scan_data->getWStep(),
				(l-scan_data->getLSteps()/2)*scan_data->getLStep(),
				scan_data->Mass(w, l));
		}
		glEnd();
	}

	/*for (w = 0; w <  scan_data->getWSteps(); w++) {
		glBegin(GL_LINE_STRIP);
		float col;
		for (int l = 0; l < scan_data->getLSteps(); l++) {
			col = scan_data->Mass(w, l)*180/dispz;
			glColor3f(trunc(sin((col-90)/180*PI)),trunc(sin((col-0)/180*PI)),trunc(sin((col+90)/180*PI)));
			glVertex3f((w-scan_data->getWSteps()/2)*scan_data->getWStep(),
				(l-scan_data->getLSteps()/2)*scan_data->getLStep(),
				scan_data->Mass(w, l));
		}
		glEnd();
	}*/

   /*glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glEnable(GL_BLEND);

   glBegin(GL_QUADS);
   glColor4f(0, 1, 0, 0.1);
   glVertex3f(-scan_data->getWSteps()/2, -scan_data->getLSteps()/2, 0.5);
   glVertex3f(scan_data->getWSteps()/2, -scan_data->getLSteps()/2, 0.5);
   glVertex3f(scan_data->getWSteps()/2, scan_data->getLSteps()/2, 0.5);
   glVertex3f(-scan_data->getWSteps()/2, scan_data->getLSteps()/2, 0.5);
   glEnd(); */

   glDisable(GL_BLEND);

   glLoadIdentity();
   glOrtho(0, Width, 0, Height, -1, 1);

   glBegin(GL_QUAD_STRIP);
   glColor3f(0, 0, 1);
   glVertex2f(10, 10);
   glVertex2f(20, 10);
   glColor3f(0, 1, 1);
   glVertex2f(10, 30);
   glVertex2f(20, 30);
   glColor3f(0, 1, 0);
   glVertex2f(10, 50);
   glVertex2f(20, 50);
   glColor3f(1, 1, 0);
   glVertex2f(10, 70);
   glVertex2f(20, 70);
   glColor3f(1, 0, 0);
   glVertex2f(10, 90);
   glVertex2f(20, 90);
   glEnd();

   glBegin(GL_LINES);
   glColor3f(0, 0, 1);
   glVertex2f(20, 10);
   glVertex2f(25, 10);
   glColor3f(0, 1, 1);
   glVertex2f(20, 30);
   glVertex2f(25, 30);
   glColor3f(0, 1, 0);
   glVertex2f(20, 50);
   glVertex2f(25, 50);
   glColor3f(1, 1, 0);
   glVertex2f(20, 70);
   glVertex2f(25, 70);
   glColor3f(1, 0, 0);
   glVertex2f(20, 90);
   glVertex2f(25, 90);
   glEnd();

	if (!wglSwapLayerBuffers(hdc, WGL_SWAP_MAIN_PLANE)) {
		log("ERROR: wglSwapLayerBuffers returned false");
		return;
	}
	//log("OK: wglSwapLayerBuffers");
}

void __fastcall TfrmView3d::FormPaint(TObject *Sender)
{
	log("3dFrom PAINT");
	Draw();
}
//---------------------------------------------------------------------------



void __fastcall TfrmView3d::FormMouseMove(TObject *Sender, TShiftState Shift,
		int X, int Y)
{
	if (!Active) return;

	rollz = 1.0*X/Width*180.0;
	//if (Shift.Contains(ssShift))
	{
		dist = (float)Y/Height*maxdist;
	}
//  else
	tilt = 1.0*Y/Height*90.0;
	Draw();
}
//---------------------------------------------------------------------------

void __fastcall TfrmView3d::FormResize(TObject *Sender)
{
	glViewport(4, 4, Width-8, Height-8);
	Draw();
}
//---------------------------------------------------------------------------

void __fastcall TfrmView3d::FormActivate(TObject *Sender)
{
	if (!wglMakeCurrent(hdc, hgl)) {
		log("ERROR: wglMakeCurrent returned false");
		return;
	}
	log("OK: wglMakeCurrent");
}
//---------------------------------------------------------------------------

void __fastcall TfrmView3d::FormClose(TObject *Sender,
      TCloseAction &Action)
{
	Action = caFree;	
}
//---------------------------------------------------------------------------

