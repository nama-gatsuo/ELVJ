#version 420

layout (binding = 0) uniform sampler2DRect tex0;
uniform vec2 res;
float s2 = 0.3;

in vec2 vTexCoord;
out vec4 outputColor;

void main() {

    vec2 p = (vTexCoord * 2.0 - res) / min(res.x, res.y);

    float d2 = p.x * p.x + p.y * p.y;
    vec2 newTexCoord = (1.0 / d2) * p;

    newTexCoord = ((min(res.x, res.y) * s2) * newTexCoord + res) * 0.5;

    vec4 col = texture(tex0, newTexCoord);

    outputColor = col;
}
