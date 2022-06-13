from cProfile import label
from operator import index
from unicodedata import name
import numpy as np
import matplotlib.pyplot as plt
import plotly.figure_factory as ff
import pandas as pd

def readFile(filename):
    file = open(filename,"rb")
    file.readline()
    string = ''
    
    for line in file:
        for i in range(1, (len(line) - 2), 2):
            string += chr(line[i])

    file.close()
    
    return string 


def plot_charts():

    # SPESIFIC CODE LENGTH
    content = readFile("benchmarking/benchmarks_startend_without_OS_changes.txt")
    data = []
    data.append(content.split(": ")[1])
    data.append(content.split(": ")[2])
    data.append(content.split(": ")[3])
    data.append(content.split(": ")[4])

    data[0] = data[0].split(" \r")[0]
    data[1] = data[1].split(" \r")[0]
    data[1] = int(data[1])
    data[2] = data[2].split("\r")[0]
    data[2] = int(data[2])
    data[3] = data[3].split(" \r")[0]
    data[3] = abs(int(data[3]))

    title = "Improvement in lines of code for " + data[0] + " threads"
    
    data = [data[1], data[2], data[3]]
    bar_titles = ["with improvement", "without improvement", "difference"]


    # SPESIFIC CODE LENGHT FIGURE
    plt.figure(1)
    plt.bar(bar_titles, data)
    plt.title(title)
    plt.ylabel("Lines of code")
    plt.xticks(["with improvement", "without improvement", "difference"])
    
    # GENERAL CASE CODE LENGHT
    diff =[]
    with_imp = []
    without_imp = []
    x = np.arange(50)
    base = 35
    spesific = 4

    for i in range(50):
        with_imp.append(i+spesific)
        without_imp.append((i*base)+spesific)
        diff.append(without_imp[i] - with_imp[i])

    
    # CPU USAGE
    data = readFile("benchmarking/benchmarks_cpu.txt")
    arr_CPUUsage = []

    i = 0
    
    while (i < len(data) and i != -1):
        i = data.find("%", i)

        if i == -1:
            break

        if data[i+4] == ".":
            number = data[i+2:i+5]
        else: 
            number = data[i+2:i+4]

        arr_CPUUsage.append(float(number))
        i = i+1
        
    a = np.array(arr_CPUUsage)
    

    # CALCULATE MEAN
    CPU_usage_mean = a.mean(0)
    # CALCULATE STD DEV
    CPU_usage_std = a.std()

    textstr = '\n'.join((
        r'$\mu=%.2f$' % (CPU_usage_mean, ),
        r'$\sigma=%.2f$' % (CPU_usage_std, )))

    prop = dict(boxstyle='square', facecolor='wheat', alpha=0.5)
    
    # DATA VISUALIZATION
    y = np.arange(len(a))

    # CPU USAGE PLOT
    plt.figure(3)
    plt.plot(y, a)
    plt.legend([textstr])
    plt.xlabel('Sample')
    plt.ylabel('CPU usage in %')
    plt.title('CPU usage')
    
    # GENERAL CODE LENGTH FIGURE
    plt.figure(2)
    plt.plot(x, with_imp, label = "With improvements")
    plt.plot(x, without_imp, label= "Without improvements")

    plt.title("Code lenght for general case")
    plt.xlabel("Number of threads")
    plt.ylabel("Lines of code")
    plt.legend(["With improvement", "Without improvement", "Difference"])
    
    plt.show()


def plot_gantt():
    data = readFile('benchmarking/benchmarks_startend_cpu.txt')
    df_list = []
    i = 0
    j = 0

    # CALCULATION THREAD
    while i < len(data) and i != -1:

        i = data.find("calc=S:", i)
        if i == -1: 
            break
        elif data[i+8] == ';':
            start = int(data[i+7])
        elif data[i+9] == ';':
            start = int(data[i+7] + data[i+8])
        elif data[i+10] == ';':
            start = int(data[i+7] + data[i+8]+ data[i+9])
        elif data[i+11] == ';':
            start = int(data[i+7] + data[i+8]+ data[i+9] + data[i+10])
        
        i = data.find("calc=E:", i)
        if i == -1: 
            break
        elif data[i+8] == ';':
            finish = int(data[i+7])
            df1 = pd.DataFrame([dict(Task="Calculate Servo Position", Start=start, Finish=finish)] , columns=['Task', 'Start', 'Finish'])
            df_list.append(df1)
        elif data[i+9] == ';':
            finish = int(data[i+7] + data[i+8])
            df1 = pd.DataFrame([dict(Task="Calculate Servo Position", Start=start, Finish=finish)] , columns=['Task', 'Start', 'Finish'])
            df_list.append(df1)
        elif data[i+10] == ';':
            finish = int(data[i+7] + data[i+8]+ data[i+9])
            df1 = pd.DataFrame([dict(Task="Calculate Servo Position", Start=start, Finish=finish)] , columns=['Task', 'Start', 'Finish'])
            df_list.append(df1)
        elif data[i+11] == ';':
            finish = int(data[i+7] + data[i+8]+ data[i+9] + data[i+10])
            df1 = pd.DataFrame([dict(Task="Calculate Servo Position", Start=start, Finish=finish)] , columns=['Task', 'Start', 'Finish'])
            df_list.append(df1)

    

    i = 0
    # SET SERVO THREAD  
    while i < len(data) and i != -1:
        i = data.find("set=S:", i)
        if i == -1: 
            break
        elif data[i+7] == ';':
            start = int(data[i+6])
        elif data[i+8] == ';':
            start = int(data[i+6] + data[i+7])
        elif data[i+9] == ';':
            start = int(data[i+6] + data[i+7]+ data[i+8])
        elif data[i+10] == ';':
            start = int(data[i+6] + data[i+7]+ data[i+8] + data[i+9])
        
        i = data.find("set=E:", i)
        if i == -1: 
            break
        elif data[i+7] == ';':
            finish = int(data[i+6])
            df1 = pd.DataFrame([dict(Task="Set Servo Position", Start=start, Finish=finish)] , columns=['Task', 'Start', 'Finish'])
            df_list.append(df1)
        elif data[i+8] == ';':
            finish = int(data[i+6] + data[i+7])
            df1 = pd.DataFrame([dict(Task="Set Servo Position", Start=start, Finish=finish)] , columns=['Task', 'Start', 'Finish'])
            df_list.append(df1)
        elif data[i+9] == ';':
            finish = int(data[i+6] + data[i+7]+ data[i+8])
            df1 = pd.DataFrame([dict(Task="Set Servo Position", Start=start, Finish=finish)] , columns=['Task', 'Start', 'Finish'])
            df_list.append(df1)
        elif data[i+10] == ';':
            finish = int(data[i+6] + data[i+7]+ data[i+8] + data[i+9])
            df1 = pd.DataFrame([dict(Task="Set Servo Position", Start=start, Finish=finish)] , columns=['Task', 'Start', 'Finish'])
            df_list.append(df1)


    i = 0
    # CPU THREAD  
    while i < len(data) and i != -1:

        i = data.find("cpu=S:", i)
        if i == -1: 
            break
        elif data[i+7] == ';':
            start = int(data[i+6])
        elif data[i+8] == ';':
            start = int(data[i+6] + data[i+7])
        elif data[i+9] == ';':
            start = int(data[i+6] + data[i+7]+ data[i+8])
        elif data[i+10] == ';':
            start = int(data[i+6] + data[i+7]+ data[i+8] + data[i+9])
        
        i = data.find("cpu=E:", i)
        if i == -1: 
            break
        elif data[i+7] == ';':
            finish = int(data[i+6])
            df1 = pd.DataFrame([dict(Task="CPU", Start=start, Finish=finish)] , columns=['Task', 'Start', 'Finish'])
            df_list.append(df1)

        elif data[i+8] == ';':
            finish = int(data[i+6] + data[i+7])
            df1 = pd.DataFrame([dict(Task="CPU", Start=start, Finish=finish)] , columns=['Task', 'Start', 'Finish'])
            df_list.append(df1)
            

        elif data[i+9] == ';':
            finish = int(data[i+6] + data[i+7]+ data[i+8])
            df1 = pd.DataFrame([dict(Task="CPU", Start=start, Finish=finish)] , columns=['Task', 'Start', 'Finish'])
            df_list.append(df1)

        elif data[i+10] == ';':
            finish = int(data[i+6] + data[i+7]+ data[i+8] + data[i+9])
            df1 = pd.DataFrame([dict(Task="CPU", Start=start, Finish=finish)] , columns=['Task', 'Start', 'Finish'])
            df_list.append(df1)


    i = 0
    # PRESSURE thread  
    while i < len(data) and i != -1:
        i = data.find("press=S:", i)
        if i == -1: 
            break
        elif data[i+9] == ';':
            start = int(data[i+8])
        elif data[i+10] == ';':
            start = int(data[i+8] + data[i+9])
        elif data[i+11] == ';':
            start = int(data[i+8] + data[i+9]+ data[i+10])
        elif data[i+12] == ';':
            start = int(data[i+8] + data[i+9]+ data[i+10] + data[i+11])
        
        i = data.find("press=E:", i)
        if i == -1: 
            break
        elif data[i+9] == ';':
            finish = int(data[i+8])
            df1 = pd.DataFrame([dict(Task="Calculate Servo Position", Start=start, Finish=finish)] , columns=['Task', 'Start', 'Finish'])
            df_list.append(df1) 

        elif data[i+10] == ';':
            finish = int(data[i+8] + data[i+9])
            df1 = pd.DataFrame([dict(Task="Calculate Servo Position", Start=start, Finish=finish)] , columns=['Task', 'Start', 'Finish'])
            df_list.append(df1) 
            
        elif data[i+11] == ';':
            finish = int(data[i+8] + data[i+9]+ data[i+10])
            df1 = pd.DataFrame([dict(Task="Calculate Servo Position", Start=start, Finish=finish)] , columns=['Task', 'Start', 'Finish'])
            df_list.append(df1)
            
        elif data[i+12] == ';':
            finish = int(data[i+8] + data[i+9]+ data[i+10] + data[i+11])
            df1 = pd.DataFrame([dict(Task="Calculate Servo Position", Start=start, Finish=finish)] , columns=['Task', 'Start', 'Finish'])
            df_list.append(df1)
            

    i = 0
    # TEMPERATURE THREAD  
    while i < len(data) and i != -1:

        i = data.find("temp=S:", i)
        if i == -1:
            break
        if data[i-1] != 'x':
            
            if data[i+8] == ';':
                start = int(data[i+7])
            elif data[i+9] == ';':
                start = int(data[i+7] + data[i+8])
            elif data[i+10] == ';':
                start = int(data[i+7] + data[i+8]+ data[i+9])
            elif data[i+11] == ';':
                start = int(data[i+7] + data[i+8]+ data[i+9] + data[i+10])
        
        i = data.find("temp=E:", i)
        if i == -1:
            break

        if data[i-1] == 'x':
            i = i+7
            i = data.find("temp=E:", i)

        if data[i-1] != 'x':
            if data[i+8] == ';':
                finish = int(data[i+7])
                df1 = pd.DataFrame([dict(Task="Temperature Thread", Start=start, Finish=finish)] , columns=['Task', 'Start', 'Finish'])
                df_list.append(df1)
            elif data[i+9] == ';':
                finish = int(data[i+7] + data[i+8])
                df1 = pd.DataFrame([dict(Task="Temperature Thread", Start=start, Finish=finish)] , columns=['Task', 'Start', 'Finish'])
                df_list.append(df1)
            elif data[i+10] == ';':
                finish = int(data[i+7] + data[i+8]+ data[i+9])
                df1 = pd.DataFrame([dict(Task="Temperature Thread", Start=start, Finish=finish)] , columns=['Task', 'Start', 'Finish'])
                df_list.append(df1)
            elif data[i+11] == ';':
                finish = int(data[i+7] + data[i+8]+ data[i+9] + data[i+10])
                df1 = pd.DataFrame([dict(Task="Temperature Thread", Start=start, Finish=finish)] , columns=['Task', 'Start', 'Finish'])
                df_list.append(df1)

    i = 0
        # EXTREME TEMPERATURE THREAD  
    while i < len(data) and i != -1:

        i = data.find("extemp=S:", i)
        if data[i+1] == "x":
            if i == -1: 
                break
            elif data[i+10] == ';':
                start = int(data[i+9])
            elif data[i+11] == ';':
                start = int(data[i+9] + data[i+10])
            elif data[i+12] == ';':
                start = int(data[i+9] + data[i+10]+ data[i+11])
            elif data[i+13] == ';':
                start = int(data[i+9] + data[i+10]+ data[i+11] + data[i+12])
        
        i = data.find("extemp=E:", i)
        if data[i+1] == "x":
            if i == -1: 
                break
            elif data[i+10] == ';':
                finish = int(data[i+9])
            elif data[i+11] == ';':
                finish = int(data[i+9] + data[i+10])
                df1 = pd.DataFrame([dict(Task="Extreme Temperature Handling", Start=start, Finish=finish)] , columns=['Task', 'Start', 'Finish'])
                df_list.append(df1)
            elif data[i+12] == ';':
                finish = int(data[i+9] + data[i+10]+ data[i+11])
                df1 = pd.DataFrame([dict(Task="Extreme Temperature Handling", Start=start, Finish=finish)] , columns=['Task', 'Start', 'Finish'])
                df_list.append(df1)
            elif data[i+13] == ';':
                finish = int(data[i+9] + data[i+10]+ data[i+11] + data[i+12])
                df1 = pd.DataFrame([dict(Task="Extreme Temperature Handling", Start=start, Finish=finish)] , columns=['Task', 'Start', 'Finish'])
                df_list.append(df1)

    # CONCATENATE DATA FRAMES
    df = pd.concat(df_list) 

    # CREATE GANTT PLOT
    
    fig = ff.create_gantt(df, index_col='Task', show_colorbar=True,
                      group_tasks=True)
    fig.update_layout(xaxis_type='linear')

    fig.show()



if __name__ == '__main__':

   # SCHEDULING PLOT
   plot_gantt()
   
   # IMPROVEMENT VISUALIZATION
   plot_charts()

