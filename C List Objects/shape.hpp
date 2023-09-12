/*
 * partner: kuanwei2
 * 
 * This program is used to create a list containing different shapes of object, including Rectangle, Circle, Sphere, and RectPrism.
 * In each shape, there will be its volume and area and its dimension. The program will read an input file to store all the shapes
 * into a list and then print all the shapes in the list and the maximum area and volume of the list.
 * 
 */
#ifndef SHAPE_H_
#define SHAPE_H_

#include<iostream>
#include<cmath>
#include<string>
#include<algorithm>
#include<list>
#include<fstream>
#include <iomanip>    

using namespace std;

//Base class
//Please implement Shape's member functions
//constructor, getName()
class Shape{
public:
	//Base class' constructor should be called in derived classes'
	//constructor to initizlize Shape's private variable 
  	Shape(string name) {																										// constructor for storing the name of the shape
		name_=name;
	}
	
  	string getName() {																											// return the name of the shape
		return name_;
	}
	
  	virtual double getArea() const = 0;																							// virtual function of getArea
  	virtual double getVolume() const = 0;																						// virtual function of getVolume
	
private:
  string name_;


};

//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-

template <class T>
class Rectangle : public Shape{
public:
  	Rectangle<T>(T width = 0, T length = 0):Shape("Rectangle") {																// constructor for setting rectangle's width and length
		width_=width;
		length_=length;
	}
	
  	double getArea() const {																									// return the Area(width*length) of the rectangle
		return (double)width_*length_;
	}
	
  	double getVolume() const {																									// return the Volume(0) of the rectangle
		return 0.0;
	}
	
	Rectangle<T> operator + (const Rectangle<T>& rec) {																			// return a rectangle object with the width and length that are the sum of the current rectangle
		return Rectangle<T>(width_+rec.getWidth(),length_+rec.getLength());														// and the input rectangle
	}
	
	Rectangle<T> operator - (const Rectangle<T>& rec) {																			// return a rectangle object with the width and length that are the max of (the difference of the current rectangle
		return Rectangle<T>(fmax(width_-rec.getWidth(),0),fmax(0,length_-rec.getLength()));										// and the input rectangle) and 0. 
	} 
	
	T getWidth() const { 																										// return the width of the rectangle
		return width_;
	}
	
	T getLength() const { 																										// return the length of the rectangle
		return length_;
	}
private:
	T width_;
    T length_;

};

//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

class Circle : public Shape{
public:
  	Circle(double radius):Shape("Circle") {																						// constructor for setting circle's radius
		radius_=radius;
	}
	
  	double getArea() const{																										// return the area(pi*r^2) of the circle
		return M_PI*pow(radius_,2);
	}
	
 	double getVolume() const{																									// return the volume(0) of the circle
		return 0.0;
	}
	
  	Circle operator + (const Circle& cir){																						// return a circle object with radius that are the sum of the current circle and 
		return Circle(radius_+cir.getRadius());																					// the input circle
	}
	
	Circle operator - (const Circle& cir){																						// return a circle object with radius that are the max(difference of the current circle and 
		return Circle(fmax(0,radius_-cir.getRadius()));																			// the input circle, 0)
	} 

	double getRadius() const { 																									// return the radius of the circle
		return radius_;
	}
	
private:
	double radius_;

};



//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

class Sphere : public Shape{
public:
  	Sphere(double radius):Shape("Sphere") {																						// constructor for setting sphere's radius
		radius_=radius;
	}

  	double getVolume() const {																									// return the volume(4/3*pi*r^3) of the sphere
		return  (4.0/3.0)*M_PI*pow(radius_,3);					
	}	
	
  	double getArea() const {																									// return the surface area(4*pi*r^2) of the sphere
		return 4*M_PI*pow(radius_,2);
	}

	Sphere operator + (const Sphere& sph) {																						// return a sphere object with radius that are the sum of the current sphere and
		return Sphere(radius_+sph.getRadius());																					// the input sphere
	}

	Sphere operator - (const Sphere& sph) {																						// return a sphere object with radius that are max(the difference of the current sphere and
		return Sphere(fmax(0,radius_-sph.getRadius()));																			// the input sphere, 0)
	} 
	
	double getRadius() const {																									// return the radius of the sphere
		return radius_;
	}

private:
	double radius_;

};

//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
class RectPrism : public Shape{
public:
  	RectPrism(double width, double length, double height):Shape("RectPrism") {													// constructor for setting rectprism's width, length, height
		width_=width;
		length_=length;
		height_=height;
	}
	
  	double getVolume() const {																									// return the volume(width*length*height) of the rectprism
		return (double)width_*length_*height_;
	}
  	
	double getArea() const {																									// return the surface area(2*(width*length+width*height+length*height) of the rectprism
		return (double)2*(width_*length_+width_*height_+length_*height_);
	}
	
	RectPrism operator + (const RectPrism& rectp){																				// return a rectprism object with dimension that are the sum of the current rectprism and
		return RectPrism(width_+rectp.getWidth(),length_+rectp.getLength(),height_+rectp.getHeight());							// input rectprism
	}
	
	RectPrism operator - (const RectPrism& rectp){
		return RectPrism(fmax(0,width_-rectp.getWidth()),fmax(0,length_-rectp.getLength()),fmax(0,height_-rectp.getHeight()));	// return a rectprism object with dimension that are max(difference of the current rectprism and
	}																															// and input rectprism, 0)
	
	double getWidth() const { 																									// return the width of the rectprism
		return width_;
	}
	
	double getLength() const { 																									// return the length of the rectprism
		return length_;
	}
	
	double getHeight() const { 																									// return the height of the rectprism
		return height_;
	}
  
private:
  	double length_;
  	double width_;
  	double height_;

};

// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects 
static list<Shape*> CreateShapes(char* file_name) {
	//@@Insert your code here
	int num;
	ifstream ifs (file_name, std::ifstream::in);																				// read the input file
	ifs >> num; 																												// read the number of shapes in the file
	list<Shape*> shapes;																										// create a list of shape*
	for(int i=0;i<num;i++){																										// iterate through each shape
		string type;
		double var1;
		ifs >> type >> var1; 																									// read the name of the shape and the first value
		if(type.compare("Rectangle")==0){																						// if it is a rectangle, read its length
			double var2;
			ifs >> var2; 
			shapes.push_back(new Rectangle<double>(var1,var2));																	// create a rectangle object with its dimension and put it in the list
		}
		else if(type.compare("Circle")==0){																						// if it is a circle
			shapes.push_back(new Circle(var1));																					// create a circle object with its dimension and put it in the list
		}
		else if(type.compare("Sphere")==0){																						// if it is a sphere
			shapes.push_back(new Sphere(var1));																					// create a sphere object with its dimension and put it in the list
		}
		else if(type.compare("RectPrism")==0){																					// if it is a rectprism, read its length and height
			double var2,var3;
			ifs >> var2 >> var3; 
			shapes.push_back(new RectPrism(var1,var2,var3));																	// create a rectprism object with its dimension and put it in the list
		}
	}
	ifs.close();																												// close the file
	return shapes;																												// return the list
}

// call getArea() of each object 
// return the max area
static double MaxArea(list<Shape*> shapes){
	double max_area = 0;																										// set 0 as maximum area
	//@@Insert your code here
	for(list<Shape*>::iterator it =shapes.begin(); it != shapes.end(); it++)													// iterate through each shape in the list
		max_area = fmax(max_area,(*it)->getArea());																				// store the greater value of the area of current shape and the previous maximum area 
	return max_area;																											// return the maximum area
}

// call getVolume() of each object 
// return the max volume
static double MaxVolume(list<Shape*> shapes){
	double max_volume = 0;																										// set 0 as maximum volume
	//@@Insert your code here
	for(list<Shape*>::iterator it =shapes.begin(); it != shapes.end(); it++)													// iterate through each shape in the list
		max_volume = fmax(max_volume,(*it)->getVolume());																		// store the greater value of the volume of current shape and the previous maximum volume 
	return max_volume;																											// return the maximum volume
}
#endif

