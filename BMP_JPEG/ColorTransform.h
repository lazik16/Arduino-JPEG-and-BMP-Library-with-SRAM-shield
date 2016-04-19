// ColorTransform.h

#ifndef _COLORTRANSFORM_h
#define _COLORTRANSFORM_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Color.h"

class ColorTransformClass
{
 protected:


 public:
	 static YCbCr RGBToYCbCr(unsigned char R, unsigned char G, unsigned char B);
	 static RGB YCbCrToRGB(unsigned char y, unsigned char cb, unsigned char cr);
	 static unsigned char validateColor(float value);
};

extern ColorTransformClass ColorTransform;

#endif

