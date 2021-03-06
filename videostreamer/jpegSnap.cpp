#include <iostream>
#include "ImpEncoder.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_usage() {
    printf("Usage: jpegSnap -w 1920 -h 1080\n");
}

int main(int argc, char *argv[]) {

    int width = 1920;
    int height = 1080;
    int nightvision = 0;

    // Parse Arguments:
    int c;
    while ((c = getopt(argc, argv, "w:h:n:")) != -1) {
        switch (c) {
            case 'w':
                width = atoi(optarg);
                break;
            case 'h':
                height = atoi(optarg);
            case 'n':
                nightvision = atoi(optarg);
                break;
            default:
                printf("Invalid Argument %c\n", c);
                exit(EXIT_FAILURE);
        }
    }


    impParams params;
    params.width = width;
    params.height = height;
    params.mode = IMP_MODE_JPEG;
    if(nightvision == 1){
        params.nightvision = true;
    } else{
        params.nightvision = false;
    }

    ImpEncoder *impEncoder = new ImpEncoder(params);
    int bytesRead = impEncoder->snap_jpeg();
    void *buffer = impEncoder->getBuffer();

    int ret;
    //int stream_fd = open("", O_RDWR);
    ret = fwrite(buffer, bytesRead, 1, stdout);

    return ret;
}
