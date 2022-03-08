import sys
import os
import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import seaborn as sns

def plot_rank():
    df = pd.read_csv("/Users/henryxu/Desktop/Sp2022/858D/858D-assignments/assign1/writeup/data/evaluate_rank.csv")
    # print(df.head(10))
    plt.figure()
    sns.lineplot(x='bit-vector size', y='time', data=df)
    plt.ticklabel_format(style='plain')
    plt.xlabel('bit-vector size (bit)')
    plt.ylabel('time of 1000 rank operations (s)')
    plt.title('bit-vector size versus the time requried to do 1000 rank operations')
    plt.savefig('/Users/henryxu/Desktop/Sp2022/858D/858D-assignments/assign1/writeup/figs/evaluate_rank_time.pdf', bbox_inches="tight")

    df = df[['bit-vector size', 'space overhead', 'n']].copy()
    df.set_index('bit-vector size', inplace=True)
    plt.figure()
    sns.lineplot(data=df)
    plt.ticklabel_format(style='plain')
    plt.xlabel('bit-vector size (bit)')
    plt.ylabel('space overhead (bit)')
    plt.title('bit-vector size versus rank_support space overhead')
    plt.savefig('/Users/henryxu/Desktop/Sp2022/858D/858D-assignments/assign1/writeup/figs/evaluate_rank_space.pdf', bbox_inches="tight")

def plot_select():
    df = pd.read_csv("/Users/henryxu/Desktop/Sp2022/858D/858D-assignments/assign1/writeup/data/evaluate_select.csv")
    # print(df.head(10))
    plt.figure()
    sns.lineplot(x='bit-vector size', y='time', data=df)
    plt.ticklabel_format(style='plain')
    plt.xlabel('bit-vector size (bit)')
    plt.ylabel('time of 1000 select operations (s)')
    plt.title('bit-vector size versus the time requried to do 1000 select operations')
    plt.savefig('/Users/henryxu/Desktop/Sp2022/858D/858D-assignments/assign1/writeup/figs/evaluate_select_time.pdf', bbox_inches="tight")

    df = df[['bit-vector size', 'space overhead', 'n']].copy()
    df.set_index('bit-vector size', inplace=True)
    plt.figure()
    sns.lineplot(data=df)
    plt.ticklabel_format(style='plain')
    plt.xlabel('bit-vector size (bit)')
    plt.ylabel('space overhead (bit)')
    plt.title('bit-vector size versus select_support space overhead')
    plt.savefig('/Users/henryxu/Desktop/Sp2022/858D/858D-assignments/assign1/writeup/figs/evaluate_select_space.pdf', bbox_inches="tight")

def plot_sparse_array():
    df = pd.read_csv("/Users/henryxu/Desktop/Sp2022/858D/858D-assignments/assign1/writeup/data/evaluate_sparse_array.csv")
    # print(df.head(10))
    plt.figure()
    sns.lineplot(x='length', y='time_create_append', hue='sparsity', data=df, markers=True, dashes=False)
    plt.ticklabel_format(style='plain')
    plt.xlabel('sparse array length')
    plt.ylabel('time of create + append all elements (s)')
    plt.title('sparse array length versus the time requried to create and append all elements')
    plt.savefig('/Users/henryxu/Desktop/Sp2022/858D/858D-assignments/assign1/writeup/figs/evaluate_sparse_array_time_create_append.pdf', bbox_inches="tight")

    plt.figure()
    sns.lineplot(x='length', y='time_get_at_rank', hue='sparsity', data=df, markers=True, dashes=False)
    plt.ticklabel_format(style='plain')
    plt.xlabel('sparse array length')
    plt.ylabel('time of 1000 time_get_at_rank operations (s)')
    plt.title('sparse array length versus the time requried for 1000 time_get_at_rank operations')
    plt.savefig('/Users/henryxu/Desktop/Sp2022/858D/858D-assignments/assign1/writeup/figs/evaluate_sparse_array_time_get_at_rank.pdf', bbox_inches="tight")

    plt.figure()
    sns.lineplot(x='length', y='time_get_at_index', hue='sparsity', data=df, markers=True, dashes=False)
    plt.ticklabel_format(style='plain')
    plt.xlabel('sparse array length')
    plt.ylabel('time of 1000 time_get_at_index operations (s)')
    plt.title('sparse array length versus the time requried for 1000 time_get_at_index operations')
    plt.savefig('/Users/henryxu/Desktop/Sp2022/858D/858D-assignments/assign1/writeup/figs/evaluate_sparse_array_time_get_at_index.pdf', bbox_inches="tight")

    plt.figure()
    sns.lineplot(x='length', y='time_num_elem_at', hue='sparsity', data=df, markers=True, dashes=False)
    plt.ticklabel_format(style='plain')
    plt.xlabel('sparse array length')
    plt.ylabel('time of 1000 time_num_elem_at operations (s)')
    plt.title('sparse array length versus the time requried for 1000 time_num_elem_at operations')
    plt.savefig('/Users/henryxu/Desktop/Sp2022/858D/858D-assignments/assign1/writeup/figs/evaluate_sparse_array_time_num_elem_at.pdf', bbox_inches="tight")

    plt.figure()
    sns.lineplot(x='length', y='saving', hue='sparsity', data=df, markers=True, dashes=False)
    plt.ticklabel_format(style='plain')
    plt.xlabel('sparse array length')
    plt.ylabel('space savings compared to directly implement the array (bit)')
    plt.title('sparse array length versus the space savings compared to directly implement the array')
    plt.savefig('/Users/henryxu/Desktop/Sp2022/858D/858D-assignments/assign1/writeup/figs/evaluate_sparse_array_saving.pdf', bbox_inches="tight")
