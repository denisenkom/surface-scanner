//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>
#include <string>
#pragma hdrstop
#include "..\..\common\driver_dll.h"
//#include "..\driver.h"
#include "..\driver.cpp"
//---------------------------------------------------------------------------
//   Important note about DLL memory management when your DLL uses the
//   static version of the RunTime Library:
//
//   If your DLL exports any functions that pass String objects (or structs/
//   classes containing nested Strings) as parameter or function results,
//   you will need to add the library MEMMGR.LIB to both the DLL project and
//   any other projects that use the DLL.  You will also need to use MEMMGR.LIB
//   if any other projects which use the DLL will be performing new or delete
//   operations on any non-TObject-derived classes which are exported from the
//   DLL. Adding MEMMGR.LIB to your project will change the DLL and its calling
//   EXE's to use the BORLNDMM.DLL as their memory manager.  In these cases,
//   the file BORLNDMM.DLL should be deployed along with your DLL.
//
//   To avoid using BORLNDMM.DLL, pass string information using "char *" or
//   ShortString parameters.
//
//   If your DLL uses the dynamic version of the RTL, you do not need to
//   explicitly add MEMMGR.LIB as this will be done implicitly for you
//---------------------------------------------------------------------------

driver driver;
std::string last_error;
const char * unknown_error = "Нейзвестная ошибка";
const char * buffer_too_small = "Буфер недостаточно велик";

#pragma argsused
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fwdreason, LPVOID lpvReserved)
{
   return 1;
}
//---------------------------------------------------------------------------
BOOL DRIVERAPI profilometer_driver_dll::SelectPort(LPCTSTR portname)
{
   try
   {
      driver.close_port();
      driver.port = portname;
      return TRUE;
   }
   catch (std::exception &ex)
   {
      last_error = ex.what();
      return FALSE;
   }
   catch (...)
   {
      last_error = unknown_error;
      return FALSE;
   }
}

BOOL DRIVERAPI profilometer_driver_dll::GetPortName(LPTSTR name, DWORD size)
{
   if (driver.port.size() - 1 > size)
   {
      last_error = buffer_too_small;
      return FALSE;
   }
   strcpy(name, driver.port.c_str());
   return TRUE;
}
//
BOOL DRIVERAPI profilometer_driver_dll::SetPortMode(LPCTSTR portmode)
{
   try
   {
      driver.close_port();
      driver.mode = portmode;
      return TRUE;
   }
   catch (std::exception &ex)
   {
      last_error = ex.what();
      return FALSE;
   }
   catch (...)
   {
      last_error = unknown_error;
      return FALSE;
   }
}

BOOL DRIVERAPI profilometer_driver_dll::GetPortMode(LPTSTR mode, DWORD size)
{
   if (driver.mode.size() - 1 > size)
   {
      last_error = buffer_too_small;
      return FALSE;
   }
   strcpy(mode, driver.mode.c_str());
   return TRUE;
}
//
BOOL DRIVERAPI profilometer_driver_dll::RequestACP(BYTE num, SHORT* values)
{
   try
   {
      driver.request_acp(num, values);
      return TRUE;
   }
   catch (std::exception &ex)
   {
      last_error = ex.what();
      return FALSE;
   }
   catch (...)
   {
      last_error = unknown_error;
      return FALSE;
   }
}
//
BOOL DRIVERAPI profilometer_driver_dll::Test()
{
   try
   {
      return driver.test() ? TRUE : FALSE;
   }
   catch (std::exception &ex)
   {
      last_error = ex.what();
      return FALSE;
   }
   catch (...)
   {
      last_error = unknown_error;
      return FALSE;
   }
}
//
BOOL DRIVERAPI profilometer_driver_dll::MakeSteps(int num)
{
   try
   {
      driver.steps(num);
      return TRUE;
   }
   catch (std::exception &ex)
   {
      last_error = ex.what();
      return FALSE;
   }
   catch (...)
   {
      last_error = unknown_error;
      return FALSE;
   }
}
//
BOOL DRIVERAPI profilometer_driver_dll::SetDigital(BYTE digital)
{
   try
   {
      driver.set_digital(digital);
      return TRUE;
   }
   catch (std::exception &ex)
   {
      last_error = ex.what();
      return FALSE;
   }
   catch (...)
   {
      last_error = unknown_error;
      return FALSE;
   }
}

BOOL DRIVERAPI profilometer_driver_dll::GetDigital(LPTSTR res)
{
   try
   {
      char cres[6];
      driver.get_digital(cres);
      return TRUE;
   }
   catch (std::exception &ex)
   {
      last_error = ex.what();
      return FALSE;
   }
   catch (...)
   {
      last_error = unknown_error;
      return FALSE;
   }
}

VOID DRIVERAPI profilometer_driver_dll::GetLastError(LPSTR err, DWORD size)
{
   DWORD s = (last_error.size() + 1) > size ? (size - 1) : last_error.size();
   memcpy(err, last_error.c_str(), s);
   err[s] = 0;
}
