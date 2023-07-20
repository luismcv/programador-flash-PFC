//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "nuevodisp.h"
#include "basedatos.h"
#include "datamodule.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormNDisp *FormNDisp;
//---------------------------------------------------------------------------
__fastcall TFormNDisp::TFormNDisp(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormNDisp::BOkClick(TObject *Sender)
{
        Boolean error;
        Integer valor;

        error=false;

        try
        {
                valor=StrToInt(EIdDisp->Text);
        }
        catch(...)
        {
                error=true;
        }

        if (error || valor < 0 || valor > 255)
                ShowMessage(AnsiString("El identificador de dispositivo tiene que ser un valor entero entre 0 y 255"));
        else if (EModelo->Text=="")
                ShowMessage(AnsiString("Debe introducir un nombre para el modelo"));
        else
                ModalResult=mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TFormNDisp::BCancelarClick(TObject *Sender)
{
        ModalResult=mrCancel;
}
//---------------------------------------------------------------------------
