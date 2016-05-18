//
// Created by Kevin Jayne on 5/17/16.
//

#ifndef POSITION_H
#define POSITION_H

class Position{

protected:

public:

  float x, y, z;

  Position(){
    x = 0;
    y = 0;
    z = 0;
  };

  Position(int xi, int yi, int zi){
    x = xi;
    y = yi;
    z = zi;
  };

};



#endif //POSITION_H
