/** @file obj.cpp
 *  @brief Class for working with obj models
 *
 *  Class for working with obj models specifically.
 *
 *  @author Joseph Triolo
 *  @bug No known bugs.
 */
#ifndef OBJ_H
#define OBJ_H

#include <string>
#include <vector>
#include "vec3.h"

class OBJ {
public:
    // Constructor loads a filename with the .obj extension
    OBJ(std::string fileName);

    // Destructor clears any memory that has been allocated
    ~OBJ();

    // Returns vertex vector
    std::vector <vec3> getVertexVector();

    // Returns normal vertex vector
    std::vector <vec3> getNormalVertexVector();

    // Returns face vector for vertices
    std::vector <vec3> getFaceVertexVector();

    // Returns face vector for normal vertices
    std::vector<unsigned int> getFaceNormalVertexVector();

    //Rotates the Object along the selected axis, Angle specified in Degrees
    std::vector<vec3> rotateXAxis(std::vector<vec3> selectedVector, float angle);

    //Rotates the Object along the selected axis, Angle specified in Degrees
    std::vector<vec3> rotateYAxis(std::vector<vec3> selectedVector, float angle);

    //Rotates the Object along the selected axis, Angle specified in Degrees
    std::vector<vec3> rotateZAxis(std::vector<vec3> selectedVector, float angle);

    //Scales a given Object by the specified value. Makes it bigger or smaller.
    std::vector<vec3> scaleObjectSize(std::vector<vec3> selectedVector, float scaleValue);


//// NOTE:    You may add any helper functions you like in the
////          private section.
private:
    // Vector to store vertices
    std::vector <vec3> vertexVector;

    // Vector to store normal vertices
    std::vector <vec3> normalVertexVector;

    // Vector to store face vertex indices
//    std::vector<unsigned int> faceVertexVector;

    std::vector <vec3> faceVertexVector;

    // Vector to store face normal vertex indices
    std::vector<unsigned int> faceNormalVertexVector;

    // Parse vertex and normal vertex lines into float arrays
    float *parseVertices(char token[], float arr[]);

    // Parse faces for vertices and normal vertices into respective uint arrays
    void parseFaces(char token[], float arr[]);

    // Array for holding floats for vertex and normal vertex data
    float *arr;
    float piVal = 3.14159265359f;

};


#endif
