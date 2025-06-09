#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in vec3 Normal;
in vec3 crntPos;

uniform sampler2D tex0;
uniform vec3 lightPos;
uniform vec3 camPos;
uniform vec4 lightColor;

void main()
{
    float ambient = 0.35f;
    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(lightPos - crntPos);
    float diffuse = max(dot(normal, lightDirection), 0.0f);
    
    float specularLight = 0.25f;
    vec3 viewDirection = normalize(camPos - crntPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
    float specular = specAmount * specularLight;
    
    vec4 textureColor = texture(tex0, texCoord);
    vec3 lighting = (ambient + diffuse + specular) * lightColor.rgb;
    FragColor = vec4(textureColor.rgb * lighting, textureColor.a);
}