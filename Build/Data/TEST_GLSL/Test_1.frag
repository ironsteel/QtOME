// Red Shader
vec4 gl_FragColor;
varying float Time;

void main()
{
	//T = abs(T);
	gl_FragColor = vec4(abs(Time), 0.0, 0.0, 0.0);
}