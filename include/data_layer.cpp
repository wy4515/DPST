#include "data_layer.h"

DataLayer::DataLayer(int _in_w, int _in_h, int _in_ch, int _num_samples,
          Func data) : Layer(0) {

  in_w = _in_w;
  in_h = _in_w;
  in_ch = _in_ch;
  num_samples = _num_samples;

  // Define forward
  forward(x, y, z, n) = data(x, y, z);

}

// Nothing to propagate
void DataLayer::back_propagate(Func dout) {
  assert(dout.defined());
  return;
}

int DataLayer::out_dims() { return 4; }

int DataLayer::out_dim_size(int i) {
  assert(i < 4);
  int size = 0;
  if (i == 0)
    size = in_w;
  else if (i == 1)
    size = in_h;
  else if (i == 2)
    size = in_ch;
  else if (i == 3)
    size = num_samples;
  return size;
}