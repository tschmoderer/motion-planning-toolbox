#include "../../include/header/common/outputHelper.h"

/**
 * @brief Construct a new Output Helper:: Output Helper object
 * 
 * @param c 
 * @param out output file string format can be : 
 * "file.ext"
 * "../file.ext"
 * "./relative/path/file.ext"
 * "/absolute/path/file.ext"
 * 
 * @warning If necessary the OutputHelper object will create the subdirectories
 * @warning Notice that relative path are relative with respect to where you launch the program 
 * and not where the exe is located
 */
OutputHelper::OutputHelper(const Controls & c, string out, string tsout) {
    this->time_ = c.get_time();
    this->data_ = c.get_data();
    this->type_t = control;

    this->set_output_structure(out); 
    this->set_output_structure_ts(tsout); 
    this->create_output_dir();
}

OutputHelper::OutputHelper(const Trajectory & t, string out, string tsout) {
    this->time_ = t.get_time();
    this->data_ = t.get_data();
    this->type_t = trajectory;

    this->set_output_structure(out); 
    this->set_output_structure_ts(tsout); 
    this->create_output_dir();
}

/* DESTRUCTOR */
OutputHelper::~OutputHelper() {}

/* ACCESSORS */
OutputHelper OutputHelper::format(Eigen::IOFormat iof) {
    this->fmt = iof;
    return *this;
}

/* METHODS */
void OutputHelper::save(int exp_nb) const {
    // a modified save function where a number is added before the extension in the filename
    ofstream myfile;
    string fname;

    fname = this->exp_filename_ts(exp_nb);
    myfile.open(fname);
    //myfile << this->make_data().format(this->fmt);
    myfile << this->time_.format(this->fmt);
    myfile.close();

    cout << "Timestamps successfully saved in " << fname << endl;
    
    fname = this->exp_filename(exp_nb);
    myfile.open(fname);
    //myfile << this->make_data().format(this->fmt);
    myfile << this->data_.format(this->fmt);
    myfile.close();

    cout << "Data successfully saved in " << fname << endl;
}

/* OPERATORS */
std::ostream & operator<<(std::ostream & os, const OutputHelper & oh) {
    assert(oh.time_.size() == oh.data_.rows());

    os << oh.make_data().format(oh.fmt);
    
    return os;
}

MatrixXd OutputHelper::make_data() const {
    MatrixXd dat(this->time_.size(), this->data_.cols()+1); 

    dat(Eigen::all, 0) = this->time_;
    dat(Eigen::all, Eigen::seq(1, Eigen::last)) = this->data_;

    return dat;
}

void OutputHelper::set_output_structure(string out) {
    this->out_file_ = out; 
    size_t pos = out.find_last_of('/');
    this->out_dir_ = out.substr(0, pos);

    this->filename_ = out.substr(pos);
    pos = this->filename_.find_last_of('.');
    this->fileext_ = this->filename_.substr(pos+1);
    this->filename_ = this->filename_.substr(1,pos-1);
}

void OutputHelper::set_output_structure_ts(string tsout) {
    this->ts_out_file_ = tsout; 
    size_t pos = tsout.find_last_of('/');

    this->ts_filename_ = tsout.substr(pos);
    pos = this->ts_filename_.find_last_of('.');
    this->ts_fileext_ = this->ts_filename_.substr(pos+1);
    this->ts_filename_ = this->ts_filename_.substr(1,pos-1);
}

void OutputHelper::create_output_dir() const {
    fs::create_directories(this->out_dir_);
}

string OutputHelper::exp_filename(int exp_nb) const {
    string res; 
    res = this->out_dir_ + "/" + this->filename_ + "-"; 
    res += to_string(exp_nb);
    res += "." + this->fileext_;
    return res; 
}

string OutputHelper::exp_filename_ts(int exp_nb) const {
    string res; 
    res = this->out_dir_ + "/" + this->ts_filename_ + "-"; 
    res += to_string(exp_nb);
    res += "." + this->ts_fileext_;
    return res; 
}