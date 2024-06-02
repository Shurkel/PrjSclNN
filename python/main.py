import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Read points from file
def read_points_from_file(filename):
    points = []
    with open(filename, 'r') as file:
        for line in file:
            study_hours, sleep_hours, pass_fail, color = line.strip().split(',')
            points.append((float(study_hours), float(sleep_hours), int(pass_fail), color))
    return points

# Plot points
def plot_points(points):
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    for study_hours, sleep_hours, pass_fail, color in points:
        ax.scatter(study_hours, sleep_hours, pass_fail, c=color)
    ax.set_xlabel('Study Hours')
    ax.set_ylabel('Sleep Hours')
    ax.set_zlabel('Pass/Fail')
    ax.set_title('Student Performance')
    plt.show()

# Main function
if __name__ == '__main__':
    filename = '../python/data.txt'  # Specify the filename
    points = read_points_from_file(filename)
    plot_points(points)
