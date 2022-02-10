#ifndef POINT3D_H
#define POINT3D_H

class Point3D{
    public:float x;
    public:float y;
    public:float z;
    
    Point3D operator + (Point3D& second){
        struct Point3D result = {x + second.x, y + second.y, z + second.z}; 
        return result;
    }

    Point3D operator - (Point3D& second){
        struct Point3D result = {x - second.x, y - second.y, z - second.z}; 
        return result;
    }

    Point3D abs(Point3D first){
        struct Point3D result;
        result.x = first.x > 0 ? first.x : -first.x;
        result.y = first.y > 0 ? first.y : -first.x;
        result.z = first.z > 0 ? first.z : -first.z;
        return result;
    }

    void swap(Point3D& second){
        float tempX = x;
        float tempY = y;
        float tempZ = z;

        x = second.x;
        y = second.y;
        z = second.z;

        second.x = tempX;
        second.y = tempY;
        second.z = tempZ;
    }
};



#endif