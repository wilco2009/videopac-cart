unit TransferRS232;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, FileUtil, Forms, Controls, Graphics, Dialogs, StdCtrls,
  ExtCtrls, registry, Tools, Synaser;

type

  { TFormTransRAM }

  TFormTransRAM = class(TForm)
    ButtonStart: TButton;
    Button2: TButton;
    Label1: TLabel;
    ListBoxRAMFiles: TListBox;
    RadioGroupBaudRate: TRadioGroup;
    SerialComboBox: TComboBox;
    procedure Button2Click(Sender: TObject);
    procedure ButtonStartClick(Sender: TObject);
    procedure FormActivate(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure ListBoxRAMFilesClick(Sender: TObject);
    procedure ListBoxRAMFilesSelectionChange(Sender: TObject; User: boolean);
    procedure RadioGroupBaudRateSelectionChanged(Sender: TObject);
    procedure SerialTransfer(RAMFileName: String);
  private
    RAMFileNameList: TStringList;
    SerialPort: String;
    BaudRate: integer;
    StopBits: Integer;
    procedure ReadActiveComs;
    procedure ReadRAMFiles;
  public

  end;

var
  FormTransRAM: TFormTransRAM;

implementation

{$R *.lfm}

{ TFormTransRAM }

procedure TFormTransRAM.FormCreate(Sender: TObject);
begin
  SerialPort := 'COM1:';
  RadioGroupBaudRate.ItemIndex := 1;
  BaudRate := 19200;
  StopBits := SB2;
  RAMFileNameList := TStringList.Create;
end;

procedure TFormTransRAM.ListBoxRAMFilesClick(Sender: TObject);
begin

end;

procedure TFormTransRAM.ListBoxRAMFilesSelectionChange(Sender: TObject; User: boolean);
begin
  if ListBoxRAMFiles.ItemIndex >= 0 then
     ButtonStart.Enabled := True;
end;

procedure TFormTransRAM.RadioGroupBaudRateSelectionChanged(Sender: TObject);
begin
     if RadioGroupBaudRate.ItemIndex = 0 then
     begin
        BaudRate := 9600;
        StopBits := SB1;
     end
     else begin
       BaudRate := 19200;
       StopBits := SB1;
     end;
end;

procedure TFormTransRAM.ReadRAMFiles;
var
  S: String;
  i, j: Integer;
begin
     RAMFileNameList.Items.Clear;
     ListBoxRAMFiles.Items.Clear;
     FindAllFiles(RAMFileNameList, 'G7000RAM', '*.ram', false);
     for i := 0 to RAMFileNameList.Count-1 do
     begin
       S := ChangeFileExt(RAMFileNameList[i], '.bin');
       S := copy(S, 9, 999);
       S := concat('ROMs', S);
       j := Search(SourceFileNameList, S);
       if j >= 0 then
          ListBoxRAMFiles.Items.Add(SourceNameList[j])
       else
         ListBoxRAMFiles.Items.Add(RAMFileNameList[i])
     end;
end;

procedure TFormTransRAM.FormActivate(Sender: TObject);
begin
     ButtonStart.Enabled := ListBoxRAMFiles.ItemIndex >= 0;
     ReadActiveComs;
     ReadRAMFiles;
end;

procedure TFormTransRAM.Button2Click(Sender: TObject);
begin
  Self.Close;
end;

procedure TFormTransRAM.ButtonStartClick(Sender: TObject);
begin
     SerialTransfer(RAMFileNameList[ListBoxRAMFiles.ItemIndex]);
     ShowMessage('Transfer finished.');
end;

procedure TFormTransRAM.ReadActiveComs;
var
  reg:  TRegistry;
  l: TStringList;
  I:Integer;
begin
  Reg := TRegistry.Create;
  l := TStringList.Create;
 try
    Reg.RootKey := HKEY_LOCAL_MACHINE;
    SerialComboBox.Clear;
    if Reg.OpenKeyReadOnly('HARDWARE\DEVICEMAP\SERIALCOMM') then
    begin
       Reg.GetValueNames(l);
       for I := 0 to l.Count - 1 do
           SerialComboBox.Items.Add(Reg.ReadString(l[i]));
    end;
    SerialComboBox.Sorted := true;
  finally
    Reg.Free;
  end;
  if SerialComboBox.Items.Count > 0 then
  begin
     i := SerialComboBox.Items.IndexOf(SerialPort);
     if i < 0 then
     begin
       i := 0;
     end;
     SerialComboBox.ItemIndex := i;
     SerialPort := SerialComboBox.Items[i];
  end;
end;

procedure TFormTransRAM.SerialTransfer(RAMFileName: String);
var
  ser: TBlockSerial;
  F: File of Byte;
  t, i: integer;
  buff: array[0..3071] of byte;
begin
  ser:=TBlockSerial.Create;
  AssignFile(F, RAMFileName);
  Reset(F);
  try
    ser.Connect(SerialPort);
    ser.config(BaudRate, 8, 'N', StopBits, False, False);
    t := FileSize(F);
    for i := 1 to 4 do
    begin
         if Eof(f) then
            seek(f, 0);
         blockread(f, buff, 3072);
         ser.SendBuffer(@buff, 3072);
    end;
    closeFile(F);
  finally
    ser.free;
  end;
end;



end.

