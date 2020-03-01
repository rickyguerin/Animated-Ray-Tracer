# Raytracer
A ray tracer I'm building to learn C++ and to practice what I learned in CSCI-711 Global Illumination.

### Current Functionality
+ Can render spheres with flat shading
+ Can parse input files like [this](Raytracer/world/prog.txt) that define keyframes for one sphere
+ Can use keyframes to produce a series of images that can be turned into a gif/mp4

### Dependencies
+ Relies on the [LodePNG](https://github.com/lvandeve/lodepng) NuGet package for writing .png files.
+ Relies on the [GLMathematics](https://www.nuget.org/packages/glm/0.9.9.600) NuGet package for matrix/vector math
