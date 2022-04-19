#include "include/raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <immintrin.h>

// Why intrinsics dont work on Virtual Machine?

const int AVX_SIZE = 8;

Color* mondelbrot_point_color_avx (Color* pixel_colors, float x0, float y0, float dx);

void draw_mondelbrot_avx (const int screenWidth, const int screenHeight,
                          float scale_factor, float shift_x, float shift_y);

int main ()
	{
	const int screenWidth = 600, screenHeight = 400;
	InitWindow(screenWidth, screenHeight, "My dear Mondelbrot...");

	// Draw FPS
	char StringFPS[10] = {};
	sprintf(StringFPS,"%d", GetFPS());
	DrawText(StringFPS, 0, 0, 20, VIOLET);

	// Zoom and movement values
	float scale_factor = 0.01, shift_x = 0, shift_y = 0;
	const float shift_factor = 0.2; // percentage of screen to be shifted during movement
	bool show_controls = true;

	while (!WindowShouldClose())
		{
		BeginDrawing();

			ClearBackground(RAYWHITE);

			// Check if user wants zoom in/out
			if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
				{
				scale_factor = scale_factor / 2;
				}
			else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
				{
				scale_factor = scale_factor * 2;
				}


			// User interface
			if (IsKeyPressed(KEY_ESCAPE))
				{
				break;
				}
			else if (IsKeyPressed(KEY_LEFT))
				{
				shift_x -= screenWidth * shift_factor * scale_factor;
				}
			else if (IsKeyPressed(KEY_RIGHT))
				{
				shift_x += screenWidth * shift_factor * scale_factor;
				}
			else if (IsKeyPressed(KEY_UP))
				{
				shift_y -= screenHeight * shift_factor * scale_factor;
				}
			else if (IsKeyPressed(KEY_DOWN))
				{
				shift_y += screenHeight * shift_factor * scale_factor;
				}

            draw_mondelbrot_avx(screenWidth, screenHeight, scale_factor, shift_x, shift_y);

			if (show_controls)
				{
				DrawText("Press LEFT/RIGHT MOUSE BUTTON to zoom out/in", 10, 10, 15, GREEN);
				DrawText("Press LEFT/RIGHT/UP/DOWN KEYS to displace respectively", 10, 30, 15, GREEN);
				}

			// Draw FPS
			char StringFPS[5] = {};
			sprintf(StringFPS,"%d", GetFPS());
			DrawText(StringFPS, 0, 0, 20, VIOLET);

		EndDrawing();
		}
	CloseWindow();

	return 0;
	}


void draw_mondelbrot_avx (const int screenWidth, const int screenHeight,
                          float scale_factor, float shift_x, float shift_y)
	{
	size_t RUN_NUM = 10;

	// clock_t t = clock(), t0;
	// float iter_time = 0;

	for (int run_id = 0; run_id < RUN_NUM; run_id++)
		{
		// Draw pixels that belong Mondelbrot's set

        // Count 8 points at once
		for (int y = 0; y < screenHeight; y++)
			{
			for (int x = 0; x < screenWidth; x = x + AVX_SIZE)
				{
				Color pixel_colors[AVX_SIZE] = {};

				// Transform coords from left-conored coord system to centered one
				float scaled_x = (x - screenWidth / 2) * scale_factor + shift_x;
                float scaled_y = (y - screenHeight / 2) * scale_factor + shift_y;

				mondelbrot_point_color_avx (pixel_colors, scaled_x, scaled_y, scale_factor);

				for (size_t pixel_shift = 0; pixel_shift < AVX_SIZE; pixel_shift++)
                    {
                    DrawPixel(x + pixel_shift, y, pixel_colors[pixel_shift]);
                    }
				}
			}
		}
	// t = clock() - t;
	// iter_time = (CLOCKS_PER_SEC * RUN_NUM) / (float) t ;

	// printf("FPS: %f\n", iter_time);
	}


// Count whether point belongs to the Mondelbrot set or not and return respective color
Color* mondelbrot_point_color_avx (Color* pixel_colors, float x0_f, float y0_f, float dx_f)
	{
	const size_t MAX_STEP = 256;

    __m256i N = _mm256_setzero_si256(); // Exit-step counters

	__m256 MAX_R2    = _mm256_set1_ps(100.f);
    __m256 x0        = _mm256_set1_ps(x0_f);
    __m256 y0        = _mm256_set1_ps(y0_f);
    __m256 _76543210 = _mm256_set_ps(7, 6, 5, 4, 3, 2, 1, 0); // Specific of 256 storage
    __m256 dx        = _mm256_set1_ps(dx_f);
    __m256 x         = _mm256_add_ps(_mm256_mul_ps(dx, _76543210), x0);
    __m256 y         = _mm256_set1_ps(y0_f);
    x0 = _mm256_add_ps(_mm256_mul_ps(dx, _76543210), x0);


    size_t step_id = 0;

	for (;step_id < MAX_STEP; step_id++)
		{
		__m256 xx = _mm256_mul_ps(x, x),
               xy = _mm256_mul_ps(x, y),
               yy = _mm256_mul_ps(y, y);


        // x^2 + y^2 < MAX_R^2                           lower than----\/
        __m256 cmp = _mm256_cmp_ps(_mm256_add_ps(xx, yy), MAX_R2, _CMP_LT_OS);

        /*
        If point is farther than R, cmp command will return 0 in respective position,
        else cmp command will return 0xFFFFFFFF.

        During integers subtraction f.ex: a - b
        b is translated into 2's complement
        then usual sum is computed

        2's complement to 0xFFFFFFF is 0x00000001

        so with this command we just increase counter, if LT
        and do nothing in other way
        */
        N = _mm256_sub_epi32(N, _mm256_castps_si256(cmp));

        // Create mask from the most significant bits of cmp elements
        int mask = _mm256_movemask_ps(cmp);

		if (!mask)
			{
			break;
			}

		y = _mm256_add_ps(_mm256_add_ps(xy, xy), y0);
		x = _mm256_add_ps(_mm256_sub_ps(xx, yy), x0);
		}

    int* exit_step = (int*) &N;

    // Draw pixels
    for (int pixel_id = 0; pixel_id < AVX_SIZE; pixel_id++)
        {
        if (exit_step[pixel_id] == MAX_STEP)
            {
            pixel_colors[pixel_id] = YELLOW;
            }
        else
            {
            pixel_colors[pixel_id] = BLUE;
            }
        }

    return pixel_colors;
	}
