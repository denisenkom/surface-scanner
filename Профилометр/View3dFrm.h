//---------------------------------------------------------------------------

#ifndef View3dFrmH
#define View3dFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ToolWin.hpp>
//---------------------------------------------------------------------------

class View3d : public ScanDataView {
friend class T_3dForm;
private:
	class TfrmView3d* _form;
public:
	View3d(ScanData* scan_data);
	virtual void setData(ScanData* scan_data);
	virtual void update();
	virtual ScanData* getData();
};

class TfrmView3d : public TForm
{
friend class View3d;
__published:	// IDE-managed Components
	TToolBar *ToolBar1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormPaint(TObject *Sender);
	void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift, int X,
			 int Y);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
	View3d* _view;
	ScanData* scan_data;
	float maxdist;
	float dispz;
	bool initialized;
	HDC hdc;
	HGLRC hgl;
	float rollz;
	float maxrollz;
	float tilt;
	float dist;		// User declarations
	__fastcall TfrmView3d(TComponent* Owner);
	void Draw();
	ScanDataView* getView();
};
//---------------------------------------------------------------------------
#endif
