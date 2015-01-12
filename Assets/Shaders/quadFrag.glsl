#version 330

in vec2 UV;

out vec3 fragColor;

uniform sampler2D myTexture;

void main()
{
	fragColor = texture2D(myTexture, UV).rgb;
}