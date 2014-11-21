#version 330

in vec3 View;
in vec3 Light;
in vec4 Normal;
in float height;
in vec4 ledColor;

in vec2 texCoords_0;
in vec2 texCoords_1;

uniform sampler2D objectTexture; //Texture on the Droplet
uniform sampler2D projectionTexture; //Image to be projected (treat like a directional light?)

out vec4 fragColor; // rely on linker to automatically link this to FragColor

void main()
{
	// from old file
	vec4 tex_Color = texture2D(objectTexture,texCoords_0);

	vec3 N = normalize(Normal.xyz);
	vec3 L = normalize(Light);
	vec3 R = reflect(-L,N);
	vec3 V = normalize(View);

	float Id = max(dot(L,N) , 0.0);
	float Is = (Id>0.0) ? pow(max(dot(R , V) , 0.0) , 16) : 0.0;

	vec4 emission=vec4(0.0,0.0,0.0,1.0);

	// fade led light from unlit bottom to lit top over 0.1 distance
	if (height>0.58) 
	{
		emission.x=ledColor.x*(height-0.58)/0.1;
		emission.y=ledColor.y*(height-0.58)/0.1;
		emission.z=ledColor.z*(height-0.58)/0.1;
	}

	if (height>0.68)
	{
		emission.x=ledColor.x;
		emission.y=ledColor.y;
		emission.z=ledColor.z;
	}

	fragColor = (emission
				+ vec4(0.4,0.4,0.4,1.0) // ambient lighting
				+ Id * vec4(0.3,0.3,0.3,1.0) // diffuse lighting
				+ Is * vec4(0.2,0.2,0.2,1.0)) // specular lighting
				* (tex_Color);
}