
#ifndef SIZE_H
#define SIZE_H
struct Size
{
	Size(float a,float b,float c,float e):x(a),y(b),w(c),h(e){}
	Size(){}
	int x;
	int y;
	int w;
	int h;
};
#endif SIZE_H