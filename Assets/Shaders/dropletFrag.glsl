#version 330

in vec3 View;
in vec3 Light;
in vec4 Normal;
in float height;
in vec4 ledColor;

out vec4 fragColor; // rely on linker to automatically link this to FragColor



void main()
{
	vec3 N = normalize(Normal.xyz);
	vec3 L = normalize(Light);
	vec3 R = reflect(-L,N);
	vec3 V = normalize(View);

	float Id = max(dot(L,N) , 0.0);
	float Is = (Id>0.0) ? pow(max(dot(R , V) , 0.0) , 16) : 0.0;

	vec4 emission=vec4(0.5,0.5,0.5,1.0);

	// fade led light from unlit bottom to lit top over 0.1 distance
	if (height>0.68)
	{
		emission.x=ledColor.x;
		emission.y=ledColor.y;
		emission.z=ledColor.z;
	}

	fragColor = emission
				+ vec4(0.3,0.3,0.3,1.0) // ambient lighting
				+ Id * vec4(0.2,0.2,0.2,1.0) // diffuse lighting
				+ Is * vec4(0.1,0.1,0.1,1.0); // specular lighting

}