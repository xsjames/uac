//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================
//
//  UAC simple 3d vector implementation
//
//=============================================================================
#ifndef __UAC__VECTOR3_H
#define __UAC__VECTOR3_H

#include <stdlib.h>


namespace UAC
{
namespace Common
{

	//! 3d vector template class
	template <class T>
	class vector3
	{
	public:
		//! Default constructor (null vector).
		vector3() : X(0), Y(0), Z(0) {}
		//! Constructor with three different values.
		vector3(T nx, T ny, T nz) : X(nx), Y(ny), Z(nz) {}
		//! Constructor with the same value for all elements.
		explicit vector3(T n) : X(n), Y(n), Z(n) {}
		//! Copy constructor.
		vector3(const vector3<T>& other) : X(other.X), Y(other.Y), Z(other.Z) {}


		// operators

		vector3<T> operator-() const { return vector3<T>(-X, -Y, -Z); }

		vector3<T>& operator=(const vector3<T>& other) { X = other.X; Y = other.Y; Z = other.Z; return *this; }

		vector3<T> operator+(const vector3<T>& other) const { return vector3<T>(X + other.X, Y + other.Y, Z + other.Z); }
		vector3<T>& operator+=(const vector3<T>& other) { X+=other.X; Y+=other.Y; Z+=other.Z; return *this; }
		vector3<T> operator+(const T val) const { return vector3<T>(X + val, Y + val, Z + val); }
		vector3<T>& operator+=(const T val) { X+=val; Y+=val; Z+=val; return *this; }

		vector3<T> operator-(const vector3<T>& other) const { return vector3<T>(X - other.X, Y - other.Y, Z - other.Z); }
		vector3<T>& operator-=(const vector3<T>& other) { X-=other.X; Y-=other.Y; Z-=other.Z; return *this; }
		vector3<T> operator-(const T val) const { return vector3<T>(X - val, Y - val, Z - val); }
		vector3<T>& operator-=(const T val) { X-=val; Y-=val; Z-=val; return *this; }

		//! use weak float compare
		bool operator==(const vector3<T>& other) const
		{
			return this->equals(other);
		}

		bool operator!=(const vector3<T>& other) const
		{
			return !this->equals(other);
		}

		// functions

		//! returns if this vector equals the other one, taking floating point rounding errors into account
		bool equals(const vector3<T>& other, const T tolerance = (T)ROUNDING_ERROR_f32 ) const
		{
			return _equals(X, other.X, tolerance) &&
				_equals(Y, other.Y, tolerance) &&
				_equals(Z, other.Z, tolerance);
		}

		vector3<T>& set(const T nx, const T ny, const T nz) { X=nx; Y=ny; Z=nz; return *this; }
		vector3<T>& set(const vector3<T>& p) { X=p.X; Y=p.Y; Z=p.Z; return *this; }

		
		//! sets vector values reading from passed string
		//TODO - speedup using fast_atof
		void set(const char* text)
		{
			// parse text
			const char* P = text;

			// reset
			set(0, 0, 0);

			for(unsigned int i = 0; i < 3 && *P; ++i)
			{
				while(*P && P[0]!='-' && (P[0]==' ' || (P[0] < '0' || P[0] > '9')))
					++P;

				// set value
				if(*P)
				{
					if(i == 0)
						X = static_cast<float>(atof(P));
					else if(i == 1)
						Y = static_cast<float>(atof(P));
					else
						Z = static_cast<float>(atof(P));

					// skip values
					while(*P && (P[0]=='-' || (P[0]>='0' && P[0]<='9') || P[0]=='.' || P[0]=='e' || P[0]=='E'))
						++P;
				}
			}
		}


		//! X coordinate of the vector
		T X;

		//! Y coordinate of the vector
		T Y;

		//! Z coordinate of the vector
		T Z;


	protected:
		//! returns if a equals b, taking possible rounding errors into account
		inline bool _equals(const float a, const float b, const float tolerance = ROUNDING_ERROR_f32)
		{
			return (a + tolerance >= b) && (a - tolerance <= b);
		}
		//! returns if a equals b, taking an explicit rounding tolerance into account
		inline bool _equals(const int a, const int b, const int tolerance = 0)
		{
			return (a == b);
		}
	};


	//! Typedef for a float 3d vector.
	typedef vector3<float> vector3f;

	//! Typedef for an integer 3d vector.
	typedef vector3<int> vector3i;

} // namespace Common
} // namespace UAC

#endif // __UAC__VECTOR3_H
