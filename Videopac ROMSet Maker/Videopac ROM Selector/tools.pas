unit Tools;

{$mode objfpc}{$H+}

interface
uses
  Classes, SysUtils;

function search(List: TStringList; S: String): integer;

Var
  SourceFileNameList: TStringList;
  SourceTmpFileNameList: TStringList;
  DestCRCList: TStringList;
  SourceCRCList: TStringList;
  SourceYearList: TStringList;
  SourceManfList: TStringList;
  SourceManualList: TStringList;
  SourceTmpCRCList: TStringList;
  SourceTmpYearList: TStringList;
  SourceTmpNameList: TStringList;
  SourceNameList: TStringList;
  SourceTmpManfList: TStringList;
  SourceTmpManualList: TStringList;

implementation

function search(List: TStringList; S: String): integer;
var
   i: integer;
   S1: String;
begin
     S := UpperCase(S);
     for i := 0 to List.Count-1 do
     begin
       S1 := UpperCase(List[i]);
       if S1 = S then
          exit(i);
     end;
     exit(-1);
end;


end.

