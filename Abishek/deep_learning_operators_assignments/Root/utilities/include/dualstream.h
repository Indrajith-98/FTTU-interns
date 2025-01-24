#ifndef DUAL_STREAMBUF_H
#define DUAL_STREAMBUF_H

#include <iostream>
#include <fstream>
#include <streambuf>

// Custom streambuf to duplicate output to console and file
class DualStreambuf : public std::streambuf {
private:
    std::streambuf* console_buf; // Original console buffer
    std::streambuf* file_buf;    // File buffer
public:
    // Constructor
    DualStreambuf(std::streambuf* console_buf, std::streambuf* file_buf)
        : console_buf(console_buf), file_buf(file_buf) {}

    // Override overflow to duplicate characters
    int overflow(int c) override {
        if (c != EOF) {
            if (console_buf) console_buf->sputc(c);
            if (file_buf) file_buf->sputc(c);
        }
        return c;
    }

    // Synchronize both streams
    int sync() override {
        if (console_buf) console_buf->pubsync();
        if (file_buf) file_buf->pubsync();
        return 0;
    }
};

// Utility function to set up dual logging
class Logger {
private:
    std::ofstream log_file;
    DualStreambuf* dual_buf;
    std::streambuf* original_buf;

public:
    Logger(const std::string& file_name) : dual_buf(nullptr), original_buf(nullptr) {
        log_file.open(file_name, std::ios::out);
        if (!log_file.is_open()) {
            throw std::ios_base::failure("Failed to open log file: " + file_name);
        }
        // Save original buffer and redirect
        original_buf = std::cout.rdbuf();
        dual_buf = new DualStreambuf(original_buf, log_file.rdbuf());
        std::cout.rdbuf(dual_buf);
    }

    ~Logger() {
        // Restore original buffer and clean up
        if (original_buf) std::cout.rdbuf(original_buf);
        delete dual_buf;
        if (log_file.is_open()) log_file.close();
    }
};

#endif // DUAL_STREAMBUF_H