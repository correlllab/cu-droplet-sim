#version 330

//Common Vertex Shader
//Simple vertex shader common to non-Droplet objects. Applies textures and sets up lighting.

// Input vertex data, different for all executions of this shader.
layout(location=0) in vec4 in_vertexPos;
layout(location=1) in vec3 in_Normals; //Lighting normals on objs
layout(location=2) in vec2 in_Texture; 

//Uniforms for model-view matrix calculation
uniform mat4 in_Projection;
uniform mat4 in_View;
uniform mat4 in_Model;	
uniform vec4 in_Color;
uniform vec3 in_lightDir;
uniform vec2 in_ProjOffsets;

//Info to be passed into fragment shader
out vec4 model_Color;
out vec3 transformedLightingDirection;
out vec3 transformedProjDirection;
out vec3 normal;
out vec2 texCoords_0;
out vec2 texCoords_1;
out vec3 directionalColor;
out vec3 ambientColor;

void main(){

	ambientColor = vec3(0.4);
	directionalColor = vec3(0.4);

	mat4 modelView = in_View * in_Model;

	normal =  (modelView * vec4(in_Normals, 0.0)).xyz;

	transformedLightingDirection = vec3(in_View * vec4(in_lightDir,0.0));
	transformedProjDirection = vec3(in_View * vec4(0,0,10,0));
	//Lighting to be passed into fragment shader.

	texCoords_0 = in_Texture;

	vec2 worldCoords = (in_Model * in_vertexPos).xy;
	texCoords_1 = (worldCoords + in_ProjOffsets/2.0)/in_ProjOffsets;
	gl_Position = in_Projection * (modelView * in_vertexPos);

	model_Color = in_Color;
	
}