#include <sstream>
#include <OBJ.h>
#include <memory>
#include "ppmLoader.h"
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


vec3 color(const ray &r, canHitGeneric *world, int depth) {
    hit_record rec{};

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


//canHitGeneric *cornellBox() {
//    auto **list = new canHitGeneric *[8];
//    int i = 0;
//    material *red = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.65, 0.05, 0.05)));
//    material *white = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.73, 0.73, 0.73)));
//    material *green = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.12, 0.45, 0.15)));
//    material *light = new diffuseLightMaterial(new constantTexture(vec3(15, 15, 15)));
//
//    list[i++] = new flipNormals(new yzRectangleCanHit(0, 555, 0, 555, 555, green));
//    list[i++] = new yzRectangleCanHit(0, 555, 0, 555, 0, red);
//    list[i++] = new xzRectangleCanHit(213, 343, 227, 332, 554, light);
//    list[i++] = new flipNormals(new xzRectangleCanHit(0, 555, 0, 555, 555, white));
//    list[i++] = new xzRectangleCanHit(0, 555, 0, 555, 0, white);
//    list[i++] = new flipNormals(new rectangleCanHit(0, 555, 0, 555, 555, white));
//
//    list[i++] = new translate(new rotateY(new boxCanHit(vec3(0, 0, 0), vec3(165, 165, 165), white), -18),
//                              vec3(130, 0, 65));
//    //list[i++] = new triangleCanHit(vec3(100,100,120), vec3(165,330,165), vec3(140,140,140),red);
//    list[i++] = new translate(new rotateY(new boxCanHit(vec3(0, 0, 0), vec3(165, 330, 165), white), 15),
//                              vec3(265, 0, 295));
//
//    //list[i++] = new translate(new rotateY( new boxCanHit(vec3(130, 0, 65), vec3(295, 165, 230), white)),vec3(130,0,65));
//    //list[i++] = new boxCanHit(vec3(265, 0, 295), vec3(430, 330, 460), white);
//    //return new canHitGenericList(list, i);
//    return new canHitGenericList(list, i);
//}

//canHitGeneric *cornellHotBox() {
//    auto **list = new canHitGeneric *[8];
//    int i = 0;
//    material *red = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.65, 0.05, 0.05)));
//    material *white = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.73, 0.73, 0.73)));
//    material *green = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.12, 0.45, 0.15)));
//    material *light = new diffuseLightMaterial(new constantTexture(vec3(7, 7, 7)));
//
//    list[i++] = new flipNormals(new yzRectangleCanHit(0, 555, 0, 555, 555, green));
//    list[i++] = new yzRectangleCanHit(0, 555, 0, 555, 0, red);
//    list[i++] = new xzRectangleCanHit(113, 443, 127, 432, 554, light);
//    list[i++] = new flipNormals(new xzRectangleCanHit(0, 555, 0, 555, 555, white));
//    list[i++] = new xzRectangleCanHit(0, 555, 0, 555, 0, white);
//    list[i++] = new flipNormals(new rectangleCanHit(0, 555, 0, 555, 555, white));
//
//    auto *b1 = new translate(new rotateY(new boxCanHit(vec3(0, 0, 0), vec3(165, 165, 165), white), -18),
//                             vec3(130, 0, 65));
//    auto *b2 = new translate(new rotateY(new boxCanHit(vec3(0, 0, 0), vec3(165, 330, 165), white), 15),
//                             vec3(265, 0, 295));
//
//    list[i++] = new constantMedium(b1, 0.01, new constantTexture(vec3(1.0, 1.0, 1.0)));
//    list[i++] = new constantMedium(b2, 0.01, new constantTexture(vec3(0.0, 0.0, 0.0)));
//    return new canHitGenericList(list, i);
//
//}

//canHitGeneric *cornellHotBox2() {
//    OBJ bunny("./bunny_centered.obj");
//    vector<vec3> bun1 = bunny.getFaceVertexVector();
//    vector<vec3> bun2 = bunny.getFaceVertexVector();
//    vector<vec3> bun3 = bunny.getFaceVertexVector();
//    vector<vec3> bun4 = bunny.getFaceVertexVector();
//
//
//    auto **list = new canHitGeneric *[4 * bun1.size() + 8];
//    int i = 0;
//    material *red = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.65, 0.05, 0.05)));
//    material *white = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.73, 0.73, 0.73)));
//    material *green = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.12, 0.45, 0.15)));
//    material *light = new diffuseLightMaterial(new constantTexture(vec3(7, 7, 7)));
//
//    list[i++] = new flipNormals(new yzRectangleCanHit(0, 555, 0, 555, 555, green));
//    list[i++] = new yzRectangleCanHit(0, 555, 0, 555, 0, red);
//    list[i++] = new xzRectangleCanHit(113, 443, 127, 432, 554, light);
//    list[i++] = new flipNormals(new xzRectangleCanHit(0, 555, 0, 555, 555, white));
//    list[i++] = new xzRectangleCanHit(0, 555, 0, 555, 0, white);
//    list[i++] = new flipNormals(new rectangleCanHit(0, 555, 0, 555, 555, white));
//    material *metalGold = new metalMaterial(new constantTexture(vec3(0.83, 0.686, 0.2156)), 0.0);
//    material *ferrariRed = new metalMaterial(new constantTexture(vec3(1.0f, 0.062745098f, 0.0f)), 0.0);
//    material *diamond = new dielectricMaterial(2.42f);
//    material *glass = new dielectricMaterial(1.5f);
//
//    bun1 = bunny.rotateYAxis(bun1, -50);
//    bun1 = bunny.scaleObjectSize(bun1, 40);
//
//    for (unsigned int k = 0; k < bun1.size(); k += 3) {
//        list[i++] = new translate(
//                new triangleCanHit(bun1.at(k), bun1.at(k + 1), bun1.at(k + 2), ferrariRed), vec3(440, 50, 0));
//    }
//    bun2 = bunny.rotateYAxis(bun2, -25);
//    bun2 = bunny.scaleObjectSize(bun2, 53);
//
//
//    for (unsigned int k = 0; k < bun2.size(); k += 3) {
//        list[i++] = new translate(
//                new triangleCanHit(bun2.at(k), bun2.at(k + 1), bun2.at(k + 2), diamond), vec3(350, 56, 0));
//    }
//    bun3 = bunny.rotateYAxis(bun3, 25);
//    bun3 = bunny.scaleObjectSize(bun3, 66);
//
//    for (unsigned int k = 0; k < bun3.size(); k += 3) {
//        list[i++] = new translate(
//                new triangleCanHit(bun3.at(k), bun3.at(k + 1), bun3.at(k + 2), metalGold), vec3(240, 62, 0));
//    }
//    bun4 = bunny.scaleObjectSize(bun4, 80);
//    for (unsigned int k = 0; k < bun4.size(); k += 3) {
//        list[i++] = new translate(new triangleCanHit(bun4.at(k), bun4.at(k + 1), bun4.at(k + 2), glass),
//                                  vec3(120, 67, 0));
//    }
////    list[i++] = new translate(new rotateY(new boxCanHit(vec3(0, 0, 0), vec3(165, 165, 165), white), -18),
////                              vec3(130, 0, 65));
////
////    list[i++] = new translate(new rotateY(new boxCanHit(vec3(0, 0, 0), vec3(165, 330, 165), white), 15),
////                              vec3(265, 0, 295));
//
//    return new bvhNode(list, i, 0, 0);
//
//}
//
//canHitGeneric *randomSceneGen() {
//    int n = 500;
//    auto **list = new canHitGeneric *[n + 1];
//    texture *checkerBoard = new checkerBoardTexture(new constantTexture(vec3(1.0, 1.0, 1.0)),
//                                                    new constantTexture(vec3(0.0, 0.0, 0.0)));
//
//    list[0] = new sphereCanHit(vec3(0, -1000, 0), 1000, new diffuseMaterial_Lambertian(checkerBoard));
//    int i = 1;
//    for (int a = -11; a < 11; a++) {
//        for (int b = -11; b < 11; b++) {
//            float choose_mat = (rand() / (RAND_MAX + 1.0));
//            vec3 center(a + 0.9 * (rand() / (RAND_MAX + 1.0)), 0.2f, b + 0.9f * (rand() / (RAND_MAX + 1.0)));
//            if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
//                if (choose_mat < 0.8) {
//
//                    list[i++] = new sphereCanHit(center, 0.2, new diffuseMaterial_Lambertian(new constantTexture(
//                            vec3((rand() / (RAND_MAX + 1.0)) * (rand() / (RAND_MAX + 1.0)),
//                                 (rand() / (RAND_MAX + 1.0)) * (rand() / (RAND_MAX + 1.0)),
//                                 (rand() / (RAND_MAX + 1.0)) * (rand() / (RAND_MAX + 1.0))))));
//                } else if (choose_mat < 0.95) {
//                    list[i++] = new sphereCanHit(center, 0.2, new metalMaterial(
//                            new constantTexture(
//                                    vec3(0.5 * (1 + (rand() / (RAND_MAX + 1.0))),
//                                         0.5 * (1 + (rand() / (RAND_MAX + 1.0))),
//                                         0.5 * (1 + (rand() / (RAND_MAX + 1.0))))),
//                            0.5 * (rand() / (RAND_MAX + 1.0)))
//                    );
//
//                } else {
//                    list[i++] = new sphereCanHit(center, 0.2, new dielectricMaterial(1.5));
//                }
//            }
//        }
//    }
//
//    int w, h;
//    ppmLoader loadPPM{};
//
//    static unsigned char *pixx = loadPPM.pix("cap.ppm", w, h);
//    std::cout << w << " " << h << "\n";
//
//    list[i++] = new sphereCanHit(vec3(0, 1, 0), 1.0, new dielectricMaterial(1.5));
//    list[i++] = new sphereCanHit(vec3(4, 1, 0), 1.0, new diffuseMaterial_Lambertian(new imageTexture(pixx, w, h)));
//    list[i++] = new sphereCanHit(vec3(-4, 1, 0), 1.0,
//                                 new metalMaterial(
//                                         new constantTexture(vec3(0.83, 0.686, 0.2156)), 0.0));
//    list[i++] = new rectangleCanHit(3, 5, 1, 3, -2, new diffuseLightMaterial(new constantTexture(vec3(4, 4, 4))));
//
//    return new bvhNode(list, i, 0.0, 0.0);
//}
//
//canHitGeneric *cornellLotsOfSpheres() {
//    int nb = 20;
//    auto **list = new canHitGeneric *[30];
//    auto **boxList = new canHitGeneric *[10000];
//    auto **boxList2 = new canHitGeneric *[10000];
//
//    auto *white = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.73, 0.73, 0.73)));
//    auto *ground = new diffuseMaterial_Lambertian(new constantTexture(vec3(0.48, 0.83, 0.53)));
//
//    int b = 0;
//    for (int i = 0; i < nb; i++) {
//        for (int j = 0; j < nb; j++) {
//            float w = 100;
//            float x0 = -1000 + i * w;
//            float y0 = 0;
//            float z0 = -1000 * j * w;
//
//            float x1 = x0 + w;
//            float y1 = 100.0f * ((rand() / (RAND_MAX + 1.0)) + 0.01f);
//            float z1 = z0 + w;
//            boxList[b++] = new boxCanHit(vec3(x0, y0, z0), vec3(x1, y1, z1), ground);
//        }
//    }
//    int l = 0;
//    list[l++] = new bvhNode(boxList, b, 0, 1);
//    auto *light = new diffuseLightMaterial(new constantTexture(vec3(7, 7, 7)));
//    list[l++] = new xzRectangleCanHit(123, 423, 147, 412, 554, light);
//    vec3 center(400, 400, 200);
//    list[l++] = new sphereCanHit(vec3(260, 150, 45), 50, new dielectricMaterial(1.5));
//    list[l++] = new sphereCanHit(vec3(0, 150, 145), 50,
//                                 new metalMaterial(new constantTexture(vec3(0.8, 0.8, 0.9)), 10.0));
//
//    auto *boundary = new sphereCanHit(vec3(360, 150, 145), 70, new dielectricMaterial(1.5));
//    list[l++] = boundary;
//    list[l++] = new constantMedium(boundary, 0.2, new constantTexture(vec3(0.2, 0.4, 0.9)));
//    boundary = new sphereCanHit(vec3(0, 0, 0), 5000, new dielectricMaterial(1.5));
//    list[l++] = new constantMedium(boundary, 0.0001, new constantTexture(vec3(1.0, 1.0, 1.0)));
//
//
//    int w, h;
//    ppmLoader loadPPM{};
//    auto *pixx = loadPPM.pix("cap.ppm", w, h);
//    auto *emat = new diffuseMaterial_Lambertian(new imageTexture(pixx, w, h));
//
//
//    list[l++] = new sphereCanHit(vec3(400, 200, 400), 100, emat);
//
//    pixx = loadPPM.pix("w.ppm", w, h);
//    emat = new diffuseMaterial_Lambertian(new imageTexture(pixx, w, h));
//    list[l++] = new sphereCanHit(vec3(220, 280, 300), 80, emat);
//    int ns = 1000;
//    for (int j = 0; j < ns; j++) {
//        boxList2[j] = new sphereCanHit(vec3(165 * (rand() / (RAND_MAX + 1.0)), 165 * ((rand() / (RAND_MAX + 1.0))),
//                                            165 * (rand() / (RAND_MAX + 1.0))), 10, white);
//    }
//    list[l++] = new translate(new rotateY(new bvhNode(boxList2, ns, 0.0, 1.0), 15), vec3(-100, 270, 395));
//    return new canHitGenericList(list, l);
//
//    //return new bvhNode(list,l,0,0);
//
//}

camera makeCameraTri(float vFOV, float wH, vec3 z, float aperture, float distToFocus) {
    return {vFOV, wH, {278, 278, -800}, {278, 278, 0}, z, aperture, distToFocus, 0.0, 1.0};
}

camera makeCameraBox(float vFOV, float wH, vec3 z, float aperture, float distToFocus) {
    return {vFOV, wH, {278, 278, 4}, {278, 278, 0}, z, aperture, distToFocus, 0.0, 1.0};
}


canHitGeneric *makeTriangleScene() {
     auto **list = new canHitGeneric *[2];


     //Bullshit I tried to get it working, idk...

    //shared_ptr<canHitGeneric> **list(new canHitGeneric*[2]);
    //auto *list(reinterpret_cast<shared_ptr<canHitGeneric> *>(new canHitGeneric *[2]));
    //shared_ptr<canHitGeneric> **list(new canHitGeneric*[2]);
    int i = 0;
    shared_ptr<texture> cT(new constantTexture(vec3(1.0, 0.0, 0.0)));
    shared_ptr<material> red(new diffuseMaterial_Lambertian(cT));
    //shared_ptr<canHitGeneric> tr(new triangleCanHit(vec3(0, 0, -1), vec3(4, 0, -1), vec3(2, 2, -1), &red));

    //THIS BELOW LEAKS MEMORY - Change to 1280x640 to see Red Triangle being rendered, if uncommented.
    //Change to 20x10 for Valgrind, otherwise it's way too slow.
    list[i++] = new translate(new triangleCanHit(vec3(0, 0, -1), vec3(4, 0, -1), vec3(2, 2, -1), red),vec3(278,278,0));
   //ONLY TRY USING THE TRIANGLECANHIT, SPHERE ISN'T DONE, I THINK?
   //LIST NEEDS TO BE A shared_ptr otherwise it leaks memory
   //Got stuck here

//    list[i++] = new sphereCanHit(vec3(0, 0, -1), 0.5,
//                                 new diffuseMaterial_Lambertian(new constantTexture(vec3(0.1, 0.2, 0.5))));

    return new canHitGenericList(list, i);
}

//canHitGeneric *makeBunny() {
//    OBJ bunny("./bunny_centered.obj");
//    vector<vec3> bun = bunny.getFaceVertexVector();
////    std::cout << bun.size() << "\n";
//    auto **list = new canHitGeneric *[bun.size()];
//    material *red = new metalMaterial(new constantTexture(vec3(0.83, 0.686, 0.2156)), 0.0);
//    int k = 0;
////    for (unsigned int i = 0; i < bun.size(); i += 3) {
////        list[k++] = new triangleCanHit(bun.at(i), bun.at(i + 1), bun.at(i + 2), red);
////    }
//    return new bvhNode(list, k, 0, 0);
//}


int main() {
    //Valgrind command
    //valgrind --leak-check=full  ./lab

    //Anything with a regular pointer pretty much needs to be converted to a shared_ptr
    //Otherwise it will leak memory...
    //It's going to be a ton of work to convert and TEST - many bugs.


    ofstream myfile;
    myfile.open("test.ppm");

    //Size
    //LEAVE AT 20 by 10 for Valgrind, Change to 1280 by 640 for rendering checks

    //!!!!!!!!!!!!
    //If you change it to a value that's too low, you can get a segfault from the Progress Bar Code
    //!!!!!!!!!!!!

    int nx = 20;
    int ny = 10;
    //Anti-Aliasing Samples, Higher = Better = Slower
    //Higher Resolution means lower ns value is needed.
    int ns = 1;

    myfile << "P3\n" << nx << " " << ny << "\n255\n";

    canHitGeneric *world = makeTriangleScene();
    //makeBunny();//cornellHotBox2();
//            makeBunny();
//            makeTriangleScene();//cornellBox();//cornellLotsOfSpheres();//cornellHotBox();//cornellBox();//randomSceneGen();
    //camera(float vFOV, float aspect, vec3 lookFrom, vec3 lookAt, vec3 vUp, aperture, focus_dist)


    vec3 lookFrom(278, 278, -800);
    vec3 lookAt(278, 278, 0);
    float dist_to_focus = 10.0;//(lookFrom-lookAt).length();
    float aperture = 0.0;
    int vFOV = 40;

    camera cam = makeCameraBox(vFOV, float(nx) / float(ny), vec3(0, 1, 0), aperture, dist_to_focus);
    //camera cam(vFOV, float(nx) / float(ny), lookFrom, lookAt, vec3(0, 1, 0), aperture, dist_to_focus, 0.0, 1.0);

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
            //Put OpenMP For Loop HERE if wanted
            for (int s = 0; s < ns; s++) {
                //Implements Anti-Aliasing
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


    //REMEMBER TO FREE THE SPHERES
    myfile.close();
    delete world;

    return 0;
}