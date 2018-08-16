#version 420

layout (binding = 0) uniform sampler2DRect tex;
uniform vec2 res;
uniform float slit;
in vec2 vTexCoord;
out vec4 outputColor;

void main (void) {

    vec2 texCoord = vec2(3.0 + floor(vTexCoord.x / slit) * slit, vTexCoord.y);
    outputColor = texture(tex, texCoord);

}
