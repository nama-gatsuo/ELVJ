#version 400

uniform vec2 res;
uniform float time;


int ns[2];   // num
float rs[2]; // radius
uniform int fs[2];   // freq
float ps[2]; // power

in vec2 vTexCoord;
out vec4 outputColor;

const float PI = 3.14159265359;

float waveSum(int index, in vec2 uv) {
    float sum = 0.;
    float limit = ns[index];

    for (float i = 0.; i < 17.; i += 1.) {

        if (i >= limit) return sum;

        float divisor = 0.5 * ns[index];
        vec2 p = rs[index] * vec2(cos(PI / divisor * i), sin(PI / divisor * i));
        float dist = distance(p, uv);
        sum += ps[index] * cos(dist * PI * fs[index] - time);

    }
    return sum;
}

void main(){

    ns[0] = 4;
    rs[0] = (cos(0.3-time*0.1) + 1.) * 1.11;
    ps[0] = sin(0.1-time) * 1.;

    ns[1] = 8;
    rs[1] = (cos(0.3-time*0.2)+ 1.) * 2.51;
    ps[1] = sin(time) * 1.;

    vec2 uv = (vTexCoord / res.y) * 2. - vec2(res) / res.y;

    float sum = 0.;
    sum += waveSum(0, uv);
    sum += waveSum(1, uv);

    sum *= 0.5;
    sum += 0.5;

    outputColor = vec4(vec3(sum), 1.);

}
