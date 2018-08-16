#version 420

layout (binding = 0) uniform sampler2DRect tex;
uniform float rand;

in vec2 vTexCoord;
out vec4 outputColor;

void main (void) {

    vec4 col = texture(tex, vTexCoord);
    vec4 col_r = texture(tex, vTexCoord + vec2(-35.) * rand);
    vec4 col_l = texture(tex, vTexCoord + vec2(35., 45) * rand);
    vec4 col_g = texture(tex, vTexCoord + vec2( -10.5 * rand, 0));


    col.b = col.b + col_r.b * max(1.0,sin(vTexCoord.y * 1.2) * 2.5) * rand;
    col.r = col.r + col_l.r * max(1.0,sin(vTexCoord.y * 1.2) * 2.5) * rand;
    col.g = col.g + col_g.g * max(1.0,sin(vTexCoord.y * 1.2) * 2.5) * rand;

    outputColor = col;
}
