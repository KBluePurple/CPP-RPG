#include "Type.h"
#include "GlobalStd.h"

Color Color::DefaultForgroundColor = Color(0, 0, 0);
Color Color::DefaultBackgroundColor = Color(255, 255, 255);

Color Color::Rainbow(double ratio)
{
	int normalized = int(ratio * 256 * 6);

	int region = normalized / 256;

	int x = normalized % 256;

	uint8_t red = 0, green = 0, blue = 0;
	switch (region)
	{
	case 0: red = 255; green = 0;   blue = 0;   green += x; break;
	case 1: red = 255; green = 255; blue = 0;   red -= x; break;
	case 2: red = 0;   green = 255; blue = 0;   blue += x; break;
	case 3: red = 0;   green = 255; blue = 255; green -= x; break;
	case 4: red = 0;   green = 0;   blue = 255; red += x; break;
	case 5: red = 255; green = 0;   blue = 255; blue -= x; break;
	}
	return Color(red, green, blue);
}

Vector2 Vector2::Zero = Vector2(0, 0);