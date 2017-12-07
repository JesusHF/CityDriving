
/****************************************************************************************

    ForestDriving (Objects.cpp)

    Computer Graphics project.
    OpenGL with Shaders
  ---------------------------------------------------------------------------------------

    ForestDriving (CC) 2017

*****************************************************************************************/

#include "Objects.h"
#include <GL/glui.h>
#include <math.h>

#include "load3ds.c"
#include "loadjpeg.c"

//Wheel placing variables to match car
#define x_left              0.5
#define x_right            -0.2
#define zdistance           1.05

#define car_x_offset        0
#define car_y_offset        0.04
#define car_z_offset       -28.05545

#define chasis_y_offset    0.32

#define wheel_x_offset     -0.35
#define wheel_z_offset     0.75

#pragma GCC diagnostic ignored "-Wwrite-strings"

// Variable for initializing vectors with initials values
GLfloat light0_ambient_c[4]  = {   0.2f,   0.2f,  0.2f, 1.0f };
GLfloat light0_diffuse_c[4]  = {   0.8f,   0.8f,  0.8f, 1.0f };
GLfloat light0_specular_c[4] = {   1.0f,   1.0f,  1.0f, 1.0f };
GLfloat light0_position_c[4] = {-100.0f, 100.0f, 50.0f, 1.0f };

GLfloat light1_ambient_c[4]  = {   0.2f,   0.2f,  0.2f, 1.0f };
GLfloat light1_diffuse_c[4]  = {   0.8f,   0.8f,  0.8f, 1.0f };
GLfloat light1_specular_c[4] = {   1.0f,   1.0f,  1.0f, 1.0f };
GLfloat light1_position_c[4] = {   0.0f, 100.0f,  0.0f, 1.0f };

GLfloat mat_ambient_c[4]    = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat mat_diffuse_c[4]    = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat mat_specular_c[4]   = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat mat_shininess_c[1] = { 100.0f };

// 4x4 Matrix = (I)
float view_rotate_c[16] = { 1,0,0,0, 0,1,0,0, 0,0,-1,0, 0,0,0,1 };
float view_position_c[3] = { 0.0, -2.0, -35 };

float colorsc_c[2][4] = { {0.8, 0.5, 0.0, 1.0}, {0.5, 0.5, 0.5, 1.0}}; // Car color
float colorsr_c[2][4] = { {0.3, 0.3, 0.3, 1.0}, {1.0, 1.0, 1.0, 1.0}}; // Road color
float colors_floor[2][4] = { {0.0, 0.6, 0.0, 1.0}, {1.0, 1.0, 1.0, 1.0}}; // Floor color
float colors_river[2][4] = { {0.0, 0.6, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0}}; // River color
float colors_mount[2][4] = { {0.3, 0.15,0.0, 1.0}, {1.0, 1.0, 1.0, 1.0}}; // Mountains  color
float colors_platf[2][4] = { {0.8, 0.5, 0.0, 1.0}, {0.5, 0.5, 0.5, 1.0}}; // Platform color

//************************************************************** Class Variables

TScene scene;
TGui    gui;

//************************************************************** TPrimitive Class

TPrimitive::TPrimitive(int DL, int t)
{

    ID   = DL;
    type = t;

    sx = sy = sz = 1;
    rx = ry = rz = 0;
	tx = ty = tz = 0;

	switch (type) {
		case ROAD_ID: {  // Road creation

            memcpy(colors[0], colorsr_c, 8*sizeof(float));
            //************************ Loading 3ds models ***********************************
            // 8 floats format per vertex (x, y, z, A, B, C, u, v)
            model0 = Load3DS("../../models/carretera.3ds", &num_vertex0);

            break;
		}
		case CAR_ID: { // Car creation

            tx = car_x_offset;
            ty = car_y_offset;
            tz = car_z_offset;

            dirAngle = Angle(0);
            turnAngle = 0;

		    memcpy(colors, colorsc_c, 8*sizeof(float));
            //************************ Loading 3ds models ***********************************
            // 8 floats format per vertex (x, y, z, A, B, C, u, v)
            model0 = Load3DS("../../models/coche_salchicha.3ds", &num_vertex0);
            model1 = Load3DS("../../models/rueda.3ds", &num_vertex1);
            break;
		}

		case PLATFORM_ID: { // Platform

		    memcpy(colors, colors_platf, 8*sizeof(float));
            //************************ Loading 3ds models ***********************************
            // 8 floats format per vertex (x, y, z, A, B, C, u, v)
            model0 = Load3DS("../../models/platform.3ds", &num_vertex0);
            break;
		}

        case FLOOR_ID: { // Platform

		    memcpy(colors, colors_floor, 8*sizeof(float));
            //************************ Loading 3ds models ***********************************
            // 8 floats format per vertex (x, y, z, A, B, C, u, v)
            model0 = Load3DS("../../models/floor.3ds", &num_vertex0);
            break;
		}

		case FLOOR2_ID: { // Platform

		    memcpy(colors, colors_floor, 8*sizeof(float));
            //************************ Loading 3ds models ***********************************
            // 8 floats format per vertex (x, y, z, A, B, C, u, v)
            model0 = Load3DS("../../models/floor2.3ds", &num_vertex0);
            break;
		}

        case RIVER_ID: { // Platform

		    tx = ty = tz = 0;
		    memcpy(colors, colors_river, 8*sizeof(float));

            //************************ Loading 3ds models ***********************************
            // 8 floats format per vertex (x, y, z, A, B, C, u, v)
            model0 = Load3DS("../../models/rio.3ds", &num_vertex0);
            break;
		}

        case MOUNTAINS_ID: { // Platform

		    memcpy(colors, colors_mount, 8*sizeof(float));
            //************************ Loading 3ds models ***********************************
            // 8 floats format per vertex (x, y, z, A, B, C, u, v)
            model0 = Load3DS("../../models/mountains.3ds", &num_vertex0);
            break;
		}

        case TREES_ID: { // Platform

		    memcpy(colors, colors_mount, 8*sizeof(float));
            //************************ Loading 3ds models ***********************************
            // 8 floats format per vertex (x, y, z, A, B, C, u, v)
            model0 = Load3DS("../../models/trees.3ds", &num_vertex0);
            break;
		}

		case TUNNEL_ID: {  // Road creation

            memcpy(colors[0], colorsr_c, 8*sizeof(float));
            //************************ Loading 3ds models ***********************************
            // 8 floats format per vertex (x, y, z, A, B, C, u, v)
            model0 = Load3DS("../../models/tunel.3ds", &num_vertex0);

            break;
		}

		case BOLLARDS_ID: {  // Road creation

            memcpy(colors[0], colors_floor, 8*sizeof(float));
            //************************ Loading 3ds models ***********************************
            // 8 floats format per vertex (x, y, z, A, B, C, u, v)
            model0 = Load3DS("../../models/bollards.3ds", &num_vertex0);

            break;
		}

		case SIGNAL1_ID: {  // Road creation

            memcpy(colors[0], colors_floor, 8*sizeof(float));
            //************************ Loading 3ds models ***********************************
            // 8 floats format per vertex (x, y, z, A, B, C, u, v)
            model0 = Load3DS("../../models/signal_sausage.3ds", &num_vertex0);

            break;
		}

		case SIGNAL2_ID: {  // Road creation

            memcpy(colors[0], colors_floor, 8*sizeof(float));
            //************************ Loading 3ds models ***********************************
            // 8 floats format per vertex (x, y, z, A, B, C, u, v)
            model0 = Load3DS("../../models/signal_not_sausage.3ds", &num_vertex0);

            break;
		}

	} // switch
}

void __fastcall TPrimitive::Render(int selection, bool reflex)
{
    glm::mat4   modelMatrix;
    glm::mat4   modelViewMatrix;
    switch (type) {

        case ROAD_ID: {
            if (scene.show_road) {

                // ModelView calculation
                modelMatrix     = glm::mat4(1.0f); // identity matrix
                modelViewMatrix = scene.viewMatrix * modelMatrix;

                // send ModelView to Vertex Shader
                glUniformMatrix4fv(scene.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // draw road
                glUniform4fv(scene.uColorLocation, 1, colors[0]);
                //glUniform1i(scene.uTextureUnitLocation, scene.textures[4]);

                // associate vertex and its normals
                glVertexAttribPointer(scene.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, model0);
                glVertexAttribPointer(scene.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, model0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertex0);

            }
            break;
        }
        case CAR_ID: {

            if (scene.show_car) {
                glUniform4fv(scene.uColorLocation, 1, (const GLfloat *) colors[0]);

                // associate vertex and its normals
                glVertexAttribPointer(scene.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, model0);
                glVertexAttribPointer(scene.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, model0+3);

                // Matrix model calculation
                modelMatrix     = glm::mat4(1.0f); // identity matrix
                modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx, ty+chasis_y_offset, tz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0));

                modelViewMatrix = scene.viewMatrix * modelMatrix;

                // send ModelView to Vertex Shader
                glUniformMatrix4fv(scene.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glDrawArrays(GL_TRIANGLES, 0, num_vertex0);
            }


            if (scene.show_wheels)
            {
                glUniform4fv(scene.uColorLocation, 1, (const GLfloat *) colors[1]);

                // associate vertex and its normals
                glVertexAttribPointer(scene.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, model1);
                glVertexAttribPointer(scene.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, model1+3);

                // TOP RIGHT WHEEL : Matrix model calculation
                modelMatrix     = glm::mat4(1.0f); // identity matrix

                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx+wheel_x_offset+x_left, ty, tz+wheel_z_offset));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(turnAngle), glm::vec3(0,1,0));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(1,0,0));      // radians
                //modelMatrix     = glm::rotate()

                modelViewMatrix = scene.viewMatrix * modelMatrix;

                // send ModelView to Vertex Shader
                glUniformMatrix4fv(scene.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glDrawArrays(GL_TRIANGLES, 0, num_vertex1);

                // TOP LEFT WHEEL : Matrix model calculation
                modelMatrix     = glm::mat4(1.0f); // identity matrix
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx+wheel_x_offset-x_right, ty, tz+wheel_z_offset));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(turnAngle), glm::vec3(0,1,0));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(1,0,0));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(180.0), glm::vec3(0,0,1));   // radians

                modelViewMatrix = scene.viewMatrix * modelMatrix;

                // send ModelView to Vertex Shader
                glUniformMatrix4fv(scene.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glDrawArrays(GL_TRIANGLES, 0, num_vertex1);

                // BOT LEFT WHEEL: Matrix model calculation
                modelMatrix     = glm::mat4(1.0f); // identity matrix

                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx+wheel_x_offset+x_left, ty, tz+wheel_z_offset-zdistance));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(1,0,0));      // radians

                modelViewMatrix = scene.viewMatrix * modelMatrix;

                // send ModelView to Vertex Shader
                glUniformMatrix4fv(scene.uMVMatrixLocation,1, GL_FALSE, &modelViewMatrix[0][0]);

                glDrawArrays(GL_TRIANGLES, 0, num_vertex1);

                // BOT RIGHT WHEEL: Matrix model calculation
                modelMatrix     = glm::mat4(1.0f); // identity matrix
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx+wheel_x_offset-x_right, ty, tz+wheel_z_offset-zdistance));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(1,0,0));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(180.0), glm::vec3(0,0,1));   // radians

                modelViewMatrix = scene.viewMatrix * modelMatrix;

                // send ModelView to Vertex Shader
                glUniformMatrix4fv(scene.uMVMatrixLocation,1, GL_FALSE, &modelViewMatrix[0][0]);

                glDrawArrays(GL_TRIANGLES, 0, num_vertex1);
                break;
            }
        }

        case PLATFORM_ID:
        case FLOOR_ID:
        case FLOOR2_ID:
        case RIVER_ID:
        case MOUNTAINS_ID:
        case TREES_ID:
        case TUNNEL_ID:
        case SIGNAL1_ID:
        case SIGNAL2_ID:
        {
            if (scene.show_road) {

                // ModelView calculation
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelViewMatrix = scene.viewMatrix * modelMatrix;

                // send ModelView to Vertex Shader
                glUniformMatrix4fv(scene.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Matrix model calculation
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx, ty, tz));

                modelViewMatrix = scene.viewMatrix * modelMatrix;

                // draw road
                glUniform4fv(scene.uColorLocation, 1, colors[0]);

                // associate vertex and its normals
                glVertexAttribPointer(scene.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, model0);
                glVertexAttribPointer(scene.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, model0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertex0);

            }
            break;
        }

        //default:
            //std::cout<<"There is no ID for this:"<<type<<std::endl;
    } // switch

}

//************************************************************** Clase TScene

TScene::TScene() {

    selection = 1;
    num_objects = 0;
    num_cars = 0;

    show_car = 1;
    show_wheels = 1;
    show_road = 1;

    // live variables used by GLUI in TGui
    wireframe = 0;
    z_buffer = 1;
    culling = 0;

    scale = 1.0;
    xy_aspect = 1;
    last_x = 0;
    last_y = 0;

    memcpy(view_position, view_position_c, 3*sizeof(float));
    memcpy(view_rotate, view_rotate_c, 16*sizeof(float));

    memcpy(light0_ambient, light0_ambient_c, 4*sizeof(float));

    memcpy(light0_ambient, light0_ambient_c, 4*sizeof(float));
    memcpy(light0_diffuse, light0_diffuse_c, 4*sizeof(float));
    memcpy(light0_specular, light0_specular_c, 4*sizeof(float));
    memcpy(light0_position, light0_position_c, 4*sizeof(float));

    memcpy(light1_ambient, light1_ambient_c, 4*sizeof(float));
    memcpy(light1_diffuse, light1_diffuse_c, 4*sizeof(float));
    memcpy(light1_specular, light1_specular_c, 4*sizeof(float));
    memcpy(light1_position, light1_position_c, 4*sizeof(float));

    memcpy(mat_ambient, mat_ambient_c, 4*sizeof(float));
    memcpy(mat_diffuse, mat_diffuse_c, 4*sizeof(float));
    memcpy(mat_specular, mat_specular_c, 4*sizeof(float));
    memcpy(mat_shininess, mat_shininess_c, 1*sizeof(float));
}

void __fastcall TScene::InitGL()
{
    int tx, ty, tw, th;

    // Habilita el z_buffer
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Inicialización de GLEW
    std::cout << "Inicializando GLEW" << std::endl << std::endl;
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("glewInit failed");

    // print out some info about the graphics drivers
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vendedor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

    // Carga de los Shaders
    std::cout << std::endl << "Cargando Shaders" << std::endl;

    Shader shader;

    std::vector<GLuint> shaders;
    shaders.push_back(shader.LoadShader("../../Shaders/VertexShader.glsl", GL_VERTEX_SHADER));
    //std::cout << "Vertex Shader: " << shader.ReturnShaderID() << std::endl;
    shaders.push_back(shader.LoadShader("../../Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER));
    //std::cout << "Fragment Shader: " << shader.ReturnShaderID() << std::endl;
    shaderProgram = new Program(shaders);

    //std::cout << "Shader Program: " << shaderProgram->ReturnProgramID() << std::endl;

    glUseProgram(shaderProgram->ReturnProgramID());
    //glValidateProgram(shaderProgram->ReturnProgramID());

    aPositionLocation=shaderProgram->attrib(A_POSITION);
    aNormalLocation=shaderProgram->attrib(A_NORMAL);

    uProjectionMatrixLocation=shaderProgram->uniform(U_PROJECTIONMATRIX);
    uMVMatrixLocation=shaderProgram->uniform(U_MVMATRIX);
    uVMatrixLocation=shaderProgram->uniform(U_VMATRIX);
    uColorLocation=shaderProgram->uniform(U_COLOR);
    //uTextureUnitLocation=shaderProgram->uniform(U_TEXTUREUNITLOCATION);

    uLuz0Location=shaderProgram->uniform(U_LUZ0);

    /*
    std::cout << "a_Position Location: " << aPositionLocation << std::endl;
    std::cout << "a_Normal Location: " << aNormalLocation << std::endl;

    std::cout << "u_ProjectionMatrix Location: " << uProjectionMatrixLocation << std::endl;
    std::cout << "u_MVMatrix Location: " << uMVMatrixLocation << std::endl;
    std::cout << "u_VMatrix Location: " << uVMatrixLocation << std::endl;
    std::cout << "u_Color Location: " << uColorLocation << std::endl;
    std::cout << "u_Luz0 Location: " << uLuz0Location << std::endl;
    */

    // Habilitamos el paso de attributes
    glEnableVertexAttribArray(aPositionLocation);
    glEnableVertexAttribArray(aNormalLocation);

    // Estableciendo la matriz de proyección perspectiva
    GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
    xy_aspect = (float)tw / (float)th;
    projectionMatrix = glm::perspective(45.0f, xy_aspect, 0.1f, 1000.0f);
    glUniformMatrix4fv(uProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));


    //Loading textures
    glGenTextures(10, textures);
    LoadTexture("../../models/textures/textura_coche.jpg", 0);
    LoadTexture("../../models/textures/textura_rueda.jpg", 1);
    LoadTexture("../../models/textures/textura_tunel.jpg", 2);
    LoadTexture("../../models/textures/textura_arbol.jpg", 3);
    LoadTexture("../../models/textures/textura_carretera.jpg", 4);
    LoadTexture("../../models/textures/textura_suelo.jpg", 5);
    LoadTexture("../../models/textures/textura_tunel.jpg", 6);
    LoadTexture("../../models/textures/textura_peligro_salchicha.jpg", 7);
    LoadTexture("../../models/textures/textura_senal_not.jpg", 8);

}


/************************** TScene::AddCar(TPrimitive *car) *****************/

void __fastcall TScene::AddCar(TPrimitive *car)
{
    cars[num_cars] = car;
    num_cars++;
}

/******************** TScene::AddObject(TPrimitive *object) *****************/

void __fastcall TScene::AddObject(TPrimitive *object)
{
    objects[num_objects] = object;
    num_objects++;
}

void __fastcall TScene::LoadTexture(char* path, unsigned char id){
    unsigned char* pixeles;
    int width, height;

    pixeles = LoadJPEG(path, &width, &height);
    glActiveTexture(GL_TEXTURE0 + textures[id]);
    glBindTexture(GL_TEXTURE_2D, textures[id]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixeles);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    free(pixeles);
}

/******************** TPrimitive *TScene::GetCar(int id) ********************/

TPrimitive __fastcall *TScene::GetCar(int id)
{
    TPrimitive *p=NULL;

    for (int i=0; i<num_cars; i++)
    {
        if (cars[i]->ID==id)
        {
            p = cars[i];
        }

    }
    return(p);
}

/******************** TScene::RenderCars() **********************************/

void __fastcall TScene::RenderCars(bool reflex) {

    for (int i=0; i<num_cars; i++)
    {
        cars[i]->Render(selection, reflex);
    }
}

/******************** TScene::RenderCars() **********************************/

void __fastcall TScene::RenderObjects(bool reflex) {

    for (int i=0; i<num_objects; i++)
    {
        objects[i]->Render(selection, reflex);
    }
}

/***************************************** TScene::Render() *****************/

void __fastcall TScene::Render()
{
    glm::mat4 rotateMatrix;

    glClearColor(0.0, 0.7, 0.9, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Cálculo de la vista (cámara)
    viewMatrix      = glm::mat4(1.0f);
    rotateMatrix    = glm::make_mat4(view_rotate);
    viewMatrix      = glm::translate(viewMatrix,glm::vec3(view_position[0], view_position[1], view_position[2]));
    viewMatrix      = viewMatrix*rotateMatrix;
    viewMatrix      = glm::scale(viewMatrix,glm::vec3(scale, scale, scale));

    glUniform1i(uLuz0Location, gui.light0_enabled);
    glUniformMatrix4fv(uVMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix)); // Para la luz matrix view pero sin escalado!

    // draw road and objects
    RenderObjects(selection);

    // draw objects
    RenderCars(selection);

    glutSwapBuffers();
}

// Selects a object through mouse
void __fastcall TScene::Pick3D(int mouse_x, int mouse_y)
{
}

//************************************************************** Class TGui

TGui::TGui()
{
    sel = 1;
    enable_panel2 = 1;
    light0_enabled = 1;
    light1_enabled = 1;
    light0_intensity = 0.8;
    light1_intensity = 0.8;
    memcpy(light0_position, light0_position_c, 4*sizeof(float));
    memcpy(light1_position, light1_position_c, 4*sizeof(float));
}

void controlCallback(int control)
{
    gui.ControlCallback(control);
}

void __fastcall TGui::Init(int main_window) {

    /****************************************************/
    /*        Código con el interfaz Gráfico GLUI       */
    /****************************************************/
    printf( "GLUI version: %3.2f\n", GLUI_Master.get_version() );

    window_id = main_window;

    /*** Crea a ventana lateral ***/
    glui = GLUI_Master.create_glui_subwindow( window_id, GLUI_SUBWINDOW_RIGHT );

    // Añade una separación
    new GLUI_StaticText( glui, "" );

    // Añade un panel con texto con el valor de la selección
    GLUI_Panel *panel0 = new GLUI_Panel(glui, "Selection");
    GLUI_RadioGroup *radioGroup = new GLUI_RadioGroup(panel0, &sel, SEL_ID, controlCallback);
    glui->add_radiobutton_to_group(radioGroup, "NONE");


    glui->add_radiobutton_to_group(radioGroup, "CAR 1");
    glui->add_radiobutton_to_group(radioGroup, "CAR 2");


    // Adds a separation
    new GLUI_StaticText( glui, "" );

    obj_panel = new GLUI_Rollout(glui, "Properties", true );

    /***** Control para las propiedades de scene *****/

    new GLUI_Checkbox( obj_panel, "Wired mode", &scene.wireframe, 1, controlCallback );
    glui->add_column_to_panel(obj_panel, true);
    new GLUI_Checkbox( obj_panel, "Culling", &scene.culling, 1, controlCallback );
    new GLUI_Checkbox( obj_panel, "Z Buffer", &scene.z_buffer, 1, controlCallback );

    /******** Añade controles para las luces ********/

    // Añade una separación
    new GLUI_StaticText( glui, "" );

    GLUI_Rollout *roll_lights = new GLUI_Rollout(glui, "Lights", false );

    GLUI_Panel *light0 = new GLUI_Panel( roll_lights, "Light 1" );
    GLUI_Panel *light1 = new GLUI_Panel( roll_lights, "Light 2" );

    new GLUI_Checkbox( light0, "Turned ON", &light0_enabled, LIGHT0_ENABLED_ID, controlCallback );
    light0_spinner = new GLUI_Spinner( light0, "Intensidad:", &light0_intensity,
                            LIGHT0_INTENSITY_ID, controlCallback );
    light0_spinner->set_float_limits( 0.0, 1.0 );
    GLUI_Scrollbar *sb;
    sb = new GLUI_Scrollbar( light0, "X",GLUI_SCROLL_HORIZONTAL,
                            &scene.light0_position[0],LIGHT0_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);
    sb = new GLUI_Scrollbar( light0, "Y",GLUI_SCROLL_HORIZONTAL,
                            &scene.light0_position[1],LIGHT0_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);
    sb = new GLUI_Scrollbar( light0, "Z",GLUI_SCROLL_HORIZONTAL,
                            &scene.light0_position[2],LIGHT0_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);

    new GLUI_Checkbox( light1, "Turned ON", &light1_enabled, LIGHT1_ENABLED_ID, controlCallback );
    light1_spinner = new GLUI_Spinner( light1, "Intensity:", &light1_intensity,
                            LIGHT1_INTENSITY_ID, controlCallback );
    light1_spinner->set_float_limits( 0.0, 1.0 );
    sb = new GLUI_Scrollbar( light1, "X",GLUI_SCROLL_HORIZONTAL,
                            &scene.light1_position[0],LIGHT1_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);
    sb = new GLUI_Scrollbar( light1, "Y",GLUI_SCROLL_HORIZONTAL,
                            &scene.light1_position[1],LIGHT1_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);
    sb = new GLUI_Scrollbar( light1, "Z",GLUI_SCROLL_HORIZONTAL,
                            &scene.light1_position[2],LIGHT1_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);


    // Añade una separación
    new GLUI_StaticText( glui, "" );

    /***  Rollout de Opciones ***/
    GLUI_Rollout *options = new GLUI_Rollout(glui, "Options", true );
    new GLUI_Checkbox( options, "Draw Car", &scene.show_car );
    new GLUI_Checkbox( options, "Draw Wheels", &scene.show_wheels );
    new GLUI_Checkbox( options, "Draw road", &scene.show_road );


    /*** Disable/Enable botones ***/
    // Añade una separación
    new GLUI_StaticText( glui, "" );
    new GLUI_Checkbox( glui, "Block movement", &enable_panel2 );
    // Añade una separación
    new GLUI_StaticText( glui, "" );
    new GLUI_Button( glui, "Reset Position", RESET_ID, controlCallback );

    // Añade una separación
    new GLUI_StaticText( glui, "" );

    new GLUI_Separator( glui );

     // Añade una separación
    new GLUI_StaticText( glui, "" );

    new GLUI_StaticText( glui, "  Author:" );
    new GLUI_StaticText( glui, "  2017 (CC) @JesusHF_" );

    // Adds a separation
    new GLUI_StaticText( glui, "" );

    new GLUI_Separator( glui );

    // Add a separation
    new GLUI_StaticText( glui, "" );

    /****** A 'quit' button *****/
    new GLUI_Button( glui, "QUIT", 0,(GLUI_Update_CB)exit );

    // Create sub window
    glui2 = GLUI_Master.create_glui_subwindow( window_id, GLUI_SUBWINDOW_BOTTOM );

    /**** Link windows to GLUI, and register idle callback ******/
    glui->set_main_gfx_window( window_id );
    glui2->set_main_gfx_window( window_id );

    view_rot = new GLUI_Rotation(glui2, "Rotacion Escena", scene.view_rotate );
    view_rot->set_spin( 1.0 );
    new GLUI_Column( glui2, false );
    GLUI_Translation *trans_xy = new GLUI_Translation(glui2, "Traslacion Escena XY", GLUI_TRANSLATION_XY, scene.view_position );
    trans_xy->set_speed( .005 );
    new GLUI_Column( glui2, false );
    GLUI_Translation *trans_x =  new GLUI_Translation(glui2, "Traslacion Escena X", GLUI_TRANSLATION_X, scene.view_position );
    trans_x->set_speed( .005 );
    new GLUI_Column( glui2, false );
    GLUI_Translation *trans_y = new GLUI_Translation( glui2, "Traslacion Escena Y", GLUI_TRANSLATION_Y, &scene.view_position[1] );
    trans_y->set_speed( .005 );
    new GLUI_Column( glui2, false );
    GLUI_Translation *trans_z = new GLUI_Translation( glui2, "Traslacion Escena Z", GLUI_TRANSLATION_Z, &scene.scale );
    trans_z->set_speed( .005 );

}

/**************************************** TGui::ControlCallback() *******************/

void __fastcall TGui::ControlCallback( int control )
{
    switch (control) {
        case LIGHT0_ENABLED_ID: {
            if ( light0_enabled )
                light0_spinner->enable();
            else
                light0_spinner->disable();
            break;
        }
        case LIGHT1_ENABLED_ID: {
            if ( light1_enabled )
                light1_spinner->enable();
            else
                light1_spinner->disable();
            break;
        }
        case LIGHT0_INTENSITY_ID: {

            float v[] = {
                scene.light0_diffuse[0],  scene.light0_diffuse[1],
                scene.light0_diffuse[2],  scene.light0_diffuse[3] };

            v[0] *= light0_intensity;
            v[1] *= light0_intensity;
            v[2] *= light0_intensity;
            break;
        }
        case LIGHT1_INTENSITY_ID: {

            float v[] = {
                scene.light1_diffuse[0],  scene.light1_diffuse[1],
                scene.light1_diffuse[2],  scene.light1_diffuse[3] };

            v[0] *= light1_intensity;
            v[1] *= light1_intensity;
            v[2] *= light1_intensity;
            break;
        }
        case ENABLE_ID: {
            glui2->enable();
            break;
        }
        case DISABLE_ID: {
            glui2->disable();
            break;
        }
        case RESET_ID: {
            memcpy(scene.view_position,view_position_c,3*sizeof(float));
            view_rot->reset();
            scene.scale = 1.0;
            break;
        }
        case SEL_ID: {
            scene.selection = sel;
            //GLUI_Master.SetFocus(true);
            glutSetWindow( glui->get_glut_window_id() );
            break;
        }
  } // switch
}

/***************************************** TGui::Idle() ***********/

void __fastcall TGui::Idle( void )
{
  /* According to the GLUT specification, the current window is
     undefined during an idle callback.  So we need to explicitly change
     it if necessary */
  if ( glutGetWindow() != window_id )
    glutSetWindow(window_id);

  /*  GLUI_Master.sync_live_all();  -- not needed - nothing to sync in this
                                       application  */
    if (enable_panel2)

        glui2->enable();
    else
        glui2->disable();

  glutPostRedisplay();
}

/**************************************** TGui::reshape() *************/

void __fastcall TGui::Reshape( int x, int y )
{
    int tx, ty, tw, th;
    GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
    glViewport( tx, ty, tw, th );

    scene.xy_aspect = (float)tw / (float)th;
    scene.projectionMatrix = glm::perspective(45.0f, scene.xy_aspect, 0.1f, 1000.0f);
    glUniformMatrix4fv(scene.uProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(scene.projectionMatrix));

    //std::cout << "xy aspect: " << scene.xy_aspect << std::endl;

    glutPostRedisplay();
}

/***************************************** gui::motion() **********/

void __fastcall TGui::Motion(int x, int y )
{
    glutPostRedisplay();
}

/***************************************** gui::Mouse() **********/

void __fastcall TGui::Mouse(int button, int button_state, int x, int y )
{
    scene.Pick3D(x, y);
}

