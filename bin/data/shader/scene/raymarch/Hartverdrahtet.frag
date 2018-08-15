#version 400
uniform vec3 cs;
uniform float fs;
uniform vec3 fc;
uniform float fu;
uniform float fd;

float DF(vec3 z0) {

	float v = 1.;
	for(int i = 0; i < 9; i++){
		z0 = 2. * clamp(z0, -cs, cs) - z0;
		float c = max(fs / dot(z0, z0), 1.);
		z0 *= c;
		v *= c;
		z0 += fc;
	}
	float z = length(z0.xy) - fu;
	return fd * max(z, abs(length(z0.xy) * z0.z) / sqrt(dot(z0, z0))) / abs(v);
}

#pragma include "Renderer.frag"
