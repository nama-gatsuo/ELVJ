const float PI = 3.14159265359;

in vec2 vTexCoord;
out vec4 outputColor;

uniform vec2 res;
uniform vec3 cp;
uniform vec4 color;
uniform float equiFactor;

void main() {
    vec2 st = vTexCoord / res;
    vec3 ro = cp;

    float lon = st.x * PI * 2.;
    float lat = st.y * PI;

    vec3 rd1 = vec3(cos(lon) * sin(lat), cos(lat), sin(lon) * sin(lat));

    vec2 uv = 2. * st - 1.;
    uv.x *= res.x / res.y;

    vec3 cf = normalize(vec3(0.0) - ro);
    vec3 cs = normalize(cross(cf, vec3(0.0, 1.0, 1.0)));
    vec3 cu = normalize(cross(cs, cf));
    float depth = 2.8;

    vec3 rd2 = normalize(cs * uv.x + cu * uv.y + cf * depth);

    vec3 rd = mix(rd1, rd2, equiFactor);
    //vec3 rd = rd2;

    float d = 1., td = 1.;
    const float md = 100.;
    float cnt = 0.;

    for (int i = 0; i < 100; i++) {
        d = DF(ro + td * rd);
        td += d;
        cnt += 1.0;
        if (d < 0.001) break;
        if (td > md) break;
    }

    float c = td * 0.01;
    vec4 col = vec4(vec3(c) + color.rgb * cnt * 0.15, 1.0);
    col.xyz = vec3(0.9) - col.xyz;

    // outputColor = vec4(st, 1., 1.);
    outputColor = col;
}
