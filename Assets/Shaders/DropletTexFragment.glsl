#version 330
//Texture Fragment Shader for Droplet (no projector)
//Applies per-vertex lighting to textured Droplet

uniform sampler2D objectTexture;

//To fragment shader
out vec4 out_Color;

in vec4 aux_Color;
in vec3 transformedLightingDirection;
in vec3 normal;
in vec2 texCoords_0;
in vec3 directionalColor;
in vec3 ambientColor;
in float height;
in vec4 View;

//Lighting


void main()
{
	vec4 tex_Color = texture2D(objectTexture,texCoords_0);

	vec3 transformedNormal = normalize(normal);
	float directionalLightWeighting = max(dot(transformedNormal, normalize(transformedLightingDirection)), 0.0);
	vec3 vLightWeighting = ambientColor + directionalColor*directionalLightWeighting;
	vec3 light = 1 - (1 - vLightWeighting * (1-aux_Color.a)) * (1 - aux_Color.xyz*tex_Color.a);

	//out_Color = vec4(tex_Color.xyz * light,1.0);
	vec3 R = reflect(-normalize(transformedLightingDirection),transformedNormal);
	vec3 V = normalize(View.xyz);
	float Is = (directionalLightWeighting>0.0) ? pow(max(dot(R,V),0.0) , 8) : 0.0;


	vec4 emission = vec4(0.0, 0.0, 0.0, 1.0);
	if (height>0.58) {
		emission.x = (height - 0.58) / 0.08 * aux_Color.x;
		emission.y = (height - 0.58) / 0.08 * aux_Color.y;
		emission.z = (height - 0.58) / 0.08 * aux_Color.z;
	}

	if (height>0.66) {
		emission.x=aux_Color.x;
		emission.y=aux_Color.y;
		emission.z=aux_Color.z;
	}
	float ambient = 0.5;
	float diffuse = 0.12;
	float specular = 0.5;

	out_Color = (
				   emission 
				 + vec4(ambient, ambient, ambient, 1.0) 
				 + directionalLightWeighting * vec4(diffuse, diffuse, diffuse, 1.0) 
				 //+ Is * vec4(specular, specular, specular, 1.0)
				 ) * vec4(tex_Color.xyz,1.0);

}