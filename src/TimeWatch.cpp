#include "TimeWatch.hpp"
#include <iostream>
#include <iomanip>

wlib::TimeWatch::TimeWatch(const std::string & title, const size_t & average_samples) noexcept
    : title_(title), average_samples_(average_samples){}

void wlib::TimeWatch::start(void){
    this->start_ = std::chrono::system_clock::now();
    this->labels_.clear();
}

void wlib::TimeWatch::stop(void){
    this->stamp("end");
}

int64_t wlib::TimeWatch::stamp(const std::string & label){
    int64_t elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - this->start_).count();

    this->labels_.push_back(label);
    this->timestamps_[label].push_back(elapsed_time);
    if(this->timestamps_.at(label).size() >= this->average_samples_) this->timestamps_.at(label).pop_front();

    start_ = std::chrono::system_clock::now();
	return elapsed_time;
}

int64_t wlib::TimeWatch::get(const std::string & label) const{
    if(this->timestamps_.count(label)){
        if(this->timestamps_.at(label).size()) return *this->timestamps_.at(label).rbegin();
    }
    return -1;
}

void wlib::TimeWatch::printCSVHeader(std::ostream & out, const std::string & delimiter) const{
    std::string delim = "";
    for(auto p = this->labels_.begin(); p != this->labels_.end(); ++p){
        out << delim << *p;
        delim = delimiter;
    }
}

void wlib::TimeWatch::printCSVResult(std::ostream & out, const std::string & delimiter) const{
    std::string delim = "";
    for(auto p = this->labels_.begin(); p != this->labels_.end(); ++p){
        out << delim << *this->timestamps_.at(*p).rbegin();
        delim = delimiter;
    }
}

void wlib::TimeWatch::printDecoratedResult(std::ostream & out) const{
    //---------------------------------------
    // LABEL        | TIME(ms)   | DELTA(ms)
    //---------------------------------------
    // start        | 0          | 0
    // hogehoge     | 10         | 10
    // foobar       | 16         | 6
    // end          | 21         | 3
    //---------------------------------------
    out << "--------------------------------------------------------------------" << std::endl;
    out << " " << std::setw(30) << this->title_ << " | TIME(ms) | AVE" << std::setw(3) << std::right << this->average_samples_ << "(ms) | PEEK (ms)" << std::endl;
    out << "--------------------------------------------------------------------" << std::endl;

    int64_t delta_amount_ave = 0;
	int64_t total = 0;
	double total_ave = 0;
    for(auto p = this->labels_.begin(); p != this->labels_.end(); ++p){
        //平均を計算する
        size_t idx = 0;
        double ave = 0;
        int64_t max = 0;
        for(auto n = this->timestamps_.at(*p).rbegin(); n != this->timestamps_.at(*p).rend() && idx < this->average_samples_; ++n, ++idx){
            ave += *n;
            if(max < *n) max = *n;
        }
        ave /= idx;

		total += *this->timestamps_.at(*p).rbegin();
		total_ave += ave;

        out << " " << std::setw(30) << *p << " | "
            << std::setw(8) << std::right 
            << *this->timestamps_.at(*p).rbegin() << " | " 
            << std::setw(10) << std::right << std::fixed << std::setprecision(4) << ave
            << " | " << std::setw(9) << std::right << max
            << std::endl;
    }
	out << "--------------------------------------------------------------------" << std::endl;
	out << " " << std::setw(30) << "TOTAL" << " | "
		<< std::setw(8) << std::right
		<< total << " | "
		<< std::setw(10) << std::right << std::fixed << std::setprecision(4) << total_ave
		<< " | " << std::setw(9) << std::right << "---"
		<< std::endl;
	out << "--------------------------------------------------------------------" << std::endl;
}
