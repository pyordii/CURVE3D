// Приведенный ниже блок ifdef — это стандартный метод создания макросов, упрощающий процедуру
// экспорта из библиотек DLL. Все файлы данной DLL скомпилированы с использованием символа CURVE3DLIB_EXPORTS
// Символ, определенный в командной строке. Этот символ не должен быть определен в каком-либо проекте,
// использующем данную DLL. Благодаря этому любой другой проект, исходные файлы которого включают данный файл, видит
// функции CURVE3DLIB_API как импортированные из DLL, тогда как данная DLL видит символы,
// определяемые данным макросом, как экспортированные.
#ifdef CURVE3DLIB_EXPORTS
#define CURVE3DLIB_API __declspec(dllexport)
#else
#define CURVE3DLIB_API __declspec(dllimport)
#endif

#include <iostream>
#include <type_traits>

/*
// Этот класс экспортирован из библиотеки DLL
class CURVE3DLIB_API CCurve3DLib {
public:
	CCurve3DLib(void);
	// TODO: добавьте сюда свои методы.
};

extern CURVE3DLIB_API int nCurve3DLib;

CURVE3DLIB_API int fnCurve3DLib(void);
*/

template <typename myType>
class CURVE3DLIB_API Point3D
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

namespace crv
{
	// Базовый класс для трехмерной кривой
	template <typename myType>
	class Curve3D
	{
	protected:
		static const myType PI;
	public:
		// Возвращает точку на кривой по углу t в радианах
		inline virtual Point3D<myType> GetPoint(myType t) const = 0;

		// Возвращает производную кривой по углу t в радианах
		inline virtual Point3D<myType> GetDerivative(myType t) const = 0;
	};

	template <typename myType>
	const myType Curve3D<myType>::PI = myType(3.14159265358979323846);

	// Класс окружности
	template <typename myType>
	class CURVE3DLIB_API Circle : public Curve3D<myType> {
	private:
		myType radius;

	public:
		Circle<myType>(myType myRadius);
		myType GetRadius();
		Point3D<myType> GetPoint(myType t) const override;
		Point3D<myType> GetDerivative(myType t) const override;

	};



	// Класс эллипса
	template <typename myType>
	class CURVE3DLIB_API Ellipse : public Curve3D<myType> {
	private:
		myType radiusX;
		myType radiusY;

	public:
		Ellipse(myType myRadiusX, myType myRadiusY);

		myType GetRadiusX();
		myType GetRadiusY();
		Point3D<myType> GetPoint(myType t) const override;
		Point3D<myType> GetDerivative(myType t) const override;
	};

	// Класс спирали
	template <typename myType>
	class CURVE3DLIB_API Helix : public Curve3D<myType> {
	private:
		myType radius;
		myType step;

	public:
		Helix(myType myRadius, myType myStep);
		myType GetRadius();
		myType GetStep();

		Point3D<myType> GetPoint(myType t) const override;
		Point3D<myType> GetDerivative(myType t) const override;
	};
}