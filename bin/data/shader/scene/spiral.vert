#version 150
#pragma include "./util/random.frag"

uniform mat4 modelViewProjectionMatrix;
in vec4 position; // random val in -1 ~ 1
in vec4 color;
in vec2 texcoord;
out vec4 vColor;

uniform float rSize;
uniform float sSize;
uniform float tSize;

uniform float rInit;
uniform float sStep;
uniform float tStep;
uniform float rStep;

uniform float time;

//float PI = 3.1415926535897932384626433832795;


void main() {

    float ri = mod(texcoord.x, rSize);
    float ti = floor(texcoord.x / rSize);
    float si = texcoord.y;

    float r = rInit + ri * rStep;
    float t = 3.0 * PI / tSize * ti + tStep * ri + rand(texcoord) * 0.03;
    float s = 1.5 * PI / sSize * si + sStep * ri + rand(texcoord) * 0.03;

    vec3 p;
    p.x = r * cos(t) * sin(s);
    p.y = r * sin(t) * sin(s);
    p.z = r * cos(s);

    vColor = color;
    gl_Position = modelViewProjectionMatrix * vec4(p.xyz, 1.0);
    gl_PointSize = 800.0 / gl_Position.w;

}
