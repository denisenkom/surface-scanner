//---------------------------------------------------------------------------

#ifndef GraphFrmH
#define GraphFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TGraph : public TForm
{
__published:	// IDE-managed Components
private:	// User declarations
public:
        double scaleX;
        double scaleY;
        double offsY;
        double offsX;
        double sizeX;
        double sizeY;		// User declarations
        __fastcall TGraph(TComponent* Owner);
        void AddTrace(float dataX[], float dataY[], int len, TColor color);
};
//---------------------------------------------------------------------------
extern PACKAGE TGraph *Graph;
//---------------------------------------------------------------------------
#endif
