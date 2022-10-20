#include "../../include/header/trajectory/trajectory.h"

Trajectory::Trajectory() {
    this->interp_ = Interpolator1D(INTERP_LINEAR, EXTEND_ZERO, EXTEND_ZERO);
}

Trajectory::Trajectory(VectorXd t, MatrixXd d) {
    this->time_ = t; 
    this->data_ = d; 
    this->interp_ = Interpolator1D(INTERP_LINEAR, EXTEND_ZERO, EXTEND_ZERO);
} 

Trajectory::Trajectory(const Trajectory & traj) {
    this->time_ = traj.time_;
    this->data_ = traj.data_; 
    this->interp_ = traj.interp_;
}

Trajectory::~Trajectory() {} 

void Trajectory::set_interpolation_method(interpolation_method_t im, extend_t el, extend_t er) {
    this->interp_.set_method(im);
    this->interp_.set_exleft(el); 
    this->interp_.set_exright(er);
}

VectorXd Trajectory::evaluate(double t) const {
    assert(this->time_.size() == this->data_.rows()); 
    VectorXd res(this->data_.cols());
    VectorXd col_data(this->data_.rows());
    for (int i = 0; i < this->data_.cols(); i++) {
        col_data =  this->data_.col(i);
        res(i) = this->interp_.interp1d(&this->time_, &col_data, t); 
    }
    return res;
} 

std::ostream & operator<<(std::ostream & os, const Trajectory & traj) {
    assert(traj.time_.size() == traj.data_.rows());
    for (int i = 0; i < traj.time_.size(); i++) {
        os << traj.time_(i);
        for (int j = 0; j < traj.data_.cols(); j++) {
            os << "\t" << traj.data_(i,j);
        }    
        os << std::endl;
    }
    return os;
}