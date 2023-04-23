	#define CATCH_CONFIG_MAIN

	#include "../Car/Car.h"
	#include "../Car/ControllerCar.h"
	#include "../../../lw2/catch2/catch.hpp"

	SCENARIO("car is operated correctly")
	{
		GIVEN("a car")
		{
			Car car;

			WHEN("it is just created")
			{
				THEN("the engine is off")
				{
					REQUIRE(!car.IsTurnedOn());
				}

				THEN("it is at zeroth gear")
				{
					REQUIRE(car.GetGear() == 0);
				}

				THEN("it has zero speed")
				{
					REQUIRE(car.GetSpeed() == 0);
				}

				THEN("it is not moving")
				{
					REQUIRE(car.GetDirection() == Car::MoveDirection::STAY);
				}

				THEN("it can't change gear")
				{
					REQUIRE(!car.SetGear(1));
					REQUIRE(car.GetGear() == 0);
					REQUIRE(!car.SetGear(-1));
					REQUIRE(car.GetGear() == 0);
				}

				THEN("it can't change speed")
				{
					REQUIRE(!car.SetSpeed(10));
					REQUIRE(car.GetSpeed() == 0);
				}

				THEN("the engine can't be turned off")
				{
					REQUIRE(!car.TurnOffEngine());
					REQUIRE(!car.IsTurnedOn());
				}

				THEN("the engine can be turned on")
				{
					REQUIRE(car.TurnOnEngine());
					REQUIRE(car.IsTurnedOn());
				}

				WHEN("the engine is turned on")
				{
					car.TurnOnEngine();

					THEN("it is at zeroth gear")
					{
						REQUIRE(car.GetGear() == 0);
					}

					THEN("it has zero speed")
					{
						REQUIRE(car.GetSpeed() == 0);
					}

					THEN("it is not moving")
					{
						REQUIRE(car.GetDirection() == Car::MoveDirection::STAY);
					}

					THEN("the engine can be turned off")
					{
						REQUIRE(car.TurnOffEngine());
						REQUIRE(!car.IsTurnedOn());
					}

					THEN("the engine can't be turned on")
					{
						REQUIRE(!car.TurnOnEngine());
						REQUIRE(car.IsTurnedOn());
					}

					THEN("it can set first gear")
					{
						REQUIRE(car.SetGear(1));
						REQUIRE(car.GetGear() == 1);
					}

					THEN("it can set reverse gear")
					{
						REQUIRE(car.SetGear(-1));
						REQUIRE(car.GetGear() == -1);
					}

					THEN("neutral gear can be set")
					{
						REQUIRE(car.SetGear(0));
						REQUIRE(car.GetGear() == 0);
					}

					WHEN("reverse gear is set")
					{
						car.SetGear(-1);

						THEN("the engine can't be turned off")
						{
							REQUIRE(!car.TurnOffEngine());
							REQUIRE(car.IsTurnedOn());
						}

						THEN("neutral gear can be set")
						{
							REQUIRE(car.SetGear(0));
							REQUIRE(car.GetGear() == 0);
						}

						THEN("reverse gear can be set")
						{
							REQUIRE(car.SetGear(-1));
							REQUIRE(car.GetGear() == -1);
						}

						THEN("first gear can be set")
						{
							REQUIRE(car.SetGear(1));
							REQUIRE(car.GetGear() == 1);
						}

						THEN("speed from 0 to 20 can be set")
						{
							REQUIRE(car.SetSpeed(20));
							REQUIRE(car.GetSpeed() == 20);
							REQUIRE(car.SetSpeed(0));
							REQUIRE(car.GetSpeed() == 0);
						}

						THEN("speed exceeding limit can't be set")
						{
							REQUIRE(!car.SetSpeed(21));
							REQUIRE(car.GetSpeed() == 0);
						}

						WHEN("it speeds up")
						{
							car.SetSpeed(10);

							THEN("it is moving backward")
							{
								REQUIRE(car.GetDirection() == Car::MoveDirection::BACKWARD);
							}

							THEN("neutral gear can be set")
							{
								REQUIRE(car.SetGear(0));
								REQUIRE(car.GetGear() == 0);
							}

							WHEN("neutral gear is set")
							{
								car.SetGear(0);

								THEN("it has the same speed")
								{
									REQUIRE(car.GetSpeed() == 10);
								}

								THEN("it is STAY moving backwards")
								{
									REQUIRE(car.GetDirection() == Car::MoveDirection::BACKWARD);
								}

								THEN("it can't speed up")
								{
									REQUIRE(!car.SetSpeed(15));
									REQUIRE(car.GetSpeed() == 10);
								}

								THEN("it can slow down")
								{
									REQUIRE(car.SetSpeed(5));
									REQUIRE(car.GetSpeed() == 5);
									REQUIRE(car.GetDirection() == Car::MoveDirection::FORWARD);
								}
							}
						}
					}

					WHEN("first gear is set")
					{
						car.SetGear(1);

						THEN("the engine can't be turned off")
						{
							REQUIRE(!car.TurnOffEngine());
							REQUIRE(car.IsTurnedOn());
						}

						THEN("speed from 0 to 30 can be set")
						{
							REQUIRE(car.SetSpeed(30));
							REQUIRE(car.GetSpeed() == 30);
							REQUIRE(car.SetSpeed(0));
							REQUIRE(car.GetSpeed() == 0);
						}

						THEN("speed exceeding limit can't be set")
						{
							REQUIRE(!car.SetSpeed(31));
							REQUIRE(car.GetSpeed() == 0);
							REQUIRE(!car.SetSpeed(-10));
							REQUIRE(car.GetSpeed() == 0);
						}

						THEN("fist gear can be set")
						{
							REQUIRE(car.SetGear(1));
							REQUIRE(car.GetGear() == 1);
						}

						WHEN("it speeds up")
						{
							car.SetSpeed(20);

							THEN("it is moving forward")
							{
								REQUIRE(car.GetDirection() == Car::MoveDirection::FORWARD);
							}

							THEN("neutral gear can be set")
							{
								REQUIRE(car.SetGear(0));
								REQUIRE(car.GetGear() == 0);
							}

							WHEN("neutral gear is set")
							{
								car.SetGear(0);

								THEN("it has the same speed")
								{
									REQUIRE(car.GetSpeed() == 20);
								}

								THEN("it is still moving forward")
								{
									REQUIRE(car.GetDirection() == Car::MoveDirection::FORWARD);
								}

								THEN("it can't speed up")
								{
									REQUIRE(!car.SetSpeed(25));
									REQUIRE(car.GetSpeed() == 20);
								}

								THEN("it can slow down")
								{
									REQUIRE(car.SetSpeed(10));
									REQUIRE(car.GetSpeed() == 10);
								}
							}
						}
					}

					WHEN("second gear is set")
					{
						car.SetGear(1);
						car.SetSpeed(20);
						car.SetGear(2);

						THEN("speed from 20 to 50 can be set")
						{
							REQUIRE(car.SetSpeed(20));
							REQUIRE(car.GetSpeed() == 20);
							REQUIRE(car.SetSpeed(50));
							REQUIRE(car.GetSpeed() == 50);
						}

						THEN("speed exceeding limit can't be set")
						{
							REQUIRE(!car.SetSpeed(19));
							REQUIRE(car.GetSpeed() == 20);
							REQUIRE(!car.SetSpeed(51));
							REQUIRE(car.GetSpeed() == 20);
						}
					}

					WHEN("third gear is set")
					{
						car.SetGear(1);
						car.SetSpeed(20);
						car.SetGear(2);
						car.SetSpeed(30);
						car.SetGear(3);

						THEN("speed from 30 to 60 can be set")
						{
							REQUIRE(car.SetSpeed(30));
							REQUIRE(car.GetSpeed() == 30);
							REQUIRE(car.SetSpeed(60));
							REQUIRE(car.GetSpeed() == 60);
						}

						THEN("speed exceeding limit can't be set")
						{
							REQUIRE(!car.SetSpeed(29));
							REQUIRE(car.GetSpeed() == 30);
							REQUIRE(!car.SetSpeed(61));
							REQUIRE(car.GetSpeed() == 30);
						}
					}

					WHEN("fourth gear is set")
					{
						car.SetGear(1);
						car.SetSpeed(20);
						car.SetGear(2);
						car.SetSpeed(30);
						car.SetGear(3);
						car.SetSpeed(40);
						car.SetGear(4);

						THEN("speed from 40 to 90 can be set")
						{
							REQUIRE(car.SetSpeed(40));
							REQUIRE(car.GetSpeed() == 40);
							REQUIRE(car.SetSpeed(90));
							REQUIRE(car.GetSpeed() == 90);
						}

						THEN("speed exceeding limit can't be set")
						{
							REQUIRE(!car.SetSpeed(39));
							REQUIRE(car.GetSpeed() == 40);
							REQUIRE(!car.SetSpeed(91));
							REQUIRE(car.GetSpeed() == 40);
						}
					}

					WHEN("fifth gear is set")
					{
						car.SetGear(1);
						car.SetSpeed(20);
						car.SetGear(2);
						car.SetSpeed(30);
						car.SetGear(3);
						car.SetSpeed(40);
						car.SetGear(4);
						car.SetSpeed(50);
						car.SetGear(5);

						THEN("speed from 50 to 150 can be set")
						{
							REQUIRE(car.SetSpeed(50));
							REQUIRE(car.GetSpeed() == 50);
							REQUIRE(car.SetSpeed(150));
							REQUIRE(car.GetSpeed() == 150);
						}

						THEN("speed exceeding limit can't be set")
						{
							REQUIRE(!car.SetSpeed(49));
							REQUIRE(car.GetSpeed() == 50);
							REQUIRE(!car.SetSpeed(151));
							REQUIRE(car.GetSpeed() == 50);
						}
					}
				}
			}
		}
	}

	