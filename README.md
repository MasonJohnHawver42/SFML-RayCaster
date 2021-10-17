# RayCasterEngine
A simple ray caster engine based on the wolfenstien 3d engine made by id software.

# How it Works

A grid of cells is stores the walls and sprites asociated with the walls. Then a ray for each collum of the screen is cast from the player at a specific angle, and determines the distance and whitch wall is hit. Then a strip of the wall sprite hit by the ray is scalled to a specific height based of the distance to the wall is to the player and is drawn to the screen. In that last step there is also a ray cast for sprites too.

# Versions:

V1 - https://youtu.be/U_pcrTzJWkU (basic raycaster)

V1.1 - https://youtu.be/vAEl36fxl68 (added map editor)

V2.0 - https://youtu.be/Fp03-gWVtss (billboard sprites)

V2.2 - <link pending> (directional sprites (sorry for the year-ish wait (was on leave (also working on other repos)))

# Demos on Desmos

Demos on desmos showcassing the math used to calculate the values nessasary to render a scene on the screen.

 - ray caster demo - https://www.desmos.com/calculator/8h3dkoubzj ( how the distance to the walls is found )

 - sprites demo - https://www.desmos.com/calculator/gfdjpd1vzu ( how the dis and height / size of the sprites are found so they can be drawn. )

# Future Updates

 - real time wall and player collisions (harder (depending on the decided method))
 - variable wall heights (hard - have to work out the maths for it and change the rendering method in the camera classs)
 - variable actor heights ( med - just have to change the rendering method in the camera a bit, and think about the maths for this a tad)
 - better map edditor and a texture editor.
