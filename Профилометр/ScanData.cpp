//---------------------------------------------------------------------------

#include <vcl.h>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <mmsystem.h>
#pragma hdrstop

#include "ScanData.h"
#include "Driver.h"
#include "log.h"
#include "MainFrm.h"
#include "uScanningForm.h"
#include "ScanParFrm.h"

#pragma package(smart_init)

//---------------------------------------------------------------------------
ScanData::ScanData(int wsteps, double wstep, int lsteps, double lstep) :
   _wsteps(wsteps),
   _wstep(wstep),
   _lsteps(lsteps),
   _lstep(lstep),
   _data(new double[wsteps*lsteps]),
   _views_num(0)
{
	if (wsteps < 0) throw Exception("Число шагов должно быть >0");
	if (lsteps < 0) throw Exception("Число шагов должно быть >0");
}

ScanData::ScanData(std::string filename)
: _views_num(0)
{
	std::ifstream file(filename.c_str());
   if (!file)
   	throw std::runtime_error("Неудалость открыть файл: " + filename);
   file >> _wsteps;
   file >> _wstep;
   file >> _lsteps;
   file >> _lstep;
	_data = new double[_wsteps*_lsteps];
   if (!_data)
   	throw std::runtime_error("Недостаточно памяти для выделения массива данных под файл.");
   for (int i = 0; i < _wsteps; i++)
   	for (int j = 0; j < _lsteps; j++)
      	file >> _data[i*_lsteps+j];
}

ScanData::~ScanData() {
	delete[] _data;
}

void ScanData::Save(std::string filename) {
	std::ofstream file(filename.c_str());
   if (!file)
   	throw std::runtime_error("Неудалось открыть файл для записи: " + filename);
   file << _wsteps << '\n';
   file << _wstep << '\n';
   file << _lsteps << '\n';
   file << _lstep << '\n';
   if (!_data)
   	throw std::runtime_error("Нет данных для сохранения в файле");
   for (int i = 0; i < _wsteps; i++) {
   	for (int j = 0; j < _lsteps; j++)
      	file << _data[i*_lsteps+j] << '\t';
      file << '\n';
   }
}

int ScanData::getWSteps() {
	return _wsteps;
}

double ScanData::getWStep() {
	return _wstep;
}

int ScanData::getLSteps() {
	return _lsteps;
}

double ScanData::getLStep() {
	return _lstep;
}

double& ScanData::Mass(int w, int l) {
	if (w < 0 || w >= _wsteps || l < 0 || l >= _lsteps)
		throw Exception(AnsiString("Неправильное значение индекса: w=") + w + ", l=" + l);
	return _data[w*_lsteps + l];
}

void ScanData::updateViews() {
	for (int i = 0; i < _views_num; i++)
		_views[i]->update();
}

void ScanData::addView(ScanDataView* view) {
	if (_views_num == 10) return;
	_views[_views_num++] = view;
	view->setData(this);
}

class ScanProcess : public TThread {
   double length, width;
   unsigned lsteps, wsteps;
public:
   volatile bool cancel;
   volatile int progress;
	__fastcall ScanProcess(double length, unsigned lsteps, double width, unsigned wsteps)
      : TThread(false), length(length), lsteps(lsteps), width(width), wsteps(wsteps), cancel(false)
   {
   }
   virtual void __fastcall Execute();
};

void __fastcall ScanProcess::Execute()
{
   if (Terminated) return;
   try
   {
      log("Начало сканирования поверхности...");
      ScanningForm->progress = &progress;
      double wstep = width/wsteps, lstep = length/lsteps;
   	ScanData* scan_data = new ScanData(wsteps, wstep, lsteps, lstep);
      DisplacePlate(-GetPlatePosition());  // Возвращаем столик в исходное положение
   	for (unsigned w = 0; w < wsteps; w++)
      {
         if (cancel)
            throw Exception("Операция была отменена пользователем.");
         DWORD start_time = timeGetTime();
	   	PushButton(start_scan_btn);
         std::vector<double> profile(lsteps);
         ReadADC(profile);
         for (unsigned i = 0; i < lsteps; i++)
            scan_data->Mass(w, i) = profile[i];
	   	progress = w*100/wsteps;
		   PushButton(stop_scan_btn);
   		PushButton(reverse_btn);
         Sleep(timeGetTime() - start_time + 500);  // подождать пока инструмент
                                                   // вернется в исходную позицию
	   	DisplacePlate(wstep);
   	}
      MainForm->_scan_data = scan_data;
      Synchronize(MainForm->DataAccepted);
      log("Сканирование завершено.");
   }
   catch (Exception& ex) {
      log(("Ошибка сканирования: " + ex.Message).c_str());
      Application->ShowException(&ex);
   }
 	ScanningForm->Visible = false;
   ScanningForm->progress = 0;
   //delete this;
}

void ActionScan()
{
	if (frmScanParam->ShowModal() != 1) {
		return;
	}

	double len = frmScanParam->Edit1->Text.ToDouble();
	double lstep = frmScanParam->Edit3->Text.ToDouble();
	double wid = frmScanParam->Edit2->Text.ToDouble();
	double wstep = frmScanParam->Edit4->Text.ToDouble();
	int lsteps = (int)len/lstep;
	int wsteps = (int)wid/wstep;
	ScanningForm->Visible = true;
	new ScanProcess(len, lsteps, wid, wsteps);
}
