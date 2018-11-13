#include <utility>

#ifndef NOVEMBERGAMEJAM_LOGGING_H
#define NOVEMBERGAMEJAM_LOGGING_H

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>

bool create_directories(const std::string &full_path, std::string delim = "/");

class Message {
public:
    static inline Message close(std::string reason = "") {
        return Message("Closing application.", (reason.empty()) ? "" : " Reason: \n\t" + std::move(reason) + ".");
    }

    static inline Message key_pressed(std::string key) {
        return Message("Key pressed: ", std::move(key));
    }

    static inline Message warning(std::string message) {
        return Message("Warning: ", std::move(message));
    }

public:
    template<typename... Ts>
    explicit Message(Ts... messages) {
        std::ostringstream ss;
        add_to_ss(ss, messages...);
        message_ = std::move(ss.str());
    }

    const std::string &string() { return message_; }
    void prepend(std::string str) { message_ = str + message_; }

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
                                                                  stream_(stream),
                                                                  no_log_(logfile_.empty()) {}

    bool write_header() {
        auto time = std::time(nullptr);
        return write(Message("---------------------------------------\n",
                             "Logging started at: ",
                             std::put_time(std::localtime(&time),
                                           "%d-%m-%Y %H:%M:%S")));
    }

    void prepend(std::string str) { prepend_ += str; }

    void clear_prepend() { prepend_ = ""; }

    // Ideally, in the future all these methods (in all classes) would return an std::optional<Message>
    bool write(Message message) {
        // Check if we want to prepend this message with something.
        if (prepend_ != "") {
            message.prepend(prepend_);
            clear_prepend();
        }

        // If we stream every message, just write it out.
        if (stream_freq_ == 0) stream(message.string(), true);

        // If we need a buffer to stream, or we are logging, add the message to the buffer.
        if (stream_freq_ > 0 || !no_log_) buffer_.push_back(std::move(message));

        // If we stream every stream_freq_ messages, check if we've hit that number, then stream the buffer subsection.
        if (stream_freq_ > 0 && streamed_since_reset_ > 0 && streamed_since_reset_ % stream_freq_ == 0) {
            while (stream_counter_ < buffer_.size()) {
                stream(buffer_.at(stream_counter_++).string());
            }
            flush_stream();
            streamed_since_reset_ = 0;

            // If we don't log, just empty the buffer now.
            if (no_log_) {
                // Make sure to make the counter 0 again.
                stream_counter_ = 0;
                buffer_.clear();
            }
        } else {
            streamed_since_reset_++;
        }

        return false;
    }

    void stream(std::string str, bool flush = false) {
        stream_ << str << '\n';
        if (flush) flush_stream();
    }

    void flush_stream() {
        stream_ << std::flush;
    }

    bool flush() {
        bool err = false;
        if (!logfile_.empty() && !buffer_.empty()) {
            std::ofstream f(logfile_, std::fstream::out | std::fstream::app);
            if (!f.good()) err = true;
            else {
                for (auto &&message : buffer_) {
                    f << message.string() << '\n';
                }
                f << std::flush;
            }
        }
        if (stream_freq_ < 0) {
            for (auto &&message : buffer_) {
                stream(message.string());
            }
            flush_stream();
        }
        buffer_.clear();
        return err;
    }

    ~Logger() { flush(); }

private:
    std::string logfile_; // Do not change the order of this & no_log_
    bool no_log_;
    int stream_freq_;
    size_t stream_counter_ = 0;
    size_t streamed_since_reset_ = 0;
    T &stream_;
    std::vector<Message> buffer_;
    std::string prepend_ = "";
};


#endif //NOVEMBERGAMEJAM_LOGGING_H
