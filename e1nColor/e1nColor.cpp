///////////////////////////////////////////////////////////////////////////////////////////////////////
//  e1nColor.cpp - Implementation file for the e1nColor library.
//
//  Created by Keith Goreham on 3/26/19.
//  Copyright © 2022 Kunst Logic LLC. All rights reserved.
///////////////////////////////////////////////////////////////////////////////////////////////////////

// Includes:
#include "lib/stdafx.h"
#include "lib/e1nColor/e1nColor.h"
#include <opencv2/opencv.hpp>               // Some functions require the OpenCV library.

// Preprocessor directives:
using namespace std;
using namespace cv;

//====================================================================================================
// Constructors:
//====================================================================================================

// Default
e1nColor::e1nColor()
{
    r = 0.0f;
    g = 0.0f;
    b = 0.0f;
    a = 1.0f;
}

// Single-Byte per channel RGB initialization.
e1nColor::e1nColor(const unsigned char rVal, const unsigned char gVal, const unsigned char bVal)
{
	r = rVal / 255.0f;		// Red
	g = gVal / 255.0f;		// Green
	b = bVal / 255.0f;		// Blue
	a = 1.0f;				// Alpha defaults to white.
}

e1nColor::e1nColor(const unsigned char rVal, const unsigned char gVal, const unsigned char bVal, const unsigned char aVal)     // Single-Byte per channel RGBA initialization.
{
	r = rVal / 255.0f;		// Red
	g = gVal / 255.0f;		// Green
	b = bVal / 255.0f;		// Blue
	a = aVal / 255.0f;		// Alpha
}

// RGB Floating-Point initialization.
e1nColor::e1nColor(const float rVal, const float gVal, const float bVal)
{
    r = rVal;                           // Red
    g = gVal;                           // Green
    b = bVal;                           // Blue
    a = 1.0;                            // Alpha Defaults To White.
}

// RGBA Floating-Point initialization.
e1nColor::e1nColor(const float rVal, const float gVal, const float bVal, const float aVal)
{
    r = rVal;                           // Red
    g = gVal;                           // Green
    b = bVal;                           // Blue
    a = aVal;                           // Alpha
}

// OpenCV Mat pixel initialization. Single-byte per channel RGB vector.
e1nColor::e1nColor(Vec3b &someRGB_888)
{
    r = someRGB_888[0] / 255.0f;        // Red
    g = someRGB_888[1] / 255.0f;        // Green
    b = someRGB_888[2] / 255.0f;        // Blur
    a = 1.0f;                           // Alpha Defaults to White
}

//====================================================================================================
// Destructor:
//====================================================================================================
e1nColor::~e1nColor()
{
    // Nothing Needed Yet.
}

//====================================================================================================
// Standard Object Maintenance:
//====================================================================================================

// Print operator overload. So we can cout the color.
ostream &operator <<(ostream &os, e1nColor &someColor)
{
	someColor.print(&os);
	return os;
}

// Print function (for debugging).
void e1nColor::print(ostream *os)
{
	float h = e1nColor::GetHue();
	float s = e1nColor::GetSat();
	float v = e1nColor::GetVal();
	
	cout << "\nRed: " << r << "  Green:" << g << "  Blue: " << b << " | Hue: " << h << "  Saturation: " << s << "  Value: " << v << "\n";
}

//====================================================================================================
// Member functions:
//====================================================================================================
// Functions to retrieve the maximum and minimum RGB component values:
//----------------------------------------------------------------------------------------------------

float e1nColor::GetMaxRGB()
{
    if      (r >= b && r >= g) {return r;}
    else if (g >= r && g >= b) {return g;}
    else                       {return b;}
}

float e1nColor::GetMinRGB()
{
    if      (r <= b && r <= g) {return r;}
    else if (g <= r && g <= b) {return g;}
    else                       {return b;}
}

//----------------------------------------------------------------------------------------------------
// Hue, Saturation, and Value Access Functions:
//----------------------------------------------------------------------------------------------------

float e1nColor::GetHue()                // Get the color's position on the hue wheel (such as red vs. orange or blue).
{
	// Find Min, Max, & Delta:
	float max   = GetMaxRGB();
	float min   = GetMinRGB();
	float delta = max - min;
	
	// Invert the color into its complement.
	float Rc;
	float Gc;
	float Bc;
	
	if (delta == 0.0f)
	{
		Rc = 0.0f;
		Gc = 0.0f;
		Bc = 0.0f;
	}
	else
	{
		Rc = (max - r) / delta;
		Gc = (max - g) / delta;
		Bc = (max - b) / delta;
	}
	
	// Calculate the color's 0-360º floating-point Hue.
	float h;
	
	if 		(r == max) {h = 60.0f * (Bc - Gc);}
	else if (g == max) {h = 60.0f * (2.0 + Rc - Bc);}
	else			   {h = 60.0f * (4.0 + Gc - Rc);}
	
	// Correct for negative results in the 300º - 359.9º (Magenta to Red) range.
	if (h < 0.0f){h = h + 360.0f;}
    
    // And reduce the 0-360º hue range to 0-1.
    h = h / 360.0f;
	
    return h;
}

float e1nColor::GetSat()                // Get the intensity of a color. It's hue-purity if you will.
{
    // Find Min, Max, & Delta:
    float max = GetMaxRGB();
    float min = GetMinRGB();
    
    // Calculate the 0-100 floating-point Saturation.
    float s = (max - min);
    
    return s;
}

float e1nColor::GetVal()                // Get the lightness (value) of a color.
{
    // Find Min, Max, & Delta:
    float max = GetMaxRGB();
    float min = GetMinRGB();
    
    // Calculate the 0-100 floating-point brightness Value.
    float v = ((max + min) / 2.0f);
    
    return v;
}

//----------------------------------------------------------------------------------------------------
// Hue, Saturation, and Value Assignment Functions:
//----------------------------------------------------------------------------------------------------

void e1nColor::SetHue(const float newHue)
{
    // ToDo
}

void e1nColor::SetSat(const float newSat)
{
    // ToDo
}


void e1nColor::SetVal(float newVal)
{
    // ToDo
}

//----------------------------------------------------------------------------------------------------
// Interoperability With The OpenCV Library:
//----------------------------------------------------------------------------------------------------

Vec3b e1nColor::GetVec3b()                      // Reads in a 3-byte OpenCV color from a Mat image.
{
    return { (unsigned char) (round(r * 255.0)),
             (unsigned char) (round(g * 255.0)),
             (unsigned char) (round(b * 255.0))} ;
}

//----------------------------------------------------------------------------------------------------
//     This function converts the RGB values to the HSL (Hue, Saturation, Lumenance) color space &
// then writes them to the RGB Channels. Note that HSL is FAR more more color-accurate than Adobe's
// HSV color space, as it doesn't confuse saturation with value, and has double the lumenance value
// granularity.
//----------------------------------------------------------------------------------------------------

void e1nColor::ConvertRGB2HLS()
{
    // Find Min, Max, & Delta:
    float max = GetMaxRGB();
    float min = GetMinRGB();
    float del = max - min;
    
    // Invert the color into its complement.
    float Rc;
    float Gc;
    float Bc;
    
    if (del == 0.0f)
    {
        Rc = 0.0f;
        Gc = 0.0f;
        Bc = 0.0f;
    }
    else
    {
        Rc = (max - r) / del;
        Gc = (max - g) / del;
        Bc = (max - b) / del;
    }
    
    // Calculate the 0-1 floating-point brightness Value.
    float v = ((max + min) / 2.0f);
    
    // Calculate the 0-1 floating-point Saturation.
    float s = del;
    
    // Calculate the color's 0-360º floating-point Hue.
    float h;
    
    if      (r == max) {h = 60.0f * (Bc - Gc);}
    else if (g == max) {h = 60.0f * (2.0 + Rc - Bc);}
    else               {h = 60.0f * (4.0 + Gc - Rc);}
    
    // Correct for negative results in the 300º - 359.9º (Magenta to Red) range.
    if (h < 0.0f){h = h + 360.0f;}
    
    // And reduce the 0-360º hue range to 0-1.
    h = h / 360.0f;
    
    // Assign the Value, Saturation, and Hue to the Red, Green, and Blue channels respectively.
    r = h;
    g = v;
    b = s;
}

//----------------------------------------------------------------------------------------------------
//     The inverse of the previous function, the HLS to RGB function allows for switching back and
// forth between the RGB & HSL color spaces freely in memory. Avoiding the need for image copies when
// working with very large multi-gigabyte source images.
//----------------------------------------------------------------------------------------------------

void e1nColor::ConvertHLS2RGB()
{
    float h = r;
    float v = g;
    float s = b;

    float min = ((2 * v) - s) * 0.5;
    float max = s + min;


    //float mid = 0.0f;

    if (s == 0)                                   // No Saturation? No Color.
    {
        r = v;
        g = v;
        b = v;
    }
    else
    {
        h = h * 360.0f;

        if (h >= 0.0f && h < 60.0f)               // Red To Yellow Range.
        {
            h = h / 60.0f;

            r = max;
            g = (h * s) + min;
            b = min;
        }
        else if (h >= 60.0f && h < 120.0f)        // Yellow to Green Range.
        {
            h = 1 - ((h - 60.0f) / 60.0f);

            r = (h * s) + min;
            g = max;
            b = min;
        }
        else if (h >= 120.0f && h < 180.0f)       // Green to Cyan Range.
        {
            h = (h - 120.0f) / 60.0f;

            r = min;
            g = max;
            b = (h * s) + min;
        }
        else if (h >= 180.0f && h < 240.0f)       // Cyan to Blue Range.
        {
            h = 1 - ((h - 180.0f) / 60.0f);

            r = min;
            g = (h * s) + min;
            b = max;
        }
        else if (h >= 240.0f && h < 300.0f)       // Blue to Magenta Range.
        {
            h = (h - 240.0f) / 60.0f;

            r = (h * s) + min;
            g = min;
            b = max;
        }
        else                                      // Magenta to Red Range.
        {
            h = 1 - ((h - 300.0f) / 60.0f);

            r = max;
            g = min;
            b = (h * s) + min;
        }
    }
}

//----------------------------------------------------------------------------------------------------
// Simple vector normalization function:
//----------------------------------------------------------------------------------------------------

void e1nColor::NormalizeRGB()
{
    float max = GetMaxRGB();
    
    float delta = 1.0f / max;
    
    r *= delta;
    g *= delta;
    b *= delta;
}

//----------------------------------------------------------------------------------------------------
// Color Blending Functions:
//----------------------------------------------------------------------------------------------------

// Todo: Masked blending functions that encapsulate Photoshop-like blending modes.
//
//      1) Opacity Blending
//      2) Alpha Blending
//      3) Color Multiplication
//      4) Color Screening
//      5) Overlay Blending
//      6) Hue Blending
//      7) Saturation Blending
//      8) Lighten Blending
//      9) Darken Blending
//
// These functions may also end up as part of a future e1nImage class.







