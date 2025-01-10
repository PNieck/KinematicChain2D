#version 410 core

// vertex position
layout (location = 0) in vec2 aPos;

uniform vec2 maxCoordinates;


void main()
{
    // convert XYZ vertex to XYZW homogeneous coordinate
    gl_Position = vec4(aPos.x / maxCoordinates.x, aPos.y / maxCoordinates.y, 0.f , 1.0);
}
