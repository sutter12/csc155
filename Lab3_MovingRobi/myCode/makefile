RobotTest: I2C.c PWM.c MotorHat.c Robot.c RobotTest.c
	gcc -c I2C.c -lbcm2835
	gcc -c PWM.c -lbcm2835
	gcc -c MotorHat.c -lbcm2835
	gcc -c Robot.c -lbcm2835
	gcc -o Robi RobotTest.c I2C.o PWM.o MotorHat.o Robot.o -lbcm2835 -lm
