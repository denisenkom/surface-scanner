//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "GraphFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGraph *Graph;
//---------------------------------------------------------------------------
__fastcall TGraph::TGraph(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------


void TGraph::AddTrace(float dataX[], float dataY[], int len, TColor color)
{
}
