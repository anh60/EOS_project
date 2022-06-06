$qemupath = "C:/RT-ThreadStudio/repo/Extract/Debugger_Support_Packages/RealThread/QEMU/4.2.0.4\qemu-system-arm.exe"

Write-Output ""
Write-Output "Run in terminal   [1]"
Write-Output "Save to file      [2]"
Write-Output "What to do?     "
$q = Read-Host " "


function Set-Logfile() {
    switch ($type) {
        1 { $file = "benchmarking/benchmarks_startend.txt"; break }
        2 { $file = "benchmarking/benchmarks_startend_cpu.txt"; break }
        3 { $file = "benchmarking/benchmarks_cpu.txt"; break }
        4 { $file = "benchmarking/benchmarks_startend_without_OS_changes.txt"; break }
        Default { $file = "benchmarking/benchmarks_undefined.txt"; break }
    }
    return $file
}

function Write-Log() {   
    $logfile = ""
    $logfile = Set-Logfile
    Write-Output "$logfile at $currentFile"

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
        exit
    }

}
     

if ($q -eq '1') {
    & $qemupath `
        -M stm32f401-st-nucleo `
        -sd sd.bin `
        -serial stdio `
        -monitor null -nographic `
        -kernel Debug/rtthread.bin
} 
elseif ($q -eq '2') {
    Write-Output "Select type of benchmark"
    Write-Output "  Thread start and end time                       [1]"
    Write-Output "  Thread start and end time  + CPU usage          [2]"
    Write-Output "  CPU usage                                       [3]"
    Write-Output "  Thread start and end time without OS changes    [4]"
    $type = Read-Host " "

    Write-Log
}
else {
    Write-Output "nope"
    Write-Output ""
    exit
}