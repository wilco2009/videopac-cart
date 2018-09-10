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
begin
     for i := 0 to List.Count-1 do
     begin
       if UpperCase(List[i]) = UpperCase(S) then
          exit(i);
     end;
     exit(-1);
end;


end.

