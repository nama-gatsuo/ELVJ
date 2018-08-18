#version 150
precision mediump float;

in vec4 vColor;
out vec4 outputColor;

void main() {
    
    float gamma = 1.0 / 2.2;
    
    vec3 n;
    n.xy = gl_PointCoord.xy * 2.0 - 1.0;
    n.z = 1.0 - dot(n.xy, n.xy);
    
    float pAlpha = smoothstep(0.0, 1.0, n.z);
    
    outputColor = vec4(vColor.rgb, pAlpha);
}
