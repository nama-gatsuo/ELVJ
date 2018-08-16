#version 420

/*
    based on https://www.shadertoy.com/view/4sfGDj
*/

layout (binding = 0) uniform sampler2DRect tex;
uniform vec2 res;
uniform float time;

in vec2 vTexCoord;
out vec4 outputColor;

void main() {

	vec4 base = texture(tex, vTexCoord);

	const int maxiters = 80;
	//int iters = int(mod(scaledT, float(maxiters)));
    int iters = 68 + int(5. * sin(time));
	for (int i = 0; i < maxiters; i++) {
		base *= 0.8 + (clamp((float(i < iters)) + (1.1/float(iters)) * vec4(vec2(res.x * dFdx(base.rb)), vec2(res.y * dFdy(base.ga))), 0.0, 1.0) * 0.25);
	}

	outputColor = base;
}
