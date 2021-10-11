#include <iostream>
#include <cstdint>
using namespace std;

typedef float F32;

inline uint32_t swapuint32_t(uint32_t value)

{

    return ((value & 0x000000FF) << 24)

        | ((value & 0x0000FF00) << 8)

        | ((value & 0x00FF0000) >> 8)

        | ((value & 0xFF000000) >> 24);
}

union uint32_tF32

{

    uint32_t m_asuint32_t;

    F32 m_asF32;

};

inline F32 swapF32(F32 value)

{

    uint32_tF32 u;

    u.m_asF32 = value;

    u.m_asuint32_t = swapuint32_t(u.m_asuint32_t);

    return u.m_asF32;

}


void showSwappedVersion(uint32_tF32& ex)

{

    char hex_string[20];


    uint32_tF32 result;

    result.m_asF32 = swapF32(ex.m_asF32);


    sprintf_s(hex_string, "%X", result.m_asuint32_t);

    cout << hex_string << endl;


}


void main() {

    uint32_tF32 data;

    data.m_asuint32_t = 0xABCD1234;

    showSwappedVersion(data);
}