#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

namespace mypage
{
class manage : public drogon::HttpController<manage>
{
  public:
    METHOD_LIST_BEGIN
    // use METHOD_ADD to add your custom processing function here;
    // METHOD_ADD(manage::get, "/{2}/{1}", Get); // path is /mypage/manage/{arg2}/{arg1}
    // METHOD_ADD(manage::your_method_name, "/{1}/{2}/list", Get); // path is /mypage/manage/{arg1}/{arg2}/list
    // ADD_METHOD_TO(manage::your_method_name, "/absolute/path/{1}/{2}/list", Get); // path is /absolute/path/{arg1}/{arg2}/list

    METHOD_ADD(manage::manage_direct, "", Get);
    METHOD_ADD(manage::manage_login, "/login", Get);
    METHOD_ADD(manage::manage_login_submit, "/login", Post);
    METHOD_ADD(manage::manage_changepass, "/changepass", Get);
    METHOD_ADD(manage::manage_changepass_submit, "/changepass", Post);

    METHOD_LIST_END
    // your declaration of processing function maybe like this:
    // void get(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int p1, std::string p2);
    // void your_method_name(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, double p1, int p2) const;

    void manage_direct( const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback ) const;

    void manage_login( const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback ) const;

    void manage_login_submit( const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback ) const;

    void manage_changepass( const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback ) const;

    void manage_changepass_submit( const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback ) const;
};
}
