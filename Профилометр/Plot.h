//---------------------------------------------------------------------------

#ifndef PlotH
#define PlotH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfrmPlot : public TForm
{
__published:	// IDE-managed Components
	void __fastcall FormPaint(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
	double *datax, *datay, scalex, scaley, minx, maxx, miny, maxy;
   int len;
public:		// User declarations
	__fastcall TfrmPlot(TComponent* Owner, const double datax[], const double datay[], int len, std::string caption);
	virtual __fastcall ~TfrmPlot();
   void setScaleX(double scalex);
   void setScaleY(double scaley);
};
//---------------------------------------------------------------------------
#endif
