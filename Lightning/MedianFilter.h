#ifndef MEDIAN_FILTER_H
#define MEDIAN_FILTER_H

// Median filter class
class MedianFilter
{
  private:
    int _x[3];
    int _median;
  public:
    MedianFilter()
    {
      _x[0] = 0;
      _x[1] = 0;
      _x[2] = 0;
      _median = 0;
    }

    int run(int data)
    {
      _x[0] = _x[1];
      _x[1] = _x[2];
      _x[2] = data;

      if (_x[2] < _x[1]) {
        if (_x[2] < _x[0]) {
          if (_x[1] < _x[0]) {
            _median = _x[1];
          }
          else {
            _median = _x[0];
          }
        }
        else {
          _median = _x[2];
        }
      }
      else {
        if (_x[2] < _x[0]) {
          _median = _x[2];
        }
        else {
          if (_x[1] < _x[0]) {
            _median = _x[0];
          }
          else {
            _median = _x[1];
          }
        }
      }
      return (_median);
    }
};

#endif // MEDIAN_FILTER_H 