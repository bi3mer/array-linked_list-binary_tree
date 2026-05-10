import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import os

csv_path = os.path.join(os.path.dirname(__file__), '..', 'results.csv')
df = pd.read_csv(csv_path)

plots_dir = os.path.join(os.path.dirname(__file__), '..', 'plots')
os.makedirs(plots_dir, exist_ok=True)

operations = df['operation'].unique()
structures = ['Array', 'SortedArray', 'LinkedList', 'LinkedListTail', 'DoublyLinkedList', 'BST']
styles = {
    'Array':           {'color': 'tab:blue',   'linestyle': '-',  'marker': 'o'},
    'SortedArray':     {'color': 'tab:orange', 'linestyle': '--', 'marker': 's'},
    'LinkedList':      {'color': 'tab:green',  'linestyle': '-',  'marker': '^'},
    'LinkedListTail':  {'color': 'tab:purple', 'linestyle': '--', 'marker': 'D'},
    'DoublyLinkedList':{'color': 'tab:brown',  'linestyle': '-.',  'marker': 'v'},
    'BST':             {'color': 'tab:red',    'linestyle': ':',  'marker': '*'},
}

for op in operations:
    subset = df[df['operation'] == op]
    fig, ax = plt.subplots(figsize=(7, 5))
    for s in structures:
        valid = subset[s].notna()
        if valid.any():
            ax.plot(subset.loc[valid, 'N'], subset.loc[valid, s],
                    label=s, linewidth=2, **styles[s])
    ax.set_title(op, fontsize=13, fontweight='bold')
    ax.set_xlabel('N')
    ax.set_ylabel('Time (ms)')
    ax.legend()
    ax.xaxis.set_major_formatter(ticker.FuncFormatter(lambda x, _: f'{int(x):,}'))
    ax.grid(True, alpha=0.3)
    plt.tight_layout()
    out_path = os.path.join(plots_dir, f'{op}.png')
    plt.savefig(out_path, dpi=150)
    plt.close(fig)
    print(f'saved {out_path}')
