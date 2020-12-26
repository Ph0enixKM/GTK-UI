<div align="center">
    <img src="img/liblogo.png">
</div>

# GTK-UI 🎨

**GTK-UI** is a library for creating an easy interfaces in C language using low level GTK library.

## Instalation

In order to install this library - clone this repository (or download in `.zip` format) and then include the header and compile with the source.

```c
#include <gtkui.h>
```

## Documentation

### Hello world

The first step of learning how GTK-UI works is to create a Hello World program. As you can see it looks pretty much similar to the vanilla GTK version.

```c
#include <gtk/gtk.h>
#include <gtkui.h>

int main(int argc, char* argv[]) {
    gtk_init(&argc, &argv);
    // Here is our GTK-UI function
    UIPrint("Hello World");
    gtk_main();
}
```

> Keep in mind that **GTK-UI** works in synergy with **GTK** and is IS NOT supposed to replace the usage of GTK library.

<div align="center">
    <img src="img/hello.png">
</div>

- ### Creating a window

```c
UI window = UICreateWindow("Title", (WindowConfig) {
    .width = 1020,
    .height = 720,
    .center = true,
    .resizable = true,
    .border = 10
});
```

You do not have to show the window - it's set to be **visible** by default - the same thing applies to all components made by GTK-UI

- ### Creating a label

```c
UI label = UICreateLabel("Some text here");
UIAppend(window, label);
```

- ### Creating a button

```c
UI button = UICreateButton("Click me!", onclick);
UIAppend(window, button);
```

`onclick` in this example is a pointer to a function that will be invoked once the button is clicked

- ### Creating a box

```c
UI boxh = UICreateBox('-'); // Horizontal box
UI boxv = UICreateBox('|'); // Vertical box
```

The orientation describes direction in which children will line up.

- ### Creating an image

```c
UI img = UICreateImage("path/to/image.png");
```

You can also load up image file and then reuse it's data for later usage. This way you can reuse the image much faster and use less resources.

```c
GdkPixbuf* imgData = UILoadImageData("path/to/image.png");
UI img = UILoadImage(imgData);
UIAppend(window, img);
```

- ### Creating a grid

```c
UI grid = UICreateGrid(true); // Homogeneous?
IAppend(window, grid);
// Let's add an image to our grid
UIAttach(grid, img, 0, 0, 0, 0);
// Numerical values indicate x, y, width, height
```

- ### Attaching event callbacks

```c
UI window = UICreateWindow("Title", options);
UIEvent(window, "destroyed", qtk_main_quit, NULL);
```

- ### Load CSS
  
  - From file
    
    ```c
    UILoadCSS("path/to/style.css");
    ```
  
  - From string
    
    ```c
    UILoadCSSData(
        ".box {"
        "background: red;"
        "}"
    );
    ```

- ### Set CSS ID
  
  ```c
  UISetID(widget, "container");
  ```

- ### Manipulate with CSS class names
  
  ```c
  UIAddClass(widget, "btn");
  bool has = UIHasClass(widget, "btn");
  UIRemoveClass(widget, "btn");
  ```

- ### Message box
  
  ```c
  UIError("Oops!");
  UIWarning("Are you sure?");
  UIPrint("Debug information");
  ```
  
  
