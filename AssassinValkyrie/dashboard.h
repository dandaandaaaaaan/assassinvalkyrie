//  Module:             Gameplay Programming
//  Assignment2:        LET IT RAIN
//  Student Name:       Timothy Chua
//  Student Number:     10165581F

#ifndef _DASHBOARD_H 
#define _DASHBOARD_H
#define WIN32_LEAN_AND_MEAN

#include "image.h"
#include "constants.h"

namespace dashboardNS
{
	const int   WIDTH = 403;      
	const int   HEIGHT = 32;
	const int   TEXTURE_COLS = 1;
	const int   BAR_FRAME = 8;
}

class Bar : public Image
{
private:
	int originalHealth;

public:
    bool initialize(Graphics *graphics, TextureManager *textureM, int left, int top,
                    float scale, int total_health);
    // Set Bar Size
    void setSize(int health);
};

#endif

