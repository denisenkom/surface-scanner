object ScanningForm: TScanningForm
  Left = 422
  Top = 287
  BorderStyle = bsDialog
  Caption = 'Сканирование'
  ClientHeight = 98
  ClientWidth = 174
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Process: TProgressBar
    Left = 16
    Top = 16
    Width = 150
    Height = 16
    Min = 0
    Max = 100
    TabOrder = 0
  end
  object SubProcess: TProgressBar
    Left = 16
    Top = 40
    Width = 150
    Height = 16
    Min = 0
    Max = 100
    TabOrder = 1
  end
  object ButtonCancel: TButton
    Left = 88
    Top = 64
    Width = 75
    Height = 25
    Caption = 'Отмена'
    TabOrder = 2
    OnClick = ButtonCancelClick
  end
  object Timer1: TTimer
    Interval = 100
    OnTimer = Timer1Timer
    Left = 24
    Top = 64
  end
end
