#include "tensor2image.h"

using namespace Halide;

Image<float>
LoadImageFromTensor(const caffe2::TensorProto& tensor) {
    int width = 0;
    int height = 0;
    int channel = 0;
    int num = 0;

    if (tensor.dims_size() == 4) {
        channel = tensor.dims(0);
        width = tensor.dims(1);
        height = tensor.dims(2);
        num = tensor.dims(3);
    } else {
        // only 1 dim:
        // one bias per channel
        std::cout << "channel = " << tensor.dims(0) << std::endl;
        channel = tensor.dims(0);
    }

    Image<float> image(width, height, channel, num);

    int idx = 0;

    if (tensor.dims_size() == 4) {
        /* TODO: Can we parallel this? */
        for (int n=0; n<num; n++) {
            for (int k=0; k<channel; k++) {
                for (int j=0; j<height; j++) {
                    for (int i=0; i<width; i++) {
                        image(i, j, k, n) = tensor.float_data(idx);
                        idx += 1;
                    }
                }
            }
        }
    }
    else {// dim size = 1
        std::cout << "Tensor has 1 dim" << std::endl;
        for (int c=0; c<channel; c++) {
            image(1, 1, c, 1) = tensor.float_data(idx);
            idx += 1;
        }
    }

    printf("Load Halide::Image from Tensor\n");

    return image;
}