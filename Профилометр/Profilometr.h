//---------------------------------------------------------------------------

#ifndef ProfilometrH
#define ProfilometrH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TProfilometrForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TEdit *SDPosEdit;
	TTabSheet *TabSheet2;
	TButton *Ra;
	TButton *Rz;
	TButton *Rmax;
	TButton *Rp;
	TButton *Sm;
	TButton *DID;
	TButton *t5;
	TButton *t10;
	TButton *t20;
	TButton *t30;
	TButton *t40;
	TButton *t50;
	TButton *t60;
	TButton *t70;
	TButton *t80;
	TButton *t90;
	TEdit *EditDID;
	TGroupBox *GroupBox1;
	TButton *ButtonStop;
	TButton *ButtonStartScan;
	TButton *ButtonReverse;
	TGroupBox *GroupBox2;
	TGroupBox *GroupBox3;
	TButton *Button8;
	TButton *Button9;
	TEdit *EditDIDFilter;
   TButton *OnOff;
	TTabSheet *TabSheet3;
	TEdit *EditADC;
	TButton *ButtonReadADC;
	TTabSheet *TabSheet4;
	TComboBox *ComboBoxPort;
	TSpeedButton *ButtonLF;
	TSpeedButton *ButtonHF;
	TSpeedButton *ButtonLength;
	TSpeedButton *ButtonScaleFilter;
   TEdit *PortModeEdit;
   TLabel *Label4;
   TLabel *Label5;
   TTabSheet *TabSheet5;
   TStringGrid *ButtonsStringGrid;
   TLabel *Label2;
   TLabel *Label3;
   TEdit *StepsPerMmEdit;
   TButton *TestButton;
   TLabel *Label6;
   TEdit *ADCMultiplierEdit;
   TLabel *Label7;
	void __fastcall ButtonReadADCClick(TObject *Sender);
	void __fastcall ComboBoxPortChange(TObject *Sender);
	void __fastcall ButtonStartScanClick(TObject *Sender);
	void __fastcall ButtonReverseClick(TObject *Sender);
	void __fastcall ButtonStopClick(TObject *Sender);
	void __fastcall ButtonLengthClick(TObject *Sender);
	void __fastcall ButtonScaleFilterClick(TObject *Sender);
	void __fastcall TabSheet1Show(TObject *Sender);
   void __fastcall PortModeEditChange(TObject *Sender);
   void __fastcall SDPosEditExit(TObject *Sender);
   void __fastcall ButtonsStringGridSetEditText(TObject *Sender, int ACol,
          int ARow, const AnsiString Value);
   void __fastcall FormCreate(TObject *Sender);
   void __fastcall StepsPerMmEditExit(TObject *Sender);
   void __fastcall EditDIDClick(TObject *Sender);
   void __fastcall RaClick(TObject *Sender);
   void __fastcall Button8Click(TObject *Sender);
   void __fastcall Button9Click(TObject *Sender);
   void __fastcall ButtonLFClick(TObject *Sender);
   void __fastcall ButtonHFClick(TObject *Sender);
   void __fastcall RzClick(TObject *Sender);
   void __fastcall RmaxClick(TObject *Sender);
   void __fastcall RpClick(TObject *Sender);
   void __fastcall SmClick(TObject *Sender);
   void __fastcall t5Click(TObject *Sender);
   void __fastcall t10Click(TObject *Sender);
   void __fastcall t20Click(TObject *Sender);
   void __fastcall t30Click(TObject *Sender);
   void __fastcall t40Click(TObject *Sender);
   void __fastcall t50Click(TObject *Sender);
   void __fastcall t60Click(TObject *Sender);
   void __fastcall t70Click(TObject *Sender);
   void __fastcall t80Click(TObject *Sender);
   void __fastcall t90Click(TObject *Sender);
   void __fastcall DIDClick(TObject *Sender);
   void __fastcall OnOffClick(TObject *Sender);
   void __fastcall TestButtonClick(TObject *Sender);
   void __fastcall ADCMultiplierEditExit(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TProfilometrForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TProfilometrForm *ProfilometrForm;
//---------------------------------------------------------------------------
#endif
