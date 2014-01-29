#ifndef RECTANGLE_H_
#define RECTANGLE_H_

struct Rectangle {
   Rectangle(int x, int y, int width, int height) :
       x_{x},
       y_{y},
       width_{width},
       height_{height}
    {}

   int getLeft() const { return x_; }
   int getRight() const { return x_ + width_; }
   int getTop() const { return y_; }
   int getBottom() const { return y_ + height_; }

   int getWidth() const { return width_; }
   int getHeight() const { return height_; }

private:
   const int x_;
   const int y_;
   const int width_;
   const int height_;
};

#endif /* RECTANGLE_H_ */
