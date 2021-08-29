
%matplotlib inline
import matplotlib.pyplot as plt
import matplotlib.image as mpimg

mpimg.imread('abc.jpg')

plt.plot(x, y)
plt.scatter(x, y)
plt.imshow(np rank 2/3 tensor)



t = np.linspace(0, math.pi*3, 100)
x = np.sin(t); y = np.cos(t)
fig, (ax0, ax1) = plt.subplots(ncols=2, subplot_kw={"projection":'3d'}, figsize=(10, 6), dpi=100)
ax0.scatter(x, y, t); ax1.plot(x, y, 8-t)


x = np.linspace(-1, 1, 50)
x, y = np.meshgrid(x, x)
z = x ** 2 + y ** 2
fig, (ax0, ax1, ax2) = plt.subplots(ncols=3, subplot_kw={"projection":"3d"}, figsize=(10, 6), dpi=100)
ax0.plot_surface(x, y, z)
ax1.plot_wireframe(x, y, z)
ax2.contour(x, y, z)


