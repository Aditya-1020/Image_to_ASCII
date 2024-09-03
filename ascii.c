/* chars on increasing brightness "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\|()1{}[]?-_+~<>i!lI;:,"^`'. " */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb/stb_image_resize2.h"


int main(void) {

    int width, height, channels;
    unsigned char *Img = stbi_load("homer.png", &width, &height, &channels, 0);
    if (Img == NULL){
        printf("error loading image");
        return 1;
    }

    // resize image
/*
    if (*resize_img){
        if (*Desired_width <= 0){
            printf("Must be greater than 0");
            return 1;
        } else if (*Desired_width > width){
            printf("cannot be more than original width");
            return 1;
        }
    }
*/
    // image to gray
    size_t img_size = width * height * channels;
    int grey_channels = channels == 4 ? 2 : 1;
    size_t grey_img_size = width * height * grey_channels;

    unsigned char *grey_img = malloc(grey_img_size);
    if (grey_img == NULL){ 
        printf("Unable to allocate memory");
    }

    for (unsigned char *p = Img, *pg = grey_img; p != Img + img_size; p += channels, pg += grey_channels) {
        *pg = (uint8_t)((*p + *(p + 1) + *(p + 2)) / 3.0);
        if (channels == 4) {
            *(pg + 1) = *(p + 3);
        }
    }

    stbi_write_png("homer_grey.png", width, height, grey_channels, grey_img, width * grey_channels);


    int new_width = 300;
    int new_height = height * new_width / width; // maintains aspect ratio
    unsigned char *Resized_img = malloc(new_width * new_height * grey_channels);
    if (Resized_img == NULL){
        printf("Unable to resize image\n");
        free(grey_img);
        stbi_image_free(Img);
        return 1;
    }

    if (!stbir_resize_uint8_linear(grey_img, width, height, 0, Resized_img, new_width, new_height, 0, grey_channels)){
        printf("Error resizing image");
        free(Resized_img);
        free(grey_img);
        stbi_image_free(Img);
        return 1;
    }
    
    if (!stbi_write_png("homer_resized_grayscale.png", new_width, new_height, grey_channels, Resized_img, new_width * grey_channels)) {
        printf("Error writing resized image\n");
    } else {
        printf("Resized image saved as 'resized_grayscale.png'\n");
    }

    // Don't forget to free allocated memory
    free(Resized_img);
    free(grey_img);
    stbi_image_free(Img);



    

    return 0;
}

//https://github.com/JosefVesely/img2ascii/blob/main/src/ascii_art.h
