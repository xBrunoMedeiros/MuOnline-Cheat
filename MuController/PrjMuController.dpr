program PrjMuController;

uses
  Windows, SysUtils, IdHttp, Classes, Forms,
  uMainForm in 'uMainForm.pas' {MainForm},
  uTools in 'uTools.pas';

{$R .\Resources\PrjMuController.res}
{$R .\Resources\UAC.res}

var
  // -------------- Product Info ---------------
  ClientUserId  : PDWORD;
  ProductId     : DWORD = 1;
  ProductVersion: DWORD = 1;
  WebAuth       : String = 'http://www.CheatsUnknown.net/Painel/Trainer.php';
  WebSintaxe    : String = '?Key=%d&ProductId=%d&ProductVersion=%d&UserId=%d&UserMac=%s';
  // -------------------------------------------

var
  GameProcessId : DWORD;
  AuthResult    : TStringList;
begin
  { Initialize }
  AllocConsole;
  { Access User Id }
  ClientUserId := PDWORD(GetModuleHandleA(nil) + $50);
  { Logo }
  WriteLn('  ______ _                          _     _       _                             ');
  WriteLn(' / _____) |               _        | |   | |     | |                            ');
  WriteLn('| /     | | _   ____ ____| |_   ___| |   | |____ | |  _ ____   ___  _ _ _ ____  ');
  WriteLn('| |     | || \ / _  ) _  |  _) /___) |   | |  _ \| | / )  _ \ / _ \| | | |  _ \ ');
  WriteLn('| \_____| | | ( (/ ( ( | | |__|___ | |___| | | | | |< (| | | | |_| | | | | | | |');
  WriteLn(' \______)_| |_|\____)_||_|\___|___/ \______|_| |_|_| \_)_| |_|\___/ \____|_| |_|');
  WriteLn(#13 + #13);
  WriteLn('--------------------------------------------------------------------------------');
  { Create Client Key }
  Randomize;
  KeyClient := Random(99999);
  { Create Auth Result }
  AuthResult := TStringList.Create();
  { Authenticate }
  AuthResult := Authenticate(WebAuth, WebSintaxe, KeyClient, ClientUserId^, '123456789', ProductId, ProductVersion);
  { Check Authenticate }
  if AuthResult.Strings[0] = 'LOGIN_INVALID_PRODUCT' then
    ErrorMsg('Error: This product is invalid, contact the administration.')
  else if AuthResult.Strings[0] = 'LOGIN_INVALID_VERSION' then
    ErrorMsg('Error: This version has been disabled, visit the website and update.')
  else if AuthResult.Strings[0] = 'LOGIN_NOVIP' then
    ErrorMsg('Error: You are not a VIP.')
  else if AuthResult.Strings[0] = 'LOGIN_INVALID_MAC' then
    ErrorMsg('Error: Your computer is not authorized to use the system.')
  else if AuthResult.Strings[0] = 'LOGIN_INVALID_USER' then
    ErrorMsg('Error: This account is not valid.')
  else if AuthResult.Strings[0] = 'LOGIN_SUCCESS' then
  begin
    {  }
    WriteLn(' - Wellcome ', AuthResult.Strings[1], ', booting the system.');
    WriteLn(#13 + #13);
    { Get processid of game process }
    GameProcessId := GetProcessIdByClassName('MU');
    { Check already running process }
    if (GameProcessId = 0) then
      ErrorMsg('Error: You must be on the character screen when you open the system, try again.')
    { Process Found, Inject Module }
    else if RemoteLoadLibrary(GameProcessId, GetCurrentDir + '\MuOnline97d.dll') then
    begin
      { Close Console }
      FreeConsole;
      { Initialize Interface }
      Application.Initialize;
      { Set ServerKey }
      if AuthResult.Count >= 2 then
      try
        KeyServer := StrToInt(AuthResult[2]);
      except ExitProcess(0); end else ExitProcess(0);
      Application.CreateForm(TMainForm, MainForm);
      Application.ShowMainForm := False;
      Application.Run;
    end else
      ErrorMsg('Error: There was a system startup failure.');
  end else
    ErrorMsg('Error: There was a failure to communicate with the server, please try again later.');
end.
