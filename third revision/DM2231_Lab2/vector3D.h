/******************************************************************************/
/*BY SHUM WENG SANG
DET(G)
VECTOR 3D CLASS

THE PURPOSE OF THIS CLASS IS TO CREATE A LIBRARY THAT IS EXCLUSIVELY USED FOR CALCULATIONS OF
VECTOR MATHIMATICS. THIS CLASS IS JUST FOR THE USER TO HAVE EASE OF USE WITH VECTORS.
*/
/******************************************************************************/
#pragma once
#include <iostream>

class DivideByZero : public std::exception
{
public:
	const char* what() { return "Divide By Zero"; }
};
/******************************************************************************/
/*
HERE WE DEFINE THE CLASS AND ALL THE ACCOMPYNING METHODS.
METHODS INTRODUCED: CONTRUCTOR, OPERATOR +, OPERATOR -. OPERATOR *, OPERATOR /
OPERATOR ==, OPERATOR !=, OPERATOR <<, MAGNITUDE, CROSS PRODUCT, DOR PRODUCT, AND NORMALIZE
*/
/******************************************************************************/
template <class T>
class Vector3D
{
public:
	T x, y, z;
	/******************************************************************************/
	/*
	CONTRUCTOR METHODS BEGIN. 2 CONSTRUCTORS.
	INPUT = VECTOR OR 3 NUMBERS

	OUTPUT = CREATING AN INSTANCE OF THE VECTOR CLASS

	DEFAULTS = ALL VALUES SET TO 0 IF NOT SPECIFIED
	*/
	/******************************************************************************/
	Vector3D(T a = 0.0, T b = 0.0, T c = 0.0){
		x = (T)a;
		y = (T)b;
		z = (T)c;
	}
	Vector3D(const Vector3D &rhs)
	{
		x = (T)rhs.x;
		y = (T)rhs.y;
		z = (T)rhs.z;
	}
	~Vector3D()
	{
	}

	/******************************************************************************/
	/*
	SET METHOD FOR VECTOR CLASS. AN ALTERNATIVE TO =
	INPUT = 3 NUMBERS
	OUTPUT = SETS THE VECTOR'S XYZ TO THE 3 NUMBERS
	DEFAULTS = ALL VALUES SET TO 0 IF NOT SPECIFIED
	*/
	/******************************************************************************/
	void Set(T a = 0, T b = 0, T c = 0) //Set all data
	{
		x = (T)a;
		y = (T)b;
		z = (T)c;
	}

	/******************************************************************************/
	/*
	OPERATORS +, +=, -, -=
	INPUT = A VECTOR CLASS
	OUTPUT = RETURNS THE RESULTANT VECTOR. += AND -= CHANGES THE ORIGNIAL VECTOR
	TO THE RETURNED VECTOR
	DEFAULTS = NONE
	*/
	/******************************************************************************/
	Vector3D operator+(const Vector3D& rhs) const //Vector addition
	{
		return Vector3D(x + (T)rhs.x, y + (T)rhs.y, z + (T)rhs.z);
	}
	Vector3D& operator+=(const Vector3D& rhs)
	{
		x += (T)rhs.x;
		y += (T)rhs.y;
		z += (T)rhs.z;
		return *this;
	}

	Vector3D operator-(const Vector3D& rhs) const //Vector subtraction
	{
		return Vector3D(x - (T)rhs.x, y - (T)rhs.y, z - (T)rhs.z);
	}

	Vector3D& operator-=(const Vector3D& rhs)
	{
		x -= (T)rhs.x;
		y -= (T)rhs.y;
		z -= (T)rhs.z;
		return *this;
	}

	/******************************************************************************/
	/*
	UNARY NEGATION IS DEFINED HERE
	INPUT = NONE
	OUTPUT = RETURNS THE NEGETIVE VECTOR OF THE VECTOR USED
	DEFAUTLS = NONE
	EG: -VECTOR1;
	*/
	/******************************************************************************/
	Vector3D operator-(void) const //Unary negation
	{
		return Vector3D(-x, -y, -z);
	}

	/******************************************************************************/
	/*
	OPERATORS *, *=, /, /=
	INPUT: A SCALAR UNIT
	OUTPUT: SCALAR MULTIPLICATION OF THE VECTOR CLASS. THE XYZ ARE MULTIPLIED/ DIVIDED BY THE
	SCALAR UNIT
	EG: VECTOR * 5
	DEFAULTS = NONE
	*/
	/******************************************************************************/
	Vector3D operator*(T scalar) const
	{
		return Vector3D(scalar * x, scalar * y, scalar * z);
	}
	Vector3D& operator*=(T scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}
	Vector3D operator/(T scalar) const
	{
		return Vector3D(x / scalar, y / scalar, z / scalar);
	}
	Vector3D& operator/=(T scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}

	/******************************************************************************/
	/*
	OPERATORS ==, !=
	INPUT: VECTORS
	OUTPUT: RETURNS A BOOLEAN TRUE OF FALSE FOR CHECKING.
	DEFAULTS = NONE
	*/
	/******************************************************************************/
	bool operator==(const Vector3D& rhs) const //Equality Check
	{
		if (this->x != rhs.x)
			return false;
		if (this->y != rhs.y)
			return false;
		if (this->z != rhs.z)
			return false;
		return true;
	}
	bool operator!= (const Vector3D& rhs) const //Inequality check
	{
		if (this->x == rhs.x)
			return false;
		if (this->y == rhs.y)
			return false;
		if (this->z == rhs.z)
			return false;
		return true;
	}

	/******************************************************************************/
	/*
	OPERATORS = (AKA ASSIGNMENT OPERATOR)
	INPUT: VECTORS
	OUTPUT: RETURNS A VECTOR THAT HAS ITS VALUE SET TO THE VECTOR USED AND ASSIGNS IT
	TO THE ORIGINAL VECTOR
	DEFAULTS = NONE
	*/
	/******************************************************************************/
	Vector3D& operator=(const Vector3D& rhs) //Assignment operator
	{
		x = (T)rhs.x;
		y = (T)rhs.y;
		z = (T)rhs.z;
		return *this;
	}

	/******************************************************************************/
	/*
	FINDING A MAGNITUDE
	INPUT: NONE
	OUTPUT: RETURNS THE MAGNITUDE OF THE VECTOR
	DEFAULTS = NONE
	*/
	/******************************************************************************/
	T Magnitude(void) const //Get magnitude
	{
		return sqrt(x * x + y * y + z * z);
	}

	/******************************************************************************/
	/*
	FINDING THE SQUARE OF THE MAGNITUDE
	INPUT: NONE
	OUTPUT: RETURNS THE MAGNITUDE OF THE VECTOR SQUARED
	DEFAULTS = NONE
	*/
	/******************************************************************************/
	T MagSquared(void) const //Get square of magnitude
	{
		return x * x + y * y + z * z;
	}

	/******************************************************************************/
	/*
	FINDING THE DOT PRODUCT OF ONE VECTOR WITH ANOTHER VECTOR
	INPUT: VECTOR
	OUTPUT: RETURNS THE RESULTANT NUMBER FROM DOT PRODUCT
	DEFAULTS = NONE
	*/
	/******************************************************************************/
	T Dot(const Vector3D& rhs) const //Dot product
	{
		return x * (T)rhs.x + y * (T)rhs.y + z * (T)rhs.z;
	}

	/******************************************************************************/
	/*
	FINDING THE CROSS PRODUCT OF ONE VECTOR WITH ANOTHER
	INPUT: VECTOR
	OUTPUT: RETURNS THE RESULTANT VECTOR FROM THE CROSS PRODUCT
	DEFAULTS = NONE
	*/
	/******************************************************************************/
	Vector3D Cross(const Vector3D& rhs) const //Cross product
	{
		return Vector3D(y * (T)rhs.z - z * (T)rhs.y, z * (T)rhs.x - x * (T)rhs.z, x * (T)rhs.y - y * (T)rhs.x);
	}

	/******************************************************************************/
	/*
	NORMALIZING A VECOTR
	INPUT: NONE
	OUTPUT: RETURNS THE NORMALIZED VECTOR.
	DEFAULTS = NONE
	*/
	/******************************************************************************/
	Vector3D Normalized(void) const throw(DivideByZero)
	{
		T d = Magnitude();
		if (d == 0)
			throw DivideByZero();
		return Vector3D(x / d, y / d, z / d);
	}

	/******************************************************************************/
	/*
	NORMALIZING A VECTOR
	INPUT: NONE
	OUTPUT: RETURNS THE NORMALIZED VECTOR AND SETS IT TO THE VECTOR
	DEFAULTS = NONE
	*/
	/******************************************************************************/
	Vector3D& Normalize(void) throw(DivideByZero)
	{
		T d = Magnitude();
		if (d == 0)
			throw DivideByZero();
		x /= d;
		y /= d;
		z /= d;
		return *this;
	}
	/*************************************
	FRIEND FUNCTIONS DEFINED BELOW
	**************************************/

	/******************************************************************************/
	/*
	OPERATOR <<
	INPUT: VECTOR
	OUTPUT: PRINTS TO OSTREAM
	DEFAULTS = NONE
	*/
	/******************************************************************************/
	friend std::ostream& operator<<(std::ostream& os, Vector3D& rhs) //print to ostream
	{
		os << "[ " << rhs.x << ", " << rhs.y << ", " << rhs.z << " ]";
		return os;
	}

	/******************************************************************************/
	/*
	OPERATOR *
	INPUT: VECTOR AND SCALAR
	OUTPUT: RETURNS THE RESULATANT VECTOR
	NOTE: DIFFERENCE BETWEEN THIS AND THE ONES ABOVE ARE IN WAYS OF USING
	EG: 5 * VECTOR
	DEFAULTS = NONE
	*/
	/******************************************************************************/
	friend Vector3D operator*(T scalar, const Vector3D& rhs)
	{
		return rhs * (T)scalar;
	}

	/******************************************************************************/
	/*
	OPERATOR /
	INPUT: VECTOR AND SCALAR
	OUTPUT: RETURNS THE DIVIDED VALUE
	NOTE: DIFFERENCE BETWEEN THIS AND THE ONES ABOVE ARE IN WAYS OF USING
	EG: 5 / VECTOR
	DEFAULTS = NONE
	*/
	/******************************************************************************/
	friend Vector3D operator/(T scalar, const Vector3D& rhs)
	{
		return rhs / (T)scalar;
	}
};


