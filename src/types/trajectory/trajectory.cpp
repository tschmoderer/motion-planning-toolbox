#include "../../../include/header/types/trajectory/trajectory.h"

/* CONSTRUCTORS */
Trajectory::Trajectory() {
    this->time_ = TimeVector();
    this->data_ = StateMatrix(); 
    this->interp_ = Interpolator1D(INTERP_LINEAR, EXTEND_ZERO, EXTEND_ZERO); 
}

Trajectory::Trajectory(TimeVector t, StateMatrix d, interpolation_method_t im, extend_t el, extend_t er) {
    this->time_ = t;
    this->data_ = d; 
    this->interp_ = Interpolator1D(im, el, er); 
}

Trajectory::Trajectory(const Trajectory & traj) {
    this->time_ = traj.time_; 
    this->data_ = traj.data_; 
    this->interp_ = traj.interp_; 
}

/* DESTRUCTOR */
Trajectory::~Trajectory() {}

/* ACCESSORS */
TimeVector Trajectory::get_time() const {
    return this->time_; 
}

StateMatrix Trajectory::get_data() const {
    return this->data_; 
}

void Trajectory::set_interpolation_method(interpolation_method_t im, extend_t el, extend_t er) {
    this->interp_.set_method(im);
    this->interp_.set_exleft(el); 
    this->interp_.set_exright(er);
}

/* METHODS */
StateVector Trajectory::evaluate(Time_t t) const {
    assert(this->time_.size() == this->data_.rows()); 
    
    StateVector res(this->data_.cols());
    //StateVector * col_data = new StateVector(this->data_.rows());
    StateVector col_data(this->data_.rows());

    for (int j = 0; j < this->data_.cols(); j++) {
        for (int i = 0; i < this->data_.rows(); i++) {
            col_data(i) = this->data_(i,j);
        }
        res(j) = this->interp_.interp1d<StateVector, State_t>(&this->time_, &col_data, t); 
    }

    return res;
} 

StateVector Trajectory::endpoint() const {
    assert(this->time_.size() == this->data_.rows()); 
    //StateVector * res = new StateVector(this->data_.cols()); 
    StateVector res(this->data_.cols()); 
    for (int j = 0; j < this->data_.cols(); j++) {
        res = this->data_(this->data_.rows()-1, j);
    }
    return res;
}