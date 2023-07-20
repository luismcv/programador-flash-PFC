object FormPrinc: TFormPrinc
  Left = 326
  Top = 137
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Programador de memorias FLASH'
  ClientHeight = 474
  ClientWidth = 634
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poDesktopCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object StatusBar1: TStatusBar
    Left = 0
    Top = 455
    Width = 634
    Height = 19
    Panels = <>
    SimplePanel = True
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 634
    Height = 455
    ActivePage = TabSheet1
    Align = alClient
    HotTrack = True
    TabOrder = 1
    TabWidth = 120
    OnChange = PageControl1Change
    object TabSheet1: TTabSheet
      Caption = 'Dispositivo'
      object GroupBox1: TGroupBox
        Left = 7
        Top = 8
        Width = 611
        Height = 113
        Caption = 'Identificación dispositivo'
        TabOrder = 0
        object Label1: TLabel
          Left = 14
          Top = 32
          Width = 75
          Height = 13
          Alignment = taRightJustify
          Caption = 'Cód. fabricante:'
        end
        object Label3: TLabel
          Left = 224
          Top = 32
          Width = 90
          Height = 13
          Alignment = taRightJustify
          Caption = 'Nombre fabricante:'
        end
        object Label2: TLabel
          Left = 23
          Top = 72
          Width = 66
          Height = 13
          Alignment = taRightJustify
          Anchors = [akLeft, akTop, akRight]
          Caption = 'ID dispositivo:'
        end
        object Label4: TLabel
          Left = 224
          Top = 72
          Width = 90
          Height = 13
          Alignment = taRightJustify
          Caption = 'Modelo dispositivo:'
        end
        object BAutoidentificar: TButton
          Left = 501
          Top = 40
          Width = 100
          Height = 30
          Caption = 'Autoidentificar'
          TabOrder = 4
          OnClick = BAutoidentificarClick
        end
        object DBLCBFab: TDBLookupComboBox
          Left = 336
          Top = 28
          Width = 129
          Height = 21
          KeyField = 'CODIGO'
          ListField = 'NOMBRE'
          ListSource = DM.DSFabricanteInt
          TabOrder = 2
          OnClick = DBLCBFabClick
        end
        object DBLCBMod: TDBLookupComboBox
          Left = 336
          Top = 68
          Width = 129
          Height = 21
          KeyField = 'ID'
          ListField = 'NOMBRE'
          ListSource = DM.DSDispositivoInt
          TabOrder = 3
          OnClick = DBLCBModClick
        end
        object DBEdit1: TDBEdit
          Left = 105
          Top = 28
          Width = 89
          Height = 21
          TabStop = False
          AutoSelect = False
          DataField = 'CODIGO'
          DataSource = DM.DSFabricante
          ReadOnly = True
          TabOrder = 0
        end
        object DBEdit2: TDBEdit
          Left = 105
          Top = 68
          Width = 89
          Height = 21
          TabStop = False
          DataField = 'ID'
          DataSource = DM.DSDispositivo
          ReadOnly = True
          TabOrder = 1
        end
      end
      object GroupBox2: TGroupBox
        Left = 7
        Top = 128
        Width = 611
        Height = 289
        Anchors = [akLeft, akTop, akRight, akBottom]
        Caption = 'Información'
        TabOrder = 1
        object Label5: TLabel
          Left = 16
          Top = 32
          Width = 71
          Height = 13
          Caption = 'Núm. sectores:'
        end
        object Label6: TLabel
          Left = 168
          Top = 32
          Width = 51
          Height = 13
          Caption = 'Tipo prog.:'
        end
        object Label16: TLabel
          Left = 304
          Top = 32
          Width = 42
          Height = 13
          Caption = 'Tamaño:'
        end
        object ENumSect: TEdit
          Left = 96
          Top = 28
          Width = 49
          Height = 21
          TabStop = False
          ReadOnly = True
          TabOrder = 0
          Text = 'ENumSect'
        end
        object ETamTotal: TEdit
          Left = 360
          Top = 28
          Width = 129
          Height = 21
          TabStop = False
          ReadOnly = True
          TabOrder = 1
          Text = 'ETamTotal'
        end
        object SGSectores: TStringGrid
          Left = 11
          Top = 72
          Width = 593
          Height = 209
          TabStop = False
          FixedCols = 0
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine]
          TabOrder = 2
          OnDrawCell = SGSectoresDrawCell
        end
        object BEstadoSectores: TButton
          Left = 504
          Top = 26
          Width = 100
          Height = 30
          Caption = 'Estado Protec.'
          TabOrder = 3
          OnClick = BEstadoSectoresClick
        end
        object ETipo: TEdit
          Left = 232
          Top = 28
          Width = 57
          Height = 21
          TabStop = False
          ReadOnly = True
          TabOrder = 4
          Text = 'ETipo'
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Lectura'
      ImageIndex = 1
      object GroupBox3: TGroupBox
        Left = 7
        Top = 8
        Width = 611
        Height = 201
        Caption = 'Lectura'
        TabOrder = 0
        object Label7: TLabel
          Left = 113
          Top = 26
          Width = 48
          Height = 13
          Caption = 'Dirección:'
        end
        object Label8: TLabel
          Left = 115
          Top = 117
          Width = 46
          Height = 13
          Caption = 'Dir. inicio:'
        end
        object Label9: TLabel
          Left = 352
          Top = 117
          Width = 41
          Height = 13
          Caption = 'Dir. final:'
        end
        object ELDir: TEdit
          Left = 176
          Top = 22
          Width = 153
          Height = 21
          Enabled = False
          TabOrder = 1
          OnEnter = DirEnter
          OnExit = DirExit
          OnKeyPress = DirKeyPress
        end
        object RBLByte: TRadioButton
          Left = 8
          Top = 24
          Width = 49
          Height = 17
          Caption = 'Byte'
          TabOrder = 0
          OnClick = RBLByteClick
        end
        object RBLSector: TRadioButton
          Left = 8
          Top = 69
          Width = 57
          Height = 17
          Caption = 'Sector'
          TabOrder = 2
          OnClick = RBLSectorClick
        end
        object CBLSector: TComboBox
          Left = 176
          Top = 67
          Width = 153
          Height = 21
          Enabled = False
          ItemHeight = 0
          TabOrder = 3
        end
        object RBLRango: TRadioButton
          Left = 8
          Top = 115
          Width = 57
          Height = 17
          Caption = 'Rango'
          TabOrder = 4
          OnClick = RBLRangoClick
        end
        object ELDirIni: TEdit
          Left = 176
          Top = 113
          Width = 153
          Height = 21
          Enabled = False
          TabOrder = 5
          OnEnter = DirEnter
          OnExit = DirExit
          OnKeyPress = DirKeyPress
        end
        object ELDirFin: TEdit
          Left = 408
          Top = 113
          Width = 153
          Height = 21
          Enabled = False
          TabOrder = 6
          OnEnter = DirEnter
          OnExit = DirExit
          OnKeyPress = DirKeyPress
        end
        object RBLMemoria: TRadioButton
          Left = 8
          Top = 160
          Width = 121
          Height = 17
          Caption = 'Memoria completa'
          Checked = True
          TabOrder = 7
          TabStop = True
          OnClick = RBLMemoriaClick
        end
      end
      object GroupBox4: TGroupBox
        Left = 7
        Top = 224
        Width = 611
        Height = 137
        Caption = 'Datos'
        TabOrder = 1
        object Label11: TLabel
          Left = 16
          Top = 34
          Width = 24
          Height = 13
          Caption = 'Valor'
        end
        object Label14: TLabel
          Left = 16
          Top = 84
          Width = 35
          Height = 13
          Caption = 'Fichero'
        end
        object ELFichero: TEdit
          Left = 88
          Top = 80
          Width = 369
          Height = 21
          TabOrder = 1
        end
        object BLExaminar: TButton
          Left = 504
          Top = 78
          Width = 75
          Height = 25
          Caption = 'Examinar'
          TabOrder = 2
          OnClick = BLExaminarClick
        end
        object ELValor: TEdit
          Left = 88
          Top = 30
          Width = 81
          Height = 21
          TabStop = False
          ReadOnly = True
          TabOrder = 0
        end
      end
      object BLeer: TButton
        Left = 263
        Top = 384
        Width = 100
        Height = 30
        Caption = 'Leer'
        TabOrder = 2
        OnClick = BLeerClick
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'Escritura'
      ImageIndex = 2
      object GroupBox7: TGroupBox
        Left = 7
        Top = 8
        Width = 611
        Height = 201
        Caption = 'Grabación'
        TabOrder = 0
        object Label10: TLabel
          Left = 113
          Top = 26
          Width = 48
          Height = 13
          Caption = 'Dirección:'
        end
        object Label12: TLabel
          Left = 115
          Top = 117
          Width = 46
          Height = 13
          Caption = 'Dir. inicio:'
        end
        object Label13: TLabel
          Left = 352
          Top = 117
          Width = 41
          Height = 13
          Caption = 'Dir. final:'
        end
        object EEDir: TEdit
          Left = 176
          Top = 22
          Width = 153
          Height = 21
          Enabled = False
          TabOrder = 1
          OnEnter = DirEnter
          OnExit = DirExit
          OnKeyPress = DirKeyPress
        end
        object RBEByte: TRadioButton
          Left = 8
          Top = 24
          Width = 49
          Height = 17
          Caption = 'Byte'
          TabOrder = 0
          OnClick = RBEByteClick
        end
        object RBESector: TRadioButton
          Left = 8
          Top = 69
          Width = 57
          Height = 17
          Caption = 'Sector'
          TabOrder = 2
          OnClick = RBESectorClick
        end
        object CBESector: TComboBox
          Left = 176
          Top = 67
          Width = 153
          Height = 21
          Enabled = False
          ItemHeight = 0
          TabOrder = 3
        end
        object RBERango: TRadioButton
          Left = 8
          Top = 115
          Width = 57
          Height = 17
          Caption = 'Rango'
          TabOrder = 4
          OnClick = RBERangoClick
        end
        object EEDirIni: TEdit
          Left = 176
          Top = 113
          Width = 153
          Height = 21
          Enabled = False
          TabOrder = 5
          OnEnter = DirEnter
          OnExit = DirExit
          OnKeyPress = DirKeyPress
        end
        object EEDirFin: TEdit
          Left = 408
          Top = 113
          Width = 153
          Height = 21
          Enabled = False
          TabOrder = 6
          OnEnter = DirEnter
          OnExit = DirExit
          OnKeyPress = DirKeyPress
        end
        object RBEMemoria: TRadioButton
          Left = 8
          Top = 160
          Width = 145
          Height = 17
          Caption = 'Memoria completa'
          Checked = True
          TabOrder = 7
          TabStop = True
          OnClick = RBEMemoriaClick
        end
      end
      object GroupBox8: TGroupBox
        Left = 7
        Top = 224
        Width = 611
        Height = 145
        Caption = 'Datos'
        TabOrder = 1
        object RBEValor: TRadioButton
          Left = 8
          Top = 24
          Width = 89
          Height = 17
          Caption = 'Valor'
          TabOrder = 0
          OnClick = RBEValorClick
        end
        object RBEValorAleatorio: TRadioButton
          Left = 8
          Top = 61
          Width = 113
          Height = 17
          Caption = 'Valores aleatorios'
          TabOrder = 2
          OnClick = RBEValorAleatorioClick
        end
        object RBEFichero: TRadioButton
          Left = 8
          Top = 98
          Width = 113
          Height = 17
          Caption = 'Fichero'
          Checked = True
          TabOrder = 3
          TabStop = True
          OnClick = RBEFicheroClick
        end
        object EEValor: TEdit
          Left = 88
          Top = 22
          Width = 81
          Height = 21
          Enabled = False
          TabOrder = 1
          OnEnter = ValorEnter
          OnExit = ValorExit
          OnKeyPress = ValorKeyPress
        end
        object EEFichero: TEdit
          Left = 88
          Top = 96
          Width = 369
          Height = 21
          TabOrder = 4
        end
        object BEExaminar: TButton
          Left = 504
          Top = 94
          Width = 75
          Height = 25
          Caption = 'Examinar'
          TabOrder = 5
          OnClick = BEExaminarClick
        end
      end
      object CBVerificar: TCheckBox
        Left = 123
        Top = 387
        Width = 137
        Height = 17
        Caption = 'Verificar grabación'
        TabOrder = 2
      end
      object BGrabar: TButton
        Left = 403
        Top = 380
        Width = 100
        Height = 30
        Caption = 'Grabar'
        TabOrder = 3
        OnClick = BGrabarClick
      end
    end
    object TabSheet4: TTabSheet
      Caption = 'Borrado'
      ImageIndex = 3
      object GroupBox5: TGroupBox
        Left = 7
        Top = 8
        Width = 611
        Height = 113
        Caption = 'Borrado'
        TabOrder = 0
        object RBBSector: TRadioButton
          Left = 8
          Top = 24
          Width = 57
          Height = 17
          Caption = 'Sector'
          TabOrder = 0
          OnClick = RBBSectorClick
        end
        object CBBSector: TComboBox
          Left = 176
          Top = 22
          Width = 153
          Height = 21
          Enabled = False
          ItemHeight = 0
          TabOrder = 1
        end
        object RBBMemoria: TRadioButton
          Left = 8
          Top = 72
          Width = 145
          Height = 17
          Caption = 'Memoria completa'
          Checked = True
          TabOrder = 2
          TabStop = True
          OnClick = RBBMemoriaClick
        end
      end
      object BBorrar: TButton
        Left = 135
        Top = 376
        Width = 100
        Height = 30
        Caption = 'Borrar'
        TabOrder = 1
        OnClick = BBorrarClick
      end
      object BComprobarBorrado: TButton
        Left = 391
        Top = 376
        Width = 100
        Height = 30
        Caption = 'Comprobar'
        TabOrder = 2
        OnClick = BComprobarBorradoClick
      end
    end
    object TabSheet5: TTabSheet
      Caption = 'Comandos'
      ImageIndex = 4
      object GroupBox6: TGroupBox
        Left = 8
        Top = 8
        Width = 611
        Height = 105
        Caption = 'Ejecución comandos'
        TabOrder = 0
        object Label15: TLabel
          Left = 16
          Top = 48
          Width = 48
          Height = 13
          Caption = 'Comando:'
        end
        object CBComando: TComboBox
          Left = 112
          Top = 44
          Width = 185
          Height = 21
          ItemHeight = 0
          TabOrder = 0
        end
        object BEjecutar: TButton
          Left = 408
          Top = 39
          Width = 100
          Height = 30
          Caption = 'Ejecutar'
          TabOrder = 1
          OnClick = BEjecutarClick
        end
      end
    end
  end
  object BProgreso: TProgressBar
    Left = 168
    Top = 456
    Width = 465
    Height = 16
    Min = 0
    Max = 100
    TabOrder = 2
  end
  object MainMenu1: TMainMenu
    BiDiMode = bdLeftToRight
    ParentBiDiMode = False
    Left = 616
    Top = 24
    object Archivo1: TMenuItem
      Caption = 'Opciones'
      object C1: TMenuItem
        Caption = 'Configurar puerto paralelo'
        OnClick = C1Click
      end
      object Basededatosdememorias1: TMenuItem
        Caption = 'Base de datos de memorias'
        OnClick = Basededatosdememorias1Click
      end
      object Salir1: TMenuItem
        Caption = 'Salir'
        OnClick = Salir1Click
      end
    end
    object Ayuda1: TMenuItem
      Caption = 'Ayuda'
      object Ayudaprogramador1: TMenuItem
        Caption = 'Ayuda programador'
        OnClick = Ayudaprogramador1Click
      end
      object Ayudabasededatos1: TMenuItem
        Caption = 'Ayuda base de datos'
        OnClick = Ayudabasededatos1Click
      end
      object Acercade1: TMenuItem
        Caption = 'Acerca de...'
        OnClick = Acercade1Click
      end
    end
  end
  object OpenDialog1: TOpenDialog
    DefaultExt = 'rom'
    Filter = 
      'Archivos ROM|*.rom|Archivos BIN|*.bin|Archivos HEX|*.hex|Todos|*' +
      '.*'
    Left = 488
    Top = 8
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = 'rom'
    Filter = 
      'Archivos ROM|*.rom|Archivos BIN|*.bin|Archivos HEX|*.hex|Todos|*' +
      '.*'
    Left = 512
    Top = 8
  end
end
