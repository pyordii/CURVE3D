#pragma once

#include <iostream>
#include "Point3D.h"


namespace crv
{
	// ������� ����� ��� ���������� ������
	template <typename myType>
	class Curve3D
	{
	protected:
		static const myType PI;
	public:
		// ���������� ����� �� ������ �� ���� t � ��������
		inline virtual Point3D<myType> GetPoint(myType t) const = 0;

		// ���������� ����������� ������ �� ���� t � ��������
		inline virtual Point3D<myType> GetDerivative(myType t) const = 0;
	};

	template <typename myType>
	const myType Curve3D<myType>::PI = myType(3.14159265358979323846);

	// ����� ����������
	template <typename myType>
	class Circle : public Curve3D<myType> {
	private:
		myType radius;

	public:
		Circle<myType>(myType myRadius);
		myType GetRadius();
		Point3D<myType> GetPoint(myType t) const override;
		Point3D<myType> GetDerivative(myType t) const override;

	};


	// ����� �������
	template <typename myType>
	class Ellipse : public Curve3D<myType> {
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

	// ����� �������
	template <typename myType>
	class Helix : public Curve3D<myType> {
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