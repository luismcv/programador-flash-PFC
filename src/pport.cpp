//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "pport.h"
#include <IniFiles.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TDLPortIO"
#pragma resource "*.dfm"
TPP *PP;
//---------------------------------------------------------------------------
__fastcall TPP::TPP(TComponent* Owner)
        : TDataModule(Owner)
{
        int DirBase;
        Boolean ComprobarTimeout;

        // Indicamos que el driver se encuentra en el directorio
        // donde se encuentra nuestro ejecutable y lo iniciamos
        PortIO->DriverPath=ExtractFileDir(ParamStr(0));
        PortIO->OpenDriver();
        if (!PortIO->ActiveHW)
        {
                MessageDlg("Could not open the DriverLINX driver.",
                 mtError, TMsgDlgButtons() << mbOK, 0);
                exit(1);
        }

        ListaPuertos = new TList;

        CrearListaPuertos();

        if (ListaPuertos->Count == 0)
        {
                MessageDlg("No se encontró ningún puerto paralelo",
                 mtError, TMsgDlgButtons() << mbOK, 0);
                exit(1);
        }

        if (LeerConfiguracion(&DirBase, &ComprobarTimeout))
        {
                Configurar(DirBase, ComprobarTimeout);
        }
        else
        {
                // Tomamos el primer puerto como puerto por defecto
                TPuerto *Puerto;
                Puerto = (TPuerto *)ListaPuertos->Items[0];
                Configurar(Puerto->DirBase, true);
        }
}

//---------------------------------------------------------------------------
void __fastcall TPP::BorrarListaPuertos(void)
{
        int Cont;

        for (Cont = 0 ; Cont < ListaPuertos->Count ; Cont++)
                delete ListaPuertos->Items[Cont];

        ListaPuertos->Clear();
}

//---------------------------------------------------------------------------
void __fastcall TPP::CrearListaPuertos(void)
{
        int NumPuertosPorDetectar, DirBase;
        TPuerto *NuevoPuerto;

        BorrarListaPuertos();

        NumPuertosPorDetectar = PP->PrinterPortIO->LPTNumPorts;

        for (int Cont=1; NumPuertosPorDetectar > 0; Cont++)
        {
                PP->PrinterPortIO->LPTNumber = Cont;
                DirBase = PP->PrinterPortIO->LPTBasePort;
                if (DirBase != 0)
                {
                        NuevoPuerto = new TPuerto;
                        NuevoPuerto->Nombre = "LPT"+IntToStr(Cont);
                        NuevoPuerto->DirBase = DirBase;
                        ListaPuertos->Add(NuevoPuerto);
                        NumPuertosPorDetectar--;
                }
        }
}

//---------------------------------------------------------------------------
void __fastcall TPP::Configurar(int NuevoPuertoBase, Boolean ComprobarTimeout)
{
        PuertoBase = NuevoPuertoBase;
        ComprobarTout = ComprobarTimeout;

        // Ponemos el puerto en modo EPP
        PortIO->Port[SPP_CONTROL_PORT]=0x4;
        PortIO->Port[SPP_CONTROL_PORT]=PortIO->Port[SPP_CONTROL_PORT] & 0xDF;
        PortIO->Port[ECP_ECR]=0x80;
}

//---------------------------------------------------------------------------
TList * __fastcall TPP::ObtenerListaPuertos(void)
{
        return ListaPuertos;
}

//---------------------------------------------------------------------------
void __fastcall TPP::EnviarDato(char dato)
{
        PortIO->Port[EPP_DATA_PORT]=dato;

        if (ComprobarTout)
        {
                int Intentos = 1;
                while (ComprobarTimeout() && Intentos < MAX_REP_TIMEOUT)
                {
                        PortIO->Port[EPP_DATA_PORT]=dato;
                        Intentos++;
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TPP::EnviarDireccion(char dir)
{
        PortIO->Port[EPP_ADDR_PORT]=dir;

        if (ComprobarTout)
        {
                int Intentos = 1;
                while (ComprobarTimeout() && Intentos < MAX_REP_TIMEOUT)
                {
                        PortIO->Port[EPP_ADDR_PORT]=dir;
                        Intentos++;
                }
        }
}
//---------------------------------------------------------------------------
char __fastcall TPP::RecibirDato(void)
{
        char Dato;

        Dato = PortIO->Port[EPP_DATA_PORT];

        if (ComprobarTout)
        {
                int Intentos = 1;
                while (ComprobarTimeout() && Intentos < MAX_REP_TIMEOUT)
                {
                        Dato = PortIO->Port[EPP_DATA_PORT];
                        Intentos++;
                }
        }

        return Dato;
}
//---------------------------------------------------------------------------
// ComprobarTimeout()
// Devuelve true si se ha producido timeout y false en caso contrario
Boolean __fastcall TPP::ComprobarTimeout(void)
{
        unsigned char Estado;
        Boolean Timeout = false;

        Estado = PortIO->Port[SPP_STATUS_PORT];

        if (Estado & 0x01)
        {
//                ShowMessage("EPP timeout "); /* ******** */
                Timeout = true;
                // Para limpiar el bit de timeout algunas máquinas requieren
                // hacer una doble lectura
                Estado = PortIO->Port[SPP_STATUS_PORT];
                Estado = PortIO->Port[SPP_STATUS_PORT];
                // otras, escribir un 1
                PortIO->Port[SPP_STATUS_PORT]=Estado | 0x01;
                // otras un 0
                PortIO->Port[SPP_STATUS_PORT]=Estado & 0xFE;
                // Volvemos a comprobar el estado
                Estado = PortIO->Port[SPP_STATUS_PORT];
                if (Estado & 0x01)
                        throw Exception("No se puede limpiar bit de timeout de EPP");
        }

        return Timeout;
}
//---------------------------------------------------------------------------
Boolean __fastcall TPP::LeerConfiguracion(int *DirBase, Boolean *ComprobarTimeout)
{
        AnsiString NombreFichConf;
        TIniFile *FichConf;

        NombreFichConf = ExtractFileDir(ParamStr(0)) + "\\programador.ini";

        if (FileExists(NombreFichConf))
        {
                FichConf = new TIniFile(NombreFichConf);

                *DirBase = FichConf->ReadString("Configuracion PP","Direccion base",0).ToInt();
                *ComprobarTimeout = FichConf->ReadBool("Configuracion PP","Comprobar timeout",true);

                delete FichConf;

                return true;
        }
        else
                return false;

}
//---------------------------------------------------------------------------
void __fastcall TPP::GrabarConfiguracion(int DirBase, Boolean ComprobarTimeout)
{
        TIniFile *FichConf;

        FichConf = new TIniFile(ExtractFileDir(ParamStr(0)) + "\\programador.ini");

        FichConf->WriteString("Configuracion PP","Direccion base","0x"+IntToHex(DirBase,4));
        FichConf->WriteBool("Configuracion PP","Comprobar timeout",ComprobarTimeout);

        delete FichConf;
}
//---------------------------------------------------------------------------
Boolean __fastcall TPP::SaltaTimeout(void)
{
        char Dato;

        // Realizamos una lectura
        Dato = PortIO->Port[EPP_DATA_PORT];

        // y comprobamos si ha saltado el timeout
        return ComprobarTimeout();
}

