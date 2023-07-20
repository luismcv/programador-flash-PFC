//---------------------------------------------------------------------------

#ifndef acerca_deH
#define acerca_deH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TFormAcercaDe : public TForm
{
__published:	// IDE-managed Components
        TBevel *Bevel1;
        TImage *Image1;
        TStaticText *StaticText1;
        TStaticText *StaticText2;
        TStaticText *StaticText3;
        TStaticText *StaticText4;
        TStaticText *StaticText5;
        TStaticText *StaticText6;
        TStaticText *StaticText7;
        TStaticText *StaticText8;
private:	// User declarations
public:		// User declarations
        __fastcall TFormAcercaDe(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormAcercaDe *FormAcercaDe;
//---------------------------------------------------------------------------
#endif
