object ProfilometrForm: TProfilometrForm
  Left = 351
  Top = 174
  Width = 492
  Height = 211
  Caption = 'Параметры'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poMainFormCenter
  ShowHint = True
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 484
    Height = 177
    Align = alClient
    BevelInner = bvLowered
    BevelOuter = bvLowered
    Caption = 'Panel1'
    TabOrder = 0
    object PageControl1: TPageControl
      Left = 2
      Top = 2
      Width = 480
      Height = 173
      ActivePage = TabSheet4
      Align = alClient
      TabOrder = 0
      object TabSheet1: TTabSheet
        Hint = 'Шаговый двигатель'
        Caption = 'ШД'
        OnShow = TabSheet1Show
        object Label2: TLabel
          Left = 16
          Top = 56
          Width = 53
          Height = 13
          Hint = 'Количество шагов в одном миллиметре'
          Caption = 'Шагов/мм:'
          ParentShowHint = False
          ShowHint = True
        end
        object Label3: TLabel
          Left = 16
          Top = 24
          Width = 131
          Height = 13
          Caption = 'Текущее положение (мм):'
        end
        object SDPosEdit: TEdit
          Left = 152
          Top = 24
          Width = 73
          Height = 21
          TabOrder = 0
          OnExit = SDPosEditExit
        end
        object StepsPerMmEdit: TEdit
          Left = 80
          Top = 56
          Width = 73
          Height = 21
          TabOrder = 1
          OnExit = StepsPerMmEditExit
        end
      end
      object TabSheet3: TTabSheet
        Hint = 'Аналого-цифровой преобразователь'
        Caption = 'АЦП'
        ImageIndex = 2
        object Label6: TLabel
          Left = 8
          Top = 16
          Width = 87
          Height = 13
          Caption = 'Множитель АЦП:'
        end
        object Label7: TLabel
          Left = 8
          Top = 48
          Width = 52
          Height = 13
          Caption = 'Значение:'
        end
        object EditADC: TEdit
          Left = 104
          Top = 48
          Width = 121
          Height = 21
          ReadOnly = True
          TabOrder = 0
        end
        object ButtonReadADC: TButton
          Left = 232
          Top = 48
          Width = 75
          Height = 25
          Caption = 'Считать'
          TabOrder = 1
          OnClick = ButtonReadADCClick
        end
        object ADCMultiplierEdit: TEdit
          Left = 104
          Top = 16
          Width = 121
          Height = 21
          TabOrder = 2
          OnExit = ADCMultiplierEditExit
        end
      end
      object TabSheet4: TTabSheet
        Caption = 'COM Порт'
        ImageIndex = 3
        object Label4: TLabel
          Left = 16
          Top = 56
          Width = 36
          Height = 13
          Caption = 'Режим:'
        end
        object Label5: TLabel
          Left = 16
          Top = 16
          Width = 29
          Height = 13
          Caption = 'Порт:'
        end
        object ComboBoxPort: TComboBox
          Left = 64
          Top = 16
          Width = 97
          Height = 21
          ItemHeight = 13
          TabOrder = 0
          Text = 'COM1'
          OnChange = ComboBoxPortChange
          Items.Strings = (
            'COM1'
            'COM2'
            'COM3'
            'COM4')
        end
        object PortModeEdit: TEdit
          Left = 64
          Top = 56
          Width = 369
          Height = 21
          TabOrder = 1
          Text = 'baud=19200'
          OnChange = PortModeEditChange
        end
        object TestButton: TButton
          Left = 72
          Top = 96
          Width = 153
          Height = 25
          Caption = 'Проверить соединение'
          TabOrder = 2
          OnClick = TestButtonClick
        end
      end
      object TabSheet5: TTabSheet
        Caption = 'Клавиши'
        ImageIndex = 5
        object ButtonsStringGrid: TStringGrid
          Left = 0
          Top = 0
          Width = 472
          Height = 145
          Hint = 'Коды клавиш посылаемые на дешифратор'
          Align = alClient
          ColCount = 2
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRowSizing, goColSizing, goRowMoving, goEditing, goThumbTracking]
          TabOrder = 0
          OnSetEditText = ButtonsStringGridSetEditText
        end
      end
      object TabSheet2: TTabSheet
        Hint = 'Панель управления электронным блоком'
        Caption = 'Эл. блок'
        ImageIndex = 1
        object Ra: TButton
          Left = 368
          Top = 32
          Width = 25
          Height = 25
          Caption = 'Ra'
          TabOrder = 0
          OnClick = RaClick
        end
        object Rz: TButton
          Left = 392
          Top = 32
          Width = 25
          Height = 25
          Caption = 'Rz'
          TabOrder = 1
          OnClick = RzClick
        end
        object Rmax: TButton
          Left = 416
          Top = 32
          Width = 25
          Height = 25
          Caption = 'Rmax'
          TabOrder = 2
          OnClick = RmaxClick
        end
        object Rp: TButton
          Left = 440
          Top = 32
          Width = 25
          Height = 25
          Caption = 'Rp'
          TabOrder = 3
          OnClick = RpClick
        end
        object Sm: TButton
          Left = 368
          Top = 56
          Width = 25
          Height = 25
          Caption = 'Sm'
          TabOrder = 4
          OnClick = SmClick
        end
        object DID: TButton
          Left = 392
          Top = 56
          Width = 25
          Height = 25
          Hint = 'Вкл/выкл дисплея'
          TabOrder = 5
          OnClick = DIDClick
        end
        object t5: TButton
          Left = 416
          Top = 56
          Width = 25
          Height = 25
          Caption = 't5'
          TabOrder = 6
          OnClick = t5Click
        end
        object t10: TButton
          Left = 440
          Top = 56
          Width = 25
          Height = 25
          Caption = 't10'
          TabOrder = 7
          OnClick = t10Click
        end
        object t20: TButton
          Left = 368
          Top = 80
          Width = 25
          Height = 25
          Caption = 't20'
          TabOrder = 8
          OnClick = t20Click
        end
        object t30: TButton
          Left = 392
          Top = 80
          Width = 25
          Height = 25
          Caption = 't30'
          TabOrder = 9
          OnClick = t30Click
        end
        object t40: TButton
          Left = 416
          Top = 80
          Width = 25
          Height = 25
          Caption = 't40'
          TabOrder = 10
          OnClick = t40Click
        end
        object t50: TButton
          Left = 440
          Top = 80
          Width = 25
          Height = 25
          Caption = 't50'
          TabOrder = 11
          OnClick = t50Click
        end
        object t60: TButton
          Left = 368
          Top = 104
          Width = 25
          Height = 25
          Caption = 't60'
          TabOrder = 12
          OnClick = t60Click
        end
        object t70: TButton
          Left = 392
          Top = 104
          Width = 25
          Height = 25
          Caption = 't70'
          TabOrder = 13
          OnClick = t70Click
        end
        object t80: TButton
          Left = 416
          Top = 104
          Width = 25
          Height = 25
          Caption = 't80'
          TabOrder = 14
          OnClick = t80Click
        end
        object t90: TButton
          Left = 440
          Top = 104
          Width = 25
          Height = 25
          Caption = 't90'
          TabOrder = 15
          OnClick = t90Click
        end
        object EditDID: TEdit
          Left = 232
          Top = 32
          Width = 121
          Height = 21
          Hint = 'Щелкните по полю чтобы обновить значение на дисплее'
          TabStop = False
          ReadOnly = True
          TabOrder = 16
          OnClick = EditDIDClick
        end
        object GroupBox1: TGroupBox
          Left = 232
          Top = 80
          Width = 121
          Height = 49
          Caption = 'Трассирование'
          TabOrder = 17
          object ButtonLength: TSpeedButton
            Left = 64
            Top = 16
            Width = 25
            Height = 25
            Hint = 'Базовая длина'
            AllowAllUp = True
            GroupIndex = 1
            Caption = 'L'
            OnClick = ButtonLengthClick
          end
          object ButtonStop: TButton
            Left = 8
            Top = 16
            Width = 25
            Height = 25
            Hint = 'Стоп'
            Caption = '|'
            TabOrder = 0
            OnClick = ButtonStopClick
          end
          object ButtonStartScan: TButton
            Left = 32
            Top = 16
            Width = 25
            Height = 25
            Hint = 'Пуск'
            Caption = '->'
            TabOrder = 1
            OnClick = ButtonStartScanClick
          end
          object ButtonReverse: TButton
            Left = 88
            Top = 16
            Width = 27
            Height = 25
            Hint = 'Реверс'
            Caption = '<--'
            TabOrder = 2
            OnClick = ButtonReverseClick
          end
        end
        object GroupBox2: TGroupBox
          Left = 160
          Top = 80
          Width = 65
          Height = 49
          Caption = 'Сигнал'
          TabOrder = 18
          object ButtonLF: TSpeedButton
            Left = 8
            Top = 16
            Width = 25
            Height = 25
            Hint = 'Низкочастотная составляющая'
            AllowAllUp = True
            GroupIndex = 1
            Caption = 'НЧ'
            OnClick = ButtonLFClick
          end
          object ButtonHF: TSpeedButton
            Left = 32
            Top = 16
            Width = 25
            Height = 25
            Hint = 'Высокочастотная составляющая'
            AllowAllUp = True
            GroupIndex = 2
            Caption = 'ВЧ'
            OnClick = ButtonHFClick
          end
        end
        object GroupBox3: TGroupBox
          Left = 32
          Top = 80
          Width = 121
          Height = 49
          Caption = 'Увеличение/Фильтр'
          TabOrder = 19
          object ButtonScaleFilter: TSpeedButton
            Left = 8
            Top = 16
            Width = 25
            Height = 25
            Hint = 'Переключает режим увеличение/фильтр'
            AllowAllUp = True
            GroupIndex = 1
            Caption = 'У'
            OnClick = ButtonScaleFilterClick
          end
          object Button8: TButton
            Left = 64
            Top = 16
            Width = 25
            Height = 25
            Caption = '+'
            TabOrder = 0
            OnClick = Button8Click
          end
          object Button9: TButton
            Left = 88
            Top = 16
            Width = 25
            Height = 25
            Caption = '-'
            TabOrder = 1
            OnClick = Button9Click
          end
        end
        object EditDIDFilter: TEdit
          Left = 32
          Top = 32
          Width = 121
          Height = 21
          ReadOnly = True
          TabOrder = 20
        end
        object OnOff: TButton
          Left = 0
          Top = 96
          Width = 25
          Height = 25
          Hint = 'Вкл/выкл'
          Caption = 'Вкл'
          TabOrder = 21
          OnClick = OnOffClick
        end
      end
    end
  end
end
