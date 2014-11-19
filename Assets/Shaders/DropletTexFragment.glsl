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

//Lighting


void main()
{
	vec4 tex_Color = texture2D(objectTexture,texCoords_0);

	vec3 transformedNormal = normalize(normal);
	float directionalLightWeighting = max(dot(transformedNormal, normalize(transformedLightingDirection)), 0.0);
	vec3 vLightWeighting = ambientColor + directionalColor*directionalLightWeighting;
	vec3 light = 1 - (1 - vLightWeighting * (1-aux_Color.a)) * (1 - aux_Color.xyz*tex_Color.a);

	//out_Color = vec4(tex_Color.xyz * light,1.0);

	vec4 emission = vec4(0.0, 0.0, 0.0, 1.0);

	if (height>0.58) {
		emission.x=aux_Color.x;
		emission.y=aux_Color.y;
		emission.z=aux_Color.z;
	}

	out_Color = (emission +
				 vec4(0.3, 0.3, 0.3, 1.0) +
				 directionalLightWeighting * vec4(0.5, 0.5, 0.5, 1.0)
				) * tex_Color;
}