varying vec4 vertPos;

uniform sampler2D text;
uniform vec2 lightPos;
uniform float time;

void main()
{
	//Ambient valo
	vec4 ambient = vec4(0.07, 0.07, 0.02, 1);

	vec2 newLightPos = lightPos;

	newLightPos = (gl_ModelViewProjectionMatrix * vec4(newLightPos, 0, 1)).xy;
	
	vec2 lightToFrag = newLightPos - vertPos.xy;
	lightToFrag.y = lightToFrag.y / 1.7;

	//Length of the vector (distance)
	float vecLength = clamp(length(lightToFrag) * 2.8 + (52 * sin(0.36 * time)), 0.2, 0.96);

    vec4 pixel = texture2D(text, gl_TexCoord[0].xy);

	gl_FragColor = gl_Color * pixel * (clamp(ambient + vec4(1-vecLength, 1-vecLength, 1-vecLength, 1), 0., 1.));
}