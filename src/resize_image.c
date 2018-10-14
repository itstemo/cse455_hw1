#include <math.h>
#include "image.h"

float nn_interpolate(image im, float x, float y, int c)
{
    // YOUR CODE HERE
    // return 0;
    return im.data[(int) round(x) + im.w * (int) round(y) + im.w * im.h * c];
}

image nn_resize(image im, int w, int h)
{
    image ret = make_image(w, h,im.c);
    // YOUR CODE HERE

    // system of equations
    // aX + b = Y
    // a* -.5 + b = .5
    // a* X.w = ret.

    // 4 * 4 -> 7 * 7
    // new_x to old_x = old_x.width / new_x.width
    // new_y to old_y ?
    int i,j;
    float new_x, new_y, new_val;
    for (i = 0; i < w; i++){
        for(j = 0; j < h; j++){
            // get the new coordinates from system of equations
            for(int k = 0; k < im.c; k++){
                new_val = nn_interpolate(im, new_x, new_y, k);
                set_pixel(ret, i,j,k,new_val);
            }
        }
    }
}

float bilinear_interpolate(image im, float x, float y, int c)
{
    // YOUR CODE HERE
    int x_1, x_2, y_1, y_2;

    x_1 = (int) floor(x);
    x_2 = (int) ceil(x);
    y_1 = (int) floor(y);
    y_2 = (int) ceil(y);

    float R1, R2, P, Q11, Q21, Q12, Q22;

    Q11 = get_pixel(im, x_1, y_1, c);
    Q21 = get_pixel(im, x_2,y_2, c);
    Q12 = get_pixel(im, x_1, y_2, c);
    Q22 = get_pixel(im, x_2, y_2, c);
    R1 = ((x_2 - x) / (x_2 - x_1)) * Q11 + ((x - x_1)/(x_2 - x_1))*Q21;
    R2 = ((x_2 - x)/ (x_2 - x_1)) * Q12 + ((x-x_1)/(x_2-x_1))*Q22;
    P = ((y_2 - y) / (y_2 - y_1))* R1 + ((y - y_1)/(y_2 - y_1))* R2;

    return P;
}

image bilinear_resize(image im, int w, int h)
{
    image ret = make_image(w, h, im.c);
    // YOUR CODE HERE
    int i, j, k;
    float scaled_x, scaled_y, new_val;

    for(i = 0; i < w; i++){
        for(j = 0; j < h; j++){
            // get scaled coordinates
            for(k = 0; k < im.c; k++){
                new_val = bilinear_interpolate(im, scaled_x, scaled_y, k);
                set_pixel(ret, i,j, k, new_val);
            }
        }
    }
    return ret;
}

