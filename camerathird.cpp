#include "camerathird.h"
#include <iostream>
#include <math.h>
#include "matrix.h"

CameraThird::CameraThird(float distanceFromPivot){
    this->distanceFromPivot = distanceFromPivot,
    position.x=0;position.y=0;position.z=0;
    lookAt.x=0;lookAt.y=0;lookAt.z=0;
    pitch=1;
    angleAroundPivot=0;
    FOV = 40;
    NEAR_PLANE = 0.1f;
    FAR_PLANE = 8000;
}

CameraThird::CameraThird()
{
    position.x=0;position.y=0;position.z=0;
    lookAt.x=0;lookAt.y=0;lookAt.z=0;
    pitch=1;
    angleAroundPivot=0;
    distanceFromPivot=10;
    FOV = 40;
    NEAR_PLANE = 0.1f;
    FAR_PLANE = 8000;
}


void CameraThird::move(float dx, float dy, int dw, int z, int s, int q, int d){
    float zoomLevel = dw;

    if(distanceFromPivot - zoomLevel > 1.0f && distanceFromPivot - zoomLevel < 3000 )
        distanceFromPivot -= zoomLevel;



    float pitchChange = dy * 0.3f;
    //if(pitch - pitchChange >0 && pitch - pitchChange <85)
        pitch -= pitchChange;
    float angleChange = dx * 0.3f;
    angleAroundPivot -= angleChange;



    if(z){

        lookAt.z += 1.5f * cos(toRadians(angleAroundPivot));

        lookAt.x += 1.5f * sin(toRadians(angleAroundPivot));

    }
    else if(s){

        lookAt.z -= 1.5f * cos(toRadians(angleAroundPivot));

        lookAt.x -= 1.5f * sin(toRadians(angleAroundPivot));
    }
    else if(q){

        lookAt.z -= 1.5f * sin(toRadians(angleAroundPivot));

        lookAt.x += 1.5f * cos(toRadians(angleAroundPivot));
    }
    else if(d){

        lookAt.z += 1.5f * sin(toRadians(angleAroundPivot));

        lookAt.x -= 1.5f * cos(toRadians(angleAroundPivot));

    }

    float horizontalDistance = calculateHorizontal();
    float verticalDistance = calculateVertical();
    calculateCameraPosition(horizontalDistance,verticalDistance);

    yaw = 180 - angleAroundPivot;
}

void CameraThird::calculateCameraPosition(float hD, float vD){
    float offsetX = (float) (hD * sin(toRadians(angleAroundPivot)));
    float offsetZ = (float) (hD * cos(toRadians(angleAroundPivot)));
    position.x = lookAt.x - offsetX;
    position.y = lookAt.y + vD;
    position.z = lookAt.z - offsetZ;
}

float CameraThird::calculateHorizontal(){
    return (float) (distanceFromPivot * cos(toRadians(pitch)));
}

float CameraThird::calculateVertical(){
    return (float) (distanceFromPivot * sin(toRadians(pitch)));
}

float CameraThird::toRadians(float degree)
{
    return degree/180.0*M_PI;
}

glm::mat4 CameraThird::getViewMatrix(){
    viewMatrix = Matrix::createViewMatrix(*this);
    return viewMatrix;/* glm::lookAt(
                glm::vec3(position.x,position.y,position.z), // La caméra est à (4,3,3), dans l'espace monde
                glm::vec3(lookAt.x,lookAt.y,lookAt.z), // et regarde l'origine
                glm::vec3(0,1,0)  // La tête est vers le haut (utilisez 0,-1,0 pour regarder à l'envers)
            );*/
}

