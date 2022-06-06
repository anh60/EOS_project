$fishpath = ".\runfish.ps1"

Write-Output ""
Write-Output "Run in terminal   [1]"
Write-Output "Save to file      [2]"
$q = Read-Host "What to do?     "
Write-Output "Select type of benchmark"
Write-Output "Thread time, start to end        [1]"
Write-Output "Thread time, start to end + cpu  [2]"
$type = Read-Host " "


Write-Output ""

function Publish-Log() {
    & $qemupath `
        -M stm32f401-st-nucleo `
        -sd sd.bin `
        -serial stdio `
        -monitor null -nographic `
        -kernel Debug/rtthread.bin
}


if ($q -eq '1') {
    Publish-Log
} 
elseif ($q -eq '2') {
    
    for ($currentFile = 1; $currentFile -le 1; $currentFile++) {
        $script = Start-Process $fishpath -PassThru
        $script.ID
        $script.Name

        Start-Sleep -Seconds 3
        Get-Process -Name $script.Name  | Stop-Process -Force
    }
}
else {
    Write-Output "nope"
    Write-Output ""
    exit
}
