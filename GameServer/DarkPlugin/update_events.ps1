
$files = @(
    'd:\MuOnline 2026\Versão 97x\Sources\Sources Base FT - Atualizada 97D\Source Base FT - Biel Atualizada CMZ\GameServer\DarkPlugin\Pascoa.cpp',
    'd:\MuOnline 2026\Versão 97x\Sources\Sources Base FT - Atualizada 97D\Source Base FT - Biel Atualizada CMZ\GameServer\DarkPlugin\Natal.cpp'
)

foreach ($p in $files) {
    if (Test-Path $p) {
        $e = [System.Text.Encoding]::GetEncoding(1252)
        $c = [System.IO.File]::ReadAllText($p, $e)
        
        # 1. Update Load() logic
        $oldLoad = 'this->(Pascoa|Natal)Struct\[this->_Count\[0\]\]\._Duration = Section\.Rows\[i\]\.GetInt\(3\) \* 60 \* 1000;'
        $newLoad = 'this->$1Struct[this->_Count[0]]._Duration = Section.Rows[i].GetInt(3) * 60 * 1000; this->$1Struct[this->_Count[0]]._Map = Section.Rows[i].GetInt(4); this->$1Struct[this->_Count[0]]._X = Section.Rows[i].GetInt(5); this->$1Struct[this->_Count[0]]._Y = Section.Rows[i].GetInt(6); this->$1Struct[this->_Count[0]]._QNTD[0] = Section.Rows[i].GetInt(7); this->$1Struct[this->_Count[0]]._QNTD[1] = Section.Rows[i].GetInt(8);'
        $c = [System.Text.RegularExpressions.Regex]::Replace($c, $oldLoad, $newLoad)

        # 2. Update Run() logic (Regex for the whole spawn block)
        $msgVar = if ($p -like "*Pascoa*") { "PascoaMapName" } else { "iMapName" }
        $eventName = if ($p -like "*Pascoa*") { "Pascoa" } else { "Natal" }
        $eventChar = if ($p -like "*Pascoa*") { "Pscoa" } else { "Natal" }

        $oldSpawn = 'srand\(time\(NULL\)\);\r?\n\s+BYTE Sortear = \(BYTE\)\(rand\(\) % sizeof\((PascoaMapNumber|iMapNumber)\)\);\r?\n\s+this->_Mapa = (PascoaMapNumber|iMapNumber)\[Sortear\];\r?\n\s+this->_Total\[0\] = 0;\r?\n\s+for \(int x = 0; x < 3; x\+\+\)\r?\n\s+\{\r?\n\s+while \(Func\.GetBoxPosition\(this->_Mapa, 10, 10, 240, 240, this->_X, this->_Y\) == 0\) \{\}\r?\n\s+Func\.MonsterAdd\(this->_Class\[0\], this->_Mapa, this->_X, this->_Y\);\r?\n\s+this->_Total\[0\]\+\+;\r?\n\s+\}\r?\n\s+this->_Total\[1\] = 0;\r?\n\s+for \(int x = 0; x < 15; x\+\+\)\r?\n\s+\{\r?\n\s+while \(Func\.GetBoxPosition\(this->_Mapa, 10, 10, 240, 240, this->_X, this->_Y\) == 0\) \{\}\r?\n\s+Func\.MonsterAdd\(this->_Class\[1\], this->_Mapa, this->_X, this->_Y\);\r?\n\s+this->_Total\[1\]\+\+;\r?\n\s+\}\r?\n\s+for \(int Index = OBJECT_MIN; Index < OBJECT_MAX; Index\+\+\)\r?\n\s+\{\r?\n\s+if \(gObj\[Index\]\.Connected == 3\)\r?\n\s+\{\r?\n\s+Func\.MsgOutput\(Index, 0, "A invaso de ' + $eventChar + ' comeou em %s", ' + $msgVar + '\[this->_Mapa\]\);'
        
        $newSpawn = 'this->_Mapa = this->' + $eventName + 'Struct[i]._Map; int mX = this->' + $eventName + 'Struct[i]._X; int mY = this->' + $eventName + 'Struct[i]._Y; this->_Total[0] = 0; for (int x = 0; x < this->' + $eventName + 'Struct[i]._QNTD[0]; x++) { int SafetyCount = 0; int x1 = (mX <= 0 && mY <= 0) ? 10 : mX - 10; int y1 = (mX <= 0 && mY <= 0) ? 10 : mY - 10; int x2 = (mX <= 0 && mY <= 0) ? 240 : mX + 10; int y2 = (mX <= 0 && mY <= 0) ? 240 : mY + 10; while (Func.GetBoxPosition(this->_Mapa, x1, y1, x2, y2, this->_X, this->_Y) == 0 && SafetyCount < 50) { SafetyCount++; } Func.MonsterAdd(this->_Class[0], this->_Mapa, this->_X, this->_Y); this->_Total[0]++; } this->_Total[1] = 0; for (int x = 0; x < this->' + $eventName + 'Struct[i]._QNTD[1]; x++) { int SafetyCount = 0; int x1 = (mX <= 0 && mY <= 0) ? 10 : mX - 10; int y1 = (mX <= 0 && mY <= 0) ? 10 : mY - 10; int x2 = (mX <= 0 && mY <= 0) ? 240 : mX + 10; int y2 = (mX <= 0 && mY <= 0) ? 240 : mY + 10; while (Func.GetBoxPosition(this->_Mapa, x1, y1, x2, y2, this->_X, this->_Y) == 0 && SafetyCount < 50) { SafetyCount++; } Func.MonsterAdd(this->_Class[1], this->_Mapa, this->_X, this->_Y); this->_Total[1]++; } for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++) { if (gObj[Index].Connected == 3) { if (this->_Mapa >= 0 && this->_Mapa <= 3) { Func.MsgOutput(Index, 0, "A invaso de ' + $eventChar + ' comeou em %s", ' + $msgVar + '[this->_Mapa]); } else { Func.MsgOutput(Index, 0, "A invaso de ' + $eventChar + ' comeou no Mapa: %d", this->_Mapa); }'

        $c = [System.Text.RegularExpressions.Regex]::Replace($c, $oldSpawn, $newSpawn)
        
        [System.IO.File]::WriteAllText($p, $c, $e)
        Write-Host "Updated $p"
    }
}
