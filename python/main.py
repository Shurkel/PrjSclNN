import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

# Input data (study hours, sleep hours)
input_data = [
    # Fail values
    [2, 4], [3, 5], [1, 3], [4, 2], [2, 1],
    [3, 2], [1, 5], [4, 3], [2, 6], [3, 1],
    [2, 7], [1, 4], [4, 5], [3, 6], [1, 1],
    [4, 1], [2, 2], [3, 3], [1, 2], [4, 4],
    # Pass values
    [8, 10], [9, 11], [7, 9], [10, 8], [8, 7],
    [9, 8], [7, 11], [10, 9], [8, 12], [9, 7],
    [8, 13], [7, 10], [10, 11], [9, 12], [7, 7],
    [10, 7], [8, 8], [9, 9], [7, 8], [10, 10],
    [6, 6], [11, 11], [5, 5], [12, 12], [6, 5]
]

# Convert the data to NumPy array
input_data = np.array(input_data)

# Reverse the direction of sleep hours
input_data[:, 1] *= -1

# Create a scatter plot
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.scatter(input_data[:20, 0], input_data[:20, 1], np.zeros(20), c='r', label='Fail')
ax.scatter(input_data[20:, 0], input_data[20:, 1], np.ones_like(input_data[20:, 0]), c='g', label='Pass')

# Set labels and title
ax.set_xlabel('Study Hours')
ax.set_ylabel('Sleep Hours')
ax.set_zlabel('Pass/Fail')
ax.set_title('Student Performance')
ax.legend()

plt.show()
