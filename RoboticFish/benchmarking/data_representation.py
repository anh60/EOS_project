import numpy as np
import matplotlib.pyplot as plt

def load(filename):
    Data = []
    with open(filename, 'r') as f:
        for line in f:
            try:
                Data.append(line.strip())
            except:
                pass

    return np.array(Data, dtype= int)


if __name__ == '__main__':
    range = (0, 99)
    bins = 10
    data = load('benchmarking/benchmarks.txt')

    # CALCULATE MEAN
    CPU_usage_mean = data.mean(0)
    print('mean CPU usage: ', CPU_usage_mean)
    # CALCULATE STD DEV
    CPU_usage_std = data.std()
    print('standard deviation CPU usage: ', CPU_usage_std)
    
    # PLOT HISTOGRAM
    plt.hist(data, bins, range, color= 'green', rwidth= 0.8)
    plt.xlabel('CPU usage in %')
    plt.ylabel('number of samples')
    plt.title('CPU usage')
    plt.show()

    #TODO MAYBE SAME FOR MEMORY USAGE?


