object frmScanParam: TfrmScanParam
  Left = 412
  Top = 229
  BorderStyle = bsDialog
  Caption = 'Параметры сканирования'
  ClientHeight = 233
  ClientWidth = 237
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 12
    Top = 40
    Width = 51
    Height = 13
    Caption = 'Длина, мм'
  end
  object Label2: TLabel
    Left = 12
    Top = 68
    Width = 59
    Height = 13
    Caption = 'Ширина, мм'
  end
  object Edit1: TEdit
    Left = 96
    Top = 36
    Width = 121
    Height = 21
    TabOrder = 0
    Text = '50'
  end
  object Edit2: TEdit
    Left = 96
    Top = 64
    Width = 121
    Height = 21
    TabOrder = 1
    Text = '50'
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 92
    Width = 221
    Height = 77
    Caption = 'Параметры дискретизации'
    TabOrder = 2
    object Label3: TLabel
      Left = 8
      Top = 48
      Width = 73
      Height = 13
      Caption = 'По ширине, мм'
    end
    object Label4: TLabel
      Left = 8
      Top = 20
      Width = 66
      Height = 13
      Caption = 'По длине, мм'
    end
    object Edit3: TEdit
      Left = 88
      Top = 16
      Width = 121
      Height = 21
      TabOrder = 0
      Text = '1'
    end
    object Edit4: TEdit
      Left = 88
      Top = 44
      Width = 121
      Height = 21
      TabOrder = 1
      Text = '1'
    end
  end
  object Button1: TButton
    Left = 148
    Top = 200
    Width = 75
    Height = 25
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 3
  end
  object Button2: TButton
    Left = 12
    Top = 200
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Отмена'
    ModalResult = 2
    TabOrder = 4
  end
end
