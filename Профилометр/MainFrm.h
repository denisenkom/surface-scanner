//---------------------------------------------------------------------------

#ifndef MainFrmH
#define MainFrmH
//---------------------------------------------------------------------------
#include <ActnList.hpp>
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <StdCtrls.hpp>
#include <ToolWin.hpp>
#include "ScanData.h"

//---------------------------------------------------------------------------
/*class MyInput : public Streams::Input {
private:
	int pos;
	int end;
	char* _buffer;

public:
	MyInput();
	virtual unsigned int readBytes(unsigned char bytes[], unsigned int len);
	void setBuffer(const AnsiString& str);
}; */

//---------------------------------------------------------------------------
/*class MyOutput : public Streams::Output {
public:
	virtual void writeBytes(const unsigned char bytes[], unsigned int len);
}; */

/*class MyPrompt : public Prompt {
public:
	virtual void setPrompt(char* prompt);
}; */

class ScanDataServer {
private:
	ScanData* _datas[10];
	int _datas_num;
public:
	ScanDataServer();
	void addScanData(ScanData* scan_data);
};

//---------------------------------------------------------------------------
class TMainForm : public TForm
{
friend class ScanProcess;
__published:	// IDE-managed Components
	TStatusBar *StatusBar1;
	TToolBar *ToolBar1;
	TMainMenu *MainMenu1;
	TMenuItem *itemFile;
	TMenuItem *itemExit;
	TMenuItem *itemLoad;
	TMenuItem *itemScan;
	TProgressBar *ProgressBar1;
	TSplitter *Splitter1;
	TToolButton *ToolButton1;
	TToolButton *ToolButton2;
	TMenuItem *itemSave;
	TMenuItem *N6;
	TToolButton *ToolButton4;
	TToolButton *ToolButton3;
	TToolButton *ToolButton5;
	TToolButton *ToolButton6;
	TImageList *ImageList1;
	TActionList *ActionList1;
	TAction *ActionNew;
	TAction *ActionOpen;
	TAction *ActionSave;
	TAction *ActionZoomIn;
	TAction *ActionZoomOut;
	TToolButton *ToolButton7;
	TMenuItem *NNN1;
	TMenuItem *GGG1;
	TActionList *ActionList2;
	TAction *ActionKorrelat;
	TAction *Action3d;
	TMenuItem *N3D1;
	TPanel *Panel1;
	TSplitter *Splitter2;
	TMemo *Memo1;
	TPanel *Panel2;
	TEdit *Edit1;
	TMenuItem *N7;
	TMenuItem *N8;
	TSaveDialog *SaveDialog;
	TOpenDialog *OpenDialog;
	void __fastcall itemExitClick(TObject *Sender);
	void __fastcall ActionNewExecute(TObject *Sender);
	void __fastcall ActionOpenExecute(TObject *Sender);
	void __fastcall ActionSaveExecute(TObject *Sender);
	void __fastcall ActionZoomInExecute(TObject *Sender);
	void __fastcall ActionZoomOutExecute(TObject *Sender);
	void __fastcall ActionKorrelatExecute(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Action3dExecute(TObject *Sender);
	void __fastcall Edit1KeyPress(TObject *Sender, char &Key);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall N8Click(TObject *Sender);
private:	// User declarations
	//ConsoleThread* consoleThread;
	ScanData* _scan_data;
	ScanData* _datas[10];
   ScanDataServer scanDataServer;
	//IProcess* _process;
public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);
	virtual __fastcall ~TMainForm();
	void __fastcall DataAccepted();
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;

//---------------------------------------------------------------------------
#endif
