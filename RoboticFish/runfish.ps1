$qemupath   = "C:/RT-ThreadStudio/repo/Extract/Debugger_Support_Packages/RealThread/QEMU/4.2.0.4\qemu-system-arm.exe"
$logfile    = "benchmarking/benchmarks.txt"

Write-Output ""
Write-Output "Run in terminal   [1]"
Write-Output "Save to file      [2]"
$q = Read-Host "What to do?"
Write-Output ""

if($q -eq '1'){
    & $qemupath `
        -M stm32f401-st-nucleo `
        -sd sd.bin `
        -serial stdio `
        -monitor null -nographic `
        -kernel Debug/rtthread.bin
} 
elseif($q -eq '2'){
    try {
        & $qemupath `
            -M stm32f401-st-nucleo `
            -sd sd.bin `
            -serial stdio `
            -monitor null `
            -nographic `
            -kernel Debug/rtthread.bin | Out-File $logfile
    }
    finally {
        notepad $logfile
    }
}
else{
    Write-Output "nope"
    Write-Output ""
    exit
}