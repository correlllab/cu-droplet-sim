#version 330

// Vertex shading: http://www.gamedev.net/page/resources/_/technical/opengl/the-basics-of-glsl-40-shaders-r2861 

layout(location=0) in vec4 in_vertexPos;
layout(location=1) in vec3 in_Normals;

uniform mat4 in_Projection;
uniform mat4 in_View;
uniform mat4 in_Model;	
uniform vec4 in_LightPosition;
uniform vec4 in_LEDColor;

out vec3 View;
out vec3 Light;
out vec4 Normal;
out float height;
out vec4 ledColor;

void main(){	
	mat4 modelView = in_View * in_Model;

	vec4 P = modelView * in_vertexPos;

	View = -P.xyz;

	vec3 lightPosition = (in_Projection * (modelView * in_LightPosition)).xyz;
	Light = in_LightPosition.xyz - P.xyz; 

	height = in_vertexPos.z; 

	Normal = modelView * vec4(in_Normals,0.0);

	ledColor = in_LEDColor;

	gl_Position = in_Projection * P;
}