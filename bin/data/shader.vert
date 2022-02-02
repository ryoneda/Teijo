#version 150

varying vec4 position;
void main(void)
{
  position = gl_ModelViewMatrix * gl_Vertex;

  gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
  gl_Position = ftransform();
}
