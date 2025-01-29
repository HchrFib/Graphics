#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;

out vec4 fragColor;

uniform sampler2D colorMap;

void main()
{
    const int NUM = 6;
    int n_pos = int(NUM * vtexCoord.x);

    // six first digits: 480267
    vec2 offset;
    if (n_pos < 1) {
        offset = vec2(4 * 0.1, 0);
    }
    else if (n_pos < 2) {
        offset = vec2(8 * 0.1, 0);
    }
    else if (n_pos < 3) {
        offset = vec2(0 * 0.1, 0);
    }
    else if (n_pos < 4) {
        offset = vec2(2 * 0.1, 0);
    }
    else if (n_pos < 5) {
        offset = vec2(6 * 0.1, 0);
    }
    else {
        offset = vec2(7 * 0.1, 0);
    }

    vec2 coord = offset + vec2(mod(vtexCoord.x, 1.0 / NUM) / (1.0 / NUM) * 0.1, vtexCoord.y);
    vec4 C = texture(colorMap, coord);
    if (C.a < 0.5) {
        discard;
    }
    fragColor = vec4(0, 0.5, 1, 1);
}
