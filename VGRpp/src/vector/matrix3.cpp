#include "../../inc/vector/matrix3.h"

#include <cstring>
#include <sstream>

#define SIZE_MAT_3 	(9 * sizeof(double))
#define AT(i,j)		(i * 3 + j)

Matrix3::Matrix3(double e[])
{
	memcpy(this->e_, e, SIZE_MAT_3 );
}

Matrix3::Matrix3()
{
	//Cascade constructors?
	double eye[] = {1,0,0,0,1,0,0,0,1};
	memcpy(this->e_, eye, SIZE_MAT_3 );
}

void Matrix3::set(double e[])
{
	memcpy(this->e_, e, SIZE_MAT_3 );
}

double Matrix3::at(unsigned int i, unsigned int j) const
{
	//(!!!) Watch out for i and j out of bounds!
	return this->e_[ AT(i,j) ];
}

double Matrix3::at(unsigned int i) const
{
	return this->e_[i];
}

void Matrix3::operator=(const Matrix3& lhs)
{
	for(int i = 0; i < 9; i++)
		this->e_[i] = lhs.at(i);
}

Matrix3 Matrix3::operator*(const Matrix3& rhs) const
{
	double out[] = { e_[0]*rhs.at(0) + e_[1]*rhs.at(3) + e_[2]*rhs.at(6), e_[0]*rhs.at(1) + e_[1]*rhs.at(4) + e_[2]*rhs.at(7), e_[0]*rhs.at(2) + e_[1]*rhs.at(5) + e_[2]*rhs.at(8),
					e_[3]*rhs.at(0) + e_[4]*rhs.at(3) + e_[5]*rhs.at(6), e_[3]*rhs.at(1) + e_[4]*rhs.at(4) + e_[5]*rhs.at(7), e_[3]*rhs.at(2) + e_[4]*rhs.at(5) + e_[5]*rhs.at(8),
					e_[6]*rhs.at(0) + e_[7]*rhs.at(3) + e_[8]*rhs.at(6), e_[6]*rhs.at(1) + e_[7]*rhs.at(4) + e_[8]*rhs.at(7), e_[6]*rhs.at(2) + e_[7]*rhs.at(5) + e_[8]*rhs.at(8) };
	return Matrix3(out);
}

Matrix3 Matrix3::operator*(double s) const {
	double out[9];
	for(int i = 0; i < 9; i++)
		out[i] = e_[i] * s;
	return Matrix3(out);
}

Vec3 Matrix3::apply(const Vec3& v) const
{
	Vec3 out;
	out.setX( e_[0] * v.x() + e_[1] * v.y() + e_[2] * v.w() );
	out.setY( e_[3] * v.x() + e_[4] * v.y() + e_[5] * v.w() );
	out.setW( e_[6] * v.x() + e_[7] * v.y() + e_[8] * v.w() );

	return out;
}

std::string Matrix3::mat2str() const
{
	std::stringstream ss("");

	ss<<"{";
	for(int i = 0; i < 3; i++)
	{
		ss<<"{";
		for(int j = 0; j < 3; j++)
			ss<<this->e_[i*3 + j]<<", ";
		ss<<"} ";
	}
	ss<<"}";

	return ss.str();
}

Matrix3 Matrix3::inv() const {
	//Thanks wikipedia for the formula
	double A = e_[4]*e_[8] - e_[5]*e_[7];
	double B = -(e_[3]*e_[8] - e_[5]*e_[6]);
	double C = e_[3]*e_[7] - e_[4]*e_[6];
	double D = -(e_[1]*e_[8] - e_[2]*e_[7]);
	double E = e_[0]*e_[8] - e_[2]*e_[6];
	double F = -(e_[0]*e_[7] - e_[1]*e_[6]);
	double G = e_[1]*e_[5] - e_[2]*e_[4];
	double H = -(e_[0]*e_[5] - e_[2]*e_[3]);
	double I = e_[0]*e_[4] - e_[1]*e_[3];

	double det = e_[0]*A + e_[1]*B + e_[2]*C;

	double out[] = {A/det, D/det, G/det,
					B/det, E/det, H/det,
				 	C/det, F/det, I/det};

	return Matrix3(out);
}

Matrix3 Matrix3::transpose() const {
	double out[] = {e_[0], e_[3], e_[6],
					e_[1], e_[4], e_[7],
					e_[2], e_[5], e_[8]};

	return Matrix3(out);
}