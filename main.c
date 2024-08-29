#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

int main(void) {
    // load image
    int width, height, channels;
    unsigned char *img = stbi_load("1980.png", &width, &height, &channels, 0);
    if (img == NULL) {
        printf("Error in loading the image\n");
        exit(1);
    }

    // convert to grayscale (ie: single channel)
    size_t img_size = width * height * channels;
    int gray_channels = channels == 4 ? 2 : 1;
    size_t gray_img_size = width * height * gray_channels;

    unsigned char *gray_img = malloc(gray_img_size);
    if (gray_img == NULL) {
        printf("Unable to allocate memory for gray image\n");
        exit(1);
    }

    for (unsigned char *p = img, *pg = gray_img; p != img + img_size; p += channels, pg += gray_channels) {
        *pg = (uint8_t)((*p + *(p + 1) + *(p + 2)) / 3.0);
        if (channels == 4) {
            *(pg + 1) = *(p + 3);
        }
    }
    
    stbi_write_png("1980_gray.png", width, height, gray_channels, gray_img, width * gray_channels);

    // Free allocated memory
    stbi_image_free(img);
    free(gray_img);

    printf("Image converted to gray");

    return 0;
}