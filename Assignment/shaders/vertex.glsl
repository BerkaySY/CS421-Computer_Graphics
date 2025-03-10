#version 330 core                      
layout (location = 0) in vec3 inPosition;  
layout (location = 1) in vec2 inTexCoord;  

uniform mat4 uWorldTransform;
out vec2 texCoord;

void main()                                
{             
   gl_Position = uWorldTransform*vec4(inPosition, 2.0);    
   texCoord = inTexCoord;
}                                          