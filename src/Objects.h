
/***************************************************************************************

    ForestDriving (main.cpp)

    Computer Graphics project.
    OpenGL with Shaders
  --------------------------------------------------------------------------------------

    ForestDriving (CC) 2017

****************************************************************************************/

//---------------------------------------------------------------------------
#ifndef ObjectsH
#define ObjectsH
//---------------------------------------------------------------------------

#define GLEW_STATIC

#include "Shader.h"
#include "Program.h"

#include <GL/glui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Internal ids for objects
#define ROAD_ID          10
#define CAR_ID	        100
#define PLATFORM_ID     105
#define FLOOR_ID        110
#define RIVER_ID        115
#define MOUNTAINS_ID    120
#define TREES_ID        125
#define TUNNEL_ID       130
#define BOLLARDS_ID     135


// TGui callbacks IDs
#define LIGHT0_ENABLED_ID    200
#define LIGHT1_ENABLED_ID    201
#define LIGHT0_POSITION_ID   210
#define LIGHT1_POSITION_ID   211
#define LIGHT0_INTENSITY_ID  220
#define LIGHT1_INTENSITY_ID  221


#define ENABLE_ID            300
#define DISABLE_ID           301

#define RESET_ID             400

#define SEL_ID               500

// 3DS format data (x, y, z, A, B, C, u, v)
#define POSITION_COMPONENT_COUNT    3
#define NORMAL_COMPONENT_COUNT      3
#define UV_COMPONENT_COUNT          2
// stride operation (3+3+2)*4 = 8*4 = 32
#define STRIDE                      32

// attributes name
#define A_POSITION  "a_Position"
#define A_NORMAL    "a_Normal"

// uniforms name
#define U_PROJECTIONMATRIX      "u_ProjectionMatrix"
#define U_MVMATRIX              "u_MVMatrix"
#define U_VMATRIX               "u_VMatrix"
#define U_COLOR                 "u_Color"
#define U_LUZ0                  "u_Luz0"

//************************************************************** Clase TPrimtiva

class TPrimitive
{
public: // Class attributes
		int ID;				    // DisplayLists
		int type;               // Object type
		float tx,ty,tz; 	    // Object position
		float sx,sy,sz; 	    // Object scale
		float rx,ry,rz;     	// Object rotation
		float rr;               // Wheel rotation
		float colors[2][4];    // RGB Color and Alfa channel

		float   *model0;        // model to render
		int     num_vertex0;   // vertex number

        float   *model1;        // second model to render
		int     num_vertex1;   // vertex number

public: // Methods
 		TPrimitive(int DL, int type);
        void __fastcall Render(int selection, bool reflex=false);
};

//************************************************************** TScene Class

class TScene
{
public: // Class attributes
		int   	selection;   	// Object selected, 0=none
        int		num_objects;    // Objects number
        int     num_cars;       // Car number

        //Up to 10 cars in scene
        TPrimitive  *cars[10];
        //Up to 100 objects in scene
        TPrimitive  *objects[100];

        // Attributes & uniforms Handles
        int aPositionLocation;
        int aNormalLocation;
        int uProjectionMatrixLocation;
        int uMVMatrixLocation;
		int uVMatrixLocation;
		int uColorLocation;
		int uLuz0Location;

		glm::mat4 projectionMatrix; // Stores Projection matrix
        glm::mat4 viewMatrix;       // Stores View matrix (camera)

		Program  *shaderProgram;    // Stores OpenGL program (ShaderProgram)

        // Lights and materials vectors
        GLfloat light0_ambient[4];
        GLfloat light0_diffuse[4];
        GLfloat light0_specular[4];
        GLfloat light0_position[4];

        GLfloat light1_ambient[4];
        GLfloat light1_diffuse[4];
        GLfloat light1_specular[4];
        GLfloat light1_position[4];

        GLfloat mat_ambient[4];
        GLfloat mat_diffuse[4];
        GLfloat mat_specular[4];
        GLfloat mat_shininess[1];

        float   xy_aspect;
        int     last_x, last_y;

        // live variables used by GLUI in TGui
        int     wireframe;
        int     z_buffer;
        int     culling;

        int     show_car;
        int     show_wheels;
        int     show_road;

        GLfloat view_position[3];
        GLfloat view_rotate[16];
        float   scale;

public: // Methods
		TScene();

        void __fastcall InitGL();
		void __fastcall Render();
		void __fastcall RenderCars(bool reflex=false);
		void __fastcall RenderObjects(bool reflex=false);

		void __fastcall AddCar(TPrimitive *car);
		void __fastcall AddObject(TPrimitive *object);

		TPrimitive __fastcall *GetCar(int id);

		void __fastcall Pick3D(int mouse_x, int mouse_y);


};

//************************************************************** Class TGui

class TGui
{
public:
        int             window_id;

        // live variables used by GLUI
        int             sel;
        int             enable_panel2;
        int             light0_enabled;
        int             light1_enabled;
        float           light0_intensity;
        float           light1_intensity;
        float           light0_position[4];
        float           light1_position[4];

        GLUI            *glui, *glui2;
        GLUI_Spinner    *light0_spinner;
        GLUI_Spinner    *light1_spinner;
        GLUI_RadioGroup *radio;
        GLUI_Panel      *obj_panel;
        GLUI_Rotation   *view_rot;

public:
        TGui();
        void __fastcall Init(int main_window);
        void __fastcall ControlCallback(int control);
        void __fastcall Idle( void );
        void __fastcall Reshape( int x, int y  );
        void __fastcall Motion( int x, int y  );
        void __fastcall Mouse(int button, int button_state, int x, int y );
};

//************************************************************** Variables de clase

extern TScene  scene;
extern TGui     gui;

#endif
