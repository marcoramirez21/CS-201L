# Pseudocode for Distance calculation Program (lab1)
## Overview
This program compares the distances of two poinst from origin until the user quits.
It offers two mode for coordinates input: manual entry or random generation.

BEGIN Program
	INITIALIZE random number generator with current time

	REPEAT 
		DECLARE x1, x2, y1, y2 AS INTEGER
		DECLARE choice, variable 'again' AS CHAR 

		
		PRINT "(E)nter values or (G)enerate randomly? (E/G): "
		GET USER choice

		If choice IN ['E', 'e'] THEN
			x1 <- getValidatedInput("x1 (-10 to 10): ")
			y1 <- getValidatedInput("y1 (-10 to 10): ")
			x2 <- getValidatedInput("x2 (-10 to 10): ")
			y2 <- getValidatedInput("y2 (-10 to 10): ")
		ELSE
			x1 <- randomCordinate() 
			y1 <- randomCordinate()  
			x2 <- randomCordinate() 
			y2 <- randomCordinate() 


			PRINT Random coordinate: P1(x1, y1), P2(x2, y2)
			END IF

		d1 <- distanceToOrigen(x1,y1)
		d2 <- distanceToOrigen(x2,y2)

		PRINT    "Distance P1:" << d1; 
		PRINT    "Distance P2:" << d2;

		IF (d1<d2) THEN
			PRINT "point 1 is closer"
		ELSE IF (d2<d1) THEN
			PRINT "point 2 is closer"
		ELSE
			PRINT "Both points are equally close."
		END IF

		PRINT "Type 'Y' to RUN again. Type any other letter to END the program:"
		GET USER 'again'

	UNTIL again IS NOT IN ['Y', 'y'] 

	PRINT "Program ended"

END program



#HELPER FUNCTION

FUNCTION randomCoordinate()
	RETUR rand() % 21-10; 
END FUNCTION


FUNCTION distanceToOrigiN(x,y)
	RETURN sqrt(x*x + y*y ); 
END FUNCTION 


FUNCTION getValidateInput(prompt)
	DO
		PRINT prompt
		GET input
	WHILE input NOT INTEGER OR (input is  <  -10) OR (input  >  10) 
	RETURN input                                     
END FUNCTION






