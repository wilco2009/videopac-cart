program VideopacROMSelector;

{$mode objfpc}{$H+}

uses
  {$IFDEF UNIX}{$IFDEF UseCThreads}
  cthreads,
  {$ENDIF}{$ENDIF}
  Interfaces, // this includes the LCL widgetset
  Forms, laz_synapse, printer4lazarus, MainDialog, CRC32, TransferUnit,
  TransferRS232, Tools, code
  { you can add units after this };

{$R *.res}

begin
  RequireDerivedFormResource:=True;
  Application.Initialize;
  Application.CreateForm(TOpenROMDlg, OpenROMDlg);
  Application.CreateForm(TFTP_Transfer, FTP_Transfer);
  Application.CreateForm(TFormTransRAM, FormTransRAM);
  Application.CreateForm(TForm_Code, Form_Code);
  Application.Run;
end.

