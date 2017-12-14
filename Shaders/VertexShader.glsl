attribute vec4 a_Position;	        // in: Posición de cada vértice
attribute vec3 a_Normal;	        // in: Normal de cada vértice
attribute vec2 a_UV; // in: Coordenadas UV de mapeado de textura

uniform mat4 u_ProjectionMatrix; 	// in: Matriz Projection
uniform mat4 u_MVMatrix;	        // in: Matriz ModelView
uniform mat4 u_VMatrix;             // in: Matriz View (cámara)
//uniform vec4 u_Color;		        // in: Color del objeto

uniform int   u_Luz0;                // in: Indica si la luz 0 está encedida
uniform mat4  u_Luz0Position;        // in: Indica la posicion de la luz 0
uniform float u_Luz0Intensidad;      // in: Indica la intensidad de la luz 0

uniform int   u_Luz1;
uniform mat4  u_Luz1Position;
uniform float u_Luz1Intensidad;

uniform int   u_Luz2;
uniform mat4  u_Luz2Position;
uniform float u_Luz2Intensidad;

varying   vec4 v_Color;		        // out: Color al fragment shader
varying   vec2 v_uv;

void main()
{
    vec4 LightPos; // Posición de la luz [fija]
    vec3 P = vec3(u_MVMatrix * a_Position);	            // Posición del vértice
    vec3 N;     // Normal del vértice

    float d;    // distancia de la luz
    vec3  L;    // Vector Luz

    float ambient = 0.15;                               // (15% de int. ambiente)
    float diffuse = 0.0;
    float color = 0.0;
    float Ks = 0.7;
    float n = 20;
    float specular1 = 0.0;

    vec4 posCamara = vec4(u_VMatrix[0][0], u_VMatrix[0][1], u_VMatrix[0][2], 1.0);
    vec3 V = normalize(vec3(u_VMatrix * posCamara * vec4(0.0, 0.0, 0.0, 1.0) - vec4(P, 1.0)));

    if (u_Luz0>0)                                       // Si la luz 0 está encendida se calcula la intesidad difusa de L
    {

        LightPos = u_VMatrix*vec4( -u_Luz0Position[0][0], -u_Luz0Position[0][2], -u_Luz0Position[0][1],1);
	    N = vec3(u_MVMatrix * vec4(a_Normal, 0.0));
	    d = length(LightPos.xyz - P);
	    L = normalize(LightPos.xyz - P);

        diffuse = max(dot(N, L), 0.0);		            // Cálculo de la int. difusa
        float attenuation = 1.0/(0.25+(0.01*d)+(0.003*d*d));         // Cálculo de la atenuación
        diffuse = diffuse*attenuation*u_Luz0Intensidad*100;
        specular1 = 2* attenuation * Ks * pow(max(0.0, dot(reflect(-L, N), V)), n);
        specular1 = specular1 * u_Luz0Intensidad * 100.0;
    }

    color = color + (ambient + diffuse) + specular1;
    specular1 = 0.0;

    if (u_Luz1>0) {                                     // Si la luz 0 está encendida se calcula la intesidad difusa de L

        LightPos = u_VMatrix*vec4( -u_Luz1Position[0][0], -u_Luz1Position[0][2], -u_Luz1Position[0][1],1);
	    N = vec3(u_MVMatrix * vec4(a_Normal, 0.0));
	    d = length(LightPos.xyz - P);
	    L = normalize(LightPos.xyz - P);

        diffuse = max(dot(N, L), 0.0);		            // Cálculo de la int. difusa
        float attenuation = 1.0/(0.25+(0.01*d)+(0.003*d*d));         // Cálculo de la atenuación
        diffuse = diffuse*attenuation*u_Luz1Intensidad*100;
        specular1 = 2* attenuation * Ks * pow(max(0.0, dot(reflect(-L, N), V)), n);
        specular1 = specular1 * u_Luz1Intensidad*100;
	}

    color = color + (ambient + diffuse) + specular1;
    specular1 = 0.0;

	if (u_Luz2>0) {                                     // Si la luz 0 está encendida se calcula la intesidad difusa de L

        LightPos = u_VMatrix*vec4( -u_Luz2Position[0][0], -u_Luz2Position[0][2], -u_Luz2Position[0][1],1);
	    N = vec3(u_MVMatrix * vec4(a_Normal, 0.0));
	    d = length(LightPos.xyz - P);
	    L = normalize(LightPos.xyz - P);

        diffuse = max(dot(N, L), 0.0);		            // Cálculo de la int. difusa
        float attenuation = 1.0/(0.25+(0.01*d)+(0.003*d*d));         // Cálculo de la atenuación
        diffuse = diffuse*attenuation*u_Luz2Intensidad*100;
        specular1 = 2* attenuation * Ks * pow(max(0.0, dot(reflect(-L, N), V)), n);
        specular1 = specular1 * u_Luz2Intensidad*100;
	}

    v_uv = a_UV;
    v_Color =  vec4(ambient + diffuse, ambient + diffuse, ambient + diffuse, ambient + diffuse);
    gl_Position = u_ProjectionMatrix * vec4(P, 1.0);
}
