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