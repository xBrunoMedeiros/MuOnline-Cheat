object MainForm: TMainForm
  Left = 202
  Top = 116
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'CheatsUnknown - MuOnline'
  ClientHeight = 331
  ClientWidth = 649
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object GBBattleFunctions: TGroupBox
    Left = 8
    Top = 0
    Width = 409
    Height = 121
    Caption = 'Battle Functions'
    TabOrder = 0
    object GBOneHit: TGroupBox
      Left = 208
      Top = 24
      Width = 185
      Height = 81
      Caption = 'OneHit'
      TabOrder = 1
      object CBOneHit: TCheckBox
        Left = 16
        Top = 24
        Width = 160
        Height = 17
        Caption = 'Enable'
        TabOrder = 0
      end
      object TBOneHit: TTrackBar
        Left = 2
        Top = 50
        Width = 181
        Height = 29
        Align = alBottom
        Max = 30
        Frequency = 3
        Position = 15
        TabOrder = 1
        ThumbLength = 15
      end
      object KeyOneHit: TComboBox
        Left = 104
        Top = 20
        Width = 73
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        ItemIndex = 3
        TabOrder = 2
        Text = 'SPACE'
        Items.Strings = (
          'ALT'
          'CTRL'
          'SHIFT'
          'SPACE'
          'Q'
          'W'
          'E'
          'RMouse')
      end
    end
    object GBFastPot: TGroupBox
      Left = 16
      Top = 24
      Width = 185
      Height = 81
      Caption = 'FastPot'
      TabOrder = 0
      object CBFastPot: TCheckBox
        Left = 16
        Top = 24
        Width = 160
        Height = 17
        Caption = 'Enable'
        TabOrder = 0
      end
      object TBFastPot: TTrackBar
        Left = 2
        Top = 50
        Width = 181
        Height = 29
        Align = alBottom
        Max = 500
        Frequency = 50
        Position = 15
        TabOrder = 1
        ThumbLength = 15
      end
      object KeyFastPot: TComboBox
        Left = 104
        Top = 20
        Width = 73
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        ItemIndex = 1
        TabOrder = 2
        Text = 'CTRL'
        Items.Strings = (
          'ALT'
          'CTRL'
          'SHIFT'
          'SPACE'
          'Q'
          'W'
          'E'
          'RMouse')
      end
    end
  end
  object GBUtilities: TGroupBox
    Left = 424
    Top = 0
    Width = 217
    Height = 305
    Caption = 'Utilities'
    TabOrder = 1
    object GBGameSpeed: TGroupBox
      Left = 16
      Top = 24
      Width = 185
      Height = 81
      Caption = 'GameSpeed'
      TabOrder = 0
      object CBGameSpeed: TCheckBox
        Left = 16
        Top = 24
        Width = 160
        Height = 17
        Caption = 'Enable'
        TabOrder = 0
      end
      object TBGameSpeed: TTrackBar
        Left = 2
        Top = 50
        Width = 181
        Height = 29
        Align = alBottom
        Max = 300
        Frequency = 30
        Position = 100
        TabOrder = 1
        ThumbLength = 15
      end
      object KeyGameSpeed: TComboBox
        Left = 104
        Top = 20
        Width = 73
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        ItemIndex = 1
        TabOrder = 2
        Text = 'CTRL'
        Items.Strings = (
          'ALT'
          'CTRL'
          'SHIFT'
          'SPACE'
          'Q'
          'W'
          'E'
          'RMouse')
      end
    end
    object GBTargetsFunctions: TGroupBox
      Left = 16
      Top = 112
      Width = 185
      Height = 97
      Caption = 'Targets Functions'
      TabOrder = 1
      object CBPull: TCheckBox
        Left = 8
        Top = 24
        Width = 81
        Height = 17
        Caption = 'Pull (Targets)'
        Enabled = False
        TabOrder = 0
      end
      object CBTrace: TCheckBox
        Left = 8
        Top = 40
        Width = 97
        Height = 17
        Caption = 'Trace (Target)'
        Enabled = False
        TabOrder = 1
      end
      object CBAimbot: TCheckBox
        Left = 8
        Top = 56
        Width = 97
        Height = 17
        Caption = 'Aimbot (Target)'
        Enabled = False
        TabOrder = 2
      end
      object CBAutoTrade: TCheckBox
        Left = 8
        Top = 72
        Width = 113
        Height = 17
        Caption = 'Auto Trade (Target)'
        Enabled = False
        TabOrder = 3
      end
    end
    object GBAutoKill: TGroupBox
      Left = 16
      Top = 216
      Width = 185
      Height = 73
      Caption = 'Auto Kill'
      TabOrder = 2
      object CBAutoKill: TCheckBox
        Left = 16
        Top = 18
        Width = 105
        Height = 17
        Caption = 'Enable'
        TabOrder = 0
      end
      object TBAutoKillSpeed: TTrackBar
        Left = 2
        Top = 42
        Width = 181
        Height = 29
        Align = alBottom
        Max = 100
        Frequency = 10
        Position = 75
        TabOrder = 1
        ThumbLength = 15
      end
      object TBAutoKillRange: TTrackBar
        Left = 120
        Top = 15
        Width = 63
        Height = 27
        Align = alRight
        Max = 1000
        Min = 150
        Frequency = 300
        Position = 300
        TabOrder = 2
        ThumbLength = 15
      end
    end
  end
  object GBTargets: TGroupBox
    Left = 8
    Top = 128
    Width = 409
    Height = 177
    Caption = 'Targets'
    TabOrder = 2
    object LVTargets: TListView
      Left = 8
      Top = 16
      Width = 393
      Height = 129
      Columns = <
        item
          AutoSize = True
          Caption = 'Nickname'
        end>
      GridLines = True
      ReadOnly = True
      RowSelect = True
      TabOrder = 2
      ViewStyle = vsReport
      OnDblClick = LVTargetsDblClick
    end
    object BAdd: TButton
      Left = 8
      Top = 146
      Width = 105
      Height = 26
      Caption = 'Add'
      TabOrder = 1
      OnClick = BAddClick
    end
    object ETarget: TEdit
      Left = 120
      Top = 149
      Width = 281
      Height = 21
      MaxLength = 10
      TabOrder = 0
      OnKeyDown = ETargetKeyDown
    end
  end
  object StatusBar: TStatusBar
    Left = 0
    Top = 312
    Width = 649
    Height = 19
    Panels = <
      item
        Text = 'Status: Running'
        Width = 150
      end
      item
        Alignment = taCenter
        Text = 'Licensed to %s, CheatsUnknown MuOnline97d '
        Width = 50
      end>
  end
  object FormController: TTimer
    Enabled = False
    Interval = 100
    OnTimer = FormControllerTimer
    Left = 576
    Top = 8
  end
  object MemoryCache: TTimer
    Enabled = False
    Interval = 50
    OnTimer = MemoryCacheTimer
    Left = 608
    Top = 8
  end
end
