# Computer Graphics - Assignment 1 Report

**Student Name:** Ayauzhan Baurzhanova

**Student ID:** SE-2416

**Operating System Tested:** Windows 11

**Development Environment:** Visual Studio 2022 (C++ Console App with FreeGLUT, GLEW, and GLM)

---

## Overview
This repository contains the complete implementation of Assignment 1. All programs strictly utilize the modern OpenGL Core Profile. Vertex Array Objects (VAOs), Vertex Buffer Objects (VBOs), and custom shaders are used throughout to render geometry. Deprecated OpenGL functions (such as `glBegin()` and `glEnd()`) were strictly avoided in all tasks 

---

## Task 1: Getting Started

### 1. Single Red Triangle
*   **Implementation Steps:** I initialized a basic OpenGL application window and defined an array of three 2D vertices. These vertices were loaded into a VBO and bound to a VAO. A basic vertex and fragment shader pipeline was compiled to process the coordinates and output a static red color vector for the rasterizer.

### 2. Single Blue Square
*   **Implementation Steps:** I modified the base `red_triangle.cpp` code to render a blue square that scales to fit inside the window
*   **Code Changes:** I added a fourth vertex to the coordinate array, changed the draw call to process 4 vertices, and updated the fragment shader output to emit blue (`vec4(0.0, 0.0, 1.0, 1.0)`) instead of red.

---

## Task 2: Drawing 2D Polygons with Color

### Part 1: Recreating the Reference Image
A program was created to open a $500\times500$ pixel window containing four distinct geometric objects[cite: 24]. Attribute data was passed to the vertex shader utilizing the specific variable names `"vPosition"` and `"vColor"`

*   **Concentric Squares (Center):** 
    *   Calculated vertex corners using angles, establishing the first point at $\pi/4$ and incrementing by $\pi/2$ for subsequent points
    *   Drawn by looping through 5 overlapping square arrays, varying the provided RGB color values between black and white for each layer
*   **Red Ellipse (Top Left):** 
    *   Utilized the parametric circle equations inside a loop
    *   The y coordinate was multiplied by 0.6 to scale the height down to 60% of the width
*   **Color-Interpolated Triangle (Top Center):** 
    *   Defined using three distinct vertices, each bound to a different primary color (Red, Green, Blue) using the `"vColor"` attribute. The fragment shader automatically generated the color-interpolated gradient across the face
*   **Shaded Circle (Top Right):** 
    *   Generated points around the perimeter by incrementing an angle variable 
    *   Drawn using `GL_TRIANGLE_FAN`, ensuring the first declared vertex was positioned exactly at the center of the circle
    *   To achieve the required edge-shading effect, the red color value was passed as a mathematical function of the current angle during vertex generation

### Part 2: Creative 2D Scene
*   **Implementation Steps:** Created a standalone program rendering an original scene featuring at least 3 distinct objects
*   **Techniques Used:** Applied the mathematical coordinate generation learned in Part 1 to build new layered polygons. Demonstrated creativity by utilizing custom RGB color ranges, structural offsets, and a combination of `GL_TRIANGLES` and `GL_TRIANGLE_FAN` topologies.

---

## Compilation and Execution Instructions

1. **Prerequisites:** Ensure Visual Studio 2022 is installed with the "Desktop development with C++" workload. 
2. **Library Setup:** The project relies on the FreeGLUT, GLEW, and GLM packages. If building from source, ensure these packages are restored/installed via the NuGet Package Manager.
3. **Running the Code:** 
    *   Open the `.sln` file in Visual Studio.
    *   Set the active configuration to **Debug** or **Release** (x86/x64).
    *   Press the **Local Windows Debugger** button (or `F5`) to compile, link, and launch the executable.
