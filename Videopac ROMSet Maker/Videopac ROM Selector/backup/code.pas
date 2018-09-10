unit code;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, FileUtil, Forms, Controls, Graphics, Dialogs, ExtCtrls,
  StdCtrls;

type

  { TForm_Code }

  TForm_Code = class(TForm)
    Button1: TButton;
    Button2: TButton;
    EdName: TEdit;
    Label1: TLabel;
    RG_ROMSetNum: TRadioGroup;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure RG_ROMSetNumClick(Sender: TObject);
  private

  public
    doCode: boolean;

  end;

var
  Form_Code: TForm_Code;

implementation

{$R *.lfm}

{ TForm_Code }

procedure TForm_Code.RG_ROMSetNumClick(Sender: TObject);
begin

end;

procedure TForm_Code.Button1Click(Sender: TObject);
begin
  DoCode = True;
  self.close();

end;

procedure TForm_Code.Button2Click(Sender: TObject);
begin
  doCode = false;
  self.close();
end;

procedure TForm_Code.FormShow(Sender: TObject);
begin
  doCode := false;
end;

end.

