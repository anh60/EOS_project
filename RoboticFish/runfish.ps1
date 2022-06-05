$qemupath   = "C:/RT-ThreadStudio/repo/Extract/Debugger_Support_Packages/RealThread/QEMU/4.2.0.4\qemu-system-arm.exe"
$logfile_1    = "benchmarking/benchmarks_startend_1.txt"
$logfile_2    = "benchmarking/benchmarks_startend_2.txt"
$logfile_3    = "benchmarking/benchmarks_startend_3.txt"
$logfile_4    = "benchmarking/benchmarks_startend_4.txt"
$logfile_5    = "benchmarking/benchmarks_startend_5.txt"
$logfile_6    = "benchmarking/benchmarks_startend_6.txt"
$logfile_7    = "benchmarking/benchmarks_startend_7.txt"
$logfile_8    = "benchmarking/benchmarks_startend_8.txt"
$logfile_9    = "benchmarking/benchmarks_startend_9.txt"
$logfile_10    = "benchmarking/benchmarks_startend_10.txt"
$logfile_u    = "benchmarking/benchmarks_startend_u.txt"

Write-Output ""
Write-Output "Run in terminal   [1]"
Write-Output "Save to file      [2]"
$q = Read-Host "What to do?     "
Write-Output "Select type of benchmark"
$type = Read-Host "Thread time, start to end  [1]   "
$index = Read-Host "Which iteration?    [1-10]      "

Write-Output ""
if($index -eq 1) {
    $logfile = $logfile_1
}elseif($index -eq 2){
    $logfile = $logfile_2
}elseif($index -eq 3){
    $logfile = $logfile_3
}elseif($index -eq 4){
    $logfile = $logfile_4
}elseif($index -eq 5){
    $logfile = $logfile_5
}elseif($index -eq 6){
    $logfile = $logfile_6
}elseif($index -eq 7){
    $logfile = $logfile_7
}elseif($index -eq 8){
    $logfile = $logfile_8
}elseif($index -eq 9){
    $logfile = $logfile_9
}elseif($index -eq 10){
    $logfile = $logfile_10
}else{
    $logfile = $logfile_u
}


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