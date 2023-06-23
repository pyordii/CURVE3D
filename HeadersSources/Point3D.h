#pragma once
// Класс трехмерной точки
#include <iostream>
#include <type_traits>

template <typename myType>
class  Point3D
{
	// Проверка, что шаблонный параметр является типом float или double
	static_assert(std::is_same<myType, float>::value || std::is_same<myType, double>::value, "Template parameter must be float or double.");

public:
	myType x;
	myType y;
	myType z;
	
	Point3D(myType myX, myType myY, myType myZ);

	
	inline friend std::ostream& operator<< (std::ostream& os, const Point3D<myType>& point) {
		os << "(" << point.x << ", " << point.y << ", " << point.z << ")";
		return os;
	}

};

