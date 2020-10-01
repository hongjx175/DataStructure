import matplotlib.pyplot as plt

path = "points.txt"

file = open(path, 'r', encoding='UTF-8')

x = []
y = []

num = int(file.readline())
for i in range(0, num):
    x.append(int(file.readline()))
    y.append(int(file.readline()))

plt.figure(num='凸包', figsize=(20, 12))
plt.scatter(x, y)

convex_hull_x = []
convex_hull_y = []
num = int(file.readline())
for i in range(0, num):
    convex_hull_x.append(int(file.readline()))
    convex_hull_y.append(int(file.readline()))
'''for i in range(0, num):
    plt.text(convex_hull_x[i], convex_hull_y[i],i)'''
plt.plot(convex_hull_x, convex_hull_y)

plt.show()
