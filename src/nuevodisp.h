//---------------------------------------------------------------------------

#ifndef nuevodispH
#define nuevodispH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DBCtrls.hpp>
//---------------------------------------------------------------------------
class TFormNDisp : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TDBLookupComboBox *DBLCBFab;
        TLabel *Label4;
        TEdit *EIdDisp;
        TLabel *Label2;
        TEdit *EModelo;
        TButton *BOk;
        TButton *BCancelar;
        void __fastcall BOkClick(TObject *Sender);
        void __fastcall BCancelarClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormNDisp(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormNDisp *FormNDisp;
//---------------------------------------------------------------------------
#endif
