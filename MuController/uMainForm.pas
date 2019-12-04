unit uMainForm;

interface

uses
  Windows, SysUtils, Messages, Graphics, Controls, Forms,
  XpMan, StdCtrls, ComCtrls, Classes, ExtCtrls, Menus;

type
  TShareMemory = record
    // Key of protection based on Timer
    KeyProtect     : DWORD;
    // FastPot
    FastPotKey     : DWORD;
    FastPotTimer   : DWORD;
    FastPotStatus  : BOOLEAN;
    // OneHit
    OneHitKey      : DWORD;
    OneHitTimer    : DWORD;
    OneHitStatus   : BOOLEAN;
    // GameSpeed
    GameSpeedTimer : DWORD;
    // Target Functions
    PullEnable     : BOOLEAN;
    TraceEnable    : BOOLEAN;
    AimbotEnable   : BOOLEAN;
    // Auto Trade
    AutoTradeEnable: BOOLEAN;
    // Auto Kill                
    AutoKillRange  : DWORD;
    AutoKillTimer  : DWORD;
    AutoKillStatus : BOOLEAN;
    // Targets Selected
    Targets        : Array[0..10 { Total }, 0..10 { Nickname Size }] of Char;
  end;
  PShareMemory = ^TShareMemory;
  TMainForm = class(TForm)
    GBBattleFunctions: TGroupBox;
    GBOneHit: TGroupBox;
    GBFastPot: TGroupBox;
    CBOneHit: TCheckBox;
    TBOneHit: TTrackBar;
    CBFastPot: TCheckBox;
    TBFastPot: TTrackBar;
    GBUtilities: TGroupBox;
    GBGameSpeed: TGroupBox;
    CBGameSpeed: TCheckBox;
    TBGameSpeed: TTrackBar;
    GBTargets: TGroupBox;
    LVTargets: TListView;
    BAdd: TButton;
    ETarget: TEdit;
    GBTargetsFunctions: TGroupBox;
    CBPull: TCheckBox;
    CBTrace: TCheckBox;
    CBAimbot: TCheckBox;
    CBAutoTrade: TCheckBox;
    FormController: TTimer;
    StatusBar: TStatusBar;
    KeyFastPot: TComboBox;
    KeyOneHit: TComboBox;
    KeyGameSpeed: TComboBox;
    MemoryCache: TTimer;
    GBAutoKill: TGroupBox;
    CBAutoKill: TCheckBox;
    TBAutoKillSpeed: TTrackBar;
    TBAutoKillRange: TTrackBar;
    procedure FormCreate(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure FormControllerTimer(Sender: TObject);
    procedure BHideClick(Sender: TObject);
    procedure MemoryCacheTimer(Sender: TObject);
    procedure BAddClick(Sender: TObject);
    procedure LVTargetsDblClick(Sender: TObject);
    procedure ETargetKeyDown(Sender: TObject; var Key: Word; Shift: TShiftState);
  private
    procedure MessageToClose(szMessage : String; szTitle : String = 'Error'; dwType: Cardinal = (MB_OK or MB_ICONERROR));
    function GetKeyIndex(Keys : TComboBox) : DWORD;
  public
    { Public declarations }
  end;

var                                 
  KeyClient             : DWORD = 0;
  KeyServer             : DWORD = 0;
  MainForm              : TMainForm;
  hShareMemory          : THandle;
  ShareMemory           : PShareMemory;

implementation

{$R *.dfm}

procedure TMainForm.MessageToClose(szMessage : String; szTitle : String = 'Error'; dwType: Cardinal = (MB_OK or MB_ICONERROR));
begin
    MessageBoxA(0, PAnsiChar(szMessage), PAnsiChar(szTitle), dwType);
    Application.Terminate();
end;

function TMainForm.GetKeyIndex(Keys : TComboBox) : DWORD;
begin
  case Keys.ItemIndex of
    { ALT }
    0: Result := VK_LMENU;
    { CTRL }
    1: Result := VK_LCONTROL;
    { SHIFT }
    2: Result := VK_LSHIFT;
    { SPACE }
    3: Result := VK_SPACE;
    { Q }
    4: Result := ord('Q');
    { W }
    5: Result := ord('W');
    { E }
    6: Result := ord('E');
    { RMouse }
    7: Result := VK_RBUTTON;
    else
      Result := 0;
  end;
end;

procedure TMainForm.FormCreate(Sender: TObject);
begin
  // Create handle to memory file
  hShareMemory := CreateFileMapping($FFFFFFFF, nil, PAGE_READWRITE, 0, SizeOf(TShareMemory), 'Global\MappingCheatsUnknown');
  // Check multiple instance
  if (GetLastError = ERROR_ALREADY_EXISTS) then
    Self.MessageToClose('Error 0x0001: An open instance already exists.')
  // Check handle to memory file
  else if (hShareMemory = 0) then
    Self.MessageToClose(
      'Error 0x0002: Parameter initialization failed.' + #13 +
      'Try Again with Privileges of Administrator.'
    )
  else begin
    // Take pointer to memory shared
    ShareMemory := MapViewOfFile(hShareMemory, FILE_MAP_WRITE, 0, 0, 0);
    // Initialize timers
    FormController.Enabled := True;
    MemoryCache.Enabled    := True;
    // Show mainform
    Self.Show;
  end;
end;

procedure TMainForm.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  // Free Memory
  UnMapViewOfFile(ShareMemory);
  // Close Handle
  CloseHandle(hShareMemory);
end;

procedure TMainForm.FormControllerTimer(Sender: TObject);
begin
  // Authenticate Cracked, critical block.
  if (((KeyClient + $F2) xor $C3) <> KeyServer) then
    Self.Close;
  // Print position of TrackBars
  CBGameSpeed.Caption := Format('Enable - %d', [TBGameSpeed.Position]);
  CBFastPot.Caption   := Format('Enable - %d', [TBFastPot.Position]);
  CBOneHit.Caption    := Format('Enable - %d', [TBOneHit.Position]);
  CBAutoKill.Caption  := Format('Enable - %d/%d', [TBAutoKillSpeed.Position, TBAutoKillRange.Position]);
  // Keyboard to Restore
  if GetKeyState(VK_F12) < 0 then
    Application.Restore
end;

procedure TMainForm.BHideClick(Sender: TObject);
begin
  Application.Minimize;
end;

procedure TMainForm.MemoryCacheTimer(Sender: TObject);
var
  I : Integer;
begin
  // Authenticate Cracked, critical block.
  if (((KeyClient + $F2) xor $C3) <> KeyServer) then Exit;
  // Memory Protect
  ShareMemory^.KeyProtect      := GetTickCount();
  // FastPot Control
  ShareMemory^.FastPotKey      := Self.GetKeyIndex(KeyFastPot);
  ShareMemory^.FastPotStatus   := CBFastPot.Checked;
  ShareMemory^.FastPotTimer    := TBFastPot.Max - TBFastPot.Position;
  // OneHit Control
  ShareMemory^.OneHitKey       := Self.GetKeyIndex(KeyOneHit);
  ShareMemory^.OneHitStatus    := CBOneHit.Checked;
  ShareMemory^.OneHitTimer     := TBOneHit.Max - TBOneHit.Position;
  // GameSpeed Control
  if (GetKeyState(Self.GetKeyIndex(KeyGameSpeed)) < 0) and (CBGameSpeed.Checked) then
  begin
    ShareMemory^.GameSpeedTimer  := TBGameSpeed.Position;
  end else begin
    ShareMemory^.GameSpeedTimer  := 0;
  end;
  // Enable Disable target functions
  ShareMemory^.PullEnable      := CBPull.Checked;
  ShareMemory^.TraceEnable     := CBTrace.Checked;
  ShareMemory^.AimbotEnable    := CBAimbot.Checked;
  ShareMemory^.AutoTradeEnable := CBAutoTrade.Checked;
  // Auto Kill
  ShareMemory^.AutoKillStatus  := CBAutoKill.Checked;
  ShareMemory^.AutoKillTimer   := TBAutoKillSpeed.Max - TBAutoKillSpeed.Position;
  ShareMemory^.AutoKillRange   := TBAutoKillRange.Position;
  // Targets
  for I := 0 to Length(ShareMemory^.Targets) - 1 do
  begin
    if (I <= LVTargets.Items.Count - 1) then
    begin
      MoveMemory(@ShareMemory^.Targets[I], @LVTargets.Items.Item[I].Caption[1],
          Length(LVTargets.Items.Item[I].Caption));
    end else begin
      ZeroMemory(@ShareMemory^.Targets[I], SizeOf(ShareMemory^.Targets[I]));
    end;
  end;
end;

procedure TMainForm.BAddClick(Sender: TObject);
 var
  I: Integer;
begin
  // Check already exists nickname.
  for I := 0 to LVTargets.Items.Count-1 do
    if (LowerCase(ETarget.Text) = LVTargets.Items.Item[I].Caption) then
    begin
      MessageBoxA(0, 'The selected player already exists in the list.', 'ERROR', MB_OK or MB_ICONERROR);
      Exit;
    end;
  // Check have nickname in edit
  if (ETarget.Text = EmptyStr) then
  begin
    MessageBoxA(0, 'Fill the field of nickname.', 'ERROR', MB_OK or MB_ICONERROR);
    ETarget.Clear;
    Exit;
  end;
  // Add new target
  LVTargets.Items.Add.Caption := LowerCase(ETarget.Text);
  // Clear input
  ETarget.Clear;
end;

procedure TMainForm.LVTargetsDblClick(Sender: TObject);
begin
  // Double click remove selected target
  LVTargets.DeleteSelected;
end;

procedure TMainForm.ETargetKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  // Enter confirm add
  if Key = 13 then
    BAdd.Click;
end;

end.
