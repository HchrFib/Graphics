#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;

out vec4 fragColor;

const vec4 BLUE = vec4(0, 0.6, 1, 1);
const vec4 RED = vec4(1, 0, 0, 1);
const vec4 YELLOW = vec4(1, 1, 0, 1);
const vec4 GREEN = vec4(0, 0.75, 0.3, 1);
const vec4 WHITE = vec4(1);

void main()
{
    vec4 color = GREEN;
    vec2 c1 = vec2(0.3, 0.5);
    vec2 c2 = vec2(0.4, 0.5);
    vec2 u1 = (vtexCoord - c1) * vec2(1, 0.75);
    vec2 u2 = (vtexCoord - c2) * vec2(1, 0.75);
    if (vtexCoord.x < 0.5) {
        if (step(0.22, length(u1)) == 0) {
            color = WHITE;
        }
        if (step(0.2, length(u2)) == 0) {
            color = GREEN;
        }
    } else {
        if (abs(vtexCoord.y - 0.5) < 0.2 && (vtexCoord.x - 0.5) < 0.4 * 0.75) {
            color = WHITE;
        }
    }
    fragColor = color;
}
