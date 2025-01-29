#version 330 core

in vec4 frontColor;
out vec4 fragColor;
uniform float time;
uniform float SIZE;
in vec2 vtexCoord;

uniform sampler2D colorMap;

void main()
{
    vec2 st = (gl_FragCoord.xy- vec2(0.5))/SIZE;
    float s = st.x;
    float t = st.y;
    float offset = 0.01*sin(10.0*time + 30.0*s);
    fragColor = texture(colorMap, vec2( s + offset , t+ offset) );
}
