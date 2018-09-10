unit MainDialog;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, FileUtil, PrintersDlgs, Forms, Controls, Graphics, Dialogs,
  StdCtrls, ExtCtrls, Buttons, CRC32, IniFiles, HTTPSend, blcksock, ftpsend, Printers,
  TransferUnit, TransferRS232, Tools, code;

const
  MaxROMs = 32;

type

  { TOpenROMDlg }

  TOpenROMDlg = class(TForm)
    Button1: TButton;
    Button2: TButton;
    ButtonCode: TButton;
    ButtonSerial: TButton;
    ButtonPrint: TButton;
    ButtonGenerate: TButton;
    ButtonDownload: TButton;
    ButtonSaveProject: TButton;
    ButtonLoadProject: TButton;
    ButtonSaveProjectAs: TButton;
    TargetComboBox: TComboBox;
    Label1: TLabel;
    LabelProjectName: TLabel;
    PrintDialog1: TPrintDialog;
    SaveDialog1: TSaveDialog;
    UpButton: TButton;
    ImageSource: TImage;
    ImageDest: TImage;
    LCRCDest: TLabel;
    LFileNameSource: TLabel;
    LCRCSource: TLabel;
    LFileNameDest: TLabel;
    LManfDest: TLabel;
    LYearSource: TLabel;
    ListBoxROMSource: TListBox;
    LManfSource: TLabel;
    LYearDest: TLabel;
    OpenDialog1: TOpenDialog;
    Logo: TImage;
    ListBoxROMDestination: TListBox;
    UpButton1: TButton;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure ButtonGenerateClick(Sender: TObject);
    procedure ButtonDownloadClick(Sender: TObject);
    procedure ButtonLoadProjectClick(Sender: TObject);
    procedure ButtonCodeClick(Sender: TObject);
    procedure ButtonPrintClick(Sender: TObject);
    procedure ButtonSaveProjectAsClick(Sender: TObject);
    procedure ButtonSaveProjectClick(Sender: TObject);
    procedure ButtonSerialClick(Sender: TObject);
    procedure CRCButtonClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure AddButtonClick(Sender: TObject);
    procedure ImageSourceClick(Sender: TObject);
    procedure ListBoxROMDestinationSelectionChange(Sender: TObject; User: boolean);
    procedure ListBoxROMSourceClick(Sender: TObject);
    procedure ListBoxROMSourceSelectionChange(Sender: TObject; User: boolean);
    procedure SelectFileButtonClick(Sender: TObject);
    procedure ListBoxROMDestinationClick(Sender: TObject);
    procedure LogoClick(Sender: TObject);
    procedure UpButton1Click(Sender: TObject);
    procedure UpButtonClick(Sender: TObject);
  private
    ProjectName: String;
    procedure InitialiseLists();

  public

  end;

var
  OpenROMDlg: TOpenROMDlg;

implementation

{$R *.lfm}

{ TOpenROMDlg }

function IntToBin(Value: Byte; Len: Byte): string;
var
  i: Integer;
begin
  SetLength(Result, Len);
  for i := 8-Len+1 to 8 do begin
    if (Value shl (i-1) and $ff) shr 7 = 0 then begin
      Result[i-8+Len] := '0'
    end else begin
      Result[i-8+Len] := '1';
    end;
  end;
end;

type
THttpFile=class(THttpSend)
  private
  public
    function Download(const aURL,aFileName:string):boolean;
  end;

function THttpFile.Download(const aURL,aFileName: string): boolean;
begin
  HTTPMethod('GET', aURL+aFileName);
  with TFileStream.Create(aFileName,fmCreate or fmOpenWrite) do
  try
    Seek(0, soFromBeginning);
    CopyFrom(Document, 0);
  finally
    Free;
  end;
end;

procedure TOpenROMDlg.LogoClick(Sender: TObject);
begin
end;

procedure TOpenROMDlg.UpButton1Click(Sender: TObject);
var
   i: integer;
   S1, S2: String;
begin
  with ListBoxROMDestination do
  begin
       i := ItemIndex;
       if i < Items.Count-1 then
       begin
            S1 := concat(IntToHex(i+1,2),copy(Items[i],3,length(Items[i])-2));
            S2 := concat(IntToHex(i,2),copy(Items[i+1],3,length(Items[i+1])-2));
            Items[i]:=S2;
            Items[i+1]:=S1;
            DestCRCList.Move(i, i+1);
            ItemIndex := i+1;
       end;
  end;
end;

procedure TOpenROMDlg.UpButtonClick(Sender: TObject);
var
   i: integer;
   S1, S2: String;
begin
     with ListBoxROMDestination do
     begin
          i := ItemIndex;
          if i > 0 then
          begin
              S1 := concat(IntToHex(i-1,2),copy(Items[i],3,length(Items[i])-2));
              S2 := concat(IntToHex(i,2),copy(Items[i-1],3,length(Items[i-1])-2));
//              Items.Move(i, i-1);
              Items[i]:=S2;
              Items[i-1]:=S1;
              DestCRCList.Move(i, i-1);
              ItemIndex := i-1;
          end;
     end;
end;


procedure TOpenROMDlg.ImageSourceClick(Sender: TObject);
begin

end;

procedure TOpenROMDlg.ListBoxROMDestinationSelectionChange(Sender: TObject; User: boolean
  );
var
   filename: String;
   i,j: integer;
begin
  j := ListBoxROMDestination.ItemIndex;
  if j >= 0 then
  begin
    i := search(SourceCRCList, DestCRCList[j]);
    if i >= 0 then
    begin
       filename := concat('shots\',SourceCRCList[i],'.bmp');
       LYearDest.Caption := Concat('Year: ',SourceYearList[i]);
       LManfDest.Caption := Concat('Manufacturer: ',SourceMANFList[i]);
       LCRCDest.Caption := Concat('CRC32: ',SourceCRCList[i]);
       LFileNameDest.Caption := Concat('File: ',SourceFileNameList[i]);
    end else begin
        filename := '';
        LYearDest.Caption := 'Year: ';
        LManfDest.Caption := 'Manufacturer: ';
        LCRCDest.Caption := 'CRC32: ';
        LFileNameDest.Caption := 'File: ';
    end;
    if Not FileExists(filename) then
       filename := 'NOIMG.BMP';
    ImageDest.Picture.LoadFromFile(filename);
  end;
end;

procedure TOpenROMDlg.ListBoxROMSourceClick(Sender: TObject);
begin
end;

procedure TOpenROMDlg.ListBoxROMSourceSelectionChange(Sender: TObject;
  User: boolean);
var
   filename: String;
   i: integer;
begin
     i := ListBoxROMSource.ItemIndex;
     filename := concat('shots\',SourceCRCList[i],'.bmp');
     if Not FileExists(filename) then
        filename := 'NOIMG.BMP';
     ImageSource.Picture.LoadFromFile(filename);
     LYearSource.Caption := Concat('Year: ',SourceYearList[i]);
     LManfSource.Caption := Concat('Manufacturer: ',SourceMANFList[i]);
     LCRCSource.Caption := Concat('CRC32: ',SourceCRCList[i]);
     LFileNameSource.Caption := Concat('File: ',SourceFileNameList[i]);

end;

procedure TOpenROMDlg.SelectFileButtonClick(Sender: TObject);
var
  filename: string;

begin
  if OpenDialog1.Execute then
  begin
      filename := OpenDialog1.Filename;
//    ListBoxROMDestination.Items.Add(filename);
//      LFileNameSource.Caption := filename;
//    ShowMessage(filename);
  end;
end;

procedure TOpenROMDlg.InitialiseLists();
const
  MAXLEN = 30;
var
  i,j : Integer;
  CRC: dword;
  INI, ININew: TINIFile;
  S1, FileName, SCRC, GameName, Year, MANUAL, MANUF: String;
  F: TextFile;

begin
  SourceTmpFileNameList := TStringList.Create;
  SourceTmpNameList := TStringList.Create;
  SourceTmpCRCList := TStringList.Create;
  SourceTmpYearList := TStringList.Create;
  SourceTmpManfList := TStringList.Create;
  SourceTmpManualList := TStringList.Create;

  SourceNameList.Clear;
  SourceFileNameList.Clear;
  SourceCRCList.Clear;
  SourceYearList.Clear;
  SourceManfList.Clear;
  SourceManualList.Clear;
  ListBoxROMSource.Items.Clear;

  FindAllFiles(SourceFileNameList, 'Roms', '*.bin', false);
  for i := 0 to SourceFileNameList.Count-1 do
  begin
      CalcCRC32(SourceFileNameList[i],CRC);
      SourceCRCList.Add(IntToHex(CRC,8));
  end;
  INI := TINIFile.Create('gamelist.ini');
  ININew := TINIFile.Create('gamelistadd.ini');
  try
    for i := 0 to SourceFileNameList.Count-1 do
    begin
      GameName := INI.ReadString(SourceCRCList[i],'Name','');
      if GameName = '' then
      begin
         GameName := Concat('??? ', ExtractFileName(SourceFileNameList[i]));
         ININew.WriteString(SourceCRCList[i], 'Name', GameName);
      end;
      Year := INI.ReadString(SourceCRCList[i],'Year','');
      MANUAL := INI.ReadString(SourceCRCList[i],'MANUAL','');
      MANUF := INI.ReadString(SourceCRCList[i],'MANUF','');
      SourceTmpFileNameList.Add(SourceFileNameList[i]);
      SourceNameList.Add(GameName);
      SourceTmpNameList.Add(GameName);
      SourceTmpYearList.Add(Year);
      SourceTmpManfList.Add(MANUF);
      SourceTmpManualList.Add(MANUAL);
      SourceTmpCRCList.Add(SourceCRCList[i]);
    end;

    SourceCRCList.Clear();
    SourceFileNameList.Clear();
    j := SourceCRCList.Count;
    SourceNameList.Sort();
    for i := 0 to SourceTmpNameList.Count-1 do
    begin
         j := search(SourceTmpNameList, SourceNameList[i]);
         GameName := SourceTmpNameList[j];
         ListBoxROMSource.Items.Add(GameName);
         FileName := SourceTmpFileNameList[j];
         SourceFileNameList.Add(FileName);
         Year := SourceTmpYearList[j];
         SourceYearList.Add(Year);
         MANUF := SourceTmpManfList[j];
         SourceManfList.Add(MANUF);
         MANUAL := SourceTmpManualList[j];
         SourceManualList.Add(MANUAL);
         SCRC := SourceTMPCRCList[j];
         SourceCRCList.Add(SCRC);
    end;
    SourceCRCList.SaveToFile('TODO.CRC');
    SourceFileNameList.SaveToFile('TODO.FIL');

    AssignFile(F, 'ROMLIST.C');
    Rewrite(F);
    writeln(F, '#define MAXLEN ', MAXLEN);
    writeln(F);
    writeln(F, 'static const unsigned long PROGMEM CRCList [] = {');
    for i :=0 to SourceCRCList.Count-1 do
    begin
      write(F, #9, '0x', SourceCRCList[i]);
      if i < SourceCRCList.Count-1 then
         writeln(F, ',');
    end;
    writeln(F);
    writeln(F, '};');
    writeln(F);

    for i :=0 to SourceCRCList.Count-1 do
    begin
      S1 := '';
      for j := 1 to 30 do
        if j <= Length(SourceNameList[i]) then
        begin
             if SourceNameList[i][j] = '"' then
                S1 := concat(S1, '""')
             else
                 S1 := concat(S1, SourceNameList[i][j]);

        end;

      writeln(F, #9, 'const char string', IntToStr(i),'[MAXLEN] PROGMEM =  "', S1, '";');
 //    write(F, #9, '"',S1, '"');
      //if i < SourceCRCList.Count-1 then
      //   writeln(F, ',');
    end;
    write(F, 'const char* const ROMNameList [', IntToStr(SourceCRCList.Count),'] = {');
    for i :=0 to SourceCRCList.Count-1 do
    begin
         write(F,'string',IntToStr(i));
         if i < SourceCRCList.Count-1 then writeln(F, ', ');
    end;

    writeln(F, '};');
   writeln(F);
   CloseFile(F);

  finally
    SourceTmpNameList.Free;
    SourceTmpYearList.Free;
    SourceTmpManfList.Free;
    SourceTmpManualList.Free;
    SourceTmpFileNameList.Free;
    INI.free;
    ININew.UpdateFile;
    ININew.free;
  end;
end;

procedure TOpenROMDlg.FormCreate(Sender: TObject);
begin
  if Not DirectoryExists('ROMs') then
     MkDir('ROMs');

  if Not DirectoryExists('shots') then
     MkDir('shots');

  if Not DirectoryExists('G7000RAM') then
     MkDir('G7000RAM');

  if Not DirectoryExists('ROMSet') then
     MkDir('ROMSet');

  if Not DirectoryExists('CODE') then
     MkDir('CODE');

  if Not DirectoryExists('prj') then
     MkDir('prj');

  SourceNameList := TStringList.Create;
  SourceFileNameList := TStringList.Create;
  SourceCRCList := TStringList.Create;
  SourceYearList := TStringList.Create;
  SourceManfList := TStringList.Create;
  SourceManualList := TStringList.Create;
  DestCRCList := TStringList.Create;

  ProjectName := 'NoName.prj';

  InitialiseLists;

end;

procedure TOpenROMDlg.AddButtonClick(Sender: TObject);
begin

end;

procedure TOpenROMDlg.CRCButtonClick(Sender: TObject);
begin
end;

procedure TOpenROMDlg.Button1Click(Sender: TObject);
var
   i, c: integer;
begin
  i := ListBoxROMSource.ItemIndex;
  c := ListBoxROMDestination.Items.Count;
  if c < MaxROMs then
  begin
    ListBoxROMDestination.Items.Add(concat(IntToHex(c,2),' ', ListBoxROMSource.Items[i]));
    DestCRCList.Add(SourceCRCList[i]);
    With ListBoxROMSource do
         if ItemIndex < Items.Count-1 then
            ItemIndex := ItemIndex + 1;
  end
end;

procedure TOpenROMDlg.Button2Click(Sender: TObject);
var
   i, j: integer;
   S1: String;
begin
  if (ListBoxROMDestination.Items.Count > 0) and (ListBoxROMDestination.ItemIndex >= 0) then
  begin
      i := ListBoxROMDestination.ItemIndex;
      ListBoxROMDestination.Items.Delete(i);
      DestCRCList.Delete(i);
      with ListBoxROMDestination do
      begin
        for j := i to Items.count-1 do
        begin
             S1 := concat(IntToHex(j,2),copy(Items[j],3,length(Items[j])-2));
             Items[j] := S1;
        end;
        if i <= Items.Count-1 then
           ItemIndex := i
        else if Items.Count > 0 then
             ItemIndex := Items.Count-1;
      end;
  end;
end;

procedure TOpenROMDlg.ButtonGenerateClick(Sender: TObject);
var
   f, FDest: file of byte;
   Bloque: Array[0..16383] of byte;
   k, i, j, Err: integer;
   ROMSetName: String;
   ROMName: String;
   ss: integer;
begin
  if TargetComboBox.ItemIndex = 0 then // MultiROM Cart 32
  begin
    ROMSetName := concat('ROMSET\',ChangeFileExt(ExtractFileName(ProjectName), '.set'));
    AssignFile(FDest, ROMSetName);
    Rewrite(FDest);
    for i := 0 to DestCRCList.Count-1 do
    begin
      j := search(SourceCRCList, DestCRCList[i]);
      if j >= 0 then
      begin
          ROMName := SourceFileNameList[j];
           AssignFile(f, ROMName);
          try
             Reset(f);
             ss := filesize(f);
             if (ss = 2048) or (ss = 4096) or (ss = 8192) then
             begin
                 for k := 1 to 8 do
                 begin
                      {$I-}
                      if EOF(f) then
                      begin
                        seek(f, 0);
                      end;
                      if not Eof(f) then
                           BlockRead(f,Bloque, 1024);
                      {$I+}
                      BlockWrite(FDest, Bloque, 1024);
                      BlockWrite(FDest, Bloque, 1024);
                 end;
             end else if (ss = 3072) or (ss = 6144) or (ss =  9216) or (ss = 12288) then
             begin
                 for k := 1 to 4 do
                 begin
                      fillchar(Bloque, 1024, $FF);
                      BlockWrite(FDest, Bloque, 1024);
                      {$I-}
                      if EOF(f) then
                      begin
                        seek(f, 0);
                      end;
                      if not Eof(f) then
                           BlockRead(f,Bloque, 3072);
                      {$I+}
                      BlockWrite(FDest, Bloque, 3072);
                 end;
             end else if (ss = 16384) then
             begin
                 {$I-}
                if EOF(f) then
                begin
                  seek(f, 0);
                end;
                if not Eof(f) then
                     BlockRead(f,Bloque, 16384);
                {$I+}
                BlockWrite(FDest, Bloque, 16384);
             end else begin
               ShowMessage(concat('Bad size in file ', ROMName));
             end;
             Closefile(f);
          except
            // If there was an error the reason can be found here
            on E: EInOutError do
               writeln('error');
          end;
      end;
    end;
    CloseFile(FDest);
  end else begin // G7000RAM Cart
    for i := 0 to DestCRCList.Count-1 do
    begin
      j := search(SourceCRCList, DestCRCList[i]);
      ROMSetName := concat('G7000RAM\',ChangeFileExt(ExtractFileName(SourceFileNameList[j]), '.RAM'));
      AssignFile(FDest, ROMSetName);
      Rewrite(FDest);
      if j >= 0 then
      begin
         ROMName := SourceFileNameList[j];
         AssignFile(f, ROMName);
         try
            Reset(f);
            ss := filesize(f);
            if (ss = 2048) or (ss = 4096) or (ss = 8192) then
            begin
                for k := 1 to 4 do
                begin
                     if not EOF(f) then
                     begin
                        BlockRead(f,Bloque, 2048);
                        BlockWrite(FDest, Bloque, 2048);
                        fillchar(Bloque, 1024, $FF);
                        BlockWrite(FDest, Bloque, 1024);

                     end;
                end;
            end else if (ss = 3072) or (ss = 6144) or (ss =  9216) or (ss = 12288) then
            begin
                for k := 1 to 4 do
                begin
                     if not Eof(f) then
                     begin
                        BlockRead(f,Bloque, 3072);
                        BlockWrite(FDest, Bloque, 3072);
                     end;
                end;
            end else if (ss = 16384) then
            begin
                {$I-}
               if EOF(f) then
               begin
                 seek(f, 0);
               end;
               if not Eof(f) then
                    BlockRead(f,Bloque, 16384);
               {$I+}
               BlockWrite(FDest, Bloque, 16384);
            end else begin
              ShowMessage(concat('Bad size in file ', ROMName));
            end;
            Closefile(f);
         except
           // If there was an error the reason can be found here
           on E: EInOutError do
              writeln('error');
         end;
      end;
      Closefile(FDest);
    end;
  end;
  ShowMessage('ROMSet generated');
end;

procedure TOpenROMDlg.ButtonDownloadClick(Sender: TObject);
begin
     DownloadFiles;
     InitialiseLists;
end;

procedure TOpenROMDlg.ButtonLoadProjectClick(Sender: TObject);
const
  MAXLEN = 30;

var
   Game: String;
   i,j: integer;
   F: TextFile;
begin
  if OpenDialog1.Execute then
  begin
    ProjectName := OpenDialog1.Filename;
    DestCRCList.LoadFromFile(ProjectName);
    ListBoxROMDestination.Items.Clear;
    for i := 0 to DestCRCList.Count-1 do
    begin
      j := search(SourceCRCList, DestCRCList[i]);
      if j >= 0 then
           Game := ListBoxROMSource.Items[j]
      else
          Game := '********* File not found *********';
      ListBoxROMDestination.Items.Add(concat(IntToHex(i,2),' ', Game));
    end;
  end;
  LabelProjectName.Caption := ProjectName;
end;

procedure TOpenROMDlg.ButtonCodeClick(Sender: TObject);
const
  MAXLEN = 30;

var
   CodeName, S: String;
   i: integer;
   F: TextFile;
begin
  Form_Code.EdName.Text := copy(ChangeFileExt(ExtractFileName(ProjectName),''), 0, 8);
  Form_Code.RG_ROMSetNum.Itemindex := 0;
  Form_Code.ShowModal();
  if Form_Code.doCode = True then
  begin
    S := Form_Code.EdName.Text;
    CodeName := concat('CODE\',ChangeFileExt(S, '.H'));
    AssignFile(F, CodeName);
    Rewrite(F);
    with Form_Code.RG_ROMSetNum do
    begin
      writeln(F, '#define FACT_ROMSET_', Itemindex, ' "', S, '"');
      writeln(F);
      if Itemindex = 0 then
         writeln(F, 'unsigned long int ROMSET_CRC[32] = {   ')
      else
          writeln(F, 'const unsigned long int PROGMEM ROMSET_CRC_',Itemindex,'[32] = {   ');
    end;
    for i :=0 to DestCRCList.Count-1 do
    begin
      write(F, #9, '0x', DestCRCList[i]);
      if i < DestCRCList.Count-1 then
         writeln(F, ',');
    end;
    writeln(F);
    writeln(F, '};');
    writeln(F);
    closeFile(F);
    ShowMessage(concat('Codigo generado en ', CodeName));
  end;
end;

procedure TOpenROMDlg.ButtonPrintClick(Sender: TObject);
const
  LEFTMARGIN = 100;
  TOTAL_PAGES = 1;
var
  YPos, LineHeight, VerticalMargin: Integer;
  SuccessString: String;
  WW, MaxPos, page, startPage, endPage, i, j : Integer;
  S, S1: String;
begin
  // Set up print dialog options
  printDialog1.MinPage := 1;               // First allowed page number
  printDialog1.MaxPage := TOTAL_PAGES;     // Highest allowed page number
  printDialog1.ToPage  := TOTAL_PAGES;     // 1 to ToPage page range allowed
  //printDialog1.Options := [poPageNums];    // Allow page range selection

  if PrintDialog1.Execute then
  begin
    with Printer do
    try
      // Set the number of copies to print each page
      // This is crude - it doies not take Collation into account
      Copies := printDialog1.Copies;

      // Start printing
      BeginDoc;

      // Has the user selected a page range?
      if printDialog1.PrintRange = prPageNums then
      begin
       startPage := printDialog1.FromPage;
       endPage   := printDialog1.ToPage;
      end
      else // All pages
      begin
       startPage := 1;
       endPage   := TOTAL_PAGES;
      end;

      // Set up the start page number
      page := startPage;
      Canvas.Font.Name := 'Courier New';

      LineHeight := Round(1.2 * Abs(Canvas.TextHeight('I')));
      VerticalMargin := 4 * LineHeight;
      YPos := VerticalMargin;

      MaxPos := Printer.PaperSize.Height-VerticalMargin;

      Canvas.Font.Size := 14;
      Canvas.Font.Color := clBlue;
      Canvas.Font.Bold := True;
      S := ExtractFileName(ProjectName);

      Printer.Canvas.TextOut(LEFTMARGIN, YPos, Copy(S, 0, Length(S)-4));
      inc(YPos, LineHeight*2);

      Canvas.Font.Bold := False;
      Canvas.Font.Size := 10;
      Canvas.Font.Color := clBlack;

      WW := Printer.Canvas.TextWidth('│1│2│3│4│5│');
      Printer.Canvas.TextOut(LEFTMARGIN, YPos, '│1│2│3│4│5│ NUM GAME DESCRIPTION');
      Printer.Canvas.Frame(LEFTMARGIN, Round(YPos-LineHeight*0.1), LEFTMARGIN+WW, Round(YPos+LineHeight*0.8));
      inc(YPos, LineHeight);

      for i := 0 to ListBoxROMDestination.Items.Count-1 do
      begin
        S1 := '│';
        S := IntToBin(i,5);
        for j := 0 to 4 do
        begin
          if S[5-j] = '1' then
             S1 := concat(S1,'▄│')
          else
              S1 := concat(S1, '▀│');
        end;
        Printer.Canvas.TextOut(LEFTMARGIN, YPos, Concat(S1, '  ', ListBoxROMDestination.Items[i]));
        Printer.Canvas.Frame(LEFTMARGIN, Round(YPos-LineHeight*0.1), LEFTMARGIN+WW, Round(YPos+LineHeight*0.8));
        inc(YPos, LineHeight);
      end;
      // Keep printing whilst all OK
      //while (not Printer.Aborted) and Printer.Printing do
      //begin
      //end;
    finally
      EndDoc;
    end;
  end;
end;

procedure TOpenROMDlg.ButtonSaveProjectAsClick(Sender: TObject);
begin
     SaveDialog1.FileName := ProjectName;
     if SaveDialog1.Execute then
     begin
          LabelProjectName.Caption := concat('Saving ', ProjectName);
          ProjectName := SaveDialog1.Filename;
          DestCRCList.SaveToFile(ProjectName);
     end;
     LabelProjectName.Caption := ProjectName;
end;

procedure TOpenROMDlg.ButtonSaveProjectClick(Sender: TObject);
begin
  if ProjectName = 'NoName.prj' then
  begin
    SaveDialog1.FileName := ProjectName;
    if SaveDialog1.Execute then
    begin
         ProjectName := SaveDialog1.Filename;
         LabelProjectName.Caption := concat('Saving ', ProjectName);
         DestCRCList.SaveToFile(ProjectName);
    end;
  end else begin
     LabelProjectName.Caption := concat('Saving ', ProjectName);
     DestCRCList.SaveToFile(ProjectName);
  end;
  LabelProjectName.Caption := ProjectName;
end;

procedure TOpenROMDlg.ButtonSerialClick(Sender: TObject);
begin
  FormTransRAM.ShowModal;
end;

procedure TOpenROMDlg.ListBoxROMDestinationClick(Sender: TObject);
begin

end;


end.

