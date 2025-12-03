import matplotlib.pyplot as plt
import pandas as pd 
import numpy as np
from matplotlib.animation import FuncAnimation


def getOptimalWeight(file_path):
    last_line = None
    with open(file_path, "r") as f:
        for line in f:
            last_line = line
    return float(last_line)


df = pd.read_csv('data.csv')
x=np.linspace(0,60 ,100)
b=0
w=getOptimalWeight('weight_file')

y=x*w+b

fs=df['foot_size_cm']
ps=df['penis_size_cm']

plt.plot(x,y,'r')
plt.plot(fs,ps,'bo')
plt.title("test")
plt.show()