#version 400

uniform float minr;
uniform float maxr;
uniform float minc;
uniform float maxc;
uniform float scale;
uniform vec3 p0;
uniform vec3 offset;

float DF(vec3 z0) {
    z0 = mod(z0, 2.0);
    vec4 s = vec4(vec3(scale), abs(scale));
    vec4 z = vec4(z0, 1.0);
    for (int n = 0; n < 3; n++) {
        z.xyz = clamp(z.xyz, minc, maxc) * 2.0 - z.xyz;
        z *= s / clamp(dot(z.xyz, z.xyz), minr, maxr) * 1.;
        z += vec4(p0, 0.0);
    }
    float dS = (length(max(abs(z.xyz) - offset, 0.0)) - 0.06) / z.w;
    return dS;
}

#pragma include "Renderer.frag"
