varying vec4 vertPos;

uniform sampler2D text;
uniform vec2 lightPos;
//uniform bool hasTexture; t‰‰ oli tutoriaali videossa mutta me ei varmaa tarvita t‰t‰. Eli jos renderattava ei k‰yt‰ tekstuuria eli spritea.

void main()
{
	//Ambient light
	vec4 ambient = vec4(0.02, 0.02, 0.02, 1);

	vec2 newLightPos = lightPos;

	//Convert light to view coords
	newLightPos = (gl_ModelViewProjectionMatrix * vec4(newLightPos, 0, 1)).xy;
	
	//Calculate the vector from light to pixel (Make circular)
	vec2 lightToFrag = newLightPos - vertPos.xy;
	lightToFrag.y = lightToFrag.y / 1.7;

	//Length of the vector (distance)
	
	float vecLength = clamp(length(lightToFrag) * 2.5, 0., 1.);

    // lookup the pixel in the texture
    vec4 pixel = texture2D(text, gl_TexCoord[0].xy);

    // multiply it by the color and lighting
	//if(hasTexture == true)
	//{
	gl_FragColor = gl_Color * pixel * (clamp(ambient + vec4(1-vecLength, 1-vecLength, 1-vecLength, 1), 0., 1.));
	//}
	//else
	//{
		//gl_FragColor = gl_Color;
	//}
}