#ifndef SYSTEM_SYSTEM_H_
#define SYSTEM_SYSTEM_H_

#include "vector3D.h"
#include <map>
#include <string>



class System{
private:
	double q, gamma, t;
	Vector3D p, r, u;

public:
    //System(double q0, double g, double t0, Vector3D p0, Vector3D r0, Vector3D u0): q(q0), gamma(g), t(t0), p(p0), r(r0), u(u0){}
    System(){
		q = 1.6e-19;
		gamma = -1.76e11;
		t = 0;
        p = Vector3D{2.11e-30, 0, 0}; //2.11e-26 //8.11e-26
		r = Vector3D{0, 1e-9, 0};
        u = Vector3D{203428, 0, 100000}; //503428//8191289
    }

    System(std::map<std::string, double> parameters):
        q{-1.6e-19 * parameters["Q"]},
        gamma{-1.76e11 * parameters["Gamma"]},
        t{0.0},
        p{1e-30*parameters["P"], 0.0, 0.0},
        r{1e-9 * parameters["X0"],1e-9 * parameters["Y0"],1e-9 * parameters["Z0"]},
        u{parameters["Ux0"], parameters["Uy0"], parameters["Uz0"]}
    {

    }

    double Q() const{return q;}
    double Gamma() const{return gamma;}
    double T() const{return t;}
    double X() const {return r.getx();}
    double Y() const {return r.gety();}
    double Z() const {return r.getz();}
    Vector3D R() {return r;}
    double P() const{return p.length();}
    double Ux() const {return u.getx();}
    double Uy() const {return r.gety();}
    double Uz() const {return r.getz();}
    Vector3D U() const{return u;}



	Vector3D func1(Vector3D R);  //как в задаче

	double LOEC();

	void RK4_step(double dt);



};


#endif /* SYSTEM_SYSTEM_H_ */
