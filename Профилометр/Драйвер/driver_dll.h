#ifdef DLLEXPORT
#define DRIVERAPI __declspec(dllexport)
#else
#define DRIVERAPI __declspec(dllimport)
#endif

namespace profilometer_driver_dll
{
BOOL DRIVERAPI SelectPort(LPCTSTR portname);
BOOL DRIVERAPI GetPortName(LPTSTR name, DWORD size);
BOOL DRIVERAPI SetPortMode(LPCTSTR portmode);
BOOL DRIVERAPI GetPortMode(LPTSTR mode, DWORD size);
BOOL DRIVERAPI RequestACP(BYTE num, SHORT* values);
BOOL DRIVERAPI Test();
BOOL DRIVERAPI MakeSteps(int num);
BOOL DRIVERAPI SetDigital(BYTE digital);
BOOL DRIVERAPI GetDigital(LPTSTR res);
VOID DRIVERAPI GetLastError(LPSTR err, DWORD size);
}
