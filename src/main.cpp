#include <sstream>
#include <OBJ.h>
#include "canHitGeneric.h"
#include "texture.h"
#include "checkerBoardTexture.h"
#include "sphereCanHit.h"
#include "constantTexture.h"
#include "diffuseMaterial_Lambertian.h"
#include "dielectricMaterial.h"
#include "metalMaterial.h"
#include "bvhNode.h"
#include "camera.h"
#include "fstream"
#include "imageTexture.h"
#include "rectangleCanHit.h"
#include "diffuseLightMaterial.h"
#include "yzRectangleCanHit.h"
#include "xzRectangleCanHit.h"
#include "canHitGenericList.h"
#include "flipNormals.h"
#include "boxCanHit.h"
#include "translate.h"
#include "rotateY.h"
#include "constantMedium.h"
#include "triangleCanHit.h"


using namespace std;

//Normals are not enforced to be unit length





//For a sphere centered at origin,
//If R*R = x*x + y*y + z*z then (x,y,z) is on the sphere, otherwise it is not

//For a sphere centered at (cx,cy,cz),
//(x-cx)^2+(y-cy)^2+(z-cz)^2 = R^2

//Chapter 4 Start, Math outlined
//float hit_sphere(const vec3 &center, float radius, const ray &r) {
//    vec3 oc = r.origin() - center;
//    float a = dot(r.direction(), r.direction());
//    float b = 2.0f * dot(oc, r.direction());
//    float c = dot(oc, oc) - radius * radius;
//    float discriminant = b * b - 4 * a * c;
//
//    if(discriminant < 0){
//        return -1.0f;
//    }
//    return (-b-sqrt(discriminant)) / (2.0f*a);
//}


//Creating Diffuse Surface = Matte
//vec3 random_in_unit_sphere(){
//    vec3 p;
//    do{
//        p = 2.0f*vec3(drand48(),drand48(),drand48()) - vec3(1,1,1);
//    }while(p.squared_length() >= 1.0);
//    return p;
//}

vec3 rotateYAxis(vec3 vector, float angle) {
    angle = angle * (3.14159265359f / 180.0f);
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
    return {xResult, yResult, zResult};
}

vec3 color(const ray &r, canHitGeneric *world, int depth) {
    hit_record rec;

    if (world->hit(r, 0.001, FLT_MAX, rec)) {
        ray scattered;
        vec3 attenuation;
        vec3 emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);

        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return emitted + attenuation * color(scattered, world, depth + 1);
        }
        return emitted;
    }
    return {1, 1, 1}; //No lights in scene, Have to put your own

    //Global Light
//    vec3 unit_direction = unit_vector(r.direction());
//    float t = 0.5f * (unit_direction.y() + 1.0f);
//    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);




    //return attenuation* color(scattered, world, depth + 1);
//        } else {
//            return {0, 0, 0};
//        }
//    } else {
//        vec3 unit_direction = unit_vector(r.direction());
//        float t = 0.5f * (unit_direction.y() + 1.0f);
//        return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
//    }

    //    float tValue = hit_sphere(vec3(0, 0, -1), 0.5, r);
//    if(tValue > 0.0){
//        vec3 N = unit_vector(r.point_at_param(tValue) - vec3(0,0,-1));
//        return 0.5f*vec3(N.x()+1.0f,N.y()+1.0f,N.z()+1.0f);
//
//    }
//    vec3 unit_dir = unit_vector(r.direction());
//    float t = 0.5f * (unit_dir.y() + 1.0f);
//    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);


}

unsigned char *pix(const string &ppmFile, int &width, int &height) {
    ifstream openFile;
    openFile.open(ppmFile);
    std::string eachLine;
    int m_width, m_height, m_max;
    unsigned char *m_PixelData;

    if (!openFile.is_open()) {
        std::cout << "Error Opening File ff";
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

canHitGeneric *cornellBox() {
    auto **list = new canHitGeneric *[8];
    int i = 0;
    material *red = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.65, 0.05, 0.05)));
    material *white = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.73, 0.73, 0.73)));
    material *green = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.12, 0.45, 0.15)));
    material *light = new diffuseLightMaterial(new constantTexture(vec3(15, 15, 15)));

    list[i++] = new flipNormals(new yzRectangleCanHit(0, 555, 0, 555, 555, green));
    list[i++] = new yzRectangleCanHit(0, 555, 0, 555, 0, red);
    list[i++] = new xzRectangleCanHit(213, 343, 227, 332, 554, light);
    list[i++] = new flipNormals(new xzRectangleCanHit(0, 555, 0, 555, 555, white));
    list[i++] = new xzRectangleCanHit(0, 555, 0, 555, 0, white);
    list[i++] = new flipNormals(new rectangleCanHit(0, 555, 0, 555, 555, white));

    list[i++] = new translate(new rotateY(new boxCanHit(vec3(0, 0, 0), vec3(165, 165, 165), white), -18),
                              vec3(130, 0, 65));
    //list[i++] = new triangleCanHit(vec3(100,100,120), vec3(165,330,165), vec3(140,140,140),red);
    list[i++] = new translate(new rotateY(new boxCanHit(vec3(0, 0, 0), vec3(165, 330, 165), white), 15),
                              vec3(265, 0, 295));

    //list[i++] = new translate(new rotateY( new boxCanHit(vec3(130, 0, 65), vec3(295, 165, 230), white)),vec3(130,0,65));
    //list[i++] = new boxCanHit(vec3(265, 0, 295), vec3(430, 330, 460), white);
    //return new canHitGenericList(list, i);
    return new canHitGenericList(list, i);
}

canHitGeneric *cornellHotBox() {
    auto **list = new canHitGeneric *[8];
    int i = 0;
    material *red = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.65, 0.05, 0.05)));
    material *white = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.73, 0.73, 0.73)));
    material *green = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.12, 0.45, 0.15)));
    material *light = new diffuseLightMaterial(new constantTexture(vec3(7, 7, 7)));

    list[i++] = new flipNormals(new yzRectangleCanHit(0, 555, 0, 555, 555, green));
    list[i++] = new yzRectangleCanHit(0, 555, 0, 555, 0, red);
    list[i++] = new xzRectangleCanHit(113, 443, 127, 432, 554, light);
    list[i++] = new flipNormals(new xzRectangleCanHit(0, 555, 0, 555, 555, white));
    list[i++] = new xzRectangleCanHit(0, 555, 0, 555, 0, white);
    list[i++] = new flipNormals(new rectangleCanHit(0, 555, 0, 555, 555, white));

    auto *b1 = new translate(new rotateY(new boxCanHit(vec3(0, 0, 0), vec3(165, 165, 165), white), -18),
                             vec3(130, 0, 65));
    auto *b2 = new translate(new rotateY(new boxCanHit(vec3(0, 0, 0), vec3(165, 330, 165), white), 15),
                             vec3(265, 0, 295));

    list[i++] = new constantMedium(b1, 0.01, new constantTexture(vec3(1.0, 1.0, 1.0)));
    list[i++] = new constantMedium(b2, 0.01, new constantTexture(vec3(0.0, 0.0, 0.0)));
    return new canHitGenericList(list, i);

}

canHitGeneric *cornellHotBox2() {
    OBJ bunny("./bunny_centered.obj");
    vector <vec3> bun = bunny.getFaceVertexVector();
    auto **list = new canHitGeneric *[4 * bun.size() + 8];
    int i = 0;
    material *red = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.65, 0.05, 0.05)));
    material *white = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.73, 0.73, 0.73)));
    material *green = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.12, 0.45, 0.15)));
    material *light = new diffuseLightMaterial(new constantTexture(vec3(7, 7, 7)));

    list[i++] = new flipNormals(new yzRectangleCanHit(0, 555, 0, 555, 555, green));
    list[i++] = new yzRectangleCanHit(0, 555, 0, 555, 0, red);
    list[i++] = new xzRectangleCanHit(113, 443, 127, 432, 554, light);
    list[i++] = new flipNormals(new xzRectangleCanHit(0, 555, 0, 555, 555, white));
    list[i++] = new xzRectangleCanHit(0, 555, 0, 555, 0, white);
    list[i++] = new flipNormals(new rectangleCanHit(0, 555, 0, 555, 555, white));
    material *metalGold = new metalMaterial(new constantTexture(vec3(0.83, 0.686, 0.2156)), 0.0);
    material *ferrariRed = new metalMaterial(new constantTexture(vec3(1.0f, 0.062745098f, 0.0f)), 0.0);
    material *diamond = new dielectricMaterial(2.42f);
    material *glass = new dielectricMaterial(1.5f);

    for (unsigned int k = 0; k < bun.size(); k += 3) {
        list[i++] = new translate(
                new triangleCanHit(rotateYAxis(bun.at(k), -50) * 40, rotateYAxis(bun.at(k + 1), -50) * 40,
                                   rotateYAxis(bun.at(k + 2), -50) * 40, ferrariRed),
                vec3(440, 50, 0));
    }
    for (unsigned int k = 0; k < bun.size(); k += 3) {
        list[i++] = new translate(
                new triangleCanHit(rotateYAxis(bun.at(k), -25) * 53, rotateYAxis(bun.at(k + 1), -25) * 53,
                                   rotateYAxis(bun.at(k + 2), -25) * 53, diamond),
                vec3(350, 56, 0));
    }
    for (unsigned int k = 0; k < bun.size(); k += 3) {
        list[i++] = new translate(
                new triangleCanHit(rotateYAxis(bun.at(k), 25) * 66, rotateYAxis(bun.at(k + 1), 25) * 66,
                                   rotateYAxis(bun.at(k + 2), 25) * 66, metalGold),
                vec3(240, 62, 0));
    }
    for (unsigned int k = 0; k < bun.size(); k += 3) {
        list[i++] = new translate(new triangleCanHit(bun.at(k) * 80, bun.at(k + 1) * 80, bun.at(k + 2) * 80, glass),
                                  vec3(120, 67, 0));
    }
//    list[i++] = new translate(new rotateY(new boxCanHit(vec3(0, 0, 0), vec3(165, 165, 165), white), -18),
//                              vec3(130, 0, 65));
//
//    list[i++] = new translate(new rotateY(new boxCanHit(vec3(0, 0, 0), vec3(165, 330, 165), white), 15),
//                              vec3(265, 0, 295));

    return new bvhNode(list, i, 0, 0);

}

canHitGeneric *randomSceneGen() {
    int n = 500;
    auto **list = new canHitGeneric *[n + 1];
    texture *checkerBoard = new checkerBoardTexture(new constantTexture(vec3(1.0, 1.0, 1.0)),
                                                    new constantTexture(vec3(0.0, 0.0, 0.0)));

    list[0] = new sphereCanHit(vec3(0, -1000, 0), 1000, new diffuseMaterial_Lambertian(checkerBoard));
    int i = 1;
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            float choose_mat = (rand() / (RAND_MAX + 1.0));
            vec3 center(a + 0.9 * (rand() / (RAND_MAX + 1.0)), 0.2f, b + 0.9f * (rand() / (RAND_MAX + 1.0)));
            if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
                if (choose_mat < 0.8) {

                    list[i++] = new sphereCanHit(center, 0.2, new diffuseMaterial_Lambertian(new constantTexture(
                            vec3((rand() / (RAND_MAX + 1.0)) * (rand() / (RAND_MAX + 1.0)),
                                 (rand() / (RAND_MAX + 1.0)) * (rand() / (RAND_MAX + 1.0)),
                                 (rand() / (RAND_MAX + 1.0)) * (rand() / (RAND_MAX + 1.0))))));
                } else if (choose_mat < 0.95) {
                    list[i++] = new sphereCanHit(center, 0.2, new metalMaterial(
                            new constantTexture(
                                    vec3(0.5 * (1 + (rand() / (RAND_MAX + 1.0))),
                                         0.5 * (1 + (rand() / (RAND_MAX + 1.0))),
                                         0.5 * (1 + (rand() / (RAND_MAX + 1.0))))),
                            0.5 * (rand() / (RAND_MAX + 1.0)))
                    );

                } else {
                    list[i++] = new sphereCanHit(center, 0.2, new dielectricMaterial(1.5));
                }
            }
        }
    }

    int w, h;
    unsigned char *pixx = pix("cap.ppm", w, h);
    std::cout << w << " " << h << "\n";

    list[i++] = new sphereCanHit(vec3(0, 1, 0), 1.0, new dielectricMaterial(1.5));
    list[i++] = new sphereCanHit(vec3(4, 1, 0), 1.0, new diffuseMaterial_Lambertian(new imageTexture(pixx, w, h)));
    list[i++] = new sphereCanHit(vec3(-4, 1, 0), 1.0,
                                 new metalMaterial(
                                         new constantTexture(vec3(0.83, 0.686, 0.2156)), 0.0));
//    list[i++] = new rectangleCanHit(3, 5, 1, 3, -2, new diffuseLightMaterial(new constantTexture(vec3(4, 4, 4))));

    return new bvhNode(list, i, 0.0, 0.0);
}

canHitGeneric *cornellLotsOfSpheres() {
    int nb = 20;
    auto **list = new canHitGeneric *[30];
    auto **boxList = new canHitGeneric *[10000];
    auto **boxList2 = new canHitGeneric *[10000];

    auto *white = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.73, 0.73, 0.73)));
    auto *ground = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.48, 0.83, 0.53)));

    int b = 0;
    for (int i = 0; i < nb; i++) {
        for (int j = 0; j < nb; j++) {
            float w = 100;
            float x0 = -1000 + i * w;
            float y0 = 0;
            float z0 = -1000 * j * w;

            float x1 = x0 + w;
            float y1 = 100.0f * ((rand() / (RAND_MAX + 1.0)) + 0.01f);
            float z1 = z0 + w;
            boxList[b++] = new boxCanHit(vec3(x0, y0, z0), vec3(x1, y1, z1), ground);
        }
    }
    int l = 0;
    list[l++] = new bvhNode(boxList, b, 0, 1);
    auto *light = new diffuseLightMaterial(new constantTexture(vec3(7, 7, 7)));
    list[l++] = new xzRectangleCanHit(123, 423, 147, 412, 554, light);
    vec3 center(400, 400, 200);
    list[l++] = new sphereCanHit(vec3(260, 150, 45), 50, new dielectricMaterial(1.5));
    list[l++] = new sphereCanHit(vec3(0, 150, 145), 50,
                                 new metalMaterial(new constantTexture(vec3(0.8, 0.8, 0.9)), 10.0));

    auto *boundary = new sphereCanHit(vec3(360, 150, 145), 70, new dielectricMaterial(1.5));
    list[l++] = boundary;
    list[l++] = new constantMedium(boundary, 0.2, new constantTexture(vec3(0.2, 0.4, 0.9)));
    boundary = new sphereCanHit(vec3(0, 0, 0), 5000, new dielectricMaterial(1.5));
    list[l++] = new constantMedium(boundary, 0.0001, new constantTexture(vec3(1.0, 1.0, 1.0)));


    int w, h;
    unsigned char *pixx = pix("cap.ppm", w, h);
    auto *emat = new diffuseMaterial_Lambertian(new imageTexture(pixx, w, h));


    list[l++] = new sphereCanHit(vec3(400, 200, 400), 100, emat);

    pixx = pix("w.ppm", w, h);
    emat = new diffuseMaterial_Lambertian(new imageTexture(pixx, w, h));
    list[l++] = new sphereCanHit(vec3(220, 280, 300), 80, emat);
    int ns = 1000;
    for (int j = 0; j < ns; j++) {
        boxList2[j] = new sphereCanHit(vec3(165 * (rand() / (RAND_MAX + 1.0)), 165 * ((rand() / (RAND_MAX + 1.0))),
                                            165 * (rand() / (RAND_MAX + 1.0))), 10, white);
    }
    list[l++] = new translate(new rotateY(new bvhNode(boxList2, ns, 0.0, 1.0), 15), vec3(-100, 270, 395));
    return new canHitGenericList(list, l);

    //return new bvhNode(list,l,0,0);

}

camera makeCameraTri(float vFOV, float wH, vec3 z, float aperture, float distToFocus) {
    return {vFOV, wH, {278, 278, -800}, {278, 278, 0}, z, aperture, distToFocus, 0.0, 1.0};
}

camera makeCameraBox(float vFOV, float wH, vec3 z, float aperture, float distToFocus) {
    return {vFOV, wH, {278, 278, -800}, {278, 278, 0}, z, aperture, distToFocus, 0.0, 1.0};
}


canHitGeneric *makeTriangleScene() {
    auto **list = new canHitGeneric *[2];
    int i = 0;
    material *red = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.65, 0.05, 0.05)));
    list[i++] = new triangleCanHit(vec3(0, 0, -1), vec3(4, 0, -1), vec3(2, 2, -1), red);
    list[i++] = new sphereCanHit(vec3(0, 0, -1), 0.5,
                                 new diffuseMaterial_Lambertian(new constantTexture(vec3(0.1, 0.2, 0.5))));
    return new canHitGenericList(list, i);;
}

canHitGeneric *makeBunny() {
    OBJ bunny("./bunny_centered.obj");
    vector <vec3> bun = bunny.getFaceVertexVector();
//    std::cout << bun.size() << "\n";
    auto **list = new canHitGeneric *[bun.size()];
    material *red = new metalMaterial(new constantTexture(vec3(0.83, 0.686, 0.2156)), 0.0);
    int k = 0;
    for (unsigned int i = 0; i < bun.size(); i += 3) {
        list[k++] = new triangleCanHit(bun.at(i), bun.at(i + 1), bun.at(i + 2), red);
    }
    return new bvhNode(list, k, 0, 0);
}


int main() {
    ofstream myfile;
    myfile.open("test.ppm");

    //Size
    int nx = 1280;
    int ny = 640;
    //Anti-Aliasing Samples, Higher = Better = Slower
    //Higher Resolution means lower ns value is needed.
    int ns = 1;


    //std::cout<<a->getHeight();
    myfile << "P3\n" << nx << " " << ny << "\n255\n";

//    canHitGeneric *list[4];
//    list[0] = new sphereCanHit(vec3(0, 0, -1), 0.5, new diffuseMaterial_Lambertian(vec3(0.1, 0.2, 0.5)));
//    list[1] = new sphereCanHit(vec3(0, -100.5f, -1), 100, new metalMaterial(vec3(0.8, 0.6, 0.2),0.0));//new diffuseMaterial_Lambertian(vec3(0.8, 0.8, 0.0)));
//    list[2] = new sphereCanHit(vec3(1, 0, -1), 0.5, new metalMaterial(vec3(0.8, 0.6, 0.2),0.0));
//    list[3] = new sphereCanHit(vec3(-1, 0, -1),0.5, new metalMaterial(vec3(0.8, 0.6, 0.2),0.99));
    //list[4] = new sphereCanHit(vec3(-1, 0, -1),-0.45f, new dielectricMaterial(1.5));


    //canHitGeneric *world = new canHitGenericList(list, 4);
    canHitGeneric *world =
//            cornellHotBox2();
//            makeBunny();
            makeTriangleScene();
// cornellBox();//cornellLotsOfSpheres();//cornellHotBox();//cornellBox();
//            randomSceneGen();
    //camera(float vFOV, float aspect, vec3 lookFrom, vec3 lookAt, vec3 vUp, aperture, focus_dist)
    //RandomScene Values
    vec3 lookFrom(13, 2, 3);
    vec3 lookAt(0, 0, 0);

//    vec3 lookFrom(278, 278, -800);
//    vec3 lookAt(278, 278, 0);
    float dist_to_focus = 10.0;//(lookFrom-lookAt).length();
    float aperture = 0.0;
//    int vFOV = 40;
    int vFOV = 20;

//    camera cam = makeCameraTri(vFOV, float(nx) / float(ny), vec3(0, 1, 0), aperture, dist_to_focus);
    camera cam(vFOV, float(nx) / float(ny), lookFrom, lookAt, vec3(0, 1, 0), aperture, dist_to_focus, 0.0, 1.0);

    int timer = 0;
    int progress = ny / 10;
    std::cout << ":::::::Rendering Progress:::::::\n";
    std::cout << timer << "% \n";
    for (int j = ny - 1; j >= 0; j--) {
        if (j % progress == 0) {
            timer += 10;
            std::cout << timer << "% \n";
        }
        for (int i = 0; i < nx; i++) {
            vec3 col(0, 0, 0);
            for (int s = 0; s < ns; s++) {
                //Implements Anti-Aliasing
                float u = float(i + (rand() / (RAND_MAX + 1.0))) / float(nx);
                float v = float(j + (rand() / (RAND_MAX + 1.0))) / float(ny);
                ray r = cam.get_ray(u, v);
                //vec3 p = r.point_at_param(2.0);
                col += color(r, world, 0);

            }
            col /= float(ns);
            //Gamma Correction
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            //  vec3 col = color(r);
            //vec3 col(float(i) / float(nx), float(j)/ float(ny),0.2);
//            float r = float(i) / float(nx);
//            float g = float(j) / float(ny);
//            float b = 0.2;
            auto ir = int(255.99 * col[0]);
            auto ig = int(255.99 * col[1]);
            auto ib = int(255.99 * col[2]);
            myfile << ir << " " << ig << " " << ib << "\n";
        }
    }
    std::cout << ":::::::Render Complete:::::::\n";

    //REMEMBER TO FREE THE SPHERES

    return 0;
}