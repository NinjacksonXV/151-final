#version 120

uniform vec2 u_resolution;
uniform vec2 position;

// Essentially generates a random value between 0 and 1 (not THAT random, but pretty darn close)
float Hash21(vec2 p) {
    p = fract(p * vec2(123.34, 456.21));
    p += dot(p, p + 45.32);
    return fract(p.x * p.y);
} 

void main()
{
    vec2 uv = (gl_FragCoord-.5 * u_resolution.xy)/u_resolution.y; // Normalized pixel coordinates (from 0 to 1)
    uv *= 10.; 
    uv += position * 0.001; // Scroll the UV with player position 
    vec3 col = vec3(0); // Black

    vec2 gv = fract(uv) - .5;
    vec2 id = floor(uv); // I'm not sure how, but this splits the UV into several smaller UVs


    //Still working through this one. I think this nested for loop works through each pixel of the given sub-UV/GV?
    for(int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
        vec2 offs = vec2(x, y);
            float rand = Hash21(id + offs);
            float d = length(gv - offs - vec2(rand - .5, fract(rand * 10.) - .5));
            float m = .02/d;
            m *= smoothstep(.3, .01, d); //This is what allows stars to render inside other GVs, I think.
            float size = fract(rand * 345.22);
            col += (m * size);
}}
    //if (gv.x > .48 || gv.y > .48) col.r = 1.; //Add red outlines to each box
    gl_FragColor = vec4(col,1.0);
}