#version 330

in vec2 UV;

out vec4 fragColor;

uniform sampler2D sceneTexture;
uniform sampler2D blurTexture;
uniform float blurPercent;

void main()
{
	vec4 sceneColor = texture2D(sceneTexture,UV);
	vec4 blurColor = texture2D(blurTexture,UV);

	fragColor = sceneColor * blurPercent + blurColor * (1-blurPercent);
}