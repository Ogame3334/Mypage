#include "hello.h"

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

void hello::hello_api_get( const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) const {
    Json::Value data;
    data["message"] = "hello!!";

    auto res = HttpResponse::newHttpJsonResponse(data);

    callback(res);
}

void hello::hello_api_get_name( const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, std::string name ) const {
    std::string key = req->getParameter("key");
    Json::Value data;
    data["message"] = "hello, " + name + "!!";
    data["key"] = key;

    auto res = HttpResponse::newHttpJsonResponse(data);

    callback(res);
}


void hello::hello_api_post( const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) const {
    std::string name = req->getParameter("body");
    Json::Value data;
    std::string message = "hello, ";
    message += name;
    message += "!!";
    data["message"] = message;

    auto res = HttpResponse::newHttpJsonResponse(data);

    callback(res);
    
}