//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "datamodule.h"
#include "basedatos.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TDLPortIO"
#pragma resource "*.dfm"
TDM *DM;

Integer NextSectStartDir;

//---------------------------------------------------------------------------
__fastcall TDM::TDM(TComponent* Owner)
        : TDataModule(Owner)
{
        typedef Set<char,0,255> CharsSet;
        CharsSet ConjLetras;
        char letras[]="ABCDEFabcdefx";
        char i;

        Database1->Close();
        Database1->Params->Values["PATH"]=ExtractFilePath(ParamStr(0))+"bd\\";

        TFabricante->Open();
        TJuegoComandos->Open();
        TComando->Open();
        TDispositivo->Open();
        TSector->Open();

        TJuegoComandosAux->Open();
        TComandoAux->Open();
        TFabricanteAux->Open();
        TDispositivoAux->Open();
        TSectorAux->Open();

        TFabricanteInt->Open();
        TDispositivoInt->Open();
        TJuegoComandosInt->Open();
        TComandoInt->Open();

        for (i=strlen(letras)-1;i>=0;i--)
                ConjLetras << letras[i];

        TFabricante->FieldByName("CODIGO")->ValidChars+=ConjLetras;
        TDispositivo->FieldByName("id")->ValidChars+=ConjLetras;
        TSector->FieldByName("DIRECCION_COMIENZO")->ValidChars+=ConjLetras;
}
//---------------------------------------------------------------------------

void __fastcall TDM::TSectorCalcFields(TDataSet *DataSet)
{
        if (TSectorLONGITUD->IsNull || TSectorNUMERO->IsNull)
                TSectorLONGITUD_TOTAL->Value=0;
        else
                TSectorLONGITUD_TOTAL->AsString=TSectorLONGITUD->AsInteger*TSectorNUMERO->AsInteger;

        TSectorDIRECCION_FINAL->Value="0x"+IntToHex(TSectorDIRECCION_COMIENZO->AsInteger+TSectorLONGITUD_TOTAL->AsInteger-1,5);
}
//---------------------------------------------------------------------------

void __fastcall TDM::T8bitsHexGetText(TField *Sender, AnsiString &Text,
      bool DisplayText)
{
        if (Sender->IsNull)
                Text="";
        else
                Text="0x"+IntToHex(Sender->AsInteger,2);
}
//---------------------------------------------------------------------------

void __fastcall TDM::T8bitsHexSetText(TField *Sender,
      const AnsiString Text)
{
        int Valor=0;

        Valor = StrToInt(Text);
        if (Valor < 0 || Valor > 0xFF)
                throw Exception("El valor debe estar comprendido entre 0x00 y 0xFF");

        Sender->AsInteger=Valor;
        }
//---------------------------------------------------------------------------

void __fastcall TDM::T20bitsHexGetText(TField *Sender,
      AnsiString &Text, bool DisplayText)
{
        if (Sender->IsNull)
                Text="";
        else
                Text="0x"+IntToHex(Sender->AsInteger,5);
}
//---------------------------------------------------------------------------

void __fastcall TDM::T20bitsSetText(TField *Sender,
      const AnsiString Text)
{
        int Valor=0;

        Valor = StrToInt(Text);
        if (Valor < 0 || Valor > 0x7FFFF)
                throw Exception("El valor debe estar comprendido entre 0x00000 y 0x7FFFF");

        Sender->AsInteger=Valor;
}
//---------------------------------------------------------------------------

void __fastcall TDM::TSectorAfterInsert(TDataSet *DataSet)
{
        DataSet->FieldByName("DIRECCION_COMIENZO")->AsInteger=NextSectStartDir;
}
//---------------------------------------------------------------------------

void __fastcall TDM::TSectorBeforeInsert(TDataSet *DataSet)
{
        if (DataSet->IsEmpty())
                NextSectStartDir=0;
        else
                NextSectStartDir=DataSet->FieldByName("DIRECCION_FINAL")->AsInteger+1;
}
//---------------------------------------------------------------------------


