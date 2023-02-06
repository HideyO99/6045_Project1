#pragma once

typedef unsigned char uchar;

struct C24BitBMPpixel
{
public:
	C24BitBMPpixel();	// Default constructor - all zeros
	C24BitBMPpixel(uchar red, uchar green, uchar blue);
	~C24BitBMPpixel();
	uchar redPixel;
	uchar greenPixel;
	uchar bluePixel;
};

struct C32BitBMPpixel
{
public:
	C32BitBMPpixel();	// Default constructor - all zeros
	C32BitBMPpixel(uchar red, uchar green, uchar blue);
	C32BitBMPpixel(uchar red, uchar green, uchar blue, uchar aplha);
	~C32BitBMPpixel();
	uchar redPixel;
	uchar greenPixel;
	uchar bluePixel;
	uchar alphaPixel;
};
