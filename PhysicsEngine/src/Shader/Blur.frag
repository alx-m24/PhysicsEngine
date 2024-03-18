// Fragment shader for Gaussian blur
#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D u_texture; // The input texture
uniform vec2 u_resolution; // The resolution of the texture
uniform vec2 u_direction; // The direction of the blur (horizontal or vertical)
uniform float strength;

// The number of samples to take along the blur direction
const int NUM_SAMPLES = 15;

void main() {
    vec2 texCoord = gl_FragCoord.xy / u_resolution;
    vec4 color = vec4(0.0);
    float total = 0.0;

    // The offsets for the blur samples
    float offset[NUM_SAMPLES] = float[](0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0);
    // The weights for each sample based on the Gaussian distribution
    float weight[NUM_SAMPLES] = float[](0.233, 0.213, 0.192, 0.172, 0.152, 0.132, 0.112, 0.092, 0.072, 0.052, 0.032, 0.022, 0.012, 0.002, 0.001);

    // Calculate the blurred color by combining the samples
    for (int i = 0; i < NUM_SAMPLES; ++i) {
        vec2 sampleOffset = u_direction * (offset[i] + (i * strength)) / u_resolution;
        color += texture2D(u_texture, texCoord + sampleOffset) * weight[i];
        total += weight[i];
    }
    
    gl_FragColor = color / total;
}
