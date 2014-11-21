#version 330

// Per pixel lighting based on code from Dr. William Schreuder's graphics class
// http://www.prinmath.com/csci5229/F14/programs/index.html

layout(location=0) in vec4 in_vertexPos; // vertex position in object CS
layout(location=1) in vec3 in_Normals; // normals in object CS
layout(location=2) in vec2 in_Texture; 

uniform mat4 in_Projection; // Projection Matrix
uniform mat4 in_View; // View Matrix
uniform mat4 in_Model;	// Model Matrix
uniform vec4 in_LightPosition; // in world CS
uniform vec4 in_LEDColor; // color of the LED, (0,0,0) is off
uniform vec4 projectorPosition; // in world CS
uniform vec2 in_ProjOffsets; // offsets for projected texture calculations

out vec3 View; // vector to eye position
out vec3 Light; // vector from light to vertex
out vec4 Normal; // vertex normal
out float height; // height of vertex for LED lighting
out vec4 ledColor; // color of the LED
out vec4 Proj; // vector from projector to droplet
out vec2 texCoords_0; // droplet texture
out vec2 texCoords_1; // projection texture

void main(){	
	mat4 modelView = in_View * in_Model;

	vec4 P = modelView * in_vertexPos;

	View = -P.xyz;

	Light = (in_View * (in_LightPosition - in_Model * in_vertexPos)).xyz; 
	Proj = in_View * (projectorPosition - in_Model * in_vertexPos);

	height = in_vertexPos.z; // used to determine lit portion of droplet 

	Normal = modelView * vec4(in_Normals,0.0);

	ledColor = in_LEDColor;
	gl_Position = in_Projection * P;

	// textures:
	vec2 worldCoords = (in_Model * in_vertexPos).xy; // where droplet is on the floor
	texCoords_1 = (worldCoords + in_ProjOffsets/2.0)/in_ProjOffsets; // what portion projected of the texture to add to droplet
	texCoords_0 = in_Texture; // droplet texture
}