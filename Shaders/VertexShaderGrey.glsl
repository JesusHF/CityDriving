
attribute vec4 a_Position;	        // in: Posición de cada vértice

uniform mat4 u_ProjectionMatrix; 	// in: Matriz Projection
uniform mat4 u_MVMatrix;	        // in: Matriz ModelView
uniform int u_Color;		        // in: Color del objeto

varying vec4 v_Color;		        // out: Color al fragment shader

void main()
{
    vec3 P = vec3(u_MVMatrix * a_Position);	            // Posición del vértice

	v_Color = vec4(u_Color/255.0, u_Color/255.0, u_Color/255.0, u_Color/255.0);
	gl_Position = u_ProjectionMatrix * vec4(P, 1.0);
}
