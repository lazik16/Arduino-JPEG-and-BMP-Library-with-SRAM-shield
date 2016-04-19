// 
// 
// 

#include "ColorTransform.h"

YCbCr ColorTransformClass::RGBToYCbCr(unsigned char R, unsigned char G, unsigned char B)
{
	float r, g, b;
	r = R;
	g = G;
	b = B;

	YCbCr ret;
	float p;

	p = 0.299 * r + 0.587 * g + 0.114 * b;
	ret.y = validateColor(p);
	p = -0.1687 * r - 0.3313 *g + 0.5 * b + 128.0;
	ret.cb = validateColor(p);
	p = 0.5*r - 0.4187 * g - 0.0813 * b + 128.0;
	ret.cr = validateColor(p);



	return ret;
}

RGB ColorTransformClass::YCbCrToRGB(unsigned char y, unsigned char cb, unsigned char cr)
{
	RGB ret;
	float p;
	int Cr = cr - 128;
	int Cb = cb - 128;

	p = y + 1.402 *  (float)(Cr);
	ret.r = validateColor(p);
	p = y - 0.34414 * (float)(Cb)-0.71414 * (float)(Cr);
	ret.g = validateColor(p);
	p = y + 1.772   * (float)(Cb);
	ret.b = validateColor(p);

	return ret;
}

unsigned char ColorTransformClass::validateColor(float value){
	if (value < 0)
		return 0;
	if (value > 255)
		return 255;
	else
		return (unsigned char)value;
}


ColorTransformClass ColorTransform;

