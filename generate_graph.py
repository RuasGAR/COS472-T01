import os
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

def main():
    xp_path = "./experiments/"

    for filename in os.listdir(xp_path):
        with open(f"./experiments/{filename}", "r") as f:
            data = pd.read_csv(f,sep=";",index_col=False,names=["Size", "Time"]);
            title = filename.split(".")[0].replace("xp","").replace('__','_').replace('_',' ').title();
            title = title.split(" ");
            title = f"Matriz-Vetor ({title[1]},{title[2]}) em {title[3]}";
        generate_graph(data, title);


def generate_graph(data, title):
    x = data["Size"].values;
    y = data["Time"].values;

    _fig, ax = plt.subplots();

    coeffs = np.polyfit(x,y,2);
    fit = np.polyval(coeffs,x);

    ax.plot(x, fit, 'r-');
    ax.set_title(title);
    ax.legend();

    plt.scatter(data["Size"],data["Time"]);
    plt.xlabel('Número de elementos (N)');
    plt.ylabel('Tempo de execução (seg)');
    plt.show()

main();