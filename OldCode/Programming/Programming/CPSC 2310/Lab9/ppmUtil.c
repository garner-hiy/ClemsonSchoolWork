/**************************
*AJ Garner*
*CPSC 2310 Spring 23 *
*UserName: adgarne*
*Instructor: Dr. Yvon Feaster *
*email: adgarne@clemson.edu*
*************************/
#include "ppmUtil.h"

//This function will take the image file and the head pointer
//then it will simply call readheader and return the readPixels function
pixel_t* read(FILE* image, header_t* head_data){
    readHeader(image, head_data);
    return readPixels(image, *head_data);
}

//This function will take in the image file and the head pointer
void readHeader(FILE* image, header_t* head_data){
    //file scan the type
    fscanf(image, "%s\n", head_data->type);
    //check for comments
    ckComment(image);
    //repeat for the rest of the header data
    fscanf(image, "%d\n", &head_data->width);
    ckComment(image);
    fscanf(image, "%d\n", &head_data->height);
    ckComment(image);
    fscanf(image, "%d\n", &head_data->maxVal);
    ckComment(image);
}

//This function will check for comments
//It will iterate through the file and move the pointer where needed
void ckComment(FILE* image){

    //char a is used to move the pointer
    char a = fgetc(image);
    while(a == ' '|| a == '#'){
        if(a =='#'){
            while(a != '\n'&& a != EOF){

                //this will update the pointer to move along 
                a = fgetc(image);
            }
        }
        a = fgetc(image);
    }
    //this will move the pointer to the first character
    fseek(image, -1, SEEK_CUR);
}

//this will read all the data for the RGB in the image
pixel_t* readPixels(FILE* image, header_t head_data){
    //this is a function call to allocate the memory needed
    pixel_t* pixels = allocatePixMemory(head_data);
    //this reads in all the RGB data
    fread(pixels, sizeof(pixel_t), head_data.width * head_data.height, image);
    return pixels;
}

//This will call the functions needed to write the data
void write(FILE* outImage, header_t head_data, pixel_t* pixels){
    writeHeader(outImage, head_data);
    writePixels(outImage, pixels, head_data);
}

//This will write the data from the header to the file
void writeHeader(FILE* outImage, header_t head_data){
    fprintf(outImage, "%s\n", head_data.type);
    fprintf(outImage, "%d\n%d\n%d\n", 
    head_data.width, head_data.height, head_data.maxVal);
}

//This will write the pixels to the output file
void writePixels(FILE* outImage, pixel_t* pixels, header_t head_data){
    fwrite(pixels, sizeof(pixel_t), 
    head_data.width * head_data.height, outImage);
}

//This will simply allocate the memory for the pixels
pixel_t* allocatePixMemory(header_t head_data){
    return(pixel_t*)malloc(sizeof(pixel_t)*head_data.width*head_data.height);
}

//This will do as named. Free the data from the pixels
void freeMemory(pixel_t* pixels){
    free(pixels);
}
