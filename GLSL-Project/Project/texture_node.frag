#version 120

uniform sampler2D texture1;
uniform sampler2D texture2;

varying vec2 f_texcoord;
 
void main(void) {

	vec3 inColor = texture2D(texture1, f_texcoord).xyz;
	vec3 outColor;
	outColor.r = texture2D(texture2, vec2(inColor.r, 1)).r;
	outColor.g = texture2D(texture2, vec2(inColor.g, 1)).g;
	outColor.b = texture2D(texture2, vec2(inColor.b, 1)).b;
    gl_FragColor = vec4(outColor, 1.0);
}

