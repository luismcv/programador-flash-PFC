//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "princ.h"
#include "basedatos.h"
#include "datamodule.h"
#include "pport.h"
#include "math.h"
#include "flash.h"
#include "ppconf.h"
#include "acerca_de.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormPrinc *FormPrinc;

//---------------------------------------------------------------------------
__fastcall TFormPrinc::TFormPrinc(TComponent* Owner)
        : TForm(Owner)
{

        /* Preparación tablas sectores */
        int Temp;
        SGSectores->ColWidths[0]=65;
        SGSectores->ColWidths[4]=85;
        SGSectores->ColWidths[1]=110;
        Temp=(SGSectores->Width-285)/2;
        SGSectores->ColWidths[2]=Temp;
        SGSectores->ColWidths[3]=Temp;

        SGSectores->Cells[0][0]="Sector";
        SGSectores->Cells[1][0]="Tamaño";
        SGSectores->Cells[2][0]="Dirección comienzo";
        SGSectores->Cells[3][0]="Dirección final";
        SGSectores->Cells[4][0]="Protegido";

        ListaIdComandos = new TStringList;
        ListaSectores = new TListaSectores;
        ListaComandos = new TListaComandos;
}
//---------------------------------------------------------------------------
__fastcall TFormPrinc::~TFormPrinc(void)
{
        delete ListaIdComandos;
        delete ListaSectores;
        delete ListaComandos;
}
//---------------------------------------------------------------------------
void __fastcall TFormPrinc::Salir1Click(TObject *Sender)
{
        exit(0);
}
//---------------------------------------------------------------------------

void __fastcall TFormPrinc::SGSectoresDrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
  TFont* HeaderFont;
  TFont* CellFont;
  TFont* RowTitleFont;

  HeaderFont=new TFont;
  HeaderFont->Style = HeaderFont->Style << fsBold;

  CellFont=new TFont;   //default font is ms sans serif

  int leftMargin;

if (ARow == 0)
  {
    SGSectores->Canvas->Brush->Color=clBtnFace;
    SGSectores->Canvas->FillRect(Rect);

    SGSectores->Canvas->Font->Assign(HeaderFont);
    leftMargin=(Rect.Right-Rect.Left-SGSectores->Canvas->TextWidth(SGSectores->Cells[ACol][ARow]))/2;
    SGSectores->Canvas->TextOut(Rect.Left+leftMargin,Rect.Top+4,SGSectores->Cells[ACol][ARow]);
    SGSectores->Canvas->Font->Assign(CellFont);
  }
 else
  {
    SGSectores->Canvas->Brush->Color=clWhite;
    SGSectores->Canvas->FillRect(Rect);
    leftMargin=(Rect.Right-Rect.Left-SGSectores->Canvas->TextWidth(SGSectores->Cells[ACol][ARow]))/2;
    SGSectores->Canvas->Font->Assign(CellFont);
    SGSectores->Canvas->TextOut(Rect.Left+leftMargin,Rect.Top+4,SGSectores->Cells[ACol][ARow]);

  }
}

//---------------------------------------------------------------------------
void __fastcall TFormPrinc::Basededatosdememorias1Click(TObject *Sender)
{
        unsigned char AntCodFab, AntIdDisp;

        AntCodFab = DM->TDispositivo->FieldByName("CODIGO_FABRICANTE")->Value;
        AntIdDisp = DM->TDispositivo->FieldByName("ID")->Value;

        FormBD->ShowModal();

        DM->TFabricante->SetKey();
        DM->TFabricante->FieldByName("CODIGO")->Value=AntCodFab;
        DM->TFabricante->GotoKey();

        DM->TDispositivo->SetKey();
        DM->TDispositivo->FieldByName("CODIGO_FABRICANTE")->Value=AntCodFab;
        DM->TDispositivo->FieldByName("ID")->Value=AntIdDisp;
        DM->TDispositivo->GotoKey();

        ActualizarDatos();
}
//---------------------------------------------------------------------------

void __fastcall TFormPrinc::C1Click(TObject *Sender)
{
        ParPortConf->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TFormPrinc::DBLCBFabClick(TObject *Sender)
{
        DM->TFabricante->SetKey();
        DM->TFabricante->FieldByName("CODIGO")->Value=DBLCBFab->KeyValue;
        DM->TFabricante->GotoKey();

        DM->TDispositivo->First();
        ActualizarDatos();
}
//---------------------------------------------------------------------------
void __fastcall TFormPrinc::ActualizarDatos()
{
        char Tamanyos[][24]={"16 KBit (2K x 8-Bit)","32 KBit (4K x 8-Bit)",
                        "64 KBit (8K x 8-Bit)","128 KBit (16K x 8-Bit)",
                        "256 KBit (32K x 8-Bit)","512 KBit (64K x 8-Bit)",
                        "1 MBit (128K x 8-Bit)","2 MBit (256K x 8-Bit)",
                        "4 MBit (512K x 8-Bit)"};
        int i, NumSects, DirIni, DirFin, Tam;

        DBLCBFab->KeyValue=0;
        DBLCBFab->KeyValue=255;
        DBLCBFab->KeyValue=DM->TFabricante->FieldByName("CODIGO")->AsInteger;

        DBLCBMod->KeyValue=0;
        DBLCBMod->KeyValue=255;
        DBLCBMod->KeyValue=DM->TDispositivo->FieldByName("ID")->AsInteger;

        for (int row = 1; row < 7; row++)
                for (int col = 0; col < 5; col++)
                        SGSectores->Cells[col][row]="";

        // Si hay algún dispositivo del fabricante actual
        // mostraremos sus datos
        if(DM->TDispositivo->RecordCount)
        {
                ETamTotal->Text=Tamanyos[(DM->TDispositivo->FieldByName("TAMANYO")->AsInteger)-MIN_MEM_TAMANYO];
                MaxDir = pow(2,DM->TDispositivo->FieldByName("TAMANYO")->AsInteger-3)-1;

                // Obtenemos la lista de comandos
                CBComando->Items->Clear();
                ListaComandos->Borrar();
                ListaIdComandos->Clear();
                DM->TComando->First();
                while (!DM->TComando->Eof)
                {
                        ListaComandos->AnyadirComando(DM->TComando->FieldByName("ID")->AsInteger,
                                        DM->TComando->FieldByName("DESCRIPCION")->AsString,
                                        DM->TComando->FieldByName("SEC_DIREC")->AsString,
                                        DM->TComando->FieldByName("SEC_DATOS")->AsString);

                        if (DM->TComando->FieldByName("ID")->AsInteger > MAX_ID_C_BAS)
                        {
                                CBComando->Items->Add(DM->TComando->FieldByName("DESCRIPCION")->AsString);
                                ListaIdComandos->Add(DM->TComando->FieldByName("ID")->AsString);
                        }
                        DM->TComando->Next();
                }

                // y la de sectores
                DM->TSector->First();
                ListaSectores->Borrar();
                while (!DM->TSector->Eof)
                {
                        ListaSectores->AnyadirSectores(DM->TSector->FieldByName("DIRECCION_COMIENZO")->AsInteger,
                                        DM->TSector->FieldByName("LONGITUD")->AsInteger,
                                        DM->TSector->FieldByName("NUMERO")->AsInteger);

                        DM->TSector->Next();
                }

                CBLSector->Items->Clear();
                CBESector->Items->Clear();
                CBBSector->Items->Clear();
                NumSects = 0;
                ListaSectores->IrInicioLista();
                while (!ListaSectores->Eof())
                {
                        ListaSectores->SectorActual(&DirIni,&DirFin);
                        Tam=DirFin - DirIni + 1;
                        NumSects++;
                        SGSectores->Cells[0][NumSects]=NumSects;
                        SGSectores->Cells[1][NumSects]=Tam;
                        SGSectores->Cells[2][NumSects]="0x"+IntToHex(DirIni,5);
                        SGSectores->Cells[3][NumSects]="0x"+IntToHex(DirFin,5);
                        SGSectores->Cells[4][NumSects]="?";
                        CBLSector->Items->Add("0x"+IntToHex(DirIni,5));
                        ListaSectores->Siguiente();
                }

                SGSectores->RowCount=max(NumSects+1,7);
                ENumSect->Text=NumSects;
                CBESector->Items->AddStrings(CBLSector->Items);
                CBBSector->Items->AddStrings(CBLSector->Items);

                TDatosMemoria DatosMemoria;
                DatosMemoria.TamMem = pow(2,DM->TDispositivo->FieldByName("TAMANYO")->AsInteger-3);
                DatosMemoria.TamPag = pow(2,DM->TDispositivo->FieldByName("TAMANYO_PAGINA")->AsInteger);
                DatosMemoria.Tipo = DM->TDispositivo->FieldByName("TIPO")->AsInteger;
                DatosMemoria.ListaComandos = ListaComandos;
                DatosMemoria.ListaSectores = ListaSectores;

                MemFlash.Configurar(&DatosMemoria);

                if (MemFlash.EsProgramable())
                {
                        TabSheet3->TabVisible=true;
                        TabSheet4->TabVisible=true;
                        TabSheet5->TabVisible=true;
                        if (MemFlash.SoportaConsultaEstadoSectores() && CBLSector->Items->Count)
                                BEstadoSectores->Visible=true;
                        else
                                BEstadoSectores->Visible=false;
                        if (MemFlash.EsPorPaginas())
                                ETipo->Text="Páginas";
                        if (MemFlash.EsByteAByte())
                                ETipo->Text="Byte";

                }
                else
                {
                        TabSheet3->TabVisible=false;
                        TabSheet4->TabVisible=false;
                        TabSheet5->TabVisible=false;
                        BEstadoSectores->Visible=false;
                        ETipo->Text="ROM";
                }

                // Si el dispositivo mostrado no tiene sectores
                // y estaba activada alguna opción de sectores
                // la desactivamos
                if (!CBLSector->Items->Count)
                {
                        if (RBLSector->Checked)
                                RBLMemoria->Checked=true;
                        if (RBESector->Checked)
                                RBEMemoria->Checked=true;
                        RBLSector->Enabled = false;
                        RBESector->Enabled = false;
                }
                else
                {
                        RBLSector->Enabled = true;
                        RBESector->Enabled = true;
                }

                if (!MemFlash.SoportaBorradoSectores() || !CBLSector->Items->Count)
                {
                        RBBMemoria->Checked=true;
                        RBBSector->Enabled=false;
                }
                else
                        RBBSector->Enabled=true;

        }
        // y si no hay ningún dispositivo
        // limpiamos la pantalla
        else
        {
                ETamTotal->Text="";
                SGSectores->RowCount=7;

                ENumSect->Text="";
                CBLSector->Items->Clear();
                CBESector->Items->Clear();
                CBBSector->Items->Clear();
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormPrinc::FormShow(TObject *Sender)
{
        ActualizarDatos();
}
//---------------------------------------------------------------------------

void __fastcall TFormPrinc::RBLByteClick(TObject *Sender)
{
        ELDir->Enabled=true;
        CBLSector->Enabled=false;
        ELDirIni->Enabled=false;
        ELDirFin->Enabled=false;
        ELFichero->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrinc::RBLSectorClick(TObject *Sender)
{
        ELDir->Enabled=false;
        CBLSector->Enabled=true;
        ELDirIni->Enabled=false;
        ELDirFin->Enabled=false;
        ELFichero->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrinc::RBLRangoClick(TObject *Sender)
{
        ELDir->Enabled=false;
        CBLSector->Enabled=false;
        ELDirIni->Enabled=true;
        ELDirFin->Enabled=true;
        ELFichero->Enabled=true;
}

//---------------------------------------------------------------------------

void __fastcall TFormPrinc::RBLMemoriaClick(TObject *Sender)
{
        ELDir->Enabled=false;
        CBLSector->Enabled=false;
        ELDirIni->Enabled=false;
        ELDirFin->Enabled=false;
        ELFichero->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrinc::RBEByteClick(TObject *Sender)
{
        EEDir->Enabled=true;
        CBESector->Enabled=false;
        EEDirIni->Enabled=false;
        EEDirFin->Enabled=false;
        RBEValor->Checked=true;        
}
//---------------------------------------------------------------------------

void __fastcall TFormPrinc::RBESectorClick(TObject *Sender)
{
        EEDir->Enabled=false;
        CBESector->Enabled=true;
        EEDirIni->Enabled=false;
        EEDirFin->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrinc::RBERangoClick(TObject *Sender)
{
        EEDir->Enabled=false;
        CBESector->Enabled=false;
        EEDirIni->Enabled=true;
        EEDirFin->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrinc::RBEMemoriaClick(TObject *Sender)
{
        EEDir->Enabled=false;
        CBESector->Enabled=false;
        EEDirIni->Enabled=false;
        EEDirFin->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrinc::RBBSectorClick(TObject *Sender)
{
        CBBSector->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrinc::RBBMemoriaClick(TObject *Sender)
{
        CBBSector->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrinc::BLExaminarClick(TObject *Sender)
{
        if(SaveDialog1->Execute())
        {
                ELFichero->Text=SaveDialog1->FileName;
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormPrinc::RBLValorClick(TObject *Sender)
{
        ELValor->Enabled=true;
        ELFichero->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrinc::RBLFicheroClick(TObject *Sender)
{
        ELValor->Enabled=false;
        ELFichero->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrinc::BEExaminarClick(TObject *Sender)
{
        if(OpenDialog1->Execute())
        {
                EEFichero->Text=OpenDialog1->FileName;
                RBEFichero->Checked=true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormPrinc::RBEValorClick(TObject *Sender)
{
        EEValor->Enabled=true;
        EEFichero->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrinc::RBEValorAleatorioClick(TObject *Sender)
{
        EEValor->Enabled=false;
        EEFichero->Enabled=false;
        if (RBEByte->Checked)
                RBEMemoria->Checked=true;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrinc::RBEFicheroClick(TObject *Sender)
{
        EEValor->Enabled=false;
        EEFichero->Enabled=true;
        if (RBEByte->Checked)
                RBEMemoria->Checked=true;
}
//---------------------------------------------------------------------------
void __fastcall TFormPrinc::DirKeyPress(TObject *Sender, char &Key)
{
        if (Key ==  VK_RETURN)
        {
                try
                {
                        ((TEdit *)Sender)->Text="0x"+IntToHex(((TEdit *)Sender)->Text.ToInt(),5);
                }
                catch(EConvertError &)
                {
                        MessageDlg("Formato incorrecto.",mtError,TMsgDlgButtons() << mbOK,0);
                }
        }
        if (Key ==  VK_ESCAPE)
                ((TEdit *)Sender)->Text=AntiguaDir;

}
//---------------------------------------------------------------------------

void __fastcall TFormPrinc::DirExit(TObject *Sender)
{
        if (!((TEdit *)Sender)->Text.IsEmpty())
        {
                try
                {
                        ((TEdit *)Sender)->Text="0x"+IntToHex(((TEdit *)Sender)->Text.ToInt(),5);
                }
                catch(EConvertError &)
                {
                        MessageDlg("Formato incorrecto.",mtError,TMsgDlgButtons() << mbOK,0);
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormPrinc::ValorKeyPress(TObject *Sender, char &Key)
{
        if (Key ==  VK_RETURN)
        {
                try
                {
                        ((TEdit *)Sender)->Text="0x"+IntToHex(((TEdit *)Sender)->Text.ToInt(),2);
                }
                catch(EConvertError &)
                {
                        MessageDlg("Formato incorrecto.",mtError,TMsgDlgButtons() << mbOK,0);
                }
        }
        if (Key ==  VK_ESCAPE)
                ((TEdit *)Sender)->Text=AntiguoValor;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrinc::ValorExit(TObject *Sender)
{
        if (!((TEdit *)Sender)->Text.IsEmpty())
        {
                try
                {
                        ((TEdit *)Sender)->Text="0x"+IntToHex(((TEdit *)Sender)->Text.ToInt(),2);
                }
                catch(EConvertError &)
                {
                        MessageDlg("Formato incorrecto.",mtError,TMsgDlgButtons() << mbOK,0);
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormPrinc::BLeerClick(TObject *Sender)
{
        int Dir, DirSector, DirIni, DirFin, Valor;

        // Primero comprobamos que los parámetros necesarios hayan sido introducidos correctamente
        if (RBLByte->Checked)
        {
                try
                {
                        Dir = ELDir->Text.ToInt();
                        if (Dir < 0 || Dir > MaxDir)
                        {
                                MessageDlg("Dirección fuera de rango",mtError,TMsgDlgButtons() << mbOK,0);
                                return;
                        }
                }
                catch(EConvertError &Excepcion)
                {
                        MessageDlg("Debe introducir una dirección válida",mtError,TMsgDlgButtons() << mbOK,0);
                        return;
                }
        }
        if (RBLSector->Checked)
        {
                try
                {
                        DirSector = CBLSector->Items->Strings[CBLSector->ItemIndex].ToInt();
                }
                catch(EConvertError &Excepcion)
                {
                        MessageDlg("Debe elegir un sector válido",mtError,TMsgDlgButtons() << mbOK,0);
                        return;
                }
        }
        if (RBLRango->Checked)
        {
                try
                {
                        DirIni = ELDirIni->Text.ToInt();
                        DirFin = ELDirFin->Text.ToInt();
                        if (DirIni < 0 || DirIni > MaxDir)
                        {
                                MessageDlg("Dirección inicial fuera de rango",mtError,TMsgDlgButtons() << mbOK,0);
                                return;
                        }
                        if (DirFin < 0 || DirFin > MaxDir)
                        {
                                MessageDlg("Dirección inicial fuera de rango",mtError,TMsgDlgButtons() << mbOK,0);
                                return;
                        }
                        if (DirFin <= DirIni )
                        {
                                MessageDlg("La dirección inicial debe ser menor que la final",mtError,TMsgDlgButtons() << mbOK,0);
                                return;
                        }
                }
                catch(EConvertError &Excepcion)
                {
                        MessageDlg("Debe introducir un rango válido",mtError,TMsgDlgButtons() << mbOK,0);
                        return;
                }
        }

        // Ahora pasamos a realizar la operación solicitada
        if (RBLByte->Checked)
        {
                ELValor->Text="0x"+IntToHex((unsigned char)MemFlash.LeerByte(Dir),2);
        }
        else
        {
                ELValor->Text="";
                if (ELFichero->Text.IsEmpty())
                        if(SaveDialog1->Execute())
                                ELFichero->Text=SaveDialog1->FileName;
                        else return;
                if (FileExists(ELFichero->Text))
                        if(MessageDlg("¿Desea sobre escribir el fichero '"+ELFichero->Text+"'?",mtConfirmation,
                                TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo)
                                return;

                StatusBar1->SimpleText="Leyendo...";
                if (RBLSector->Checked)
                        MemFlash.LeerSector(DirSector,ELFichero->Text, BProgreso);
                else if (RBLRango->Checked)
                        MemFlash.LeerRango(DirIni,DirFin,ELFichero->Text,BProgreso);
                else if (RBLMemoria->Checked)
                        MemFlash.LeerMemoria(ELFichero->Text, BProgreso);
        }
        StatusBar1->SimpleText="Lectura finalizada";
}
//---------------------------------------------------------------------------

void __fastcall TFormPrinc::DBLCBModClick(TObject *Sender)
{
        DM->TDispositivo->SetKey();
        DM->TDispositivo->FieldByName("CODIGO_FABRICANTE")->Value=DBLCBFab->KeyValue;
        DM->TDispositivo->FieldByName("ID")->Value=DBLCBMod->KeyValue;
        DM->TDispositivo->GotoKey();

        ActualizarDatos();
}
//---------------------------------------------------------------------------

void __fastcall TFormPrinc::BBorrarClick(TObject *Sender)
{
        int Estado;

        if (RBBSector->Checked)
        {
                if(CBBSector->ItemIndex == -1)
                {
                        MessageDlg("Debe seleccionar un sector.",mtError,TMsgDlgButtons() << mbOK,0);
                        return;
                }
                if(MessageDlg("¿Está seguro de querer borrar el sector '"+CBBSector->Items->Strings[CBBSector->ItemIndex]+"'?",mtConfirmation,
                        TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo)
                        return;
                StatusBar1->SimpleText="Borrando sector...";
                Estado = MemFlash.BorrarSector(CBBSector->Items->Strings[CBBSector->ItemIndex].ToInt());
         }
         else if (RBBMemoria->Checked)
         {
                if(MessageDlg("¿Está seguro de querer borrar la memoria?",mtConfirmation,
                        TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo)
                        return;
                StatusBar1->SimpleText="Borrando memoria...";
                Estado = MemFlash.BorrarMemoria();
         }
         if (Estado == SIN_ERROR)
                  StatusBar1->SimpleText="Borrado finalizado";
         else
                  StatusBar1->SimpleText="Borrado fallido";
}
//---------------------------------------------------------------------------

void __fastcall TFormPrinc::BGrabarClick(TObject *Sender)
{
        int ResGrab = 0;
        Boolean VerifOk;
        int Dir, DirSector, DirIni, DirFin, Valor;

        // Primero comprobamos que los parámetros necesarios hayan sido introducidos correctamente
        if (RBEByte->Checked)
        {
                try
                {
                        Dir = EEDir->Text.ToInt();
                        if (Dir < 0 || Dir > MaxDir)
                        {
                                MessageDlg("Dirección fuera de rango",mtError,TMsgDlgButtons() << mbOK,0);
                                return;
                        }
                }
                catch(EConvertError &Excepcion)
                {
                        MessageDlg("Debe introducir una dirección válida",mtError,TMsgDlgButtons() << mbOK,0);
                        return;
                }
        }
        if (RBESector->Checked)
        {
                try
                {
                        DirSector = CBESector->Items->Strings[CBESector->ItemIndex].ToInt();
                }
                catch(EConvertError &Excepcion)
                {
                        MessageDlg("Debe elegir un sector válido",mtError,TMsgDlgButtons() << mbOK,0);
                        return;
                }
        }
        if (RBERango->Checked)
        {
                try
                {
                        DirIni = EEDirIni->Text.ToInt();
                        DirFin = EEDirFin->Text.ToInt();
                        if (DirIni < 0 || DirIni > MaxDir)
                        {
                                MessageDlg("Dirección inicial fuera de rango",mtError,TMsgDlgButtons() << mbOK,0);
                                return;
                        }
                        if (DirFin < 0 || DirFin > MaxDir)
                        {
                                MessageDlg("Dirección inicial fuera de rango",mtError,TMsgDlgButtons() << mbOK,0);
                                return;
                        }
                        if (DirFin <= DirIni )
                        {
                                MessageDlg("La dirección inicial debe ser menor que la final",mtError,TMsgDlgButtons() << mbOK,0);
                                return;
                        }
                }
                catch(EConvertError &Excepcion)
                {
                        MessageDlg("Debe introducir un rango válido",mtError,TMsgDlgButtons() << mbOK,0);
                        return;
                }
        }
        if (RBEValor->Checked)
        {
                try
                {
                        Valor = EEValor->Text.ToInt();
                        if (Valor < 0 || Valor > 0xFF)
                        {
                                MessageDlg("El valor debe estar comprendido entre 0x00 y 0xFF",mtError,TMsgDlgButtons() << mbOK,0);
                                return;
                        }
                }
                catch(EConvertError &Excepcion)
                {
                        MessageDlg("Debe introducir un valor válido",mtError,TMsgDlgButtons() << mbOK,0);
                        return;
                }
        }


        // Ahora pasamos a realizar la operación solicitada
        if (RBEByte->Checked)
        {
                Valor = EEValor->Text.ToInt();

                ResGrab = MemFlash.EscribirByte(Dir,Valor);

                if (CBVerificar->Checked)
                        VerifOk = (Valor == MemFlash.LeerByte(Dir));
        }
        else if (RBEFichero->Checked)
        {
                if (EEFichero->Text.IsEmpty())
                        if(OpenDialog1->Execute())
                                EEFichero->Text=OpenDialog1->FileName;
                        else return;

                StatusBar1->SimpleText="Grabando...";
                if (RBEMemoria->Checked)
                        ResGrab = MemFlash.EscribirMemoria(EEFichero->Text, BProgreso);
                else if (RBESector->Checked)
                        ResGrab = MemFlash.EscribirSector(DirSector,EEFichero->Text, BProgreso);
                else if (RBERango->Checked)
                        ResGrab = MemFlash.EscribirRango(DirIni,DirFin,EEFichero->Text,BProgreso);

                if (ResGrab==SIN_ERROR && CBVerificar->Checked)
                {
                        StatusBar1->SimpleText="Verificando...";
                        if (RBEMemoria->Checked)
                                VerifOk = MemFlash.VerificarMemoria(EEFichero->Text, BProgreso);
                        else if (RBESector->Checked)
                                VerifOk = MemFlash.VerificarSector(DirSector,EEFichero->Text, BProgreso);
                        else if (RBERango->Checked)
                                VerifOk = MemFlash.VerificarRango(DirIni,DirFin,EEFichero->Text,BProgreso);
                }
        }
        else
        {
                unsigned char Buffer[512*1024]; // Como máximo programaremos memorias de 512KB (4MBits)

                if (RBEValor->Checked)
                        memset(&Buffer,Valor,512*1024);
                else
                {
                        randomize();
                        for (int Cont=0; Cont < 512*1024; Cont++)
                                Buffer[Cont]=rand()%256;
                }

                StatusBar1->SimpleText="Grabando...";
                if (RBEMemoria->Checked)
                        ResGrab = MemFlash.EscribirMemoria((unsigned char*)&Buffer, BProgreso);
                else if (RBESector->Checked)
                        ResGrab = MemFlash.EscribirSector(DirSector,(unsigned char*)&Buffer, BProgreso);
                else if (RBERango->Checked)
                        ResGrab = MemFlash.EscribirRango(DirIni,DirFin,(unsigned char*)&Buffer,BProgreso);

                if (ResGrab==SIN_ERROR && CBVerificar->Checked)
                {
                        StatusBar1->SimpleText="Verificando...";
                        if (RBEMemoria->Checked)
                                VerifOk = MemFlash.VerificarMemoria((unsigned char*)&Buffer, BProgreso);
                        else if (RBESector->Checked)
                                VerifOk = MemFlash.VerificarSector(DirSector,(unsigned char*)&Buffer, BProgreso);
                        else if (RBERango->Checked)
                                VerifOk = MemFlash.VerificarRango(DirIni,DirFin,(unsigned char*)&Buffer,BProgreso);
                }
        }

        if (ResGrab!=SIN_ERROR)
                StatusBar1->SimpleText="Grabación fallida";
        else if (CBVerificar->Checked && !VerifOk)
                StatusBar1->SimpleText="Verificación fallida";
        else
                StatusBar1->SimpleText="Grabación finalizada";
}
//---------------------------------------------------------------------------

void __fastcall TFormPrinc::BAutoidentificarClick(TObject *Sender)
{
        unsigned char ManufCode, DeviceId;

        if (MemFlash.Identificar(&ManufCode,&DeviceId))
        {
                DM->TFabricante->SetKey();
                DM->TFabricante->FieldByName("CODIGO")->Value=ManufCode;
                DM->TFabricante->GotoKey();

                DM->TDispositivo->SetKey();
                DM->TDispositivo->FieldByName("ID")->Value=DeviceId;
                DM->TDispositivo->FieldByName("CODIGO_FABRICANTE")->Value=ManufCode;

                if (!DM->TDispositivo->GotoKey())
                        MessageDlg("El dispositivo ha devuelto los siguientes valores,\npero no se han encontrado en la base de datos.\n\nCód. Fabricante: 0x"+IntToHex(ManufCode,2)+"\nId. dispositivo: 0x"+IntToHex(DeviceId,2),mtInformation,TMsgDlgButtons() << mbOK,0);

                ActualizarDatos();
        }
        else
                MessageDlg("No se pudo identificar la memoria.\nSeleccionela manualmente.",mtWarning,TMsgDlgButtons() << mbOK,0);
}
//---------------------------------------------------------------------------

void __fastcall TFormPrinc::BEjecutarClick(TObject *Sender)
{
        if (CBComando->ItemIndex < 0)
                MessageDlg("Seleccione un comando.",mtWarning,TMsgDlgButtons() << mbOK,0);
        else
                MemFlash.EnviarComando(ListaIdComandos->Strings[CBComando->ItemIndex].ToInt());
}
//---------------------------------------------------------------------------

void __fastcall TFormPrinc::BComprobarBorradoClick(TObject *Sender)
{
         StatusBar1->SimpleText="Comprobando...";
         if (RBBSector->Checked)
         {
                if(CBBSector->ItemIndex == -1)
                        MessageDlg("Debe seleccionar un sector.",mtError,TMsgDlgButtons() << mbOK,0);

                else if (MemFlash.EstaBorradoSector(CBBSector->Items->Strings[CBBSector->ItemIndex].ToInt(), BProgreso))
                        MessageDlg("El sector está borrado.",mtInformation,TMsgDlgButtons() << mbOK,0);
                else
                        MessageDlg("El sector contiene datos.",mtInformation,TMsgDlgButtons() << mbOK,0);
         }
         else if (RBBMemoria->Checked)
         {
                if (MemFlash.EstaBorradaMemoria(BProgreso))
                        MessageDlg("La memoria está borrada.",mtInformation,TMsgDlgButtons() << mbOK,0);
                else
                        MessageDlg("La memoria contiene datos.",mtInformation,TMsgDlgButtons() << mbOK,0);
         }
         StatusBar1->SimpleText="";
}
//---------------------------------------------------------------------------

void __fastcall TFormPrinc::BEstadoSectoresClick(TObject *Sender)
{
        int DirIni, Tam, NumSects, i;

        if (MemFlash.SoportaConsultaEstadoSectores())
        {
                if (!MemFlash.HayFlash())
                {
                        MessageDlg("No se pudo comunicar con la memoria.\nAsegúrese de que todo está bien conectado\ny el programador está encendido.",mtError,TMsgDlgButtons() << mbOK,0);
                        return;
                }

                NumSects=0;
                DM->TSector->First();
                while (!DM->TSector->Eof)
                {
                        DirIni = DM->TSector->FieldByName("DIRECCION_COMIENZO")->AsInteger;
                        Tam = DM->TSector->FieldByName("LONGITUD")->AsInteger;
                        for(i=DM->TSector->FieldByName("NUMERO")->AsInteger;i>0;i--)
                        {
                                NumSects++;
                                SGSectores->Cells[0][NumSects]=NumSects;
                                SGSectores->Cells[1][NumSects]=Tam;
                                SGSectores->Cells[2][NumSects]="0x"+IntToHex(DirIni,5);
                                SGSectores->Cells[3][NumSects]="0x"+IntToHex(DirIni+Tam-1,5);
                                if (MemFlash.SectorProtegido(DirIni))
                                        SGSectores->Cells[4][NumSects]="SI";
                                else
                                        SGSectores->Cells[4][NumSects]="NO";
                                CBLSector->Items->Add("0x"+IntToHex(DirIni,5));
                                DirIni+=Tam;
                        }
                        DM->TSector->Next();
                }
        }
        else
                MessageDlg("Esta memoria no soporta\nesta función.",mtWarning,TMsgDlgButtons() << mbOK,0);
}
//---------------------------------------------------------------------------

void __fastcall TFormPrinc::Ayudaprogramador1Click(TObject *Sender)
{
        AnsiString FicheroAyuda;

        FicheroAyuda=ExtractFileDir(ParamStr(0))+"\\manual\\index.html";
        ShellExecute(0,"open",FicheroAyuda.c_str(),NULL,NULL,SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TFormPrinc::Ayudabasededatos1Click(TObject *Sender)
{
        AnsiString FicheroAyuda;

        FicheroAyuda=ExtractFileDir(ParamStr(0))+"\\manual\\node11.html";
        ShellExecute(0,"open",FicheroAyuda.c_str(),NULL,NULL,SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TFormPrinc::Acercade1Click(TObject *Sender)
{
        FormAcercaDe->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TFormPrinc::PageControl1Change(TObject *Sender)
{
         StatusBar1->SimpleText="";
         BProgreso->Position=0;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrinc::DirEnter(TObject *Sender)
{
        AntiguaDir = ((TEdit *)Sender)->Text;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrinc::ValorEnter(TObject *Sender)
{
        AntiguoValor = ((TEdit *)Sender)->Text;
}
//---------------------------------------------------------------------------


