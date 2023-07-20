object DM: TDM
  OldCreateOrder = False
  Left = 174
  Top = 173
  Height = 505
  Width = 794
  object Database1: TDatabase
    Connected = True
    DatabaseName = 'Disp'
    DriverName = 'STANDARD'
    Params.Strings = (
      'PATH=G:\proyectos\programador\bd'
      'DEFAULT DRIVER=PARADOX'
      'ENABLE BCD=FALSE')
    SessionName = 'Default'
    TransIsolation = tiDirtyRead
    Left = 24
    Top = 8
  end
  object TFabricante: TTable
    DatabaseName = 'Disp'
    FieldDefs = <
      item
        Name = 'CODIGO'
        Attributes = [faRequired]
        DataType = ftSmallint
      end
      item
        Name = 'NOMBRE'
        DataType = ftString
        Size = 30
      end>
    IndexDefs = <
      item
        Name = 'TFabricanteIndex1'
        Fields = 'CODIGO'
        Options = [ixPrimary, ixUnique]
      end>
    IndexFieldNames = 'CODIGO'
    StoreDefs = True
    TableName = 'fabricante.DB'
    Left = 24
    Top = 56
    object TFabricanteCODIGO: TSmallintField
      FieldName = 'CODIGO'
      Required = True
      OnGetText = T8bitsHexGetText
      OnSetText = T8bitsHexSetText
    end
    object TFabricanteNOMBRE: TStringField
      FieldName = 'NOMBRE'
      Size = 30
    end
  end
  object DSFabricante: TDataSource
    DataSet = TFabricante
    Left = 24
    Top = 104
  end
  object TJuegoComandos: TTable
    DatabaseName = 'Disp'
    TableName = 'juego_comandos'
    Left = 256
    Top = 56
  end
  object TComando: TTable
    DatabaseName = 'Disp'
    IndexFieldNames = 'JUEGO_COMANDOS'
    MasterFields = 'ID'
    MasterSource = DSJuegoComando
    TableName = 'comando.DB'
    Left = 168
    Top = 56
  end
  object DSJuegoComando: TDataSource
    DataSet = TJuegoComandos
    Left = 256
    Top = 104
  end
  object DSComando: TDataSource
    DataSet = TComando
    Left = 168
    Top = 104
  end
  object TDispositivo: TTable
    DatabaseName = 'Disp'
    IndexFieldNames = 'CODIGO_FABRICANTE;ID'
    MasterFields = 'CODIGO'
    MasterSource = DSFabricante
    TableName = 'dispositivo.DB'
    Left = 96
    Top = 56
    object TDispositivoID: TSmallintField
      DisplayWidth = 10
      FieldName = 'ID'
      Required = True
      OnGetText = T8bitsHexGetText
      OnSetText = T8bitsHexSetText
      MaxValue = 255
    end
    object TDispositivoCODIGO_FABRICANTE: TSmallintField
      FieldName = 'CODIGO_FABRICANTE'
      Required = True
      OnGetText = T8bitsHexGetText
      OnSetText = T8bitsHexSetText
    end
    object TDispositivoNOMBRE: TStringField
      FieldName = 'NOMBRE'
      Required = True
    end
    object TDispositivoNUM_PINES: TSmallintField
      FieldName = 'NUM_PINES'
      Required = True
    end
    object TDispositivoTIPO: TSmallintField
      FieldName = 'TIPO'
      Required = True
    end
    object TDispositivoJUEGO_COMANDOS: TSmallintField
      FieldName = 'JUEGO_COMANDOS'
      Required = True
    end
    object TDispositivoTAMANYO: TIntegerField
      FieldName = 'TAMANYO'
      Required = True
    end
    object TDispositivoTAMANYO_PAGINA: TIntegerField
      FieldName = 'TAMANYO_PAGINA'
      Required = True
    end
  end
  object DSDispositivo: TDataSource
    DataSet = TDispositivo
    Left = 96
    Top = 104
  end
  object TJuegoComandosAux: TTable
    DatabaseName = 'Disp'
    TableName = 'juego_comandos'
    Left = 352
    Top = 184
  end
  object TComandoAux: TTable
    DatabaseName = 'Disp'
    IndexFieldNames = 'JUEGO_COMANDOS'
    MasterFields = 'ID'
    MasterSource = DSJuegoComando
    TableName = 'comando.DB'
    Left = 256
    Top = 184
  end
  object TFabricanteAux: TTable
    DatabaseName = 'Disp'
    TableName = 'fabricante.DB'
    Left = 32
    Top = 184
    object TFabricanteAuxCODIGO: TSmallintField
      FieldName = 'CODIGO'
      Required = True
      OnGetText = T8bitsHexGetText
      OnSetText = T8bitsHexSetText
      MaxValue = 255
    end
    object TFabricanteAuxNOMBRE: TStringField
      FieldName = 'NOMBRE'
      Size = 30
    end
  end
  object DSFabricanteAux: TDataSource
    DataSet = TFabricanteAux
    Left = 32
    Top = 232
  end
  object TSector: TTable
    BeforeInsert = TSectorBeforeInsert
    AfterInsert = TSectorAfterInsert
    OnCalcFields = TSectorCalcFields
    DatabaseName = 'Disp'
    FieldDefs = <
      item
        Name = 'CODIGO_FABRICANTE'
        Attributes = [faRequired]
        DataType = ftSmallint
      end
      item
        Name = 'ID_DISPOSITIVO'
        Attributes = [faRequired]
        DataType = ftSmallint
      end
      item
        Name = 'DIRECCION_COMIENZO'
        Attributes = [faRequired]
        DataType = ftInteger
      end
      item
        Name = 'NUMERO'
        DataType = ftInteger
      end
      item
        Name = 'LONGITUD'
        Attributes = [faRequired]
        DataType = ftInteger
      end>
    IndexFieldNames = 'CODIGO_FABRICANTE;ID_DISPOSITIVO'
    MasterFields = 'CODIGO_FABRICANTE;ID'
    MasterSource = DSDispositivo
    StoreDefs = True
    TableName = 'lista_sectores.DB'
    Left = 344
    Top = 56
    object TSectorCODIGO_FABRICANTE: TSmallintField
      FieldName = 'CODIGO_FABRICANTE'
      Required = True
    end
    object TSectorID_DISPOSITIVO: TSmallintField
      FieldName = 'ID_DISPOSITIVO'
      Required = True
    end
    object TSectorDIRECCION_COMIENZO: TIntegerField
      Alignment = taCenter
      FieldName = 'DIRECCION_COMIENZO'
      Required = True
      OnGetText = T20bitsHexGetText
      OnSetText = T20bitsSetText
    end
    object TSectorNUMERO: TIntegerField
      Alignment = taCenter
      FieldName = 'NUMERO'
    end
    object TSectorLONGITUD: TIntegerField
      Alignment = taCenter
      FieldName = 'LONGITUD'
      Required = True
    end
    object TSectorDIRECCION_FINAL: TStringField
      Alignment = taCenter
      FieldKind = fkCalculated
      FieldName = 'DIRECCION_FINAL'
      Calculated = True
    end
    object TSectorLONGITUD_TOTAL: TStringField
      Alignment = taCenter
      DisplayWidth = 20
      FieldKind = fkCalculated
      FieldName = 'TAMANYO_TOTAL'
      Calculated = True
    end
  end
  object DSListaSectores: TDataSource
    DataSet = TSector
    Left = 344
    Top = 104
  end
  object TDispositivoAux: TTable
    DatabaseName = 'Disp'
    TableName = 'dispositivo.DB'
    Left = 176
    Top = 184
  end
  object TSectorAux: TTable
    DatabaseName = 'Disp'
    TableName = 'lista_sectores.DB'
    Left = 104
    Top = 184
  end
  object TFabricanteInt: TTable
    DatabaseName = 'Disp'
    TableName = 'fabricante.db'
    Left = 152
    Top = 304
  end
  object DSFabricanteInt: TDataSource
    DataSet = TFabricanteInt
    Left = 152
    Top = 352
  end
  object TDispositivoInt: TTable
    DatabaseName = 'Disp'
    IndexFieldNames = 'CODIGO_FABRICANTE;ID'
    MasterFields = 'CODIGO'
    MasterSource = DSFabricanteInt
    TableName = 'dispositivo.DB'
    Left = 240
    Top = 304
  end
  object DSDispositivoInt: TDataSource
    DataSet = TDispositivoInt
    Left = 240
    Top = 352
  end
  object DSJuegoComandosInt: TDataSource
    DataSet = TJuegoComandosAux
    Left = 328
    Top = 352
  end
  object TJuegoComandosInt: TTable
    DatabaseName = 'Disp'
    TableName = 'juego_comandos.db'
    Left = 328
    Top = 304
  end
  object TComandoInt: TTable
    DatabaseName = 'Disp'
    IndexFieldNames = 'JUEGO_COMANDOS'
    MasterFields = 'ID'
    MasterSource = DSJuegoComandosInt
    TableName = 'comando.DB'
    Left = 424
    Top = 304
  end
  object DSComandoInt: TDataSource
    DataSet = TComandoInt
    Left = 424
    Top = 352
  end
end
