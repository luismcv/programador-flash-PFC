//---------------------------------------------------------------------------

#ifndef pportH
#define pportH

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TDLPortIO.h"

//---------------------------------------------------------------------------

#define SPP_DATA_PORT (PuertoBase)
#define SPP_STATUS_PORT (PuertoBase + 0x1)
#define SPP_CONTROL_PORT (PuertoBase + 0x2)
#define EPP_ADDR_PORT (PuertoBase + 0x3)
#define EPP_DATA_PORT (PuertoBase + 0x4)
#define ECP_ECR (PuertoBase + 0x402)

#define MAX_REP_TIMEOUT 30

typedef struct
{
        String Nombre;
        int DirBase;
} TPuerto;

//---------------------------------------------------------------------------
class TPP : public TDataModule
{
__published:	// IDE-managed Components
        TDLPortIO *PortIO;
        TDLPrinterPortIO *PrinterPortIO;
private:	// User declarations
        int PuertoBase;
        Boolean ComprobarTout;
        TList *ListaPuertos;
        void __fastcall BorrarListaPuertos(void);
        void __fastcall CrearListaPuertos(void);
public:		// User declarations
        __fastcall TPP(TComponent* Owner);
        TList * __fastcall ObtenerListaPuertos(void);
        void __fastcall Configurar(int PuertoBase, Boolean ComprobarTimeout);
        void __fastcall EnviarDato(char dato);
        void __fastcall EnviarDireccion(char dir);
        char __fastcall RecibirDato(void);
        Boolean __fastcall ComprobarTimeout(void);
        Boolean __fastcall LeerConfiguracion(int *DirBase, Boolean *ComprobarTimeout);
        void __fastcall GrabarConfiguracion(int DirBase, Boolean ComprobarTimeout);
        Boolean __fastcall SaltaTimeout(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TPP *PP;
//---------------------------------------------------------------------------
#endif
