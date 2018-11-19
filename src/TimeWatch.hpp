///
/// @fn TimeWatch.hpp
/// @brief 時間計測を行うクラスのヘッダファイル
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
/// @brief 処理時間を調べるためのクラス
///
/// インスタンスを生成し、ラベルを登録することで、後でデータ化しやすくするものです
///
class TimeWatch{
public:

    /// @brief コンストラクタ
    ///
    /// ラベルを指定し、今後スナップショットを取る際はそのラベルと一緒に指定します。
    /// ラベルは、start、stopは予約されています。
    /// ラベルの重複は許可されません。
    ///
    /// @param title [in] Timewatch instance name.
    /// @param average_samples [in] Amount of sample for calculating average.
    ///
    explicit TimeWatch(const std::string & title = "", const size_t & average_samples = 20) noexcept;

    ///
    /// @brief Destructor
    ///
    ~TimeWatch(void) = default;

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
    int64_t stamp(const std::string & label);

    ///
    /// @brief Get the elapsed time from label.
    ///
    /// @param label [in] target label
    ///
    /// @return Elapsed time (ms)
    ///
    int64_t get(const std::string & label) const;

    ///
    /// @brief CSVのヘッダを出力する
    ///
    /// printResultCSV()はデータのみ出力するため、ヘッダを出力する場合はこの関数を使用してください。
    ///
    /// @param out_stream [out] output stream instance
    /// @param delimiter delimiter of data.
    ///
    void printCSVHeader(std::ostream & out_stream, const std::string & delimiter = ",") const;

    ///
    /// @brief 計測結果をプリントする
    ///
    /// 引数のストリームに対して出力します。データ用として利用するのに最適なCSV形式にして出力します。
    ///
    /// @param out 出力ストリーム
    /// @param delimiter CSVの区切り文字
    ///
    void printCSVResult(std::ostream & out_stream, const std::string & delimiter = ",") const;

    ///
    /// @brief 計測結果を装飾して出力する
    ///
    /// 引数のストリームに対して出力します。
    /// 表示用として確認するのに最適にフォーマットします。
    /// @param out 出力ストリーム
    ///
    void printDecoratedResult(std::ostream & out) const;

private:
    const size_t average_samples_;
    const std::string title_;

    std::vector<std::string> labels_;
    std::unordered_map<std::string, std::list<int64_t>> timestamps_;
    std::chrono::system_clock::time_point start_;
};

}

#endif
