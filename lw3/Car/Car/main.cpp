#include "ControllerCar.h"

int main()
{
	Car car;
	ControllerCar control(std::cin, std::cout, car);
	control.ControlCar();

	return 0;
}