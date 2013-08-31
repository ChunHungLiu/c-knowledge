class cMath {
public:
    double Radians ( float Degrees );
    void AngleVectors ( const float angles[3], float* forward, float* right, float* up );
    void VectorCopy ( float v1[3], float v2[3] );
    void VectorSubtract ( float* v1, float* v2, float* out );
    void VectorAngles ( const float value1[3], float angles[3] );
    void VectorAdd ( float* v1, float* v2, float* v3 );
    float GetDistance ( float A[3], float B[3] );
};

extern cMath Math;
