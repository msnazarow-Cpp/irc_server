struct Message {
    using std::string;
    string time;
    string from;
    string data;
    string to_string() {// TODO:
        return "[" + time + "] " + from + " :" + data;
    }
};
