#include "mypage.h"

// Add definition of your processing function here
void mypage::direct( const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) const {
    auto res = HttpResponse::newHttpViewResponse("top.csp");
    
    callback(res);
}