import pandas as pd
import matplotlib.pyplot as plt

# Load data from the first CSV (Row-Major vs Column-Major)
df_row_column = pd.read_csv('result/times_row_column.csv')

# Load data from the second CSV (Classic vs Blocks)
df_classic_blocks = pd.read_csv('result/times_block_classic.csv')

# Plot Row-Major vs Column-Major
plt.figure(figsize=(10, 6))
plt.plot(df_row_column['Tamaño'], df_row_column['Time Row-Major'], label='Row-Major Time', marker='o')
plt.plot(df_row_column['Tamaño'], df_row_column['Time Column-Major'], label='Column-Major Time', marker='o')
plt.xlabel('Matrix Size')
plt.ylabel('Time (seconds)')
plt.title('Comparison of Times: Row-Major vs Column-Major')
plt.legend()
plt.grid(True)
# Save the first plot in the result directory
plt.savefig('result/comparison_row_column.png')
plt.close()  # Close the figure to free memory

# Plot Classic vs Blocks
plt.figure(figsize=(10, 6))
plt.plot(df_classic_blocks['Tamaño'], df_classic_blocks['Clásica'], label='Classic', marker='o')
plt.plot(df_classic_blocks['Tamaño'], df_classic_blocks['Bloques'], label='Blocks', marker='o')
plt.xlabel('Matrix Size')
plt.ylabel('Time (seconds)')
plt.title('Comparison of Times: Classic vs Blocks')
plt.legend()
plt.grid(True)
# Save the second plot in the result directory
plt.savefig('result/comparison_classic_blocks.png')
plt.close()  # Close the figure to free memory
