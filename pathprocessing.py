import numpy as np
import matplotlib.pyplot as plt

# Create a figure and axis
fig, ax = plt.subplots()
path = []
new_path = []
path_x = []
path_y = []

# Callback function to capture mouse movement
def onmove(event):
    if event.inaxes is not None and event.button == 1:  # Check if left mouse button is pressed
        path.append((event.xdata, event.ydata))
        ax.plot(event.xdata, event.ydata, 'b.', alpha=0.3)  # Plot the point with low opacity
        plt.draw()

# Connect the callback function to the figure
fig.canvas.mpl_connect('motion_notify_event', onmove)

# Show the plot and wait for user input
ax.set_xlim(0,10)
ax.set_ylim(0,10)
ax.set_aspect('equal')
plt.title('Draw the path with your mouse. Close the window when done.')
plt.show()

def select_waypoints(interval):
    for i in range(0, int(len(path)), interval):
        new_path.append(path[i])

concentration = 20
interval = int(len(path)/concentration)
select_waypoints(interval)

# plt.plot(path_x ,path_y, 'o-r')

for coord in new_path:
   plt.plot(coord[0], coord[1], 'or')


plt.show()

print("path:", path)
print("newpath:", new_path)
print(new_path[0][0])

integers = new_path
i= 0

with open("ints.txt", "w") as file:
    for num in integers:
        file.write(str(num[0]))
        file.write("\n")
        file.write(str(num[1]))
        file.write("\n")
        i+=1
print(i*2)

