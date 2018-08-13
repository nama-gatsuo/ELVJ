#version 400

uniform sampler2DRect mixTex;
uniform sampler2DRect tex1;
uniform sampler2DRect tex2;
uniform float thres;

in vec2 vTexCoord;
out vec4 outputColor;

void main(){

    float flag = texture(mixTex, vTexCoord).r;
    if (flag > thres) {
        outputColor = texture(tex1, vTexCoord);
    } else {
        outputColor = texture(tex2, vTexCoord);
    }

}
