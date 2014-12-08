#version 330
//http://www.gamerendering.com/2008/10/11/gaussian-blur-filter-shader/
in vec2 UV;

out vec3 fragColor;

uniform sampler2D myTexture;
uniform int blurDirection;
uniform float blurRadius;

void main()
{

	float blurSize = 1.0/blurRadius;
	vec4 sum = vec4(0.0);

	if (blurDirection==0)
	{
		sum = texture2D(myTexture, vec2(UV.x - 4.0*blurSize, UV.y)) * 0.05;
		sum += texture2D(myTexture, vec2(UV.x - 3.0*blurSize, UV.y)) * 0.09;
		sum += texture2D(myTexture, vec2(UV.x - 2.0*blurSize, UV.y)) * 0.12;
		sum += texture2D(myTexture, vec2(UV.x - blurSize, UV.y)) * 0.15;
		sum += texture2D(myTexture, vec2(UV.x, UV.y)) * 0.16;
		sum += texture2D(myTexture, vec2(UV.x + blurSize, UV.y)) * 0.15;
		sum += texture2D(myTexture, vec2(UV.x + 2.0*blurSize, UV.y)) * 0.12;
		sum += texture2D(myTexture, vec2(UV.x + 3.0*blurSize, UV.y)) * 0.09;
		sum += texture2D(myTexture, vec2(UV.x + 4.0*blurSize, UV.y)) * 0.05;
 
		fragColor = sum.rgb;
	}
	else
	{
		sum += texture2D(myTexture, vec2(UV.x, UV.y - 4.0*blurSize)) * 0.05;
		sum += texture2D(myTexture, vec2(UV.x, UV.y - 3.0*blurSize)) * 0.09;
		sum += texture2D(myTexture, vec2(UV.x, UV.y - 2.0*blurSize)) * 0.12;
		sum += texture2D(myTexture, vec2(UV.x, UV.y - blurSize)) * 0.15;
		sum += texture2D(myTexture, vec2(UV.x, UV.y)) * 0.16;
		sum += texture2D(myTexture, vec2(UV.x, UV.y + blurSize)) * 0.15;
		sum += texture2D(myTexture, vec2(UV.x, UV.y + 2.0*blurSize)) * 0.12;
		sum += texture2D(myTexture, vec2(UV.x, UV.y + 3.0*blurSize)) * 0.09;
		sum += texture2D(myTexture, vec2(UV.x, UV.y + 4.0*blurSize)) * 0.05;
 
		fragColor = sum.rgb;
	}

}