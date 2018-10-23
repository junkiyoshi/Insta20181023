#version 150

const int number_of_targets = 60;

uniform float time;
uniform vec2 resolution;
uniform vec2 targets1[number_of_targets];
uniform vec2 targets2[number_of_targets];

out vec4 outputColor;

/// Reference
/// https://trap.jp/post/142/
float crs(vec2 v1, vec2 v2) {
    return v1.x*v2.y - v1.y*v2.x;
}

// 2点v1, v2を端点に持つ線分との距離を返す
float line(vec2 p, vec2 v1, vec2 v2) {
    p  -= v1;
    vec2 v = v2-v1;
    float t = dot(p, normalize(v));
    if (t<0.0) {
        return length(p);
    } else if (t>length(v)) {
        return length(p-v);
    } else {
        return abs(crs(p, normalize(v)));
    }
}

void main() {

  vec2 p = (gl_FragCoord.xy * 2.0 - resolution) / min(resolution.x, resolution.y);
  vec3 color = vec3(0.0);

  for(int i = 0; i < 60; i++){

    vec2 t1 = vec2(targets1[i].x, -targets1[i].y) / min(resolution.x, resolution.y) * 2.0;
    vec2 t2 = vec2(targets2[i].x, -targets2[i].y) / min(resolution.x, resolution.y) * 2.0;
    t1.xy += vec2(-resolution.x, resolution.y) / min(resolution.x, resolution.y);
    t2.xy += vec2(-resolution.x, resolution.y) / min(resolution.x, resolution.y);

    float v = 0.005 / line(p, t1, t2);
    vec3 c = vec3(smoothstep(0.0, 1.0, v), 0.0, 0.0);

    color += c;
  }

  outputColor = vec4(color, 1.0);
}
