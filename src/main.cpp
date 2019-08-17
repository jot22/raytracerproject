#include <sstream>
#include <OBJ.h>
#include <ppmLoader.h>
#include "canHitGeneric.h"
#include "texture.h"
#include "checkerBoardTexture.h"
#include "constantTexture.h"
#include "diffuseMaterial_Lambertian.h"
#include "dielectricMaterial.h"
#include "metalMaterial.h"
#include "bvhNode.h"
#include "bvh.h"
#include "camera.h"
#include "fstream"
#include "imageTexture.h"
#include "rectangleCanHit.h"
#include "diffuseLightMaterial.h"
#include "yzRectangleCanHit.h"
#include "xzRectangleCanHit.h"
#include "canHitGenericList.h"
#include "flipNormals.h"
#include "sphereCanHit.h"
#include "boxCanHit.h"
#include "translate.h"
#include "rotateY.h"
#include "constantMedium.h"
#include "triangleCanHit.h"


using namespace std;

//rotate vector along y axis at given angle
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

//gets color of ray hitting world
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
//    return {1, 1, 1}; //fully lit up scene (spheres, triangle, bunny)
    return {0, 0, 0}; //No lights in scene, Have to put your own
}

//makes cornellbox scene
canHitGeneric *cornellBox() {
    auto **list = new canHitGeneric *[8];
    int i = 0;
    material *red = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.65, 0.05, 0.05)));
//    material *red2 = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.65, 0.05, 0.05)));
    material *white = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.73, 0.73, 0.73)));
    material *white2 = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.73, 0.73, 0.73)));
    material *white3 = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.73, 0.73, 0.73)));
    material *white4 = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.73, 0.73, 0.73)));
    material *white5 = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.73, 0.73, 0.73)));
//    material *white6 = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.73, 0.73, 0.73)));
//    material *white7 = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.73, 0.73, 0.73)));
    material *green = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.12, 0.45, 0.15)));
    material *light = new diffuseLightMaterial(new constantTexture(vec3(15, 15, 15)));

    list[i++] = new flipNormals(new yzRectangleCanHit(0, 555, 0, 555, 555, green));
    list[i++] = new yzRectangleCanHit(0, 555, 0, 555, 0, red);
    list[i++] = new xzRectangleCanHit(213, 343, 227, 332, 554, light);
    list[i++] = new flipNormals(new xzRectangleCanHit(0, 555, 0, 555, 555, white));
    list[i++] = new xzRectangleCanHit(0, 555, 0, 555, 0, white2);
    list[i++] = new flipNormals(new rectangleCanHit(0, 555, 0, 555, 555, white3));

    list[i++] = new translate(new rotateY(new boxCanHit(vec3(0, 0, 0), vec3(165, 165, 165), white4), -18),
                              vec3(130, 0, 65));
    //list[i++] = new triangleCanHit(vec3(100,100,120), vec3(165,330,165), vec3(140,140,140),red2);
    list[i++] = new translate(new rotateY(new boxCanHit(vec3(0, 0, 0), vec3(165, 330, 165), white5), 15),
                              vec3(265, 0, 295));

    //list[i++] = new translate(new rotateY( new boxCanHit(vec3(130, 0, 65), vec3(295, 165, 230), white6)),vec3(130,0,65));
    //list[i++] = new boxCanHit(vec3(265, 0, 295), vec3(430, 330, 460), white7);
    return new canHitGenericList(list, i);
}

//makes cornell hot box scene
canHitGeneric *cornellHotBox() {
    auto **list = new canHitGeneric *[8];
    int i = 0;
    material *red = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.65, 0.05, 0.05)));
    material *white = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.73, 0.73, 0.73)));
    material *white2 = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.73, 0.73, 0.73)));
    material *white3 = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.73, 0.73, 0.73)));
    material *white4 = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.73, 0.73, 0.73)));
    material *white5 = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.73, 0.73, 0.73)));
    material *green = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.12, 0.45, 0.15)));
    material *light = new diffuseLightMaterial(new constantTexture(vec3(7, 7, 7)));

    list[i++] = new flipNormals(new yzRectangleCanHit(0, 555, 0, 555, 555, green));
    list[i++] = new yzRectangleCanHit(0, 555, 0, 555, 0, red);
    list[i++] = new xzRectangleCanHit(113, 443, 127, 432, 554, light);
    list[i++] = new flipNormals(new xzRectangleCanHit(0, 555, 0, 555, 555, white));
    list[i++] = new xzRectangleCanHit(0, 555, 0, 555, 0, white2);
    list[i++] = new flipNormals(new rectangleCanHit(0, 555, 0, 555, 555, white3));

    auto *b1 = new translate(new rotateY(new boxCanHit(vec3(0, 0, 0), vec3(165, 165, 165), white4), -18),
                             vec3(130, 0, 65));
    auto *b2 = new translate(new rotateY(new boxCanHit(vec3(0, 0, 0), vec3(165, 330, 165), white5), 15),
                             vec3(265, 0, 295));

    list[i++] = new constantMedium(b1, 0.01, new constantTexture(vec3(1.0, 1.0, 1.0)));
    list[i++] = new constantMedium(b2, 0.01, new constantTexture(vec3(0.0, 0.0, 0.0)));
    return new canHitGenericList(list, i);

}

//makes cornell box with bunnies
canHitGeneric *cornellHotBox2() {
    OBJ bunny("./bunny_centered.obj");
    vector <vec3> bun = bunny.getFaceVertexVector();
    auto **list = new canHitGeneric *[4 * bun.size() + 6];
    int i = 0;
    material *red = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.65, 0.05, 0.05)));
    material *white = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.73, 0.73, 0.73)));
    material *white2 = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.73, 0.73, 0.73)));
    material *white3 = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.73, 0.73, 0.73)));
    material *green = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.12, 0.45, 0.15)));
    material *light = new diffuseLightMaterial(new constantTexture(vec3(7, 7, 7)));

    list[i++] = new flipNormals(new yzRectangleCanHit(0, 555, 0, 555, 555, green));
    list[i++] = new yzRectangleCanHit(0, 555, 0, 555, 0, red);
    list[i++] = new xzRectangleCanHit(213, 343, 227, 332, 554, light);
    list[i++] = new flipNormals(new xzRectangleCanHit(0, 555, 0, 555, 555, white));
    list[i++] = new xzRectangleCanHit(0, 555, 0, 555, 0, white2);
    list[i++] = new flipNormals(new rectangleCanHit(0, 555, 0, 555, 555, white3));

    for (unsigned int k = 0; k < bun.size(); k += 3) {
        material *ferrariRed = new metalMaterial(new constantTexture(vec3(1.0f, 0.062745098f, 0.0f)), 0.0);
        list[i++] = new translate(
                new triangleCanHit(rotateYAxis(bun.at(k), -50) * 40, rotateYAxis(bun.at(k + 1), -50) * 40,
                                   rotateYAxis(bun.at(k + 2), -50) * 40, ferrariRed),
                vec3(440, 50, 0));
    }
    for (unsigned int k = 0; k < bun.size(); k += 3) {
        material *diamond = new dielectricMaterial(2.42f);
        list[i++] = new translate(
                new triangleCanHit(rotateYAxis(bun.at(k), -25) * 53, rotateYAxis(bun.at(k + 1), -25) * 53,
                                   rotateYAxis(bun.at(k + 2), -25) * 53, diamond),
                vec3(350, 56, 0));
    }
    for (unsigned int k = 0; k < bun.size(); k += 3) {
        material *metalGold = new metalMaterial(new constantTexture(vec3(0.83, 0.686, 0.2156)), 0.0);
        list[i++] = new translate(
                new triangleCanHit(rotateYAxis(bun.at(k), 25) * 66, rotateYAxis(bun.at(k + 1), 25) * 66,
                                   rotateYAxis(bun.at(k + 2), 25) * 66, metalGold),
                vec3(240, 62, 0));
    }
    for (unsigned int k = 0; k < bun.size(); k += 3) {
        material *glass = new dielectricMaterial(1.5f);
        list[i++] = new translate(new triangleCanHit(bun.at(k) * 80, bun.at(k + 1) * 80, bun.at(k + 2) * 80, glass),
                                  vec3(120, 67, 0));
    }
//    list[i++] = new translate(new rotateY(new boxCanHit(vec3(0, 0, 0), vec3(165, 165, 165), white), -18),
//                              vec3(130, 0, 65));
//
//    list[i++] = new translate(new rotateY(new boxCanHit(vec3(0, 0, 0), vec3(165, 330, 165), white), 15),
//                              vec3(265, 0, 295));

    return new bvh(list, i, 0, 0);

}

//makes scene with random spheres
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
    ppmLoader *loadPPM = new ppmLoader();

    loadPPM->pix("cap.ppm", w, h);
    std::cout << w << " " << h << "\n";

    list[i++] = new sphereCanHit(vec3(0, 1, 0), 1.0, new dielectricMaterial(1.5));
    list[i++] = new sphereCanHit(vec3(4, 1, 0), 1.0, new diffuseMaterial_Lambertian(new imageTexture(loadPPM, w, h)));
    list[i++] = new sphereCanHit(vec3(-4, 1, 0), 1.0,
                                 new metalMaterial(
                                         new constantTexture(vec3(0.83, 0.686, 0.2156)), 0.0));
//    list[i++] = new rectangleCanHit(3, 5, 1, 3, -2, new diffuseLightMaterial(new constantTexture(vec3(4, 4, 4))));
    return new bvh(list, i, 0.0, 0.0);
}

//makes cornell box with lots of spheres
canHitGeneric *cornellLotsOfSpheres() {
    int nb = 20;
    auto **list = new canHitGeneric *[30];
    auto **boxList = new canHitGeneric *[10000];
    auto **boxList2 = new canHitGeneric *[10000];

    int b = 0;
    for (int i = 0; i < nb; i++) {
        for (int j = 0; j < nb; j++) {
            auto *ground = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.48, 0.83, 0.53)));
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
    list[l++] = new bvh(boxList, b, 0, 1);
    auto *light = new diffuseLightMaterial(new constantTexture(vec3(7, 7, 7)));
    list[l++] = new xzRectangleCanHit(123, 423, 147, 412, 554, light);
    vec3 center(400, 400, 200);
    list[l++] = new sphereCanHit(vec3(260, 150, 45), 50, new dielectricMaterial(1.5));
    list[l++] = new sphereCanHit(vec3(0, 150, 145), 50,
                                 new metalMaterial(new constantTexture(vec3(0.8, 0.8, 0.9)), 10.0));

    auto *boundary = new sphereCanHit(vec3(360, 150, 145), 70, new dielectricMaterial(1.5));
    auto *boundary2 = new sphereCanHit(vec3(360, 150, 145), 70, new dielectricMaterial(1.5));

    list[l++] = boundary;
    list[l++] = new constantMedium(boundary2, 0.2, new constantTexture(vec3(0.2, 0.4, 0.9)));
    auto *boundary3 = new sphereCanHit(vec3(0, 0, 0), 5000, new dielectricMaterial(1.5));
    list[l++] = new constantMedium(boundary3, 0.0001, new constantTexture(vec3(1.0, 1.0, 1.0)));


    int w, h;
    ppmLoader *pixx = new ppmLoader();

    pixx->pix("cap.ppm", w, h);
    auto *emat = new diffuseMaterial_Lambertian(new imageTexture(pixx, w, h));


    list[l++] = new sphereCanHit(vec3(400, 200, 400), 100, emat);

    ppmLoader *pixx2 = new ppmLoader();
    pixx2->pix("w.ppm", w, h);
    emat = new diffuseMaterial_Lambertian(new imageTexture(pixx2, w, h));
    list[l++] = new sphereCanHit(vec3(220, 280, 300), 80, emat);
    int ns = 1000;
    for (int j = 0; j < ns; j++) {
        auto *white = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.73, 0.73, 0.73)));
        boxList2[j] = new sphereCanHit(vec3(165 * (rand() / (RAND_MAX + 1.0)), 165 * ((rand() / (RAND_MAX + 1.0))),
                                            165 * (rand() / (RAND_MAX + 1.0))), 10, white);
    }
    list[l++] = new translate(new rotateY(new bvh(boxList2, ns, 0.0, 1.0), 15), vec3(-100, 270, 395));

    return new bvh(list, l, 0, 0);
}

//sets up camera with input values
camera makeCameraTri(float vFOV, float wH, vec3 z, float aperture, float distToFocus) {
    return {vFOV, wH, {278, 278, -800}, {278, 278, 0}, z, aperture, distToFocus, 0.0, 1.0};
}

//sets up camera with input values
camera makeCameraBox(float vFOV, float wH, vec3 z, float aperture, float distToFocus) {
    return {vFOV, wH, {278, 278, -800}, {278, 278, 0}, z, aperture, distToFocus, 0.0, 1.0};
}

//makes triangle scene
canHitGeneric *makeTriangleScene() {
    auto **list = new canHitGeneric *[1];
    int i = 0;
    material *red = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.65, 0.05, 0.05)));
    list[i++] = new triangleCanHit(vec3(0, 0, -1), vec3(4, 0, -1), vec3(2, 2, -1), red);
//    list[i++] = new sphereCanHit(vec3(0, 0, -1), 0.5,
//                                 new diffuseMaterial_Lambertian(new constantTexture(vec3(0.1, 0.2, 0.5))));
    return new canHitGenericList(list, i);
}

//makes bunny scene
canHitGeneric *makeBunny() {
    OBJ bunny("./bunny_centered.obj");
    vector <vec3> bun = bunny.getFaceVertexVector();
//    std::cout << bun.size() << "\n";
    auto **list = new canHitGeneric *[bun.size()];
    int k = 0;
    for (unsigned int i = 0; i < bun.size(); i += 3) {
        material *red = new metalMaterial(new constantTexture(vec3(0.83, 0.686, 0.2156)), 0.0);
        list[k++] = new triangleCanHit(bun.at(i), bun.at(i + 1), bun.at(i + 2), red);
    }
    //return new canHitGenericList(list, k);
    return new bvh(list, k, 0, 0);
}

//main function for ray tracing where you can initialize world, perform ray tracing, and output to ppm
int main() {
    ofstream myfile;
    myfile.open("test.ppm");

    //Size
    int nx = 1280; //Width
    int ny = 640;  //Height
    //Anti-Aliasing Samples, Higher = Better = Slower
    //Higher Resolution means lower ns value is needed.
    int ns = 10;

    myfile << "P3\n" << nx << " " << ny << "\n255\n";

    //initializes world to output to ppm
    canHitGeneric *world =
//            cornellBox();
//            cornellHotBox();
            cornellHotBox2();
//            cornellLotsOfSpheres();
//            randomSceneGen();
//            makeTriangleScene();
//            makeBunny();

    //random/triangle/bunny camera look from/at
//    vec3 lookFrom(13, 2, 3);
//    vec3 lookAt(0, 0, 0);

//    cornell camera look from/at
    vec3 lookFrom(278, 278, -800);
    vec3 lookAt(278, 278, 0);

    float dist_to_focus = 10.0;
    float aperture = 0.0;
    int vFOV = 40;
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
                float u = float(i + (rand() / (RAND_MAX + 1.0))) / float(nx);
                float v = float(j + (rand() / (RAND_MAX + 1.0))) / float(ny);
                ray r = cam.get_ray(u, v);
                col += color(r, world, 0);
            }
            col /= float(ns);
            //Gamma Correction
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            auto ir = int(255.99 * col[0]);
            auto ig = int(255.99 * col[1]);
            auto ib = int(255.99 * col[2]);
            myfile << ir << " " << ig << " " << ib << "\n";
        }
    }
    std::cout << ":::::::Render Complete:::::::\n";
    myfile.close();
    delete world;

    return 0;
}