#version 400
uniform mat4 modelViewMatrix; // oF Default
uniform mat4 modelViewProjectionMatrix; // oF Default
in vec4 position; // oF Default
in vec4 normal; // oF Default
in vec4 color; // oF Default
in vec2 texcoord; // oF Default

uniform float lds;
uniform float seed;

out vec4 vPosition;
out float vDepth;
out vec2 vTexCoord;
out vec4 vColor;

void main(){
    vec3 p = position.xyz;
    p += normal.xyz * seed * 40.;

    gl_Position = modelViewProjectionMatrix * vec4(p, 1.);

    vec4 viewPos = modelViewMatrix * vec4(p, 1.);
    vDepth = - viewPos.z * lds;
    vTexCoord = texcoord;
    vColor = color;
    vPosition = viewPos;
}
