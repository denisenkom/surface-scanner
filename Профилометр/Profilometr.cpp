//---------------------------------------------------------------------------

#include <vcl.h>
#include <string>
#include <vector>
#include <map>
#pragma hdrstop

#include "Profilometr.h"
#include "ScanData.h"
#include "Driver.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TProfilometrForm *ProfilometrForm;
//extern Profilometr* profilometr;
//extern DModel* device;
//extern WINAPI_RS232_Interface* commport;

//---------------------------------------------------------------------------
__fastcall TProfilometrForm::TProfilometrForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TProfilometrForm::ButtonReadADCClick(TObject *Sender) {
   std::vector<double> vec(1);
   ReadADC(vec);
	EditADC->Text = vec[0];
}

//---------------------------------------------------------------------------
void __fastcall TProfilometrForm::ComboBoxPortChange(TObject *Sender) {
	LPCTSTR port = ComboBoxPort->Text.c_str();
	SetPortName(port);
}
//---------------------------------------------------------------------------
void __fastcall TProfilometrForm::ButtonStartScanClick(TObject *Sender) {
	PushButton(start_scan_btn);
}
//---------------------------------------------------------------------------

void __fastcall TProfilometrForm::ButtonReverseClick(TObject *Sender) {
	PushButton(reverse_btn);
}
//---------------------------------------------------------------------------

void __fastcall TProfilometrForm::ButtonStopClick(TObject *Sender) {
	PushButton(stop_scan_btn);
}
//---------------------------------------------------------------------------


void __fastcall TProfilometrForm::ButtonLengthClick(TObject *Sender) {
	PushButton(set_base_length_btn);
}
//---------------------------------------------------------------------------


void __fastcall TProfilometrForm::ButtonScaleFilterClick(TObject *Sender)
{
   PushButton(filter_scale_btn);
	if (ButtonScaleFilter->Down) {
		ButtonScaleFilter->Caption = "Ф";
	}
	else {
		ButtonScaleFilter->Caption = "У";
	}
}
//---------------------------------------------------------------------------
void __fastcall TProfilometrForm::TabSheet1Show(TObject *Sender)
{
	SDPosEdit->Text = GetPlatePosition();
}
//---------------------------------------------------------------------------
void __fastcall TProfilometrForm::PortModeEditChange(TObject *Sender)
{
   SetPortMode(PortModeEdit->Text.c_str());
}
//---------------------------------------------------------------------------
void __fastcall TProfilometrForm::SDPosEditExit(TObject *Sender)
{
   DisplacePlate(SDPosEdit->Text.ToDouble()-GetPlatePosition());
   SDPosEdit->Text = GetPlatePosition();
}
//---------------------------------------------------------------------------
class button_container : public TObject
{
public:
   button btn;
   button_container(button &btn)
      : btn(btn)
   {
   }
};
//---------------------------------------------------------------------------
void __fastcall TProfilometrForm::ButtonsStringGridSetEditText(TObject *Sender,
      int ACol, int ARow, const AnsiString Value)
{
   buttons[dynamic_cast<button_container*>(ButtonsStringGrid->Objects[0][ARow])->btn.id].code = Value.ToIntDef(0);
}
//---------------------------------------------------------------------------
void __fastcall TProfilometrForm::FormCreate(TObject *Sender)
{
   // инициализация вкладки шагового двигателя
   StepsPerMmEdit->Text = GetSDStepsPerMm();
   SDPosEdit->Text = GetPlatePosition();
   // инициализация вкладки COM порт
   ComboBoxPort->Text = GetPortName();
   PortModeEdit->Text = GetPortMode();
   // инициализация вкладки АЦП
   ADCMultiplierEdit->Text = acp_mult;
   // инициализация таблицы кнопок
   ButtonsStringGrid->Col = 1;
   ButtonsStringGrid->Cells[0][0] = "Клавиша";
   ButtonsStringGrid->Cells[1][0] = "Код";
   ButtonsStringGrid->RowCount = buttons.size() + 1;
   int i = 1;
   for (t_buttons::iterator it = buttons.begin(); it != buttons.end(); it++, i++)
   {
      ButtonsStringGrid->Cells[0][i] = it->second.name.c_str();
      ButtonsStringGrid->Cells[1][i] = "0x" + IntToHex(it->second.code, 2);
      ButtonsStringGrid->Objects[0][i] = new button_container(it->second);
      ButtonsStringGrid->RowHeights[i] = 18;
   }
}
//---------------------------------------------------------------------------


void __fastcall TProfilometrForm::StepsPerMmEditExit(TObject *Sender)
{
   SetSDStepsPerMm(StepsPerMmEdit->Text.ToDouble());
}
//---------------------------------------------------------------------------
void __fastcall TProfilometrForm::EditDIDClick(TObject *Sender)
{
   EditDID->Text = ReadDisplay();
}
//---------------------------------------------------------------------------

void __fastcall TProfilometrForm::RaClick(TObject *Sender)
{
   PushButton(ra_btn);   
}
//---------------------------------------------------------------------------

void __fastcall TProfilometrForm::Button8Click(TObject *Sender)
{
   PushButton(increase_btn);   
}
//---------------------------------------------------------------------------

void __fastcall TProfilometrForm::Button9Click(TObject *Sender)
{
   PushButton(decrease_btn);   
}
//---------------------------------------------------------------------------

void __fastcall TProfilometrForm::ButtonLFClick(TObject *Sender)
{
   PushButton(low_freq_btn);   
}
//---------------------------------------------------------------------------

void __fastcall TProfilometrForm::ButtonHFClick(TObject *Sender)
{
   PushButton(high_freq_btn);   
}
//---------------------------------------------------------------------------

void __fastcall TProfilometrForm::RzClick(TObject *Sender)
{
   PushButton(rz_btn);   
}
//---------------------------------------------------------------------------

void __fastcall TProfilometrForm::RmaxClick(TObject *Sender)
{
   PushButton(rmax_btn);
}
//---------------------------------------------------------------------------

void __fastcall TProfilometrForm::RpClick(TObject *Sender)
{
   PushButton(rp_btn);   
}
//---------------------------------------------------------------------------

void __fastcall TProfilometrForm::SmClick(TObject *Sender)
{
   PushButton(sm_btn);   
}
//---------------------------------------------------------------------------


void __fastcall TProfilometrForm::t5Click(TObject *Sender)
{
   PushButton(t5_btn);   
}
//---------------------------------------------------------------------------

void __fastcall TProfilometrForm::t10Click(TObject *Sender)
{
   PushButton(t10_btn);   
}
//---------------------------------------------------------------------------

void __fastcall TProfilometrForm::t20Click(TObject *Sender)
{
   PushButton(t20_btn);   
}
//---------------------------------------------------------------------------

void __fastcall TProfilometrForm::t30Click(TObject *Sender)
{
   PushButton(t30_btn);   
}
//---------------------------------------------------------------------------

void __fastcall TProfilometrForm::t40Click(TObject *Sender)
{
   PushButton(t40_btn);   
}
//---------------------------------------------------------------------------

void __fastcall TProfilometrForm::t50Click(TObject *Sender)
{
   PushButton(t50_btn);   
}
//---------------------------------------------------------------------------

void __fastcall TProfilometrForm::t60Click(TObject *Sender)
{
   PushButton(t60_btn);   
}
//---------------------------------------------------------------------------

void __fastcall TProfilometrForm::t70Click(TObject *Sender)
{
   PushButton(t70_btn);   
}
//---------------------------------------------------------------------------

void __fastcall TProfilometrForm::t80Click(TObject *Sender)
{
   PushButton(t80_btn);   
}
//---------------------------------------------------------------------------

void __fastcall TProfilometrForm::t90Click(TObject *Sender)
{
   PushButton(t90_btn);   
}
//---------------------------------------------------------------------------

void __fastcall TProfilometrForm::DIDClick(TObject *Sender)
{
   PushButton(display_btn);
}
//---------------------------------------------------------------------------

void __fastcall TProfilometrForm::OnOffClick(TObject *Sender)
{
   PushButton(turn_on_btn);   
}
//---------------------------------------------------------------------------

void __fastcall TProfilometrForm::TestButtonClick(TObject *Sender)
{
   try
   {
      TestProfilom();
      Application->MessageBoxA("Тестирование успешно.", "Профилометр", MB_OK);
   }
   catch (Exception &ex)
   {
      Application->ShowException(&ex);
   }
}
//---------------------------------------------------------------------------
void __fastcall TProfilometrForm::ADCMultiplierEditExit(TObject *Sender)
{
   acp_mult = ADCMultiplierEdit->Text.ToDouble();
}
//---------------------------------------------------------------------------
