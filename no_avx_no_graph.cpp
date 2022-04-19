#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int Color;
const int BLACK = 1, WHITE = -1;

Color mondelbrot_point_color (float x0, float y0, const int screenWidth, const int screenHeight);

void draw_mondelbrot (const int screenWidth, const int screenHeight, float scale_factor);

int main ()
	{
	const int screenWidth = 600, screenHeight = 400;

	// Zoom and movement values
	float scale_factor = 0.01;

    clock_t t = clock();
	float fps = 0;

    size_t RUN_NUM = 100;

	for (int run_id = 0; run_id < RUN_NUM; run_id++)
		{
        draw_mondelbrot(screenWidth, screenHeight, scale_factor);
        }

    t = clock() - t;
	fps = (CLOCKS_PER_SEC * RUN_NUM) / (float) t ;

	printf("FPS: %f\n", fps);


	return 0;
	}


void draw_mondelbrot (const int screenWidth, const int screenHeight, float scale_factor)
	{
	// Draw pixels than belong Mondelbrot's set
	for (int y = 0; y < screenHeight; y++)
		{
		for (int x = 0; x < screenWidth; x++)
			{
            // Transform coords from left-conored coord system to centered one
            float scaled_x = (x - screenWidth / 2) * scale_factor;
            float scaled_y = (y - screenHeight / 2) * scale_factor;

            Color pixel_color = mondelbrot_point_color(scaled_x, scaled_y, screenWidth, screenHeight);
            }
		}
	}


// Count whether point belongs to the Mondelbrot set or not and return respective color
Color mondelbrot_point_color (float x0, float y0, const int screenWidth, const int screenHeight)
	{
	const size_t MAX_STEP = 256;
	const float MAX_R_SQUARE = 100.f;

	size_t step_id = 0;

	float x = x0, y = y0;

	for (; step_id < MAX_STEP; step_id++)
		{
		float xx = x * x;
		float xy = x * y;
		float yy = y * y;

		if (xx + yy > MAX_R_SQUARE)
			{
			break;
			}

		y = 2*xy + y0;
		x = xx - yy + x0;
        }

	return step_id == MAX_STEP? BLACK : WHITE;
	}
