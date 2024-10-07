#include<bits/stdc++.h>
using namespace std;

class Joint{
	public:
		vector<Member> members;
		vector<float> angles;
		vector<Force> forces;
		RollerSupport connecting_roller;
		PinSupport connecting_pin;

		Joint(vector<Member> cms, vector<float> a, vector<Force> fs, RollerSupport rs, PinSupport ps){
			members = cms;
			angles = a;
			forces = fs;
			connecting_roller = rs;
			connecting_pin = ps;
		}
};

class RollerSupport{
	public:
		Joint connecting_joint;
		float fy;

		RollerSupport(Joint j){
			connecting_joint = j;
		}
};

class PinSupport{
	public:
		Joint connecting_joint;
		float fx, fy;

		PinSupport(Joint j){
			connecting_joint = j;
		}
};

class Member{
	public:
		float angle; // angle is with horizontal
		float length;
		float fx, fy;


		Member(float a; float l){
			length = l;
			angle = a;
		}
};

class Force{
	public:
		Joint application_joint;
		float magx;
		float magy;

		Force(Joint aj, float mx, float my){
			magx = mx;
			magy = my;
			application_joint = aj;
		}
};

class Member_force_info{
	public:
		Member m;
		float magx;
		float magy;
		Member_force_info(Member mem, float mx, float my){
			m = mem;
			magx = mx;
			magy = my;
		}
};

class Truss{
	public:
		vector<Member> Members;
		vector<Joint> Joints;
		vector<RollerSupport> RollerSupports;
		vector<PinSupport> PinSupports;
		vector<Force> forces;

		bool is_valid = true;

		// answer
		vector<Member_force_info> force_in_members;

		Truss(vector<Member> ms, vector<Joint> js, vector<RollerSupport> rss, vector<PinSupport> pss){
			Members = ms;
			Joints = js;
			RollerSupports = rss;
			PinSupports = pss;

			for(int i=0;i<ms.size();i++){
				pair<Member, int> temp;
				temp.first = ms[i];
				force_in_members.push_back(temp);
			}

			is_valid = check_validity();
		}

		bool check_validity(){
			return true;
		}

		// answer calculation
		void calculate(){

			bool done = false;

			while (!done) {

			for(int i=0; i<Joints.size(); i++){
				done = true;
			
				float fx = 0, fy = 0;
				vector<Member> unknowns;
				vector<int> unknowns_idx;

				// unknowns amongst pin supports
				if (!Joints[i]->connecting_roller->fy){
					unknowns.push_back(connecting_roller);
				}else{
					fy += Joints[i]->connecting_roller->fy;
				}
				

				// unknowns amongst roller supports
				if (!Joints[i]->connecting_pin->fx){
					unknowns.push_back(connecting_pin);
				}else{
					fx += Joints[i]->connecting_pin->fx;
					fx += Joints[i]->connecting_pin->fy;
				}

				// unknowns amongst members
				for(int j=0; j<Joints[i]->members.size(); j++){
					if(!Joints[i]->members[j]->fx){
						unknowns.push_back(Joints[i]->members[j]);
						unknowns_idx.push_back(j);
					}
					else {
						fx += Joints[i]->members[j]->fx;
						fy += Joints[i]->members[j]->fy;
					}
				}

				if (unknowns.size() < 3 && 0 < unknowns.size()){

					// calculating external forces
					for(int j=0; j<Joints[i]->forces.size(); j++){
						fx += Joints[i]->forces[j]->magx;
						fy += Joints[i]->forces[j]->magy;
					}

					// calculating unknowns
					//
					//
					/*
					 *valid if all are members (not rollers or pins)
					 * if(unknowns.size() == 2) {
						float a1 = unknowns[0]->angle;
						float a2 = unknowns[1]->angle;

						float f1 = ( fy*cos(a2) - fx*sin(a2) ) / ( cos(a1)*sin(a2) - sin(a1)*cos(a2) )
						float f2 = ( fy*cos(a1) - fx*sin(a1) ) / ( cos(a2)*sin(a1) - sin(a2)*cos(a1) )

						Joints[i]->members[unknown_idx[0]]->fx = f1*cos(a1);
						Joints[i]->members[unknown_idx[0]]->fy = f1*sin(a1);
						Joints[i]->members[unknown_idx[1]]->fx = f2*cos(a2);
						Joints[i]->members[unknown_idx[1]]->fy = f2*sin(a2);
					}else if(unknowns.size() == 1){
						Joints[i]->members[unknown_idx[0]]->fx = -fx;
						Joints[i]->members[unknown_idx[0]]->fy = -fy;
					}*/

				}else {
					done = false;
				}


			}
			}
		}

};

int main(){
	
	return 0;
}
