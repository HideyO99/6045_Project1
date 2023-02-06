#include "C24BitBMPpixel.h"

C24BitBMPpixel::C24BitBMPpixel()
{
	redPixel = 0.f;
	greenPixel = 0.f;
	bluePixel = 0.f;
}

C24BitBMPpixel::C24BitBMPpixel(uchar red, uchar green, uchar blue)
{
	redPixel = red;
	greenPixel = green;
	bluePixel = blue;
}

C24BitBMPpixel::~C24BitBMPpixel()
{
}

C32BitBMPpixel::C32BitBMPpixel()
{
	redPixel = 0.f;
	greenPixel = 0.f;
	bluePixel = 0.f;
	alphaPixel = 1.f;
}

C32BitBMPpixel::C32BitBMPpixel(uchar red, uchar green, uchar blue)
{
	redPixel = red;
	greenPixel = green;
	bluePixel = blue;
	alphaPixel = 1.f;
}

C32BitBMPpixel::C32BitBMPpixel(uchar red, uchar green, uchar blue, uchar aplha)
{
	redPixel = red;
	greenPixel = green;
	bluePixel = blue;
	alphaPixel = aplha;
}

C32BitBMPpixel::~C32BitBMPpixel()
{
}
