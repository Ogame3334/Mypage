#include "mypage_hello.h"

using namespace mypage;

// Add definition of your processing function here
void hello::mypage_hello(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback){
    auto res = HttpResponse::newHttpResponse();
    res->setStatusCode(k200OK);
    res->setContentTypeCode(CT_TEXT_HTML);
    res->setBody("<p>hello, world!!</p>");

    callback(res);
}