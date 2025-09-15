#version 410

in vec4 color;
out vec4 fcolor;

uniform vec4 uniformColor;

void main (void)
{
  fcolor = color * uniformColor;
}
