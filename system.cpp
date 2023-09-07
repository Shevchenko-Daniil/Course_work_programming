#include "system.h"
#include <cmath>
#include <iostream>



const double k(9e9);

Vector3D System::func1(Vector3D R){          //как в задаче- с дипольным моментом
	Vector3D d2r = gamma*k*( R * (3*scalprod(p, R) + q*R.length()*R.length())/pow(R.length(), 5) - p/pow(R.length(), 3)  );
	return d2r;
}


/*double System::LOEC(Vector3D R0, Vector3D U0){
	return U0.length() * U0.length() + 2*gamma*k*(scalprod(p, R0)/pow(R0.length(), 3) - scalprod(p, r)/pow(r.length(), 3) + q*(1/R0.length() - 1/(r.length())));
}*/

double System::LOEC(){
	return u.length()*u.length()/2 + gamma*k*scalprod(p, r)/pow(r.length(), 3) + gamma*k*q/r.length();
}


void System::RK4_step(double dt){
	Vector3D u0 = u;

	Vector3D k1, k2, k3, k4, l1, l2, l3, l4;

	k1 = u0;
	l1 = func1(r);
	k2 = u0 + 0.5*dt*l1;
	l2 = func1(r + 0.5*dt*k1);
	k3 = u0 + 0.5*dt*l2;
	l3 = func1(r + 0.5*dt*k2);
	k4 = u0 + dt*l3;
	l4 = func1(r + dt*k3);


	r += dt*(k1 + 2*k2 + 2*k3 + k4)/6;
	u += dt*(l1 + 2*l2 + 2*l3 + l4)/6;
	t += dt;

}

