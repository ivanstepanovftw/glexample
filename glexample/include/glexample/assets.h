//
// Created by ivan on 12.01.2020.
//

#pragma once

#include <vector>
#include <deque>
#include <filesystem>

// TODO: remove
namespace fs = std::filesystem;


class AssetManager {
public:
    AssetManager() noexcept
    : AssetManager(true) {};

    explicit AssetManager(bool recursive) noexcept {
      AssetManager::recursive(recursive);
      AssetManager::add(fs::current_path());
    }

    bool add(const std::filesystem::path &pathname) {
      if (!fs::exists(pathname))
        return false;
      m_locators.push_back(pathname);
      return true;
    }

    //bool add(const std::string& url) {
    //}

    void remove(const std::filesystem::path &pathname) {
      m_locators.erase(std::remove(m_locators.begin(), m_locators.end(), pathname), m_locators.end());
      m_excluded.erase(std::remove(m_excluded.begin(), m_excluded.end(), pathname), m_excluded.end());
    }

    //void remove(const std::string& url) {
    //}

    void exclude(const std::filesystem::path &pathname) {
      remove(pathname);
      m_excluded.push_back(pathname);
    }

    void clear() {
      m_locators.clear();
      m_excluded.clear();
    }

    void recursive(bool enable) {
      m_recursive = enable;
    }

    [[nodiscard]] bool recursive() const {
      return m_recursive;
    }

    void limit(size_t count) {
      m_limit = count;
    }

    [[nodiscard]] size_t limit() const {
      return m_limit;
    }

    [[nodiscard]] fs::path find(const std::string &filename) const {
      if (m_locators.empty()) {
        return fs::path();
      }
      for (const auto &p1 : m_locators) {
        if (fs::is_directory(p1)) {
          if (m_recursive) {
            for (const auto &p2 : fs::recursive_directory_iterator(p1)) {
              if (check(p2, filename)) {
                return p2.path();
              }
            }
          } else {
            for (const auto &p2 : fs::directory_iterator(p1)) {
              if (check(p2, filename)) {
                return p2.path();
              }
            }
          }
        } else {
          if (check(p1, filename)) {
            return p1;
          }
        }
      }
      return fs::path();
    }

private:
    /**
     * NON-RECURSIVE
     */
    [[nodiscard]] bool excluded(const fs::path& pathname) const {
        for (const auto &p : m_excluded) {
          if (p == pathname)
            return true;
        }
        return false;
    }

    [[nodiscard]] bool check(const fs::path& p1, const std::string& filename) const {
      m_limit_cursor--;
      if (m_limit_cursor == 0) {
        throw std::runtime_error("Too many files checked (limit: "+std::to_string(m_limit)+")");
      }
      return p1.filename() == filename && !fs::is_directory(p1) && !excluded(p1);
    }

private:
    std::vector<std::filesystem::path> m_locators;
    std::vector<std::filesystem::path> m_excluded;
    bool m_recursive = true;
    size_t m_limit = 1000;
    mutable size_t m_limit_cursor = m_limit;
};


//FIXME: move to cpp file
//https://stackoverflow.com/questions/22794382/are-c11-thread-local-variables-automatically-static
thread_local AssetManager assetManager;
