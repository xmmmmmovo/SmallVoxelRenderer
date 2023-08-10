#version 460 core

layout (location = 0) out vec4 vFragColor;    //fragment shader output

layout (location = 0) smooth in vec3 vUV;    //3D texture coordinates form vertex shader

//uniform
layout (location = 0) uniform sampler3D volume;

layout (std140, binding = 2) uniform Camera {
    vec4 cam_position;
    vec4 ray_step_size;
};

//constants
const int MAX_SAMPLES = 300;    //total samples for each ray march step
const vec3 texMin = vec3(0);    //minimum texture access coordinate
const vec3 texMax = vec3(1);    //maximum texture access coordinate
const float delta = 0.01;        //delta value for ray marching
const float isoValue = 40.0f / 255.0f;        //iso value for isosurface

//function to give a more accurate position of where the given iso-value (iso) is found
//given the initial minimum limit (left) and maximum limit (right)
vec3 bisection(vec3 left, vec3 right, float iso) {
    //loop 4 times
    for (int i = 0;i < 4; i++)
    {
        //get the mid value between the left and right limit
        vec3 midpoint = (right + left) * 0.5;
        //sample the texture at the middle point
        float cM = texture(volume, midpoint).x;
        //check if the value at the middle point is less than the given iso-value
        if (cM < iso) {
            //if so change the left limit to the new middle point
            left = midpoint;
        } else {
            //otherwise change the right limit to the new middle point
            right = midpoint;
        }

    }
    //finally return the middle point between the left and right limit
    return vec3(right + left) * 0.5;
}

vec3 getGradient(vec3 uvw) {
    //get the gradient in the x direction
    float dx = texture(volume, uvw - vec3(delta, 0, 0)).x - texture(volume, uvw + vec3(delta, 0, 0)).x;
    //get the gradient in the y direction
    float dy = texture(volume, uvw - vec3(0, delta, 0)).x - texture(volume, uvw + vec3(0, delta, 0)).x;
    //get the gradient in the z direction
    float dz = texture(volume, uvw - vec3(0, 0, delta)).x - texture(volume, uvw + vec3(0, 0, delta)).x;
    //return the gradient vector
    return normalize(vec3(dx, dy, dz) / 2.0f);
}

vec4 phongShading(vec3 L, vec3 N, vec3 V, float specPower, vec3 diffuseColor) {
    float diffuse = max(dot(L, N), 0.0);
    vec3 halfVec = normalize(L + V);
    float specular = pow(max(0.00001, dot(halfVec, N)), specPower);
    return vec4((diffuse * diffuseColor + specular), 1.0);
}

void main() {
    vec3 camPos = cam_position.xyz;
    vec3 step_size = ray_step_size.xyz;

    //get the 3D texture coordinates for lookup into the volume dataset
    vec3 dataPos = vUV;

    //Getting the ray marching direction:
    //get the object space position by subracting 0.5 from the
    //3D texture coordinates. Then subtraact it from camera position
    //and normalize to get the ray marching direction
    vec3 geomDir = normalize((vUV - vec3(0.5)) - camPos);

    //multiply the raymarching direction with the step size to get the
    //sub-step size we need to take at each raymarching step
    vec3 dirStep = geomDir * step_size;

    //flag to indicate if the raymarch loop should terminate
    bool stop = false;

    //for all samples along the ray
    for (int i = 0; i < MAX_SAMPLES; i++) {
        // advance ray by dirstep
        dataPos = dataPos + dirStep;

        //The two constants texMin and texMax have a value of vec3(-1,-1,-1)
        //and vec3(1,1,1) respectively. To determine if the data value is
        //outside the volume data, we use the sign function. The sign function
        //return -1 if the value is less than 0, 0 if the value is equal to 0
        //and 1 if value is greater than 0. Hence, the sign function for the
        //calculation (sign(dataPos-texMin) and sign (texMax-dataPos)) will
        //give us vec3(1,1,1) at the possible minimum and maximum position.
        //When we do a dot product between two vec3(1,1,1) we get the answer 3.
        //So to be within the dataset limits, the dot product will return a
        //value less than 3. If it is greater than 3, we are already out of
        //the volume dataset
        stop = dot(sign(dataPos - texMin), sign(texMax - dataPos)) < 3.0;

        //if the stopping condition is true we brek out of the ray marching loop
        if (stop) {
            break;
        }

        // data fetching from the red channel of volume texture
        float sample_color = texture(volume, dataPos).r;
        float sample_color_next = texture(volume, dataPos + dirStep).r;

        //In case of iso-surface rendering, we do not use compositing.
        //Instead, we find the zero crossing of the volume dataset iso function
        //by sampling two consecutive samples.
        if ((sample_color - isoValue) < 0 && (sample_color_next - isoValue) >= 0.0) {
            //If there is a zero crossing, we refine the detected iso-surface
            //location by using bisection based refinement.
            vec3 xN = dataPos;
            vec3 xF = dataPos + dirStep;
            vec3 tc = bisection(xN, xF, isoValue);

            //To get the shaded iso-surface, we first estimate the normal
            //at the refined position
            vec3 N = getGradient(tc);

            //The view vector is simply opposite to the ray marching
            //direction
            vec3 V = -geomDir;

            //We keep the view vector as the light vector to give us a head
            //light
            vec3 L = V;

            //Finally, we call PhongLighing function to get the final colour
            //with diffuse and specular components. Try changing this call to this
            //vFragColor =  PhongLighting(L,N,V,250,  tc); to get a multi colour
            //iso-surface
            vFragColor = phongShading(L, N, V, 250, vec3(0.5));
            break;
        }
    }
}