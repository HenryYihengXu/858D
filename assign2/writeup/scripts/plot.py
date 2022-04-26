import sys
import os
import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import seaborn as sns

def plot_buildsa():
    df = pd.read_csv("/Users/henryxu/Desktop/Sp2022/858D/858D-assignments/assign2/writeup/data/evaluate_buildsa.csv")
    
    plt.figure()
    sns.lineplot(x='size(MB)', y='time(s)', hue='k', data=df, marker="o", dashes=False)
    # plt.ticklabel_format(style='plain')
    plt.xlabel('reference size (MB)')
    plt.ylabel('time building suffix array (s)')
    plt.xticks(list(df['size(MB)']))
    plt.title('reference size versus the time requried to build corresponding suffix array')
    plt.savefig('/Users/henryxu/Desktop/Sp2022/858D/858D-assignments/assign2/writeup/figs/evaluate_buildsa_time.pdf', bbox_inches="tight")

    plt.figure()
    sns.lineplot(x='size(MB)', y='serial-size(MB)', hue='k', data=df, marker="o", dashes=False)
    # plt.ticklabel_format(style='plain')
    plt.xlabel('reference size (MB)')
    plt.ylabel('size of serialized suffix array (MB)')
    plt.xticks(list(df['size(MB)']))
    plt.title('reference size versus size of the serialized corresponding suffix array')
    plt.savefig('/Users/henryxu/Desktop/Sp2022/858D/858D-assignments/assign2/writeup/figs/evaluate_buildsa_size.pdf', bbox_inches="tight")

    df = df[df['k'] == 0].copy()
    plt.figure()
    sns.lineplot(x='size(MB)', y='time(s)', data=df, marker="o", dashes=False)
    # plt.ticklabel_format(style='plain')
    plt.xlabel('reference size (MB)')
    plt.ylabel('time building suffix array (s)')
    plt.xticks(list(df['size(MB)']))
    for x, y in zip(df['size(MB)'], df['time(s)']):
        plt.text(x, y, y)
    plt.title('reference size versus the time requried to build corresponding suffix array')
    plt.savefig('/Users/henryxu/Desktop/Sp2022/858D/858D-assignments/assign2/writeup/figs/evaluate_buildsa_time_k0.pdf', bbox_inches="tight")

    plt.figure()
    sns.lineplot(x='size(MB)', y='serial-size(MB)', data=df, marker="o", dashes=False)
    # plt.ticklabel_format(style='plain')
    plt.xlabel('reference size (MB)')
    plt.ylabel('size of serialized suffix array (MB)')
    plt.xticks(list(df['size(MB)']))
    for x, y in zip(df['size(MB)'], df['serial-size(MB)']):
        plt.text(x, y, y)
    plt.title('reference size versus size of the serialized corresponding suffix array')
    plt.savefig('/Users/henryxu/Desktop/Sp2022/858D/858D-assignments/assign2/writeup/figs/evaluate_buildsa_size_k0.pdf', bbox_inches="tight")
