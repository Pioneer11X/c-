//
//  Camera.h
//  CEngine
//
//  Created by Sravan Karuturi on 10/29/17.
//

#ifndef Camera_h
#define Camera_h

#include "glm/glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>

using namespace glm;

class Camera{
  
public:
    
    vec3 position;
    vec3 forward;
    vec3 up;
    
    Camera(){
        Camera(0);
    }
    
    Camera(int constructorType){
        
        // GL Camera Constuctor.
        if ( 1 == constructorType ){
            position = vec3(0.0f, 0.0f, 3.0f);
            forward = vec3(0.0f, 0.0f, -1.0f);
            up = vec3(0.0f, 1.0f, 0.0f);
        }else{
            
            // Garbage Values.
            std::cout << "Camera Initialised with Garbage Values " << std::endl;
            
            position = vec3(0.0f, 0.0f, 0.0f);
            forward = vec3(0.0f, 0.0f, 0.0f);
            up = vec3(0.0f, 0.0f, 0.0f);
        }
        
    };
    
};


#endif /* Camera_h */
