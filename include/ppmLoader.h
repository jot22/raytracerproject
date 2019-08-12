//
// Created by ap on 8/10/19.
//

#ifndef RAYTRACERPROJECT_PPMLOADER_H
#define RAYTRACERPROJECT_PPMLOADER_H

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

class ppmLoader {
public:
    ppmLoader() = default;

    /**
     * Loads a PPM File into a Char Array, and populates the supplied width and height params.
     * @param ppmFile the ppm file to be loaded
     * @param width Filling up the width of the PPM.
     * @param height Filling up the height of the PPM.
     * @return the PPM file data transformed as an unsigned char array
     */
    unsigned char *pix(const string &ppmFile, int &width, int &height) {
        ifstream openFile;
        openFile.open(ppmFile);
        std::string eachLine;


        if (!openFile.is_open()) {
            cout << "Error Opening File ff";
            exit(-1);
        }
        int count = 1;
        int pixelArrPos = 0;
        int scaleBy = 1;

        while (getline(openFile, eachLine)) {

            if (count < 4) {
                if (eachLine[0] == '#') {
                    continue;
                }
                //Width, Height Grab
                if (count == 2) {
                    string sizeArr[2];
                    stringstream tok(eachLine);
                    int sizeCount = 0;
                    while (tok.good() && sizeCount < 2) {
                        tok >> sizeArr[sizeCount];
                        sizeCount++;
                    }
                    m_width = std::stoi(sizeArr[0]);
                    m_height = std::stoi(sizeArr[1]);
                    m_PixelData = new unsigned char[m_width * m_height * 3];
                }
                //Scale up
                if (count == 3) {
                    int maxValPreScale = stoi(eachLine);
                    scaleBy = 255 / std::stoi(eachLine);
                    m_max = maxValPreScale * scaleBy;
                }
                count++;
            } else {
                if (eachLine[0] == '#') {
                    continue;
                }
                stringstream tokRGB(eachLine);
                while (tokRGB.good()) {
                    string temp;
                    tokRGB >> temp;
                    int k = std::stoi(temp) * scaleBy;
                    m_PixelData[pixelArrPos] = k;
                    pixelArrPos++;
                }
            }
        }

        openFile.close();
        height = m_height;
        width = m_width;
        return m_PixelData;
        //Do error handling if file is broken
    }

    ~ppmLoader() {
        delete[] m_PixelData;
    }

private:
    int m_height;
    int m_width;
    int m_max;
    unsigned char *m_PixelData;
};

#endif //RAYTRACERPROJECT_PPMLOADER_H
