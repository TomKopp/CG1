//
// This source code is property of the Computer Graphics and Visualization
// chair of the TU Dresden. Do not distribute!
// Copyright (C) 2015 - 2017 CGV TU Dresden - All Rights Reserved
//
#version 130

in vec4 fragment_color;
in vec4 orig_position;
uniform vec2 julia_c;
uniform float julia_zoom;
out vec4 color;

void main(void)
{
	float a;
	vec2 z;
	// color = fragment_color*0.5 + vec4(0.5);

	z.x = orig_position.x * julia_zoom;
	z.y = orig_position.y * julia_zoom;

	int i;
    for(i = 0; i <= 200; i++) {
        float x = (z.x * z.x - z.y * z.y) + julia_c.x;
        float y = (z.y * z.x + z.x * z.y) + julia_c.y;

        if((x * x + y * y) > 4.0)
		{
			break;
		}

        z.x = x;
        z.y = y;
    }

	if (i < 200)
	{
		a = float(i)/200;
	}
	color = a * 10.0f * fragment_color;


//  *** Begin of tasks ***
// - 1.2.5
// Implement the pseudo-code for calculating the julia fractal at a point.
// To get the point you can declare a new "in" variable which contains the
// position and just use the X- and Y- value.


// *** End of tasks ***
}

