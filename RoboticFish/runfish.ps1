$qemupath = "C:/RT-ThreadStudio/repo/Extract/Debugger_Support_Packages/RealThread/QEMU/4.2.0.4\qemu-system-arm.exe"

Write-Output ""
Write-Output "Run in terminal   [1]"
Write-Output "Save to file      [2]"
Write-Output "Plot benchmark    [3]"

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
     
function Write-CodeDiff($numberOfPeriodicTask) {
    $logfile = Set-Logfile

    $baseLength = 35 #Code length periodic function
    $commonLength = 4 #"Duplication" of code, function decleration etc.
    $codeLengthWithOSChanges = (([int]$numberOfPeriodicTask * $commonLength) + $baseLength)
    $codeLengthWithoutOSChanges = ([int]$numberOfPeriodicTask * $baseLength)

    Write-Output " With OS changes: $codeLengthWithOSChanges "
    Write-Output " Without OS changes: $codeLengthWithoutOSChanges "
    
    $codeDiff = $codeLengthWithOSChanges - $codeLengthWithoutOSChanges

    Write-Output " Difference in length: $codeDiff "

    "" | Out-File $logfile
    Add-Content $logfile "Number of periodic threads: $numberOfPeriodicTask "
    Add-Content $logfile "With OS changes: $codeLengthWithOSChanges "
    Add-Content $logfile "Without OS changes: $codeLengthWithoutOSChanges"
    Add-Content $logfile "Difference in length: $codeDiff "
    

    
}


if ($q -eq '1') {
    & $qemupath `
        -M stm32f401-st-nucleo `
        -sd sd.bin `
        -serial stdio `
        -monitor null `
        -nographic `
        -kernel Debug/rtthread.bin
} 
elseif ($q -eq '2') {
    Write-Output " "
    Write-Output "Select type of benchmark"
    Write-Output "  Thread start and end time                       [1]"
    Write-Output "  Thread start and end time  + CPU usage          [2]"
    Write-Output "  CPU usage                                       [3]"
    Write-Output "  Code length with vs without OS changes          [4]"
    $type = Read-Host " "

    if ($type -eq '4') {
        Write-Output "  How many periodic threads do you have?"
        $tasks = Read-Host " "
        Write-CodeDiff($tasks)
    }
    else {
        Write-Log
    }
}
elseif ($q -eq '3') {
    python ./benchmarking/data_representation.py

}
else {
    Write-Output "nope"
    Write-Output ""
    exit
}
