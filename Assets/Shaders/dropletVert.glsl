#version 330

// Vertex shading: http://www.gamedev.net/page/resources/_/technical/opengl/the-basics-of-glsl-40-shaders-r2861 

layout(location=0) in vec4 in_vertexPos;
layout(location=1) in vec3 in_Normals;
layout(location=2) in vec2 in_Texture; 

uniform mat4 in_Projection;
uniform mat4 in_View;
uniform mat4 in_Model;	
uniform vec4 in_LightPosition;
uniform vec4 in_LEDColor;
uniform vec2 in_ProjOffsets;

out vec3 View;
out vec3 Light;
out vec4 Normal;
out float height;
out vec4 ledColor;

out vec2 texCoords_0;
out vec2 texCoords_1;

void main(){	
	mat4 modelView = in_View * in_Model;

	vec4 P = modelView * in_vertexPos;

	View = -P.xyz;

	Light = in_LightPosition.xyz - P.xyz; 

	height = in_vertexPos.z; 

	Normal = modelView * vec4(in_Normals,0.0);

	ledColor = in_LEDColor;

	gl_Position = in_Projection * P;

	// texture data from old file:
	vec2 worldCoords = (in_Model * in_vertexPos).xy;
	texCoords_1 = (worldCoords + in_ProjOffsets/2.0)/in_ProjOffsets;
	texCoords_0 = in_Texture;
}