//---------------------------------------------------------------------------

#include <vcl.h>
#include <string>
#include <math.h>
#pragma hdrstop

#include "MainFrm.h"
#include "ScanParFrm.h"
#include "View2dFrm.h"
#include "View3dFrm.h"
#include "GraphFrm.h"
#include "Plot.h"
#include "uScanningForm.h"
#include "Profilometr.h"
#include "log.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//extern ScanDataServer* scanDataServer;
//extern Streams::Output* logstream;
//extern Streams::Input* userinput;
//Prompt* prompt;
//extern Profilometr* profilometr;

/*//---------------------------------------------------------------------------
void MyOutput::writeBytes(const unsigned char bytes[], unsigned int len) {
	char accumstr[256];
	for (unsigned int i = 0, j = 0; i < len; i++) {
		if (bytes[i] != '\n' && bytes[i] != '\r')
			accumstr[j++] = bytes[i];
		else {
			if (j == 0) continue;
			accumstr[j] = 0;
			j = 0;
			MainForm->Memo1->Lines->Add(accumstr);
		}
	}
}

//---------------------------------------------------------------------------
MyInput::MyInput() {
	_buffer = new char[1000];
	pos = 0;
	end = 0;
}

unsigned int MyInput::readBytes(unsigned char buf[], unsigned int buflen) {
	if (pos == end) return 0;
	unsigned int ofs;
	for (ofs = pos; pos <= end && pos - ofs < buflen; pos++)
		buf[pos - ofs] = _buffer[pos];
	return pos - ofs;
}

void MyInput::setBuffer(const AnsiString& str) {
	int i;
	for (i = 0; i < str.Length(); i++)
		_buffer[i] = str.operator [](i+1);
	pos = 0;
	end = i - 1;
}

//---------------------------------------------------------------------------

void MyPrompt::setPrompt(char* prompt) {
	AnsiString as(prompt);
	as += " :";
	MainForm->Panel2->Caption = as;
}*/

ScanDataServer::ScanDataServer() {
	_datas_num = 0;
}

void ScanDataServer::addScanData(ScanData* data) {
	if (_datas_num > 10) return;
	_datas[_datas_num++] = data;
}

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
  : TForm(Owner)
{
	//_process = 0;
	//userinput = new MyInput();
	//logstream = new MyOutput();
	//prompt = new MyPrompt();
	//consoleThread = new ConsoleThread(logstream, prompt, userinput, false);
}

__fastcall TMainForm::~TMainForm() {
	//delete consoleThread;
	//delete prompt;
	//delete logstream;
	//delete userinput;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::itemExitClick(TObject *Sender)
{
  //TGraph* frm;
  //Application->CreateForm(__classid(TGraph),&frm);
  int len = 50;
  double* dataX = new double[len];
  double* dataY = new double[len];
  for (int i = 0; i < len; i++)
  	{
   	double x = 2.0*acos(-1)*i/len;
	 	dataX[i] = x;
	 	dataY[i] = sin(x);
  	}
  TfrmPlot* plot = new TfrmPlot(this, dataX, dataY, len, "test plot");
  plot->setScaleX(100);
  plot->setScaleY(100);
  //frm->AddTrace(dataX, dataY, len, clRed);
  //frm->scaleX = 300;
  //frm->scaleY = 300;
  //frm->offsY = 1;
  //frm->Update();
  //Close();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ActionNewExecute(TObject *Sender)
{
   ActionScan();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ActionOpenExecute(TObject *Sender)
{
  	if (MainForm->OpenDialog->Execute()) {
		ScanData* scan_data;
      scan_data = new ScanData(MainForm->OpenDialog->FileName.c_str());
		scanDataServer.addScanData(scan_data);
		View2d* view = new View2d(scan_data);
		view->update();
   }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ActionSaveExecute(TObject *Sender)
{
	if (ActiveMDIChild && ActiveMDIChild->ClassType() == __classid(TfrmView2d))
		((TfrmView2d*)ActiveMDIChild)->Save();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ActionZoomInExecute(TObject *Sender)
{
	if (ActiveMDIChild && ActiveMDIChild->ClassType() == __classid(TfrmView2d))
		((TfrmView2d*)ActiveMDIChild)->ZoomIn();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ActionZoomOutExecute(TObject *Sender)
{
	if (ActiveMDIChild && ActiveMDIChild->ClassType() == __classid(TfrmView2d))
		((TfrmView2d*)ActiveMDIChild)->ZoomOut();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ActionKorrelatExecute(TObject *Sender)
{
	if (ActiveMDIChild && ActiveMDIChild->ClassType() == __classid(TfrmView2d))
		((TfrmView2d*)ActiveMDIChild)->Korrelat();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
	log("Программа запущена");
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Action3dExecute(TObject *Sender)
{
	if (ActiveMDIChild && ActiveMDIChild->ClassType() == __classid(TfrmView2d)) {
		View3d* view3d = new View3d((dynamic_cast<TfrmView2d*>(ActiveMDIChild))->getView()->getData());
		view3d->update();
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Edit1KeyPress(TObject *Sender, char &Key)
{
	//if (Key == 0x0d) {
		//command[strlen(command)-1] = 0;
		//((MyInput*)userinput)->setBuffer(Edit1->Text + "\r\n");
		//Edit1->Clear();
	//}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	//consoleThread->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::DataAccepted()
{
	scanDataServer.addScanData(_scan_data);
	View2d* view = new View2d(_scan_data);
	view->update();

	/*MainForm->ActionSave->Enabled = true;
	MainForm->ActionZoomIn->Enabled = true;
	MainForm->ActionZoomOut->Enabled = true;*/
}

void __fastcall TMainForm::N8Click(TObject *Sender) {
	ProfilometrForm->Visible = true;
}
//---------------------------------------------------------------------------

