#version 400

/*
    based on https://www.shadertoy.com/view/4sfGDj
*/

uniform sampler2D tex;
uniform vec2 res;
uniform float time;

in vec2 vTexCoord;
out vec4 outputColor;

void main() {

	vec4 base = texture(tex, vTexCoord);
	vec4 color = base;

	const int maxiters = 50;
	//int iters = int(mod(scaledT, float(maxiters)));
    int iters = int(sin(time * 10.) * 0.5 + 0.5) * 50;
	for (int i = 0; i < maxiters; i++) {
		color *= 0.8 + (clamp((float(i < iters)) + (1.0/float(iters)) * vec4(vec2(res.x * dFdx(color.rg)), vec2(res.y * dFdy(color.ba))), 0.0, 1.0) * 0.25);
	}

	outputColor = color;
}
