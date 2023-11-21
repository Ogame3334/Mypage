#include "root.h"

// Add definition of your processing function here
void root::direct( const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) const {
    auto res = HttpResponse::newHttpViewResponse("direct.csp");
    res->setStatusCode(k200OK);
    res->setContentTypeCode(CT_TEXT_HTML);
    
    callback(res);   
}