//---------------------------------------------------------------------------

#ifndef ScanParFrmH
#define ScanParFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfrmScanParam : public TForm
{
__published:	// IDE-managed Components
  TEdit *Edit1;
  TEdit *Edit2;
  TLabel *Label1;
  TLabel *Label2;
  TGroupBox *GroupBox1;
  TEdit *Edit3;
  TEdit *Edit4;
  TLabel *Label3;
  TLabel *Label4;
  TButton *Button1;
  TButton *Button2;
private:	// User declarations
public:		// User declarations
  __fastcall TfrmScanParam(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmScanParam *frmScanParam;
//---------------------------------------------------------------------------
#endif
