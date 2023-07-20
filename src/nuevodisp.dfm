object FormNDisp: TFormNDisp
  Left = 247
  Top = 191
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Nuevo dispositivo'
  ClientHeight = 195
  ClientWidth = 397
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 78
    Top = 24
    Width = 53
    Height = 13
    Caption = 'Fabricante:'
  end
  object Label4: TLabel
    Left = 64
    Top = 66
    Width = 67
    Height = 13
    Caption = 'Id. dispositivo:'
  end
  object Label2: TLabel
    Left = 93
    Top = 108
    Width = 38
    Height = 13
    Caption = 'Modelo:'
  end
  object DBLCBFab: TDBLookupComboBox
    Left = 152
    Top = 20
    Width = 145
    Height = 21
    KeyField = 'CODIGO'
    ListField = 'NOMBRE'
    ListSource = DM.DSFabricanteInt
    TabOrder = 0
  end
  object EIdDisp: TEdit
    Left = 152
    Top = 62
    Width = 145
    Height = 21
    TabOrder = 1
    Text = 'EIdDisp'
  end
  object EModelo: TEdit
    Left = 152
    Top = 104
    Width = 145
    Height = 21
    MaxLength = 20
    TabOrder = 2
    Text = 'EModelo'
  end
  object BOk: TButton
    Left = 81
    Top = 152
    Width = 75
    Height = 25
    Caption = 'Ok'
    TabOrder = 3
    OnClick = BOkClick
  end
  object BCancelar: TButton
    Left = 241
    Top = 152
    Width = 75
    Height = 25
    Caption = 'Cancelar'
    TabOrder = 4
    OnClick = BCancelarClick
  end
end
