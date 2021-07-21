#include <libc.h>
#include "Request.h"


Request::Request(const int fd)
        : method(OTHER),
          complete(false),
          fd_(fd) {}

bool Request::isComplete() const { return complete; }

int Request::receive() {
    assert(complete == false);
    int ret = 1;
    char buffer[BUFFER_SIZE + 1];
    size_t i;
    bool read_activated = false;

    return ret;
}

void Request::clear() {
    method = OTHER;
    complete = false;
}


