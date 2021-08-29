
def f(x):
	return x
interact(f, x = 10)
interact(f, x = True)
interact(f, x = "hi there")
interact(f, x = (0, 4)) # this creates knobs from 0 to 4 (inclusive)
interact(f, x = (0., 4., .25))
interact(f, x=['apples','oranges']) # drop down menus
interact(f, x=[('one', 10), ('two', 20)]) # "one" and "two" displayed, but 10 and 20 is passed into the function

# jupyter nbextension enable --py widgetsnbextension
# jupyter labextension install @jupyter-widgets/jupyterlab-manager
from ipywidgets import interact
@interact
def echo(str="Hello, world", times=[1, 5, 1]):
	return (str+" ")*times



# really nice example that's complete and flexible
import ipywidgets as ipy
from ipywidgets import widgets
import IPython
def model():
    islider = ipy.IntSlider(7, 0, 10)
    btn = ipy.Button(description="desc", tooltip="tooltip")
    out = ipy.Output()
    def update(x):
        out.clear_output()
        with out:
            print(f"Update: {x}")
    def btnClicked(x):
        update(x)
        with out:
            print("Clicked")
    islider.observe(update)
    btn.on_click(btnClicked)
    a = ipy.VBox([islider, btn, out])
    return a
model()
