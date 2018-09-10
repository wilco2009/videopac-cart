unit TransferUnit;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, FileUtil, Forms, Controls, Graphics, Dialogs, ComCtrls,
  StdCtrls, ExtCtrls,ftpsend;

procedure DownloadFiles;

type

  { TFTP_Transfer }

  TFTP_Transfer = class(TForm)
    ButtonCancel: TButton;
    LabelProgress: TLabel;
    Output: TMemo;
    ProgressBar: TProgressBar;
    procedure ButtonCancelClick(Sender: TObject);
  private

  public

  end;

var
  FTP_Transfer: TFTP_Transfer;
  Cancelar: Boolean;

implementation

{$R *.lfm}

{ TFTP_Transfer }

function FtpGetDir(const IP, Port, Path, User, Pass: string; DirList: TStringList): Boolean;
var
  i: Integer;
  s: string;
begin
  Result := False;
  with TFTPSend.Create do
  try
    Username := User;
    Password := Pass;
    TargetHost := IP;
    TargetPort := Port;
    if not Login then
      Exit;
    Result := List(Path, False);
    for i := 0 to FtpList.Count -1 do
    begin
      s := FTPList[i].FileName;
      DirList.Add(s);
    end;
    Logout;
  finally
    Free;
  end;
end;

procedure DownloadFiles;
Const
  HostIP = 'wilco2009.hopto.org';
  FTPPort = '21';
  FTPUser = 'invitadoftp';
  FTPaswd = 'invitadoftp';
  FTP_ROM_DIR = '/Videopac/ROM/';
  FTP_ROOT_DIR = '/Videopac/ROOT/';
  FTP_SHOTS_DIR = '/Videopac/shots/';
var
   result: boolean;
   FileName: String;
   DirList: TStringList;
   i, Progress: integer;

   procedure DownloadDir(Source, Dest, extension: String);
   var
      i: integer;
      ext, SourceFile, DestinationFile: String;
   begin
     FTP_Transfer.Output.Append(concat('Reading ', Source, ' directory'));
     DirList := TStringList.Create;
     with FTP_Transfer.ProgressBar do
     begin
       Min := 0;
       Max := 100;
       Step := 1;
       Position := 1;
     end;
     Result := FtpGetDir(HostIP, FTPPort, Source, FTPUser, FTPaswd, DirList);
     i := DirList.Count;
     FTP_Transfer.ProgressBar.Position := 2;
     Application.ProcessMessages;
     if Result and not Cancelar then
        FTP_Transfer.Output.Append('Done');
     begin
 //     DirList.SaveToFile('DIR.TXT');
        FTP_Transfer.Output.Append('Traferring files.....');
       for i := 0 to DirList.Count-1 do
        begin
          FTP_Transfer.ProgressBar.Position := Round((i+1)*100/DirList.Count);
          FileName := DirList[i];
          ext := ExtractFileExt(FileName);
          if (extension = '') or (extension = ext) then
          begin
            DestinationFile := concat(Dest, FileName);
            if fileExists(DestinationFile)then
            begin
              FTP_Transfer.Output.Append('Skiped')
            end else begin
                SourceFile := concat(Source, FileName);
                FTP_Transfer.Output.Append(concat('Downloading file ', FileName));
                Result := FtpGetFile(HostIP, FTPPort, SourceFile, DestinationFile, FTPUser, FTPaswd);
                Application.ProcessMessages;
                if Result and not Cancelar then
                   FTP_Transfer.Output.Append('Done')
                else
                    Break;
            end;
          end;
        end;
        DirList.Free;
     end;

   end;

begin
//     FileName := '1.TXT';
//   DownloadFromDropbox('https://www.dropbox.com/your_link_to_your_shared_file?dl=1', 'c:\temp\');
//   DownloadFromDropbox('https://www.dropbox.com/s/qzm9vuzt4cnix7p/Videopac ROMSet Maker v1.0.zip', '');
//     result := DownloadFTP('ftp://ftp.does.summitoh.net/GIS%20Info%20per%20Cityworks/Cityworks%20noted%20sanitary%20problems%20Q-446.pdf', 'TEST.pdf');
//  Result:= FtpGetFile('wilco2009.hopto.org', '21', '/python_games/4row_arrow.png', 'c:\tmp\4row_arrow.png', 'pi', 'raspberry');
//  Result:= FtpGetFile('192.168.1.30', '21', FileName, concat('c:\tmp\','2.txt'), 'invitado', 'invitado');
// Result := FtpGetFile(HostIP, FTPPort, '234.mobi', 'c:\tmp\kkk.mobi', FTPUser, FTPaswd);
 // Result:= FtpGetFile('192.168.1.30', '21', FileName, 'c:\tmp\222.mobi', 'invitado', 'invitado');
    FileName := '';
    Cancelar := False;
    FTP_Transfer.Show;
    if Dialogs.MessageDlg('Do you want to update your ROMs from the Internet?',
      mtConfirmation, [mbYes, mbNo], 0, mbYes) = mrYes then
    begin
        FTP_Transfer.Output.Clear;
        FTP_Transfer.LabelProgress.Caption := 'Transferring ROMs...';
        DownloadDir(FTP_ROM_Dir, 'ROMs\', '.bin');

        if Result and Not Cancelar then
        begin
           FTP_Transfer.LabelProgress.Caption := 'Transferring screen shots...';
           DownloadDir(FTP_SHOTS_Dir, 'shots\', '.bmp');
        end;

        if Result and Not Cancelar then
        begin
          FTP_Transfer.LabelProgress.Caption := 'Transferring root files...';
          DownloadDir(FTP_ROOT_Dir, '', '');
           //FTP_Transfer.Output.Append(concat('Downloading file ', 'gamelist.ini'));
           //Result := FtpGetFile(HostIP, FTPPort, '/Videopac/gamelist.ini', 'gamelist.ini', FTPUser, FTPaswd);
           //FTP_Transfer.Output.Append('Done')
           //if Result and Not Cancelar then
           //begin
           //     FTP_Transfer.Output.Append(concat('Downloading file ', 'NOIMG.bmp'));
           //     Result := FtpGetFile(HostIP, FTPPort, '/Videopac/NOIMG.bmp', 'NOIMG.bmp', FTPUser, FTPaswd);
           //     FTP_Transfer.Output.Append('Done')
           //end;
        end;
//       if Result and Not Cancelar then
//       begin
//           Result := FtpGetFile(HostIP, FTPPort, '/Videopac/VideopacROMSelector.exe', 'VideopacROMSelector.exe', FTPUser, FTPaswd);
//           FTP_Transfer.Output.Append('Done')
//       end;
        if Cancelar then
           ShowMessage('Cancelled by user')
        else if Not Result then
             ShowMessage('Error.')
        else
            ShowMessage('Transfer done');
    end;
    FTP_Transfer.Output.Clear;
    FTP_Transfer.Hide;
end;

procedure TFTP_Transfer.ButtonCancelClick(Sender: TObject);
begin
  Cancelar := True;
end;

end.

