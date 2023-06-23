#include "Point3D.h"

template <typename myType>
Point3D<myType>::Point3D(myType myX, myType myY, myType myZ) {
	x = myX;
	y = myY;
	z = myZ;
}

template class Point3D<double>;
template class Point3D<float>;
//template class Point3D<int>;