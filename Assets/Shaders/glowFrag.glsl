#version 330

// Per pixel lighting based on code from Dr. William Schreuder's graphics class
// http://www.prinmath.com/csci5229/F14/programs/index.html

in vec3 View;  // view matrix
in vec3 Light; // direction to the light source
in vec4 Normal; // vertex normals
in float height; // vertex height for LED 
in vec4 ledColor;
in vec4 Proj; // direction to the projector
in vec2 texCoords_0; // droplet texture coords
in vec2 texCoords_1; // projection texture coords

uniform sampler2D objectTexture; //Texture on the Droplet
uniform sampler2D projectionTexture; //Image to be projected (treat like a directional light?)
uniform sampler2D activeTexture;
uniform int is_projecting;
uniform int is_activeTexture;

out vec4 fragColor; // output color

void main()
{
	vec4 tex_Color = texture2D(objectTexture,texCoords_0);
	vec4 proj_Color = vec4(0.0);
	float Ip = 0.0;
	float percentColored = 0.6;

	vec3 N = normalize(Normal.xyz);
	vec3 L = normalize(Light);
	vec3 R = reflect(-L,N);
	vec3 V = normalize(View);

	if (is_projecting==1) 
	{
		Ip = max(dot(N,normalize(Proj.xyz)) , 0.0);
		proj_Color=texture2D(projectionTexture,texCoords_1);
	} 

	if (is_activeTexture==1)
	{
		Ip = max(dot(N,normalize(Proj.xyz)) , 0.0);
		proj_Color=texture2D(activeTexture,texCoords_1);
	}

	// intensity of diffuse and specular light, 
	// 8 = max shininess
	float Id = max(dot(L,N) , 0.0);
	float Is = (Id>0.0) ? pow(max(dot(R , V) , 0.0) , 8) : 0.0;

	// fade led light from unlit bottom to lit top over 0.3 distance
	vec4 emission=vec4(0.0,0.0,0.0,1.0);
	if (height>0.48) 
	{
		emission.x=ledColor.x*(height-0.48)/0.3;
		emission.y=ledColor.y*(height-0.48)/0.3;
		emission.z=ledColor.z*(height-0.48)/0.3;
	}
	if (height>0.78)
	{
		emission.x=ledColor.x;
		emission.y=ledColor.y;
		emission.z=ledColor.z;
	}

	if (height>0.86)
	{
		emission.x=0.0; //ledColor.x*(0.92-height)/0.07;
		emission.y=0.0; //ledColor.y*(0.92-height)/0.07;
		emission.z=0.0; //ledColor.z*(0.92-height)/0.07;
	}

	// TODO: get these parameters from the light source object
	fragColor = emission;
}