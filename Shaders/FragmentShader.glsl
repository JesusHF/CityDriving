
precision mediump float;	// Precisión media

varying vec4 v_Color;		// in: color del vertex shader
varying vec2 v_uv;		// in: color del vertex shader
uniform sampler2D u_TextureUnit; // in: Unidad de Textura

void main()
{
    		gl_FragColor = v_Color * texture2D(u_TextureUnit, v_uv);
}
