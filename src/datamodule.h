//---------------------------------------------------------------------------

#ifndef datamoduleH
#define datamoduleH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
#include "TDLPortIO.h"
//---------------------------------------------------------------------------
class TDM : public TDataModule
{
__published:	// IDE-managed Components
        TDatabase *Database1;
        TTable *TFabricante;
        TDataSource *DSFabricante;
        TTable *TJuegoComandos;
        TTable *TComando;
        TDataSource *DSJuegoComando;
        TDataSource *DSComando;
        TTable *TDispositivo;
        TDataSource *DSDispositivo;
        TTable *TJuegoComandosAux;
        TTable *TComandoAux;
        TTable *TFabricanteAux;
        TDataSource *DSFabricanteAux;
        TTable *TSector;
        TDataSource *DSListaSectores;
        TIntegerField *TSectorLONGITUD;
        TStringField *TSectorDIRECCION_FINAL;
        TSmallintField *TSectorCODIGO_FABRICANTE;
        TSmallintField *TSectorID_DISPOSITIVO;
        TIntegerField *TSectorDIRECCION_COMIENZO;
        TSmallintField *TDispositivoCODIGO_FABRICANTE;
        TStringField *TDispositivoNOMBRE;
        TSmallintField *TDispositivoNUM_PINES;
        TSmallintField *TDispositivoTIPO;
        TSmallintField *TDispositivoJUEGO_COMANDOS;
        TIntegerField *TDispositivoTAMANYO;
        TIntegerField *TDispositivoTAMANYO_PAGINA;
        TSmallintField *TDispositivoID;
        TSmallintField *TFabricanteAuxCODIGO;
        TStringField *TFabricanteAuxNOMBRE;
        TSmallintField *TFabricanteCODIGO;
        TStringField *TFabricanteNOMBRE;
        TIntegerField *TSectorNUMERO;
        TStringField *TSectorLONGITUD_TOTAL;
        TTable *TDispositivoAux;
        TTable *TSectorAux;
        TTable *TFabricanteInt;
        TDataSource *DSFabricanteInt;
        TTable *TDispositivoInt;
        TDataSource *DSDispositivoInt;
        TDataSource *DSJuegoComandosInt;
        TTable *TJuegoComandosInt;
        TTable *TComandoInt;
        TDataSource *DSComandoInt;
        void __fastcall TSectorCalcFields(TDataSet *DataSet);
        void __fastcall T8bitsHexGetText(TField *Sender, AnsiString &Text,
          bool DisplayText);
        void __fastcall T8bitsHexSetText(TField *Sender,
          const AnsiString Text);
        void __fastcall T20bitsHexGetText(TField *Sender,
          AnsiString &Text, bool DisplayText);
        void __fastcall T20bitsSetText(TField *Sender,
          const AnsiString Text);
        void __fastcall TSectorAfterInsert(TDataSet *DataSet);
        void __fastcall TSectorBeforeInsert(TDataSet *DataSet);
private:	// User declarations
public:		// User declarations
        __fastcall TDM(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDM *DM;
//---------------------------------------------------------------------------
#endif
