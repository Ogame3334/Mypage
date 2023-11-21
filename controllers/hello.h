#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class hello : public drogon::HttpController<hello>
{
  public:
    METHOD_LIST_BEGIN
    // use METHOD_ADD to add your custom processing function here;
    // METHOD_ADD(hello::get, "/{2}/{1}", Get); // path is /mypage/hello/{arg2}/{arg1}
    // METHOD_ADD(hello::your_method_name, "/{1}/{2}/list", Get); // path is /mypage/hello/{arg1}/{arg2}/list
    // ADD_METHOD_TO(hello::your_method_name, "/absolute/path/{1}/{2}/list", Get); // path is /absolute/path/{arg1}/{arg2}/list

    METHOD_ADD(hello::mypage_hello, "", Get);
    METHOD_ADD(hello::hello_api_get, "/json", Get);
    METHOD_ADD(hello::hello_api_get_name, "/json/{1}", Get);
    METHOD_ADD(hello::hello_api_post, "/json", Post);

    METHOD_LIST_END
    // your declaration of processing function maybe like this:
    // void get(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int p1, std::string p2);
    // void your_method_name(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, double p1, int p2) const;

    void mypage_hello(
      const HttpRequestPtr &req,
      std::function<void(const HttpResponsePtr &)> &&callback);

    void hello_api_get( const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback ) const;
    void hello_api_get_name( const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, std::string name ) const;
    void hello_api_post( const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback ) const;
};
