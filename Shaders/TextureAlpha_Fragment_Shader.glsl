#version 330 core

in vec4 color;
in vec2 fragTexCoord; //this is the texture coord
in vec3 fragNormal;
in vec3 fragVert;

uniform sampler2D tex; //this is the texture
uniform mat4 model;

uniform vec3 lightColor;
uniform vec3 lightPosition;


layout(location = 0) out vec4 out_color;
 
void main(void)
{
	float materialShininess = 80.0;
	vec3 materialSpecularColor = vec3(1.0f, 1.0f, 1.0f);
	float lightAttenuation = 0.2;
	float lightAmbientCoefficient = 0.005;
	vec3 cameraPosition = lightPosition;

	vec3 normal = normalize(transpose(inverse(mat3(model))) * fragNormal);
    vec3 surfacePos = vec3(model * vec4(vec3(1-fragVert.x-1, fragVert.yz), 1));
    vec4 surfaceColor = texture(tex, fragTexCoord);
    vec3 surfaceToLight = normalize(lightPosition - surfacePos);
    vec3 surfaceToCamera = normalize(cameraPosition - surfacePos);
    
    //ambient
    vec3 ambient = lightAmbientCoefficient * surfaceColor.rgb * lightColor;

    //diffuse
    float diffuseCoefficient = max(0.0, dot(normal, surfaceToLight));
    vec3 diffuse = diffuseCoefficient * surfaceColor.rgb * lightColor;
    
    //specular
    float specularCoefficient = 0.0;
    if(diffuseCoefficient > 0.0)
        specularCoefficient = pow(max(0.0, dot(surfaceToCamera, reflect(-surfaceToLight, normal))), materialShininess);
    vec3 specular = specularCoefficient * materialSpecularColor * lightColor;
    
    //attenuation
    float distanceToLight = length(lightPosition - surfacePos);
    float attenuation = 1.0 / (1.0 + lightAttenuation * pow(distanceToLight, 2));

    //linear color (color before gamma correction)
    vec3 linearColor = ambient + attenuation*(diffuse + specular);
    
    //final color (after gamma correction)
    vec3 gamma = vec3(1.0/2.2);
    out_color = vec4(pow(linearColor, gamma), surfaceColor.a);
	out_color.a = 0.5;
		
		//out_color = texture(tex, vec2(1 - fragTexCoord.x, fragTexCoord.y));
}