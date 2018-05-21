#simple GUI
#input from SD card is an array with time, speed, other values on there

import matplotlib as mpl
import numpy as np
import sys
if sys.version_info[0] < 3:
    import Tkinter as tk
else:
    import tkinter as tk
import matplotlib.backends.tkagg as tkagg
from matplotlib.backends.backend_agg import FigureCanvasAgg
from tkinter import *
import csv

xvals=[]
yvals=[]

with open('SPEED1.CSV') as csvfile:
    readcsv = csv.reader(csvfile, delimiter=',')
    for row in readcsv:
            xval = row[0]
            yval = row[1]
            xvals.append(xval)
            yvals.append(yval)
    #xvals=xvals[1:200]
    #yvals=yvals[1:200]
            


def draw_figure(canvas, figure, loc=(0, 0)):
    """ Draw a matplotlib figure onto a Tk canvas

    loc: location of top-left corner of figure on canvas in pixels.
    Inspired by matplotlib source: lib/matplotlib/backends/backend_tkagg.py
    """
    figure_canvas_agg = FigureCanvasAgg(figure)
    figure_canvas_agg.draw()
    figure_x, figure_y, figure_w, figure_h = figure.bbox.bounds
    figure_w, figure_h = int(figure_w), int(figure_h)
    photo = tk.PhotoImage(master=canvas, width=figure_w, height=figure_h)

    # Position: convert from top-left anchor to center anchor
    canvas.create_image(loc[0] + figure_w/2, loc[1] + figure_h/2, image=photo)

    # Unfortunately, there's no accessor for the pointer to the native renderer
    tkagg.blit(photo, figure_canvas_agg.get_renderer()._renderer, colormode=2)

    # Return a handle which contains a reference to the photo object
    # which must be kept live or else the picture disappears
    return photo


# Create a canvas
w, h = 1000, 650
window = tk.Tk()
window.title("Potential GUI 2")

canvas = tk.Canvas(window, width=w, height=h)
canvas.pack()


# Generate some example data
#X=[2,3,4,5,6,7]
#Y=[1,1,1,1,2,2]

X = xvals
Y = yvals
print(xvals)
print(yvals)

# Create the figure we desire to add to an existing canvas
fig = mpl.figure.Figure(figsize=(6, 4))
ax = fig.add_axes([0, 0, 1, 1])
ax.plot(X,Y)

# Keep this handle alive, or else figure will disappear
fig_x, fig_y = 100, 100
fig_photo = draw_figure(canvas, fig, loc=(fig_x, fig_y))
fig_w, fig_h = fig_photo.width(), fig_photo.height()

# Add more elements to the canvas, potentially on top of the figure
canvas.create_text(100, 50, text="Raw SD card data", anchor="s")

# ROUND 2 Create the figure we desire to add to an existing canvas
#fig2 = mpl.figure.Figure(figsize=(6, 4))
#ax = fig2.add_axes([0, 0, 1, 1])
#ax.plot(Y)

# ROUND 2 Keep this handle alive, or else figure will disappear
#fig2_x, fig2_y = 100, 100
#fig2_photo = draw_figure(canvas, fig2, loc=(fig2_x, fig2_y))
#fig2_w, fig2_h = fig2_photo.width(), fig2_photo.height()

window.mainloop()

