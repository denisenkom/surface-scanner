//---------------------------------------------------------------------------

#include <vcl.h>
#include <string>
#pragma hdrstop

#include "ScanData.h"
#include "uScanningForm.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TScanningForm *ScanningForm;

//---------------------------------------------------------------------------
__fastcall TScanningForm::TScanningForm(TComponent* Owner)
	: TForm(Owner), progress(0)
{
}
//---------------------------------------------------------------------------
void __fastcall TScanningForm::ButtonCancelClick(TObject *Sender) {
	//CancelScan();
}
//---------------------------------------------------------------------------
void __fastcall TScanningForm::Timer1Timer(TObject *Sender)
{
   if (progress)
      Process->Position = *progress;
}
//---------------------------------------------------------------------------

