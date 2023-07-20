//---------------------------------------------------------------------------

#ifndef basedatosH
#define basedatosH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <DBCtrls.hpp>
#include <Mask.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>

#define MIN_MEM_TAMANYO 14   // 16Kbit = 2 ^ 14
//---------------------------------------------------------------------------
class TFormBD : public TForm
{
__published:	// IDE-managed Components
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TTabSheet *TabSheet2;
        TTabSheet *TabSheet3;
        TMainMenu *MainMenu1;
        TMenuItem *Salir1;
        TMenuItem *Ayuda1;
        TDBGrid *DBGrid1;
        TDBLookupComboBox *DBLCBJuegoComandos;
        TDBLookupComboBox *DBLCBComando;
        TButton *BCopiarComando;
        TButton *BCopiarJuegoComandos;
        TButton *BEliminarJuegoComandos;
        TButton *BEliminarComando;
        TGroupBox *GroupBox1;
        TGroupBox *GroupBox2;
        TGroupBox *GroupBox3;
        TGroupBox *GBCaract;
        TGroupBox *GBSect;
        TLabel *Label1;
        TDBLookupComboBox *DBLCBFab;
        TDBLookupComboBox *DBLCBMod;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TDBEdit *DBECodFab;
        TDBEdit *DBEIdDisp;
        TButton *BEliminarDisp;
        TLabel *Label5;
        TLabel *Label6;
        TGroupBox *GroupBox6;
        TRadioButton *RBPag;
        TDBLookupComboBox *DBLCBJuegoComandos2;
        TLabel *Label9;
        TButton *BNuevoJuegoComandos;
        TButton *BNuevoComando;
        TButton *BNuevoDisp;
        TDBGrid *DBGSec;
        TComboBox *CBTam;
        TComboBox *CBNumPin;
        TRadioButton *RBRom;
        TRadioButton *RBByte;
        TLabel *Label7;
        TComboBox *CBTamPag;
        TStringGrid *SGSecuencias;
        TLabel *Label8;
        TButton *BCopiarDisp;
        TButton *BGuardarCambiosDisp;
        TButton *BCancelarCambiosDisp;
        TCheckBox *CBDQ7;
        TCheckBox *CBDQ6;
        TCheckBox *CBDQ5;
        TMenuItem *Ayudaprogramador1;
        TMenuItem *Ayudabasededatos1;
        TMenuItem *Acercade1;
        TButton *BInsFab;
        TButton *BDelFab;
        TButton *BInsertSect;
        TButton *BEliminarSect;
        TButton *BExportar;
        TButton *BImportar;
        TOpenDialog *OpenDialog1;
        TSaveDialog *SaveDialog1;
        void __fastcall Salir1Click(TObject *Sender);
        void __fastcall RBByteToggleClick(TObject *Sender);
        void __fastcall RBPagClick(TObject *Sender);
        void __fastcall BNuevoJuegoComandosClick(TObject *Sender);
        void __fastcall DBLCBJuegoComandosClick(TObject *Sender);
        void __fastcall BEliminarJuegoComandosClick(TObject *Sender);
        void __fastcall BCopiarJuegoComandosClick(TObject *Sender);
        void __fastcall BNuevoComandoClick(TObject *Sender);
        void __fastcall BEliminarComandoClick(TObject *Sender);
        void __fastcall BCopiarComandoClick(TObject *Sender);
        void __fastcall DBLCBFabClick(TObject *Sender);
        void __fastcall CBTamChange(TObject *Sender);
        void __fastcall CBNumPinChange(TObject *Sender);
        void __fastcall RBRomClick(TObject *Sender);
        void __fastcall RBByteClick(TObject *Sender);
        void __fastcall CBTamPagChange(TObject *Sender);
        void __fastcall SGSecuenciasGetEditText(TObject *Sender, int ACol,
          int ARow, AnsiString &Value);
        void __fastcall SGSecuenciasKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall SGSecuenciasSelectCell(TObject *Sender, int ACol,
          int ARow, bool &CanSelect);
        void __fastcall SGSecuenciasKeyPress(TObject *Sender, char &Key);
        void __fastcall SGSecuenciasExit(TObject *Sender);
        void __fastcall DBLCBComandoClick(TObject *Sender);
        void __fastcall SGSecuenciasDrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
        void __fastcall BNuevoDispClick(TObject *Sender);
        void __fastcall PageControl1Change(TObject *Sender);
        void __fastcall PageControl1Changing(TObject *Sender,
          bool &AllowChange);
        void __fastcall DBLCBModClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall BEliminarDispClick(TObject *Sender);
        void __fastcall BCancelarCambiosDispClick(TObject *Sender);
        void __fastcall BCopiarDispClick(TObject *Sender);
        void __fastcall BGuardarCambiosDispClick(TObject *Sender);
        void __fastcall CBDQ7Click(TObject *Sender);
        void __fastcall CBDQ6Click(TObject *Sender);
        void __fastcall CBDQ5Click(TObject *Sender);
        void __fastcall Ayudaprogramador1Click(TObject *Sender);
        void __fastcall Ayudabasededatos1Click(TObject *Sender);
        void __fastcall Acercade1Click(TObject *Sender);
        void __fastcall BInsFabClick(TObject *Sender);
        void __fastcall BDelFabClick(TObject *Sender);
        void __fastcall BInsertSectClick(TObject *Sender);
        void __fastcall BEliminarSectClick(TObject *Sender);
        void __fastcall BExportarClick(TObject *Sender);
        void __fastcall BImportarClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations
        AnsiString OldData, TempAddrString, TempDataString;
        Boolean DataChanged,ActualizandoHoja;
        Integer OldColPos,OldRowPos;
        void __fastcall ComprobarCambiosPendientes(void);
        void __fastcall SaveSeqData(void);
        void __fastcall ActualizarHojaComandos(void);
        void __fastcall ActualizarHojaDispositivos(void);
        void __fastcall CancelarCambios(void);
        void __fastcall GuardarCambios(Boolean Borrando);
        void __fastcall IrAFabricante(unsigned char CodFab);
        void __fastcall IrADispositivo(unsigned char CodFab, unsigned char IdDisp);
        int __fastcall NuevoDisp(unsigned char *CodFab, AnsiString *Modelo, unsigned char *IdDisp);
        void __fastcall ExportarDisp(String NombreFich, unsigned char CodFab, unsigned char IdDisp);
        Boolean __fastcall ExisteFab(unsigned char CodFab);
        Boolean __fastcall ExisteDisp(unsigned char CodFab, unsigned char IdDisp);
        Boolean __fastcall ExisteJuegoComandos(unsigned char IdJuego);
        void __fastcall ImportarDisp(String NombreFich, unsigned char &CodFab, unsigned char &IdDisp);
public:		// User declarations
        __fastcall TFormBD(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormBD *FormBD;
//---------------------------------------------------------------------------
#endif
