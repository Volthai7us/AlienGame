#ifndef POINT2D_H
#define POINT2D_H

class Point2D{
    public:GLfloat x;
    public:GLfloat y;

    Point2D operator + (Point2D& second){
        Point2D result = {x + second.x, y + second.y}; 
        return result;
    }

    Point2D operator - (Point2D& second){
        Point2D result = {x - second.x, y - second.y}; 
        return result;
    }

    void swap(Point2D& second){
        float tempX = x;
        float tempY = y;

        x = second.x;
        y = second.y;

        second.x = tempX;
        second.y = tempY;
    }
};


#endif