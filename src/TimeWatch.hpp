///
/// @fn TimeWatch.hpp
/// @author Shirao Shotaro
/// @version 0.1.1
///

#ifndef WLIB_TIMEWATCH_HPP
#define WLIB_TIMEWATCH_HPP

#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include <chrono>

namespace wlib{

///
/// @brief Utility class of measuring processing times.
///
class TimeWatch{
public:

	///
    /// @brief Constructor
    ///
    /// @param title [in] Timewatch instance name.
    /// @param average_samples [in] Amount of sample for calculating average and maximum time.
    ///
    explicit TimeWatch(const std::string & title = "", const size_t & average_samples = 20) noexcept;

    ///
    /// @brief Destructor
    ///
    virtual ~TimeWatch(void) = default;

    ///
    /// @brief Reset and start this watch.
    ///
    void start(void);

    ///
    /// @brief Stop this watch.
    ///
    void stop(void);

    ///
    /// @brief Stamp elapsed time.
    ///
    /// @param label [in] time label.
    ///
    /// @return Elapsed time (ms)
    ///
    virtual int64_t stamp(const std::string & label);

    ///
    /// @brief Get the elapsed time by label.
    ///
	/// When you put unexisting labell, this function returns -1 and does never report any errors.
	///
    /// @param label [in] target label
    ///
    /// @return Elapsed time (ms)
    ///
    int64_t get(const std::string & label) const;

    ///
    /// @brief Output the CSV Header.
    ///
	/// Generate and output csv header from labels.
    /// If you want to output data to csv, use printResultCSV().
    ///
    /// @param out_stream [out] output stream instance
    /// @param delimiter [in] the delimiter string of data.
    ///
	/// @sa printResultCSV()
	///
    void printCSVHeader(std::ostream & out_stream, const std::string & delimiter = ",") const;

    ///
    /// @brief Output data to CSV.
    ///
    /// When you want to dump speed data, you can use this function.
    ///
    /// @param out [out] output stream instance
    /// @param delimiter [in] the delimiter string of data.
    ///
    void printCSVResult(std::ostream & out_stream, const std::string & delimiter = ",") const;

    ///
    /// @brief Output decorated results.
    ///
	/// You can implement inheritance classes.
    ///
	/// @param out_stream [out] output stream instance
    ///
    virtual void printDecoratedResult(std::ostream & out_stream) const;

	/////// GETTER ////////
	/// @brief Getter of title.
	std::string getTitle(void) const { return this->title_; }

	/// @brief Getter of average samples count.
	size_t getAverageSamplesNum(void) const { return this->average_samples_; }
	
	/// @brief Getter of current labels.
	const std::vector<std::string> & getLabels(void) const { return this->labels_; }

protected:

	std::vector<std::string> labels_;
    std::unordered_map<std::string, std::list<int64_t>> timestamps_;
    std::chrono::system_clock::time_point start_;

private:
    const size_t average_samples_;
    const std::string title_;
};

}

#endif
