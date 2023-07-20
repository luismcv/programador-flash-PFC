//---------------------------------------------------------------------------

#ifndef flashH
#define flashH
//---------------------------------------------------------------------------

#include "pport.h"

#define T_PROGRAMABLE 	0x01
#define T_POR_PAGINAS	0x02
#define T_DQ5ETL	0x20
#define T_DQ6TB 	0x40
#define T_DQ7DP 	0x80

#define DQ7             0x80
#define DQ6             0x40
#define DQ5             0x20

#define ES_PROGRAMABLE(tipo)	( tipo & T_PROGRAMABLE )
#define ES_POR_PAGINAS(tipo)	( tipo & T_POR_PAGINAS )
#define SOPORTA_DQ7DP(tipo)	( tipo & T_DQ7DP )
#define SOPORTA_DQ6TB(tipo)	( tipo & T_DQ6TB )
#define SOPORTA_DQ5ETL(tipo)     ( tipo & T_DQ5ETL )

#define SIN_ERROR        0
#define ERROR_ETL       -1	// Error Excedeed Time Limit, fallo hardware o memoria no borrada
#define ERROR_MAX_INT   -2      // Número máximo de intentos alcanzado
#define ERROR_CMP       -3      // Tras la grabación el byte leído no coincide con el supuestamente grabado

#define MAX_INTENTOS_BYTE_PROG    50
#define MAX_INTENTOS_PAGE_PROG    10
#define MAX_CICLOS      10

#define TMAX_BYTE_PROG  5
#define TMAX_PAGE_PROG  50
#define TMAX_BOR_SEC    8000
#define TMAX_BOR_MEM    64000
#define TBLCO           250

#define MAX_ID_C_BAS    50      // los comandos básicos tendrán ID 0 a MAX_ID_C_BAS
                                // y los comandos extras ID > MAX_ID_C_BAS
#define C_READ          1
#define C_RESET         2
#define C_PROGRAM       3
#define C_CHIP_ERASE    4
#define C_SECT_ERASE    5
#define C_SECT_PROTECT_VERIF    6

#define CMDSectorAddress	0x100000


class TListaSectores
{
private:
        typedef struct
        {
	        int DirIni;
        	int DirFin;
        } TSector;
        TList *LSectores;
        int PosicionActual;
        int BuscaSector(int Dir);
        void SectorNum(int Indice, int *DirIni, int *DirFin);
public:
        TListaSectores(void);
        ~TListaSectores(void);

        int NumSectores(void);
        Boolean Eof(void);
        void AnyadirSector(int DirIni, int DirFin);
        void AnyadirSectores(int DirIni, int Tamanyo, int Numero);
        void IrInicioLista(void);
        void Siguiente(void);
        void SectorActual(int *DirIni, int *DirFin);
        void SectorDir(int Dir, int *DirIni, int *DirFin);
        void Borrar(void);
};

class TListaComandos
{
private:
        typedef struct
        {
	        int Dir;
        	unsigned char Dato;
        } TCiclo;
        typedef struct
        {
        	int Id;
                String Descripcion;
        	TList *Ciclos;
        } TComando;
        TList *LComandos;
        int PosicionComandoActual;
        int PosicionCicloActual;
        int BuscaComando(int Id);
public:
        TListaComandos(void);
        ~TListaComandos(void);

        int NumComandos(void);
        int NumCiclos(void);
        Boolean EofComandos(void);
        Boolean EofCiclos(void);
        void AnyadirComando(int Id, String Descripcion, String SecDirec, String SecDatos);
        void IrInicioListaComandos(void);
        void IrAComando(int Id);
        void IrInicioListaCiclos(void);
        void SiguienteComando(void);
        void SiguienteCiclo(void);
        void Borrar(void);
        void CicloActual(int *Dir, unsigned char *Dato);
};

typedef struct
{
	int TamMem;
	int TamPag;
	unsigned char Tipo;
        TListaSectores *ListaSectores;
	TListaComandos *ListaComandos;
} TDatosMemoria;

class TFlash
{
private:
	void EnviarDireccion(int dir);
	void EnviarDato(unsigned char dato);
	unsigned char RecibirDato(void);

	int EsperarToggleBit(int MaxTime, unsigned char Dato);
	int EsperarDataValid(int MaxTime, unsigned char Dato);
	int Esperar10ms(void);
	int EsperarProgramacion(int MaxTime, unsigned char Dato);
	int EsperarBorrado(int MaxTime);

	void EsperarTblco(void);

	int TamMem;
	int TamPag;
	unsigned char Tipo;
public:
        TListaSectores *ListaSectores;
	TListaComandos *ListaComandos;

        TFlash(void);
        ~TFlash(void);

        Boolean Identificar(unsigned char *ManufCode, unsigned char *DeviceId);
        Boolean HayFlash(void);
        void Configurar(TDatosMemoria *DatosMemoria);
        Boolean EsProgramable(void);
        Boolean EsPorPaginas(void);
        Boolean EsByteAByte(void);

        void EnviarComando(int Id);
        void EnviarComando(int Id, int Parametro);

        unsigned char LeerByte(int Dir);
        int EscribirByte(int Dir, unsigned char Dato);
        Boolean VerificarByte(int Dir, unsigned char Dato);

        void LeerPagina(int Dir, unsigned char *Datos);
        void LeerPagina(int Dir, AnsiString NombreFichero );
        int EscribirPagina(int Dir, unsigned char *Datos);
        int EscribirPagina(int Dir, AnsiString NombreFichero);
        Boolean VerificarPagina(int Dir, unsigned char *Datos);
        Boolean VerificarPagina(int Dir, AnsiString NombreFichero);

        void LeerSector(int Dir, unsigned char *Datos, TProgressBar *BProgreso);
        void LeerSector(int Dir, AnsiString NombreFichero, TProgressBar *BProgreso);
        int EscribirSector(int Dir, unsigned char *Datos, TProgressBar *BProgreso);
        int EscribirSector(int Dir, AnsiString NombreFichero, TProgressBar *BProgreso);
        Boolean VerificarSector(int Dir, unsigned char *Datos, TProgressBar *BProgreso);
        Boolean VerificarSector(int Dir, AnsiString NombreFichero, TProgressBar *BProgreso);

        void LeerMemoria(unsigned char *Datos, TProgressBar *BProgreso);
        void LeerMemoria(AnsiString NombreFichero, TProgressBar *BProgreso);
        int EscribirMemoria(unsigned char *Datos, TProgressBar *BProgreso);
        int EscribirMemoria(AnsiString NombreFichero, TProgressBar *BProgreso);
        Boolean VerificarMemoria(unsigned char *Datos, TProgressBar *BProgreso);
        Boolean VerificarMemoria(AnsiString NombreFichero, TProgressBar *BProgreso);

        void LeerRango(int DirIni, int DirFin, unsigned char *Datos, TProgressBar *BProgreso);
        void LeerRango(int DirIni, int DirFin, AnsiString NombreFichero, TProgressBar *BProgreso);
        int EscribirRango(int DirIni, int DirFin, unsigned char *Datos, TProgressBar *BProgreso);
        int EscribirRango(int DirIni, int DirFin, AnsiString NombreFichero, TProgressBar *BProgreso);
        Boolean VerificarRango(int DirIni, int DirFin, unsigned char *Datos, TProgressBar *BProgreso);
        Boolean VerificarRango(int DirIni, int DirFin, AnsiString NombreFichero, TProgressBar *BProgreso);

        Boolean SoportaConsultaEstadoSectores();
        Boolean SectorProtegido(int Dir);

        Boolean SoportaBorradoSectores();
        int BorrarSector(int Dir);
        int BorrarMemoria(void);
        Boolean EstaBorradoRango(int DirIni, int DirFin, TProgressBar *BProgreso);
        Boolean EstaBorradoSector(int Dir, TProgressBar *BProgreso);
        Boolean EstaBorradaMemoria(TProgressBar *BProgreso);
};
#endif
