unit uTools;

interface

uses
  Windows, TlHelp32, SysUtils, Classes, IdHTTP;

  
function Authenticate(WebAuth, WebSintaxe : String; ClientKey, ClientId: DWORD; ClientMac : String; ProductId, ProductVersion : DWORD) : TStringList;
procedure ErrorMsg(Text : String; Timer : DWORD = 4000);

function RandomString(strLen: Integer): ShortString;
function GetProcessIdByClassName(ClassName: PAnsiChar): DWORD;
function GetProcessId(ProcessName: String) : DWORD;
function RemoteLoadLibrary(ProcessId: DWORD; LibraryName: WideString):Boolean;

implementation

function Authenticate(WebAuth, WebSintaxe : String; ClientKey, ClientId: DWORD; ClientMac : String; ProductId, ProductVersion : DWORD) : TStringList;
begin
  // Creae Result
  Result := TStringList.Create;
  Result.Text := 'Error';
  // Create IdHTTP
  with TIdHTTP.Create(nil) do
  try
    // Try Authenticate
    Result.Text := Get(
      Format(WebAuth + WebSintaxe, [
        ClientKey, ProductId, ProductVersion, ClientId, ClientMac
      ])
    );
  except { Ignore Error } end;
end;

procedure ErrorMsg(Text : String; Timer : DWORD = 4000);
begin
  WriteLn(Text);
  Sleep(Timer);
  ExitProcess(0);
end;


function RandomString(strLen: Integer): ShortString;
var
  Str: string;
begin
  Randomize;
  Str   := 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ';
  Result:= '';
  repeat
    Result := Result + Str[Random(Length(str)) + 1];
  until (Length(Result) = strLen);
end;

function GetProcessIdByClassName(ClassName: PAnsiChar): DWORD;
var
  Handle: THandle;
begin
  Result := 0;
  Handle := FindWindow(ClassName, nil);
  GetWindowThreadProcessID(Handle, Result);
end;

function GetProcessId(ProcessName: String) : DWORD;
var
  ProcessSnap : THandle;
  ProcessEntry: TProcessEntry32;
begin
  // Default return
  Result := 0;
  // Create snap handle
  ProcessSnap         := CreateToolHelp32SnapShot(TH32CS_SNAPPROCESS, 0);
  ProcessEntry.dwSize := Sizeof(TProcessEntry32);
  // Loop process
  if Process32First(ProcessSnap, ProcessEntry) then
  repeat
    // Check current process name
    if (lowercase(ProcessEntry.szExeFile) = lowercase(ProcessName)) then
    begin
      Result := ProcessEntry.th32ProcessID;
      Break;
    end;
  until not Process32Next(ProcessSnap, ProcessEntry);
  // Close Handle
  CloseHandle(ProcessSnap);
end;

function WriteProcessMemory(hProcess: Cardinal; pBaseAddress : Pointer; lpBuffer : Pointer; nSize : Cardinal; var lpNumberOfBytesWritten : Cardinal): BOOL; stdcall;
var
  pKernelBase : DWORD;
  pWriteProcessMemory : function (hProcess: Cardinal; pBaseAddress : Pointer; lpBuffer : Pointer; nSize : Cardinal; var lpNumberOfBytesWritten : Cardinal): BOOL; stdcall;
begin
  pKernelBase := GetModuleHandleA('KERNELBASE.dll');
  @pWriteProcessMemory := GetProcAddress(pKernelBase, 'WriteProcessMemory');
  Result := pWriteProcessMemory(hProcess, pBaseAddress, lpBuffer, nSize, lpNumberOfBytesWritten);
end;

function RemoteLoadLibrary(ProcessId: DWORD; LibraryName: WideString):Boolean;
var
  ProcessHandle, hThread            : THandle;
  pKernel32, BytesWritten, ThreadID : Cardinal;
  pLoadLibrary, pRemoteParam        : Pointer;
begin
  // Default return
  Result := FALSE;
  // Open handle to process
  ProcessHandle := OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessId);
  // Check handle to process
  if ProcessHandle <> INVALID_HANDLE_VALUE then
  begin
    // Get pointer of LoadLibrary in remote process
    pKernel32 := GetModuleHandle('Kernel32.dll');
    pLoadLibrary := GetProcAddress(pKernel32, 'LoadLibraryW');
    // Allocate memory to param
    pRemoteParam := VirtualAllocEx(ProcessHandle, nil, Length(LibraryName) * 2 + 2, MEM_COMMIT or MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    // Create thread on LoadLibrary with remote param
    if WriteProcessMemory(ProcessHandle, pRemoteParam, @LibraryName[1], Length(LibraryName) * 2, BytesWritten) then
      hThread := CreateRemoteThread(ProcessHandle, nil, 0, pLoadLibrary, pRemoteParam, 0, ThreadID);
    // Check our thread has created.
    if (hThread > 0) then
    begin
      // Wait execute DLLMain
      WaitForSingleObject(hThread, INFINITE);
      // Close thread handle
      CloseHandle(hThread);
      // Successfully Inject
      Result := TRUE;
    end;
    // Free memory of param
    if (pRemoteParam <> nil) then
      VirtualFreeEx(ProcessHandle, pRemoteParam, Length(LibraryName) * 2 + 2, MEM_RELEASE);
    // Close process handle
    CloseHandle(ProcessHandle);
  end;
end;

end.
