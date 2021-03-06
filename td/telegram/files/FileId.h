//
// Copyright Aliaksei Levin (levlam@telegram.org), Arseny Smirnov (arseny30@gmail.com) 2014-2018
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once

#include "td/utils/common.h"
#include "td/utils/StringBuilder.h"

#include <functional>
#include <type_traits>

namespace td {

class FileId {
  int32 id = 0;

 public:
  FileId() = default;

  explicit FileId(int32 file_id) : id(file_id) {
  }
  template <class T, typename = std::enable_if_t<std::is_convertible<T, int32>::value>>
  FileId(T file_id) = delete;

  bool empty() const {
    return id <= 0;
  }
  bool is_valid() const {
    return id > 0;
  }

  int32 get() const {
    return id;
  }

  bool operator<(const FileId &other) const {
    return id < other.id;
  }

  bool operator==(const FileId &other) const {
    return id == other.id;
  }

  bool operator!=(const FileId &other) const {
    return id != other.id;
  }
};

struct FileIdHash {
  std::size_t operator()(FileId file_id) const {
    return std::hash<int32>()(file_id.get());
  }
};

inline StringBuilder &operator<<(StringBuilder &string_builder, FileId file_id) {
  return string_builder << file_id.get();
}
}  // namespace td
