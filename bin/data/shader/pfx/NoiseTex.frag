#version 400
#pragma include "noise3d.frag"

uniform vec2 res;
uniform float time;
uniform float noiseRes;
uniform float noiseStrength;

in vec2 vTexCoord;
out vec4 outputColor;

const float PI = 3.14159265359;

void main(){

    float sum = pow(cnoise(vec3(vTexCoord * noiseRes, time * 3. + noiseStrength)) * 2., 2.);
    outputColor = vec4(vec3(sum), 1.);

}
