#pragma once

class Color
{
public:
	int r;
	int g;
	int b;
	Color(int r, int g, int b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
	}

	Color Lerp(Color c, float t)
	{
		return Color(
			(int)(r + (c.r - r) * t),
			(int)(g + (c.g - g) * t),
			(int)(b + (c.b - b) * t)
		);
	}

	Color operator+(Color c)
	{
		return Color(r + c.r, g + c.g, b + c.b);
	}
	
	Color operator-(Color c)
	{
		return Color(r - c.r, g - c.g, b - c.b);
	}

	Color operator*(Color c)
	{
		return Color(r * c.r, g * c.g, b * c.b);
	}

	Color operator*(int c)
	{
		return Color(r * c, g * c, b * c);
	}

	Color operator/(Color c)
	{
		return Color(r / c.r, g / c.g, b / c.b);
	}

	Color operator/(int c)
	{
		return Color(r / c, g / c, b / c);
	}

	Color operator=(Color c)
	{
		r = c.r;
		g = c.g;
		b = c.b;
		return *this;
	}

	Color operator+=(Color c)
	{
		r += c.r;
		g += c.g;
		b += c.b;
		return *this;
	}

	Color operator-=(Color c)
	{
		r -= c.r;
		g -= c.g;
		b -= c.b;
		return *this;
	}

	Color operator*=(Color c)
	{
		r *= c.r;
		g *= c.g;
		b *= c.b;
		return *this;
	}

	Color operator*=(int c)
	{
		r *= c;
		g *= c;
		b *= c;
		return *this;
	}

	Color operator/=(Color c)
	{
		r /= c.r;
		g /= c.g;
		b /= c.b;
		return *this;
	}

	Color operator/=(int c)
	{
		r /= c;
		g /= c;
		b /= c;
		return *this;
	}

	bool operator==(Color c)
	{
		return r == c.r && g == c.g && b == c.b;
	}

	bool operator!=(Color c)
	{
		return r != c.r || g != c.g || b != c.b;
	}
public:
	static Color DefaultForgroundColor;
	static Color DefaultBackgroundColor;
	static Color Rainbow(double ratio);
};

class Vector2
{
public:
	static Vector2 Zero;
	int x;
	int y;
	Vector2(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	bool operator==(Vector2 v)
	{
		return x == v.x && y == v.y;
	}

	bool operator!=(Vector2 v)
	{
		return x != v.x || y != v.y;
	}
};

class Rect
{
public:
	int x;
	int y;
	int w;
	int h;
	Rect(int x, int y, int w, int h)
	{
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}
};