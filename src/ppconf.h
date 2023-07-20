//----------------------------------------------------------------------------
#ifndef ppconfH
#define ppconfH
//----------------------------------------------------------------------------
#include <vcl\System.hpp>
#include <vcl\Windows.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Controls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ExtCtrls.hpp>
//----------------------------------------------------------------------------
class TParPortConf : public TForm
{
__published:        
	TButton *OKBtn;
	TButton *CancelBtn;
        TComboBox *CBPort;
        TLabel *Label1;
        TCheckBox *CBTimeout;
        void __fastcall OKBtnClick(TObject *Sender);
        void __fastcall BDetectarTOClick(TObject *Sender);
        void __fastcall CancelBtnClick(TObject *Sender);
private:
        TList *ListaPuertos;
        int AntiguoPuerto;
        Boolean AntiguaConfTimeout;
public:
	virtual __fastcall TParPortConf(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TParPortConf *ParPortConf;
//----------------------------------------------------------------------------
#endif    
