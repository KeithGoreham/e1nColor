//////////////////////////////////////////////////////////////////////////////////////////////////////
// e1nColor.h - Interface definition file for the e1nColor library.
//
// ©2019 by Keith Goreham - keith@goreham.com
//////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef E1NCOLOR_H
#define E1NCOLOR_H

#pragma once

#include "lib/stdafx.h"                 // Precompiled headers.
#include <opencv2/opencv.hpp>           // OpenCV library.
#include <istream>
#include <ostream>
#include <cmath>

using namespace std;
using namespace cv;

// Constants:
#define PI 3.1415927f

//====================================================================================================
// e1nColor - A floating point RGB Color class focused on Hue, Saturation & Value Functionality:
//====================================================================================================

typedef class e1nColor
{
private:
	
    //----------------------------------------------------------------------------------------------------
    // Member variables:
    //----------------------------------------------------------------------------------------------------

    float r;            // The color's red component.
    float g;            // The color's green component.
    float b;            // The color's blue component.
    float a;            // The color's alpha component.

public:

    //----------------------------------------------------------------------------------------------------
    // Constructors & Destructors:
    //----------------------------------------------------------------------------------------------------

    // Default constructor.
    e1nColor();
	
    // Single-Byte per channel RGB & RGBA initialization constructors.
    e1nColor(const unsigned char rVal, const unsigned char gVal, const unsigned char bVal);
    e1nColor(const unsigned char rVal, const unsigned char gVal, const unsigned char bVal, const unsigned char aVal);
	
    // Floating-Point RGB & RGBA initialization constructors.
    e1nColor(const float rVal, const float gVal, const float bVal);
    e1nColor(const float rVal, const float gVal, const float bVal, const float aVal);
	
    // For reading directly from an OpenCV Mat.
    e1nColor(Vec3b &someRGB_888);

    // Destructor.
    ~e1nColor();
	
    //----------------------------------------------------------------------------------------------------
    // Operator overloads:
    //----------------------------------------------------------------------------------------------------

    e1nColor &operator =(const e1nColor &someColor);                    // Assignment Operator

    bool operator 	  ==(const e1nColor &someColor)const;               // Equality check.
    bool operator 	  !=(const e1nColor &someColor)const;               // Inequality check.

    void print(ostream *os);                                            // Print function (for debugging);
	
    //----------------------------------------------------------------------------------------------------
    // Functions to retrieve the maximum and minimum RGB component values:
    //----------------------------------------------------------------------------------------------------

	float GetMaxRGB();
	float GetMinRGB();
	
    //----------------------------------------------------------------------------------------------------
    // Red, Blue, and Green channel access functions:
    //----------------------------------------------------------------------------------------------------

    float         GetRedFloat();
    unsigned char GetRedByte();
	
    float         GetGreenFloat();
    unsigned char GetGreenByte();
	
    float         GetBlueFloat();
    unsigned char GetBlueByte();
    
    float         GetAlphaFloat();
    unsigned char GetAlphaByte();
    
    //----------------------------------------------------------------------------------------------------
    // Red, Blue, Green & Alpha channel assignment functions:
    //----------------------------------------------------------------------------------------------------

	void SetRed   (const float someFloat);
	void SetRed   (const unsigned char someByte);
	
    void SetGreen (const float someFloat);
    void SetGreen (const unsigned char someByte);
    
    void SetBlue  (const float someFloat);
    void SetBlue  (const unsigned char someByte);
    
    void SetAlpha (const float someFloat);
    void SetAlpha (const unsigned char someByte);
	
    //----------------------------------------------------------------------------------------------------
    // Hue, Saturation, and Value access functions:
    //----------------------------------------------------------------------------------------------------

	float GetHue();
	float GetSat();
	float GetVal();
	
    //----------------------------------------------------------------------------------------------------
    // Hue, Saturation, and Value assignment functions:
    //----------------------------------------------------------------------------------------------------

	void SetHue(const float newHue);
	void SetSat(const float newSat);
	void SetVal(const float newVal);

    //----------------------------------------------------------------------------------------------------
    // Functions to convert the RGB color to an HLS color space, and back again.
    //----------------------------------------------------------------------------------------------------

    void ConvertRGB2HLS();
    void ConvertHLS2RGB();

    //----------------------------------------------------------------------------------------------------
    // Misc. Functions.
    //----------------------------------------------------------------------------------------------------

    void NormalizeRGB();
    void PowRGB();
    void CopyAlphaToRGB();

    //----------------------------------------------------------------------------------------------------
    // Interoperability with OpenCV:
    //----------------------------------------------------------------------------------------------------

    Vec3b GetVec3b();
	
} e1nRGBf;

//====================================================================================================
//                                  Inline member functions.
//====================================================================================================
// Print operator overload. So we can cout the color.
//----------------------------------------------------------------------------------------------------

std::ostream &operator <<(std::ostream &os, e1nRGBf &someColor);

//----------------------------------------------------------------------------------------------------
// Assignment operator
//----------------------------------------------------------------------------------------------------

inline e1nColor &e1nColor::operator =(const e1nColor &someColor)
{
	r = someColor.r;
	g = someColor.g;
	b = someColor.b;
	
    return *this;		                                // Returns an lvalue reference (C++ standard).
}

//----------------------------------------------------------------------------------------------------
// Equality & inequality checks.
//----------------------------------------------------------------------------------------------------

inline bool e1nColor::operator ==(const e1nColor &someColor)
const{
	return  r == someColor.r && g == someColor.g && b == someColor.b;
}

// Inequality check.
inline bool e1nColor::operator !=(const e1nColor &someColor)
const{
	return  r != someColor.r || g != someColor.g || b != someColor.b;
}

//----------------------------------------------------------------------------------------------------
// Channel Access Functions:
//----------------------------------------------------------------------------------------------------

inline float 	     e1nColor::GetRedFloat()    {return (float) r;}
inline unsigned char e1nColor::GetRedByte()     {return (unsigned char) (round(r * 255.0));}

inline float	     e1nColor::GetGreenFloat()  {return (float) g;}
inline unsigned char e1nColor::GetGreenByte()   {return (unsigned char) (round(g * 255.0));}

inline float 	     e1nColor::GetBlueFloat()   {return (float) b;}
inline unsigned char e1nColor::GetBlueByte()    {return (unsigned char) (round(b * 255.0));}

inline float         e1nColor::GetAlphaFloat()  {return (float) a;}
inline unsigned char e1nColor::GetAlphaByte()   {return (unsigned char) (round(a * 255.0));}

//----------------------------------------------------------------------------------------------------
// Channel Assignment Functions:
//----------------------------------------------------------------------------------------------------

inline void e1nColor::SetRed   (const float someFloat)        {r = someFloat;}
inline void e1nColor::SetRed   (const unsigned char someByte) {r = (float) someByte / 255.0;}

inline void e1nColor::SetGreen (const float someFloat)        {g = someFloat;}
inline void e1nColor::SetGreen (const unsigned char someByte) {g = (float) someByte / 255.0;}

inline void e1nColor::SetBlue  (const float someFloat)        {b = someFloat;}
inline void e1nColor::SetBlue  (const unsigned char someByte) {b = (float) someByte / 255.0;}

inline void e1nColor::SetAlpha (const float someFloat)        {a = someFloat;}
inline void e1nColor::SetAlpha (const unsigned char someByte) {a = (float) someByte / 255.0;}

//----------------------------------------------------------------------------------------------------
// Misc.
//----------------------------------------------------------------------------------------------------

inline void e1nColor::CopyAlphaToRGB() {r = a; g = a; b = a;}


#endif     // E1NCOLOR_H
