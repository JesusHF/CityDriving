
/****************************************************************************************************

    ForestDriving (main.cpp)

    Computer Graphics project.
    OpenGL with Shaders
  ------------------------------------------------------------------------------------------

    ForestDriving (CC) 2017

    NOTE:   In order of this application to compile, you will need the next project structure

            glut32.dll  -> C:\Windows\system

            Windows 32 bits:
            glew32s.lib -> C:\Program Files\CodeBlocks\MinGW\lib
            glew32.lib  -> C:\Program Files\CodeBlocks\MinGW\lib
            libglui32.a -> C:\Program Files\CodeBlocks\MinGW\lib
            glut32.lib  -> C:\Program Files\CodeBlocks\MinGW\lib

            glui.h      -> C:\Program Files\CodeBlocks\MinGW\include\GL
            glut.h      -> C:\Program Files\CodeBlocks\MinGW\include\GL
            glew.h      -> C:\Program Files\CodeBlocks\MinGW\include\GL

            glm         -> C:\Program Files\CodeBlocks\MinGW\include

            Windows 64 bits:
            glew32s.lib -> C:\Program Files (x86)\CodeBlocks\MinGW\lib
            glew32.lib  -> C:\Program Files (x86)\CodeBlocks\MinGW\lib
            libglui32.a -> C:\Program Files (x86)\CodeBlocks\MinGW\lib
            glut32.lib  -> C:\Program Files (x86)\CodeBlocks\MinGW\lib

            glui.h      -> C:\Program Files (x86)\CodeBlocks\MinGW\include\GL
            glut.h      -> C:\Program Files (x86)\CodeBlocks\MinGW\include\GL
            glew.h      -> C:\Program Files (x86)\CodeBlocks\MinGW\include\GL

            glm         -> C:\Program Files (x86)\CodeBlocks\MinGW\include


****************************************************************************************************/

#include "Objects.h"
#include <GL\glui.h>

/**************************************** myGlutKeyboard() **********/

void Keyboard(unsigned char Key, int x, int y)
{
    switch(Key)
    {
        case 27:
        case 'q':
            exit(0);
            break;
    }

    glutPostRedisplay();
}

/**************************************** mySpecialKey() *************/

static void SpecialKey(int key, int x, int y)
{
    TPrimitive *car = scene.GetCar(scene.selection);

    switch (key)
    {
        case GLUT_KEY_UP:   // Car goes straight
            car->rr+=8;
            car->tz += 0.05;
            break;
        case GLUT_KEY_DOWN:   // Car goes back
            car->rr-=8;
            car->tz -= 0.05;
            break;
    }

    glutPostRedisplay();
}

/***************************************** myGlutMenu() ***********/

void Menu( int value )
{
  Keyboard( value, 0, 0 );
}

void Mouse(int button, int button_state, int x, int y )
{
    gui.Mouse(button, button_state, x, y);
}

void Render()
{
    scene.Render();
}

void Idle()
{
    gui.Idle();
}

void Reshape(int x, int y){
    gui.Reshape(x, y);
}

void Motion(int x, int y){
    gui.Motion(x, y);
}

/**************************************** main() ********************/

int main(int argc, char* argv[])
{
    // Initialize GLUT and create main window
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL | GLUT_MULTISAMPLE );
    glutInitWindowPosition( 50, 50 );
    glutInitWindowSize( 1300, 600 );

    int main_window = glutCreateWindow( "Forest Driving (2017)jesushf" );

    // Initialize OpenGL values for this Application
    scene.InitGL();
    gui.Init(main_window);

    glutDisplayFunc( Render );
    GLUI_Master.set_glutReshapeFunc( Reshape );
    GLUI_Master.set_glutKeyboardFunc( Keyboard );
    GLUI_Master.set_glutSpecialFunc( SpecialKey );
    GLUI_Master.set_glutMouseFunc( Mouse );
    glutMotionFunc( Motion );

    /**** We register the idle callback with GLUI, *not* with GLUT ****/
    GLUI_Master.set_glutIdleFunc( Idle );

    // Create objects
    int object_id = 0;
    TPrimitive *road        = new TPrimitive(object_id++, ROAD_ID);
    TPrimitive *car1        = new TPrimitive(object_id++, CAR_ID);
    TPrimitive *car2        = new TPrimitive(object_id++, CAR_ID);
    TPrimitive *platform    = new TPrimitive(object_id++, PLATFORM_ID);
    TPrimitive *floor       = new TPrimitive(object_id++, FLOOR_ID);
    TPrimitive *floor2      = new TPrimitive(object_id++, FLOOR2_ID);
    TPrimitive *river       = new TPrimitive(object_id++, RIVER_ID);
    TPrimitive *mountains   = new TPrimitive(object_id++, MOUNTAINS_ID);
    TPrimitive *trees       = new TPrimitive(object_id++, TREES_ID);
    TPrimitive *tunnel      = new TPrimitive(object_id++, TUNNEL_ID);
    TPrimitive *bollards    = new TPrimitive(object_id++, BOLLARDS_ID);
    TPrimitive *signall     = new TPrimitive(object_id++, SIGNAL1_ID);
    TPrimitive *signal2     = new TPrimitive(object_id++, SIGNAL2_ID);


    scene.AddCar(car1);
    scene.AddCar(car2);
    scene.AddObject(road);
    scene.AddObject(platform);
    scene.AddObject(floor);
    scene.AddObject(floor2);
    scene.AddObject(river);
    scene.AddObject(mountains);
    scene.AddObject(trees);
    scene.AddObject(tunnel);
    scene.AddObject(bollards);
    scene.AddObject(signall);
    scene.AddObject(signal2);

    /**** Regular GLUT main loop ****/
    glutMainLoop();

    return EXIT_SUCCESS;
}

