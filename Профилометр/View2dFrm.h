//---------------------------------------------------------------------------

#ifndef View2dFrmH
#define View2dFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ActnList.hpp>

class TfrmView2d;

class View2d : public ScanDataView {
friend class TForm3;
private:
	TfrmView2d* _form;
public:
	View2d(ScanData* scan_data);
	//View2d(TForm3* form);
	virtual void setData(ScanData* data);
	virtual void update();
	virtual ScanData* getData();
};

//---------------------------------------------------------------------------
class TfrmView2d : public TForm {
friend class View2d;
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPaintBox *Shape1;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall FormDeactivate(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall Shape1MouseMove(TObject *Sender, TShiftState Shift,
			 int X, int Y);
	void __fastcall Shape1MouseDown(TObject *Sender, TMouseButton Button,
			 TShiftState Shift, int X, int Y);
	void __fastcall Shape1MouseUp(TObject *Sender, TMouseButton Button,
			 TShiftState Shift, int X, int Y);
	void __fastcall Shape1Paint(TObject *Sender);
private:	// User declarations
	ScanData* scan_data;
	View2d* _view;
	int startX, startY;
	int endX, endY;
	int oldX, oldY;
public:
	float Scale;
	struct {bool tracing; bool valid; float sx; float sy; float ex; float ey;} trace;		// User declarations
	__fastcall TfrmView2d(TComponent* Owner);
	void New();
   void Load();
	void Save();
	void ZoomIn();
	void ZoomOut();
	void RefreshField();
	void Korrelat();
	void _3D();
	ScanDataView* getView();
};
//---------------------------------------------------------------------------
#endif
