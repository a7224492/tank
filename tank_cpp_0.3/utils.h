#ifndef UTILS_H
#define UTILS_H

/////////////////////////////////////////////////////////////////////////
//
//		File: Utils.h
//
//		Author: Mat Buckland
//
//		Desc: useful utilities
//
/////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <math.h>
#include <sstream>
#include <string>
#include <SDL/SDL.h>

using namespace std;

const int     MaxInt = (std::numeric_limits<int>::max)();
const double  MaxDouble = (std::numeric_limits<double>::max)();
const double  MinDouble = (std::numeric_limits<double>::min)();
const float   MaxFloat = (std::numeric_limits<float>::max)();
const float   MinFloat = (std::numeric_limits<float>::min)();

//compares two real numbers. Returns true if they are equal
inline bool isEqual(float a, float b)
{
	if (fabs(a - b) < 1E-12)
	{
		return true;
	}

	return false;
}

inline bool isEqual(double a, double b)
{
	if (fabs(a - b) < 1E-12)
	{
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------
//	some random number functions.
//-----------------------------------------------------------------------
inline int	  RandInt(int x,int y) {return rand()%(y-x+1)+x;}

inline double RandFloat()		   {return (rand())/(RAND_MAX+1.0);}

inline bool   RandBool()
{
	if (RandInt(0,1)) return true;

	else return false;
}

//returns a random float in the range -1 < n < 1
inline double RandomClamped()	   {return RandFloat() - RandFloat();}

//-----------------------------------------------------------------------
// useful string functions
//-----------------------------------------------------------------------

//int to string function
string itos(int arg);

inline bool isPointInRect(SDL_Rect *rect, int x, int y)
{
	if (!(rect->x > x || (rect->x+rect->w) < x || rect->y > y || (rect->y+rect->h) < y))
	{
		return true;
	}
	return false;
}

inline double angleToArc(double angle)
{
	return 3.14159265358979323846/180*angle;
}


#endif