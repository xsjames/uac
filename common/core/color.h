//=============================================================================
//
// UAC - Unknown Adventure Creator
//
//=============================================================================
//
//  UAC color implementation
//  Class representing a 32 bit ARGB color.
//  The color values for alpha, red, green, and blue are stored in a single unsigned int.
// 	Alpha is opacity, so 0 is fully transparent, 255 is fully opaque (solid).
//
//=============================================================================
#ifndef __UAC__COLOR_H
#define __UAC__COLOR_H


namespace UAC
{
namespace Common
{

	class Color
	{
	public:

		//! Constructor of the Color. Does nothing.
		Color()
			: color(0)
		{}

		//! Constructs the color from 4 values representing the alpha, red, green and blue component.
		Color(unsigned int a, unsigned int r, unsigned int g, unsigned int b)
			: color(((a & 0xff)<<24) | ((r & 0xff)<<16) | ((g & 0xff)<<8) | (b & 0xff))
		{}

		//! Constructs the color from a 32 bit value. Could be another color.
		Color(unsigned int c)
			: color(c)
		{}

		//! Returns the alpha component of the color.
		unsigned int getAlpha() const { return color>>24; }

		//! Returns the red component of the color.
		unsigned int getRed() const { return (color>>16) & 0xff; }

		//! Returns the green component of the color.
		unsigned int getGreen() const { return (color>>8) & 0xff; }

		//! Returns the blue component of the color.
		unsigned int getBlue() const { return color & 0xff; }


		//! Sets the alpha component of the Color.
		void setAlpha(unsigned int a) { color = ((a & 0xff)<<24) | (color & 0x00ffffff); }

		//! Sets the red component of the Color.
		void setRed(unsigned int r) { color = ((r & 0xff)<<16) | (color & 0xff00ffff); }

		//! Sets the green component of the Color.
		void setGreen(unsigned int g) { color = ((g & 0xff)<<8) | (color & 0xffff00ff); }

		//! Sets the blue component of the Color.
		void setBlue(unsigned int b) { color = (b & 0xff) | (color & 0xffffff00); }


		//! Sets all four components of the color at once.
		void set(unsigned int a, unsigned int r, unsigned int g, unsigned int b)
		{
			color = (((a & 0xff)<<24) | ((r & 0xff)<<16) | ((g & 0xff)<<8) | (b & 0xff));
		}
		void set(unsigned int col) { color = col; }

		//! Set all four components of the color reading from passed string
		void set(const char* text)
		{
			unsigned int c;
			if(sscanf(text, "%08x", &c) != 1)
				c = 0;
			set(c);
		}


		//! Compares the color to another color.
		bool operator==(const Color& other) const { return other.color == color; }

		//! Compares the color to another color.
		bool operator!=(const Color& other) const { return other.color != color; }


		//! color in A8R8G8B8 Format
		unsigned int color;
	};


} // namespace Common
} // namespace UAC

#endif // __UAC__COLOR_H
