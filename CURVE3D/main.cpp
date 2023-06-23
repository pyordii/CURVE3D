#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>

#include <tbb/tbb.h>
#include "Curve3DLib.h"

// Только double или float
using myType = double;
const myType PI = myType(3.14159265358979323846);

// Функтор для выполнения операции суммирования
struct SumFunctor {
	const std::vector<std::shared_ptr<crv::Curve3D<myType>>>& rPtrsCurves;

	SumFunctor(const std::vector<std::shared_ptr<crv::Curve3D<myType>>>& myRPtrsCurves)
		: rPtrsCurves(myRPtrsCurves) {}

	myType operator()(const tbb::blocked_range<int>& range, myType sum) const {
		for (int i = range.begin(); i < range.end(); ++i) {
			auto pCircle = std::dynamic_pointer_cast<crv::Circle<myType>>(rPtrsCurves[i]);
			sum += pCircle->GetRadius();
		}
		return sum;
	}

	void join(SumFunctor& other) {}
};

void PopulateCurves(std::vector<std::shared_ptr<crv::Curve3D<myType>>>& myCurves, int n) {
	std::mt19937 gen(0);
	std::uniform_real_distribution<double> radiusDistribution(1.0, 10.0);

	for (int i = 0; i < n; ++i) {

		myType radiusX = 0;
		myType radiusY = 0;
		myType step = 0;

		switch (i % 3)
		{
		case 0:
			radiusX = radiusDistribution(gen);
			myCurves.push_back(std::make_shared<crv::Circle<myType>>(radiusX));
			break;

		case 1:
			radiusX = radiusDistribution(gen);
			radiusY = radiusDistribution(gen);
			myCurves.push_back(std::make_shared<crv::Ellipse<myType>>(radiusX, radiusY));
			break;

		case 2:
			radiusX = radiusDistribution(gen);
			step = radiusDistribution(gen);
			myCurves.push_back(std::make_shared<crv::Helix<myType>>(radiusX, step));
			break;
		}
	}
}

void ShowCurves(const std::vector<std::shared_ptr<crv::Curve3D<myType>>>& myCurves, const myType t) {
	for (const auto& curve : myCurves) {
		std::cout << "Curve Type: ";
		if (auto pCircle = std::dynamic_pointer_cast<crv::Circle<myType>>(curve)) {
			std::cout << "Circle" << std::endl;
			std::cout << "Radius: " << pCircle->GetRadius() << std::endl;
		}
		else if (auto pElipse = std::dynamic_pointer_cast<crv::Ellipse<myType>>(curve)) {
			std::cout << "Ellipse" << std::endl;
			std::cout << "RadiusX: " << pElipse->GetRadiusX() << std::endl;
			std::cout << "RadiusY: " << pElipse->GetRadiusY() << std::endl;
		}
		else if (auto pHelix = std::dynamic_pointer_cast<crv::Helix<myType>>(curve)) {
			std::cout << "Helix" << std::endl;
			std::cout << "Radius: " << pHelix->GetRadius() << std::endl;
			std::cout << "Step: " << pHelix->GetStep() << std::endl;
		}

		std::cout << "Point at t = " << t << ": " << curve->GetPoint(t) << std::endl;
		std::cout << "Derivative at t = " << t << ": " << curve->GetDerivative(t) << std::endl;
		std::cout << std::endl;
	}
}


int main() {
	// Создание контейнера для кривых
	std::vector<std::shared_ptr<crv::Curve3D<myType>>> ptrsCurves;
	PopulateCurves(ptrsCurves, 7);

	// Вывод описания, координат точек и производных для всех кривых в контейнере
	std::cout << "***********************Curves***********************" << std::endl;
	ShowCurves(ptrsCurves, PI / 4);

	// Заполнение второго контейнера окружностями из первого
	std::vector<std::shared_ptr<crv::Curve3D<myType>>> ptrsCircles;
	for (const auto& curve : ptrsCurves) {
		if (auto pCircle = std::dynamic_pointer_cast<crv::Circle<myType>>(curve)) {
			ptrsCircles.push_back(pCircle);
		}
	}
	std::cout << "***********************Circles***********************" << std::endl;
	ShowCurves(ptrsCircles, PI / 4);

	// Сортировка контейнера с окружностями по их радиусу
	std::sort(ptrsCircles.begin(), ptrsCircles.end(), [](const auto& c1, const auto& c2) {
		return std::dynamic_pointer_cast<crv::Circle<myType>>(c1)->GetRadius() <
			std::dynamic_pointer_cast<crv::Circle<myType>>(c2)->GetRadius();
		});
	std::cout << "***********************Sorted Circles***********************" << std::endl;
	ShowCurves(ptrsCircles, PI / 4);

	// Вычисление суммы радиусов окружностей двумя способами
	//for (const auto& pCircle : ptrsCircles) {
	//totalSum += std::dynamic_pointer_cast<crv::Circle<myType>>(pCircle)->GetRadius();
	//}

	myType totalSum = std::accumulate(std::begin(ptrsCircles), std::end(ptrsCircles), 0.0,
		[](myType sum, const auto& pCircle) {
			return sum + std::dynamic_pointer_cast<crv::Circle<myType>>(pCircle)->GetRadius();
		});


	SumFunctor sumFunctor(ptrsCircles);
	myType parallelTotalSum = tbb::parallel_reduce(tbb::blocked_range<int>(0, ptrsCircles.size()),
		myType(0.0), sumFunctor, std::plus<myType>());


	std::cout << "***********************Sum Radii***********************" << std::endl;
	std::cout << "Total sum of radii: " << totalSum << std::endl;
	std::cout << "Parallel total sum of radii: " << parallelTotalSum << std::endl;

	return 0;
}