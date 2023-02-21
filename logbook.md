Dec 30 2022:
* Started the project by creating a window using the Windows32 API
* Made the window resizeable and will not crash 1 second after loading
* Gave the window a background color based on current coordinates of each pixel

Feb 19 2023:
* Refactored the code to give responsibility to different files and organize
* The renderer file has classes that can render the background, draw a rectangle based on coordinates and color, and a clear screen method.
* Built a utility file to ensure that when resizing, there is no program crash due to trying to draw the rectangle outside the limits of the screen.

Feb 20 2023:
* Moved to VsCode and had to clarify some code so the compiler would understand

Feb 21 2023:
* Going to start on allowing inputs from the user through keyboard and objects on the screen interacting with each other