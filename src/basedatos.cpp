//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "basedatos.h"
#include "datamodule.h"
#include "nuevodisp.h"
#include "flash.h"
#include "acerca_de.h"
#include <IniFiles.hpp>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TFormBD *FormBD;

//---------------------------------------------------------------------------
__fastcall TFormBD::TFormBD(TComponent* Owner)
        : TForm(Owner)
{
        int i;

        SGSecuencias->Cells[0][1]="ADDR";
        SGSecuencias->Cells[0][2]="DATA";
        for (i=1;i<SGSecuencias->ColCount;i++)
                SGSecuencias->Cells[i][0]="Ciclo "+IntToStr(i);

        ActualizandoHoja=false;
}
//---------------------------------------------------------------------------
void __fastcall TFormBD::Salir1Click(TObject *Sender)
{
        this->Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormBD::BNuevoJuegoComandosClick(TObject *Sender)
{
        AnsiString S;
        unsigned char ID;

        if (InputQuery("Nuevo juego de comandos","Nombre:",S))
        {
                DM->Database1->StartTransaction();
                try
                {
                        DM->TJuegoComandos->Last();
                        ID=DM->TJuegoComandos->FieldByName("ID")->AsInteger+1;
                        DM->TJuegoComandos->AppendRecord(ARRAYOFCONST((ID,S)));
                        DM->TComando->AppendRecord(ARRAYOFCONST((ID,C_READ,"Read")));
                        DM->TComando->AppendRecord(ARRAYOFCONST((ID,C_RESET,"Reset")));
                        DM->TComando->AppendRecord(ARRAYOFCONST((ID,C_PROGRAM,"Program")));
                        DM->TComando->AppendRecord(ARRAYOFCONST((ID,C_CHIP_ERASE,"Chip erase")));
                        DM->TComando->AppendRecord(ARRAYOFCONST((ID,C_SECT_ERASE,"Sector erase")));
                        DM->TComando->AppendRecord(ARRAYOFCONST((ID,C_SECT_PROTECT_VERIF,"Sector protection status")));
                        DM->Database1->Commit();
                }
                catch (...)
                {
                        DM->Database1->Rollback();
                        throw;
                }
        }
        ActualizarHojaComandos();
}
//---------------------------------------------------------------------------

void __fastcall TFormBD::DBLCBJuegoComandosClick(TObject *Sender)
{
        DM->TJuegoComandos->SetKey();
        DM->TJuegoComandos->FieldByName("ID")->Value=DBLCBJuegoComandos->KeyValue;
        DM->TJuegoComandos->GotoKey();

        DM->TComando->First();

        ActualizarHojaComandos();
}
//---------------------------------------------------------------------------
void __fastcall TFormBD::BEliminarJuegoComandosClick(TObject *Sender)
{
        if(MessageDlg("¿Está seguro de que quiere borrar '"+DM->TJuegoComandos->FieldByName("NOMBRE")->AsString+"'?", mtConfirmation,
                TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
        {
                DM->Database1->StartTransaction();
                try
                {
                        DM->TComando->First();
                        while (!DM->TComando->Eof)
                                DM->TComando->Delete();
                        DM->TJuegoComandos->Delete();
                        DM->Database1->Commit();
                }
                catch (...)
                {
                        DM->Database1->Rollback();
                        throw;
                }
        }
        ActualizarHojaComandos();
}
//---------------------------------------------------------------------------
void __fastcall TFormBD::ActualizarHojaComandos(void)
{
        int c,pos_sep;

        DBLCBJuegoComandos->KeyValue=0;
        DBLCBJuegoComandos->KeyValue=255;
        DBLCBJuegoComandos->KeyValue=DM->TJuegoComandos->FieldByName("ID")->AsInteger;

        DBLCBComando->KeyValue=0;
        DBLCBComando->KeyValue=255;
        DBLCBComando->KeyValue=DM->TComando->FieldByName("ID")->AsInteger;

        TempAddrString=DM->TComando->FieldByName("SEC_DIREC")->AsString;
        c=1;
        pos_sep=TempAddrString.AnsiPos(";");
        while (pos_sep && c <= SGSecuencias->ColCount)
        {
                SGSecuencias->Cells[c][1]=TempAddrString.SubString(1,pos_sep-1);
                TempAddrString=TempAddrString.SubString(pos_sep+1,TempAddrString.Length()-pos_sep);
                pos_sep=TempAddrString.AnsiPos(";");
                c++;
        }
        while(c <= SGSecuencias->ColCount)
        {
                SGSecuencias->Cells[c][1]="";
                c++;
        }

        TempDataString=DM->TComando->FieldByName("SEC_DATOS")->AsString;
        c=1;
        pos_sep=TempDataString.AnsiPos(";");
        while (pos_sep && c <= SGSecuencias->ColCount)
        {
                SGSecuencias->Cells[c][2]=TempDataString.SubString(1,pos_sep-1);
                TempDataString=TempDataString.SubString(pos_sep+1,TempDataString.Length()-pos_sep);
                pos_sep=TempDataString.AnsiPos(";");
                c++;
        }
        while(c <= SGSecuencias->ColCount)
        {
                SGSecuencias->Cells[c][2]="";
                c++;
        }
}
//---------------------------------------------------------------------------
void __fastcall TFormBD::ActualizarHojaDispositivos(void)
{
        int temp;

        DBLCBFab->KeyValue = 0;
        DBLCBFab->KeyValue = 255;
        DBLCBFab->KeyValue = DM->TFabricante->FieldByName("CODIGO")->AsInteger;

        DBLCBMod->KeyValue = 0;
        DBLCBMod->KeyValue = 255;
        DBLCBMod->KeyValue = DM->TDispositivo->FieldByName("ID")->AsInteger;

        DBGSec->Repaint();

        temp=DM->TDispositivo->FieldByName("TAMANYO")->AsInteger-MIN_MEM_TAMANYO;
        CBTam->ItemIndex=(temp>=0)?temp:-1;

        CBNumPin->Text=DM->TDispositivo->FieldByName("NUM_PINES")->AsString;

        CBTamPag->ItemIndex=DM->TDispositivo->FieldByName("TAMANYO_PAGINA")->AsInteger;

        if(DM->TDispositivo->RecordCount)
        {
                char Tipo;

                GBCaract->Enabled=true;
                GBSect->Enabled=true;

                ActualizandoHoja=true;
                Tipo = DM->TDispositivo->FieldByName("TIPO")->AsInteger;
                if ( !ES_PROGRAMABLE(Tipo))
                        RBRom->Checked=true;
                else
                {
                        if (ES_POR_PAGINAS(Tipo))
                                RBPag->Checked=true;
                        else
                                RBByte->Checked=true;
                }

                if (SOPORTA_DQ7DP(Tipo))
                        CBDQ7->Checked=true;
                else
                        CBDQ7->Checked=false;

                if (SOPORTA_DQ6TB(Tipo))
                        CBDQ6->Checked=true;
                else
                        CBDQ6->Checked=false;

                if (SOPORTA_DQ5ETL(Tipo))
                        CBDQ5->Checked=true;
                else
                        CBDQ5->Checked=false;

                ActualizandoHoja=false;
        }
        /* Si no hay ningún dispositivo mostrado, desactivar los elementos */
        else
        {
                GBCaract->Enabled=false;
                GBSect->Enabled=false;

                ActualizandoHoja=true;
                RBByte->Checked=false;
                RBPag->Checked=false;
                RBRom->Checked=false;
                CBDQ7->Checked=false;
                CBDQ6->Checked=false;
                CBDQ5->Checked=false;
                ActualizandoHoja=false;

                CBTamPag->ItemIndex=-1;
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormBD::BCopiarJuegoComandosClick(TObject *Sender)
{
        AnsiString S;
        unsigned char ID;

        if (InputQuery("Copiar juego de comandos como...","Nombre:",S))
        {
                DM->Database1->StartTransaction();
                try
                {       // Buscamos un nuevo ID
                        DM->TJuegoComandosAux->Last();
                        ID=DM->TJuegoComandosAux->FieldByName("ID")->AsInteger+1;

                        // creamos un nuevo juego con el nuevo ID y copiamos los comandos
                        DM->TJuegoComandosAux->AppendRecord(ARRAYOFCONST((ID,S)));
                        DM->TComando->First();
                        while (!DM->TComando->Eof)
                        {
                                DM->TComandoAux->InsertRecord(ARRAYOFCONST((ID,DM->TComando->FieldByName("ID")->Value,DM->TComando->FieldByName("DESCRIPCION")->Value,DM->TComando->FieldByName("SEC_DIREC")->Value,DM->TComando->FieldByName("SEC_DATOS")->Value)));
                                DM->TComando->Next();
                        }

                        DM->Database1->Commit();
                        DM->TJuegoComandos->Last();
                }
                catch (...)
                {
                        DM->Database1->Rollback();
                        throw;
                }
        }
        ActualizarHojaComandos();
}
//---------------------------------------------------------------------------

void __fastcall TFormBD::BNuevoComandoClick(TObject *Sender)
{
        AnsiString S;
        unsigned char ID,IDJuegoComandos;

        if (InputQuery("Nuevo comando","Nombre:",S))
        {
                // Calculamos un nuevo ID
                DM->TComando->Last();
                ID=DM->TComando->FieldByName("ID")->AsInteger+1;
                if (ID <= MAX_ID_C_BAS)         // Todos los comandos añadidos por el usuario tendrán
                        ID = MAX_ID_C_BAS + 1;  // ID mayor que MAX_ID_C_BAS;

                IDJuegoComandos=DM->TJuegoComandos->FieldByName("ID")->AsInteger;
                DM->TComando->AppendRecord(ARRAYOFCONST((IDJuegoComandos,ID,S)));
        }
        ActualizarHojaComandos();
}
//---------------------------------------------------------------------------

void __fastcall TFormBD::BEliminarComandoClick(TObject *Sender)
{
        if (DM->TComando->FieldByName("ID")->AsInteger < MAX_ID_C_BAS)
        {
                MessageDlg("No se puede eliminar un comando básico.",mtError,TMsgDlgButtons() << mbOK,0);
                return;
        }

        if(MessageDlg("¿Está seguro de que quiere borrar '"+DM->TComando->FieldByName("DESCRIPCION")->AsString+"'?", mtConfirmation,
                TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
        {
                DM->TComando->Delete();
        }
        ActualizarHojaComandos();
}
//---------------------------------------------------------------------------

void __fastcall TFormBD::BCopiarComandoClick(TObject *Sender)
{
        AnsiString S;
        unsigned char ID,IDJuegoComandos;

        if (InputQuery("Copiar comando como...","Nombre:",S))
        {
                // Calculamos un nuevo ID de comando
                DM->TComandoAux->Last();
                ID=DM->TComandoAux->FieldByName("ID")->AsInteger+1;
                if (ID <= MAX_ID_C_BAS)         // Todos los comandos añadidos por el usuario tendrán
                        ID = MAX_ID_C_BAS + 1;  // ID mayor que MAX_ID_C_BAS;

                IDJuegoComandos=DM->TJuegoComandos->FieldByName("ID")->AsInteger;
                DM->TComandoAux->AppendRecord(ARRAYOFCONST((IDJuegoComandos,ID,S,DM->TComando->FieldByName("SEC_DIREC")->Value,DM->TComando->FieldByName("SEC_DATOS")->Value)));
                DM->TComando->Last();
        }
        ActualizarHojaComandos();
}
//---------------------------------------------------------------------------

void __fastcall TFormBD::IrAFabricante(unsigned char CodFab)
{
        DM->TFabricante->SetKey();
        DM->TFabricante->FieldByName("CODIGO")->Value=CodFab;
        DM->TFabricante->GotoKey();
}
//---------------------------------------------------------------------------
void __fastcall TFormBD::IrADispositivo(unsigned char CodFab, unsigned char IdDisp)
{
        DM->TDispositivo->SetKey();
        DM->TDispositivo->FieldByName("CODIGO_FABRICANTE")->Value=CodFab;
        DM->TDispositivo->FieldByName("ID")->Value=IdDisp;
        DM->TDispositivo->GotoKey();
}

//---------------------------------------------------------------------------
void __fastcall TFormBD::DBLCBFabClick(TObject *Sender)
{
        ComprobarCambiosPendientes();

        IrAFabricante(DBLCBFab->KeyValue);

        DM->TDispositivo->First();
        ActualizarHojaDispositivos();
}
//---------------------------------------------------------------------------

void __fastcall TFormBD::CBTamChange(TObject *Sender)
{
        if (DM->TDispositivo->State != dsEdit)
                DM->TDispositivo->Edit();
        DM->TDispositivo->FieldByName("TAMANYO")->AsInteger=CBTam->ItemIndex+MIN_MEM_TAMANYO;
}
//---------------------------------------------------------------------------

void __fastcall TFormBD::CBNumPinChange(TObject *Sender)
{
        if (DM->TDispositivo->State != dsEdit)
                DM->TDispositivo->Edit();
        DM->TDispositivo->FieldByName("NUM_PINES")->AsString=CBNumPin->Text;
}
//---------------------------------------------------------------------------

void __fastcall TFormBD::RBByteToggleClick(TObject *Sender)
{
        if (!ActualizandoHoja)
        {
                if (DM->TDispositivo->State != dsEdit)
                        DM->TDispositivo->Edit();
                DM->TDispositivo->FieldByName("TIPO")->AsInteger=1;
        }
        CBTamPag->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TFormBD::RBPagClick(TObject *Sender)
{
        char Tipo;

        if (!ActualizandoHoja)
        {
                if (DM->TDispositivo->State != dsEdit)
                        DM->TDispositivo->Edit();
                Tipo = DM->TDispositivo->FieldByName("TIPO")->AsInteger;
                Tipo = Tipo | T_PROGRAMABLE | T_POR_PAGINAS;
                DM->TDispositivo->FieldByName("TIPO")->AsInteger = Tipo;
        }
        CBTamPag->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TFormBD::RBRomClick(TObject *Sender)
{
        char Tipo;

        if (!ActualizandoHoja)
        {
                if (DM->TDispositivo->State != dsEdit)
                        DM->TDispositivo->Edit();
                Tipo = DM->TDispositivo->FieldByName("TIPO")->AsInteger;
                Tipo = Tipo & ~T_PROGRAMABLE;
                DM->TDispositivo->FieldByName("TIPO")->AsInteger = Tipo;
        }
        CBTamPag->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TFormBD::RBByteClick(TObject *Sender)
{
        char Tipo;

        if (!ActualizandoHoja)
        {
                if (DM->TDispositivo->State != dsEdit)
                        DM->TDispositivo->Edit();
                Tipo = DM->TDispositivo->FieldByName("TIPO")->AsInteger;
                Tipo = Tipo | T_PROGRAMABLE;
                Tipo = Tipo & ~T_POR_PAGINAS;
                DM->TDispositivo->FieldByName("TIPO")->AsInteger = Tipo;
        }
        CBTamPag->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TFormBD::CBTamPagChange(TObject *Sender)
{
        if (DM->TDispositivo->State != dsEdit)
                DM->TDispositivo->Edit();
        DM->TDispositivo->FieldByName("TAMANYO_PAGINA")->AsInteger=CBTamPag->ItemIndex;
}
//---------------------------------------------------------------------------

void __fastcall TFormBD::SGSecuenciasGetEditText(TObject *Sender, int ACol,
      int ARow, AnsiString &Value)
{
      OldData=Value;
      OldColPos=ACol;
      OldRowPos=ARow;
}
//---------------------------------------------------------------------------

void __fastcall TFormBD::SGSecuenciasKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
      if (Key == VK_ESCAPE)
      {
        SGSecuencias->Cells[SGSecuencias->Col][SGSecuencias->Row] = OldData;
        DataChanged=false;
      }
      else if ((Key == VK_RETURN))
        SaveSeqData();
      else if ((Key == VK_DELETE))
        DataChanged=true;
}
//---------------------------------------------------------------------------

void __fastcall TFormBD::SGSecuenciasSelectCell(TObject *Sender, int ACol,
      int ARow, bool &CanSelect)
{
        CanSelect=true;
        SaveSeqData();
}
//---------------------------------------------------------------------------
void __fastcall TFormBD::SaveSeqData(void)
{
        int col;

        if (DataChanged)
        {
                TempAddrString="";
                TempDataString="";
                try
                {
                        for (col=1;col<SGSecuencias->ColCount;col++)
                        {
                                if (!SGSecuencias->Cells[col][1].IsEmpty())
                                {
                                        if (SGSecuencias->Cells[col][1].AnsiCompareIC("SA")!=0)
                                        {
                                                int Valor;
                                                Valor = SGSecuencias->Cells[col][1].ToInt();
                                                if (Valor < 0 || Valor > 0x7FFFF)
                                                        throw (EConvertError("La dirección debe estar comprendida entra 0x00000 y 0x7FFFF"));
                                                SGSecuencias->Cells[col][1]="0x"+IntToHex(Valor,5);
                                        }
                                        else if (DM->TComando->FieldByName("ID")->Value==C_SECT_ERASE)
                                                SGSecuencias->Cells[col][1]="SA";
                                        else
                                                throw (EConvertError("\"SA\" sólo es aplicable\na \"Sector erase\""));
                                }
                                if (!SGSecuencias->Cells[col][2].IsEmpty())
                                {
                                        int Valor;
                                        Valor = SGSecuencias->Cells[col][2].ToInt();
                                        if (Valor < 0 || Valor > 0xFF)
                                                throw (EConvertError("El dato debe estar comprendido entre 0x00 y 0xFF"));
                                        SGSecuencias->Cells[col][2]="0x"+IntToHex(Valor,2);
                                }

                        TempAddrString=TempAddrString+SGSecuencias->Cells[col][1]+";";
                        TempDataString=TempDataString+SGSecuencias->Cells[col][2]+";";
                        }

                        DM->TComando->Edit();
                        DM->TComando->FieldByName("SEC_DIREC")->Value=TempAddrString;
                        DM->TComando->FieldByName("SEC_DATOS")->Value=TempDataString;
                        DM->TComando->Post();
                        DataChanged=false;
                }
                catch(EConvertError &Excepcion)
                        {
                                if (Excepcion.Message.IsEmpty())
                                        MessageDlg("Formato incorrecto",mtError,TMsgDlgButtons() << mbOK,0);
                                else
                                        MessageDlg(Excepcion.Message,mtError,TMsgDlgButtons() << mbOK,0);
                        }
        }
}
//---------------------------------------------------------------------------
void __fastcall TFormBD::SGSecuenciasKeyPress(TObject *Sender, char &Key)
{
        DataChanged=true;
}
//---------------------------------------------------------------------------

void __fastcall TFormBD::SGSecuenciasExit(TObject *Sender)
{
        SaveSeqData();
}
//---------------------------------------------------------------------------

void __fastcall TFormBD::DBLCBComandoClick(TObject *Sender)
{
        DM->TComando->SetKey();
        DM->TComando->FieldByName("JUEGO_COMANDOS")->Value=DBLCBJuegoComandos->KeyValue;
        DM->TComando->FieldByName("ID")->Value=DBLCBComando->KeyValue;
        DM->TComando->GotoKey();

        ActualizarHojaComandos();
}
//---------------------------------------------------------------------------

void __fastcall TFormBD::SGSecuenciasDrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
  TFont* HeaderFont;
  TFont* CellFont;
  TFont* RowTitleFont;

  HeaderFont=new TFont;
  HeaderFont->Style = HeaderFont->Style << fsBold;

  CellFont=new TFont;   //default font is ms sans serif

  int leftMargin;

if (ARow == 0 || ACol == 0)
  {
    SGSecuencias->Canvas->Brush->Color=clBtnFace;
    SGSecuencias->Canvas->FillRect(Rect);

    SGSecuencias->Canvas->Font->Assign(HeaderFont);
    leftMargin=(Rect.Right-Rect.Left-SGSecuencias->Canvas->TextWidth(SGSecuencias->Cells[ACol][ARow]))/2;
    SGSecuencias->Canvas->TextOut(Rect.Left+leftMargin,Rect.Top+4,SGSecuencias->Cells[ACol][ARow]);
    SGSecuencias->Canvas->Font->Assign(CellFont);
  }
 else
  {
    SGSecuencias->Canvas->Brush->Color=clWhite;
    SGSecuencias->Canvas->FillRect(Rect);
    leftMargin=(Rect.Right-Rect.Left-SGSecuencias->Canvas->TextWidth(SGSecuencias->Cells[ACol][ARow]))/2;
    SGSecuencias->Canvas->Font->Assign(CellFont);
    SGSecuencias->Canvas->TextOut(Rect.Left+leftMargin,Rect.Top+4,SGSecuencias->Cells[ACol][ARow]);
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormBD::CancelarCambios(void)
{
        unsigned char CodFabAct, IdDispAct;

        if (DM->TDispositivo->State == dsEdit)
                DM->TDispositivo->Post();

        if (DM->TSector->State == dsEdit)
                DM->TSector->Post();

        CodFabAct = DM->TDispositivo->FieldByName("CODIGO_FABRICANTE")->AsInteger;
        IdDispAct = DM->TDispositivo->FieldByName("ID")->AsInteger;

        if (DM->TDispositivo->UpdatesPending || DM->TSector->UpdatesPending)
        {
                DM->TDispositivo->CancelUpdates();
                DM->TSector->CancelUpdates();

                IrAFabricante(CodFabAct);
                IrADispositivo(CodFabAct,IdDispAct);
        }
}
//---------------------------------------------------------------------------
void __fastcall TFormBD::GuardarCambios(Boolean Borrando)
{
        unsigned char CodFabAct, IdDispAct;

        CodFabAct = DM->TDispositivo->FieldByName("CODIGO_FABRICANTE")->AsInteger;
        IdDispAct = DM->TDispositivo->FieldByName("ID")->AsInteger;

        if (DM->TDispositivo->State == dsEdit)
                DM->TDispositivo->Post();

        if (DM->TSector->State == dsEdit)
                DM->TSector->Post();

        if (DM->TDispositivo->UpdatesPending || DM->TSector->UpdatesPending)
        {
                DM->Database1->StartTransaction();
                try
                {
                        if (Borrando)
                        {
                                DM->TSector->ApplyUpdates();
                                DM->TDispositivo->ApplyUpdates();
                        }
                        else
                        {
                                DM->TDispositivo->ApplyUpdates();
                                DM->TSector->ApplyUpdates();
                        }
                        DM->Database1->Commit();
                }
                catch (...)
                {
                        DM->Database1->Rollback();
                        throw;
                }
                DM->TDispositivo->CommitUpdates();
                DM->TSector->CommitUpdates();

                IrAFabricante(CodFabAct);
                IrADispositivo(CodFabAct,IdDispAct);
        }

}
//---------------------------------------------------------------------------

void __fastcall TFormBD::BNuevoDispClick(TObject *Sender)
{
        AnsiString Modelo;
        unsigned char IdDisp,CodFab;

        ComprobarCambiosPendientes();

        if (NuevoDisp(&CodFab,&Modelo,&IdDisp) == mrOk)
        {

                if (ExisteDisp(CodFab,IdDisp))
                {
                        MessageDlg("Ya existe un dispositivo con la misma identificación.",mtError,TMsgDlgButtons() << mbOK,0);
                        return;
                }

                DM->Database1->StartTransaction();
                try
                {
                        DM->TDispositivoAux->Append();
                        DM->TDispositivoAux->FieldByName("NOMBRE")->AsString=Modelo;
                        DM->TDispositivoAux->FieldByName("CODIGO_FABRICANTE")->AsInteger=CodFab;
                        DM->TDispositivoAux->FieldByName("ID")->Value=IdDisp;
                        DM->TDispositivoAux->FieldByName("TIPO")->Value=1;
                        DM->TDispositivoAux->FieldByName("NUM_PINES")->AsInteger=32;
                        DM->TDispositivoAux->FieldByName("JUEGO_COMANDOS")->Value=DM->TJuegoComandos->FieldByName("ID")->Value;
                        DM->TDispositivoAux->FieldByName("TAMANYO")->AsInteger=20;
                        DM->TDispositivoAux->FieldByName("TAMANYO_PAGINA")->AsInteger=7;
                        DM->TDispositivoAux->Post();

                        DM->Database1->Commit();

                        IrAFabricante(CodFab);
                        IrADispositivo(CodFab,IdDisp);
                }
                catch (...)
                {
                        DM->Database1->Rollback();
                        throw;
                }
                ActualizarHojaDispositivos();
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormBD::PageControl1Change(TObject *Sender)
{
        // Actualizamos la pestaña a la que entramos
        // y en el caso de los dispositivos, activamos
        // el "cacheado" de cambios para que el usuario
        // pueda cancelar cambios
        if (PageControl1->ActivePageIndex == 2)
        {
                DM->TDispositivo->CachedUpdates=true;
                DM->TSector->CachedUpdates=true;
                ActualizarHojaDispositivos();
        }
        else if (PageControl1->ActivePageIndex == 1)
                ActualizarHojaComandos();

}
//---------------------------------------------------------------------------

void __fastcall TFormBD::ComprobarCambiosPendientes(void)
{
        if (DM->TDispositivo->State == dsEdit)
                DM->TDispositivo->Post();

        if (DM->TSector->State == dsEdit)
                DM->TSector->Post();

        if (DM->TDispositivo->UpdatesPending || DM->TSector->UpdatesPending)
        {
                if(MessageDlg("¿Desea guardar los cambios realizados?", mtConfirmation,
                        TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
                        GuardarCambios(false);
                else
                        CancelarCambios();
        }
}

//---------------------------------------------------------------------------

void __fastcall TFormBD::PageControl1Changing(TObject *Sender,
      bool &AllowChange)
{
        // Antes de salir de la ventana de edición de dispositivos...
        if (PageControl1->ActivePageIndex == 2)
        {
                unsigned char CodFab, IdDisp;

                // Comprobamos si hay cambios pendientes para darle la oportunidad
                // al usuario de aceptarlos o cancelarlos
                ComprobarCambiosPendientes();

                // Obtenemos la posición actual en las tablas
                CodFab=DM->TFabricante->FieldByName("CODIGO")->AsInteger;
                IdDisp=DM->TDispositivo->FieldByName("ID")->AsInteger;

                // Desactivamos las actualizaciones "cacheadas"
                DM->TSector->CachedUpdates=false;
                DM->TDispositivo->CachedUpdates=false;

                // Recuperamos la posición actual
                // que ha podido cambiarse al desactivar el cacheado de datos
                IrAFabricante(CodFab);
                IrADispositivo(CodFab,IdDisp);

        }

        // Antes de salir de la ventana de edición de fabricantes...
        if (PageControl1->ActivePageIndex == 0)
        {
                if (DM->TFabricante->State == dsInsert || DM->TFabricante->State == dsEdit)
                        DM->TFabricante->Post();
        }

}


void __fastcall TFormBD::DBLCBModClick(TObject *Sender)
{
        ComprobarCambiosPendientes();

        IrADispositivo(DBLCBFab->KeyValue,DBLCBMod->KeyValue);

        ActualizarHojaDispositivos();
}
//---------------------------------------------------------------------------

void __fastcall TFormBD::FormClose(TObject *Sender, TCloseAction &Action)
{
        ComprobarCambiosPendientes();
        DM->TSector->CachedUpdates=false;
        DM->TDispositivo->CachedUpdates=false;
}
//---------------------------------------------------------------------------

void __fastcall TFormBD::BEliminarDispClick(TObject *Sender)
{
        if (DM->TDispositivo->RecordCount)
        {
                if(MessageDlg("¿Está seguro de que quiere borrar '"+DM->TDispositivo->FieldByName("NOMBRE")->AsString+"'?", mtConfirmation,
                        TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
                {

                        CancelarCambios();

                        DM->Database1->StartTransaction();
                        try
                        {
                                DM->TSector->First();
                                while (!DM->TSector->Eof)
                                        DM->TSector->Delete();
                                DM->TDispositivo->Delete();
                                DM->Database1->Commit();
                        }
                        catch (...)
                        {
                                DM->Database1->Rollback();
                                throw;
                        }

                        GuardarCambios(true);

                        ActualizarHojaDispositivos();
                }
        }
}
//---------------------------------------------------------------------------


void __fastcall TFormBD::BCancelarCambiosDispClick(TObject *Sender)
{
        CancelarCambios();
        ActualizarHojaDispositivos();
}
//---------------------------------------------------------------------------
int __fastcall TFormBD::NuevoDisp(unsigned char *CodFab, AnsiString *Modelo, unsigned char *IdDisp)
{
        int retVal;

        FormNDisp->DBLCBFab->KeyValue=DM->TFabricante->FieldByName("CODIGO")->AsInteger;
        FormNDisp->EIdDisp->Text="";
        FormNDisp->EModelo->Text="";

        retVal=FormNDisp->ShowModal();

        if (retVal==mrOk)
        {
                *CodFab=FormNDisp->DBLCBFab->KeyValue;
                *IdDisp=StrToInt(FormNDisp->EIdDisp->Text);
                *Modelo=FormNDisp->EModelo->Text;
        }

        return retVal;
}
//---------------------------------------------------------------------------

void __fastcall TFormBD::BCopiarDispClick(TObject *Sender)
{
        AnsiString Modelo;
        unsigned char IdDisp,CodFab;
        int i;

        ComprobarCambiosPendientes();

        if (NuevoDisp(&CodFab,&Modelo,&IdDisp) == mrOk)
        {

                if (ExisteDisp(CodFab,IdDisp))
                {
                        MessageDlg("Ya existe un dispositivo con la misma identificación.",mtError,TMsgDlgButtons() << mbOK,0);
                        return;
                }

                DM->Database1->StartTransaction();
                try
                {
                        Boolean SeHanCopiadoSectores = false;

                        DM->TDispositivoAux->Append();
                        for (i=0;i < DM->TDispositivoAux->FieldCount;i++)
                                DM->TDispositivoAux->Fields->Fields[i]->Value=DM->TDispositivo->Fields->Fields[i]->Value;
                        DM->TDispositivoAux->FieldByName("CODIGO_FABRICANTE")->AsInteger=CodFab;
                        DM->TDispositivoAux->FieldByName("NOMBRE")->AsString=Modelo;
                        DM->TDispositivoAux->FieldByName("ID")->Value=IdDisp;
                        DM->TDispositivoAux->Post();

                        DM->TSector->First();
                        while (!DM->TSector->Eof)
                        {
                                SeHanCopiadoSectores=true;

                                DM->TSectorAux->Append();
                                for (i=0;i < DM->TSectorAux->FieldCount;i++)
                                        DM->TSectorAux->Fields->Fields[i]->Value=DM->TSector->Fields->Fields[i]->Value;
                                DM->TSectorAux->FieldByName("CODIGO_FABRICANTE")->AsInteger=CodFab;
                                DM->TSectorAux->FieldByName("ID_DISPOSITIVO")->AsInteger=IdDisp;

                                DM->TSector->Next();
                        }

                        if (SeHanCopiadoSectores)
                                DM->TSectorAux->Post();

                        DM->Database1->Commit();

                        IrAFabricante(CodFab);
                        IrADispositivo(CodFab,IdDisp);
                }
                catch (...)
                {
                        DM->Database1->Rollback();
                        throw;
                }
                ActualizarHojaDispositivos();
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormBD::BGuardarCambiosDispClick(TObject *Sender)
{
        GuardarCambios(false);
        ActualizarHojaDispositivos();
}
//---------------------------------------------------------------------------

void __fastcall TFormBD::CBDQ7Click(TObject *Sender)
{
        char Tipo;

        if (!ActualizandoHoja)
        {
                if (DM->TDispositivo->State != dsEdit)
                        DM->TDispositivo->Edit();
                Tipo = DM->TDispositivo->FieldByName("TIPO")->AsInteger;
                if (CBDQ7->Checked)
                        Tipo = Tipo | T_DQ7DP;
                else
                        Tipo = Tipo & ~T_DQ7DP;
                DM->TDispositivo->FieldByName("TIPO")->AsInteger = Tipo;
        }

}
//---------------------------------------------------------------------------

void __fastcall TFormBD::CBDQ6Click(TObject *Sender)
{
        char Tipo;

        if (!ActualizandoHoja)
        {
                if (DM->TDispositivo->State != dsEdit)
                        DM->TDispositivo->Edit();
                Tipo = DM->TDispositivo->FieldByName("TIPO")->AsInteger;
                if (CBDQ6->Checked)
                        Tipo = Tipo | T_DQ6TB;
                else
                        Tipo = Tipo & ~T_DQ6TB;
                DM->TDispositivo->FieldByName("TIPO")->AsInteger = Tipo;
        }

}
//---------------------------------------------------------------------------

void __fastcall TFormBD::CBDQ5Click(TObject *Sender)
{
        char Tipo;

        if (!ActualizandoHoja)
        {
                if (DM->TDispositivo->State != dsEdit)
                        DM->TDispositivo->Edit();
                Tipo = DM->TDispositivo->FieldByName("TIPO")->AsInteger;
                if (CBDQ5->Checked)
                        Tipo = Tipo | T_DQ5ETL;
                else
                        Tipo = Tipo & ~T_DQ5ETL;
                DM->TDispositivo->FieldByName("TIPO")->AsInteger = Tipo;
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormBD::Ayudaprogramador1Click(TObject *Sender)
{
        AnsiString FicheroAyuda;

        FicheroAyuda=ExtractFileDir(ParamStr(0))+"\\manual\\index.html";
        ShellExecute(0,"open",FicheroAyuda.c_str(),NULL,NULL,SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TFormBD::Ayudabasededatos1Click(TObject *Sender)
{
        AnsiString FicheroAyuda;

        FicheroAyuda=ExtractFileDir(ParamStr(0))+"\\manual\\node11.html";
        ShellExecute(0,"open",FicheroAyuda.c_str(),NULL,NULL,SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TFormBD::Acercade1Click(TObject *Sender)
{
        FormAcercaDe->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TFormBD::BInsFabClick(TObject *Sender)
{
        DM->TFabricante->Append();
}
//---------------------------------------------------------------------------

void __fastcall TFormBD::BDelFabClick(TObject *Sender)
{
        if(MessageDlg("¿Está seguro de que quiere borrar '"+DM->TFabricante->FieldByName("NOMBRE")->AsString+"'?", mtConfirmation,
               TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
                DM->TFabricante->Delete();
}
//---------------------------------------------------------------------------

void __fastcall TFormBD::BInsertSectClick(TObject *Sender)
{
        DM->TSector->Append();
}
//---------------------------------------------------------------------------

void __fastcall TFormBD::BEliminarSectClick(TObject *Sender)
{
        if(MessageDlg("¿Está seguro de que quiere borrar esta fila?", mtConfirmation,
               TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
                DM->TSector->Delete();
}
//---------------------------------------------------------------------------
void __fastcall TFormBD::ExportarDisp(String NombreFich, unsigned char CodFab, unsigned char IdDisp)
{
        TIniFile *FichDescDisp;

        DM->TFabricanteAux->SetKey();
        DM->TFabricanteAux->FieldByName("CODIGO")->Value=CodFab;
        if (!DM->TFabricanteAux->GotoKey())
                throw Exception("ERROR INTERNO: No se encontró fabricante: 0x"+IntToHex(CodFab,2));

        DM->TDispositivoAux->SetKey();
        DM->TDispositivoAux->FieldByName("CODIGO_FABRICANTE")->Value=CodFab;
        DM->TDispositivoAux->FieldByName("ID")->Value=IdDisp;
        if (!DM->TDispositivoAux->GotoKey())
                throw Exception("ERROR INTERNO: No se encontró dispositivo: 0x"+IntToHex(CodFab,2)+" - 0x"+IntToHex(IdDisp,2));

        if (FileExists(NombreFich))
                DeleteFile(NombreFich);
        FichDescDisp = new TIniFile(NombreFich);

        FichDescDisp->WriteString("Fabricante","Codigo",DM->TFabricanteAux->FieldByName("CODIGO")->AsString);
        FichDescDisp->WriteString("Fabricante","Nombre",DM->TFabricanteAux->FieldByName("NOMBRE")->AsString);

        FichDescDisp->WriteString("Dispositivo","Id",DM->TDispositivoAux->FieldByName("ID")->AsString);
        FichDescDisp->WriteString("Dispositivo","Nombre",DM->TDispositivoAux->FieldByName("NOMBRE")->AsString);
        FichDescDisp->WriteString("Dispositivo","NumPines",DM->TDispositivoAux->FieldByName("NUM_PINES")->AsString);
        FichDescDisp->WriteString("Dispositivo","Tipo",DM->TDispositivoAux->FieldByName("TIPO")->AsString);
        FichDescDisp->WriteString("Dispositivo","JuegoComandos",DM->TDispositivoAux->FieldByName("JUEGO_COMANDOS")->AsString);
        FichDescDisp->WriteString("Dispositivo","Tamaño",DM->TDispositivoAux->FieldByName("TAMANYO")->AsString);
        FichDescDisp->WriteString("Dispositivo","TamañoPagina",DM->TDispositivoAux->FieldByName("TAMANYO_PAGINA")->AsString);

        DM->TSectorAux->SetRangeStart();
        DM->TSectorAux->FieldByName("CODIGO_FABRICANTE")->Value=CodFab;
        DM->TSectorAux->FieldByName("ID_DISPOSITIVO")->Value=IdDisp;
        DM->TSectorAux->FieldByName("DIRECCION_COMIENZO")->Value=0;

        DM->TSectorAux->SetRangeEnd();
        DM->TSectorAux->FieldByName("CODIGO_FABRICANTE")->Value=CodFab;
        DM->TSectorAux->FieldByName("ID_DISPOSITIVO")->Value=IdDisp;
        DM->TSectorAux->FieldByName("DIRECCION_COMIENZO")->Value=0xFFFFF;

        DM->TSectorAux->ApplyRange();
        DM->TSectorAux->First();

        int NumSect = 0;
        while (!DM->TSectorAux->Eof)
        {
                FichDescDisp->WriteString("Sector"+IntToStr(NumSect),"DirComienzo",DM->TSectorAux->FieldByName("DIRECCION_COMIENZO")->AsString);
                FichDescDisp->WriteString("Sector"+IntToStr(NumSect),"Numero",DM->TSectorAux->FieldByName("NUMERO")->AsString);
                FichDescDisp->WriteString("Sector"+IntToStr(NumSect),"Longitud",DM->TSectorAux->FieldByName("LONGITUD")->AsString);
                DM->TSectorAux->Next();
                NumSect++;
        }

        DM->TSectorAux->CancelRange();

        delete FichDescDisp;
}

//---------------------------------------------------------------------------
Boolean __fastcall TFormBD::ExisteFab(unsigned char CodFab)
{
        DM->TFabricanteAux->SetKey();
        DM->TFabricanteAux->FieldByName("CODIGO")->Value=CodFab;
        return(DM->TFabricanteAux->GotoKey());
}
//---------------------------------------------------------------------------
Boolean __fastcall TFormBD::ExisteDisp(unsigned char CodFab, unsigned char IdDisp)
{
        DM->TDispositivoAux->SetKey();
        DM->TDispositivoAux->FieldByName("CODIGO_FABRICANTE")->Value=CodFab;
        DM->TDispositivoAux->FieldByName("ID")->Value=IdDisp;
        return(DM->TDispositivoAux->GotoKey());
}
//---------------------------------------------------------------------------
Boolean __fastcall TFormBD::ExisteJuegoComandos(unsigned char IdJuego)
{
        DM->TJuegoComandosAux->SetKey();
        DM->TJuegoComandosAux->FieldByName("ID")->Value=IdJuego;
        return(DM->TJuegoComandosAux->GotoKey());
}
//---------------------------------------------------------------------------
void __fastcall TFormBD::ImportarDisp(String NombreFich, unsigned char &CodFab, unsigned char &IdDisp)
{
        TIniFile *FichDescDisp;
        unsigned char JuegoComandos;

        if (!FileExists(NombreFich))
                throw Exception("ERROR: No se pudo leer "+NombreFich);

        FichDescDisp = new TIniFile(NombreFich);

        DM->Database1->StartTransaction();
        try
        {
                CodFab = FichDescDisp->ReadString("Fabricante","Codigo","").ToInt();

                if (!ExisteFab(CodFab))
                {
                        DM->TFabricanteAux->Append();
                        DM->TFabricanteAux->FieldByName("CODIGO")->AsString = CodFab;
                        DM->TFabricanteAux->FieldByName("NOMBRE")->AsString = FichDescDisp->ReadString("Fabricante","Nombre","");
                        DM->TFabricanteAux->Post();
                }

                IdDisp = FichDescDisp->ReadString("Dispositivo","Id","").ToInt();
                if (ExisteDisp(CodFab,IdDisp))
                        throw Exception("Ya existe un dispositivo con los mismos indentificadores.\n\nCód. Fabricante: 0x"+IntToHex(CodFab,2)+"\nId. dispositivo: 0x"+IntToHex(IdDisp,2));

                JuegoComandos = FichDescDisp->ReadString("Dispositivo","JuegoComandos","").ToInt();
                if (!ExisteJuegoComandos(JuegoComandos))
                {
                        DM->TJuegoComandosAux->First();
                        JuegoComandos = DM->TJuegoComandosAux->FieldByName("ID")->AsInteger;
                }

                DM->TDispositivoAux->Append();
                DM->TDispositivoAux->FieldByName("CODIGO_FABRICANTE")->AsString = CodFab;
                DM->TDispositivoAux->FieldByName("ID")->AsString = IdDisp;
                DM->TDispositivoAux->FieldByName("NOMBRE")->AsString = FichDescDisp->ReadString("Dispositivo","Nombre","");
                DM->TDispositivoAux->FieldByName("NUM_PINES")->AsString = FichDescDisp->ReadString("Dispositivo","NumPines","");
                DM->TDispositivoAux->FieldByName("TIPO")->AsString = FichDescDisp->ReadString("Dispositivo","Tipo","");
                DM->TDispositivoAux->FieldByName("JUEGO_COMANDOS")->AsString = JuegoComandos;
                DM->TDispositivoAux->FieldByName("TAMANYO")->AsString = FichDescDisp->ReadString("Dispositivo","Tamaño","");
                DM->TDispositivoAux->FieldByName("TAMANYO_PAGINA")->AsString = FichDescDisp->ReadString("Dispositivo","TamañoPagina","");
                DM->TDispositivoAux->Post();

                int NumSect = 0;
                AnsiString DirComienzo;
                Boolean Fin = false;
                while (!Fin)
                {
                        DirComienzo = FichDescDisp->ReadString("Sector"+IntToStr(NumSect),"DirComienzo","FIN");
                        if (DirComienzo.AnsiCompare("FIN") == 0)
                                Fin = true;
                        else
                                {
                                        DM->TSectorAux->Append();
                                        DM->TSectorAux->FieldByName("CODIGO_FABRICANTE")->AsString = CodFab;
                                        DM->TSectorAux->FieldByName("ID_DISPOSITIVO")->AsString = IdDisp;
                                        DM->TSectorAux->FieldByName("DIRECCION_COMIENZO")->AsString = DirComienzo;
                                        DM->TSectorAux->FieldByName("NUMERO")->AsString = FichDescDisp->ReadString("Sector"+IntToStr(NumSect),"Numero","0");
                                        DM->TSectorAux->FieldByName("LONGITUD")->AsString = FichDescDisp->ReadString("Sector"+IntToStr(NumSect),"Longitud","0");
                                        DM->TSectorAux->Post();
                              }
                        NumSect++;
                }

                DM->Database1->Commit();
        }
        catch (...)
        {
                DM->Database1->Rollback();
                throw;
        }

        delete FichDescDisp;
}
//---------------------------------------------------------------------------

void __fastcall TFormBD::BImportarClick(TObject *Sender)
{
        unsigned char CodFab, IdDisp;

        if (OpenDialog1->Execute())
        {
                ComprobarCambiosPendientes();
                ImportarDisp(OpenDialog1->FileName, CodFab, IdDisp);
                IrAFabricante(CodFab);
                IrADispositivo(CodFab, IdDisp);
                ActualizarHojaDispositivos();

                MessageDlg("Compruebe que el Juego de Comandos es el correcto.",mtWarning,TMsgDlgButtons() << mbOK,0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TFormBD::BExportarClick(TObject *Sender)
{
        if (SaveDialog1->Execute())
                ExportarDisp(SaveDialog1->FileName, DM->TDispositivo->FieldByName("CODIGO_FABRICANTE")->AsInteger,DM->TDispositivo->FieldByName("ID")->AsInteger);
}
//---------------------------------------------------------------------------

void __fastcall TFormBD::FormShow(TObject *Sender)
{
        ActualizarHojaComandos();
        ActualizarHojaDispositivos();        
}
//---------------------------------------------------------------------------

