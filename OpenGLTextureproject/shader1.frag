#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform int TLoaded = 1;

void main()
{    
    if (TLoaded == 1){
    FragColor = texture(texture_diffuse1, TexCoords);
    }
    else{
    FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    }
}