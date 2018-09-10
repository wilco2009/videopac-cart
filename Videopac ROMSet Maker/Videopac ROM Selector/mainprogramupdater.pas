{$define 32bits}
unit MainProgramUpdater;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, FileUtil, Forms, Controls, Graphics, Dialogs, ExtCtrls,
  StdCtrls, ftpsend, blcksock, synsock,ShellApi;

type

  { TFormUpdater }

  TFormUpdater = class(TForm)
    Image1: TImage;
    LabelStatus: TLabel;
    LabelProgress: TLabel;
    procedure FormActivate(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure Image1Click(Sender: TObject);
  private
    ftp:TFTPSend;
    Max: Longint;
    Size: Longint;
    SourceFile, DestinationFile: String;
    procedure OnHeartBeat(Sender:TObject);
    procedure OnMonitor(Sender: TObject; Writing: Boolean;
        const Buffer: TMemory; Len: Integer);
  public

  end;

var
  FormUpdater: TFormUpdater;

implementation

{$R *.lfm}

{ TFormUpdater }

procedure TFormUpdater.OnHeartBeat(Sender: TObject);
begin
  application.ProcessMessages;
end;

procedure TFormUpdater.OnMonitor(Sender: TObject; Writing: Boolean;
  const Buffer: TMemory; Len: Integer);
begin
  Size := Size + Len;
  LabelProgress.caption := concat('File ', DestinationFile, ' - ', IntToStr(Round(Size*100/Max)), '% downloaded');
end;


procedure TFormUpdater.Image1Click(Sender: TObject);
begin

end;

procedure TFormUpdater.FormCreate(Sender: TObject);
begin
end;

procedure TFormUpdater.FormActivate(Sender: TObject);
Const
  HostIP = 'wilco2009.hopto.org';
  FTPPort = '21';
  FTPUser = 'invitadoftp';
  FTPaswd = 'invitadoftp';
  {$ifdef 32bits}
  FTP_PROG_DIR = '/Videopac/PROG32/';
  {$else}
  FTP_PROG_DIR = '/Videopac/PROG/';
  {$endif}
  EXEC_FILE_NAME = 'VP.COM';
var
   RemoteVersion, LocalVersion: Integer;
   result: boolean;
   nResult: integer;
   F: TextFile;

   procedure DownloadProgram(ProgName: String);
   begin
       SourceFile := concat(FTP_PROG_DIR, ProgName);
       DestinationFile := ProgName;
       try
         Size := 0;
         ftp := TFTPSend.Create;
         ftp.DSock.OnMonitor:=@OnMonitor;
         ftp.Sock.OnHeartbeat:=@OnHeartBeat;
         ftp.DSock.OnHeartbeat:=@OnHeartBeat;
         ftp.DSock.HeartbeatRate:=150; //lets make our GUI still feel responsive
         ftp.Sock.HeartbeatRate:=150;
         //now our props
         ftp.TargetHost := HostIP;
         ftp.BinaryMode := true;
         ftp.UserName := FTPUser;
         ftp.Password := FTPaswd;
         ftp.DirectFileName := DestinationFile;
         ftp.DirectFile := true;
         if not ftp.Login then
           raise Exception.Create('could not login');
         Max:=ftp.FileSize(SourceFile);
         if not ftp.RetrieveFile(SourceFile,false) then
           raise Exception.Create('file not retrieved');
         ftp.Logout;
       finally
         ftp.free;
       end;
   end;

begin
  LocalVersion := 0;
  LabelProgress.caption := '';
  SourceFile := concat(FTP_PROG_DIR, 'VERSION.TXT');
  DestinationFile := 'VERSION.TMP';

  Result := FtpGetFile(HostIP, FTPPort, SourceFile, DestinationFile, FTPUser, FTPaswd);

  Application.ProcessMessages;
  if Result then
  begin
    {$I-}
    AssignFile(F, DestinationFile);
    Reset(F);
    Readln(F,RemoteVersion);
    CloseFile(F);
    {$I+}
    If IOResult <> 0 then
       Result := false;
  end;
  Application.ProcessMessages;
  if not Result then
  begin
       LabelStatus.Caption := 'Error reading from remote source';
  end else begin
    {$I-}
    AssignFile(F, 'VERSION.TXT');
    Reset(F);
    Readln(F, LocalVersion);
    CloseFile(F);
    {$I+}
    If IOResult <> 0 then
       LocalVersion := 0;
  end;
  If Result then
  begin
    if (LocalVersion >= RemoteVersion) then
       LabelStatus.Caption := 'No new version detected'
    else begin
        LabelStatus.Caption := concat('Upgrading to version ', IntToStr(RemoteVersion Div 1000), '.', IntToStr(RemoteVersion Mod 1000));
        Application.ProcessMessages;
        DownloadProgram(EXEC_FILE_NAME);
        DownloadProgram('libeay32.dll');
        DownloadProgram('NOIMG.bmp');
        DownloadProgram('ssleay32.dll');
    end;
    Application.ProcessMessages;
    CopyFile('VERSION.TMP', 'VERSION.TXT');
    DeleteFile('VERSION.TMP');
  end;
  DestinationFile := EXEC_FILE_NAME;
  nResult := ShellExecute(0,'open',PChar(DestinationFile),'',PChar(extractfilepath(DestinationFile)),1);
  if nResult <=32 then
  // return values 0..32 are errors
  begin
       ShowMessage('Program not found.');
  end;
  Self.Close;
end;

end.

