//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("programador.res");
USEFORM("princ.cpp", FormPrinc);
USEFORM("basedatos.cpp", FormBD);
USEFORM("datamodule.cpp", DM); /* TDataModule: File Type */
USEUNIT("flash.cpp");
USEFORM("nuevodisp.cpp", FormNDisp);
USEFORM("ppconf.cpp", ParPortConf);
USEFORM("pport.cpp", PP); /* TDataModule: File Type */
USEFORM("acerca_de.cpp", FormAcercaDe);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TFormPrinc), &FormPrinc);
                 Application->CreateForm(__classid(TFormBD), &FormBD);
                 Application->CreateForm(__classid(TDM), &DM);
                 Application->CreateForm(__classid(TFormNDisp), &FormNDisp);
                 Application->CreateForm(__classid(TPP), &PP);
                 Application->CreateForm(__classid(TParPortConf), &ParPortConf);
                 Application->CreateForm(__classid(TFormAcercaDe), &FormAcercaDe);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
