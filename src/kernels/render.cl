R"(

__constant float EPSILON = 0.00003f; /* required to compensate for limited float precision */
__constant float PI = 3.14159265359f;

// LIBRARY

typedef float *mat4_t;

mat4_t mat4_set(mat4_t mat, mat4_t dest) {
    dest[0] = mat[0];
    dest[1] = mat[1];
    dest[2] = mat[2];
    dest[3] = mat[3];
    dest[4] = mat[4];
    dest[5] = mat[5];
    dest[6] = mat[6];
    dest[7] = mat[7];
    dest[8] = mat[8];
    dest[9] = mat[9];
    dest[10] = mat[10];
    dest[11] = mat[11];
    dest[12] = mat[12];
    dest[13] = mat[13];
    dest[14] = mat[14];
    dest[15] = mat[15];
    return dest;
}

mat4_t mat4_identity(mat4_t dest) {
    dest[0] = 1;
    dest[1] = 0;
    dest[2] = 0;
    dest[3] = 0;
    dest[4] = 0;
    dest[5] = 1;
    dest[6] = 0;
    dest[7] = 0;
    dest[8] = 0;
    dest[9] = 0;
    dest[10] = 1;
    dest[11] = 0;
    dest[12] = 0;
    dest[13] = 0;
    dest[14] = 0;
    dest[15] = 1;
    return dest;
}

mat4_t mat4_transpose(mat4_t mat, mat4_t dest) {
    // If we are transposing ourselves we can skip a few steps but have to cache some values
    if (!dest || mat == dest) {
        float a01 = mat[1], a02 = mat[2], a03 = mat[3],
            a12 = mat[6], a13 = mat[7],
            a23 = mat[11];

        mat[1] = mat[4];
        mat[2] = mat[8];
        mat[3] = mat[12];
        mat[4] = a01;
        mat[6] = mat[9];
        mat[7] = mat[13];
        mat[8] = a02;
        mat[9] = a12;
        mat[11] = mat[14];
        mat[12] = a03;
        mat[13] = a13;
        mat[14] = a23;
        return mat;
    }

    dest[0] = mat[0];
    dest[1] = mat[4];
    dest[2] = mat[8];
    dest[3] = mat[12];
    dest[4] = mat[1];
    dest[5] = mat[5];
    dest[6] = mat[9];
    dest[7] = mat[13];
    dest[8] = mat[2];
    dest[9] = mat[6];
    dest[10] = mat[10];
    dest[11] = mat[14];
    dest[12] = mat[3];
    dest[13] = mat[7];
    dest[14] = mat[11];
    dest[15] = mat[15];
    return dest;
}

mat4_t mat4_inverse(mat4_t mat, mat4_t dest) {
    if (!dest) { dest = mat; }

    // Cache the matrix values (makes for huge speed increases!)
    float a00 = mat[0], a01 = mat[1], a02 = mat[2], a03 = mat[3],
        a10 = mat[4], a11 = mat[5], a12 = mat[6], a13 = mat[7],
        a20 = mat[8], a21 = mat[9], a22 = mat[10], a23 = mat[11],
        a30 = mat[12], a31 = mat[13], a32 = mat[14], a33 = mat[15],

        b00 = a00 * a11 - a01 * a10,
        b01 = a00 * a12 - a02 * a10,
        b02 = a00 * a13 - a03 * a10,
        b03 = a01 * a12 - a02 * a11,
        b04 = a01 * a13 - a03 * a11,
        b05 = a02 * a13 - a03 * a12,
        b06 = a20 * a31 - a21 * a30,
        b07 = a20 * a32 - a22 * a30,
        b08 = a20 * a33 - a23 * a30,
        b09 = a21 * a32 - a22 * a31,
        b10 = a21 * a33 - a23 * a31,
        b11 = a22 * a33 - a23 * a32,

        d = (b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06),
        invDet;

        // Calculate the determinant
        if (!d) { return NULL; }
        invDet = 1 / d;

    dest[0] = (a11 * b11 - a12 * b10 + a13 * b09) * invDet;
    dest[1] = (-a01 * b11 + a02 * b10 - a03 * b09) * invDet;
    dest[2] = (a31 * b05 - a32 * b04 + a33 * b03) * invDet;
    dest[3] = (-a21 * b05 + a22 * b04 - a23 * b03) * invDet;
    dest[4] = (-a10 * b11 + a12 * b08 - a13 * b07) * invDet;
    dest[5] = (a00 * b11 - a02 * b08 + a03 * b07) * invDet;
    dest[6] = (-a30 * b05 + a32 * b02 - a33 * b01) * invDet;
    dest[7] = (a20 * b05 - a22 * b02 + a23 * b01) * invDet;
    dest[8] = (a10 * b10 - a11 * b08 + a13 * b06) * invDet;
    dest[9] = (-a00 * b10 + a01 * b08 - a03 * b06) * invDet;
    dest[10] = (a30 * b04 - a31 * b02 + a33 * b00) * invDet;
    dest[11] = (-a20 * b04 + a21 * b02 - a23 * b00) * invDet;
    dest[12] = (-a10 * b09 + a11 * b07 - a12 * b06) * invDet;
    dest[13] = (a00 * b09 - a01 * b07 + a02 * b06) * invDet;
    dest[14] = (-a30 * b03 + a31 * b01 - a32 * b00) * invDet;
    dest[15] = (a20 * b03 - a21 * b01 + a22 * b00) * invDet;

    return dest;
}

mat4_t mat4_toRotationMat(mat4_t mat, mat4_t dest) {
    dest[0] = mat[0];
    dest[1] = mat[1];
    dest[2] = mat[2];
    dest[3] = mat[3];
    dest[4] = mat[4];
    dest[5] = mat[5];
    dest[6] = mat[6];
    dest[7] = mat[7];
    dest[8] = mat[8];
    dest[9] = mat[9];
    dest[10] = mat[10];
    dest[11] = mat[11];
    dest[12] = 0;
    dest[13] = 0;
    dest[14] = 0;
    dest[15] = 1;

    return dest;
}

float3 mat4_multiplyVec3(mat4_t mat, float3 vec) {

    float x = vec.x, y = vec.y, z = vec.z;
    
    float3 dest;

    dest.x = mat[0] * x + mat[4] * y + mat[8] * z + mat[12];
    dest.y = mat[1] * x + mat[5] * y + mat[9] * z + mat[13];
    dest.z = mat[2] * x + mat[6] * y + mat[10] * z + mat[14];

    return dest;
}

float4 mat4_multiplyVec4(mat4_t mat, float4 vec) {

    float x = vec.x, y = vec.y, z = vec.z, w = vec.w;

    float4 dest;

    dest.x = mat[0] * x + mat[4] * y + mat[8] * z + mat[12] * w;
    dest.y = mat[1] * x + mat[5] * y + mat[9] * z + mat[13] * w;
    dest.z = mat[2] * x + mat[6] * y + mat[10] * z + mat[14] * w;
    dest.w = mat[3] * x + mat[7] * y + mat[11] * z + mat[15] * w;

    return dest;
}

mat4_t mat4_translate(mat4_t mat, float3 vec, mat4_t dest) {
    float x = vec.x, y = vec.y, z = vec.z,
        a00, a01, a02, a03,
        a10, a11, a12, a13,
        a20, a21, a22, a23;

    if (!dest || mat == dest) {
        mat[12] = mat[0] * x + mat[4] * y + mat[8] * z + mat[12];
        mat[13] = mat[1] * x + mat[5] * y + mat[9] * z + mat[13];
        mat[14] = mat[2] * x + mat[6] * y + mat[10] * z + mat[14];
        mat[15] = mat[3] * x + mat[7] * y + mat[11] * z + mat[15];
        return mat;
    }

    a00 = mat[0]; a01 = mat[1]; a02 = mat[2]; a03 = mat[3];
    a10 = mat[4]; a11 = mat[5]; a12 = mat[6]; a13 = mat[7];
    a20 = mat[8]; a21 = mat[9]; a22 = mat[10]; a23 = mat[11];

    dest[0] = a00; dest[1] = a01; dest[2] = a02; dest[3] = a03;
    dest[4] = a10; dest[5] = a11; dest[6] = a12; dest[7] = a13;
    dest[8] = a20; dest[9] = a21; dest[10] = a22; dest[11] = a23;

    dest[12] = a00 * x + a10 * y + a20 * z + mat[12];
    dest[13] = a01 * x + a11 * y + a21 * z + mat[13];
    dest[14] = a02 * x + a12 * y + a22 * z + mat[14];
    dest[15] = a03 * x + a13 * y + a23 * z + mat[15];
    return dest;
}

mat4_t mat4_scale(mat4_t mat, float3 vec, mat4_t dest) {
    float x = vec.x, y = vec.y, z = vec.z;

    if (!dest || mat == dest) {
        mat[0] *= x;
        mat[1] *= x;
        mat[2] *= x;
        mat[3] *= x;
        mat[4] *= y;
        mat[5] *= y;
        mat[6] *= y;
        mat[7] *= y;
        mat[8] *= z;
        mat[9] *= z;
        mat[10] *= z;
        mat[11] *= z;
        return mat;
    }

    dest[0] = mat[0] * x;
    dest[1] = mat[1] * x;
    dest[2] = mat[2] * x;
    dest[3] = mat[3] * x;
    dest[4] = mat[4] * y;
    dest[5] = mat[5] * y;
    dest[6] = mat[6] * y;
    dest[7] = mat[7] * y;
    dest[8] = mat[8] * z;
    dest[9] = mat[9] * z;
    dest[10] = mat[10] * z;
    dest[11] = mat[11] * z;
    dest[12] = mat[12];
    dest[13] = mat[13];
    dest[14] = mat[14];
    dest[15] = mat[15];
    return dest;
}

)"
R"(

mat4_t mat4_rotate(mat4_t mat, float angle, float3 axis, mat4_t dest) {
    float x = axis.x, y = axis.y, z = axis.z,
        len = sqrt(x * x + y * y + z * z),
        s, c, t,
        a00, a01, a02, a03,
        a10, a11, a12, a13,
        a20, a21, a22, a23,
        b00, b01, b02,
        b10, b11, b12,
        b20, b21, b22;

    if (!len) { return NULL; }
    if (len != 1) {
        len = 1 / len;
        x *= len;
        y *= len;
        z *= len;
    }

    s = sin(angle);
    c = cos(angle);
    t = 1 - c;

    a00 = mat[0]; a01 = mat[1]; a02 = mat[2]; a03 = mat[3];
    a10 = mat[4]; a11 = mat[5]; a12 = mat[6]; a13 = mat[7];
    a20 = mat[8]; a21 = mat[9]; a22 = mat[10]; a23 = mat[11];

    // Construct the elements of the rotation matrix
    b00 = x * x * t + c; b01 = y * x * t + z * s; b02 = z * x * t - y * s;
    b10 = x * y * t - z * s; b11 = y * y * t + c; b12 = z * y * t + x * s;
    b20 = x * z * t + y * s; b21 = y * z * t - x * s; b22 = z * z * t + c;

    if (!dest) {
        dest = mat;
    } else if (mat != dest) { // If the source and destination differ, copy the unchanged last row
        dest[12] = mat[12];
        dest[13] = mat[13];
        dest[14] = mat[14];
        dest[15] = mat[15];
    }

    // Perform rotation-specific matrix multiplication
    dest[0] = a00 * b00 + a10 * b01 + a20 * b02;
    dest[1] = a01 * b00 + a11 * b01 + a21 * b02;
    dest[2] = a02 * b00 + a12 * b01 + a22 * b02;
    dest[3] = a03 * b00 + a13 * b01 + a23 * b02;

    dest[4] = a00 * b10 + a10 * b11 + a20 * b12;
    dest[5] = a01 * b10 + a11 * b11 + a21 * b12;
    dest[6] = a02 * b10 + a12 * b11 + a22 * b12;
    dest[7] = a03 * b10 + a13 * b11 + a23 * b12;

    dest[8] = a00 * b20 + a10 * b21 + a20 * b22;
    dest[9] = a01 * b20 + a11 * b21 + a21 * b22;
    dest[10] = a02 * b20 + a12 * b21 + a22 * b22;
    dest[11] = a03 * b20 + a13 * b21 + a23 * b22;
    return dest;
}

mat4_t mat4_rotateX(mat4_t mat, float angle, mat4_t dest) {
    float s = sin(angle),
        c = cos(angle),
        a10 = mat[4],
        a11 = mat[5],
        a12 = mat[6],
        a13 = mat[7],
        a20 = mat[8],
        a21 = mat[9],
        a22 = mat[10],
        a23 = mat[11];

    if (!dest) {
        dest = mat;
    } else if (mat != dest) { // If the source and destination differ, copy the unchanged rows
        dest[0] = mat[0];
        dest[1] = mat[1];
        dest[2] = mat[2];
        dest[3] = mat[3];

        dest[12] = mat[12];
        dest[13] = mat[13];
        dest[14] = mat[14];
        dest[15] = mat[15];
    }

    // Perform axis-specific matrix multiplication
    dest[4] = a10 * c + a20 * s;
    dest[5] = a11 * c + a21 * s;
    dest[6] = a12 * c + a22 * s;
    dest[7] = a13 * c + a23 * s;

    dest[8] = a10 * -s + a20 * c;
    dest[9] = a11 * -s + a21 * c;
    dest[10] = a12 * -s + a22 * c;
    dest[11] = a13 * -s + a23 * c;
    return dest;
}

mat4_t mat4_rotateY(mat4_t mat, float angle, mat4_t dest) {
    float s = sin(angle),
        c = cos(angle),
        a00 = mat[0],
        a01 = mat[1],
        a02 = mat[2],
        a03 = mat[3],
        a20 = mat[8],
        a21 = mat[9],
        a22 = mat[10],
        a23 = mat[11];

    if (!dest) {
        dest = mat;
    } else if (mat != dest) { // If the source and destination differ, copy the unchanged rows
        dest[4] = mat[4];
        dest[5] = mat[5];
        dest[6] = mat[6];
        dest[7] = mat[7];

        dest[12] = mat[12];
        dest[13] = mat[13];
        dest[14] = mat[14];
        dest[15] = mat[15];
    }

    // Perform axis-specific matrix multiplication
    dest[0] = a00 * c + a20 * -s;
    dest[1] = a01 * c + a21 * -s;
    dest[2] = a02 * c + a22 * -s;
    dest[3] = a03 * c + a23 * -s;

    dest[8] = a00 * s + a20 * c;
    dest[9] = a01 * s + a21 * c;
    dest[10] = a02 * s + a22 * c;
    dest[11] = a03 * s + a23 * c;
    return dest;
}

mat4_t mat4_rotateZ(mat4_t mat, float angle, mat4_t dest) {
    float s = sin(angle),
        c = cos(angle),
        a00 = mat[0],
        a01 = mat[1],
        a02 = mat[2],
        a03 = mat[3],
        a10 = mat[4],
        a11 = mat[5],
        a12 = mat[6],
        a13 = mat[7];

    if (!dest) {
        dest = mat;
    } else if (mat != dest) { // If the source and destination differ, copy the unchanged last row
        dest[8] = mat[8];
        dest[9] = mat[9];
        dest[10] = mat[10];
        dest[11] = mat[11];

        dest[12] = mat[12];
        dest[13] = mat[13];
        dest[14] = mat[14];
        dest[15] = mat[15];
    }

    // Perform axis-specific matrix multiplication
    dest[0] = a00 * c + a10 * s;
    dest[1] = a01 * c + a11 * s;
    dest[2] = a02 * c + a12 * s;
    dest[3] = a03 * c + a13 * s;

    dest[4] = a00 * -s + a10 * c;
    dest[5] = a01 * -s + a11 * c;
    dest[6] = a02 * -s + a12 * c;
    dest[7] = a03 * -s + a13 * c;

    return dest;
}

mat4_t mat4_frustum(float left, float right, float bottom, float top, float near, float far, mat4_t dest) {
    float rl = (right - left),
        tb = (top - bottom),
        fn = (far - near);
    dest[0] = (near * 2) / rl;
    dest[1] = 0;
    dest[2] = 0;
    dest[3] = 0;
    dest[4] = 0;
    dest[5] = (near * 2) / tb;
    dest[6] = 0;
    dest[7] = 0;
    dest[8] = (right + left) / rl;
    dest[9] = (top + bottom) / tb;
    dest[10] = -(far + near) / fn;
    dest[11] = -1;
    dest[12] = 0;
    dest[13] = 0;
    dest[14] = -(far * near * 2) / fn;
    dest[15] = 0;
    return dest;
}

)"
R"(

mat4_t mat4_perspective(float fovy, float aspect, float near, float far, mat4_t dest) {
    float top = near * tan(fovy * 3.14159265358979323846 / 360.0),
        right = top * aspect;
    return mat4_frustum(-right, right, -top, top, near, far, dest);
}

mat4_t mat4_ortho(float left, float right, float bottom, float top, float near, float far, mat4_t dest) {
    float rl = (right - left),
        tb = (top - bottom),
        fn = (far - near);
    dest[0] = 2 / rl;
    dest[1] = 0;
    dest[2] = 0;
    dest[3] = 0;
    dest[4] = 0;
    dest[5] = 2 / tb;
    dest[6] = 0;
    dest[7] = 0;
    dest[8] = 0;
    dest[9] = 0;
    dest[10] = -2 / fn;
    dest[11] = 0;
    dest[12] = -(left + right) / rl;
    dest[13] = -(top + bottom) / tb;
    dest[14] = -(far + near) / fn;
    dest[15] = 1;
    return dest;
}

mat4_t mat4_lookAt(float3 eye, float3 center, float3 up, mat4_t dest) {

    double x0, x1, x2, y0, y1, y2, z0, z1, z2, len,
        eyex = eye.x,
        eyey = eye.y,
        eyez = eye.z,
        upx = up.x,
        upy = up.y,
        upz = up.z,
        centerx = center.x,
        centery = center.y,
        centerz = center.z;

    if (eyex == centerx && eyey == centery && eyez == centerz) {
        return mat4_identity(dest);
    }

    //vec3.direction(eye, center, z);
    z0 = eyex - centerx;
    z1 = eyey - centery;
    z2 = eyez - centerz;

    // normalize (no check needed for 0 because of early return)
    len = 1 / sqrt(z0 * z0 + z1 * z1 + z2 * z2);
    z0 *= len;
    z1 *= len;
    z2 *= len;

    //vec3.normalize(vec3.cross(up, z, x));
    x0 = upy * z2 - upz * z1;
    x1 = upz * z0 - upx * z2;
    x2 = upx * z1 - upy * z0;
    len = sqrt(x0 * x0 + x1 * x1 + x2 * x2);
    if (!len) {
        x0 = 0;
        x1 = 0;
        x2 = 0;
    } else {
        len = 1 / len;
        x0 *= len;
        x1 *= len;
        x2 *= len;
    }

    //vec3.normalize(vec3.cross(z, x, y));
    y0 = z1 * x2 - z2 * x1;
    y1 = z2 * x0 - z0 * x2;
    y2 = z0 * x1 - z1 * x0;

    len = sqrt(y0 * y0 + y1 * y1 + y2 * y2);
    if (!len) {
        y0 = 0;
        y1 = 0;
        y2 = 0;
    } else {
        len = 1 / len;
        y0 *= len;
        y1 *= len;
        y2 *= len;
    }

    dest[0] = x0;
    dest[1] = y0;
    dest[2] = z0;
    dest[3] = 0;
    dest[4] = x1;
    dest[5] = y1;
    dest[6] = z1;
    dest[7] = 0;
    dest[8] = x2;
    dest[9] = y2;
    dest[10] = z2;
    dest[11] = 0;
    dest[12] = -(x0 * eyex + x1 * eyey + x2 * eyez);
    dest[13] = -(y0 * eyex + y1 * eyey + y2 * eyez);
    dest[14] = -(z0 * eyex + z1 * eyey + z2 * eyez);
    dest[15] = 1;

    return dest;
}

static float GetRandom(unsigned int *seed0, unsigned int *seed1) {

	/* hash the seeds using bitwise AND operations and bitshifts */
	*seed0 = 36969 * ((*seed0) & 65535) + ((*seed0) >> 16);
	*seed1 = 18000 * ((*seed1) & 65535) + ((*seed1) >> 16);

	unsigned int ires = ((*seed0) << 16) + (*seed1);

	/* use union struct to convert int to float */
	union {
		float f;
		unsigned int ui;
	} res;

	res.ui = (ires & 0x007fffff) | 0x40000000;  /* bitwise AND, bitwise OR */
	return (res.f - 2.0f) / 2.0f;
}

)"
R"(

typedef struct Ray
{
	float3 origin;
	float3 direction;
	float3 color;
} Ray;

enum CameraType
{
    Perspective,
    Orthographic,
    Panoramic
};

typedef struct Camera
{
    float3 position;
    float3 direction;
    float3 up;
    float fov;
    float width;
    float height;
    enum CameraType type;
} Camera;

typedef struct Material
{
    float3 color;
    float3 emission;

    float reflectivity;
    float roughness;
} Material;

typedef struct Collision
{
    float distance;
    float3 position;
    float3 normal;
    Material* material;
} Collision;

typedef struct Sphere 
{
	float radius;
	float3 position;
    Material* material;
} Sphere;

int IntersectSphere(const Sphere* sphere, const Ray* ray, Collision* collision)
{
	float3 rayToCenter = sphere->position - ray->origin;
	float b = dot(rayToCenter, ray->direction);
	float c = dot(rayToCenter, rayToCenter) - sphere->radius * sphere->radius;
	float disc = b * b - c;

	if (disc < 0.0f) return 0;
	else disc = sqrt(disc);

    float distance;

	if ((b - disc) > EPSILON) 
        distance = b - disc;
	else if ((b + disc) > EPSILON) 
        distance = b + disc;
    else
        return 0;

    collision->distance = distance;
    collision->position =  ray->origin + ray->direction * distance;
    collision->normal = normalize(collision->position - sphere->position);

	return 1;
}

int IntersectScene(const Ray* ray, Collision* collision, Sphere* spheres, int sphereCount)
{
    Collision newCollision;
    int hasHit = 0;
    collision->distance = 1000000.0f;
    collision->normal = (float3)(1.0f, 0.0f, 0.0f);
    for (int i=0; i<sphereCount; i++)
    {
        int hit = IntersectSphere(&(spheres[i]), ray, &newCollision);
        if (hit && collision->distance > newCollision.distance)
        {
            collision->distance = newCollision.distance;
            collision->position = newCollision.position;
            collision->normal = newCollision.normal;
            collision->material = spheres[i].material;
            hasHit = 1;
        }
    }
    return hasHit;
}

void GenerateRay(Camera* camera, int x, int y, Ray* ray)
{
    if (camera->type == Panoramic)
    {
        float angle = camera->fov/(float)(camera->width - 1);
         
        float a = y - (((float)(camera->height) - 1.0f)/2.0f);
                
        float3 right = cross(camera->up, camera->direction);

        float rotMat[16];
        mat4_identity(rotMat);
            
        mat4_rotate(rotMat, angle*a, right, rotMat);
        float3 rotVert = mat4_multiplyVec3(rotMat, camera->direction);
        a = x - (((float)(camera->width) - 1.0f)/2.0f);
                
        mat4_identity(rotMat);
        mat4_rotate(rotMat, angle*a, camera->up, rotMat);

        ray->direction = mat4_multiplyVec3(rotMat, rotVert);
        ray->color = (float3)(1.0f,1.0f,1.0f);
        ray->origin = camera->position;
    }
    else if (camera->type == Orthographic)
    {
        float aspect = (float)(camera->width)/(float)(camera->height);
        float scale = camera->fov/(float)camera->width;
            
        float mat[16];
        mat4_lookAt((float3)(0.0f,0.0f,0.0f), -camera->direction, camera->up, mat);

        float cx = (x - (float)(camera->width - 1)/2.0f) * scale;
        float cy = -(y - (float)(camera->height - 1)/2.0f) * scale;

        ray->color = (float3)(1.0f,1.0f,1.0f);
        ray->direction = normalize(camera->direction);
        ray->origin = mat4_multiplyVec3(mat, (float3)(cx,cy,0.0f)) + camera->position;
    }
    else if (camera->type == Perspective)
    {
        float aspect = (float)(camera->width)/(float)(camera->height);
        float scale = tan(camera->fov * 0.5);
        
        float cx = ((2.0f * ((float)(x) / (float)(camera->width))) - 1.0f) * aspect * scale;
        float cy = (1.0f - (2.0f * ((float)(y) / (float)(camera->height)))) * scale;

        float mat[16];
        mat4_lookAt((float3)(0.0f,0.0f,0.0f), -camera->direction, camera->up, mat);
        float3 dir = mat4_multiplyVec3(mat, (float3)(cx,cy,1.0f));
                   
        ray->color = (float3)(1.0f,1.0f,1.0f);
        ray->direction = normalize(dir);
        ray->origin = camera->position;  
    }
}

__kernel void Render(int tileSize, int tileX, int tileY, __global float* output)
{
    int width = 1920;
    int height = 1080;

	Camera camera;
	camera.position = (float3)(0.0f, 0.0f, -5.0f);
    camera.direction = (float3)(0.0f, 0.0f, 1.0f);
    camera.up = (float3)(0.0f, 1.0f, 0.0f);
	camera.width = width;
	camera.height = height;
	camera.fov = 20.0f;
	camera.type = Orthographic;// Perspective;

    Material materials[4];
    materials[0].color = (float3)(1.0f,0.5f,0.5f);
    materials[0].emission = (float3)(0.0f,0.0f,0.0f);
    materials[0].roughness = 0.0f;
    materials[0].reflectivity = 0.0f;
    materials[1].color = (float3)(0.5f,1.0f,0.5f);
    materials[1].emission = (float3)(0.0f,0.0f,0.0f);
    materials[1].roughness = 0.0f;
    materials[1].reflectivity = 0.0f;
    materials[2].color = (float3)(0.0f,0.0f,0.0f);
    materials[2].emission = (float3)(1.0f,1.0f,1.0f) * 100;
    materials[2].roughness = 0.0f;
    materials[2].reflectivity = 0.0f;
    materials[3].color = (float3)(1.0f,1.0f,1.0f) * 0.9f;
    materials[3].emission = (float3)(0.0f,0.0f,0.0f);
    materials[3].roughness = 0.0f;
    materials[3].reflectivity = 1.0f;

    Sphere spheres[4];
    spheres[0].position = (float3)(-1.0f, 0.0f, 0.0f);
    spheres[0].radius = 1.0f;
    spheres[0].material = &materials[0];
    spheres[1].position = (float3)(1.0f, 0.0f, 0.0f);
    spheres[1].radius = 1.0f;
    spheres[1].material = &materials[1];
    spheres[2].position = (float3)(0.0f, 5.0f, -3.0f);
    spheres[2].radius = 0.3f;
    spheres[2].material = &materials[2];
    spheres[3].position = (float3)(0.0f, -1002.0f, 0.0f);
    spheres[3].radius = 1000.0f;
    spheres[3].material = &materials[3];

	int id = get_global_id(0);
    int ix = id%tileSize;
    int iy = id/tileSize;

    int x = tileX + ix;
    int y = tileY + iy;
    int index = ((y * width) + x) * 4;

    if (x >= width || y >= height)
	{
		return;
	}

    float4 accumulatedColor = (float4)(0.0f,0.0f,0.0f,0.0f);             

    unsigned int seed0 = x;
    unsigned int seed1 = y;

    int sampleCount = 4096;
    for (int sample=0; sample<sampleCount; sample++)
    {
		Ray ray;
		GenerateRay(&camera, x, y, &ray);

            
        //accumulatedColor = (float4)((ray.direction + 1.0f) / 2.0f, 1.0f) * sampleCount;
        //break;

        Collision collision;

        float4 mask = (float4)(1.0f,1.0f,1.0f,1.0f);
        for (int bounce=0; bounce<8; bounce++)
        {
            int hit = IntersectScene(&ray, &collision, spheres, 4);
            if (hit)
            {
                accumulatedColor += mask * (float4)(collision.material->emission,1.0f);

                if (GetRandom(&seed0, &seed1) > collision.material->reflectivity)
                {
                    // Diffuse

                    /* compute two random numbers to pick a random point on the hemisphere above the hitpoint*/
                    float rand1 = 2.0f * PI * GetRandom(&seed0, &seed1);
                    float rand2 = GetRandom(&seed0, &seed1);
                    float rand2s = sqrt(rand2);

                    float3 w = collision.normal;
                    float3 axis = fabs(w.x) > 0.1f ? (float3)(0.0f, 1.0f, 0.0f) : (float3)(1.0f, 0.0f, 0.0f);
                    float3 u = normalize(cross(axis, w));
                    float3 v = cross(w, u);

                    ray.direction = normalize(u * cos(rand1)*rand2s + v*sin(rand1)*rand2s + w*sqrt(1.0f - rand2));
                    ray.origin = collision.position + (collision.normal * EPSILON);
                }
                else
                {
                    // Reflect
                    /* compute two random numbers to pick a random point on the hemisphere above the hitpoint*/
                    float rand1 = 2.0f * PI * GetRandom(&seed0, &seed1);
                    float rand2 = GetRandom(&seed0, &seed1);
                    float rand2s = sqrt(rand2) * collision.material->roughness;

                    float3 w = collision.normal;
                    float3 axis = fabs(w.x) > 0.1f ? (float3)(0.0f, 1.0f, 0.0f) : (float3)(1.0f, 0.0f, 0.0f);
                    float3 u = normalize(cross(axis, w));
                    float3 v = cross(w, u);

                    ray.direction = normalize(u * cos(rand1)*rand2s + v*sin(rand1)*rand2s + w*sqrt(1.0f - rand2));
                    ray.origin = collision.position + (collision.normal * EPSILON);
                }

                mask *= (float4)(collision.material->color, 1.0f);
               

            }
            else
            {
                if (bounce == 0)
                {
                    accumulatedColor = (float4)(0.1f,0.1f,0.1f,0.0f);
                }
                else
                {
                    accumulatedColor += mask * (float4)(0.1f,0.1f,0.1f,1.0f);
                }
                break;
            }
        }
    }

    accumulatedColor /= (float)sampleCount;

	output[index] = accumulatedColor.x;
	output[index + 1] = accumulatedColor.y;
	output[index + 2] = accumulatedColor.z;
	output[index + 3] = accumulatedColor.w;
}

)"