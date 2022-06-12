from unicodedata import name
import numpy as np
import matplotlib.pyplot as plt
import plotly.express as px
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


def plot_CPU_usage():

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
    
    # DATA VISUALIZATION
    y = np.arange(len(a))
    plt.plot(y, a)

    textstr = '\n'.join((
        r'$\mu=%.2f$' % (CPU_usage_mean, ),
        r'$\sigma=%.2f$' % (CPU_usage_std, )))

    prop = dict(boxstyle='square', facecolor='wheat', alpha=0.5)
    plt.text(1, len(y) + 7, textstr, fontsize = 10, bbox=prop)

    plt.xlabel('Sample')
    plt.ylabel('CPU usage in %')
    plt.title('CPU usage')
    plt.show()


def plot_improvementDifferences():

    #[nr of tasks, with changes, without changes, length difference]
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
    
    
    plt.bar(bar_titles, data)
    plt.title(title)
    plt.ylabel("Lines of code")
    plt.xticks(["with improvement", "without improvement", "difference"])
    plt.show()

def plot_gantt():
    data = readFile('benchmarking/benchmarks_startend_cpu.txt')
    df_list = []
    i = 0

    # CALCULATION THREAD
    while i < len(data) and i != -1:
        
        if i < 40: 
            i = data.find("calc=S:", i)           
            start = int(data[i+7])
            i = data.find("calc=E:", i)
            end = int(data[i+7])
            df_list.append(pd.DataFrame([dict(Task="Calculate Servo Position", Start=start, End=end)]))
        elif i < 150:
            i = data.find("calc=S:", i)
            start = int(data[i+7] + data[i+8])
            i = data.find("calc=E:", i)
            end = int(data[i+7] + data[i+8])
            df_list.append(pd.DataFrame([dict(Task="Calculate Servo Position", Start=start, End=end)]))
        elif i < 3500:
            i = data.find("calc=S:", i)
            start = int(data[i+7] + data[i+8] + data[i+9])
            i = data.find("calc=E:", i)
            end = int(data[i+7] + data[i+8] + data[i+9]) 
            df_list.append(pd.DataFrame([dict(Task="Calculate Servo Position", Start=start, End=end)]))
        else:
            i = data.find("calc=S:", i)
            if i == -1:
                break
            start = int(data[i+7] + data[i+8] + data[i+9] + data[i+10])
            i = data.find("calc=E:", i)
            end = int(data[i+7] + data[i+8] + data[i+9] + data[i+10])
            df_list.append(pd.DataFrame([dict(Task="Calculate Servo Position", Start=start, End=end)]))

    i = 0
    # SET SERVO THREAD  
    while i < len(data) and i != -1:
        if i < 40:
            i = data.find("set=S:", i)
            start = int(data[i+6])
            i = data.find("set=E:", i)
            end = int(data[i+6])
            df_list.append(pd.DataFrame([dict(Task="Set Servo Position", Start=start, End=end)]))
        elif i < 150:
            i = data.find("set=S:", i)
            start = int(data[i+6] + data[i+7])
            i = data.find("set=E:", i)
            end = int(data[i+6] + data[i+7])
            df_list.append(pd.DataFrame([dict(Task="Set Servo Position", Start=start, End=end)]))
        elif i < 3500:
            i = data.find("set=S:", i)
            start = int(data[i+6] + data[i+7] + data[i+8])
            i = data.find("set=E:", i)
            end = int(data[i+6] + data[i+7] + data[i+8]) 
            df_list.append(pd.DataFrame([dict(Task="Set Servo Position", Start=start, End=end)]))
        else:
            i = data.find("set=S:", i)
            if i == -1:
                break
            start = int(data[i+6] + data[i+7] + data[i+8] + data[i+9])
            i = data.find("set=E:", i)
            end = int(data[i+6] + data[i+7] + data[i+8] + data[i+9])
            df_list.append(pd.DataFrame([dict(Task="Set Servo Position", Start=start, End=end)]))

    i = 0
    # CPU THREAD  
    while i < len(data) and i != -1:
        if i < 40:
            i = data.find("cpu=S:", i)
            start = int(data[i+6])
            i = data.find("cpu=E:", i)
            end = int(data[i+6])
            df_list.append(pd.DataFrame([dict(Task="CPU thread", Start=start, End=end)]))
        elif i < 500:
            i = data.find("cpu=S:", i)
            start = int(data[i+6] + data[i+7])
            i = data.find("cpu=E:", i)
            end = int(data[i+6] + data[i+7])
            df_list.append(pd.DataFrame([dict(Task="CPU thread", Start=start, End=end)]))
        elif i < 3700:
            i = data.find("cpu=S:", i)
            start = int(data[i+6] + data[i+7] + data[i+8])
            i = data.find("cpu=E:", i)
            end = int(data[i+6] + data[i+7] + data[i+8]) 
            df_list.append(pd.DataFrame([dict(Task="CPU thread", Start=start, End=end)]))
        else:
            i = data.find("cpu=S:", i)
            if i == -1:
                break
            start = int(data[i+6] + data[i+7] + data[i+8] + data[i+9])
            i = data.find("cpu=E:", i)
            end = int(data[i+6] + data[i+7] + data[i+8] + data[i+9])
            df_list.append(pd.DataFrame([dict(Task="CPU thread", Start=start, End=end)]))

    i = 0
    # PRESSURE thread  
    while i < len(data) and i != -1:
        if i < 40:
            i = data.find("press=S:", i)
            start = int(data[i+8])
            i = data.find("press=E:", i)
            end = int(data[i+8])
            df_list.append(pd.DataFrame([dict(Task="Pressure thread", Start=start, End=end)]))
        elif i < 1000:
            i = data.find("press=S:", i)
            start = int(data[i+8] + data[i+9])
            i = data.find("press=E:", i)
            end = int(data[i+8] + data[i+9])
            df_list.append(pd.DataFrame([dict(Task="Pressure thread", Start=start, End=end)]))
        elif i < 3500:
            i = data.find("press=S:", i)
            start = int(data[i+8] + data[i+9] + data[i+10])
            i = data.find("press=E:", i)
            end = int(data[i+8] + data[i+9] + data[i+10])
            df_list.append(pd.DataFrame([dict(Task="Pressure thread", Start=start, End=end)]))
        else:
            i = data.find("press=S:", i)
            if i == -1:
                break
            start = int(data[i+8] + data[i+9] + data[i+10] + data[i+11])
            i = data.find("press=E:", i)
            end = int(data[i+8] + data[i+9] + data[i+10] + data[i+11])
            df_list.append(pd.DataFrame([dict(Task="Pressure thread", Start=start, End=end)]))

    i = 0
    # TEMPERATURE THREAD  
    while i < len(data) and i != -1:
        
        if i < 40: 
            i = data.find("temp=S:", i)           
            start = int(data[i+7])
            i = data.find("temp=E:", i)
            end = int(data[i+7])
            df_list.append(pd.DataFrame([dict(Task="Temperature thread", Start=start, End=end)]))
        elif i < 300:
            i = data.find("temp=S:", i)
            start = int(data[i+7] + data[i+8])
            i = data.find("temp=E:", i)
            end = int(data[i+7] + data[i+8])
            df_list.append(pd.DataFrame([dict(Task="Temperature thread", Start=start, End=end)]))
        elif i < 3500:
            i = data.find("temp=S:", i)
            start = int(data[i+7] + data[i+8] + data[i+9])
            i = data.find("temp=E:", i)
            end = int(data[i+7] + data[i+8] + data[i+9]) 
            df_list.append(pd.DataFrame([dict(Task="Temperature thread", Start=start, End=end)]))
        else:
            i = data.find("temp=S:", i)
            if i == -1:
                break
            start = int(data[i+7] + data[i+8] + data[i+9] + data[i+10])
            i = data.find("temp=E:", i)
            end = int(data[i+7] + data[i+8] + data[i+9] + data[i+10])
            df_list.append(pd.DataFrame([dict(Task="Temperature thread", Start=start, End=end)]))

    # CONCATENATE DATA FRAMES
    df = pd.concat(df_list)   
    df['delta'] = df['End'] - df['Start']

    # CREATE GANTT PLOT
    fig = px.timeline(df, x_start="Start", x_end="End", y="Task", color="Task")
    fig.update_yaxes(autorange="reversed")

    fig.layout.xaxis.type = 'linear'
    fig.data[0].x = df.delta.tolist()
    f = fig.full_figure_for_development(warn=False)
    fig.show()




if __name__ == '__main__':

   # SCHEDULING PLOT
   plot_gantt()
   
   # IMPROVEMENT VISUALIZATION
   # plot_improvementDifferences()

   # CPU USAGE
   plot_CPU_usage()

