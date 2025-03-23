#ifndef COMMON_FOG_INC
#define COMMON_FOG_INC

// Function prototype (declaration only)
float ComputeFogDensity(float3 worldPos, float density);
float HenyeyGreenstein(float cosTheta, float anisotropy);

#endif // COMMON_FOG_INC
