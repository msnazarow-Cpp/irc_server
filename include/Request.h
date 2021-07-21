#pragma once

# include "utils.h"
# include "Location.h"
# include <ostream>
# include <unistd.h>

enum e_client_status {
  CLOSE_CONNECTION, READY_TO_READ, READY_TO_SEND, SENDING
};

class Request {
 private:
  e_methods method;
  std::string raw_request;
  const int fd_;
  void setMethodFromStr(const std::string &);

  Request();
 public:
  explicit Request(const int fd);
  virtual ~Request();

  e_methods getMethod() const;
  bool isComplete() const;
  int receive();
  void clear();

    bool complete;
};

std::ostream &operator<<(std::ostream &os, const Request &request);


