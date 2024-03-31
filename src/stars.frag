uniform vec2 u_resolution;

float Hash21(vec2 p) {
    p = fract(p * vec2(123.34, 456.21));
    p += dot(p, p + 45.32);
    return fract(p.x * p.y);
}

void main()
{
    // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = (gl_FragCoord-.5 * u_resolution.xy)/u_resolution.y;
    uv *= 10.;
    // Time varying pixel color
    vec3 col = vec3(0);

    vec2 gv = fract(uv) - .5;
    vec2 id = floor(uv);

    for(int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
        vec2 offs = vec2(x, y);
            float rand = Hash21(id + offs);
            float d = length(gv - offs - vec2(rand - .5, fract(rand * 10.) - .5));
            float m = .05/d;
            m *= smoothstep(.5, .2, d);
            col += m;
}}
    //if (gv.x > .48 || gv.y > .48) col.r = 1.; //Add red outlines to each box
    
    gl_FragColor = vec4(col,1.0);
}