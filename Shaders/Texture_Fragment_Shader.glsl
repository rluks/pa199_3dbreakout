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
	mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 normal = normalize(normalMatrix * fragNormal);
    
    //calculate the location of this fragment (pixel) in world coordinates
    vec3 fragPosition = vec3(model * vec4(fragVert, 1));
    
    //calculate the vector from this pixels surface to the light source
    vec3 surfaceToLight = lightPosition - fragPosition;

    //calculate the cosine of the angle of incidence
    float brightness = dot(normal, surfaceToLight) / (length(surfaceToLight) * length(normal));
    brightness = 0.5;//clamp(brightness, 0, 1);

    //calculate final color of the pixel, based on:
    // 1. The angle of incidence: brightness
    // 2. The color/intensities of the light: light.intensities
    // 3. The texture and texture coord: texture(tex, fragTexCoord)
    vec4 surfaceColor = texture(tex, fragTexCoord);
    out_color = vec4(brightness * lightColor * surfaceColor.rgb, surfaceColor.a);

	//out_color = color;
	out_color = texture(tex, vec2(1 - fragTexCoord.x, fragTexCoord.y));
}