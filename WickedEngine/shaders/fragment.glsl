#version 410

uniform vec4 uniformColor;
uniform sampler2D decal;

in data 
{
	vec2 texcoord;
} f;
out vec4 fcolor;


void main (void)
{
  fcolor = uniformColor * texture(decal, f.texcoord);
}
