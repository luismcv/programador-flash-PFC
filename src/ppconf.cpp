//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ppconf.h"
#include "pport.h"
#include <IniFiles.hpp>
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TParPortConf *ParPortConf;
//---------------------------------------------------------------------
__fastcall TParPortConf::TParPortConf(TComponent* AOwner)
	: TForm(AOwner)
{
        TPuerto *Puerto;
        int DirBase, Indice;
        Boolean ComprobarTimeout, ConfLeida;

        ConfLeida = PP->LeerConfiguracion(&DirBase,&ComprobarTimeout);
        ListaPuertos = PP->ObtenerListaPuertos();

        CBPort->Items->Clear();
        Indice = -1;
        for (int Cont=0; Cont < ListaPuertos->Count; Cont++)
        {
                Puerto = (TPuerto *)ListaPuertos->Items[Cont];
                CBPort->Items->Add(Puerto->Nombre+ " - 0x"+IntToHex(Puerto->DirBase,4));
                if (DirBase == Puerto->DirBase)
                        Indice = Cont;
        }

        if (ConfLeida & Indice >= 0)
        {
                CBPort->ItemIndex = AntiguoPuerto = Indice;
                CBTimeout->Checked = AntiguaConfTimeout = ComprobarTimeout;
        }
        else
        {
                CBPort->ItemIndex = AntiguoPuerto = 0;
                CBTimeout->Checked = AntiguaConfTimeout = false;
        }
}
//--------------------------------------------------------------------

void __fastcall TParPortConf::OKBtnClick(TObject *Sender)
{
        TPuerto *Puerto;

        Puerto = (TPuerto *)ListaPuertos->Items[CBPort->ItemIndex];

        PP->GrabarConfiguracion(Puerto->DirBase, CBTimeout->Checked);

        PP->Configurar(Puerto->DirBase, CBTimeout->Checked);

        AntiguoPuerto = CBPort->ItemIndex;
        AntiguaConfTimeout = CBTimeout->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TParPortConf::BDetectarTOClick(TObject *Sender)
{
        TPuerto *Puerto;

        Puerto = (TPuerto *)ListaPuertos->Items[CBPort->ItemIndex];
        PP->Configurar(Puerto->DirBase, false);
        MessageDlg("Por favor, desconecte el programador.",mtInformation,TMsgDlgButtons() << mbOK,0);
        CBTimeout->Checked = PP->SaltaTimeout();
        MessageDlg("Ya puede volver a conectarlo.",mtInformation,TMsgDlgButtons() << mbOK,0);
}
//---------------------------------------------------------------------------

void __fastcall TParPortConf::CancelBtnClick(TObject *Sender)
{
        TPuerto *Puerto;

        CBPort->ItemIndex = AntiguoPuerto;
        CBTimeout->Checked = AntiguaConfTimeout;

        Puerto = (TPuerto *)ListaPuertos->Items[AntiguoPuerto];
        PP->Configurar(Puerto->DirBase, AntiguaConfTimeout);
}
//---------------------------------------------------------------------------

