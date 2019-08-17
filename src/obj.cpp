#include "OBJ.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

// Constructor loads a filename with the .obj extension
OBJ::OBJ(std::string fileName) {
    string line;
    float tempArr[3];
    std::ifstream inFile;
    inFile.open(fileName);
    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            int n = line.length();
            char charArr[n + 1];
            strcpy(charArr, line.c_str());
            char *token = strtok(charArr, "\n\t ");
            if (token == NULL) {
                continue;
            } else if (strcmp(token, "v") == 0) {
                arr = parseVertices(token, tempArr);
                vertexVector.push_back(vec3(arr[0], arr[1], arr[2]));
            } else if (strcmp(token, "vn") == 0) {
                arr = parseVertices(token, tempArr);
                normalVertexVector.push_back(vec3(arr[0], arr[1], arr[2]));
            } else if (strcmp(token, "f") == 0) {
                parseFaces(token, tempArr);
            }
        }
    }
    inFile.close();
}

// Destructor clears any memory that has been allocated
OBJ::~OBJ() {
}

// Returns vertex vector
std::vector <vec3> OBJ::getVertexVector() {
    return vertexVector;
}

// Returns normal vertex vector
std::vector <vec3> OBJ::getNormalVertexVector() {
    return normalVertexVector;
}

// Returns face vector for vertices
std::vector <vec3> OBJ::getFaceVertexVector() {
    return faceVertexVector;
}

// Returns face vector for normal vertices
std::vector<unsigned int> OBJ::getFaceNormalVertexVector() {
    return faceNormalVertexVector;
}

// Parse vertex and normal vertex lines into float arrays
float *OBJ::parseVertices(char token[], float arr[]) {
    int count = 0;
    while (count < 3) {
        token = strtok(NULL, "\n\t ");
        arr[count] = std::stof(token);
        ++count;
    }
    return arr;
}

// Parse faces for vertices and normal vertices into respective uint arrays
void OBJ::parseFaces(char token[], float arr[]) {
    int count = 0;
    while (count < 3) {
        token = strtok(NULL, "\n\t ");
        std::string face(token);
        int index1 = 0;
        int index2 = 0;
        int slashCount = 0;
        while (isdigit(face[index2])) {
            ++index2;
        }

        faceVertexVector.push_back(vertexVector[(std::stoi(face.substr(index1, index2)) - 1)]);
        index1 = index2;
        while (slashCount < 2) {
            if (face[index1] == '/') {
                ++slashCount;
            }
            ++index1;
        }
        index2 = index1;
        while (isdigit(face[index2])) {
            ++index2;
        }

        faceNormalVertexVector.push_back(std::stoi(face.substr(index1, index2)) - 1);
        ++count;
    }
}

//Rotate obj around y axis by input angle
std::vector <vec3> OBJ::rotateYAxis(std::vector <vec3> selectedVector, float angle) {
    angle = angle * (piVal / 180.0f);
    for (auto &i : selectedVector) {
        vec3 vector = i;
        float x = vector.x();
        float y = vector.y();
        float z = vector.z();

        float x0y0 = cos(angle);
        float x1y0 = 0.0f;
        float x2y0 = sin(angle);

        float x0y1 = 0.0f;
        float x1y1 = 1.0f;
        float x2y1 = 0.0f;

        float x0y2 = -sin(angle);
        float x1y2 = 0.0f;
        float x2y2 = cos(angle);

        float xResult = (x0y0 * x) + (x1y0 * y) + (x2y0 * z);
        float yResult = (x0y1 * x) + (x1y1 * y) + (x2y1 * z);
        float zResult = (x0y2 * x) + (x1y2 * y) + (x2y2 * z);

        i = {xResult, yResult, zResult};
    }
    return selectedVector;
}

//Rotate obj around x axis by input angle
std::vector <vec3> OBJ::rotateXAxis(std::vector <vec3> selectedVector, float angle) {
    angle = angle * (piVal / 180.0f);
    for (auto &i : selectedVector) {
        vec3 vector = i;
        float x = vector.x();
        float y = vector.y();
        float z = vector.z();

        float x0y0 = 1.0f;
        float x1y0 = 0.0f;
        float x2y0 = 0.0f;

        float x0y1 = 0.0f;
        float x1y1 = cos(angle);
        float x2y1 = -sin(angle);

        float x0y2 = 0;
        float x1y2 = sin(angle);
        float x2y2 = cos(angle);

        float xResult = (x0y0 * x) + (x1y0 * y) + (x2y0 * z);
        float yResult = (x0y1 * x) + (x1y1 * y) + (x2y1 * z);
        float zResult = (x0y2 * x) + (x1y2 * y) + (x2y2 * z);

        i = {xResult, yResult, zResult};
    }
    return selectedVector;
}

//Rotate obj around z axis by input angle
std::vector <vec3> OBJ::rotateZAxis(std::vector <vec3> selectedVector, float angle) {
    angle = angle * (piVal / 180.0f);
    for (auto &i : selectedVector) {
        vec3 vector = i;
        float x = vector.x();
        float y = vector.y();
        float z = vector.z();

        float x0y0 = cos(angle);
        float x1y0 = -sin(angle);
        float x2y0 = 0.0f;

        float x0y1 = sin(angle);
        float x1y1 = cos(angle);
        float x2y1 = 0.0f;

        float x0y2 = 0.0f;
        float x1y2 = 0.0f;
        float x2y2 = 1.0f;

        float xResult = (x0y0 * x) + (x1y0 * y) + (x2y0 * z);
        float yResult = (x0y1 * x) + (x1y1 * y) + (x2y1 * z);
        float zResult = (x0y2 * x) + (x1y2 * y) + (x2y2 * z);

        i = {xResult, yResult, zResult};
    }
    return selectedVector;
}

//Scale obj by input value
std::vector <vec3> OBJ::scaleObjectSize(std::vector <vec3> selectedVector, float scaleValue) {
    if (scaleValue <= 0.0f) {
        return selectedVector;
    }
    for (auto &i : selectedVector) {
        vec3 scaleBy = i;
        float xVal = scaleBy.x() * scaleValue;
        float yVal = scaleBy.y() * scaleValue;
        float zVal = scaleBy.z() * scaleValue;
        i = {xVal, yVal, zVal};
    }
    return selectedVector;
}
