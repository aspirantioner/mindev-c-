#ifndef NACKHEADER_H_
#define NACKHEADER_H_

namespace mindev::component{
    class NackHeader{
private:
    long nackReason;
public:
    static const long NackReasonUnkown = 0;
    static const long NackReasonDuplicate = 1;
    static const long NackReasonNoRoute = 2;
    };
}

#endif
