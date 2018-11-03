#ifndef NOVEMBERGAMEJAM_LOGGING_H
#define NOVEMBERGAMEJAM_LOGGING_H

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

bool is_file(std::string filename);

std::string get_filename(const std::string &filein);

bool create_directories(const std::string &full_path, std::string delim = "/");

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
    Logger(std::string logfile, T &stream, int stream_freq = 0) : logfile_(std::move(logfile)),
                                                                  stream_freq_(stream_freq),
                                                                                stream_(stream) {}


    bool write_header() {
        return write(Message("--------------------------\n",
                             "Logging started at: [TIME]"));
    }

    // Ideally, in the future all these methods (in all classes) would return an std::optional<Message>
    bool write(Message message) {
        if (stream_freq_ == 0) stream(message.string());

        buffer_.push_back(std::move(message));

        if (stream_freq_ > 0 && streamed_since_reset_ > 0 && streamed_since_reset_ % stream_freq_ == 0) {
            while (stream_counter_ < buffer_.size()) {
                stream(buffer_.at(stream_counter_++).string());
            }
            streamed_since_reset_ = 0;
        }
        else {
            streamed_since_reset_++;
        }

        return false;
    }

    void stream(std::string str) {
        stream_ << str << std::endl;
    }

    bool flush() {
        bool err = false;
        if (!logfile_.empty()) {
            std::ofstream f(logfile_, std::fstream::out | std::fstream::app);
            if (!f.good()) err = true;
            else {
                for (auto &&message : buffer_) {
                    f << message.string() << std::endl;
                }
            }
        }
        if (stream_freq_ < 0) {
            for (auto &&message : buffer_) {
                stream(message.string());
            }
        }
        buffer_.clear();
        return err;
    }

    ~Logger() { flush(); }

private:
    std::string logfile_;
    int stream_freq_;
    size_t stream_counter_ = 0;
    size_t streamed_since_reset_ = 0;
    T &stream_;
    std::vector<Message> buffer_;
};


#endif //NOVEMBERGAMEJAM_LOGGING_H
