//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "flash.h"
#include "math.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

#define MIN(x,y)	x<y?x:y
#define MAX(x,y)	x>y?x:y

// ----------------------------------------------------------------------------
// Clase TListaSectores
// ----------------------------------------------------------------------------
TListaSectores::TListaSectores(void)
{
        LSectores = new TList;
        PosicionActual = 0;
}

TListaSectores::~TListaSectores(void)
{
        Borrar();

        delete LSectores;
}

void TListaSectores::Borrar(void)
{
        int Cont;

        for (Cont = 0 ; Cont < LSectores->Count ; Cont++)
                delete LSectores->Items[Cont];

        LSectores->Clear();
        PosicionActual = 0;
}

int TListaSectores::NumSectores(void)
{
        return LSectores->Count;
}

Boolean TListaSectores::Eof(void)
{
        return (PosicionActual >= LSectores->Count);
}

int TListaSectores::BuscaSector(int Dir)
{
        int Cont, DirIni, DirFin;
        TSector *Sector;
        Boolean Encontrado;

        Cont = 0;
        Encontrado=false;
        while (Cont < LSectores->Count && !Encontrado)
        {
                Sector = (TSector*)LSectores->Items[Cont];
                DirIni = Sector->DirIni;
                DirFin = Sector->DirFin;
                if (Dir >= DirIni && Dir <= DirFin)
                        Encontrado=true;
                else
                        Cont++;
        }

        return Cont;
}

void TListaSectores::AnyadirSector(int DirIni, int DirFin)
{
        TSector *Sector;
        int Posicion;

        Sector = new TSector;

        Sector->DirIni = DirIni;
        Sector->DirFin = DirFin;

        Posicion = BuscaSector(DirIni)+1;
        if (Posicion > LSectores->Count)
                LSectores->Add(Sector);
        else
                LSectores->Insert(Posicion,Sector);
}

void TListaSectores::AnyadirSectores(int DirIni, int Tamanyo, int Numero)
{
        int DirIniTemp;

        DirIniTemp = DirIni;
        while (Numero > 0)
        {
                AnyadirSector(DirIniTemp, DirIniTemp + Tamanyo - 1);
                DirIniTemp+=Tamanyo;
                Numero--;
        }
}

void TListaSectores::IrInicioLista(void)
{
        PosicionActual = 0;
}

void TListaSectores::Siguiente(void)
{
        PosicionActual++;
}

// Devuelve la dirección de Inicio y Fin de un sector dado
void TListaSectores::SectorNum(int Indice, int *DirIni, int *DirFin)
{
        TSector *Sector;

        Sector = (TSector *)(LSectores->Items[Indice]);
        *DirIni = Sector->DirIni;
        *DirFin = Sector->DirFin;
}

void TListaSectores::SectorActual(int *DirIni, int *DirFin)
{
        SectorNum(PosicionActual, DirIni, DirFin);
}

void TListaSectores::SectorDir(int Dir, int *DirIni, int *DirFin)
{
        SectorNum(BuscaSector(Dir), DirIni, DirFin);
}

// ----------------------------------------------------------------------------
// Clase TListaComandos
// ----------------------------------------------------------------------------
TListaComandos::TListaComandos(void)
{
        LComandos = new TList;
        PosicionComandoActual = 0;
        PosicionCicloActual = 0;
}

TListaComandos::~TListaComandos(void)
{
        Borrar();
        delete LComandos;
}

void TListaComandos::Borrar(void)
{
        int Cont, ContCiclos;
        TComando *Comando;

        for (Cont = 0 ; Cont < LComandos->Count ; Cont++)
        {
                Comando = (TComando *)LComandos->Items[Cont];
                for (ContCiclos = 0; ContCiclos > Comando->Ciclos->Count; ContCiclos++)
                        delete Comando->Ciclos->Items[ContCiclos];
                delete Comando->Ciclos;
                delete LComandos->Items[Cont];
        }
        LComandos->Clear();
        PosicionComandoActual = 0;
        PosicionCicloActual = 0;
}

int TListaComandos::NumComandos(void)
{
        return LComandos->Count;
}

int TListaComandos::NumCiclos(void)
{
        TComando *Comando;

        Comando=(TComando *)LComandos->Items[PosicionComandoActual];

        return Comando->Ciclos->Count;
}

// Devuelve true si ya no hay más comandos
Boolean TListaComandos::EofComandos(void)
{
        return (PosicionComandoActual >= LComandos->Count);
}

// Devuelve true si ya no hay más ciclos
Boolean TListaComandos::EofCiclos(void)
{
        TComando *Comando;

        Comando=(TComando *)LComandos->Items[PosicionComandoActual];

        return (PosicionCicloActual >= Comando->Ciclos->Count);
}

void TListaComandos::AnyadirComando(int Id, String Descripcion, String SecDirec, String SecDatos)
{
        int PosSepDirec, PosSepDatos;
        TComando *Comando;
        TCiclo *Ciclo;
        AnsiString Subcadena;

        Comando = new TComando;
        Comando->Id = Id;
        Comando->Descripcion = Descripcion;
        Comando->Ciclos = new TList;

        LComandos->Add(Comando);

        PosSepDirec=SecDirec.AnsiPos(";");
        PosSepDatos=SecDatos.AnsiPos(";");
        while (PosSepDirec && PosSepDatos)
        {
                if (PosSepDirec > 1 && PosSepDatos > 1)
                {
                        Ciclo = new TCiclo;

                        Subcadena = SecDirec.SubString(1,PosSepDirec-1);
                        if (Subcadena.AnsiCompareIC("SA")==0)
                                Ciclo->Dir=CMDSectorAddress;
                        else
                                Ciclo->Dir=Subcadena.ToInt();
                        SecDirec=SecDirec.SubString(PosSepDirec+1,SecDirec.Length()-PosSepDirec);
                        PosSepDirec=SecDirec.AnsiPos(";");

                        Ciclo->Dato=SecDatos.SubString(1,PosSepDatos-1).ToInt();
                        SecDatos=SecDatos.SubString(PosSepDatos+1,SecDatos.Length()-PosSepDatos);
                        PosSepDatos=SecDatos.AnsiPos(";");

                        Comando->Ciclos->Add(Ciclo);
                }
                else
                        break;
        }
}

int TListaComandos::BuscaComando(int Id)
{
        int Cont;
        TComando *Comando;

        Cont = LComandos->Count;
        while (Cont)
        {
                Cont--;
                Comando = (TComando *)LComandos->Items[Cont];
                if (Comando->Id == Id)
                        return Cont;
        }

        throw Exception("ERROR INTERNO: No se encontró el comando solicitado");
}

void TListaComandos::IrAComando(int Id)
{
        PosicionComandoActual = BuscaComando(Id);
        PosicionCicloActual = 0;
}

void TListaComandos::IrInicioListaComandos(void)
{
        PosicionComandoActual = 0;
        PosicionCicloActual = 0;
}

void TListaComandos::IrInicioListaCiclos(void)
{
        PosicionCicloActual = 0;
}

void TListaComandos::SiguienteComando(void)
{
        PosicionComandoActual++;
}

void TListaComandos::SiguienteCiclo(void)
{
        PosicionCicloActual++;
}

void TListaComandos::CicloActual(int *Dir, unsigned char *Dato)
{
        TComando *Comando;
        TCiclo *Ciclo;

        Comando = (TComando *)LComandos->Items[PosicionComandoActual];
        Ciclo = (TCiclo *)Comando->Ciclos->Items[PosicionCicloActual];

        *Dir = Ciclo->Dir;
        *Dato = Ciclo->Dato;
}

// ----------------------------------------------------------------------------
// Clase TFlash
// ----------------------------------------------------------------------------
TFlash::TFlash(void)
{
}

TFlash::~TFlash(void)
{
}

void TFlash::EnviarDireccion(int Dir)
{
        unsigned char PA[3];

//        ShowMessage("Enviando direccion: 0x"+IntToHex(Dir,5));

        PA[0]=(Dir >> 16) & 0xFF;
        PA[1]=(Dir >> 8) & 0xFF;
        PA[2]=Dir & 0xFF;

        PP->EnviarDireccion(PA[0]);
        PP->EnviarDireccion(PA[1]);
        PP->EnviarDireccion(PA[2]);
}

void TFlash::EnviarDato(unsigned char Dato)
{
//        ShowMessage("Enviando dato: 0x"+IntToHex(Dato,2));

        PP->EnviarDato(Dato);
}

unsigned char TFlash::RecibirDato(void)
{
        return PP->RecibirDato();
}

Boolean TFlash::Identificar(unsigned char *ManufCode, unsigned char *DeviceId)
{
        unsigned char Pos0, Pos1;

        // Primero leemos las posiciones de memoria 0x00000, 0x00001
        // para compararlas luego
        EnviarDireccion(0x0);
        Pos0 = RecibirDato();

        EnviarDireccion(0x1);
        Pos1 = RecibirDato();

        // Enviamos comando de identificación al estilo AMD
        EnviarDireccion(0x555);
        EnviarDato(0xAA);

        EnviarDireccion(0x2AA);
        EnviarDato(0x55);

        EnviarDireccion(0x555);
        EnviarDato(0x90);

        // Algunas memorias necesitan 10ms para cambiar de modo
        Sleep(10);

        // Leemos los códigos
        EnviarDireccion(0x0);
        *ManufCode = RecibirDato();

        EnviarDireccion(0x1);
        *DeviceId = RecibirDato();

        if (*ManufCode == 0x7F && *DeviceId == 0x7F)
        {
                // Entonces se trata de una memoria EON o similar
                // Debemos leer los códigos extendidos
                EnviarDireccion(0x100);
                *ManufCode = RecibirDato();

                EnviarDireccion(0x101);
                *DeviceId = RecibirDato();

                EnviarDato(0xF0);

                return true;
        }

        // Comprobamos que efectivamente estamos leyendo los códigos de identificación
        // y no las direcciones de memoria 0x00000 y 0x00001
        if (*ManufCode != Pos0 || *DeviceId != Pos1)
        {
                EnviarDato(0xF0);
                return true;
        }

        // Algunas memorias usan unos comandos alternativos, probemos con ellos
        EnviarDireccion(0x5555);
        EnviarDato(0xAA);

        EnviarDireccion(0x2AAA);
        EnviarDato(0x55);

        EnviarDireccion(0x5555);
        EnviarDato(0x90);

        // Algunas memorias necesitan 10ms para cambiar de modo
        Sleep(10);

        // Leemos los códigos
        EnviarDireccion(0x0);
        *ManufCode = RecibirDato();

        EnviarDireccion(0x1);
        *DeviceId = RecibirDato();

        // Secuencia de salida modo AutoId
        EnviarDireccion(0x5555);
        EnviarDato(0xAA);

        EnviarDireccion(0x2AAA);
        EnviarDato(0x55);

        EnviarDireccion(0x5555);
        EnviarDato(0xF0);

        Sleep(10);

        // Comprobamos que efectivamente estamos leyendo los códigos de identificación
        // y no las direcciones de memoria 0x00000 y 0x00001
        if (*ManufCode != Pos0 || *DeviceId != Pos1)
                return true;

        // Probemos si usa el juego de comandos antiguo de Winbond
        EnviarDireccion(0x5555);
        EnviarDato(0xAA);

        EnviarDireccion(0x2AAA);
        EnviarDato(0x55);

        EnviarDireccion(0x5555);
        EnviarDato(0x80);

        EnviarDireccion(0x5555);
        EnviarDato(0xAA);

        EnviarDireccion(0x2AAA);
        EnviarDato(0x55);

        EnviarDireccion(0x5555);
        EnviarDato(0x60);

        // Algunas memorias necesitan 10ms para cambiar de modo
        Sleep(10);

        // Leemos los códigos
        EnviarDireccion(0x0);
        *ManufCode = RecibirDato();

        EnviarDireccion(0x1);
        *DeviceId = RecibirDato();

        // Secuencia de salida modo AutoId
        EnviarDireccion(0x5555);
        EnviarDato(0xAA);

        EnviarDireccion(0x2AAA);
        EnviarDato(0x55);

        EnviarDireccion(0x5555);
        EnviarDato(0xF0);

        Sleep(10);

        // Comprobamos que efectivamente estamos leyendo los códigos de identificación
        // y no las direcciones de memoria 0x00000 y 0x00001
        if (*ManufCode != Pos0 || *DeviceId != Pos1)
                return true;

        // Si lo anterior falla regresamos
        return false;
}

// Intenta descubrir si hay alguna flash conectada al programador
// y éste está encendido
Boolean TFlash::HayFlash(void)
{
        unsigned char Pos0a, Pos0b, Pos1a, Pos1b, Pos2a, Pos2b;
        unsigned char ManufCode, DeviceId;

        // Si sabemos el comando de AutoID específico de
        // esta memoria lo usamos
        if (SoportaConsultaEstadoSectores())
        {
                // Primero leemos las posiciones de memoria 0x00000, 0x00001
                // y 0x00002 para compararlas luego
                EnviarDireccion(0x0);
                Pos0a = RecibirDato();

                EnviarDireccion(0x1);
                Pos1a = RecibirDato();

                EnviarDireccion(0x2);
                Pos2a = RecibirDato();

                EnviarComando(C_SECT_PROTECT_VERIF);

                // Algunas memorias necesitan 10ms para cambiar de modo
                Sleep(10);

                EnviarDireccion(0x0);
                Pos0b = RecibirDato();

                EnviarDireccion(0x1);
                Pos1b = RecibirDato();

                EnviarDireccion(0x2);
                Pos2b = RecibirDato();

                EnviarComando(C_RESET);

                Sleep(10);

                if (Pos0a != Pos0b || Pos1a != Pos1b || Pos2a != Pos2b)
                        return true;
        }

        // Si no, probamos identificarla. Si lo conseguimos, lógicamente
        // es que hay una memoria conectada
        if (Identificar(&ManufCode,&DeviceId))
                return true;

        return false;
}

void TFlash::Configurar(TDatosMemoria *DatosMemoria)
{
        TamMem = DatosMemoria->TamMem;
        TamPag = DatosMemoria->TamPag;
        Tipo = DatosMemoria->Tipo;
        ListaSectores = DatosMemoria->ListaSectores;
        ListaComandos = DatosMemoria->ListaComandos;
}

Boolean TFlash::EsProgramable(void)
{
        return ES_PROGRAMABLE(Tipo);
}

Boolean TFlash::EsPorPaginas(void)
{
        return ES_POR_PAGINAS(Tipo);
}

Boolean TFlash::EsByteAByte(void)
{
        return (!ES_POR_PAGINAS(Tipo));
}

void TFlash::EnviarComando(int Id)
{
        int Dir;
        unsigned char Dato;

        ListaComandos->IrAComando(Id);

        while (!ListaComandos->EofCiclos())
        {
                ListaComandos->CicloActual(&Dir,&Dato);
                ListaComandos->SiguienteCiclo();

                EnviarDireccion(Dir);
                EnviarDato(Dato);
        }
}

void TFlash::EnviarComando(int Id, int Parametro)
{
        int Dir;
        unsigned char Dato;

        ListaComandos->IrAComando(Id);

        while (!ListaComandos->EofCiclos())
        {
                ListaComandos->CicloActual(&Dir,&Dato);
                ListaComandos->SiguienteCiclo();

                if (Dir & CMDSectorAddress)
                        EnviarDireccion(Parametro);
                else
                        EnviarDireccion(Dir);
                EnviarDato(Dato);
        }
}

unsigned char TFlash::LeerByte(int Dir)
{
	unsigned char Dato;

	EnviarComando(C_READ);
	EnviarDireccion(Dir);
	Dato=RecibirDato();

	return Dato;
}

int TFlash::EscribirByte(int Dir, unsigned char Dato)
{
	int DirPag;
	unsigned char *Pagina;
	int ResGrab;

	if ES_POR_PAGINAS(Tipo)
	{
		DirPag = (Dir / TamPag) * TamPag; // Calculamos la dirección del
                                                  // primer byte de la página

		Pagina = (unsigned char *)malloc(TamPag);

		LeerPagina(DirPag, Pagina);
		Pagina[Dir - DirPag] = Dato;
		ResGrab = EscribirPagina(DirPag,Pagina);

		free(Pagina);
	}
	else
	{
		EnviarComando(C_PROGRAM);
		EnviarDireccion(Dir);
		EnviarDato(Dato);
		ResGrab=EsperarProgramacion(TMAX_BYTE_PROG,Dato);
	}

	return ResGrab;
}

void TFlash::LeerPagina(int Dir, unsigned char *Datos)
{
	int Cont;

	Dir = (Dir / TamPag) * TamPag; // Calculamos la Dirección del primer byte de la página

	for(Cont = 0 ; Cont < TamPag ; Cont++, Dir++)
	{
		Datos[Cont] = LeerByte(Dir);
	}
}

int TFlash::EscribirPagina(int Dir, unsigned char *Datos)
{
	int Cont, Intentos;
	Boolean ResGrab, CmpOk;

	Dir = (Dir / TamPag) * TamPag; // Calculamos la Dirección del primer byte de la página

	CmpOk = false;
	ResGrab = SIN_ERROR;
        Intentos = 0;
        // Mientras no se consiga grabar correctamente la página y no alcancemos
        // el número máximo de intentos...
	while (!CmpOk && (Intentos < MAX_INTENTOS_PAGE_PROG))
	{
                Intentos++;
                // Pasamos el proceso a prioridad de tiempo real
                SetPriorityClass(GetCurrentProcess(),REALTIME_PRIORITY_CLASS);
		EnviarComando(C_PROGRAM);
		for(Cont = 0 ; Cont < TamPag ; Cont++, Dir++)
		{
			EnviarDireccion(Dir);
			EnviarDato(Datos[Cont]);
		}
                // Volvemos a prioridad normal
                SetPriorityClass(GetCurrentProcess(),NORMAL_PRIORITY_CLASS);
		EsperarTblco();
		ResGrab=EsperarProgramacion(TMAX_PAGE_PROG,Datos[Cont]);
                // Verificamos que la página se ha grabado completa
                // ya que ni siquiera la prioridad de tiempo real nos
                // garantiza que se envíen todos los datos sin retraso
		if (ResGrab == NO_ERROR)
                        CmpOk = VerificarPagina(Dir,Datos);
                else
                        CmpOk = false;
	}

        if (Intentos >= MAX_INTENTOS_PAGE_PROG)
                return ERROR_MAX_INT;
        else
        	return ResGrab;
}

Boolean TFlash::VerificarPagina(int Dir, unsigned char *Datos)
{
	int Cont;
	Boolean CmpOk;
	unsigned char Dato;

	Dir = (Dir / TamPag) * TamPag; // Calculamos la Dirección del primer byte de la página

	Cont=0;
	CmpOk=true;

	while (CmpOk && Cont<TamPag)
	{
		Dato = LeerByte(Dir);
		CmpOk = ( Dato == Datos[Cont] );
		Cont++;
		Dir++;
	}

	return CmpOk;
}

void TFlash::LeerSector(int Dir, unsigned char *Datos, TProgressBar *BProgreso)
{
        int DirIni, DirFin;

        ListaSectores->SectorDir(Dir, &DirIni, &DirFin);

        LeerRango(DirIni, DirFin, Datos, BProgreso);
}

void TFlash::LeerSector(int Dir, AnsiString NombreFichero, TProgressBar *BProgreso)
{
        int DirIni, DirFin;

        ListaSectores->SectorDir(Dir, &DirIni, &DirFin);

        LeerRango(DirIni, DirFin, NombreFichero, BProgreso);
}

int TFlash::EscribirSector(int Dir, unsigned char *Datos, TProgressBar *BProgreso)
{
        int DirIni, DirFin;

        ListaSectores->SectorDir(Dir, &DirIni, &DirFin);

        return EscribirRango(DirIni, DirFin, Datos, BProgreso);
}

int TFlash::EscribirSector(int Dir, AnsiString NombreFichero, TProgressBar *BProgreso)
{
        int DirIni, DirFin;

        ListaSectores->SectorDir(Dir, &DirIni, &DirFin);

        return EscribirRango(DirIni, DirFin, NombreFichero, BProgreso);
}

Boolean TFlash::VerificarSector(int Dir, unsigned char *Datos, TProgressBar *BProgreso)
{
        int DirIni, DirFin;

        ListaSectores->SectorDir(Dir, &DirIni, &DirFin);

        return VerificarRango(DirIni, DirFin, Datos, BProgreso);
}

Boolean TFlash::VerificarSector(int Dir, AnsiString NombreFichero, TProgressBar *BProgreso)
{
        int DirIni, DirFin;

        ListaSectores->SectorDir(Dir, &DirIni, &DirFin);

        return VerificarRango(DirIni, DirFin, NombreFichero , BProgreso);
}

void TFlash::LeerMemoria(unsigned char *Datos, TProgressBar *BProgreso)
{
	LeerRango(0, TamMem-1, Datos, BProgreso);
}

void TFlash::LeerMemoria(AnsiString NombreFichero, TProgressBar *BProgreso)
{
	LeerRango(0, TamMem-1, NombreFichero, BProgreso);
}

int TFlash::EscribirMemoria(unsigned char *Datos, TProgressBar *BProgreso)
{
	return EscribirRango(0, TamMem-1, Datos, BProgreso);
}

int TFlash::EscribirMemoria(AnsiString NombreFichero, TProgressBar *BProgreso)
{
	return EscribirRango(0, TamMem-1, NombreFichero, BProgreso);
}

Boolean TFlash::VerificarMemoria(unsigned char *Datos, TProgressBar *BProgreso)
{
	return VerificarRango(0, TamMem-1, Datos, BProgreso);
}

Boolean TFlash::VerificarMemoria(AnsiString NombreFichero, TProgressBar *BProgreso)
{
	return VerificarRango(0, TamMem-1, NombreFichero, BProgreso);
}

void TFlash::LeerRango(int DirIni, int DirFin, unsigned char *Datos, TProgressBar *BProgreso)
{
	int Dir,Cont,IntervaloBP;

        BProgreso->Min = 0;
        BProgreso->Max = DirFin;
        BProgreso->Min = DirIni;
        IntervaloBP = MAX(1,((DirFin - DirIni) / 20));

	for (Dir = DirIni, Cont = 0; Dir <= DirFin; Dir++, Cont++)
        {
		Datos[Cont] = LeerByte(Dir);
                if ( Dir % IntervaloBP == 0)
                        BProgreso->Position = Dir;
        }
}

void TFlash::LeerRango(int DirIni, int DirFin, AnsiString NombreFichero, TProgressBar *BProgreso)
{
        int TamBuffer, Fich;
        unsigned char *Buffer;

        TamBuffer = DirFin - DirIni + 1;

        Buffer = (unsigned char *)malloc(TamBuffer);

        LeerRango(DirIni,DirFin,Buffer, BProgreso);

        if (FileExists(NombreFichero))
                DeleteFile(NombreFichero);
        Fich = FileCreate(NombreFichero);
        FileWrite(Fich,Buffer,TamBuffer);
        FileClose(Fich);

        free(Buffer);
}

int TFlash::EscribirRango(int DirIni, int DirFin, unsigned char *Datos, TProgressBar *BProgreso)
{
        int Dir, IndiceDatos, IndicePagina, PaginaInicial, PaginaFinal, Ini, Fin, IntervaloBP;
        int ResGrab;
	unsigned char *Pagina;

        BProgreso->Min = 0;
        BProgreso->Max = DirFin;
        BProgreso->Min = DirIni;
        IntervaloBP = MAX(1,((DirFin - DirIni) / 20));

        if (ES_POR_PAGINAS(Tipo))
        {
		PaginaInicial = (DirIni / TamPag) * TamPag;
		PaginaFinal = (DirFin / TamPag) * TamPag;

                ResGrab = SIN_ERROR;

		for (Dir = PaginaInicial; (Dir <= PaginaFinal) && (ResGrab == SIN_ERROR); Dir+=TamPag)
		{
			Ini=MAX(DirIni,Dir);
			Fin=MIN(DirFin,Dir+TamPag-1);
                        // miramos si hay que grabar la página entera
			if ((Fin-Ini+1) == TamPag)
				ResGrab=EscribirPagina(Ini,&Datos[Ini-DirIni]);
                        // o sólo modificar una parte (la primera y/o última página)
			else
			{
                        	Pagina = (unsigned char *)malloc(TamPag);

				LeerPagina(Ini,Pagina);
				for (IndiceDatos=Ini-DirIni, IndicePagina=Ini%TamPag;
						IndiceDatos <= Fin-DirIni; IndiceDatos++, IndicePagina++)
					Pagina[IndicePagina]=Datos[IndiceDatos];
				ResGrab=EscribirPagina(Ini,Pagina);

                               	free(Pagina);
			}
                        BProgreso->Position = Dir;
		}
        }
        else
        {
                int Reintentos;
                Dir = DirIni;
                IndiceDatos = 0;
                ResGrab = SIN_ERROR;
                while((Dir <= DirFin) && (ResGrab == SIN_ERROR))
                {
                        ResGrab = EscribirByte(Dir,Datos[IndiceDatos]);
                        Reintentos = 1;
                        while (ResGrab != SIN_ERROR && Reintentos < MAX_INTENTOS_BYTE_PROG)
                        {
                                Reintentos++;
                                ResGrab = EscribirByte(Dir,Datos[IndiceDatos]);
                        }
                        if ( Dir % IntervaloBP == 0)
                                BProgreso->Position = Dir;
                        Dir++;
                        IndiceDatos++;
                }
        }
        return ResGrab;
}

int TFlash::EscribirRango(int DirIni, int DirFin, AnsiString NombreFichero, TProgressBar *BProgreso)
{
        int TamBuffer, Fich, ResGrab, BytesLeidos;
        unsigned char *Buffer;

        TamBuffer = DirFin - DirIni + 1;

        if (!FileExists(NombreFichero))
                throw Exception("El fichero "+NombreFichero+" no existe.");

        Buffer = (unsigned char *)malloc(TamBuffer);

        Fich = FileOpen(NombreFichero,fmOpenRead);
        BytesLeidos = FileRead(Fich,Buffer,TamBuffer);
        FileClose(Fich);

        if (BytesLeidos < TamBuffer)
                throw Exception("El fichero "+NombreFichero+" no contiene los suficientes datos.");

        ResGrab = EscribirRango(DirIni,DirFin,Buffer,BProgreso);

        free(Buffer);

        return ResGrab;
}

Boolean TFlash::VerificarRango(int DirIni, int DirFin, unsigned char *Datos, TProgressBar *BProgreso)
{
	int Dir,Cont,IntervaloBP;
        unsigned char Dato;
        Boolean VerifOk=true;

        BProgreso->Min=0;
        BProgreso->Max=DirFin;
        BProgreso->Min=DirIni;
        IntervaloBP = MAX(1,((DirFin - DirIni) / 20));

	for (Dir = DirIni, Cont = 0; Dir <= DirFin && VerifOk; Dir++, Cont++)
        {
                Dato=LeerByte(Dir);
                VerifOk = (Dato == Datos[Cont]);
                if ( Dir % IntervaloBP == 0)
                        BProgreso->Position = Dir;
        }

        return VerifOk;
}

Boolean TFlash::VerificarRango(int DirIni, int DirFin, AnsiString NombreFichero, TProgressBar *BProgreso)
{
        int TamBuffer, Fich, BytesLeidos;
        unsigned char *Buffer;
        Boolean ResVerif;

        TamBuffer = DirFin - DirIni + 1;

        if (!FileExists(NombreFichero))
                throw Exception("El fichero "+NombreFichero+" no existe.");

        Buffer = (unsigned char *)malloc(TamBuffer);

        Fich = FileOpen(NombreFichero,fmOpenRead);
        BytesLeidos = FileRead(Fich,Buffer,TamBuffer);
        FileClose(Fich);

        if (BytesLeidos < TamBuffer)
                throw Exception("El fichero "+NombreFichero+" no contiene los suficientes datos.");

        ResVerif = VerificarRango(DirIni,DirFin,Buffer,BProgreso);

        free(Buffer);

        return ResVerif;
}

Boolean TFlash::SoportaConsultaEstadoSectores()
{
        Boolean Encontrado;
        int IndiceCmd;

        ListaComandos->IrAComando(C_SECT_PROTECT_VERIF);

        if (ListaComandos->EofCiclos())
                return false;
        else
                return true;
}

Boolean TFlash::SoportaBorradoSectores()
{
        Boolean Encontrado;
        int IndiceCmd;

        ListaComandos->IrAComando(C_SECT_ERASE);

        if (ListaComandos->EofCiclos())
                return false;
        else
                return true;
}

Boolean TFlash::SectorProtegido(int Dir)
{
        Boolean Estado;
        int DirIni, DirFin;

        ListaSectores->SectorDir(Dir, &DirIni, &DirFin);

        // Normalmente se puede enviar una dirección cualquiera
        // dentro del sector, pero las memorias con sectores de arranque
        // que hemos visto exigen que se envíe 0x00002 para Bottom Boot Block
        // y 0xXXFFF2 para el Top Boot Block
        if (DirFin == (TamMem-1))
                Dir = DirFin;
        else
                Dir = DirIni;

        EnviarComando(C_SECT_PROTECT_VERIF);

        EnviarDireccion((Dir & 0xFFFF0) | 0x00002);

        // Algunas, para indicar que el sector está protegido
        // devuelven 0xFF y otras 0x01.
        // Para indicar que no está protegido suelen devolver
        // 0xFE o 0x00.
        // Comprobaremos sólo el bit menos significativo
        Estado = RecibirDato() & 0x1;

        EnviarComando(C_RESET);

        return Estado;
}

int TFlash::BorrarSector(int Dir)
{
        EnviarComando(C_SECT_ERASE,Dir);
        return EsperarBorrado(TMAX_BOR_SEC);
}

int TFlash::BorrarMemoria(void)
{
        EnviarComando(C_CHIP_ERASE);
        return EsperarBorrado(TMAX_BOR_MEM);
}

int TFlash::EsperarToggleBit(int MaxTime, unsigned char Dato)
{
        unsigned char Dato1, Dato2;
        Boolean Timeout;
        Double TicksIni;

        if SOPORTA_DQ5ETL(Tipo)
        {
                Dato2 = RecibirDato();
                Dato1 = ~Dato2;
                while ( ((Dato1 & DQ6) != (Dato2 & DQ6)) && !(Dato2 & DQ5) )
                {
                        Dato1 = Dato2;
                        Dato2 = RecibirDato();
                }

                if (Dato2 & DQ5)
                {
                        Dato1 = RecibirDato();
                        Dato2 = RecibirDato();
                }

                if ((Dato1 & DQ6) == (Dato2 & DQ6))
                {
                        Dato2 = RecibirDato();
                        if (Dato2 == Dato)
                                return SIN_ERROR;
                        else
                                return ERROR_CMP;
                }
                else
                {
                        EnviarComando(C_RESET);
                        return ERROR_ETL;
                }
        }
        else
        {
                Timeout = false;
                TicksIni = GetTickCount();

                Dato2 = RecibirDato();
                Dato1 = ~Dato2;
                while ( ((Dato1 & DQ6) != (Dato2 & DQ6)) && !Timeout )
                {
                        Dato1 = Dato2;
                        Dato2 = RecibirDato();
                        Timeout = ( GetTickCount() > (TicksIni+MaxTime+1));
                         // Esto podria fallar si se está grabando justo cuando
                         // el sistema lleve 49.7 dias sin reiniciar, pero la
                         // probabilidad de que esto ocurra es ínfima.
                }

                if (Timeout)
                {
                        Dato1 = RecibirDato();
                        Dato2 = RecibirDato();
                }

                if ((Dato1 & DQ6) == (Dato2 & DQ6))
                {
                        Dato2 = RecibirDato();
                        if (Dato2 == Dato)
                                return SIN_ERROR;
                        else
                                return ERROR_CMP;
                }
                else
                {
                        EnviarComando(C_RESET);
                        return ERROR_ETL;
                }
        }
}

int TFlash::EsperarDataValid(int MaxTime, unsigned char Dato)
{
        unsigned char DQ;
        Boolean Timeout;
        Double TicksIni;

        if SOPORTA_DQ5ETL(Tipo)
        {
                DQ = RecibirDato();
                while ( (Dato != DQ) && !(DQ & DQ5) )
                        DQ = RecibirDato();

                if (DQ & DQ5)
                        DQ = RecibirDato();

                if (Dato == DQ )
                        return SIN_ERROR;
                else
                {
                        EnviarComando(C_RESET);
                        return ERROR_ETL;
                }
        }
        else
        {
                Timeout = false;
                TicksIni = GetTickCount();

                DQ = RecibirDato();
                while ( (Dato != DQ) && !Timeout )
                {
                        DQ = RecibirDato();
                        Timeout = ( GetTickCount() > (TicksIni+MaxTime+1));
                         // Esto podria fallar si se está grabando justo cuando
                         // el sistema lleve 49.7 dias sin reiniciar, pero la
                         // probabilidad de que esto ocurra es ínfima.
                }

                if (Timeout)
                        DQ = RecibirDato();

                if (Dato == DQ)
                        return SIN_ERROR;
                else
                {
                        EnviarComando(C_RESET);
                        return ERROR_ETL;
                }
        }
}

int TFlash::Esperar10ms(void)
{
        Sleep(10);
        return SIN_ERROR;
}

void TFlash::EsperarTblco(void)
{
        Double TicksIni;

        TicksIni = GetTickCount();
        while (GetTickCount() < (TicksIni+TBLCO+1));
}

int TFlash::EsperarProgramacion(int MaxTime, unsigned char Dato)
{
        // Damos preferencia al ToggleBit porque nos permite
        // detectar pronto si el proceso de grabación no se
        // está realizando
        if SOPORTA_DQ6TB(Tipo)
		return EsperarToggleBit(MaxTime, Dato);
	else if SOPORTA_DQ7DP(Tipo)
		return EsperarDataValid(MaxTime, Dato);
	else
		return Esperar10ms();
}

int TFlash::EsperarBorrado(int MaxTime)
{
        // Damos preferencia al ToggleBit porque nos permite
        // detectar pronto si el proceso de borrado no se
        // está realizando
        if SOPORTA_DQ6TB(Tipo)
		return EsperarToggleBit(MaxTime, 0xFF);
	else if SOPORTA_DQ7DP(Tipo)
		return EsperarDataValid(MaxTime, 0xFF);
	else
		return Esperar10ms();
}

Boolean TFlash::EstaBorradoRango(int DirIni, int DirFin, TProgressBar *BProgreso)
{
	int Dir,Cont,IntervaloBP;
        unsigned char Dato;
        Boolean VerifOk=true;

        BProgreso->Min = 0;
        BProgreso->Max = DirFin;
        BProgreso->Min = DirIni;
        IntervaloBP = MAX(1,((DirFin - DirIni) / 20));

	for (Dir = DirIni, Cont = 0; Dir <= DirFin && VerifOk; Dir++, Cont++)
        {
                Dato = LeerByte(Dir);
                VerifOk = (Dato == 0xFF);
                if ( Dir % IntervaloBP == 0)
                        BProgreso->Position = Dir;
        }

        return VerifOk;
}

Boolean TFlash::EstaBorradoSector(int Dir, TProgressBar *BProgreso)
{
        int DirIni, DirFin;

        ListaSectores->SectorDir(Dir, &DirIni, &DirFin);

        return EstaBorradoRango(DirIni, DirFin, BProgreso);
}

Boolean TFlash::EstaBorradaMemoria(TProgressBar *BProgreso)
{
	return EstaBorradoRango(0, TamMem-1, BProgreso);
}

