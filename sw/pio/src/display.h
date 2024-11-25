#pragma once

#include <cstdint>

// 2024 svofski
// higher level display functions (see vfd.h for lower level)
// status display, logo animations, etc..
template<typename VFD>
class Display
{
private:
    VFD &vfd;

    int logo_y = 25;
    int logo_index = 0;
    int logo_frame = 0;
    int logo_frameskip = 0;
    int logo_delay = 0;
    bool logo_finished = false;
    char vfd_text[10];
    bool vfd_text_invalid;
    int vfd_dim_delay = 0;
    static constexpr int VFD_DIM_BRIGHT = 128;
    static constexpr int VFD_DIM_HALF = 64;
    static constexpr int VFD_DIM_IDLE = 0;

public:
    Display(VFD& _vfd) : vfd(_vfd)
    {
    }

    void init()
    {
        vfd.init();
        vfd.on(true);
        vfd.set_dimming(127);
    }

    char* text()
    {
        return static_cast<char*>(vfd_text);
    }

    void invalidate()
    {
        vfd_text_invalid = true;
    }

    void animate()
    {
        if (!logo_finished) {
            animate2();
        }
        else {
            update();
        }
    }

    void draw_glyph(int x, int y, char c)
    {
        extern const uint8_t font_data[];

        const uint8_t * srcbmp = (const uint8_t *) &font_data[c * 5];
        uint8_t bitmap[5];
        for (int i = 0; i < 5; ++i) {
            uint8_t bits = srcbmp[i];
            if (y > 0)
                bits <<= y;
            else if (y < 0)
                bits >>= -y;
            bitmap[i] = bits;
        }
        vfd.display_custom(x, bitmap, 5);
    }

    void animate2()
    {
        if (logo_finished) return;

        if (++logo_frameskip < 10) return;
        logo_frameskip = 0;

        int f8 = logo_frame >> 3;
        uint8_t addr = logo_frame % 8;

        static const char logo0[] {"PETOCTRL"};

        if (logo_delay) {
            --logo_delay;
            return;
        }

        draw_glyph(addr, logo_y, logo0[addr]);
        if (addr == 7) {
            logo_delay = 0;
            if (logo_y == 0) {
                logo_delay = 512;
            }
        }
        if (addr == 7) {
            logo_y -= 1;
        }

        if (logo_y == -32) {
            logo_finished = true;
        }

        logo_frame += 1;
    }

    void update()
    {
        static constexpr int DIM_FULLDELAY = 10000;
        static constexpr int DIM_TIME_HALF = DIM_FULLDELAY * 3 / 4;
        static constexpr int DIM_TIME_COOLDOWN = DIM_FULLDELAY / 2;
    
        if (vfd_dim_delay > 0) {
            --vfd_dim_delay;
            int dim;
            if (vfd_dim_delay >= DIM_TIME_HALF) {
                dim = VFD_DIM_BRIGHT;
            }
            else if (vfd_dim_delay >= DIM_TIME_COOLDOWN) {
                dim = VFD_DIM_HALF;
            }
            else {
                dim = VFD_DIM_IDLE * (DIM_TIME_COOLDOWN - vfd_dim_delay)
                    + VFD_DIM_HALF * vfd_dim_delay;
                dim = dim / DIM_TIME_COOLDOWN;
            }
            vfd.set_dimming(dim);
            if (vfd_dim_delay == 0) {
                vfd.set_dimming(VFD_DIM_IDLE);
            }
        }
    
        if (vfd_text_invalid) {
            vfd.display_cstr(0, vfd_text);
            vfd.set_dimming(VFD_DIM_BRIGHT);
            vfd_dim_delay = DIM_FULLDELAY;
            vfd_text_invalid = false;
        }
    }


};

#if 0
static void vfd_animate1()
{
    if (++logo_frameskip < 16) return;
    logo_frameskip = 0;

    int f8 = logo_frame >> 3;
    uint8_t addr = logo_frame % 8;

    static const char logo0[] {"PETOMANE"};
    static const char logo1[] {"CONTROLE"};
    static const char logo2[] {" CENTRE "};

    static const char *logos[] {logo0, logo1, logo2};
    static constexpr int N_LOGOS = 3;

    vfd_glyph(addr, logo_y, logos[logo_index][addr]);
    if (addr == 7) logo_y -= 1;

    if (logo_y == -7) {
        logo_y = 7;
        logo_index += 1;
        if (logo_index >= N_LOGOS) {
            logo_index = 0;
        }
    }

    logo_frame += 1;
}
#endif

