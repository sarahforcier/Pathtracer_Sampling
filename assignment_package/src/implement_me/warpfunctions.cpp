#define _USE_MATH_DEFINES
#include "warpfunctions.h"
#include <math.h>
#include "utils.h"

glm::vec3 WarpFunctions::squareToDiskUniform(const glm::vec2 &sample)
{
    float r = glm::sqrt(sample.x);
    float phi = 2.f * M_PI * sample.y;
    return glm::vec3(r * glm::cos(phi), r * glm::sin(phi), 0.f);
}

glm::vec3 WarpFunctions::squareToDiskConcentric(const glm::vec2 &sample)
{
    float r, phi;
    float a = 2.f * sample.x - 1.f; // map to [-1, 1]
    float b = 2.f * sample.y - 1.f;

    if (a > -b) {
        if (a > b) {
            r = a;
            phi = M_PI/4.f * b/a;
        } else {
            r = b;
            phi = M_PI/4.f * (2.f - a/b);
        }
    } else {
        if (a < b) {
            r = -a;
            phi = M_PI/4.f * (4.f + b/a);
        } else {
            r = -b;
            if (b != 0.f) phi = M_PI/4.f * (6.f - a/b);
            else phi = 0.f;
        }
    }

    return glm::vec3(r * glm::cos(phi), r * glm::sin(phi), 0.f);
}

float WarpFunctions::squareToDiskPDF(const glm::vec3 &sample)
{
    //TODO
    return 1/ M_PI;
}

glm::vec3 WarpFunctions::squareToSphereUniform(const glm::vec2 &sample)
{
    float z = 1.f - 2.f * sample.x;
    float r = glm::sqrt(glm::max(0.f, 1.f - z * z));
    float phi = 2.f * M_PI * sample.y;
    return glm::vec3(r * glm::cos(phi), r * glm::sin(phi), z);
}

float WarpFunctions::squareToSphereUniformPDF(const glm::vec3 &sample)
{
    return 1.f / (4.f * M_PI); //over area of radius 1
}

glm::vec3 WarpFunctions::squareToSphereCapUniform(const glm::vec2 &sample, float thetaMin)
{
    //TODO
    float z = 1.f - 2.f * sample.x/thetaMin;
    float r = glm::sqrt(glm::max(0.f, 1.f - z * z));
    float phi = 2.f * M_PI * sample.y;
    return glm::vec3(r * glm::cos(phi), r * glm::sin(phi), z);
}

float WarpFunctions::squareToSphereCapUniformPDF(const glm::vec3 &sample, float thetaMin)
{
    //TODO
    return INV_TWOPI / (1 - glm::cos(thetaMin)); //inverse area
}

glm::vec3 WarpFunctions::squareToHemisphereUniform(const glm::vec2 &sample)
{
    float r = glm::sqrt(glm::max(0.f, 1.f - sample.x * sample.x));
    float phi = 2 * M_PI * sample.y;
    return glm::vec3(r * glm::cos(phi), r * glm::sin(phi), sample.x);
}

float WarpFunctions::squareToHemisphereUniformPDF(const glm::vec3 &sample)
{
    return INV_TWOPI;
}

glm::vec3 WarpFunctions::squareToHemisphereCosine(const glm::vec2 &sample)
{
    glm::vec3 ret = squareToDiskConcentric(sample);
    ret.z = glm::sqrt(glm::max(0.f, 1.f - ret.x * ret.x - ret.y * ret.y));
    return ret;
}

float WarpFunctions::squareToHemisphereCosinePDF(const glm::vec3 &sample)
{
    //TODO
    float x = sample.x; float y = sample.y; float z = sample.z;
    float r = glm::sqrt(x*x + y*y + z*z);
    float costheta = z/r;
    return costheta * INV_PI;
}
