import numpy as np
import matplotlib.pyplot as plt

def function1(x):
    return x*x/4

def function2(x):
    return (x+-0.2)/x*x*0.5

# Generate x values
x = np.linspace(0, 1, 100)

# Calculate y values for each function
y1 = function1(x)
y2 = function2(x)

# Find intersection points
idx = np.where(np.abs(y1-y2)<0.01)[0]

# Plot the functions
plt.plot(x, y1, label='function1: y=x*x')
plt.plot(x, y2, label='function2: y=x')

# Plot the intersection points
plt.plot(x[idx], y1[idx], 'ro')

plt.xlabel('x')
plt.ylabel('y')
plt.legend()
plt.title('Intersection of Two Functions')
plt.grid(True)
plt.show()