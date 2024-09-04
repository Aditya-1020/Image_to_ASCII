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


    int new_width = 100;
    int new_height = height * new_width / width; // maintains aspect ratio
    unsigned char *Resized_img = malloc(new_width * new_height * grey_channels);
    if (Resized_img == NULL){
        printf("Unable to resize image\n");
        free(grey_img);
        stbi_image_free(Img);
        return 1;
    }


    if (!stbir_resize_uint8_linear(grey_img, width, height, 0, Resized_img, new_width, new_height, 0, grey_channels)) {
        printf("Error resizing image\n");
        free(Resized_img);
        free(grey_img);
        stbi_image_free(Img);
        return 1;
    }


    /*
    map pixel brightness to ASCII chars " .:-=+*#%@"
    use str of char darkest to lightest 
    divide range of possible values (usually 0-255 for 8 bit greyscale)
    into as many secions as the charecters you have then map each value
    to its charecter
    */


    // Map pixel brightness to ASCII chars
    // Map pixel brightness to ASCII chars
    const char *ascii_chars = " .:-=+*#%@";
    int num_chars = 10;
    float segment_size = 256.0 / num_chars;

    // Create a buffer to store the ASCII art
    char *ascii_art = malloc(new_width * new_height + new_height); // extra space for newlines
    if (ascii_art == NULL) {
        printf("Unable to allocate memory for ASCII art\n");
        free(Resized_img);
        free(grey_img);
        stbi_image_free(Img);
        return 1;
    }

    char *art_ptr = ascii_art;
    for (int y = 0; y < new_height; ++y) {
        for (int x = 0; x < new_width; ++x) {
            int pixel_value = Resized_img[y * new_width + x];
            int char_index = (int)(pixel_value / segment_size);
            *art_ptr++ = ascii_chars[char_index];
        }
        *art_ptr++ = '\n';  // Newline at the end of each row
    }
    *art_ptr = '\0';  // Null-terminate the string

    // Print the ASCII art
    printf("%s\n", ascii_art);

    // Clean up
    free(ascii_art);
    free(Resized_img);
    free(grey_img);
    stbi_image_free(Img);




    return 0;
}

//https://github.com/JosefVesely/img2ascii/blob/main/src/ascii_art.h
