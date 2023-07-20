//---------------------------------------------------------------------------

#ifndef princH
#define princH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ExtCtrls.hpp>
#include <DBCtrls.hpp>
#include <Mask.hpp>
#include <Dialogs.hpp>
#include "flash.h"
//---------------------------------------------------------------------------
class TFormPrinc : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
        TMenuItem *Salir1;
        TMenuItem *Ayuda1;
        TStatusBar *StatusBar1;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TTabSheet *TabSheet2;
        TTabSheet *TabSheet3;
        TTabSheet *TabSheet4;
        TMenuItem *Basededatosdememorias1;
        TGroupBox *GroupBox1;
        TGroupBox *GroupBox2;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TEdit *ENumSect;
        TEdit *ETamTotal;
        TLabel *Label5;
        TLabel *Label6;
        TButton *BAutoidentificar;
        TStringGrid *SGSectores;
        TGroupBox *GroupBox7;
        TLabel *Label10;
        TEdit *EEDir;
        TRadioButton *RBEByte;
        TRadioButton *RBESector;
        TComboBox *CBESector;
        TRadioButton *RBERango;
        TEdit *EEDirIni;
        TEdit *EEDirFin;
        TLabel *Label12;
        TLabel *Label13;
        TRadioButton *RBEMemoria;
        TGroupBox *GroupBox8;
        TRadioButton *RBEValor;
        TRadioButton *RBEValorAleatorio;
        TRadioButton *RBEFichero;
        TEdit *EEValor;
        TEdit *EEFichero;
        TButton *BEExaminar;
        TCheckBox *CBVerificar;
        TButton *BGrabar;
        TGroupBox *GroupBox3;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label9;
        TEdit *ELDir;
        TRadioButton *RBLByte;
        TRadioButton *RBLSector;
        TComboBox *CBLSector;
        TRadioButton *RBLRango;
        TEdit *ELDirIni;
        TEdit *ELDirFin;
        TRadioButton *RBLMemoria;
        TGroupBox *GroupBox4;
        TEdit *ELFichero;
        TButton *BLExaminar;
        TButton *BLeer;
        TGroupBox *GroupBox5;
        TRadioButton *RBBSector;
        TComboBox *CBBSector;
        TRadioButton *RBBMemoria;
        TButton *BBorrar;
        TButton *BComprobarBorrado;
        TTabSheet *TabSheet5;
        TGroupBox *GroupBox6;
        TComboBox *CBComando;
        TLabel *Label15;
        TButton *BEjecutar;
        TMenuItem *C1;
        TDBLookupComboBox *DBLCBFab;
        TDBLookupComboBox *DBLCBMod;
        TDBEdit *DBEdit1;
        TDBEdit *DBEdit2;
        TOpenDialog *OpenDialog1;
        TSaveDialog *SaveDialog1;
        TEdit *ELValor;
        TLabel *Label11;
        TLabel *Label14;
        TProgressBar *BProgreso;
        TButton *BEstadoSectores;
        TMenuItem *Ayudaprogramador1;
        TMenuItem *Ayudabasededatos1;
        TMenuItem *Acercade1;
        TLabel *Label16;
        TEdit *ETipo;
        void __fastcall Salir1Click(TObject *Sender);
        void __fastcall SGSectoresDrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
        void __fastcall Basededatosdememorias1Click(TObject *Sender);
        void __fastcall C1Click(TObject *Sender);
        void __fastcall DBLCBFabClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall RBLByteClick(TObject *Sender);
        void __fastcall RBLSectorClick(TObject *Sender);
        void __fastcall RBLRangoClick(TObject *Sender);
        void __fastcall RBLMemoriaClick(TObject *Sender);
        void __fastcall RBEByteClick(TObject *Sender);
        void __fastcall RBESectorClick(TObject *Sender);
        void __fastcall RBERangoClick(TObject *Sender);
        void __fastcall RBEMemoriaClick(TObject *Sender);
        void __fastcall RBBSectorClick(TObject *Sender);
        void __fastcall RBBMemoriaClick(TObject *Sender);
        void __fastcall BLExaminarClick(TObject *Sender);
        void __fastcall RBLValorClick(TObject *Sender);
        void __fastcall RBLFicheroClick(TObject *Sender);
        void __fastcall BEExaminarClick(TObject *Sender);
        void __fastcall RBEValorClick(TObject *Sender);
        void __fastcall RBEValorAleatorioClick(TObject *Sender);
        void __fastcall RBEFicheroClick(TObject *Sender);
        void __fastcall DirKeyPress(TObject *Sender, char &Key);
        void __fastcall DirExit(TObject *Sender);
        void __fastcall ValorKeyPress(TObject *Sender, char &Key);
        void __fastcall ValorExit(TObject *Sender);
        void __fastcall BLeerClick(TObject *Sender);
        void __fastcall DBLCBModClick(TObject *Sender);
        void __fastcall BBorrarClick(TObject *Sender);
        void __fastcall BGrabarClick(TObject *Sender);
        void __fastcall BAutoidentificarClick(TObject *Sender);
        void __fastcall BEjecutarClick(TObject *Sender);
        void __fastcall BComprobarBorradoClick(TObject *Sender);
        void __fastcall BEstadoSectoresClick(TObject *Sender);
        void __fastcall Ayudaprogramador1Click(TObject *Sender);
        void __fastcall Ayudabasededatos1Click(TObject *Sender);
        void __fastcall Acercade1Click(TObject *Sender);
        void __fastcall PageControl1Change(TObject *Sender);
        void __fastcall DirEnter(TObject *Sender);
        void __fastcall ValorEnter(TObject *Sender);
private:	// User declarations
        TStringList *ListaIdComandos;
        TListaSectores *ListaSectores;
	TListaComandos *ListaComandos;
        TFlash MemFlash;
        int MaxDir;
        String AntiguaDir, AntiguoValor;
        void __fastcall ActualizarDatos(void);
public:		// User declarations
        __fastcall TFormPrinc(TComponent* Owner);
        __fastcall ~TFormPrinc(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormPrinc *FormPrinc;
//---------------------------------------------------------------------------
#endif
