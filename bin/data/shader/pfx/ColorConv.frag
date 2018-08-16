#version 420

layout (binding = 0) uniform sampler2DRect tex0;

uniform int isNega;
uniform vec4 theme;

in vec4 vColor;
in vec2 vTexCoord;
out vec4 outputColor;

void main() {

    vec4 col = texture(tex0, vTexCoord);
//    col.rgb = pow(col.rgb, vec3(1.0/2.2));

    if (isNega == 1) {
        col.rgb = vec3(dot(vec3(1.0) - col.rgb, vec3(1.0)) / 3.0);
    } else {
        //col.rgb = vec3(dot(col.rgb, vec3(1.0)) / 3.0);
        col.rgb = vec3(1.) - col.rgb;
    }
    col.rgb *= theme.rgb;

    outputColor = col;
    //outputColor = vec4(vTexCoord, 1., 1.);
}
