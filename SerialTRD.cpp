//============================================================================
// Name        : SerialTRD.cpp
// Author      : Tomohiro Suzuki
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <Eigen/Core>

int main( int argc, char* argv[] )
{
	if (argc < 3)
	{
		std::cerr << "Usage: a.out [size of matrix] [band width]\n";
		exit(EXIT_FAILURE);
	}
	const int m = atoi(argv[1]);
	const int l = atoi(argv[2]) -1;

	assert(m>0);
	assert(l>0);
	assert(m>l);

	Eigen::MatrixXd A = Eigen::MatrixXd::Random(m,m);
	std::cout << A << std::endl << std::endl;

	Eigen::MatrixXd T(m,m);
	Eigen::VectorXd x(m);

	for (int k=0; k<m-l; k++)
	{
		x.resize(m-(l+k));
		T.resize(m-(l+k),m-k);
		////////////////////////////////////////////
		// QR
		for (int i=0; i<m-(l+k); i++)
			x[i] = A((l+k)+i,k);

		x[0] += ((x[0] >= 0.0) ? 1.0 : -1.0)*x.norm();
		x /= x.norm();

		for (int i=0; i<m-(l+k); i++)
			for (int j=0; j<m-k; j++)
				T(i,j) = A((l+k)+i,j+k);

		T -= 2.0*x*(x.transpose()*T);

		for (int i=0; i<m-(l+k); i++)
			for (int j=0; j<m-k; j++)
				A((l+k)+i,j+k) = T(i,j);
		std::cout << A << std::endl << std::endl;

		////////////////////////////////////////////
		// LQ
		for (int i=0; i<m-(l+k); i++)
			x[i] = A(k,(l+k)+i);

		x[0] += ((x[0] >= 0.0) ? 1.0 : -1.0)*x.norm();
		x /= x.norm();

		for (int i=0; i<m-(l+k); i++)
			for (int j=0; j<m-k; j++)
				T(i,j) = A(j+k,(l+k)+i);

		T -= 2.0*x*(x.transpose()*T);

		for (int i=0; i<m-(l+k); i++)
			for (int j=0; j<m-k; j++)
				A(j+k,(l+k)+i) = T(i,j);
		std::cout << A << std::endl << std::endl;
	}


	return EXIT_SUCCESS;
}
