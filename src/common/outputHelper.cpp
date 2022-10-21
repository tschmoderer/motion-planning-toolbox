#include "../../include/header/common/outputHelper.h"

OutputHelper::OutputHelper(const Controls & c) {
    this->time_ = c.get_time();
    this->data_ = c.get_data();
}
OutputHelper::OutputHelper(const Trajectory & t) {
    this->time_ = t.get_time();
    this->data_ = t.get_data();
}

/* DESTRUCTOR */
OutputHelper::~OutputHelper() {}

/* ACCESSORS */
void OutputHelper::format(Eigen::IOFormat iof) {
    this->fmt = iof;
}

/* OPERATORS */

std::ostream & operator<<(std::ostream & os, const OutputHelper & oh) {
    assert(oh.time_.size() == oh.data_.rows());
    MatrixXd dat(oh.time_.size(), oh.data_.cols()+1); 
    dat(Eigen::all, 0) = oh.time_;
    dat(Eigen::all, Eigen::seq(1, Eigen::last)) = oh.data_;

    os << dat.format(oh.fmt);
    
    return os;
}