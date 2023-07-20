object FormBD: TFormBD
  Left = 342
  Top = 192
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Base de datos de memorias'
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
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 633
    Height = 473
    ActivePage = TabSheet1
    TabOrder = 0
    TabWidth = 150
    OnChange = PageControl1Change
    OnChanging = PageControl1Changing
    object TabSheet1: TTabSheet
      Caption = 'Fabricantes'
      object DBGrid1: TDBGrid
        Left = 9
        Top = 16
        Width = 600
        Height = 377
        DataSource = DM.DSFabricante
        Options = [dgEditing, dgTitles, dgIndicator, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit]
        TabOrder = 0
        TitleFont.Charset = DEFAULT_CHARSET
        TitleFont.Color = clWindowText
        TitleFont.Height = -11
        TitleFont.Name = 'MS Sans Serif'
        TitleFont.Style = []
        Columns = <
          item
            Expanded = False
            FieldName = 'NOMBRE'
            Title.Caption = 'Nombre'
            Width = 424
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'CODIGO'
            Title.Caption = 'Código'
            Width = 137
            Visible = True
          end>
      end
      object BInsFab: TButton
        Left = 129
        Top = 408
        Width = 100
        Height = 30
        Caption = 'Nuevo'
        TabOrder = 1
        OnClick = BInsFabClick
      end
      object BDelFab: TButton
        Left = 396
        Top = 408
        Width = 100
        Height = 30
        Caption = 'Eliminar'
        TabOrder = 2
        OnClick = BDelFabClick
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Juegos de comandos'
      ImageIndex = 1
      object GroupBox1: TGroupBox
        Left = 9
        Top = 8
        Width = 608
        Height = 145
        Caption = 'Juegos de comandos'
        TabOrder = 0
        object DBLCBJuegoComandos: TDBLookupComboBox
          Left = 24
          Top = 64
          Width = 177
          Height = 21
          KeyField = 'ID'
          ListField = 'NOMBRE'
          ListSource = DM.DSJuegoComandosInt
          TabOrder = 0
          OnClick = DBLCBJuegoComandosClick
        end
        object BCopiarJuegoComandos: TButton
          Left = 356
          Top = 59
          Width = 100
          Height = 30
          Caption = 'Copiar como'
          TabOrder = 2
          OnClick = BCopiarJuegoComandosClick
        end
        object BEliminarJuegoComandos: TButton
          Left = 480
          Top = 59
          Width = 100
          Height = 30
          Caption = 'Eliminar'
          TabOrder = 3
          OnClick = BEliminarJuegoComandosClick
        end
        object BNuevoJuegoComandos: TButton
          Left = 232
          Top = 59
          Width = 100
          Height = 30
          Caption = 'Nuevo'
          TabOrder = 1
          OnClick = BNuevoJuegoComandosClick
        end
      end
      object GroupBox2: TGroupBox
        Left = 9
        Top = 160
        Width = 608
        Height = 281
        Caption = 'Comandos'
        TabOrder = 1
        object Label8: TLabel
          Left = 303
          Top = 104
          Width = 61
          Height = 13
          Caption = 'Secuencia'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object DBLCBComando: TDBLookupComboBox
          Left = 24
          Top = 53
          Width = 175
          Height = 21
          KeyField = 'ID'
          ListField = 'DESCRIPCION'
          ListSource = DM.DSComandoInt
          TabOrder = 0
          OnClick = DBLCBComandoClick
        end
        object BCopiarComando: TButton
          Left = 356
          Top = 48
          Width = 100
          Height = 30
          Caption = 'Copiar como'
          TabOrder = 2
          OnClick = BCopiarComandoClick
        end
        object BEliminarComando: TButton
          Left = 480
          Top = 48
          Width = 100
          Height = 30
          Caption = 'Eliminar'
          TabOrder = 3
          OnClick = BEliminarComandoClick
        end
        object BNuevoComando: TButton
          Left = 232
          Top = 48
          Width = 100
          Height = 30
          Caption = 'Nuevo'
          TabOrder = 1
          OnClick = BNuevoComandoClick
        end
        object SGSecuencias: TStringGrid
          Left = 16
          Top = 128
          Width = 577
          Height = 105
          ColCount = 11
          RowCount = 3
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing, goTabs]
          TabOrder = 4
          OnDrawCell = SGSecuenciasDrawCell
          OnExit = SGSecuenciasExit
          OnGetEditText = SGSecuenciasGetEditText
          OnKeyDown = SGSecuenciasKeyDown
          OnKeyPress = SGSecuenciasKeyPress
          OnSelectCell = SGSecuenciasSelectCell
        end
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'Dispositivos'
      ImageIndex = 2
      object GroupBox3: TGroupBox
        Left = 9
        Top = 8
        Width = 608
        Height = 161
        Caption = 'Identificación'
        TabOrder = 0
        object Label1: TLabel
          Left = 16
          Top = 24
          Width = 53
          Height = 13
          Caption = 'Fabricante:'
        end
        object Label2: TLabel
          Left = 31
          Top = 55
          Width = 38
          Height = 13
          Caption = 'Modelo:'
        end
        object Label3: TLabel
          Left = 304
          Top = 24
          Width = 86
          Height = 13
          Caption = 'Código fabricante:'
        end
        object Label4: TLabel
          Left = 323
          Top = 55
          Width = 67
          Height = 13
          Caption = 'Id. dispositivo:'
        end
        object DBLCBFab: TDBLookupComboBox
          Left = 88
          Top = 20
          Width = 177
          Height = 21
          KeyField = 'CODIGO'
          ListField = 'NOMBRE'
          ListSource = DM.DSFabricanteInt
          TabOrder = 0
          OnClick = DBLCBFabClick
        end
        object DBLCBMod: TDBLookupComboBox
          Left = 88
          Top = 51
          Width = 177
          Height = 21
          KeyField = 'ID'
          ListField = 'NOMBRE'
          ListSource = DM.DSDispositivoInt
          TabOrder = 1
          OnClick = DBLCBModClick
        end
        object DBECodFab: TDBEdit
          Left = 416
          Top = 20
          Width = 177
          Height = 21
          DataField = 'CODIGO'
          DataSource = DM.DSFabricante
          ReadOnly = True
          TabOrder = 2
        end
        object DBEIdDisp: TDBEdit
          Left = 416
          Top = 51
          Width = 177
          Height = 21
          DataField = 'ID'
          DataSource = DM.DSDispositivo
          ReadOnly = True
          TabOrder = 3
        end
        object BEliminarDisp: TButton
          Left = 244
          Top = 80
          Width = 100
          Height = 30
          Caption = 'Eliminar'
          TabOrder = 6
          OnClick = BEliminarDispClick
        end
        object BNuevoDisp: TButton
          Left = 16
          Top = 80
          Width = 100
          Height = 30
          Caption = 'Nuevo'
          TabOrder = 4
          OnClick = BNuevoDispClick
        end
        object BCopiarDisp: TButton
          Left = 130
          Top = 80
          Width = 100
          Height = 30
          Caption = 'Copiar como'
          TabOrder = 5
          OnClick = BCopiarDispClick
        end
        object BGuardarCambiosDisp: TButton
          Left = 496
          Top = 120
          Width = 100
          Height = 30
          Caption = 'Guardar cambios'
          TabOrder = 7
          OnClick = BGuardarCambiosDispClick
        end
        object BCancelarCambiosDisp: TButton
          Left = 384
          Top = 120
          Width = 100
          Height = 30
          Caption = 'Cancelar cambios'
          TabOrder = 8
          OnClick = BCancelarCambiosDispClick
        end
        object BExportar: TButton
          Left = 16
          Top = 120
          Width = 100
          Height = 30
          Caption = 'Exportar'
          TabOrder = 9
          OnClick = BExportarClick
        end
        object BImportar: TButton
          Left = 130
          Top = 120
          Width = 100
          Height = 30
          Caption = 'Importar'
          TabOrder = 10
          OnClick = BImportarClick
        end
      end
      object GBCaract: TGroupBox
        Left = 8
        Top = 176
        Width = 609
        Height = 129
        Caption = 'Características'
        TabOrder = 1
        object Label5: TLabel
          Left = 53
          Top = 24
          Width = 42
          Height = 13
          Caption = 'Tamaño:'
        end
        object Label6: TLabel
          Left = 39
          Top = 60
          Width = 56
          Height = 13
          Caption = 'Núm. pines:'
        end
        object Label9: TLabel
          Left = 11
          Top = 96
          Width = 84
          Height = 13
          Caption = 'Juego comandos:'
        end
        object GroupBox6: TGroupBox
          Left = 280
          Top = 8
          Width = 321
          Height = 113
          Caption = 'Tipo de programación'
          TabOrder = 3
          object Label7: TLabel
            Left = 218
            Top = 32
            Width = 92
            Height = 13
            Caption = 'Tamaño de página:'
          end
          object RBPag: TRadioButton
            Left = 112
            Top = 52
            Width = 81
            Height = 17
            Caption = 'Por páginas'
            TabOrder = 4
            OnClick = RBPagClick
          end
          object RBRom: TRadioButton
            Left = 112
            Top = 80
            Width = 201
            Height = 17
            Caption = 'ROM,EPROM,Flash 12V (sólo lect.)'
            TabOrder = 5
            OnClick = RBRomClick
          end
          object RBByte: TRadioButton
            Left = 112
            Top = 24
            Width = 49
            Height = 17
            Caption = 'Byte'
            TabOrder = 3
            OnClick = RBByteClick
          end
          object CBTamPag: TComboBox
            Left = 200
            Top = 50
            Width = 113
            Height = 21
            Style = csDropDownList
            Enabled = False
            ItemHeight = 13
            TabOrder = 6
            OnChange = CBTamPagChange
            Items.Strings = (
              '1 byte'
              '2 bytes'
              '4 bytes'
              '8 bytes'
              '16 bytes'
              '32 bytes'
              '64 bytes'
              '128 bytes'
              '256 bytes'
              '512 bytes'
              '1 Kbyte'
              '2 Kbytes'
              '4 Kbytes'
              '8 Kbytes'
              '16 Kbytes'
              '32 Kbytes'
              '64 Kbytes'
              '128 Kbytes'
              '256 Kbytes')
          end
          object CBDQ7: TCheckBox
            Left = 16
            Top = 24
            Width = 73
            Height = 17
            Caption = 'DP(DQ7)'
            TabOrder = 0
            OnClick = CBDQ7Click
          end
          object CBDQ6: TCheckBox
            Left = 16
            Top = 52
            Width = 65
            Height = 17
            Caption = 'TB(DQ6)'
            TabOrder = 1
            OnClick = CBDQ6Click
          end
          object CBDQ5: TCheckBox
            Left = 16
            Top = 80
            Width = 73
            Height = 17
            Caption = 'ETL(DQ5)'
            TabOrder = 2
            OnClick = CBDQ5Click
          end
        end
        object DBLCBJuegoComandos2: TDBLookupComboBox
          Left = 112
          Top = 92
          Width = 153
          Height = 21
          DataField = 'JUEGO_COMANDOS'
          DataSource = DM.DSDispositivo
          KeyField = 'ID'
          ListField = 'NOMBRE'
          ListSource = DM.DSJuegoComando
          TabOrder = 2
        end
        object CBTam: TComboBox
          Left = 112
          Top = 20
          Width = 153
          Height = 21
          Style = csDropDownList
          ItemHeight = 13
          TabOrder = 0
          OnChange = CBTamChange
          Items.Strings = (
            '16 KBit (2K x 8-Bit)'
            '32 KBit (4K x 8-Bit)'
            '64 KBit (8K x 8-Bit)'
            '128 KBit (16K x 8-Bit)'
            '256 KBit (32K x 8-Bit)'
            '512 KBit (64K x 8-Bit)'
            '1 MBit (128K x 8-Bit)'
            '2 MBit (256K x 8-Bit)'
            '4 MBit (512K x 8-Bit) ')
        end
        object CBNumPin: TComboBox
          Left = 112
          Top = 56
          Width = 153
          Height = 21
          ItemHeight = 13
          TabOrder = 1
          OnChange = CBNumPinChange
          Items.Strings = (
            '24'
            '28'
            '32')
        end
      end
      object GBSect: TGroupBox
        Left = 9
        Top = 312
        Width = 608
        Height = 129
        Caption = 'Sectores'
        TabOrder = 2
        object DBGSec: TDBGrid
          Left = 16
          Top = 24
          Width = 465
          Height = 88
          DataSource = DM.DSListaSectores
          TabOrder = 0
          TitleFont.Charset = DEFAULT_CHARSET
          TitleFont.Color = clWindowText
          TitleFont.Height = -11
          TitleFont.Name = 'MS Sans Serif'
          TitleFont.Style = []
          Columns = <
            item
              Expanded = False
              FieldName = 'DIRECCION_COMIENZO'
              Title.Caption = 'Dir. inicial'
              Title.Font.Charset = DEFAULT_CHARSET
              Title.Font.Color = clWindowText
              Title.Font.Height = -11
              Title.Font.Name = 'MS Sans Serif'
              Title.Font.Style = [fsBold]
              Width = 82
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'NUMERO'
              PickList.Strings = (
                '1'
                '2'
                '3'
                '4'
                '8'
                '10'
                '12'
                '14'
                '16'
                '18'
                '20'
                '24'
                '28'
                '32'
                '64'
                '128'
                '256'
                '512'
                '1024'
                '2048'
                '4096')
              Title.Caption = 'Cantidad'
              Title.Font.Charset = DEFAULT_CHARSET
              Title.Font.Color = clWindowText
              Title.Font.Height = -11
              Title.Font.Name = 'MS Sans Serif'
              Title.Font.Style = [fsBold]
              Width = 77
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'LONGITUD'
              PickList.Strings = (
                '8'
                '16'
                '32'
                '64'
                '128'
                '256'
                '512'
                '1024'
                '2048'
                '4096'
                '8192'
                '16384'
                '32768'
                '65536'
                '131072'
                '262144'
                '524288')
              Title.Caption = 'Longitud (bytes)'
              Title.Font.Charset = DEFAULT_CHARSET
              Title.Font.Color = clWindowText
              Title.Font.Height = -11
              Title.Font.Name = 'MS Sans Serif'
              Title.Font.Style = [fsBold]
              Width = 118
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'DIRECCION_FINAL'
              Title.Caption = 'Dir. final'
              Title.Font.Charset = DEFAULT_CHARSET
              Title.Font.Color = clWindowText
              Title.Font.Height = -11
              Title.Font.Name = 'MS Sans Serif'
              Title.Font.Style = [fsBold]
              Width = 77
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'TAMANYO_TOTAL'
              Title.Caption = 'Long. total'
              Title.Font.Charset = DEFAULT_CHARSET
              Title.Font.Color = clWindowText
              Title.Font.Height = -11
              Title.Font.Name = 'MS Sans Serif'
              Title.Font.Style = [fsBold]
              Width = 70
              Visible = True
            end>
        end
        object BInsertSect: TButton
          Left = 496
          Top = 32
          Width = 100
          Height = 30
          Caption = 'Insertar'
          TabOrder = 1
          OnClick = BInsertSectClick
        end
        object BEliminarSect: TButton
          Left = 496
          Top = 72
          Width = 100
          Height = 30
          Caption = 'Eliminar'
          TabOrder = 2
          OnClick = BEliminarSectClick
        end
      end
    end
  end
  object MainMenu1: TMainMenu
    Left = 552
    Top = 65528
    object Salir1: TMenuItem
      Caption = 'Salir'
      OnClick = Salir1Click
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
    DefaultExt = 'ddm'
    Filter = 'Definición Datos Memorias|*.ddm'
    Left = 488
    Top = 65528
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = 'ddm'
    Filter = 'Definición Datos Memorias|*.ddm'
    Left = 520
    Top = 65528
  end
end
