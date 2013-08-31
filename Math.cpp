#include "main.h"

cMath Math;

#define M_PI 3.14159265358979323846

double cMath::Radians ( float Degrees ) {
    return  0.01745329238474369 * Degrees;
}

void cMath::AngleVectors ( const float angles[3], float* forward, float* right, float* up ) {
    float angle;
    static float sr, sp, sy, cr, cp, cy, cpi = ( M_PI * 2 / 360 );

    angle = angles[1] * cpi;
    sy = sin ( angle );
    cy = cos ( angle );
    angle = angles[0] * cpi;
    sp = sin ( angle );
    cp = cos ( angle );
    angle = angles[2] * cpi;
    sr = sin ( angle );
    cr = cos ( angle );

    if ( forward ) {
        forward[0] = cp * cy;
        forward[1] = cp * sy;
        forward[2] = -sp;
    }

    if ( right ) {
        right[0] = ( -1 * sr * sp * cy + -1 * cr * -sy );
        right[1] = ( -1 * sr * sp * sy + -1 * cr * cy );
        right[2] = -1 * sr * cp;
    }

    if ( up ) {
        up[0] = ( cr * sp * cy + -sr * -sy );
        up[1] = ( cr * sp * sy + -sr * cy );
        up[2] = cr * cp;
    }
}

void cMath::VectorCopy ( float v1[3], float v2[3] ) {
    v2[0] = v1[0];
    v2[1] = v1[1];
    v2[2] = v1[2];
}

void cMath::VectorSubtract ( float* v1, float* v2, float* out ) {
    out[0] = v1[0] - v2[0];
    out[1] = v1[1] - v2[1];
    out[2] = v1[2] - v2[2];
}

void cMath::VectorAngles ( const float value1[3], float angles[3] ) {
    float   forward;
    float   yaw, pitch;

    if ( value1[1] == 0 && value1[0] == 0 ) {
        yaw = 0;
        if ( value1[2] > 0 ) {
            pitch = 90;
        } else {
            pitch = 270;
        }
    } else {
        if ( value1[0] ) {
            yaw = ( atan2 ( value1[1], value1[0] ) * 180 / M_PI );
        } else if ( value1[1] > 0 ) {
            yaw = 90;
        } else {
            yaw = 270;
        }
        if ( yaw < 0 ) {
            yaw += 360;
        }

        forward = sqrt ( value1[0] * value1[0] + value1[1] * value1[1] );
        pitch = ( atan2 ( value1[2], forward ) * 180 / M_PI );
        if ( pitch < 0 ) {
            pitch += 360;
        }
    }

    angles[0] = -pitch;
    angles[1] = yaw;
    angles[2] = 0;
}

void cMath::VectorAdd ( float* v1, float* v2, float* v3 ) {
    v3[0] = v1[0] * 2 + v2[0];
    v3[1] = v1[1] * 2 + v2[1];
    v3[2] = v1[2] * 2 + v2[2];
}

float cMath::GetDistance ( float A[3], float B[3] ) {
    float dx = A[0] - B[0];
    float dy = A[1] - B[1];
    float dz = A[2] - B[2];

    return ( float ) sqrt ( ( dx * dx ) + ( dy * dy ) + ( dz * dz ) ) * 0.03048f;
}