# Animated Ray Tracer
<img src="images/hallway.gif" height="400px">

A ray tracer implemented in C++. Instead of generating one static image, however, this program takes input files ([example](Raytracer/world/whitted/first.sphere)) that define animation keyframes for each of the objects in the scene and uses them to generate a series of images which can be strung together as an animation, like the gif above.

### Dependencies
+ Relies on the [LodePNG](https://github.com/lvandeve/lodepng) NuGet package for writing .png files.
+ Relies on the [GLMathematics](https://www.nuget.org/packages/glm/0.9.9.600) NuGet package for matrix/vector math
+ Relies on [FastNoise](https://github.com/Auburns/FastNoise) for noise functions
