//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

USERES("profilom.res");
USEFORM("MainFrm.cpp", MainForm);
USEFORM("ScanParFrm.cpp", frmScanParam);
USEFORM("View2dFrm.cpp", frmView2d);
USEUNIT("log.cpp");
USEFORM("View3dFrm.cpp", frmView3d);
USEFORM("uScanningForm.cpp", ScanningForm);
USEFORM("Profilometr.cpp", ProfilometrForm);
USEFORM("GraphFrm.cpp", Graph);
USEFORM("Plot.cpp", frmPlot);
USEUNIT("ScanData.cpp");
USEUNIT("Driver.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
   try
	{
      Application->Initialize();
		Application->Title = "Nirs";
		Application->CreateForm(__classid(TMainForm), &MainForm);
      Application->CreateForm(__classid(TfrmScanParam), &frmScanParam);
      Application->CreateForm(__classid(TScanningForm), &ScanningForm);
      Application->CreateForm(__classid(TProfilometrForm), &ProfilometrForm);
      Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	return 0;
}
//---------------------------------------------------------------------------
