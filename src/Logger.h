#ifndef NOVEMBERGAMEJAM_LOGGING_H
#define NOVEMBERGAMEJAM_LOGGING_H

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

bool is_file(std::string filename);

std::string get_filename(const std::string &filein);

class Message {
public:
    template<typename... Ts>
    explicit Message(Ts... messages) {
        std::ostringstream ss;
        add_to_ss(ss, messages...);
        message_ = std::move(ss.str());
    }

    const std::string &string() { return message_; }

private:
    template<typename T>
    void add_to_ss(std::ostringstream &ss, T message) {
        ss << message;
    }

    template<typename T, typename... Ts>
    void add_to_ss(std::ostringstream &ss, T message, Ts... messages) {
        add_to_ss(ss, message);
        add_to_ss(ss, messages...);
    }

private:
    std::string message_;
};

template<typename T>
class Logger {
public:
    Logger(std::string logfile, T &stream, bool stream_only_on_flush = false) : logfile_(std::move(logfile)),
                                                                                 auto_stream_(stream_only_on_flush),
                                                                                 stream_(stream) {}

    bool write(Message message) {
        if (auto_stream_) stream_ << message.string() << std::endl;
        buffer_.push_back(std::move(message));
        return false;
    }

    bool flush(bool overwrite = false) {
        bool err = false;
        if (!logfile_.empty()) {
            if (is_file(get_filename(logfile_)) && !overwrite) err = true;
            else {
                std::ofstream f(logfile_);
                if (!f.good())
                {
                    err = true;
                }
                else {
                    for (auto &&message : buffer_) {
                        f << message.string() << std::endl;
                    }
                }
            }

        }
        if (!auto_stream_) {
            for (auto &&message : buffer_) {
                stream_ << message.string() << std::endl;
            }
        }
        buffer_.clear();
        return err;
    }

private:
    std::string logfile_;
    bool auto_stream_;
    T &stream_;
    std::vector<Message> buffer_;
};


#endif //NOVEMBERGAMEJAM_LOGGING_H
