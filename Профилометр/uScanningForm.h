//---------------------------------------------------------------------------

#ifndef uScanningFormH
#define uScanningFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TScanningForm : public TForm
{
__published:	// IDE-managed Components
	TProgressBar *Process;
	TProgressBar *SubProcess;
	TButton *ButtonCancel;
   TTimer *Timer1;
	void __fastcall ButtonCancelClick(TObject *Sender);
   void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
public:		// User declarations
   volatile int * progress;
	__fastcall TScanningForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TScanningForm *ScanningForm;
//---------------------------------------------------------------------------
#endif
