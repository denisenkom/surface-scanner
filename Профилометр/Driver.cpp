//---------------------------------------------------------------------------

#include <vcl.h>
#include <string>
#include <map>
#include <vector>
#include <registry.hpp>
#pragma hdrstop

#include "ScanData.h"
#include "Driver.h"
#include "..\common\driver_dll.h"

//---------------------------------------------------------------------------

namespace driver=profilometer_driver_dll;

#pragma package(smart_init)
#pragma link "driver.lib"

double plate_position = 0;
double steps_per_mm = 1000;
double tool_speed = 1;
double acp_mult = 1;

std::map<ebutton, button> buttons;

class DummyInitializer
{
public:
   DummyInitializer()
   {
      // Массив клавиш. Изменения касающиеся структуры, количества клавиш
      // вносятся сюда.
      button _buttons[] = {button(start_scan_btn, "Старт", 0),
         button(stop_scan_btn, "Стоп", 0),
         button(reverse_btn, "Реверс", 0),
         button(set_base_length_btn, "Базовая длина", 0),
         button(high_freq_btn, "ВЧ", 0),
         button(low_freq_btn, "НЧ", 0),
         button(increase_btn, "+", 0),
         button(decrease_btn, "-", 0),
         button(turn_on_btn, "Вкл", 0),
         button(filter_scale_btn, "Увел/фильтр", 0),
         button(ra_btn, "Ra", 0),
         button(rz_btn, "Rz", 0),
         button(rmax_btn, "Rmax", 0),
         button(rp_btn, "Rp", 0),
         button(sm_btn, "Sm", 0),
         button(display_btn, "Дисплей", 0),
         button(t5_btn, "t5", 0),
         button(t10_btn, "t10", 0),
         button(t20_btn, "t20", 0),
         button(t30_btn, "t30", 0),
         button(t40_btn, "t40", 0),
         button(t50_btn, "t50", 0),
         button(t60_btn, "t60", 0),
         button(t70_btn, "t70", 0),
         button(t80_btn, "t80", 0),
         button(t90_btn, "t90", 0)};

      // Загрузка кодов клавиш из реестра
      // Создание словаря клавиш
      TRegistryIniFile *file = new TRegistryIniFile("Software\\profilom");
      for (unsigned i = 0; i < sizeof(_buttons)/sizeof(button); i++)
      {
         _buttons[i].code = file->ReadInteger("BUTTONS", _buttons[i].name.c_str(), 0);
         buttons.insert(t_buttons::value_type(_buttons[i].id, _buttons[i]));
      }

      SetPortName(file->ReadString("PORT", "Name", "COM1").c_str());
      SetPortMode(file->ReadString("PORT", "MODE", "baud=19200 parity=n stop=1").c_str());

      steps_per_mm = file->ReadFloat("SD", "Steps per mm", 1000);
      plate_position = file->ReadFloat("SD", "Position", 0);

      acp_mult = file->ReadFloat("ACP", "Multiplier", 12.0/4096.0);

      delete file;
   }

   ~DummyInitializer()
   {
      TRegistryIniFile *file = new TRegistryIniFile("Software\\profilom");
      for (t_buttons::const_iterator i = buttons.begin(); i != buttons.end(); i++)
      {
         file->WriteInteger("BUTTONS", i->second.name.c_str(), i->second.code);
      }

      file->WriteString("PORT", "Name", GetPortName());
      file->WriteString("PORT", "Mode", GetPortMode());

      file->WriteFloat("SD", "Steps per mm", steps_per_mm);
      file->WriteFloat("SD", "Position", plate_position);

      file->WriteFloat("ACP", "Multiplier", acp_mult);

      delete file;
   }

} DummyInitializer;

void SetPortName(LPCTSTR port)
{
   if (!driver::SelectPort(port))
   {
      TCHAR err[256];
      driver::GetLastError(err, sizeof(err));
      throw Exception(String("Ошибка при выборе имени порта: ") + err);
   }
}

String GetPortName()
{
   TCHAR buf[256];
   if (!driver::GetPortName(buf, sizeof(buf)))
   {
      TCHAR err[256];
      driver::GetLastError(err, sizeof(err));
      throw Exception(String("Ошибка при чтении имени порта: ") + err);
   }
   return String(buf);
}

void SetPortMode(LPCTSTR mode)
{
   if (!driver::SetPortMode(mode))
   {
      TCHAR err[256];
      driver::GetLastError(err, sizeof(err));
      throw Exception(String("Ошибка при изменении режима порта: ") + err);
   }
}

String GetPortMode()
{
   TCHAR buf[256];
   if (!driver::GetPortMode(buf, sizeof(buf)))
   {
      TCHAR err[256];
      driver::GetLastError(err, sizeof(err));
      throw Exception(String("Ошибка при чтении режима порта: ") + err);
   }
   return String(buf);
}

void SetSDStepsPerMm(double value)
{
   steps_per_mm = value;
}

double GetSDStepsPerMm()
{
   return steps_per_mm;
}

void TestProfilom()
{
   if (!driver::Test())
   {
      TCHAR err[256];
      driver::GetLastError(err, sizeof(err));
      throw Exception(String("Ошибка тестировании: ") + err);
   }
}

void ReadADC(std::vector<double> &data)
{
   short svalues[256];
   if (!driver::RequestACP(data.size(), svalues))
   {
      TCHAR err[256];
      driver::GetLastError(err, sizeof(err));
      throw Exception(String("Ошибка при чтении АЦП: ") + err);
   }
   short *si = svalues;
   for (std::vector<double>::iterator di = data.begin(); di != data.end(); si++, di++)
      *di = (*si)*acp_mult;
}

double GetPlatePosition()
{
   return plate_position;
}

void DisplacePlate(double delta)
{
   int steps = delta*steps_per_mm;
   if (!driver::MakeSteps(steps))
   {
      TCHAR err[256];
      driver::GetLastError(err, sizeof(err));
      throw Exception(String("Ошибка при выполнении шагов ШДL: ") + err);
   }
   plate_position += steps/steps_per_mm;
}

String ReadDisplay()
{
   TCHAR chars[6];
   if (!driver::GetDigital(chars))
   {
      TCHAR err[256];
      driver::GetLastError(err, sizeof(err));
      throw Exception(String("Ошибка при чтении информации с табло: ") + err);
   }
   return String(chars);
}

void PushButton(ebutton btn)
{
   button &b = buttons[btn];
   if (!driver::SetDigital(b.code))
   {
      TCHAR err[256];
      driver::GetLastError(err, sizeof(err));
      throw Exception(String("Ошибка при включении клавиши: ") + b.name.c_str() + ": " + err);
   }
}

